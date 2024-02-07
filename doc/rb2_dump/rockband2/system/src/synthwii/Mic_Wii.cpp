/*
    Compile unit: C:\rockband2\system\src\synthwii\Mic_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80562828 -> 0x80563D50
*/
class Symbol t; // size: 0x4, address: 0x80A540E4
static float kLagIdeal; // size: 0x4, address: 0x80A57A70
static float kLagDelta; // size: 0x4, address: 0x80A57A74
static float volume; // size: 0x4, address: 0x80A475F8
static class MemStream * gDebugAudio; // size: 0x4, address: 0x80A540E8
static int _x; // size: 0x4, address: 0x80A540EC
// Range: 0x80562828 -> 0x80562988
void * MicWii::MicWii(class MicWii * const this /* r30 */) {
    // References
    // -> static int _x;
    // -> static float volume;
    // -> struct [anonymous] __vt__6MicWii;
}

// Range: 0x80562988 -> 0x80562A38
void * MicWii::~MicWii(class MicWii * const this /* r29 */) {
    // References
    // -> static class MemStream * gDebugAudio;
    // -> struct [anonymous] __vt__6MicWii;
}

struct /* @class$12725Mic_Wii_cpp */ {
    // total size: 0x24
    unsigned long numEntries; // offset 0x0, size 0x4
    unsigned long entries[8]; // offset 0x4, size 0x20
};
struct /* @class$12726Mic_Wii_cpp */ {
    // total size: 0x8
    unsigned long lowerBoundary; // offset 0x0, size 0x4
    unsigned long upperBoundary; // offset 0x4, size 0x4
};
union /* @class$12724Mic_Wii_cpp */ {
    struct /* @class$12725Mic_Wii_cpp */ {
        // total size: 0x24
        unsigned long numEntries; // offset 0x0, size 0x4
        unsigned long entries[8]; // offset 0x4, size 0x20
    } list; // offset 0x0, size 0x24
    struct /* @class$12726Mic_Wii_cpp */ {
        // total size: 0x8
        unsigned long lowerBoundary; // offset 0x0, size 0x4
        unsigned long upperBoundary; // offset 0x4, size 0x4
    } range; // offset 0x0, size 0x8
};
struct micSamplingFormat {
    // total size: 0x28
    unsigned char channels; // offset 0x0, size 0x1
    unsigned char bitResolution; // offset 0x1, size 0x1
    unsigned char samplingRateType; // offset 0x2, size 0x1
    union /* @class$12724Mic_Wii_cpp */ {
        struct /* @class$12725Mic_Wii_cpp */ {
            // total size: 0x24
            unsigned long numEntries; // offset 0x0, size 0x4
            unsigned long entries[8]; // offset 0x4, size 0x20
        } list; // offset 0x0, size 0x24
        struct /* @class$12726Mic_Wii_cpp */ {
            // total size: 0x8
            unsigned long lowerBoundary; // offset 0x0, size 0x4
            unsigned long upperBoundary; // offset 0x4, size 0x4
        } range; // offset 0x0, size 0x8
    } samplingRates; // offset 0x4, size 0x24
};
struct micDesc {
    // total size: 0x2C
    unsigned char numSamplingFormats; // offset 0x0, size 0x1
    struct micSamplingFormat formats[1]; // offset 0x4, size 0x28
};
class MicrophonesChangedMsg : public Message {
    // total size: 0x8
};
// Range: 0x80562A38 -> 0x805632AC
void MicWii::Poll(class MicWii * const this /* r30 */) {
    // Local variables
    int writePos; // r29
    int playPos; // r0
    float lag; // f4
    float avgLag; // f0
    float vol; // f1
    struct micDesc md; // r1+0x58
    long res; // r0
    class MicrophonesChangedMsg msg; // r1+0x50
    class MicrophonesChangedMsg msg; // r1+0x48
    int i; // r29
    unsigned char micTaken; // r31
    int j; // r28
    class MicWii * mic; // r0

    // References
    // -> class Synth * TheSynth;
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__21MicrophonesChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class Debug TheDebug;
    // -> static float kLagIdeal;
    // -> static float kLagDelta;
}

// Range: 0x805632AC -> 0x805632B4
void MicWii::SetConnected() {}

struct micOpenParam {
    // total size: 0x8
    unsigned char channels; // offset 0x0, size 0x1
    unsigned char bitResolution; // offset 0x1, size 0x1
    unsigned short bufferMilliseconds; // offset 0x2, size 0x2
    unsigned long samplingRate; // offset 0x4, size 0x4
};
// Range: 0x805632B4 -> 0x80563504
void MicWii::Start(class MicWii * const this /* r30 */) {
    // Local variables
    long rc; // r4
    struct micDesc desc; // r1+0x10
    struct micOpenParam openParam; // r1+0x8
    int i; // r29
    float micVolume; // f0

    // References
    // -> class Debug TheDebug;
}

static int _x; // size: 0x4, address: 0x80A540F4
// Range: 0x80563504 -> 0x80563660
void MicWii::StartPlayback(class MicWii * const this /* r31 */) {
    // References
    // -> static int _x;
    // -> static float kLagIdeal;
}

// Range: 0x80563660 -> 0x805636A0
void MicWii::StopPlayback(class MicWii * const this /* r31 */) {}

// Range: 0x805636A0 -> 0x805636E8
void MicWii::Stop(class MicWii * const this /* r31 */) {}

// Range: 0x805636E8 -> 0x805636F0
unsigned char MicWii::IsRunning() {}

// Range: 0x805636F0 -> 0x8056375C
enum Type MicWii::GetType(const class MicWii * const this /* r30 */) {
    // Local variables
    struct micDesc md; // r1+0x8
    long rc; // r0
    int loop; // r31
}

// Range: 0x8056375C -> 0x80563764
void MicWii::SetDMA() {}

// Range: 0x80563764 -> 0x8056376C
unsigned char MicWii::GetDMA() {}

// Range: 0x8056376C -> 0x8056388C
void MicWii::SetGain(class MicWii * const this /* r30 */, float gain /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8056388C -> 0x80563894
float MicWii::GetGain() {}

// Range: 0x80563894 -> 0x80563910
void MicWii::SetVolume(class MicWii * const this /* r31 */) {
    // Local variables
    float v; // f31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80563910 -> 0x80563918
float MicWii::GetVolume() {}

// Range: 0x80563918 -> 0x805639B4
void MicWii::SetEarpieceVolume(class MicWii * const this /* r31 */, float volume /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805639B4 -> 0x805639BC
float MicWii::GetEarpieceVolume() {}

// Range: 0x805639BC -> 0x805639C0
void MicWii::SetCompressor() {}

// Range: 0x805639C0 -> 0x805639C8
unsigned char MicWii::GetCompressor() {}

// Range: 0x805639C8 -> 0x805639D0
float MicWii::GetCompressorParam() {}

// Range: 0x805639D0 -> 0x805639D4
void MicWii::SetCompressorParam() {}

// Range: 0x805639D4 -> 0x805639DC
signed short * MicWii::GetBuf() {}

// Range: 0x805639DC -> 0x805639E4
int MicWii::GetBufSamples() {}

// Range: 0x805639E4 -> 0x805639F0
int MicWii::GetSampleRate() {}

// Range: 0x805639F0 -> 0x80563A4C
signed short * MicWii::GetBuf(class MicWii * const this /* r30 */, int & samples /* r31 */) {}

// Range: 0x80563A4C -> 0x80563A54
int MicWii::GetAssignedPad() {}

// Range: 0x80563A54 -> 0x80563A58
void MicWii::ReleaseMic() {}

// Range: 0x80563A58 -> 0x80563B24
void MicWii::Update(class MicWii * const this /* r31 */) {
    // Local variables
    unsigned long bufferSize; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80563B24 -> 0x80563C5C
void MicWii::AddData(class MicWii * const this /* r27 */, void * data /* r28 */, int bytes /* r29 */) {
    // Local variables
    unsigned char * bufferEnd; // r4
    int size1; // r31
    int size2; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80563C5C -> 0x80563C84
void MicWii::SetFX() {}

// Range: 0x80563C84 -> 0x80563CE4
void MicWii::SetMute(class MicWii * const this /* r5 */) {}

// Range: 0x80563CE4 -> 0x80563CEC
void MicWii::AssignUSBMic() {}

// Range: 0x80563CEC -> 0x80563D50
unsigned char MicWii::MicConnected(int micIndex /* r30 */) {
    // Local variables
    struct micDesc md; // r1+0x8
    long rc; // r0
    int loop; // r31
}

struct {
    // total size: 0xC
} __vt__21MicrophonesChangedMsg; // size: 0xC, address: 0x8091A040
struct {
    // total size: 0x8
} __RTTI__21MicrophonesChangedMsg; // size: 0x8, address: 0x8091A070
struct {
    // total size: 0x80
} __vt__6MicWii; // size: 0x80, address: 0x8091A098
struct {
    // total size: 0x8
} __RTTI__6MicWii; // size: 0x8, address: 0x8091A130
struct {
    // total size: 0x8
} __RTTI__3Mic; // size: 0x8, address: 0x8091A138

