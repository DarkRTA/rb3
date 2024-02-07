/*
    Compile unit: C:\rockband2\system\src\ui\ScrollSelect.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803E9CF8 -> 0x803EAC44
*/
class Symbol t; // size: 0x4, address: 0x80A51DDC
// Range: 0x803E9CF8 -> 0x803E9D3C
void * ScrollSelect::ScrollSelect(class ScrollSelect * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12ScrollSelect;
}

// Range: 0x803E9D3C -> 0x803E9D58
unsigned char ScrollSelect::IsScrollSelected() {}

// Range: 0x803E9D58 -> 0x803E9D94
void ScrollSelect::Store(class ScrollSelect * const this /* r31 */) {}

// Range: 0x803E9D94 -> 0x803E9DA0
void ScrollSelect::Reset() {}

// Range: 0x803E9DA0 -> 0x803E9E54
unsigned char ScrollSelect::SelectScrollSelect(class ScrollSelect * const this /* r29 */, class UIComponent * c /* r30 */, class User * user /* r31 */) {}

// Range: 0x803E9E54 -> 0x803EA184
unsigned char ScrollSelect::RevertScrollSelect(class ScrollSelect * const this /* r27 */, class UIComponent * c /* r28 */, class User * user /* r29 */) {
    // Local variables
    unsigned char change; // r30
    class DataNode ret; // r1+0x40

    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__20UIComponentScrollMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
}

// Range: 0x803EA184 -> 0x803EA1AC
unsigned char ScrollSelect::CanScroll() {}

static class Symbol selected; // size: 0x4, address: 0x80A51DE4
// Range: 0x803EA1AC -> 0x803EA258
class Symbol ScrollSelect::DrawState(const class ScrollSelect * const this /* r30 */, class UIComponent * c /* r31 */) {
    // References
    // -> static class Symbol selected;
}

// Range: 0x803EA258 -> 0x803EA2A4
unsigned char ScrollSelect::CatchNavAction() {}

class UIComponentScrollSelectMsg : public Message {
    // total size: 0x8
};
static class UIComponentScrollSelectMsg scroll_select_msg; // size: 0x8, address: 0x8097E428
// Range: 0x803EA2A4 -> 0x803EA6D0
class DataNode ScrollSelect::SendScrollSelected(class ScrollSelect * const this /* r28 */, class UIComponent * c /* r29 */, class User * user /* r30 */) {
    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__26UIComponentScrollSelectMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class UIComponentScrollSelectMsg scroll_select_msg;
}

static class Symbol _s; // size: 0x4, address: 0x80A51DEC
static class Symbol _s; // size: 0x4, address: 0x80A51DF4
// Range: 0x803EA754 -> 0x803EAACC
class DataNode ScrollSelect::Handle(class ScrollSelect * const this /* r29 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__12ScrollSelect;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A51DFC
// Range: 0x803EAACC -> 0x803EAC44
unsigned char ScrollSelect::SyncProperty(class ScrollSelect * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xC
} __vt__26UIComponentScrollSelectMsg; // size: 0xC, address: 0x808E69B0
struct {
    // total size: 0x8
} __RTTI__26UIComponentScrollSelectMsg; // size: 0x8, address: 0x808E69E8
struct {
    // total size: 0x1C
} __vt__12ScrollSelect; // size: 0x1C, address: 0x808E6A10

