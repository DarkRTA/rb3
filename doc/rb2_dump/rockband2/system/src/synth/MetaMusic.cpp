/*
    Compile unit: C:\rockband2\system\src\synth\MetaMusic.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8057D3F0 -> 0x8057E6E8
*/
// Range: 0x8057D3F0 -> 0x8057D5B4
void * MetaMusic::MetaMusic(class MetaMusic * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__5Fader;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__29ObjPtrList<5Fader,9ObjectDir>;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__9MetaMusic;
}

// Range: 0x8057D5B4 -> 0x8057D8A4
void * MetaMusic::~MetaMusic(class MetaMusic * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__29ObjPtrList<5Fader,9ObjectDir>;
    // -> struct [anonymous] __vt__9MetaMusic;
}

// Range: 0x8057D8A4 -> 0x8057D8D8
unsigned char MetaMusic::Loaded() {}

static int _x; // size: 0x4, address: 0x80A54540
// Range: 0x8057D8D8 -> 0x8057DC18
void MetaMusic::Poll(class MetaMusic * const this /* r31 */) {
    // Local variables
    int num; // r1+0x10
    int bytes; // r1+0xC
    int largest; // r1+0x8

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> struct [anonymous] __vt__15MetaMusicLoader;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static int _x;
}

// Range: 0x8057DC18 -> 0x8057DEA0
void MetaMusic::Start(class MetaMusic * const this /* r31 */) {
    // Local variables
    class iterator itr; // r1+0x1C

    // References
    // -> float kStreamEnd;
    // -> class Synth * TheSynth;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8057DEA0 -> 0x8057DEB4
unsigned char MetaMusic::IsPlaying() {}

// Range: 0x8057DEB4 -> 0x8057DEBC
unsigned char MetaMusic::IsFading() {}

// Range: 0x8057DEBC -> 0x8057DF50
void MetaMusic::Stop(class MetaMusic * const this /* r31 */) {}

// Range: 0x8057DF50 -> 0x8057DF60
void MetaMusic::Mute() {}

// Range: 0x8057DF60 -> 0x8057DF70
void MetaMusic::UnMute() {}

// Range: 0x8057DF70 -> 0x8057E0AC
void MetaMusic::AddFader(class MetaMusic * const this /* r31 */, class Fader * f /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A54548
static class Symbol _s; // size: 0x4, address: 0x80A54550
static class Symbol _s; // size: 0x4, address: 0x80A54558
static class Symbol _s; // size: 0x4, address: 0x80A54560
// Range: 0x8057E0AC -> 0x8057E6C8
class DataNode MetaMusic::Handle(class MetaMusic * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class MetaMusicLoader : public Loader {
    // total size: 0x1C
    class File * mFile; // offset 0x14, size 0x4
    int & mBytesRead; // offset 0x18, size 0x4
};
// Range: 0x8057E6C8 -> 0x8057E6CC
void MetaMusicLoader::PollLoading() {}

// Range: 0x8057E6CC -> 0x8057E6E8
unsigned char MetaMusicLoader::IsLoaded(class MetaMusicLoader * const this /* r4 */) {}

struct {
    // total size: 0x14
} __vt__15MetaMusicLoader; // size: 0x14, address: 0x8091D554
struct {
    // total size: 0x8
} __RTTI__15MetaMusicLoader; // size: 0x8, address: 0x8091D588
struct {
    // total size: 0x54
} __vt__9MetaMusic; // size: 0x54, address: 0x8091D590
struct {
    // total size: 0x8
} __RTTI__9MetaMusic; // size: 0x8, address: 0x8091D608

