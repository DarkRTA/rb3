/*
    Compile unit: C:\rockband2\system\src\synthwii\soundtouch\SoundTouch.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805601C8 -> 0x80560B44
*/
class TDStretch : public FIFOProcessor {
    // total size: 0x90
protected:
    unsigned int channels; // offset 0x8, size 0x4
    unsigned int sampleReq; // offset 0xC, size 0x4
    float tempo; // offset 0x10, size 0x4
    signed short * pMidBuffer; // offset 0x14, size 0x4
    signed short * pRefMidBuffer; // offset 0x18, size 0x4
    signed short * pRefMidBufferUnaligned; // offset 0x1C, size 0x4
    unsigned int overlapLength; // offset 0x20, size 0x4
    unsigned int overlapDividerBits; // offset 0x24, size 0x4
    unsigned int slopingDivider; // offset 0x28, size 0x4
    unsigned int seekLength; // offset 0x2C, size 0x4
    unsigned int seekWindowLength; // offset 0x30, size 0x4
    unsigned int maxOffset; // offset 0x34, size 0x4
    float nominalSkip; // offset 0x38, size 0x4
    float skipFract; // offset 0x3C, size 0x4
    class FIFOSampleBuffer outputBuffer; // offset 0x40, size 0x1C
    class FIFOSampleBuffer inputBuffer; // offset 0x5C, size 0x1C
    int bQuickseek; // offset 0x78, size 0x4
    int bMidBufferDirty; // offset 0x7C, size 0x4
    unsigned int sampleRate; // offset 0x80, size 0x4
    unsigned int sequenceMs; // offset 0x84, size 0x4
    unsigned int seekWindowMs; // offset 0x88, size 0x4
    unsigned int overlapMs; // offset 0x8C, size 0x4
};
class SoundTouch : public FIFOProcessor {
    // total size: 0x2C
    class RateTransposer * pRateTransposer; // offset 0x8, size 0x4
    class TDStretch * pTDStretch; // offset 0xC, size 0x4
    float virtualRate; // offset 0x10, size 0x4
    float virtualTempo; // offset 0x14, size 0x4
    float virtualPitch; // offset 0x18, size 0x4
    int bSrateSet; // offset 0x1C, size 0x4
protected:
    unsigned int channels; // offset 0x20, size 0x4
    float rate; // offset 0x24, size 0x4
    float tempo; // offset 0x28, size 0x4
};
// Range: 0x805601C8 -> 0x80560284
void * SoundTouch::SoundTouch(class SoundTouch * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__Q210soundtouch10SoundTouch;
}

// Range: 0x80560284 -> 0x80560328
void * SoundTouch::~SoundTouch(class SoundTouch * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__Q210soundtouch10SoundTouch;
}

// Range: 0x80560328 -> 0x805603B0
void SoundTouch::setChannels(class SoundTouch * const this /* r30 */, unsigned int numChannels /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805603B0 -> 0x805603B8
void SoundTouch::setPitch() {}

// Range: 0x805603B8 -> 0x80560648
void SoundTouch::calcEffectiveRateAndTempo(class SoundTouch * const this /* r31 */) {
    // Local variables
    float oldTempo; // f31
    float oldRate; // f2
}

// Range: 0x80560648 -> 0x80560664
void SoundTouch::setSampleRate() {}

// Range: 0x80560664 -> 0x805608C4
void SoundTouch::putSamples(class SoundTouch * const this /* r26 */, const signed short * samples /* r27 */, unsigned int numSamples /* r28 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805608C4 -> 0x80560988
void SoundTouch::flush(class SoundTouch * const this /* r29 */) {
    // Local variables
    int i; // r30
    unsigned int nOut; // r0
    signed short buff[128]; // r1+0x8
}

// Range: 0x80560988 -> 0x80560AC8
int SoundTouch::setSetting(class SoundTouch * const this /* r29 */, unsigned int settingId /* r30 */, unsigned int value /* r31 */) {
    // Local variables
    unsigned int sampleRate; // r1+0x14
    unsigned int sequenceMs; // r1+0x10
    unsigned int seekWindowMs; // r1+0xC
    unsigned int overlapMs; // r1+0x8
}

// Range: 0x80560AC8 -> 0x80560B18
void SoundTouch::clear(class SoundTouch * const this /* r31 */) {}

// Range: 0x80560B18 -> 0x80560B44
unsigned int SoundTouch::numUnprocessedSamples() {}

struct {
    // total size: 0x2C
} __vt__Q210soundtouch10SoundTouch; // size: 0x2C, address: 0x80919B58
struct {
    // total size: 0x8
} __RTTI__Q210soundtouch10SoundTouch; // size: 0x8, address: 0x80919BB0

