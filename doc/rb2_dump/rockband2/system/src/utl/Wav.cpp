/*
    Compile unit: C:\rockband2\system\src\utl\Wav.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80625188 -> 0x80625374
*/
static const char * riffID; // size: 0x4, address: 0x80A47BF0
static const char * waveID; // size: 0x4, address: 0x80A47BF4
static const char * formatID; // size: 0x4, address: 0x80A47BF8
static const char * dataID; // size: 0x4, address: 0x80A47BFC
struct ChunkHeader {
    // total size: 0x8
    char mID[4]; // offset 0x0, size 0x4
    unsigned int mSize; // offset 0x4, size 0x4
};
struct RIFFHeader {
    // total size: 0x4
    char mFileID[4]; // offset 0x0, size 0x4
};
struct FormatChunk {
    // total size: 0x10
    signed short mFormatTag; // offset 0x0, size 0x2
    unsigned short mChannels; // offset 0x2, size 0x2
    unsigned int mSamplesPerSec; // offset 0x4, size 0x4
    unsigned int mAvgBytesPerSec; // offset 0x8, size 0x4
    unsigned short mBlockAlign; // offset 0xC, size 0x2
    unsigned short mBitsPerSample; // offset 0xE, size 0x2
};
// Range: 0x80625188 -> 0x80625374
void WriteWav(int samplesPerSec /* r30 */, void * buf /* r28 */, int bufsize /* r29 */) {
    // Local variables
    int fd; // r31
    int size; // r3
    struct ChunkHeader chunk; // r1+0x20
    struct RIFFHeader hdr; // r1+0xC
    struct ChunkHeader chunk; // r1+0x18
    struct FormatChunk fmtChunk; // r1+0x28
    struct ChunkHeader chunk; // r1+0x10
    const signed short * sampBuf; // r0
    int i; // r30
    signed short samp; // r1+0x8

    // References
    // -> static const char * dataID;
    // -> static const char * formatID;
    // -> static const char * waveID;
    // -> static const char * riffID;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}


