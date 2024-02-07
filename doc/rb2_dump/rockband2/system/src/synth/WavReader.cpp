/*
    Compile unit: C:\rockband2\system\src\synth\WavReader.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8059A2C4 -> 0x8059A8D4
*/
class WavReader : public StreamReader {
    // total size: 0x44
protected:
    int mNumChannels; // offset 0x4, size 0x4
    int mSampleRate; // offset 0x8, size 0x4
private:
    class File * mInFile; // offset 0xC, size 0x4
    class FileStream * mInFileStream; // offset 0x10, size 0x4
    class WaveFile * mInWaveFile; // offset 0x14, size 0x4
    class WaveFileData * mInWaveFileData; // offset 0x18, size 0x4
    unsigned char mEnableReads; // offset 0x1C, size 0x1
    int mSamplesLeft; // offset 0x20, size 0x4
    unsigned short * mRawInputBuffer; // offset 0x24, size 0x4
    unsigned short * mInputBuffers[2]; // offset 0x28, size 0x8
    int mBufNumSamples; // offset 0x30, size 0x4
    int mBufOffset; // offset 0x34, size 0x4
    int mTotalSamplesConsumed; // offset 0x38, size 0x4
    unsigned char mInitted; // offset 0x3C, size 0x1
    class StandardStream * mOutStream; // offset 0x40, size 0x4
};
// Range: 0x8059A2C4 -> 0x8059A4A8
void * WavReader::WavReader(class WavReader * const this /* r29 */, class File * wavFile /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__9WavReader;
}

// Range: 0x8059A4A8 -> 0x8059A578
void * WavReader::~WavReader(class WavReader * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__9WavReader;
}

// Range: 0x8059A578 -> 0x8059A7A8
void WavReader::Poll(class WavReader * const this /* r31 */) {
    // Local variables
    unsigned short * b[2]; // r1+0x8
    int consumed; // r0
    int bufSamplesLeft; // r0
    int i; // r29
    int i; // r29
    int consumed; // r0
}

// Range: 0x8059A7A8 -> 0x8059A7C4
void WavReader::Seek(class WavReader * const this /* r5 */) {}

// Range: 0x8059A7C4 -> 0x8059A838
void WavReader::Init(class WavReader * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8059A838 -> 0x8059A8D0
int WavReader::ConsumeData(class WavReader * const this /* r28 */, void * pcm /* r29 */, int samples /* r30 */, int startSamp /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8059A8D0 -> 0x8059A8D4
void WavReader::EndData() {}

struct {
    // total size: 0x2C
} __vt__9WavReader; // size: 0x2C, address: 0x8092119C
struct {
    // total size: 0x8
} __RTTI__9WavReader; // size: 0x8, address: 0x809211E0

