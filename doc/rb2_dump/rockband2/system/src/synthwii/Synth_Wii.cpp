/*
    Compile unit: C:\rockband2\system\src\synthwii\Synth_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80564210 -> 0x805657EC
*/
// Range: 0x80564210 -> 0x80564290
void * micAllocWii(unsigned long size /* r29 */, unsigned long align /* r30 */) {
    // Local variables
    void * p; // r30
}

// Range: 0x80564290 -> 0x805642D4
void micFreeWii(void * p /* r31 */) {}

enum State {
    kInit = 0,
    kReady = 1,
    kPlaying = 2,
    kStopped = 3,
};
class StreamReceiver {
    // total size: 0x8060
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    unsigned char mSlipEnabled; // offset 0x4, size 0x1
private:
    unsigned char mBuffer[32768]; // offset 0x20, size 0x8000
    int mNumBuffers; // offset 0x8020, size 0x4
    int mRingSize; // offset 0x8024, size 0x4
    int mRingWritePos; // offset 0x8028, size 0x4
    int mRingReadPos; // offset 0x802C, size 0x4
    int mRingFreeSpace; // offset 0x8030, size 0x4
    int mRingWrittenSpace; // offset 0x8034, size 0x4
    enum State mState; // offset 0x8038, size 0x4
    int mSendTarget; // offset 0x803C, size 0x4
    unsigned char mWantToSend; // offset 0x8040, size 0x1
    unsigned char mSending; // offset 0x8041, size 0x1
    int mBuffersSent; // offset 0x8044, size 0x4
    unsigned char mStarving; // offset 0x8048, size 0x1
    unsigned char mEndData; // offset 0x8049, size 0x1
    int mDoneBufferCounter; // offset 0x804C, size 0x4
    int mLastPlayCursor; // offset 0x8050, size 0x4
};
// Range: 0x805642D4 -> 0x80564310
class Synth * Synth::New() {}

class SynthWii * TheWiiSynth; // size: 0x4, address: 0x80A54100
// Range: 0x80564310 -> 0x80564484
void * SynthWii::SynthWii(class SynthWii * const this /* r31 */) {
    // Local variables
    int i; // r30
    int i; // r5

    // References
    // -> class SynthWii * TheWiiSynth;
    // -> struct [anonymous] __vt__8SynthWii;
}

static int _x; // size: 0x4, address: 0x80A54104
// Range: 0x80564484 -> 0x805645E0
void SynthWii::Init(class SynthWii * const this /* r30 */) {
    // Local variables
    int x; // r5

    // References
    // -> class WiiFX TheWiiFX;
    // -> static int _x;
    // -> class Voice * gVoices[96];
}

// Range: 0x805645E0 -> 0x80564694
void SynthWii::Terminate(class SynthWii * const this /* r29 */) {
    // References
    // -> class SynthWii * TheWiiSynth;
}

static class Timer * _t; // size: 0x4, address: 0x80A5410C
// Range: 0x80564694 -> 0x805647A0
void SynthWii::Poll(class SynthWii * const this /* r30 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC
    int x; // r31

    // References
    // -> static class Timer * _t;
}

// Range: 0x805647A0 -> 0x805647D8
class Mic * SynthWii::GetMic() {}

// Range: 0x805647D8 -> 0x805647E0
unsigned char SynthWii::GetMicFX() {}

// Range: 0x805647E0 -> 0x805647E8
void SynthWii::SetMicFX() {}

// Range: 0x805647E8 -> 0x80564824
void SynthWii::SetMicVolume() {
    // Local variables
    float volume; // f0
}

// Range: 0x80564824 -> 0x80564828
void SynthWii::SuspendMics() {}

// Range: 0x80564828 -> 0x8056482C
void SynthWii::ResumeMics() {}

// Range: 0x8056482C -> 0x805648B4
int SynthWii::GetNumConnectedMics(class SynthWii * const this /* r30 */) {
    // Local variables
    int x; // r31
}

// Range: 0x805648B4 -> 0x805648BC
float SynthWii::GetMicVolume() {}

// Range: 0x805648BC -> 0x80564944
void SynthWii::ReleaseMics(class SynthWii * const this /* r29 */) {
    // Local variables
    int x; // r31
    class MicWii * temp; // r30
}

// Range: 0x80564944 -> 0x80564AB4
void SynthWii::AssignUSBMic(class SynthWii * const this /* r30 */, int micIdx /* r31 */) {
    // Local variables
    int i; // r28
    class MicWii * mic; // r27
    int i; // r27
    class MicWii * mic; // r28
}

// Range: 0x80564AB4 -> 0x80564B10
class DataNode SynthWii::OnDebug() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80564B10 -> 0x80564C28
class Stream * SynthWii::NewStream(const char * filebase /* r31 */, float startMs /* f30 */, float bufSecs /* f31 */) {
    // Local variables
    class File * f; // r1+0x10
    class Symbol ext; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

// Range: 0x80564C28 -> 0x80564D48
class Stream * SynthWii::NewBufStream(void * buf /* r27 */, int size /* r28 */, class Symbol & ext /* r29 */, float startMs /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__7BufFile;
}

// Range: 0x80564D48 -> 0x80564ED4
class StreamReader * SynthWii::NewStreamDecoder(class File * f /* r29 */, class StandardStream * s /* r30 */, class Symbol & ext /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

static class Symbol bik; // size: 0x4, address: 0x80A54114
static class Symbol mogg; // size: 0x4, address: 0x80A5411C
static class Symbol wav; // size: 0x4, address: 0x80A54124
// Range: 0x80564ED4 -> 0x80565064
void SynthWii::NewStreamFile(class SynthWii * const this /* r27 */, const char * filebase /* r28 */, class File * & fileOut /* r29 */, class Symbol & extOut /* r30 */) {
    // Local variables
    class String bikFilename; // r1+0x20
    class String moggFilename; // r1+0x14
    class String wavFilename; // r1+0x8

    // References
    // -> static class Symbol wav;
    // -> static class Symbol mogg;
    // -> static class Symbol bik;
}

// Range: 0x80565064 -> 0x80565130
void SynthWii::PauseVoices(class SynthWii * const this /* r27 */, unsigned char pause /* r28 */) {
    // Local variables
    int x; // r29

    // References
    // -> class Voice * gVoices[96];
}

// Range: 0x80565130 -> 0x80565138
void SynthWii::HomePauseVoices() {}

static class Timer * _t; // size: 0x4, address: 0x80A54128
// Range: 0x80565138 -> 0x805651F4
void FrameCallback() {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> static class Timer * _t;
}

static class Symbol _s; // size: 0x4, address: 0x80A54130
static class Symbol _s; // size: 0x4, address: 0x80A54138
static class Symbol _s; // size: 0x4, address: 0x80A54140
// Range: 0x805651F4 -> 0x805657EC
class DataNode SynthWii::Handle(class SynthWii * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class BufFile : public File {
    // total size: 0x14
    const unsigned char * mBuf; // offset 0x4, size 0x4
    int mSize; // offset 0x8, size 0x4
    const unsigned char * mPos; // offset 0xC, size 0x4
    int mBytesRead; // offset 0x10, size 0x4
};
struct {
    // total size: 0x38
} __vt__7BufFile; // size: 0x38, address: 0x8091A308
struct {
    // total size: 0x8
} __RTTI__7BufFile; // size: 0x8, address: 0x8091A358
struct {
    // total size: 0xF4
} __vt__8SynthWii; // size: 0xF4, address: 0x8091A360
struct {
    // total size: 0x8
} __RTTI__8SynthWii; // size: 0x8, address: 0x8091A488
struct {
    // total size: 0x8
} __RTTI__5Synth; // size: 0x8, address: 0x8091A4B8
struct {
    // total size: 0x38
} __vt__4File; // size: 0x38, address: 0x8091A510
struct {
    // total size: 0x8
} __RTTI__4File; // size: 0x8, address: 0x8091A550
struct {
    // total size: 0x8
} __RTTI__PP6MicWii; // size: 0x8, address: 0x8091A568
struct _OKToMemCpy {
    // total size: 0x1
};

