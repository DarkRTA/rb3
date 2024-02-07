/*
    Compile unit: C:\rockband2\system\src\synth\BinkReader.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8056989C -> 0x8056A0FC
*/
int sHeap; // size: 0x4, address: 0x80A47628
struct BINKTRACK {
    // total size: 0x1C
    unsigned int Frequency; // offset 0x0, size 0x4
    unsigned int Bits; // offset 0x4, size 0x4
    unsigned int Channels; // offset 0x8, size 0x4
    unsigned int MaxSize; // offset 0xC, size 0x4
    struct BINK * bink; // offset 0x10, size 0x4
    unsigned int sndcomp; // offset 0x14, size 0x4
    int trackindex; // offset 0x18, size 0x4
};
enum BinkReaderState {
    kOpenBink = 0,
    kOpenTracks = 1,
    kInitStream = 2,
    kPlay = 3,
    kDone = 4,
    kFailure = 5,
};
class BinkReader : public StreamReader {
    // total size: 0xE8
    class File * mFile; // offset 0x4, size 0x4
    class StandardStream * mStream; // offset 0x8, size 0x4
    struct BINK * mBink; // offset 0xC, size 0x4
    struct BINKTRACK * mBinkTracks[16]; // offset 0x10, size 0x40
    unsigned char * mPCMBuffers[16]; // offset 0x50, size 0x40
    unsigned char * mPCMOffsets[16]; // offset 0x90, size 0x40
    unsigned char mDecodeTrack; // offset 0xD0, size 0x1
    int mSamplesReady; // offset 0xD4, size 0x4
    unsigned int mSampleCurrent; // offset 0xD8, size 0x4
    unsigned int mSamplesJump; // offset 0xDC, size 0x4
    enum BinkReaderState mState; // offset 0xE0, size 0x4
    int mHeap; // offset 0xE4, size 0x4
};
// Range: 0x8056989C -> 0x80569974
void * BinkReader::BinkReader(class BinkReader * const this /* r30 */, class File * pBinkFile /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> int sHeap;
    // -> struct [anonymous] __vt__10BinkReader;
}

// Range: 0x80569974 -> 0x80569A40
void * BinkReader::~BinkReader(class BinkReader * const this /* r28 */) {
    // Local variables
    unsigned char iTrackIndex; // r30

    // References
    // -> struct [anonymous] __vt__10BinkReader;
}

static class Timer * _t; // size: 0x4, address: 0x80A541A0
// Range: 0x80569A40 -> 0x80569EB8
void BinkReader::Poll(class BinkReader * const this /* r30 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC
    unsigned char iTrackIndex; // r26
    struct BINKTRACK * hBinkTrack; // r0
    int iSamplesConsumed; // r0
    unsigned char iTrackIndex; // r5
    unsigned int iDecodeSize; // r3
    int iDecodeQuota; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Timer * _t;
}

// Range: 0x80569EB8 -> 0x8056A080
void BinkReader::Seek(class BinkReader * const this /* r29 */, int iSample /* r30 */) {
    // Local variables
    float kfBinkFreq; // f31
    float kfBinkRate; // f30
    float kfSampleTime; // f1
    unsigned int kiSampleFrame; // r27
    float kfBinkTime; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8056A080 -> 0x8056A0FC
void BinkReader::Init(class BinkReader * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x24
} __vt__10BinkReader; // size: 0x24, address: 0x8091AC88
struct {
    // total size: 0x8
} __RTTI__10BinkReader; // size: 0x8, address: 0x8091ACC8
struct {
    // total size: 0x20
} __vt__12StreamReader; // size: 0x20, address: 0x8091ACD0
struct {
    // total size: 0x8
} __RTTI__12StreamReader; // size: 0x8, address: 0x8091AD00

