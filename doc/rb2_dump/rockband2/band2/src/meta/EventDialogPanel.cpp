/*
    Compile unit: C:\rockband2\band2\src\meta\EventDialogPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800EA35C -> 0x800EACF0
*/
class DataArray * types; // size: 0x4, address: 0x80A4AFF8
class Symbol name; // size: 0x4, address: 0x80A4B000
class EventDialogPanel : public UIPanel {
    // total size: 0x5C
};
// Range: 0x800EA35C -> 0x800EA428
void * EventDialogPanel::~EventDialogPanel(class EventDialogPanel * const this /* r29 */) {
    // References
    // -> class BandUI * TheBandUI;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__16EventDialogPanel;
}

static class Symbol helpbar; // size: 0x4, address: 0x80A4B008
// Range: 0x800EA428 -> 0x800EA524
void EventDialogPanel::Draw(class EventDialogPanel * const this /* r30 */) {
    // Local variables
    class DataArray * cfg; // r31

    // References
    // -> class HelpBarPanel * sInstance;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol helpbar;
}

// Range: 0x800EA524 -> 0x800EA658
class DataNode EventDialogPanel::OnMsg(class EventDialogPanel * const this /* r29 */, const class BandEventStartMsg & msg /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800EA658 -> 0x800EA6D4
class DataNode EventDialogPanel::OnMsg(class EventDialogPanel * const this /* r31 */) {}

// Range: 0x800EA6D4 -> 0x800EACF0
class DataNode EventDialogPanel::Handle(class EventDialogPanel * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode _n; // r1+0x48

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__19BandEventDismissMsg;
    // -> class Symbol t;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__17BandEventStartMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xAC
} __vt__16EventDialogPanel; // size: 0xAC, address: 0x80886498
struct {
    // total size: 0x8
} __RTTI__16EventDialogPanel; // size: 0x8, address: 0x80886578

