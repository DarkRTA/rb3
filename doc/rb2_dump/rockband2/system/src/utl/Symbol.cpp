/*
    Compile unit: C:\rockband2\system\src\utl\Symbol.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80622E68 -> 0x80623404
*/
static class StringTable * gStringTable; // size: 0x4, address: 0x80A55530
class KeylessHash {
    // total size: 0x18
    const char * * mEntries; // offset 0x0, size 0x4
    int mSize; // offset 0x4, size 0x4
    unsigned char mOwnEntries; // offset 0x8, size 0x1
    int mNumEntries; // offset 0xC, size 0x4
    const char * mEmpty; // offset 0x10, size 0x4
    const char * mRemoved; // offset 0x14, size 0x4
};
static class KeylessHash gHashTable; // size: 0x18, address: 0x8098A3D8
// Range: 0x80622E68 -> 0x80622F38
void * Symbol::Symbol(class Symbol * const this /* r30 */, const char * str /* r1+0x8 */) {
    // Local variables
    const char * * pval; // r0

    // References
    // -> class Debug TheDebug;
    // -> static class StringTable * gStringTable;
    // -> static class KeylessHash gHashTable;
    // -> const char * gNullStr;
}

// Range: 0x80622F38 -> 0x806231AC
static class DataNode PrintSymbolTable(class DataArray * d /* r25 */) {
    // Local variables
    class vector vec; // r1+0x18
    const char * * s; // r26
    int i; // r26

    // References
    // -> static class StringTable * gStringTable;
    // -> static class KeylessHash gHashTable;
    // -> class Debug TheDebug;
}

struct Alpha {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x806231AC -> 0x80623210
void Symbol::PreInit(int stringSize /* r30 */, int hashSize /* r31 */) {
    // References
    // -> static class KeylessHash gHashTable;
    // -> static class StringTable * gStringTable;
}

// Range: 0x80623210 -> 0x80623268
void Symbol::Init() {
    // References
    // -> static class StringTable * gStringTable;
}

// Range: 0x80623268 -> 0x806232A8
void Symbol::Terminate() {
    // References
    // -> static class KeylessHash gHashTable;
    // -> static class StringTable * gStringTable;
}

// Range: 0x806232A8 -> 0x8062339C
char * * KeylessHash::Find(class KeylessHash * const this /* r28 */, const char * const & key /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class DebugWarner _dw; // size: 0x100, address: 0x8098A3F0
// Range: 0x8062339C -> 0x80623404
static void __sinit_\Symbol_cpp() {
    // References
    // -> static class KeylessHash gHashTable;
}


