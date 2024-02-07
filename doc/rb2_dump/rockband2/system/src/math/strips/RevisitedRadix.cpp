/*
    Compile unit: C:\rockband2\system\src\math\strips\RevisitedRadix.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80630B04 -> 0x80630FCC
*/
// Range: 0x80630B04 -> 0x80630B60
void * RadixSorter::RadixSorter(class RadixSorter * const this /* r31 */) {}

// Range: 0x80630B60 -> 0x80630BEC
void * RadixSorter::~RadixSorter(class RadixSorter * const this /* r29 */) {}

// Range: 0x80630BEC -> 0x80630FA4
class RadixSorter & RadixSorter::Sort(class RadixSorter * const this /* r28 */, unsigned int * input /* r29 */, unsigned int nb /* r30 */, unsigned char signedvalues /* r31 */) {
    // Local variables
    unsigned char AlreadySorted; // r0
    unsigned int * Indices; // r4
    unsigned char * p; // r5
    unsigned char * pe; // r6
    unsigned int * h0; // r0
    unsigned int * h1; // r7
    unsigned int * h2; // r8
    unsigned int * h3; // r9
    unsigned int PrevVal; // r10
    unsigned int Val; // r11
    int PrevVal; // r10
    int Val; // r11
    unsigned int NbNegativeValues; // r0
    unsigned int * h3; // r4
    unsigned int i; // r5
    unsigned int j; // r3
    unsigned int * CurCount; // r4
    unsigned char PerformPass; // r6
    unsigned int i; // r7
    unsigned int i; // r8
    unsigned int i; // r8
    unsigned char * InputBytes; // r9
    unsigned int * Indices; // r10
    unsigned int * IndicesEnd; // r11
    unsigned int id; // r12
    unsigned int * Tmp; // r5
}

// Range: 0x80630FA4 -> 0x80630FCC
class RadixSorter & RadixSorter::ResetIndices() {
    // Local variables
    unsigned int i; // r5
}


