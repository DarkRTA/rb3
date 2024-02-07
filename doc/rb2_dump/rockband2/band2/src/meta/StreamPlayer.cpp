/*
    Compile unit: C:\rockband2\band2\src\meta\StreamPlayer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80193B5C -> 0x801941F8
*/
// Range: 0x80193B5C -> 0x80193BB8
void * StreamPlayer::StreamPlayer(class StreamPlayer * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12StreamPlayer;
}

// Range: 0x80193BB8 -> 0x80193C28
void * StreamPlayer::~StreamPlayer(class StreamPlayer * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__12StreamPlayer;
}

// Range: 0x80193C28 -> 0x80193C98
void StreamPlayer::Delete(class StreamPlayer * const this /* r31 */) {}

// Range: 0x80193C98 -> 0x80193D64
void StreamPlayer::PlayBuf(class StreamPlayer * const this /* r27 */, void * buf /* r28 */, int size /* r29 */, class Symbol & ext /* r30 */, float volume /* f31 */, unsigned char loop /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Synth * TheSynth;
}

// Range: 0x80193D64 -> 0x80193DBC
void StreamPlayer::SetPaused(class StreamPlayer * const this /* r31 */) {}

// Range: 0x80193DBC -> 0x80193E10
unsigned char StreamPlayer::IsPlaying() {}

// Range: 0x80193E10 -> 0x80193E24
unsigned char StreamPlayer::HasStream() {}

// Range: 0x80193E24 -> 0x80193EF0
void StreamPlayer::Poll(class StreamPlayer * const this /* r31 */) {}

// Range: 0x80193EF0 -> 0x80193F58
void StreamPlayer::Init(class StreamPlayer * const this /* r31 */) {
    // References
    // -> float kStreamEnd;
}

// Range: 0x80193F58 -> 0x80193F5C
void StreamPlayer::StopPlaying() {}

// Range: 0x80193F5C -> 0x80193F84
void StreamPlayer::SetMasterVolume(class StreamPlayer * const this /* r4 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4D054
// Range: 0x80193F84 -> 0x801941F8
class DataNode StreamPlayer::Handle(class StreamPlayer * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x54
} __vt__12StreamPlayer; // size: 0x54, address: 0x8089CCBC
struct {
    // total size: 0x8
} __RTTI__12StreamPlayer; // size: 0x8, address: 0x8089CD38

