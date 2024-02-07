/*
    Compile unit: C:\rockband2\band2\src\meta\ContentLoadingPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800E03F8 -> 0x800E09F0
*/
class DataArray * types; // size: 0x4, address: 0x80A4ADA8
class Symbol name; // size: 0x4, address: 0x80A4ADB0
class ContentLoadingPanel : public UIPanel, public Callback {
    // total size: 0x6C
    unsigned char mAllowedToShow; // offset 0x34, size 0x1
    int mCount; // offset 0x38, size 0x4
    int mCurrent; // offset 0x3C, size 0x4
};
// Range: 0x800E03F8 -> 0x800E04A0
void * ContentLoadingPanel::ContentLoadingPanel(class ContentLoadingPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__19ContentLoadingPanel;
    // -> struct [anonymous] __vt__Q210ContentMgr8Callback;
}

// Range: 0x800E04A0 -> 0x800E0560
void * ContentLoadingPanel::~ContentLoadingPanel(class ContentLoadingPanel * const this /* r29 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
    // -> struct [anonymous] __vt__19ContentLoadingPanel;
}

// Range: 0x800E0560 -> 0x800E0570
void ContentLoadingPanel::ContentMounted() {}

// Range: 0x800E0570 -> 0x800E0580
void ContentLoadingPanel::ContentFailed() {}

// Range: 0x800E0580 -> 0x800E05EC
void ContentLoadingPanel::ContentDone(class ContentLoadingPanel * const this /* r30 */) {}

// Range: 0x800E05EC -> 0x800E05F4
char * ContentLoadingPanel::ContentDir() {}

// Range: 0x800E05F4 -> 0x800E0614
unsigned char ContentLoadingPanel::HasDataToShow() {}

// Range: 0x800E0614 -> 0x800E0628
void ContentLoadingPanel::AllowedToShow() {}

static class Symbol _s; // size: 0x4, address: 0x80A4ADB8
// Range: 0x800E0628 -> 0x800E09F0
class DataNode ContentLoadingPanel::Handle(class ContentLoadingPanel * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

struct {
    // total size: 0x100
} __vt__19ContentLoadingPanel; // size: 0x100, address: 0x808845D0
struct {
    // total size: 0x8
} __RTTI__19ContentLoadingPanel; // size: 0x8, address: 0x80884708

