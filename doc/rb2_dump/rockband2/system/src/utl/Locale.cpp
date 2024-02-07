/*
    Compile unit: C:\rockband2\system\src\utl\Locale.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8060F4CC -> 0x8060FDF0
*/
const char * sIgnoreMissingText; // size: 0x4, address: 0x80A55450
unsigned char sVerboseNotify; // size: 0x1, address: 0x80A55454
struct BootLocaleEntry {
    // total size: 0x8
    const char * name; // offset 0x0, size 0x4
    const char * value; // offset 0x4, size 0x4
};
struct BootLocaleEntry gBootLocaleTable[1]; // size: 0x8, address: 0x8092CF38
class Locale TheLocale; // size: 0x18, address: 0x80989F38
// Range: 0x8060F4CC -> 0x8060FB48
void Locale::Init(class Locale * const this /* r23 */) {
    // Local variables
    const class DataArray * filelist; // r30
    class vector tables; // r1+0x48
    int size; // r29
    int idx; // r28
    const char * filename; // r26
    class DataArray * ordered_table; // r27
    class DataArray * array; // r26
    class DataArray * lastArray; // [invalid]
    int i; // r25
    class DataArray * n; // r24
    int string_size; // r25
    int i; // r26
    int i; // r25

    // References
    // -> class Hyphenator TheHyphenator;
    // -> const char * gNullStr;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP9DataArray;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8060FB48 -> 0x8060FBEC
void Sort(class DataArray * arr /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8060FBEC -> 0x8060FC5C
void Locale::Terminate(class Locale * const this /* r30 */) {
    // References
    // -> const char * gNullStr;
}

static char text[50]; // size: 0x32, address: 0x80989F50
// Range: 0x8060FC5C -> 0x8060FDC4
char * LocalizeSeparatedInt(int num /* r27 */) {
    // Local variables
    const char * sepStr; // r3
    char sep; // r31
    int offset; // r30
    unsigned char less_than_zero; // r29
    char digit[2]; // r1+0x8
    int place; // r28

    // References
    // -> static char text[50];
    // -> class Locale TheLocale;
}

// Range: 0x8060FDC4 -> 0x8060FDF0
static void __sinit_\Locale_cpp() {
    // References
    // -> const char * gNullStr;
    // -> class Locale TheLocale;
}


