/*
    Compile unit: C:\rockband2\band2\src\meta\TabInterfacePanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801942B8 -> 0x80194F80
*/
class DataArray * types; // size: 0x4, address: 0x80A4D058
// Range: 0x801942B8 -> 0x80194398
void * TabInterfacePanel::TabInterfacePanel(class TabInterfacePanel * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__17TabInterfacePanel;
    // -> struct [anonymous] __vt__12TexLoadPanel;
    // -> struct [anonymous] __vt__Q210ContentMgr8Callback;
}

// Range: 0x80194398 -> 0x801944F0
class DataNode TabInterfacePanel::OnMsg(class TabInterfacePanel * const this /* r29 */, const class UIComponentFocusChangeMsg & msg /* r30 */) {
    // Local variables
    int n; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
}

// Range: 0x801944F0 -> 0x801945A8
unsigned char TabInterfacePanel::IsFocusInsideTab(class TabInterfacePanel * const this /* r29 */) {
    // Local variables
    class UIComponent * c; // r0
    const char * focusName; // r31
    int n; // r30
}

// Range: 0x801945A8 -> 0x801945F4
char * TabInterfacePanel::GetCurrentTab() {}

static class Symbol _s; // size: 0x4, address: 0x80A4D060
static class Symbol _s; // size: 0x4, address: 0x80A4D068
// Range: 0x801945F4 -> 0x80194F80
class DataNode TabInterfacePanel::Handle(class TabInterfacePanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x40
    class MessageTimer _mt; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode _n; // r1+0x60

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__20UIComponentSelectMsg;
    // -> class Symbol t;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__25UIComponentFocusChangeMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xF4
} __vt__17TabInterfacePanel; // size: 0xF4, address: 0x8089D1A8
struct {
    // total size: 0x8
} __RTTI__PQ217TabInterfacePanel7TabData; // size: 0x8, address: 0x8089D400

