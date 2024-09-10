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

struct ConditionalInfo {
    union {
        bool condition;
        int _; // ? ParseNode() doesn't match without this
    };
    Symbol file;
    int line;
};

static CriticalSection gDataReadCrit; // yes these are the bss offsets. this tu sucks
static DataArray* gArray; // 0x28
static int gNode; // 0x2c
static Symbol gFile; // 0x30
static BinStream* gBinStream; // 0x34
static int gOpenArray = kDataTokenFinished; // 0x38 ?
static std::list<ConditionalInfo> gConditional; // 0x48 - actually a list of ConditionalInfo structs
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
    for (std::list<ConditionalInfo>::iterator it = gConditional.begin(); it != gConditional.end(); it++) {
        if (!it->condition) return false;
    }
    return true;
}

bool ParseNode() {
    int token = yylex();
    if (!Defined() && token != kDataTokenIfdef && token != kDataTokenIfndef
        && token != kDataTokenElse && token != kDataTokenEndif) {
        return true;
    }

    char bom[3] = { 0xEF, 0xBB, 0xBF };
    if(gNode == 0 && strncmp(yytext, bom, ARRAY_LENGTH(bom)) == 0){
        if(yyleng > 3) MILO_FAIL("%s starts with a ByteOrderMark, put a line return at the top of its file", gFile);
        else return true;
    }

    if(token == kDataTokenFinished){
        switch(gOpenArray){
            case kDataTokenArrayOpen:
                MILO_FAIL("Array closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            case kDataTokenCommandOpen:
                MILO_FAIL("Command closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            case kDataTokenPropertyOpen:
                MILO_FAIL("Property closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            default: break;
        }
        return false;
    }
    else if(token == kDataTokenArrayClose){
        switch(gOpenArray){
            case kDataTokenFinished:
                MILO_FAIL("File %s ends with open array", gFile);
                break;
            case kDataTokenCommandOpen:
                MILO_FAIL("Command closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            case kDataTokenPropertyOpen:
                MILO_FAIL("Property closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            default: break;
        }
        return false;
    }
    else if(token == kDataTokenPropertyClose){
        switch(gOpenArray){
            case kDataTokenFinished:
                MILO_FAIL("File %s ends with open array", gFile);
                break;
            case kDataTokenArrayOpen:
                MILO_FAIL("Array closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            case kDataTokenCommandOpen:
                MILO_FAIL("Command closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            default: break;
        }
        return false;
    }
    else if(token == kDataTokenCommandClose){
        switch(gOpenArray){
            case kDataTokenFinished:
                MILO_FAIL("File %s ends with open array", gFile);
                break;
            case kDataTokenArrayOpen:
                MILO_FAIL("Array closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            case kDataTokenPropertyOpen:
                MILO_FAIL("Property closed incorrectly (file %s, line %d)", gFile, gDataLine);
                break;
            default: break;
        }
        return false;
    }

    if(token == kDataTokenMerge){
        if(yylex() != kDataTokenSymbol){
            MILO_FAIL("DataReadFile: merging a non-symbol (file %s, line %d)", gFile, gDataLine);
        }
        if(gCachingFile){
            PushBack(DataNode(kDataMerge, Symbol(yytext).Str()));
        }
        else {
            bool usingEmbedded = false;
            DataArray* fileArr = DataGetMacro(yytext);
            if(!fileArr) {
                fileArr = ReadEmbeddedFile(yytext, true);
                usingEmbedded = true;
            }
            if(fileArr && fileArr->Size() == 0){
                MILO_FAIL("Empty merge file (possibly a re-included file): %s", yytext);
            }
            gArray->Resize(gNode);
            DataMergeTags(gArray, fileArr);
            gNode = gArray->Size();
            if(usingEmbedded) {
                fileArr->Release();
            }
        }
        return true;
    }
    else if (token == kDataTokenInclude || token == kDataTokenIncludeOptional) {
        bool required = token == kDataTokenInclude;
        if(yylex() != kDataTokenSymbol){
            MILO_FAIL("DataReadFile: including a non-symbol (file %s, line %d)", gFile, gDataLine);
        }
        if(gCachingFile){
            PushBack(DataNode(kDataInclude, Symbol(yytext).Str()));
        }
        else {
            DataArray* fileArr = ReadEmbeddedFile(yytext, required);
            if (fileArr) {
                for (int i = 0; i < fileArr->Size(); i++) {
                    PushBack(fileArr->Node(i));
                }
                fileArr->Release();
            }
        }
        return true;
    }

    switch(token){
        case kDataTokenIfdef:
        case kDataTokenIfndef: {
            bool positive = token == kDataTokenIfdef;

            int symToken = yylex();
            bool isSymbol = symToken == kDataTokenSymbol || symToken == kDataTokenQuotedSymbol;
            if (!isSymbol) {
                MILO_FAIL("DataReadFile: not macro symbol (file %s, line %d)", gFile, gDataLine);
            }

            char *text;
            if (symToken == kDataTokenQuotedSymbol) {
                // Strip quotes from quoted symbol
                yytext[yyleng - 1] = '\0';
                text = yytext + 1;
            } else {
                text = yytext;
            }

            Symbol macro(text);
            if (positive) {
                if(gCachingFile){
                    PushBack(DataNode(kDataIfdef, macro.Str()));
                }
                else {
                    bool defined = DataGetMacro(macro) != 0;

                    ConditionalInfo info;
                    info.condition = defined;
                    info.file = gFile;
                    info.line = gDataLine;
                    gConditional.push_back(info);
                }
            }
            else {
                if(gCachingFile){
                    PushBack(DataNode(kDataIfndef, macro.Str()));
                }
                else {
                    bool ndefined = DataGetMacro(macro) == 0;

                    ConditionalInfo info;
                    info.condition = ndefined;
                    info.file = gFile;
                    info.line = gDataLine;
                    gConditional.push_back(info);
                }
            }
            return true;
        }

        case kDataTokenElse: {
            if(gCachingFile){
                PushBack(DataNode(kDataElse, 0));
            }
            else {
                if (gConditional.empty()) {
                    MILO_FAIL("DataReadFile: #else not in conditional (file %s, line %d)", gFile, gDataLine);
                }
                gConditional.back().condition = !gConditional.back().condition;
            }
            return true;
        }

        case kDataTokenEndif: {
            if(gCachingFile){
                PushBack(DataNode(kDataEndif, 0));
            }
            else {
                if (gConditional.empty()) {
                    MILO_FAIL("DataReadFile: #endif not in conditional (file %s, line %d)", gFile, gDataLine);
                }
                gConditional.pop_back();
            }
            return true;
        }

        case kDataTokenAutorun: {
            int cmdToken = yylex();
            if (cmdToken != kDataTokenCommandOpen) {
                MILO_FAIL("DataReadFile: not command (file %s, line %d)", gFile, gDataLine);
            }

            int openArray = gOpenArray;
            gOpenArray = cmdToken;
            DataArray *array = ParseArray();
            gOpenArray = openArray;

            DataNode node(array, kDataCommand);
            if(gCachingFile){
                PushBack(DataNode(kDataAutorun, 0));
                PushBack(node);
            }
            else {
                node.Command(array)->Execute();
            }

            array->Release();
            return true;
        }

        case kDataTokenDefine: {
            if (yylex() != kDataTokenSymbol) {
                MILO_FAIL("DataReadFile: not symbol (file %s, line %d)", gFile, gDataLine);
            }

            Symbol macro(yytext);

            int cmdToken = yylex();
            if (cmdToken != kDataTokenArrayOpen) {
                MILO_FAIL("DataReadFile: not array (file %s, line %d)", gFile, gDataLine);
            }

            int openArray = gOpenArray;
            gOpenArray = cmdToken;
            DataArray *array = ParseArray();
            gOpenArray = openArray;

            if(gCachingFile){
                PushBack(DataNode(kDataDefine, macro.Str()));
                PushBack(DataNode(array, kDataArray));
            }
            else {
                DataSetMacro(macro, array);
            }

            array->Release();
            return true;
        }

        case kDataTokenUndef: {
            if (yylex() != kDataTokenSymbol) {
                MILO_FAIL("DataReadFile: not synbol (file %s, line %d)", gFile, gDataLine);
            }

            Symbol macro(yytext);
            if(gCachingFile){
                PushBack(DataNode(kDataUndef, macro.Str()));
            }
            else {
                DataSetMacro(macro, nullptr);
            }

            return true;
        }

        case kDataTokenArrayOpen:
        case kDataTokenPropertyOpen:
        case kDataTokenCommandOpen: {
            int openArray = gOpenArray;
            gOpenArray = token;
            DataArray *array = ParseArray();
            gOpenArray = openArray;

            DataType type;
            if (token == kDataTokenArrayOpen) {
                type = kDataArray;
            }
            else if (token == kDataTokenCommandOpen) {
                type = kDataCommand;
            }
            else {
                type = kDataProperty;
            }

            PushBack(DataNode(array, type));
            array->Release();

            return true;
        }

        case kDataTokenVar: {
            PushBack(&DataVariable(yytext + 1));
            return true;
        }

        case kDataTokenUnhandled: {
            PushBack(DataNode(kDataUnhandled, 0));
            return true;
        }

        case kDataTokenInt: {
            PushBack(atoi(yytext));
            return true;
        }

        case kDataTokenHex: {
            int i = 0;

            // Parse in reverse, up until the `x` of `0x`
            int base = 1;
            // TODO: yytext needs to be loaded twice here, but is being optimized to one load
            for (char *c = yytext + strlen(yytext) - 1; *c != 'x'; --c, base <<= 4) {
                if (*c >= 'a') {
                    i += (*c - 'a' + 10) * base;
#ifdef NON_MATCHING
                } else if (*c >= 'A') {
#else
                } else if (*c > 'A') { //! BUG: should be >=, else `A` won't parse correctly
#endif
                    i += (*c - 'A' + 10) * base;
                } else {
                    i += (*c - '0') * base;
                }
            }

            PushBack(i);
            return true;
        }

        case kDataTokenFloat: {
            PushBack((float)atof(yytext));
            return true;
        }

        default:
            break;

        // case kDataTokenString:
        // case kDataTokenArrayClose:
        // case kDataTokenPropertyClose:
        // case kDataTokenCommandClose:
        // case kDataTokenInclude:
        // case kDataTokenIncludeOptional:
        // case kDataTokenMerge:

        // case kDataTokenSymbol:
        // case kDataTokenQuotedSymbol:

        // case kDataTokenFinished:
        // default:
        //     if(yylex() != kDataTokenSymbol){
        //         MILO_FAIL("DataReadFile: including a non-symbol (file %s, line %d)", gFile, gDataLine);
        //     }
        //     if(gCachingFile){
        //         PushBack(DataNode(kDataInclude, Symbol(yytext).Str()));
        //     }
        //     return true;
    }

    if(token == kDataTokenSymbol || token == kDataTokenQuotedSymbol){
        char *text;
        if (token == kDataTokenQuotedSymbol) {
            // Strip quotes from quoted symbol
            yytext[yyleng - 1] = '\0';
            text = yytext + 1;
        } else {
            text = yytext;
        }

        Symbol sym(text);
        DataArray* macro = DataGetMacro(sym);
        bool b = macro && !gCachingFile;
        if(b){
            for(int i = 0; i < macro->Size(); i++){
                PushBack(macro->Node(i));
            }
        }
        else {
            PushBack(sym);
        }

        return true;
    }
    else if(token == kDataTokenString){
        yytext[yyleng - 1] = '\0';
        char* text = yytext + 1;

        for(char* c = text; *c != '\0'; c++){
            bool escaped = false;
            if(*c == '\\'){
                if(c[1] == 'n'){
                    *c = '\n';
                    escaped = true;
                }
                else if(c[1] == 'q'){
                    *c = '\"';
                    escaped = true;
                }
            }
            else if(*c == '\n'){
                gDataLine++;
            }

            if(escaped){
                for (char* d = c + 1; *d != '\0'; d++) {
                    *d = *(d + 1);
                }
            }
        }

        PushBack(text);
        return true;
    }
    else {
        MILO_FAIL("DataReadFile: Unrecognized token %d (file %s, line %d)", token, gFile, gDataLine);
        return false;
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
