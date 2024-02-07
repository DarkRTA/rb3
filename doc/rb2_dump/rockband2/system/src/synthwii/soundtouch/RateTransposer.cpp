/*
    Compile unit: C:\rockband2\system\src\synthwii\soundtouch\RateTransposer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8055F654 -> 0x80560164
*/
class RateTransposer : public FIFOProcessor {
    // total size: 0x6C
protected:
    class AAFilter * pAAFilter; // offset 0x8, size 0x4
    float fRate; // offset 0xC, size 0x4
    unsigned int uChannels; // offset 0x10, size 0x4
    class FIFOSampleBuffer storeBuffer; // offset 0x14, size 0x1C
    class FIFOSampleBuffer tempBuffer; // offset 0x30, size 0x1C
    class FIFOSampleBuffer outputBuffer; // offset 0x4C, size 0x1C
    int bUseAAFilter; // offset 0x68, size 0x4
};
// Range: 0x8055F654 -> 0x8055F6F0
void * RateTransposer::RateTransposer(class RateTransposer * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__Q210soundtouch14RateTransposer;
}

class FIFOProcessor : public FIFOSamplePipe {
    // total size: 0x8
protected:
    class FIFOSamplePipe * output; // offset 0x4, size 0x4
};
// Range: 0x8055F6F0 -> 0x8055F78C
void * RateTransposer::~RateTransposer(class RateTransposer * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__Q210soundtouch14RateTransposer;
}

// Range: 0x8055F78C -> 0x8055F794
void RateTransposer::enableAAFilter() {}

// Range: 0x8055F794 -> 0x8055F79C
class AAFilter * RateTransposer::getAAFilter() {}

// Range: 0x8055F79C -> 0x8055F7C8
void RateTransposer::setRate() {}

// Range: 0x8055F7C8 -> 0x8055F7CC
void RateTransposer::putSamples() {}

// Range: 0x8055F7CC -> 0x8055F938
void RateTransposer::upsample(class RateTransposer * const this /* r29 */, const signed short * src /* r31 */, unsigned int numSamples /* r30 */) {
    // Local variables
    int count; // r31
    int sizeTemp; // r0
    int num; // r30
}

// Range: 0x8055F938 -> 0x8055FAAC
void RateTransposer::downsample(class RateTransposer * const this /* r27 */, unsigned int numSamples /* r28 */) {
    // Local variables
    int count; // r30
    int sizeTemp; // r29
}

// Range: 0x8055FAAC -> 0x8055FBC4
void RateTransposer::processSamples(class RateTransposer * const this /* r29 */, const signed short * src /* r30 */, unsigned int numSamples /* r31 */) {
    // Local variables
    unsigned int sizeReq; // r0
}

// Range: 0x8055FBC4 -> 0x8055FC30
void RateTransposer::setChannels(class RateTransposer * const this /* r31 */) {}

// Range: 0x8055FC30 -> 0x8055FC7C
void RateTransposer::clear(class RateTransposer * const this /* r31 */) {}

// Range: 0x8055FC7C -> 0x8055FCDC
unsigned int RateTransposer::isEmpty(class RateTransposer * const this /* r31 */) {}

class RateTransposerFloat : public RateTransposer {
    // total size: 0x78
protected:
    float fSlopeCount; // offset 0x6C, size 0x4
    float fRateStep; // offset 0x70, size 0x4
    signed short sPrevSampleL; // offset 0x74, size 0x2
    signed short sPrevSampleR; // offset 0x76, size 0x2
};
// Range: 0x8055FCDC -> 0x8055FD44
void * RateTransposerFloat::RateTransposerFloat(class RateTransposerFloat * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__Q210soundtouch19RateTransposerFloat;
}

// Range: 0x8055FD44 -> 0x8055FDA0
void * RateTransposerFloat::~RateTransposerFloat(class RateTransposerFloat * const this /* r30 */) {}

// Range: 0x8055FDA0 -> 0x8055FDB8
void RateTransposerFloat::resetRegisters() {}

// Range: 0x8055FDB8 -> 0x8055FF1C
unsigned int RateTransposerFloat::transposeMono() {
    // Local variables
    unsigned int i; // r8
    unsigned int used; // r9
}

// Range: 0x8055FF1C -> 0x80560164
unsigned int RateTransposerFloat::transposeStereo() {
    // Local variables
    unsigned int srcPos; // r11
    unsigned int i; // r7
    unsigned int used; // r8
}

struct {
    // total size: 0x38
} __vt__Q210soundtouch19RateTransposerFloat; // size: 0x38, address: 0x809199B8
struct {
    // total size: 0x8
} __RTTI__Q210soundtouch19RateTransposerFloat; // size: 0x8, address: 0x80919A30
struct {
    // total size: 0x38
} __vt__Q210soundtouch14RateTransposer; // size: 0x38, address: 0x80919A38
struct {
    // total size: 0x8
} __RTTI__Q210soundtouch14RateTransposer; // size: 0x8, address: 0x80919AA0
struct {
    // total size: 0x8
} __RTTI__Q210soundtouch13FIFOProcessor; // size: 0x8, address: 0x80919AD0

