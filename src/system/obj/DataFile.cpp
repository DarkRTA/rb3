#include "DataFile.h"
#include "obj/Data.h"
#include "obj/DataFlex.h"
#include "os/CritSec.h"
#include "os/Debug.h"
#include "os/File.h"
#include "utl/BinStream.h"
#include "utl/BufStream.h"
#include "utl/MemMgr.h"
#include "utl/TextFileStream.h"
#include <cstddef>

static CriticalSection gDataReadCrit; // yes these are the bss offsets. this tu sucks
static DataArray* gArray; // 0x28
static int gNode; // 0x2c
static Symbol gFile; // 0x30
static BinStream* gBinStream; // 0x34
static int gOpenArray; // 0x38 ?
static std::list<bool> gConditional; // 0x48
static int gDataLine; // 0x50
static std::vector<int> gReadFiles; // 0x60

static bool gReadingFile;

extern "C" void DataFail(const char* x) {
    MILO_FAIL("%s (file %s, line %d)", x, gFile, gDataLine);
}


DataArray* ReadEmbeddedFile(const char* c, bool b) {
    CriticalSection* cs = &gDataReadCrit;
    DataArray* ret;
    if (cs) cs->Enter();
    const char* x = FileMakePath(FileGetPath(gFile.Str(), NULL), c, NULL);

    int a = gNode; BinStream* bs = gBinStream; int d = gDataLine;
    Symbol e = gFile; DataArray* f = gArray; int g = gOpenArray;

    yyrestart(NULL);
    if ((ret = DataReadFile(x, b)) && !b) MILO_FAIL("Couldn't open embedded file: %s (file %s, line %d)", x, gArray->File(), gArray->Line());
    
    gNode = a; gBinStream = bs; gDataLine = d;
    gFile = e; gArray = f; gOpenArray = g;

    yyrestart(NULL);
    if (cs) cs->Exit();
    return ret;
}

void PushBack(const DataNode& n) {
    if (gNode == gArray->mSize) {
        if (gNode >= 0x7FFF) {
            MILO_FAIL("%s(%d): array size > max %d lines", gArray->mFile.mStr, (int)gArray->mLine, 0x7FFF);
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

extern "C" int DataInput(void* v, int x) {
    if (gBinStream->Fail()) return false; else if (gBinStream->Eof()) return false; else {
        gBinStream->Read(v, x);
        MILO_ASSERT(!gBinStream->Fail(), 630);
        return x;
    }
}

DataArray* DataReadString(const char* c) {
    return DataReadStream(&BufStream((void*)c, strlen(c), true));
}

void BeginDataRead() {
    MILO_ASSERT(gReadFiles.size() == 0, 689);
    gReadingFile = true;
}

DataArray* DataReadStream(BinStream* bs) {
    CriticalSection* cs = &gDataReadCrit;
    if (cs) cs->Enter();
    gFile = Symbol(gBinStream->Name());
    gDataLine = 1;
    int old_cond_size = gConditional.size();
    DataArray* ret = ParseArray();

    if (gConditional.size() != old_cond_size) MILO_FAIL("DataReadFile: conditional block not closed (file %s (%s:%d)", gFile);
    if (cs) cs->Exit();
    return ret;
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
