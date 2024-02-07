/*
    Compile unit: C:\rockband2\band2\src\meta\StoreUIPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8019275C -> 0x801931C4
*/
class DataArray * types; // size: 0x4, address: 0x80A4D028
class DataArray * types; // size: 0x4, address: 0x80A4D030
// Range: 0x8019275C -> 0x80192824
class DataNode StoreUIPanel::FilterButtonMsg(const class ButtonDownMsg & msg /* r28 */) {
    // Local variables
    class StorePanel * sp; // r29
    class BandUser * user; // r0

    // References
    // -> class InputMgr * TheInputMgr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4D038
// Range: 0x80192824 -> 0x80192C90
class DataNode StoreUIPanel::Handle(class StoreUIPanel * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80192C90 -> 0x80192D58
class DataNode StoreHeldButtonPanel::FilterButtonMsg(const class ButtonDownMsg & msg /* r28 */) {
    // Local variables
    class StorePanel * sp; // r29
    class BandUser * user; // r0

    // References
    // -> class InputMgr * TheInputMgr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4D040
// Range: 0x80192D58 -> 0x801931C4
class DataNode StoreHeldButtonPanel::Handle(class StoreHeldButtonPanel * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xAC
} __vt__20StoreHeldButtonPanel; // size: 0xAC, address: 0x8089C95C
struct {
    // total size: 0x8
} __RTTI__20StoreHeldButtonPanel; // size: 0x8, address: 0x8089CA48
struct {
    // total size: 0xAC
} __vt__12StoreUIPanel; // size: 0xAC, address: 0x8089CA50

