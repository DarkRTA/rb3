/*
    Compile unit: C:\rockband2\system\src\synthwii\soundtouch\FIRFilter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8055F1EC -> 0x8055F654
*/
// Range: 0x8055F1EC -> 0x8055F210
void * FIRFilter::FIRFilter() {
    // References
    // -> struct [anonymous] __vt__Q210soundtouch9FIRFilter;
}

// Range: 0x8055F210 -> 0x8055F274
void * FIRFilter::~FIRFilter(class FIRFilter * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__Q210soundtouch9FIRFilter;
}

// Range: 0x8055F274 -> 0x8055F428
unsigned int FIRFilter::evaluateFilterStereo() {
    // Local variables
    unsigned int i; // r31
    unsigned int j; // r30
    unsigned int end; // r29
    long suml; // r28
    long sumr; // r27
    const signed short * ptr; // r26
}

// Range: 0x8055F428 -> 0x8055F51C
unsigned int FIRFilter::evaluateFilterMono() {
    // Local variables
    unsigned int i; // r6
    unsigned int j; // r7
    unsigned int end; // r0
    long sum; // r8
}

// Range: 0x8055F51C -> 0x8055F614
void FIRFilter::setCoefficients(class FIRFilter * const this /* r28 */, const signed short * coeffs /* r29 */, unsigned int newLength /* r30 */, unsigned int uResultDivFactor /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8055F614 -> 0x8055F654
unsigned int FIRFilter::evaluate() {}

struct {
    // total size: 0x18
} __vt__Q210soundtouch9FIRFilter; // size: 0x18, address: 0x80919980
struct {
    // total size: 0x8
} __RTTI__Q210soundtouch9FIRFilter; // size: 0x8, address: 0x809199B0

