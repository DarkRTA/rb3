/*
    Compile unit: C:\rockband2\system\src\synthwii\VoiceWii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80566910 -> 0x80567F94
*/
int active_voice_count; // size: 0x4, address: 0x80A54168
class Voice * gVoices[96]; // size: 0x180, address: 0x80982E30
unsigned char gPitchDone; // size: 0x1, address: 0x80A5416C
// Range: 0x80566910 -> 0x80566998
void VoiceTakeoverCallback() {
    // Local variables
    class Voice * voice; // r31

    // References
    // -> int active_voice_count;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Voice * gVoices[96];
}

// Range: 0x80566998 -> 0x80566A48
void Voice::ReleaseVoice(class Voice * const this /* r29 */) {
    // Local variables
    unsigned char intEnabled; // r30

    // References
    // -> class Voice * gVoices[96];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static int _x; // size: 0x4, address: 0x80A54170
// Range: 0x80566A48 -> 0x80566D24
void * Voice::Voice(class Voice * const this /* r29 */, void * buffer /* r30 */, int bufBytes /* r27 */, unsigned char bUseInPlace /* r24 */, unsigned char bUseMEM2 /* r25 */) {
    // References
    // -> static int _x;
    // -> class Voice * gVoices[96];
    // -> int active_voice_count;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80566D24 -> 0x80566E78
void * Voice::~Voice(class Voice * const this /* r29 */) {
    // Local variables
    unsigned char intEnabled; // r31

    // References
    // -> int active_voice_count;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Voice * gVoices[96];
}

// Range: 0x80566E78 -> 0x80566E80
void Voice::SetFormat() {}

// Range: 0x80566E80 -> 0x80566EB4
void Voice::SetStartSamp(class Voice * const this /* r31 */) {}

// Range: 0x80566EB4 -> 0x80566ED0
void Voice::SetStartByte(int byte /* r0 */) {}

// Range: 0x80566ED0 -> 0x80566F04
void Voice::SetLoopSamp(class Voice * const this /* r31 */) {}

// Range: 0x80566F04 -> 0x80566F38
void Voice::Play(class Voice * const this /* r31 */) {}

struct DSPADPCM {
    // total size: 0x60
    unsigned long num_samples; // offset 0x0, size 0x4
    unsigned long num_adpcm_nibbles; // offset 0x4, size 0x4
    unsigned long sample_rate; // offset 0x8, size 0x4
    unsigned short loop_flag; // offset 0xC, size 0x2
    unsigned short format; // offset 0xE, size 0x2
    unsigned long sa; // offset 0x10, size 0x4
    unsigned long ea; // offset 0x14, size 0x4
    unsigned long ca; // offset 0x18, size 0x4
    unsigned short coef[16]; // offset 0x1C, size 0x20
    unsigned short gain; // offset 0x3C, size 0x2
    unsigned short ps; // offset 0x3E, size 0x2
    unsigned short yn1; // offset 0x40, size 0x2
    unsigned short yn2; // offset 0x42, size 0x2
    unsigned short lps; // offset 0x44, size 0x2
    unsigned short lyn1; // offset 0x46, size 0x2
    unsigned short lyn2; // offset 0x48, size 0x2
    unsigned short pad[11]; // offset 0x4A, size 0x16
};
// Range: 0x80566F38 -> 0x80567210
void Voice::Init(class Voice * const this /* r28 */) {
    // Local variables
    struct _AXPBADDR addr; // r1+0x18
    unsigned int ls_addr; // r31
    unsigned int le_addr; // r30
    unsigned int lc_addr; // r29
    struct _AXPBADPCM adpcm; // r1+0x28
    struct _AXPBADPCMLOOP adpcmLoop; // r1+0x10
    unsigned long pMRAMStart; // r4
    struct DSPADPCM * ps; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80567210 -> 0x8056726C
void Voice::Start(class Voice * const this /* r31 */) {}

// Range: 0x8056726C -> 0x805672FC
void Voice::Pause(class Voice * const this /* r31 */) {}

// Range: 0x805672FC -> 0x80567360
void Voice::Stop(class Voice * const this /* r31 */) {}

// Range: 0x80567360 -> 0x8056739C
unsigned char Voice::IsPlaying() {}

// Range: 0x8056739C -> 0x805673B4
unsigned char Voice::IsPaused() {}

// Range: 0x805673B4 -> 0x805673F4
int Voice::SampToByte() {
    // Local variables
    int convSamp; // r0
}

// Range: 0x805673F4 -> 0x80567464
void * Voice::GetAddr() {
    // Local variables
    unsigned int addr; // r4
    unsigned int offset; // r5
}

// Range: 0x80567464 -> 0x805674D8
void Voice::SetVolume(class Voice * const this /* r31 */) {
    // Local variables
    float newVol; // f1
}

// Range: 0x805674D8 -> 0x805674E8
void Voice::SetFX() {}

// Range: 0x805674E8 -> 0x80567524
void Voice::SetADSR(class Voice * const this /* r31 */) {
    // Local variables
    float fEnv; // f0
}

// Range: 0x80567524 -> 0x8056768C
void Voice::SetPan(class Voice * const this /* r29 */, float p /* f1 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8056768C -> 0x80567704
void Voice::SetSpeed(class Voice * const this /* r4 */) {}

// Range: 0x80567704 -> 0x805677B4
void Voice::SetSampleRate(class Voice * const this /* r31 */) {
    // Local variables
    struct _AXPBSRC src; // r1+0x8
    unsigned long srcBits; // r0
}

static class Timer * _t; // size: 0x4, address: 0x80A54178
// Range: 0x805677B4 -> 0x80567974
void Voice::SyncBuffer(class Voice * const this /* r29 */, int byteStart /* r30 */, int numBytes /* r31 */) {
    // Local variables
    void * to; // r28
    class AutoTimer _at; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Timer * _t;
}

static int _x; // size: 0x4, address: 0x80A54180
// Range: 0x80567974 -> 0x80567AC0
void Voice::SetPitchShift(class Voice * const this /* r31 */) {
    // References
    // -> static int _x;
}

// Range: 0x80567AC0 -> 0x80567B28
void Voice::UpdateEnv(class Voice * const this /* r31 */) {
    // Local variables
    float fEnv; // f0
}

// Range: 0x80567B28 -> 0x80567BF4
void Voice::UpdateMix(class Voice * const this /* r31 */) {}

// Range: 0x80567BF4 -> 0x80567CE4
void Voice::Poll(class Voice * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80567CE4 -> 0x80567EE0
void Voice::PollPitchShift(class Voice * const this /* r31 */) {
    // Local variables
    unsigned char * writePtr; // r30
    class Timer t; // r1+0x8

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> unsigned char gPitchDone;
}

// Range: 0x80567EE0 -> 0x80567F38
void Voice::PollAll() {
    // Local variables
    int x; // r31

    // References
    // -> class Voice * gVoices[96];
}

// Range: 0x80567F38 -> 0x80567F94
void Voice::SynthPollAll() {
    // Local variables
    int x; // r31

    // References
    // -> class Voice * gVoices[96];
    // -> unsigned char gPitchDone;
}


