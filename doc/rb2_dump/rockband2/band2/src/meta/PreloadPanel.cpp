/*
    Compile unit: C:\rockband2\band2\src\meta\PreloadPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8013ECEC -> 0x8013FE6C
*/
class DataArray * types; // size: 0x4, address: 0x80A4BFA0
static class FileCache * gCache; // size: 0x4, address: 0x80A4BFA8
// Range: 0x8013ECEC -> 0x8013EDE0
void * PreloadPanel::PreloadPanel(class PreloadPanel * const this /* r30 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
    // -> static class FileCache * gCache;
    // -> struct [anonymous] __vt__12PreloadPanel;
    // -> struct [anonymous] __vt__Q210ContentMgr8Callback;
}

// Range: 0x8013EDE0 -> 0x8013EEA0
void * PreloadPanel::~PreloadPanel(class PreloadPanel * const this /* r29 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
    // -> struct [anonymous] __vt__12PreloadPanel;
}

// Range: 0x8013EEA0 -> 0x8013EFFC
void PreloadPanel::Load(class PreloadPanel * const this /* r29 */) {
    // Local variables
    class Symbol song; // r1+0x20
    unsigned char needMount; // r30
    const char * c; // r4

    // References
    // -> class ContentMgr & TheContentMgr;
    // -> class SongMgr & TheSongMgr;
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

// Range: 0x8013EFFC -> 0x8013F3DC
void PreloadPanel::StartCache(class PreloadPanel * const this /* r31 */) {
    // Local variables
    class Symbol song; // r1+0x2C
    class FilePath path; // r1+0x90
    const char * root; // r25
    class DataArray * songData; // r25

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class SongMgr & TheSongMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class FileCache * gCache;
}

// Range: 0x8013F3DC -> 0x8013F48C
void PreloadPanel::ContentMounted(class PreloadPanel * const this /* r30 */, const char * contentName /* r31 */) {
    // Local variables
    class Symbol s; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

static class Symbol wii_dlc_failed; // size: 0x4, address: 0x80A4BFB0
static class Message init; // size: 0x8, address: 0x80979278
// Range: 0x8013F48C -> 0x8013F728
void PreloadPanel::ContentFailed(class PreloadPanel * const this /* r31 */, const char * contentName /* r29 */) {
    // Local variables
    class Symbol s; // r1+0x1C

    // References
    // -> class BandUI * TheBandUI;
    // -> class SongMgr & TheSongMgr;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol wii_dlc_failed;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x8013F728 -> 0x8013F7A0
void PreloadPanel::CheckFileCached(class PreloadPanel * const this /* r30 */, const char * file /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> static class FileCache * gCache;
}

// Range: 0x8013F7A0 -> 0x8013F934
unsigned char PreloadPanel::IsLoaded(class PreloadPanel * const this /* r29 */) {
    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class FileCache * gCache;
    // -> const char * gNullStr;
}

// Range: 0x8013F934 -> 0x8013F93C
void PreloadPanel::ClearCache() {
    // References
    // -> static class FileCache * gCache;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BFB8
// Range: 0x8013F93C -> 0x8013FCE0
class DataNode PreloadPanel::Handle(class PreloadPanel * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BFC0
// Range: 0x8013FCE0 -> 0x8013FE6C
unsigned char PreloadPanel::SyncProperty(class PreloadPanel * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xFC
} __vt__12PreloadPanel; // size: 0xFC, address: 0x808932E8
struct {
    // total size: 0x8
} __RTTI__12PreloadPanel; // size: 0x8, address: 0x80893418

