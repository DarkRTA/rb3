/*
    Compile unit: C:\rockband2\system\src\utl\StringTable.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8062275C -> 0x80622BC0
*/
// Range: 0x8062275C -> 0x806227B0
void * StringTable::StringTable(class StringTable * const this /* r31 */) {}

// Range: 0x806227B0 -> 0x806228B0
void * StringTable::~StringTable(class StringTable * const this /* r30 */) {
    // Local variables
    int i; // r29
}

// Range: 0x806228B0 -> 0x80622984
void StringTable::Reserve(class StringTable * const this /* r30 */, int size /* r31 */) {
    // Local variables
    int curSize; // r0
    struct Buf buf; // r1+0x10
}

// Range: 0x80622984 -> 0x80622B1C
char * StringTable::Add(class StringTable * const this /* r29 */, const char * str /* r30 */) {
    // Local variables
    int len; // r1+0x8
    int size; // r28

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80622B1C -> 0x80622B80
int StringTable::UsedSize() {
    // Local variables
    int size; // r5
    int i; // r6
}

// Range: 0x80622B80 -> 0x80622BC0
int StringTable::Size() {
    // Local variables
    int size; // r5
    int i; // r6
}

struct {
    // total size: 0x8
} __RTTI__PQ211StringTable3Buf; // size: 0x8, address: 0x8092F2F8

