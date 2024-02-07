/*
    Compile unit: C:\rockband2\system\src\obj\DataFile.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805D2DDC -> 0x805D4640
*/
static class DataArray * gArray; // size: 0x4, address: 0x80A54E48
static int gNode; // size: 0x4, address: 0x80A54E4C
static class Symbol gFile; // size: 0x4, address: 0x80A54E50
static class BinStream * gStream; // size: 0x4, address: 0x80A54E54
static int gOpenArray; // size: 0x4, address: 0x80A54E58
static class list gConditional; // size: 0x8, address: 0x80988E60
static unsigned char gCachingFile; // size: 0x1, address: 0x80A54E5C
int gDataLine; // size: 0x4, address: 0x80A54E60
// Range: 0x805D2DDC -> 0x805D2E28
void DataFail() {
    // References
    // -> class Debug TheDebug;
    // -> int gDataLine;
    // -> static class Symbol gFile;
}

// Range: 0x805D2E28 -> 0x805D2EFC
static class DataArray * ReadEmbeddedFile(const char * file /* r24 */, unsigned char fail /* r23 */) {
    // Local variables
    const char * dir; // r0
    const char * path; // r30
    int node; // r29
    class BinStream * stream; // r28
    int line; // r27
    class DataArray * array; // r26
    int openArray; // r25
    class DataArray * newArray; // r24

    // References
    // -> class Debug TheDebug;
    // -> static int gOpenArray;
    // -> static class DataArray * gArray;
    // -> int gDataLine;
    // -> static class BinStream * gStream;
    // -> static int gNode;
    // -> static class Symbol gFile;
}

// Range: 0x805D2EFC -> 0x805D2F5C
static void PushBack(const class DataNode & n /* r31 */) {
    // References
    // -> static int gNode;
    // -> static class DataArray * gArray;
}

// Range: 0x805D2F5C -> 0x805D2FBC
static unsigned char Defined() {
    // Local variables
    struct _List_iterator i; // r1+0x10

    // References
    // -> static class list gConditional;
}

// Range: 0x805D2FBC -> 0x805D4284
static unsigned char ParseNode() {
    // Local variables
    int token; // r30
    class DataArray * array; // r30
    unsigned char fail; // r30
    class DataArray * array; // r30
    int i; // r31
    unsigned char ifdef; // r29
    char * val; // r4
    class Symbol condition; // r1+0xBC
    int openArray; // r29
    class DataArray * array; // r31
    class DataNode node; // r1+0x158
    class Symbol macro; // r1+0xB8
    int openArray; // r29
    class DataArray * array; // r31
    class Symbol macro; // r1+0xB4
    int openArray; // r29
    class DataArray * array; // r31
    enum DataType type; // r5
    int i; // r29
    int base; // r30
    char * c; // r4
    char * val; // r4
    class Symbol sym; // r1+0xB0
    class DataArray * macro; // r29
    int i; // r30
    char * val; // r4
    char * c; // r5
    unsigned char escaped; // r6
    char * d; // r3

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<b>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class list gConditional;
    // -> int yyleng;
    // -> static int gNode;
    // -> static class DataArray * gArray;
    // -> char * yytext;
    // -> static unsigned char gCachingFile;
    // -> int gDataLine;
    // -> class Debug TheDebug;
    // -> static class Symbol gFile;
    // -> static int gOpenArray;
}

// Range: 0x805D4284 -> 0x805D4320
static class DataArray * ParseArray() {
    // Local variables
    class DataArray * lastArray; // r31
    int lastNode; // r30
    class DataArray * array; // r0

    // References
    // -> int gDataLine;
    // -> static class Symbol gFile;
    // -> static int gNode;
    // -> static class DataArray * gArray;
}

// Range: 0x805D4320 -> 0x805D4380
static class DataArray * ReadCacheStream(class BinStream & stream /* r30 */, const char * file /* r31 */) {
    // Local variables
    class DataArray * array; // r1+0xC
}

// Range: 0x805D4380 -> 0x805D43E0
class DataArray * DataReadString(const char * str /* r31 */) {
    // Local variables
    class BufStream buf; // r1+0x8
}

// Range: 0x805D43E0 -> 0x805D44CC
void * DataLoader::~DataLoader(class DataLoader * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__10DataLoader;
}

// Range: 0x805D44CC -> 0x805D44DC
unsigned char DataLoader::IsLoaded() {}

// Range: 0x805D44DC -> 0x805D45DC
void DataLoader::PollLoading(class DataLoader * const this /* r31 */) {
    // Local variables
    int bytes; // r1+0x8
    class BufStream b; // r1+0xC
}

struct {
    // total size: 0x14
} __vt__10DataLoader; // size: 0x14, address: 0x809278D4
// Range: 0x805D45DC -> 0x805D4640
static void __sinit_\DataFile_cpp() {
    // References
    // -> static class list gConditional;
    // -> static class Symbol gFile;
    // -> const char * gNullStr;
}


