/*
    Compile unit: C:\rockband2\system\src\ui\Component.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803D8D00 -> 0x803DAEC0
*/
class DataArray * types; // size: 0x4, address: 0x80A51BB8
class Symbol name; // size: 0x4, address: 0x80A51BC0
int sSelectFrames; // size: 0x4, address: 0x80A51BC4
// Range: 0x803D8D00 -> 0x803D8EA4
void * UIComponent::UIComponent(class UIComponent * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<11UIComponent,9ObjectDir>;
    // -> struct [anonymous] __vt__11UIComponent;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x803D8EA4 -> 0x803D8F70
void UIComponent::Init() {
    // References
    // -> int sSelectFrames;
    // -> class Symbol name;
}

// Range: 0x803D8F70 -> 0x803D9104
void * UIComponent::~UIComponent(class UIComponent * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<11UIComponent,9ObjectDir>;
    // -> struct [anonymous] __vt__11UIComponent;
}

static class Symbol syms[5]; // size: 0x14, address: 0x8097E258
// Range: 0x803D9104 -> 0x803D91B0
class Symbol UIComponent::StateSym(const class UIComponent * const this /* r29 */) {
    // References
    // -> static class Symbol syms[5];
}

// Range: 0x803D91B0 -> 0x803D9354
void UIComponent::SetTypeDef(class UIComponent * const this /* r28 */, class DataArray * d /* r29 */) {
    // Local variables
    class DataArray * obj_data; // r30
    class DataArray * types; // r30
    class DataArray * def; // r29

    // References
    // -> class Debug TheDebug;
}

// Range: 0x803D9354 -> 0x803D9424
void UIComponent::Copy(class UIComponent * const this /* r29 */, enum CopyType type /* r30 */) {
    // Local variables
    const class UIComponent * c; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
}

// Range: 0x803D9424 -> 0x803D9518
void UIComponent::ResourceCopy(class UIComponent * const this /* r30 */, const class UIComponent * c /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803D9518 -> 0x803D9624
void UIComponent::CopyMembers(class UIComponent * const this /* r29 */, const class UIComponent * c /* r30 */, enum CopyType t /* r31 */) {}

// Range: 0x803D9624 -> 0x803D9668
void UIComponent::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x803D9668 -> 0x803D96C4
void UIComponent::Load(class UIComponent * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x803D96C4 -> 0x803D97D4
void UIComponent::PreLoad(class UIComponent * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
}

// Range: 0x803D97D4 -> 0x803D97E8
void UIComponent::PostLoad() {}

// Range: 0x803D97E8 -> 0x803D9800
unsigned char UIComponent::Exiting() {}

// Range: 0x803D9800 -> 0x803D984C
void UIComponent::Enter(class UIComponent * const this /* r31 */) {}

// Range: 0x803D984C -> 0x803D9854
void UIComponent::Exit() {}

// Range: 0x803D9854 -> 0x803D9874
void UIComponent::Poll() {}

static class UIComponentSelectMsg select_msg; // size: 0x8, address: 0x8097E278
// Range: 0x803D9874 -> 0x803D9C60
void UIComponent::SendSelect(class UIComponent * const this /* r29 */, class User * user /* r30 */) {
    // References
    // -> int sSelectFrames;
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__20UIComponentSelectMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class UIComponentSelectMsg select_msg;
}

// Range: 0x803D9C60 -> 0x803D9CAC
void UIComponent::MockSelect(class UIComponent * const this /* r31 */) {
    // References
    // -> int sSelectFrames;
}

static unsigned char gResettingType; // size: 0x1, address: 0x80A51BCA
// Range: 0x803D9CAC -> 0x803D9F58
void UIComponent::Update(class UIComponent * const this /* r31 */) {
    // Local variables
    class DataArray * types; // r30
    class DataArray * default_type; // r26

    // References
    // -> static unsigned char gResettingType;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

// Range: 0x803D9F58 -> 0x803D9FE0
void UIComponent::UpdateResource(class UIComponent * const this /* r31 */) {
    // References
    // -> static unsigned char gResettingType;
    // -> class UIManager TheUI;
}

static class UIComponentSelectDoneMsg select_msg; // size: 0x8, address: 0x8097E290
// Range: 0x803D9FE0 -> 0x803DA3E4
void UIComponent::FinishSelecting(class UIComponent * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__24UIComponentSelectDoneMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class UIComponentSelectDoneMsg select_msg;
    // -> class UIManager TheUI;
}

static class Symbol _s; // size: 0x4, address: 0x80A51BD0
static class Symbol _s; // size: 0x4, address: 0x80A51BD8
// Range: 0x803DA3E4 -> 0x803DAC08
class DataNode UIComponent::Handle(class UIComponent * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x58
    class DataNode _n; // r1+0x50
    class DataNode _n; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A51BE0
static class Symbol _s; // size: 0x4, address: 0x80A51BE8
// Range: 0x803DAC08 -> 0x803DAD58
unsigned char UIComponent::SyncProperty(class UIComponent * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x803DAD58 -> 0x803DAEC0
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x14C
} __vt__11UIComponent; // size: 0x14C, address: 0x808E40E8
struct {
    // total size: 0x18
} __vt__32ObjPtr<11UIComponent,9ObjectDir>; // size: 0x18, address: 0x808E4280
struct {
    // total size: 0x8
} __RTTI__32ObjPtr<11UIComponent,9ObjectDir>; // size: 0x8, address: 0x808E42C8

