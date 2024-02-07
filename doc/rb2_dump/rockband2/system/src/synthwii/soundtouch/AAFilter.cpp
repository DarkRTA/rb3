/*
    Compile unit: C:\rockband2\system\src\synthwii\soundtouch\AAFilter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8055EA74 -> 0x8055ED38
*/
class FIRFilter {
    // total size: 0x18
protected:
    unsigned int length; // offset 0x0, size 0x4
    unsigned int lengthDiv8; // offset 0x4, size 0x4
    unsigned int resultDivFactor; // offset 0x8, size 0x4
    signed short resultDivider; // offset 0xC, size 0x2
    signed short * filterCoeffs; // offset 0x10, size 0x4
public:
    void * __vptr$; // offset 0x14, size 0x4
};
class AAFilter {
    // total size: 0x18
protected:
    class FIRFilter * pFIR; // offset 0x0, size 0x4
    double cutoffFreq; // offset 0x8, size 0x8
    unsigned int length; // offset 0x10, size 0x4
};
// Range: 0x8055EA74 -> 0x8055EAE8
void * AAFilter::AAFilter(class AAFilter * const this /* r30 */, unsigned int length /* r31 */) {}

// Range: 0x8055EAE8 -> 0x8055EB5C
void * AAFilter::~AAFilter(class AAFilter * const this /* r30 */) {}

// Range: 0x8055EB5C -> 0x8055EB64
void AAFilter::setCutoffFreq() {}

// Range: 0x8055EB64 -> 0x8055EB6C
void AAFilter::setLength() {}

// Range: 0x8055EB6C -> 0x8055ED30
void AAFilter::calculateCoeffs(class AAFilter * const this /* r27 */) {
    // Local variables
    unsigned int i; // r30
    double cntTemp; // f28
    double temp; // f29
    double tempCoeff; // f27
    double h; // f0
    double w; // f0
    double fc2; // f31
    double wc; // f30
    double scaleCoeff; // f1
    double sum; // f26
    double * work; // r29
    signed short * coeffs; // r28
}

// Range: 0x8055ED30 -> 0x8055ED38
unsigned int AAFilter::evaluate() {}


