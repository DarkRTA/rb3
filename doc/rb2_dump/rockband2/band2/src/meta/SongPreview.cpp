/*
    Compile unit: C:\rockband2\band2\src\meta\SongPreview.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80176EC8 -> 0x801784F4
*/
class SongPreview TheSongPreview; // size: 0x54, address: 0x80979DBC
// Range: 0x80176EC8 -> 0x80176F08
static class DataNode OnSongPreviewStart() {
    // References
    // -> class SongPreview TheSongPreview;
}

// Range: 0x80176F08 -> 0x80176F74
static class DataNode OnSongPreviewFgInstr(class DataArray * args /* r31 */) {
    // References
    // -> class SongPreview TheSongPreview;
}

// Range: 0x80176F74 -> 0x80176FD4
static class DataNode OnSongPreviewFg(class DataArray * args /* r31 */) {
    // References
    // -> class SongPreview TheSongPreview;
}

// Range: 0x80176FD4 -> 0x80177034
static class DataNode OnSongPreviewBg(class DataArray * args /* r31 */) {
    // References
    // -> class SongPreview TheSongPreview;
}

// Range: 0x80177034 -> 0x80177094
static class DataNode OnSongPreviewCrowd(class DataArray * args /* r31 */) {
    // References
    // -> class SongPreview TheSongPreview;
}

// Range: 0x80177094 -> 0x801770F4
static class DataNode OnSongPreviewVocals(class DataArray * args /* r31 */) {
    // References
    // -> class SongPreview TheSongPreview;
}

// Range: 0x801770F4 -> 0x80177160
void * SongPreview::SongPreview() {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__11SongPreview;
}

// Range: 0x80177160 -> 0x80177668
void SongPreview::Init(class SongPreview * const this /* r31 */) {
    // Local variables
    class DataArray * cfg; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__5Fader;
    // -> class Symbol name;
}

// Range: 0x80177668 -> 0x80177814
void SongPreview::Terminate(class SongPreview * const this /* r31 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x80177814 -> 0x8017796C
void SongPreview::Start(class SongPreview * const this /* r29 */, class Symbol & song /* r30 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
    // -> class SongMgr & TheSongMgr;
    // -> const char * gNullStr;
}

// Range: 0x8017796C -> 0x80177A04
void SongPreview::ContentMounted(class SongPreview * const this /* r30 */, const char * contentName /* r31 */) {
    // Local variables
    class Symbol s; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80177A04 -> 0x80177AB8
void SongPreview::ContentFailed(class SongPreview * const this /* r30 */, const char * contentName /* r31 */) {
    // Local variables
    class Symbol s; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80177AB8 -> 0x80177B70
void SongPreview::PreparePreview(class SongPreview * const this /* r31 */) {
    // Local variables
    float startMs; // r1+0x14
    float endMs; // r1+0x10

    // References
    // -> class SongMgr & TheSongMgr;
}

// Range: 0x80177B70 -> 0x80177DF0
void SongPreview::Poll(class SongPreview * const this /* r31 */) {
    // Local variables
    const char * c; // r4

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class ContentMgr & TheContentMgr;
    // -> class GameMode * TheGameMode;
    // -> class UIManager TheUI;
    // -> class SongMgr & TheSongMgr;
    // -> const char * gNullStr;
}

// Range: 0x80177DF0 -> 0x80177ED4
void SongPreview::OnStart(class SongPreview * const this /* r30 */, class DataArray * args /* r31 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x80177ED4 -> 0x80177EE0
void SongPreview::OnFgInstr() {}

// Range: 0x80177EE0 -> 0x80177EEC
void SongPreview::OnFg() {}

// Range: 0x80177EEC -> 0x80177EF8
void SongPreview::OnBg() {}

// Range: 0x80177EF8 -> 0x80177F04
void SongPreview::OnCrowd() {}

// Range: 0x80177F04 -> 0x80177F10
void SongPreview::OnVocals() {}

// Range: 0x80177F10 -> 0x80177F98
void SongPreview::DetachFader(class SongPreview * const this /* r29 */, class Fader * fader /* r30 */) {
    // Local variables
    int ch; // r31
    class FaderGroup & faders; // r0
}

// Range: 0x80177F98 -> 0x80177FF8
void SongPreview::DetachFaders(class SongPreview * const this /* r31 */) {}

// Range: 0x80177FF8 -> 0x801781D0
void SongPreview::PrepareFaders(class SongPreview * const this /* r25 */, const class DataArray * song_data /* r26 */) {
    // Local variables
    class DataArray * crowd_sing_array; // r29
    class DataArray * fg_array; // r28
    class DataArray * crowd_array; // r27
    class DataArray * vocals_array; // r30
    int ch; // r31
    class FaderGroup & faders; // r26
}

// Range: 0x801781D0 -> 0x801784AC
void SongPreview::PrepareSong(class SongPreview * const this /* r31 */, class Symbol & song /* r26 */) {
    // Local variables
    const class DataArray * songData; // r26
    class String filePrev; // r1+0x28
    class DataArray * pans; // r27
    class DataArray * volumes; // r28
    int i; // r29

    // References
    // -> class Synth * TheSynth;
    // -> class Debug TheDebug;
    // -> int sHeap;
    // -> class SongMgr & TheSongMgr;
}

struct {
    // total size: 0x40
} __vt__11SongPreview; // size: 0x40, address: 0x80899998
struct {
    // total size: 0x8
} __RTTI__11SongPreview; // size: 0x8, address: 0x808999F0
// Range: 0x801784AC -> 0x801784F4
static void __sinit_\SongPreview_cpp() {
    // References
    // -> class SongPreview TheSongPreview;
}

class StreamReader {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};

