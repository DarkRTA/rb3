#include "DataFile.h"
#include "obj/DataFlex.h"
#include "os/CritSec.h"
#include "os/Debug.h"
#include "utl/BinStream.h"
#include "utl/MemMgr.h"

static CriticalSection gDataReadCrit; // yes these are the bss offsets. this tu sucks
static DataArray* gArray; // 0x28
static int gNode; // 0x2c
static Symbol gFile; // 0x30
static BinStream* gBinStream;
static int gDataLine; // 0x50

extern "C" void DataFail(const char* x) {
    MILO_FAIL("%s (file %s, line %d)", x, gFile, gDataLine);
}


int ReadEmbeddedFile(const char* c, bool b) {
    CriticalSection* cs = &gDataReadCrit;
    yyrestart(NULL);
    if (DataReadFile(c, b) && !b) MILO_FAIL("Couldn't open embedded file: %s (file %s, line %d)", NULL, gFile.mStr, gDataLine);
    yyrestart(NULL);
    if (cs) cs->Exit();
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

extern "C" int DataInput(void* v, int x) {
    if (gBinStream->Fail()) return false; else if (gBinStream->Eof()) return false; else {
        gBinStream->Read(v, x);
        MILO_ASSERT(!gBinStream->Fail(), 630);
        return x;
    }
}
