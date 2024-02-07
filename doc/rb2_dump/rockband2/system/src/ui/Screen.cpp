/*
    Compile unit: C:\rockband2\system\src\ui\Screen.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803E7610 -> 0x803E9B34
*/
class DataArray * types; // size: 0x4, address: 0x80A51D60
class Symbol name; // size: 0x4, address: 0x80A51D68
// Range: 0x803E7610 -> 0x803E7680
void * UIScreen::UIScreen(class UIScreen * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__8UIScreen;
}

static class Symbol panels; // size: 0x4, address: 0x80A51D70
static class Symbol focus; // size: 0x4, address: 0x80A51D78
static class Symbol clear_vram; // size: 0x4, address: 0x80A51D80
// Range: 0x803E7680 -> 0x803E78C0
void UIScreen::SetTypeDef(class UIScreen * const this /* r29 */, class DataArray * data /* r30 */) {
    // Local variables
    class DataArray * panelData; // r27
    int i; // r26
    class DataArray * focusData; // r26

    // References
    // -> static class Symbol clear_vram;
    // -> static class Symbol focus;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std21_List_node<P7UIPanel>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> static class Symbol panels;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std21_List_node<P7UIPanel>; // size: 0x8, address: 0x808E6660
static class Symbol _s; // size: 0x4, address: 0x80A51D88
static class Symbol _s; // size: 0x4, address: 0x80A51D90
static class Symbol _s; // size: 0x4, address: 0x80A51D98
static class Symbol _s; // size: 0x4, address: 0x80A51DA0
static class Symbol _s; // size: 0x4, address: 0x80A51DA8
static class Symbol _s; // size: 0x4, address: 0x80A51DB0
static class Symbol _s; // size: 0x4, address: 0x80A51DB8
static class Symbol _s; // size: 0x4, address: 0x80A51DC0
// Range: 0x803E78C0 -> 0x803E864C
class DataNode UIScreen::Handle(class UIScreen * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x4C
    class MessageTimer _mt; // r1+0x78
    class DataNode _n; // r1+0x70
    class DataNode _n; // r1+0x68
    class DataNode r; // r1+0x60

    // References
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x803E864C -> 0x803E86D0
unsigned char UIScreen::Entering(class UIScreen * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x803E86D0 -> 0x803E8754
unsigned char UIScreen::Exiting(class UIScreen * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

static class Message msg; // size: 0x8, address: 0x8097E3C8
// Range: 0x803E8754 -> 0x803E88EC
void UIScreen::Poll(class UIScreen * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18
    class UIPanel * p; // r3

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x8097E3E0
// Range: 0x803E88EC -> 0x803E8B70
void UIScreen::Enter(class UIScreen * const this /* r30 */, class UIScreen * from /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x803E8B70 -> 0x803E8BF8
void UIScreen::Draw(class UIScreen * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x803E8BF8 -> 0x803E8C70
void UIScreen::SetFocusPanel(class UIScreen * const this /* r30 */, class UIPanel * panel /* r31 */) {}

// Range: 0x803E8C70 -> 0x803E8CBC
unsigned char UIScreen::InComponentSelect() {
    // Local variables
    class UIComponent * u; // r0

    // References
    // -> class UIManager TheUI;
}

// Range: 0x803E8CBC -> 0x803E8D44
unsigned char UIScreen::SharesPanels(class UIScreen * const this /* r30 */, class UIScreen * screen /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x803E8D44 -> 0x803E8D9C
unsigned char UIScreen::HasPanel() {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

static class Message msg; // size: 0x8, address: 0x8097E3F8
// Range: 0x803E8D9C -> 0x803E9030
void UIScreen::Exit(class UIScreen * const this /* r30 */, class UIScreen * to /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x803E9030 -> 0x803E90E8
void UIScreen::ReenterScreen(class UIScreen * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x1C
    struct _List_iterator i; // r1+0x18
}

// Range: 0x803E90E8 -> 0x803E90F0
void UIScreen::SetShowing() {}

static class Message msg; // size: 0x8, address: 0x8097E410
// Range: 0x803E90F0 -> 0x803E9270
void UIScreen::LoadPanels(class UIScreen * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

struct iterator {
    // total size: 0x1
};
class reverse_iterator : public iterator {
    // total size: 0x4
protected:
    struct _List_iterator current; // offset 0x0, size 0x4
};
// Range: 0x803E9270 -> 0x803E92F8
void UIScreen::UnloadPanels(class UIScreen * const this /* r31 */) {
    // Local variables
    class reverse_iterator i; // r1+0x24
}

// Range: 0x803E92F8 -> 0x803E9370
unsigned char UIScreen::CheckIsLoaded(class UIScreen * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x803E9370 -> 0x803E93CC
unsigned char UIScreen::IsLoaded() {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x803E93CC -> 0x803E9428
unsigned char UIScreen::AllPanelsDown() {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

static class Symbol file; // size: 0x4, address: 0x80A51DCC
// Range: 0x803E9428 -> 0x803E965C
void UIScreen::Print(class UIScreen * const this /* r28 */, class TextStream & s /* r29 */) {
    // Local variables
    struct _List_iterator i; // r1+0x28
    class UIPanel * p; // r30
    class DataArray * f; // r0
    class DataNode n; // r1+0x30

    // References
    // -> static class Symbol file;
}

static class Symbol goto_screen; // size: 0x4, address: 0x80A51DD4
// Range: 0x803E965C -> 0x803E999C
class DataNode UIScreen::OnMsg(class UIScreen * const this /* r29 */) {
    // Local variables
    class DataNode screen; // r1+0x48
    class DataArrayPtr msg; // r1+0x40

    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol goto_screen;
}

// Range: 0x803E999C -> 0x803E9B34
class DataNode UIScreen::ForeachPanel(class UIScreen * const this /* r29 */, const class DataArray * a /* r30 */) {
    // Local variables
    class DataNode * var; // r31
    class DataNode tmp; // r1+0x28
    struct _List_iterator p; // r1+0x10
    int j; // r27
}

struct {
    // total size: 0x80
} __vt__8UIScreen; // size: 0x80, address: 0x808E6780

