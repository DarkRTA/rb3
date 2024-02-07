/*
    Compile unit: C:\rockband2\band2\src\game\SongMgr_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800A3A80 -> 0x800A3F88
*/
class WiiSongMgr : public SongMgr {
    // total size: 0x84
    enum SongMgrState mState; // offset 0x80, size 0x4
};
// Range: 0x800A3A80 -> 0x800A3A8C
void WiiSongMgr::Init() {}

// Range: 0x800A3A8C -> 0x800A3A90
void WiiSongMgr::Terminate() {}

static class Symbol downloaded; // size: 0x4, address: 0x80A4A2E4
// Range: 0x800A3A90 -> 0x800A3B5C
char * WiiSongMgr::ContentName() {
    // Local variables
    const class DataArray * data; // r31
    class DataArray * o; // r30

    // References
    // -> static class Symbol downloaded;
}

// Range: 0x800A3B5C -> 0x800A3C30
unsigned char WiiSongMgr::IsSongMounted(const class WiiSongMgr * const this /* r30 */, class Symbol & song /* r31 */) {
    // Local variables
    const char * contentName; // r4

    // References
    // -> class ContentMgr & TheContentMgr;
    // -> class Debug TheDebug;
}

// Range: 0x800A3C30 -> 0x800A3C3C
void WiiSongMgr::ContentSongLoaded() {}

// Range: 0x800A3C3C -> 0x800A3EE4
class DataNode WiiSongMgr::Handle(class WiiSongMgr * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

enum SongMgrState {
    kSongMgr_SaveMount = 0,
    kSongMgr_SaveWrite = 1,
    kSongMgr_SaveUnmount = 2,
    kSongMgr_Ready = 3,
    kSongMgr_Failure = 4,
    kSongMgr_Max = 5,
    kSongMgr_Nil = -1,
};
// Range: 0x800A3EE4 -> 0x800A3EF8
void WiiSongMgr::SetState() {}

static class WiiSongMgr gSongMgr; // size: 0x84, address: 0x80977A0C
// Range: 0x800A3EF8 -> 0x800A3F0C
unsigned char WiiSongMgr::SongCacheNeedsWrite() {
    // References
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x800A3F0C -> 0x800A3F14
unsigned char WiiSongMgr::IsPermanentMount() {}

struct {
    // total size: 0xF0
} __vt__10WiiSongMgr; // size: 0xF0, address: 0x8087BBE0
struct {
    // total size: 0x8
} __RTTI__10WiiSongMgr; // size: 0x8, address: 0x8087BD00
// Range: 0x800A3F14 -> 0x800A3F78
static void __sinit_\SongMgr_Wii_cpp() {
    // References
    // -> class SongMgr & TheSongMgr;
    // -> struct [anonymous] __vt__10WiiSongMgr;
    // -> static class WiiSongMgr gSongMgr;
}


