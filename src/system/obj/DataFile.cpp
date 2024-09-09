#include "DataFile.h"
#include "macros.h"
#include "obj/Data.h"
#include "obj/DataFlex.h"
#include "os/CritSec.h"
#include "os/Debug.h"
#include "os/File.h"
#include "os/ThreadCall.h"
#include "utl/BinStream.h"
#include "utl/BufStream.h"
#include "utl/ChunkStream.h"
#include "utl/Compress.h"
#include "utl/Loader.h"
#include "utl/MemMgr.h"
#include "utl/TextFileStream.h"
#include "obj/DataUtl.h"
#include <cstddef>
#include <cstdlib>
#include <map>

static CriticalSection gDataReadCrit; // yes these are the bss offsets. this tu sucks
static DataArray* gArray; // 0x28
static int gNode; // 0x2c
static Symbol gFile; // 0x30
static BinStream* gBinStream; // 0x34
static int gOpenArray; // 0x38 ?
static std::list<bool> gConditional; // 0x48 - actually a list of ConditionalInfo structs
int gDataLine; // 0x50
static std::map<String, DataNode> gReadFiles; // 0x60

static bool gCachingFile;
static bool gReadingFile;

void DataFail(const char* x) {
    MILO_FAIL("%s (file %s, line %d)", x, gFile, gDataLine);
}

DataArray* ReadEmbeddedFile(const char* c, bool b) {
    CritSecTracker cst(&gDataReadCrit);
    DataArray* ret;
    const char* x = FileMakePath(FileGetPath(gFile.Str(), NULL), c, NULL);

    int a = gNode;
    BinStream* bs = gBinStream;
    int d = gDataLine;
    Symbol e = gFile;
    DataArray* f = gArray;
    int g = gOpenArray;

    yyrestart(NULL);
    ret = DataReadFile(x, b);
    if (b && !ret) MILO_FAIL("Couldn't open embedded file: %s (file %s, line %d)", x, f->File(), f->Line());

    gNode = a;
    gBinStream = bs;
    gDataLine = d;
    gFile = e;
    gArray = f;
    gOpenArray = g;

    yyrestart(NULL);
    return ret;
}

void PushBack(const DataNode& n) {
    if (gNode == gArray->mSize) {
        if (gNode >= 0x7FFF) {
            MILO_FAIL("%s(%d): array size > max %d lines", gArray->File(), gArray->Line(), 0x7FFF);
        }
        MemDoTempAllocations m(true, false);
        int x = gNode << 1;
        gArray->Resize(x <= 0x7FFF ? x : 0x7FFF);
    }
    gArray->Node(gNode++) = n;
}

bool Defined() {
    for (std::list<bool>::iterator it = gConditional.begin(); it != gConditional.end(); it++) {
        if (*it == false) return false;
    }
    return true;
}

bool ParseNode() {
    int lex = yylex();
    bool defined = Defined();
    if(!defined && (lex - 0x16U > 2) && lex != 0x14) return true;
    short ss = 0xEFBB; // some ro data
    char cc = 0xBF; // some other ro data
    if(gNode == 0 && strncmp(yytext, (char*)&ss, 3) == 0){
        if(yyleng > 3) MILO_FAIL("%s starts with a ByteOrderMark, put a line return at the top of its file", gFile);
        else return true;
    }
    int i7 = gOpenArray;
    if(lex == 0){
        switch(gOpenArray){
            case 7:
                MILO_FAIL("Array closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            case 0xB:
                MILO_FAIL("Command closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            case 9:
                MILO_FAIL("Property closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            default: break;
        }
        return false;
    }
    else if(lex == 8){
        switch(gOpenArray){
            case 0:
                MILO_FAIL("File %s ends with open array", gFile);
                break;
            case 0xB:
                MILO_FAIL("Command closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            case 9:
                MILO_FAIL("Property closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            default: break;
        }
        return false;
    }
    else if(lex == 10){
        switch(gOpenArray){
            case 0:
                MILO_FAIL("File %s ends with open array", gFile);
                break;
            case 7:
                MILO_FAIL("Array closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            case 0xB:
                MILO_FAIL("Command closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            default: break;
        }
        return false;
    }
    else if(lex == 0xC){
        switch(gOpenArray){
            case 0:
                MILO_FAIL("File %s ends with open array", gFile);
                break;
            case 7:
                MILO_FAIL("Array closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            case 9:
                MILO_FAIL("Property closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            default: break;
        }
        return false;
    }
    else if(lex == 0x11){
        if(yylex() != 5){
            MILO_FAIL("DataReadFile: merging a non-symbol (file %s, line %d)", gFile, gDataLine);
        }
        if(gCachingFile){
            Symbol sym(yytext);
            PushBack(DataNode(kDataMerge, (int)&sym));
        }
        else {
            DataArray* fileArr = DataGetMacro(yytext);
            if(!fileArr) fileArr = ReadEmbeddedFile(yytext, true);
            if(fileArr && fileArr->Size() == 0){
                MILO_FAIL("Empty merge file (possibly a re-included file): %s", yytext);
            }
            gArray->Resize(gNode);
            DataMergeTags(gArray, fileArr);
            gNode = gArray->Size();
            if(fileArr) fileArr->Release();
        }
        return true;
    }
    else switch(lex){
        default:
            if(yylex() != 5){
                MILO_FAIL("DataReadFile: including a non-symbol (file %s, line %d)", gFile, gDataLine);
            }
            if(gCachingFile){
                Symbol sym(yytext);
                PushBack(DataNode(kDataInclude, (int)&sym));
            }
            return true;
        case 0x14:
        case 0x16:
            MILO_FAIL("DataReadFile: not macro symbol (file %s, line %d)", gFile, gDataLine);
            return true;
        case 0x17:
            MILO_FAIL("DataReadFile: #else not in conditional (file %s, line %d)", gFile, gDataLine);
            return true;
        case 0x18:
            MILO_FAIL("DataReadFile: #endif not in conditional (file %s, line %d)", gFile, gDataLine);
            return true;
        case 0xE:
            MILO_FAIL("DataReadFile: not command (file %s, line %d)", gFile, gDataLine);
            return true;
        case 0xD:
            MILO_FAIL("DataReadFile: not symbol (file %s, line %d)", gFile, gDataLine);
            MILO_FAIL("DataReadFile: not array (file %s, line %d)", gFile, gDataLine);
            return true;
        case 0x15:
            MILO_FAIL("DataReadFile: not synbol (file %s, line %d)", gFile, gDataLine);
            return true;
        case 9:
        case 0xB:
        case 7:
            break;
        case 0x12:
            PushBack(DataNode(&DataVariable(yytext + 1)));
            return true;
            break;
        case 0x13:
            PushBack(DataNode(kDataUnhandled, 0));
            return true;
            break;
        case 3:
            PushBack(DataNode(atoi(yytext)));
            return true;
            break;
        case 1:
            break;
        case 2:
            PushBack(DataNode((float)atof(yytext)));
            return true;
            break;
        case 0:
        case 4:
        case 5:
        case 6:
        case 8:
        case 10:
        case 0xc:
        case 0xf:
        case 0x10:
        case 0x11:
            if(lex - 5U < 2){
                char* p = yytext;
                if(lex == 6){
                    yytext[yyleng - 1] = '\0';
                    p = yytext + 1;
                }
                Symbol psym(p);
                DataArray* arr = DataGetMacro(psym);
                if(arr && !gCachingFile){
                    for(int i = 0; i < arr->Size(); i++){
                        PushBack(arr->Node(i));
                    }
                }
                else PushBack(DataNode(psym));
                return true;
            }
            else if(lex == 4){
                yytext[yyleng - 1] = '\0';
                char* p = yytext + 1;
                for(char* pp = p; *pp != '\0'; pp++){
                    bool bbb = false;
                    if(*pp == '\\'){
                        if(pp[1] == 'n'){
                            *pp = '\n';
                            bbb = true;
                        }
                        else if(pp[1] == 'q'){
                            *pp = '\"';
                            bbb = true;
                        }
                    }
                    else if(*pp == '\n'){
                        gDataLine++;
                    }
                    char* ppp = pp;
                    if(bbb){
                        // TODO: fill out
                    }
                }
                PushBack(DataNode(p));
                return true;
            }
            else {
                MILO_FAIL("DataReadFile: Unrecognized token %d (file %s, line %d)", lex, gFile, gDataLine);
                return false;
            }
            break;
    }
}

DataArray* ParseArray() {
    DataArray* sav = gArray;
    int nod = gNode;
    DataArray* da = new DataArray(16);
    gArray = da;
    da->SetFileLine(gFile, gDataLine);
    gNode = 0;
    do ; while (ParseNode());
    gArray->Resize(gNode);
    da = gArray;
    gArray = sav; gNode = nod;
    return da;
}

int DataInput(void* v, int x) {
    if (gBinStream->Fail()) {
        return 0;
    } else if (gBinStream->Eof()) {
        return 0;
    } else {
        gBinStream->Read(v, x);
        MILO_ASSERT(!gBinStream->Fail(), 630);
        return x;
    }
}

DataArray* ReadCacheStream(BinStream& bs, const char* cc){
    CritSecTracker cst(&gDataReadCrit);
    bs.EnableReadEncryption();
    DataArray::SetFile(cc);
    DataArray* arr;
    bs >> arr;
    bs.DisableEncryption();
    return arr;
}

DataArray* DataReadString(const char* c) {
    return DataReadStream(&BufStream((void*)c, strlen(c), true));
}

static const char* CachedDataFile(const char* cc, bool& b){
    bool loc = FileIsLocal(cc);
    if(strstr(cc, ".dtb")){
        b = true;
        return cc;
    }
    else if(UsingCD() && !loc){
        b = true;
        cc = MakeString("%s/gen/%s.dtb", FileGetPath(cc, 0), FileGetBase(cc, 0));
        return cc;
    }
    else b = false;
    return cc;
}

void BeginDataRead() {
    MILO_ASSERT(gReadFiles.size() == 0, 689);
    gReadingFile = true;
}

DataArray* DataReadStream(BinStream* bs) {
    CritSecTracker cst(&gDataReadCrit);
    gBinStream = bs;
    gFile = Symbol(gBinStream->Name());
    gDataLine = 1;
    gOpenArray = NULL;
    int old_cond_size = gConditional.size();
    DataArray* ret = ParseArray();

    if (gConditional.size() != old_cond_size) MILO_FAIL("DataReadFile: conditional block not closed (file %s (%s:%d)", gFile, "", gDataLine);
    return ret;
}

DataLoader::DataLoader(const FilePath& fp, LoaderPos pos, bool b) : Loader(fp, pos), unk18(""), unk24(NULL),
    fileobj(NULL), filesize(0), unk30(0), unk34(b), unk38(0) {
    const char* new_str = fp.c_str();
    if (!fp.contains("dlc/")) {
        if (fp.contains("nand/")) {
            unk34 = false;
        }
        new_str = CachedDataFile(new_str, unk34);
    }
    unk18 = new_str;
    ptmf = NULL;
}

void DataLoader::OpenFile() {
    if ((fileobj = NewFile(unk18.c_str(), 2)) && !fileobj->Fail()) {
        unk30 = _MemAlloc((filesize = fileobj->Size()), 0);
        fileobj->ReadAsync(unk30, filesize);
        ptmf = LoadFile;
    } else {
        if (*unk18.c_str()) MILO_WARN("Could not load: %s", FileLocalize(mFile.c_str(), NULL));
        ptmf = DoneLoading;
    }
}

void DataLoader::LoadFile() {
    if (unk38 != 0) {
        Timer::Sleep(0);
        ThreadCallPoll();
    } else {
        int x;
        if (fileobj->ReadDone(x)) {
            if (fileobj->Fail()) {
                ThreadDone(NULL);
                return;
            }
        unk38 = new DataLoaderThreadObj(this, NULL, fileobj, filesize, unk18.c_str(), unk30, unk34);
        ThreadCall(unk38);
        }
    }
}

void DataLoader::DoneLoading() { }

DataLoader::~DataLoader() {
    if (unk38) TheLoadMgr.PollUntilLoaded(this, NULL);
    if (!IsLoaded()) {
        delete fileobj;
        _MemFree(unk30);
    } else if (unk24) unk24->Release();
}

DataArray* DataLoader::Data() {
    MILO_ASSERT(IsLoaded(), 981);
    return unk24;
}

bool DataLoader::IsLoaded() const {
    return ptmf == DoneLoading;
}

void DataLoader::ThreadDone(DataArray* da) {
    MILO_ASSERT(MainThread(), 1001);
    unk24 = da;
    delete unk38;
    unk38 = NULL;
    if (unk30) {
        _MemFree(unk30);
        unk30 = NULL;
    }
    delete fileobj;
    fileobj = NULL;
    ptmf = DoneLoading;
}

union __bastard {
    int big;
    struct {
        u8 s1, s2, s3, s4;
    };
};

void* LoadDtz(const char* c, int i) {
    char* cc = const_cast<char*>(c + i);
    __bastard evil; evil.big = 0;
    evil.s1 = cc[-1];
    evil.s2 = cc[-2];
    evil.s3 = cc[-3];
    evil.s4 = cc[-4];
    int decompSize = evil.big;
    MILO_ASSERT(decompSize > 0, 1176);
    void* pDecompBuf = _MemAlloc(decompSize, 0);
    MILO_ASSERT(pDecompBuf, 1190);
    DecompressMem(c, i - 4, pDecompBuf, decompSize, false, NULL);
    BufStream bfs(pDecompBuf, decompSize, true);
    DataArray* da = NULL;
    bfs >> da;
    if (pDecompBuf) _MemFree(pDecompBuf);
    pDecompBuf = (void*)da;
    return pDecompBuf;
}

void DataWriteFile(const char* c, const DataArray* da, int i) {
    TextStream* ts;
    if (c) ts = new TextFileStream(c, false);
    else ts = new Debug;
    for (;i < da->Size(); i++) {
        da->Node(i).Print(*ts, false);
        *ts << "\n";
    }
    delete ts;
}
