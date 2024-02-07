/*
    Compile unit: C:\rockband2\system\src\utl\Hyphenator.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8060CE10 -> 0x8060DE4C
*/
class Hyphenator TheHyphenator; // size: 0x20, address: 0x80989EA8
// Range: 0x8060CE10 -> 0x8060CE74
unsigned char hy_isspace() {
    // References
    // -> struct __locale _current_locale;
}

// Range: 0x8060CE74 -> 0x8060CED8
unsigned char hy_ispunct() {
    // References
    // -> struct __locale _current_locale;
}

// Range: 0x8060CED8 -> 0x8060CFE0
void ValidateHyphenation(const char * str /* r28 */) {
    // Local variables
    int points[30]; // r1+0x8
    char verify[1024]; // r1+0x80
    char * pver; // r31
    int idx; // r30
    int pIdx; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8060CFE0 -> 0x8060CFE8
int compareHyphenatorPatterns() {}

// Range: 0x8060CFE8 -> 0x8060CFF8
int compareHyphenatorExceptions() {}

// Range: 0x8060CFF8 -> 0x8060D380
void Hyphenator::Init(class Hyphenator * const this /* r28 */) {
    // Local variables
    const class DataArray * config; // r29
    const class DataArray * patterns; // r30
    int i; // r29
    const class DataArray * exceptions; // r29
    int i; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8060D380 -> 0x8060D3E0
void * Hyphenator::~Hyphenator(class Hyphenator * const this /* r30 */) {}

// Range: 0x8060D3E0 -> 0x8060D610
unsigned char Hyphenator::Hyphenate(class Hyphenator * const this /* r29 */, const char * text /* r30 */, int * points /* r31 */, int maxHyphens /* r24 */, int minLength /* r25 */, int minPrefix /* r26 */, int minSuffix /* r27 */) {
    // Local variables
    struct HyphenationState state; // r1+0x8
    int offset; // r28
    int len; // r27

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8060D610 -> 0x8060DB0C
unsigned char Hyphenator::HyphenateWord(class Hyphenator * const this /* r26 */, int offset /* r27 */, int length /* r28 */, struct HyphenationState & state /* r29 */) {
    // Local variables
    char tmp[256]; // r1+0x30
    int i; // r5
    class HyphenatorException key; // r1+0x8
    class HyphenatorException * exc; // r0
    const signed char * hyp; // r6
    int points[256]; // r1+0x130
    int i; // r5
    class HyphenatorPattern testPat; // r1+0x18
    int maxPatLen; // r0
    int sIdx; // r25
    int i; // r30
    int i; // r25
    int suffixLen; // r30
    int i; // r31
    int j; // r30
    int count; // r7
    int i; // r8
    int i; // r5
    int i; // r5
    int idx; // r0
    int i; // r6

    // References
    // -> struct __locale _current_locale;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8060DB0C -> 0x8060DBF4
unsigned char Hyphenator::ConsiderPattern(class Hyphenator * const this /* r7 */, int * points /* r30 */, int offset /* r31 */) {
    // Local variables
    class HyphenatorPattern * pat; // r3
    const char * str; // r3
    const signed char * thr; // r5
    int len; // r6
    int i; // r7
}

// Range: 0x8060DBF4 -> 0x8060DCE4
void * HyphenatorException::HyphenatorException(class HyphenatorException * const this /* r31 */) {
    // Local variables
    int strIdx; // r7
    int hypIdx; // r8
    int idx; // r9
    char tmp[256]; // r1+0x10

    // References
    // -> struct __locale _current_locale;
    // -> const char * gNullStr;
}

// Range: 0x8060DCE4 -> 0x8060DDC4
void * HyphenatorPattern::HyphenatorPattern() {
    // Local variables
    int idx; // r8

    // References
    // -> struct __locale _current_locale;
}

// Range: 0x8060DDC4 -> 0x8060DE20
unsigned char Hyphenate(const char * text /* r31 */, int * points /* r12 */, int maxHyphens /* r11 */, int maxLength /* r10 */, int maxPrefix /* r0 */) {
    // References
    // -> class Hyphenator TheHyphenator;
}

// Range: 0x8060DE20 -> 0x8060DE4C
static void __sinit_\Hyphenator_cpp() {
    // References
    // -> class Hyphenator TheHyphenator;
}


