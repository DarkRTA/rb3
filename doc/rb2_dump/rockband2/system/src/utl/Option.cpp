/*
    Compile unit: C:\rockband2\system\src\utl\Option.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8061FFB4 -> 0x806202D8
*/
// Range: 0x8061FFB4 -> 0x80620084
static class DataNode DataOptionStr(class DataArray * a /* r31 */) {
    // Local variables
    const char * str; // r4
}

// Range: 0x80620084 -> 0x80620170
static class DataNode DataOptionSym(class DataArray * a /* r31 */) {
    // Local variables
    class Symbol sym; // r1+0xC

    // References
    // -> const char * gNullStr;
}

// Range: 0x80620170 -> 0x806201CC
static class DataNode DataOptionBool(class DataArray * a /* r31 */) {}

// Range: 0x806201CC -> 0x80620248
static char * * FindOption(const char * option /* r30 */) {
    // Local variables
    const char * * i; // r31

    // References
    // -> class vector TheSystemArgs;
}

// Range: 0x80620248 -> 0x806202D8
unsigned char OptionBool(unsigned char def /* r31 */) {
    // Local variables
    const char * * i; // r0

    // References
    // -> class vector TheSystemArgs;
}


