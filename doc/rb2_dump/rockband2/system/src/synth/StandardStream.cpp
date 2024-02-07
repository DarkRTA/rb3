/*
    Compile unit: C:\rockband2\system\src\synth\StandardStream.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8058D69C -> 0x805907DC
*/
static class Symbol _parent; // size: 0x4, address: 0x80A546DC
static class Symbol _default; // size: 0x4, address: 0x80A546E4
struct ChannelParams {
    // total size: 0x60
    float mPan; // offset 0x0, size 0x4
    float mSlipSpeed; // offset 0x4, size 0x4
    unsigned char mSlipEnabled; // offset 0x8, size 0x1
    class ADSR mADSR; // offset 0xC, size 0x28
    class FaderGroup mFaders; // offset 0x34, size 0x18
    class ObjPtr mFxSend; // offset 0x4C, size 0xC
    enum FXCore mFXCore; // offset 0x58, size 0x4
    unsigned char mPitchShift; // offset 0x5C, size 0x1
};
// Range: 0x8058D69C -> 0x8058D7B4
void * ChannelParams::ChannelParams(struct ChannelParams * const this /* r30 */) {
    // References
    // -> static class Symbol _default;
    // -> static class Symbol _parent;
    // -> struct [anonymous] __vt__26ObjPtr<6FxSend,9ObjectDir>;
}

// Range: 0x8058D7B4 -> 0x8058D8F4
void * StandardStream::StandardStream(class StandardStream * const this /* r28 */, class File * f /* r29 */, float startMs /* f30 */, float bufSecs /* f31 */, class Symbol & ext /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__14StandardStream;
}

// Range: 0x8058D8F4 -> 0x8058DBD0
void StandardStream::Init(class StandardStream * const this /* r29 */, float startMs /* f31 */, class Symbol & ext /* r30 */, unsigned char resync /* r27 */) {
    // Local variables
    int i; // r28

    // References
    // -> class Synth * TheSynth;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058DBD0 -> 0x8058DCB0
void StandardStream::Destroy(class StandardStream * const this /* r29 */) {}

// Range: 0x8058DCB0 -> 0x8058DFD4
void * StandardStream::~StandardStream(class StandardStream * const this /* r30 */) {
    // Local variables
    int i; // r27

    // References
    // -> struct [anonymous] __vt__26ObjPtr<6FxSend,9ObjectDir>;
    // -> struct [anonymous] __vt__14StandardStream;
}

// Range: 0x8058DFD4 -> 0x8058E24C
void StandardStream::SynthPoll(class StandardStream * const this /* r31 */) {
    // Local variables
    float frameMs; // f0
    float minTime; // r1+0xC
    float weightedThrottle; // f1
    float limit; // f1
    int jumpSample; // r0

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8058E24C -> 0x8058E778
void StandardStream::InitInfo(class StandardStream * const this /* r27 */, int numChannels /* r28 */, int sampleRate /* r29 */, unsigned char floatSamples /* r26 */) {
    // Local variables
    int bufBytes; // r30
    int numBuffers; // r26
    int i; // r30
    unsigned char slip; // r0
    int i; // r30

    // References
    // -> struct [anonymous] __vt__26ObjPtr<6FxSend,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058E778 -> 0x8058E874
unsigned char StandardStream::StuffChannels(class StandardStream * const this /* r31 */) {
    // Local variables
    unsigned char ready; // r29
    int i; // r30
}

// Range: 0x8058E874 -> 0x8058EBBC
int StandardStream::ConsumeData(class StandardStream * const this /* r28 */, void * pcmIn /* r29 */, int samples /* r1+0x8 */, int startSamp /* r26 */) {
    // Local variables
    int numChannels; // r30
    int numRealChannels; // r27
    float * pcm[30]; // r1+0x20
    int i; // r5
    unsigned int act; // r1+0x18
    int jumpSamp; // r0
    class StreamReceiver * * itr; // r27
    int sampSize; // r0
    struct pair * itr; // r27
    int chan; // r31
    signed short tmpBuf[2048]; // r1+0x98
    int i; // r6

    // References
    // -> static int kTmpBufSize;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058EBBC -> 0x8058EC10
unsigned char StandardStream::Fail() {}

// Range: 0x8058EC10 -> 0x8058EC40
unsigned char StandardStream::IsReady() {}

// Range: 0x8058EC40 -> 0x8058EC58
unsigned char StandardStream::IsFinished() {}

// Range: 0x8058EC58 -> 0x8058EC70
unsigned char StandardStream::IsPlaying() {}

// Range: 0x8058EC70 -> 0x8058EC88
unsigned char StandardStream::IsPaused() {}

// Range: 0x8058EC88 -> 0x8058ECA0
int StandardStream::GetNumChannels() {}

// Range: 0x8058ECA0 -> 0x8058ECB8
int StandardStream::GetNumChanParams() {}

// Range: 0x8058ECB8 -> 0x8058EDB8
void StandardStream::Play(class StandardStream * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058EDB8 -> 0x8058EE5C
void StandardStream::Stop(class StandardStream * const this /* r29 */) {}

// Range: 0x8058EE5C -> 0x8058EEFC
void StandardStream::Resync(class StandardStream * const this /* r31 */, float startMs /* f31 */) {
    // Local variables
    int bytes; // r1+0xC
}

// Range: 0x8058EEFC -> 0x8058F0AC
void StandardStream::SetJump(class StandardStream * const this /* r29 */, float fromMs /* f30 */, float toMs /* f31 */, const char * file /* r30 */) {
    // References
    // -> float kStreamEnd;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058F0AC -> 0x8058F0B8
void StandardStream::ClearJump() {}

// Range: 0x8058F0B8 -> 0x8058F278
void StandardStream::DoJump(class StandardStream * const this /* r29 */) {
    // Local variables
    int readAhead; // r1+0x14

    // References
    // -> class Synth * TheSynth;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058F278 -> 0x8058F28C
void StandardStream::EnableReads() {}

// Range: 0x8058F28C -> 0x8058F404
void StandardStream::UpdateTime(class StandardStream * const this /* r31 */) {
    // Local variables
    float quantum; // f30
    float rawestTime; // f0
    float rawTime; // f29
    float residue; // f28
    float t; // f28
    float qt; // f0
    float error; // f28
}

// Range: 0x8058F404 -> 0x8058F4DC
void StandardStream::UpdateTimeByFiltering(class StandardStream * const this /* r31 */) {
    // Local variables
    float error; // f31
    float kCorrectionFactor; // f2
}

// Range: 0x8058F4DC -> 0x8058F560
float StandardStream::GetRawTime(class StandardStream * const this /* r31 */) {
    // Local variables
    float streamMs; // f1
}

// Range: 0x8058F560 -> 0x8058F58C
float StandardStream::GetTime() {}

static class Symbol _default; // size: 0x4, address: 0x80A546EC
// Range: 0x8058F58C -> 0x8058F680
void StandardStream::SetVolume(class StandardStream * const this /* r29 */, int chan /* r30 */, float volDb /* f31 */) {
    // References
    // -> static class Symbol _default;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058F680 -> 0x8058F758
void StandardStream::SetPan(class StandardStream * const this /* r30 */, int chan /* r31 */, float pan /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058F758 -> 0x8058F7D8
void StandardStream::SetSpeed(class StandardStream * const this /* r30 */, float s /* f31 */) {
    // Local variables
    int j; // r31
}

// Range: 0x8058F7D8 -> 0x8058F904
void StandardStream::SetADSR(class StandardStream * const this /* r30 */, int chan /* r29 */, const class ADSR & adsr /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058F904 -> 0x8058F9AC
float StandardStream::GetVolume(const class StandardStream * const this /* r30 */, int chan /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058F9AC -> 0x8058FA50
float StandardStream::GetPan(const class StandardStream * const this /* r30 */, int chan /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058FA50 -> 0x8058FA58
float StandardStream::GetSpeed() {}

// Range: 0x8058FA58 -> 0x8058FB08
int StandardStream::MsToSamp(class StandardStream * const this /* r31 */, float ms /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _parent; // size: 0x4, address: 0x80A546F4
static class Symbol _default; // size: 0x4, address: 0x80A546FC
// Range: 0x8058FB08 -> 0x8058FCA0
void StandardStream::UpdateVolumes(class StandardStream * const this /* r31 */) {
    // Local variables
    float streamVol; // f31
    struct ChannelParams * * itr; // r30
    int i; // r29
    float channelVol; // f1

    // References
    // -> static class Symbol _default;
    // -> static class Symbol _parent;
}

// Range: 0x8058FCA0 -> 0x8058FD1C
void StandardStream::UpdateFXSends(class StandardStream * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x8058FD1C -> 0x8058FDC0
class FaderGroup & StandardStream::ChannelFaders(class StandardStream * const this /* r30 */, int channel /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058FDC0 -> 0x8058FE3C
void StandardStream::AddVirtualChannels(class StandardStream * const this /* r30 */, int n /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058FE3C -> 0x8058FEBC
void StandardStream::RemapChannel() {}

// Range: 0x8058FEBC -> 0x8058FFB4
void StandardStream::UpdateSpeed(class StandardStream * const this /* r29 */, int chn /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058FFB4 -> 0x80590098
void StandardStream::EnableSlipStreaming(class StandardStream * const this /* r29 */, int channel /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80590098 -> 0x80590158
void StandardStream::SetSlipOffset(class StandardStream * const this /* r30 */, int channel /* r31 */, float ms /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80590158 -> 0x80590208
void StandardStream::SlipStop(class StandardStream * const this /* r30 */, int channel /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80590208 -> 0x8059031C
void StandardStream::SetSlipSpeed(class StandardStream * const this /* r28 */, int channel /* r29 */, float speed /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8059031C -> 0x805903CC
float StandardStream::GetSlipOffset(class StandardStream * const this /* r30 */, int channel /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805903CC -> 0x805904EC
void StandardStream::SetFXSend(class StandardStream * const this /* r28 */, int channel /* r29 */, class FxSend * send /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805904EC -> 0x805905AC
void StandardStream::SetFX(class StandardStream * const this /* r29 */, int channel /* r30 */, unsigned char fx /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805905AC -> 0x8059065C
unsigned char StandardStream::GetFX(const class StandardStream * const this /* r30 */, int channel /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8059065C -> 0x8059070C
void StandardStream::SetFXCore(class StandardStream * const this /* r29 */, int channel /* r30 */, enum FXCore fxc /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8059070C -> 0x805907B0
enum FXCore StandardStream::GetFXCore(const class StandardStream * const this /* r30 */, int channel /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805907B0 -> 0x805907DC
void StandardStream::SetPitchShift() {}

struct {
    // total size: 0xC8
} __vt__14StandardStream; // size: 0xC8, address: 0x8091F770
struct {
    // total size: 0x8
} __RTTI__PPv; // size: 0x8, address: 0x8091F8E8
struct {
    // total size: 0x8
} __RTTI__PPQ214StandardStream13ChannelParams; // size: 0x8, address: 0x8091F918
struct {
    // total size: 0x8
} __RTTI__PP14StreamReceiver; // size: 0x8, address: 0x8091F938
struct _OKToMemCpy {
    // total size: 0x1
};
static int kTmpBufSize; // size: 0x4, address: 0x80A57CE0

