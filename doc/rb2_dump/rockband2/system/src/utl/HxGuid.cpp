/*
    Compile unit: C:\rockband2\system\src\utl\HxGuid.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8060C8C4 -> 0x8060CE10
*/
// Range: 0x8060C8C4 -> 0x8060C8F4
void * HxGuid::HxGuid(class HxGuid * const this /* r31 */) {}

// Range: 0x8060C8F4 -> 0x8060C980
void HxGuid::Generate(class HxGuid * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8060C980 -> 0x8060C998
void HxGuid::Clear() {}

// Range: 0x8060C998 -> 0x8060C9D8
unsigned char HxGuid::IsNull() {}

// Range: 0x8060C9D8 -> 0x8060CA60
int HxGuid::Chunk32(const class HxGuid * const this /* r30 */, int i /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8060CA60 -> 0x8060CAF4
void HxGuid::SetChunk32(class HxGuid * const this /* r29 */, int i /* r30 */, int value /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8060CAF4 -> 0x8060CC18
class HxGuid & HxGuid::__as(class HxGuid * const this /* r26 */, class String & hex /* r27 */) {
    // Local variables
    int n; // r31
    class String chunk; // r1+0x8
    unsigned int total; // r30
    unsigned int base; // r29
    int m; // r28
    char value; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8060CC18 -> 0x8060CC68
unsigned char HxGuid::__eq() {}

// Range: 0x8060CC68 -> 0x8060CC90
unsigned char HxGuid::__ne() {}

// Range: 0x8060CC90 -> 0x8060CC94
int * HxGuid::Data() {}

// Range: 0x8060CC94 -> 0x8060CCA8
void HxGuid::SetData() {}

// Range: 0x8060CCA8 -> 0x8060CD54
class BinStream & __ls(class BinStream & s /* r30 */, const class HxGuid & guid /* r31 */) {}

// Range: 0x8060CD54 -> 0x8060CE10
class BinStream & __rs(class BinStream & s /* r30 */, class HxGuid & guid /* r31 */) {
    // Local variables
    int rev; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}


