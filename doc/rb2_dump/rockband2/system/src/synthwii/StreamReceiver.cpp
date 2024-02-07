/*
    Compile unit: C:\rockband2\system\src\synthwii\StreamReceiver.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80567F94 -> 0x80568F4C
*/
// Range: 0x80567F94 -> 0x80567FF8
static class StreamReceiver * NewWiiReceiver(int numBuffers /* r29 */, int sampleRate /* r30 */, unsigned char slip /* r31 */) {}

class StreamReceiverWii : public StreamReceiver {
    // total size: 0x80E0
    char * mVoiceBuffer; // offset 0x8054, size 0x4
    class Voice * mRefVoice; // offset 0x8058, size 0x4
    class Voice * mVoice; // offset 0x805C, size 0x4
    int mSampleRate; // offset 0x8060, size 0x4
    int mNumBuffers; // offset 0x8064, size 0x4
    int mByteStartNext; // offset 0x8068, size 0x4
    int mBufSyncSize; // offset 0x806C, size 0x4
    int mBufSizeRemaining; // offset 0x8070, size 0x4
    unsigned char * mVBufCopySrcPtr; // offset 0x8074, size 0x4
    unsigned char * mVBufCopyDstPtr; // offset 0x8078, size 0x4
    int mVBufCopySize; // offset 0x807C, size 0x4
    int mVBufCopyRemaining; // offset 0x8080, size 0x4
    unsigned char * mVBufCopySrcPtr2; // offset 0x8084, size 0x4
    int mVBufCopyRemaining1; // offset 0x8088, size 0x4
    float mVolume; // offset 0x808C, size 0x4
    float mPan; // offset 0x8090, size 0x4
    float mSpeed; // offset 0x8094, size 0x4
    class ADSR mADSR; // offset 0x8098, size 0x28
    enum FXCore mFXCore; // offset 0x80C0, size 0x4
    unsigned char mFXActive; // offset 0x80C4, size 0x1
    unsigned char mPitchShift; // offset 0x80C5, size 0x1
};
// Range: 0x80567FF8 -> 0x80568008
void StreamReceiverWii::Init() {
    // References
    // -> class StreamReceiver * (* sFactory)(int, int, unsigned char);
}

// Range: 0x80568008 -> 0x8056816C
void * StreamReceiverWii::StreamReceiverWii(class StreamReceiverWii * const this /* r28 */, int sampleRate /* r29 */, int numBuffers /* r30 */) {
    // References
    // -> struct [anonymous] __vt__17StreamReceiverWii;
}

// Range: 0x8056816C -> 0x80568244
void * StreamReceiverWii::~StreamReceiverWii(class StreamReceiverWii * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__17StreamReceiverWii;
}

// Range: 0x80568244 -> 0x805682A8
void StreamReceiverWii::PauseImpl(class StreamReceiverWii * const this /* r30 */, unsigned char p /* r31 */) {}

// Range: 0x805682A8 -> 0x805682B4
void StreamReceiverWii::PlayImpl() {}

// Range: 0x805682B4 -> 0x805682F4
int StreamReceiverWii::GetPlayCursor(class StreamReceiverWii * const this /* r31 */) {
    // Local variables
    char * addr; // r0
}

static class Timer * _t; // size: 0x4, address: 0x80A54188
// Range: 0x805682F4 -> 0x80568468
void StreamReceiverWii::StartSendImpl(class StreamReceiverWii * const this /* r28 */, unsigned char * buf /* r29 */, int bufSize /* r30 */, int targetIdx /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC
    int byteStart; // r31

    // References
    // -> static class Timer * _t;
}

static class Timer * _t; // size: 0x4, address: 0x80A54190
// Range: 0x80568468 -> 0x80568660
void StreamReceiverWii::StartSendImpl(class StreamReceiverWii * const this /* r27 */, unsigned char * buf1 /* r28 */, unsigned char * buf2 /* r26 */, int buf1Size /* r29 */, int buf2Size /* r30 */, int targetIdx /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC
    int byteStart; // r31

    // References
    // -> static class Timer * _t;
}

static class Timer * _t; // size: 0x4, address: 0x80A54198
// Range: 0x80568660 -> 0x80568A20
unsigned char StreamReceiverWii::SendDoneImpl(class StreamReceiverWii * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> static class Timer * _t;
}

// Range: 0x80568A20 -> 0x80568A3C
void StreamReceiverWii::SetVolume() {}

// Range: 0x80568A3C -> 0x80568A58
void StreamReceiverWii::SetPan() {}

// Range: 0x80568A58 -> 0x80568A68
void StreamReceiverWii::SetSpeed() {}

// Range: 0x80568A68 -> 0x80568AD8
void StreamReceiverWii::SetADSR() {}

// Range: 0x80568AD8 -> 0x80568AF8
void StreamReceiverWii::SetFXCore() {}

// Range: 0x80568AF8 -> 0x80568B48
void StreamReceiverWii::SetFX(class StreamReceiverWii * const this /* r30 */, unsigned char fx /* r31 */) {}

// Range: 0x80568B48 -> 0x80568B64
void StreamReceiverWii::SetPitchShift() {}

// Range: 0x80568B64 -> 0x80568D60
void StreamReceiverWii::SetSlipOffset(class StreamReceiverWii * const this /* r31 */, float ms /* f31 */) {
    // Local variables
    int samp; // r6

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80568D60 -> 0x80568DE0
void StreamReceiverWii::SlipStop(class StreamReceiverWii * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80568DE0 -> 0x80568E64
void StreamReceiverWii::SetSlipSpeed(class StreamReceiverWii * const this /* r31 */, float spd /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80568E64 -> 0x80568F4C
float StreamReceiverWii::GetSlipOffset(class StreamReceiverWii * const this /* r30 */) {
    // Local variables
    float diff; // f1

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x60
} __vt__17StreamReceiverWii; // size: 0x60, address: 0x8091A9D8
struct {
    // total size: 0x8
} __RTTI__17StreamReceiverWii; // size: 0x8, address: 0x8091AA58
struct {
    // total size: 0x8
} __RTTI__14StreamReceiver; // size: 0x8, address: 0x8091AA70

