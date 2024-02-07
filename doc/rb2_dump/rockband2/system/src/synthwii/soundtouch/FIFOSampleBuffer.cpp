/*
    Compile unit: C:\rockband2\system\src\synthwii\soundtouch\FIFOSampleBuffer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8055ED38 -> 0x8055F1EC
*/
class FIFOSamplePipe {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class FIFOSampleBuffer : public FIFOSamplePipe {
    // total size: 0x1C
    signed short * buffer; // offset 0x4, size 0x4
    signed short * bufferUnaligned; // offset 0x8, size 0x4
    unsigned int sizeInBytes; // offset 0xC, size 0x4
    unsigned int samplesInBuffer; // offset 0x10, size 0x4
    unsigned int channels; // offset 0x14, size 0x4
    unsigned int bufferPos; // offset 0x18, size 0x4
};
// Range: 0x8055ED38 -> 0x8055EDA4
void * FIFOSampleBuffer::FIFOSampleBuffer(class FIFOSampleBuffer * const this /* r30 */, unsigned int numChannels /* r31 */) {
    // References
    // -> struct [anonymous] __vt__Q210soundtouch16FIFOSampleBuffer;
}

// Range: 0x8055EDA4 -> 0x8055EE10
void * FIFOSampleBuffer::~FIFOSampleBuffer(class FIFOSampleBuffer * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__Q210soundtouch16FIFOSampleBuffer;
}

// Range: 0x8055EE10 -> 0x8055EE2C
void FIFOSampleBuffer::setChannels() {
    // Local variables
    unsigned int usedBytes; // r0
}

// Range: 0x8055EE2C -> 0x8055EE94
void FIFOSampleBuffer::rewind(class FIFOSampleBuffer * const this /* r31 */) {}

// Range: 0x8055EE94 -> 0x8055EEFC
void FIFOSampleBuffer::putSamples(class FIFOSampleBuffer * const this /* r29 */, const signed short * samples /* r30 */, unsigned int numSamples /* r31 */) {}

// Range: 0x8055EEFC -> 0x8055EF48
void FIFOSampleBuffer::putSamples(class FIFOSampleBuffer * const this /* r30 */, unsigned int numSamples /* r31 */) {}

// Range: 0x8055EF48 -> 0x8055EF94
signed short * FIFOSampleBuffer::ptrEnd(class FIFOSampleBuffer * const this /* r31 */) {}

// Range: 0x8055EF94 -> 0x8055EFB0
signed short * FIFOSampleBuffer::ptrBegin() {}

static int _x; // size: 0x4, address: 0x80A540D8
// Range: 0x8055EFB0 -> 0x8055F0E4
void FIFOSampleBuffer::ensureCapacity(class FIFOSampleBuffer * const this /* r31 */, unsigned int capacityRequirement /* r29 */) {
    // Local variables
    signed short * tempUnaligned; // r0
    signed short * temp; // r29

    // References
    // -> class Debug TheDebug;
    // -> static int _x;
}

// Range: 0x8055F0E4 -> 0x8055F0F8
unsigned int FIFOSampleBuffer::getCapacity() {}

// Range: 0x8055F0F8 -> 0x8055F100
unsigned int FIFOSampleBuffer::numSamples() {}

// Range: 0x8055F100 -> 0x8055F194
unsigned int FIFOSampleBuffer::receiveSamples(class FIFOSampleBuffer * const this /* r29 */, signed short * output /* r30 */) {}

// Range: 0x8055F194 -> 0x8055F1CC
unsigned int FIFOSampleBuffer::receiveSamples() {}

// Range: 0x8055F1CC -> 0x8055F1DC
int FIFOSampleBuffer::isEmpty() {}

// Range: 0x8055F1DC -> 0x8055F1EC
void FIFOSampleBuffer::clear() {}

struct {
    // total size: 0x28
} __vt__Q210soundtouch16FIFOSampleBuffer; // size: 0x28, address: 0x809198D0
struct {
    // total size: 0x8
} __RTTI__Q210soundtouch16FIFOSampleBuffer; // size: 0x8, address: 0x80919928
struct {
    // total size: 0x8
} __RTTI__Q210soundtouch14FIFOSamplePipe; // size: 0x8, address: 0x80919950

