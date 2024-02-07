/*
    Compile unit: C:\rockband2\band2\src\game\SaytrMic.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80081408 -> 0x80082040
*/
static unsigned char gIdxTaken[2]; // size: 0x2, address: 0x80A49DF8
class list : public _List_base {
    // total size: 0x8
};
static class list gMics; // size: 0x8, address: 0x809777D0
class IIR4PoleFilter {
    // total size: 0x50
    float mB0[4]; // offset 0x0, size 0x10
    float mB[4]; // offset 0x10, size 0x10
    float mC[4]; // offset 0x20, size 0x10
    float mA[4]; // offset 0x30, size 0x10
    float mV[4]; // offset 0x40, size 0x10
};
class PitchDetector {
    // total size: 0x38
    class IIR4PoleFilter * mFilter; // offset 0x0, size 0x4
    int mSamplesPerSec; // offset 0x4, size 0x4
    int mBufferSize; // offset 0x8, size 0x4
    int mDecimation; // offset 0xC, size 0x4
    int mMinPeriod; // offset 0x10, size 0x4
    int mCurSample; // offset 0x14, size 0x4
    int mDecProg; // offset 0x18, size 0x4
    float * mBuffer1; // offset 0x1C, size 0x4
    float * mBuffer2; // offset 0x20, size 0x4
    float * mBuffer3; // offset 0x24, size 0x4
    float mPitch; // offset 0x28, size 0x4
    float mPeriod; // offset 0x2C, size 0x4
    float mAveEnergy; // offset 0x30, size 0x4
    class MemStream * mDebugStream; // offset 0x34, size 0x4
};
enum ProcessMode {
    PROCESS_PITCH = 0,
    PROCESS_SAYTR = 1,
};
class SaytrMic {
    // total size: 0x4088
    int mPadNum; // offset 0x0, size 0x4
    int mFonixIdx; // offset 0x4, size 0x4
    unsigned char mUSB; // offset 0x8, size 0x1
    unsigned char mPlayback; // offset 0x9, size 0x1
    unsigned char mWriteWav; // offset 0xA, size 0x1
    int mPlaybackSampleRate; // offset 0xC, size 0x4
    class MemStream * mStoredAudio; // offset 0x10, size 0x4
    class PitchDetector * mDetector; // offset 0x14, size 0x4
    class VocalInterpreter * mInterper; // offset 0x18, size 0x4
    enum ProcessMode mProcessMode; // offset 0x1C, size 0x4
    float mEnergy; // offset 0x20, size 0x4
    float mPitch; // offset 0x24, size 0x4
    struct SpeechAnalysis mAnalysis; // offset 0x28, size 0x22
    float mMicVolumeClamp; // offset 0x4C, size 0x4
    float mLastEnergy; // offset 0x50, size 0x4
    float mLastPitch; // offset 0x54, size 0x4
    struct SpeechAnalysis mLastAnalysis; // offset 0x58, size 0x22
    signed short mSamples[8192]; // offset 0x7A, size 0x4000
    int mNumSamples; // offset 0x407C, size 0x4
    float mFonixGain; // offset 0x4080, size 0x4
    unsigned char mSpursActive; // offset 0x4084, size 0x1
};
// Range: 0x80081408 -> 0x8008162C
void * SaytrMic::SaytrMic(class SaytrMic * const this /* r31 */) {
    // Local variables
    class String playbackFile; // r1+0x14

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<P8SaytrMic>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class list gMics;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static unsigned char gIdxTaken[2];
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_List_node<P8SaytrMic>; // size: 0x8, address: 0x80879380
// Range: 0x8008162C -> 0x80081674
void SaytrMic::Terminate() {
    // References
    // -> static class list gMics;
}

class WaveFileMarker {
    // total size: 0x14
    int mFrame; // offset 0x0, size 0x4
    int mID; // offset 0x4, size 0x4
    class String mName; // offset 0x8, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class WaveFileMarker * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class WaveFileMarker * _M_start; // offset 0x0, size 0x4
    class WaveFileMarker * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ChunkID {
    // total size: 0x4
    char mStr[4]; // offset 0x0, size 0x4
};
class ChunkHeader {
    // total size: 0xC
    class ChunkID mID; // offset 0x0, size 0x4
    int mLength; // offset 0x4, size 0x4
    unsigned char mIsList; // offset 0x8, size 0x1
};
class IListChunk {
    // total size: 0x2C
    class IListChunk * mParent; // offset 0x0, size 0x4
    class BinStream & mBaseBinStream; // offset 0x4, size 0x4
    class ChunkHeader * mHeader; // offset 0x8, size 0x4
    int mStartMarker; // offset 0xC, size 0x4
    int mEndMarker; // offset 0x10, size 0x4
    unsigned char mLocked; // offset 0x14, size 0x1
    class ChunkHeader mSubHeader; // offset 0x18, size 0xC
    unsigned char mSubChunkValid; // offset 0x24, size 0x1
    unsigned char mRecentlyReset; // offset 0x25, size 0x1
    int mSubChunkMarker; // offset 0x28, size 0x4
};
class WaveFile {
    // total size: 0x4C
    signed short mFormat; // offset 0x0, size 0x2
    unsigned short mNumChannels; // offset 0x2, size 0x2
    unsigned int mSamplesPerSec; // offset 0x4, size 0x4
    unsigned int mAvgBytesPerSec; // offset 0x8, size 0x4
    unsigned short mBlockAlign; // offset 0xC, size 0x2
    unsigned short mBitsPerSample; // offset 0xE, size 0x2
    int mNumSamples; // offset 0x10, size 0x4
    class vector mMarkers; // offset 0x14, size 0xC
    class IListChunk mRiffList; // offset 0x20, size 0x2C
};
class IDataChunk : public BinStream {
    // total size: 0x24
    class IListChunk * mParent; // offset 0xC, size 0x4
    class BinStream & mBaseBinStream; // offset 0x10, size 0x4
    class ChunkHeader * mHeader; // offset 0x14, size 0x4
    int mStartMarker; // offset 0x18, size 0x4
    int mEndMarker; // offset 0x1C, size 0x4
    unsigned char mFailed; // offset 0x20, size 0x1
    unsigned char mEof; // offset 0x21, size 0x1
};
class WaveFileData : public IDataChunk {
    // total size: 0x28
    class WaveFile & mWaveFile; // offset 0x24, size 0x4
};
// Range: 0x80081674 -> 0x800818A4
int SaytrMic::SetInputFile(class SaytrMic * const this /* r31 */) {
    // Local variables
    int sampleRate; // r29
    class FileStream f; // r1+0x38
    class WaveFile wf; // r1+0x60
    class WaveFileData wfd; // r1+0x10

    // References
    // -> class Synth * TheSynth;
}

// Range: 0x800818A4 -> 0x800818A8
void SaytrMic::Reset() {}

// Range: 0x800818A8 -> 0x800818C8
void SaytrMic::StartDetection() {}

// Range: 0x800818C8 -> 0x80081924
void SaytrMic::SetMute(unsigned char mute /* r31 */) {
    // References
    // -> class Synth * TheSynth;
}

// Range: 0x80081924 -> 0x80081C00
void SaytrMic::ThreadProcessOneFrame(class SaytrMic * const this /* r31 */) {
    // Local variables
    float live_pitch; // r1+0xC
    float energy; // r1+0x8
    float secs; // f0
    int droppedSamples; // r30
    class Mic * mic; // r29
    signed short * micSamples; // r4
    float alpha; // f0
    signed short * data; // r29

    // References
    // -> class Synth * TheSynth;
    // -> class TaskMgr TheTaskMgr;
}

static class Timer * _t; // size: 0x4, address: 0x80A49DFC
// Range: 0x80081C00 -> 0x80081F74
void SaytrMic::Update(class SaytrMic * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC
    int targSamp; // r29
    int i; // r29
    class Mic * mic; // r0

    // References
    // -> class Synth * TheSynth;
    // -> class TaskMgr TheTaskMgr;
    // -> static class Timer * _t;
}

// Range: 0x80081F74 -> 0x80081FDC
int SaytrMic::GetDataSampleRate() {
    // References
    // -> class Synth * TheSynth;
}

// Range: 0x80081FDC -> 0x80081FE4
void SaytrMic::setProcessMode() {}

// Range: 0x80081FE4 -> 0x80082040
static void __sinit_\SaytrMic_cpp() {
    // References
    // -> static class list gMics;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class SaytrMic * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};

