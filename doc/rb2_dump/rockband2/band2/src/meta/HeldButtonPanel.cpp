/*
    Compile unit: C:\rockband2\band2\src\meta\HeldButtonPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800EFFA8 -> 0x800F1858
*/
struct {
    // total size: 0x8
} __RTTI__PQ215HeldButtonPanel8PressRec; // size: 0x8, address: 0x808872A8
class DataArray * types; // size: 0x4, address: 0x80A4B0C0
class Symbol name; // size: 0x4, address: 0x80A4B0C8
// Range: 0x800EFFA8 -> 0x800F0038
void * HeldButtonPanel::HeldButtonPanel(class HeldButtonPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__15HeldButtonPanel;
}

// Range: 0x800F0038 -> 0x800F016C
class DataNode HeldButtonPanel::OnMsg(class HeldButtonPanel * const this /* r30 */, const class ButtonDownMsg & msg /* r29 */) {
    // Local variables
    struct StrActionRec * it; // r0

    // References
    // -> class TaskMgr TheTaskMgr;
}

static class Symbol held_buttons; // size: 0x4, address: 0x80A4B0D0
// Range: 0x800F016C -> 0x800F0630
void HeldButtonPanel::UpdateHeldButtons(class HeldButtonPanel * const this /* r28 */) {
    // Local variables
    class DataArray * elements; // r30
    int i; // r31
    float hold_time; // f0
    struct StrActionRec action; // r1+0x70

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ215HeldButtonPanel8PressRec;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol held_buttons;
}

// Range: 0x800F0630 -> 0x800F0798
void HeldButtonPanel::Exit(class HeldButtonPanel * const this /* r28 */) {}

static class Symbol on_button_held; // size: 0x4, address: 0x80A4B0D8
static class Message msg; // size: 0x8, address: 0x80978B30
static class ButtonDownMsg msgButtonDown; // size: 0x8, address: 0x80978B48
// Range: 0x800F0798 -> 0x800F1308
void HeldButtonPanel::Poll(class HeldButtonPanel * const this /* r24 */) {
    // Local variables
    class vector actionRecs; // r1+0xEC
    class vector users; // r1+0xE0
    class BandUser * * itUser; // r26
    class BandUser * pUser; // r23
    class JoypadData * joy; // r0
    struct StrActionRec * it; // r25
    enum JoypadButton button; // r0
    int i; // r25
    enum JoypadAction act; // r1+0x4C
    struct StrActionRec * it; // r0

    // References
    // -> static class ButtonDownMsg msgButtonDown;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class TaskMgr TheTaskMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> struct [anonymous] __RTTI__PQ215HeldButtonPanel8PressRec;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ215HeldButtonPanel12StrActionRec;
    // -> unsigned char gStlAllocNameLookup;
    // -> class UIManager TheUI;
    // -> static class Symbol on_button_held;
}

struct {
    // total size: 0x8
} __RTTI__PQ215HeldButtonPanel12StrActionRec; // size: 0x8, address: 0x80887320
static class Symbol _s; // size: 0x4, address: 0x80A4B0E0
// Range: 0x800F1308 -> 0x800F1858
class DataNode HeldButtonPanel::Handle(class HeldButtonPanel * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xAC
} __vt__15HeldButtonPanel; // size: 0xAC, address: 0x80887354

