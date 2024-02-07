/*
    Compile unit: C:\rockband2\system\src\ui\Slider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803EAC44 -> 0x803EC624
*/
class DataArray * types; // size: 0x4, address: 0x80A51E00
class Symbol name; // size: 0x4, address: 0x80A51E08
// Range: 0x803EAC44 -> 0x803EAD50
void * UISlider::UISlider(class UISlider * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__8UISlider;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

static int gRev; // size: 0x4, address: 0x80A51E0C
// Range: 0x803EAD50 -> 0x803EAD94
void UISlider::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x803EAD94 -> 0x803EADF0
void UISlider::Load(class UISlider * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x803EADF0 -> 0x803EAEB4
void UISlider::PreLoad(class UISlider * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x803EAEB4 -> 0x803EAF30
void UISlider::PostLoad(class UISlider * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> static int gRev;
}

// Range: 0x803EAF30 -> 0x803EAF64
void UISlider::Enter(class UISlider * const this /* r31 */) {}

// Range: 0x803EAF64 -> 0x803EAFC4
void UISlider::DrawShowing(class UISlider * const this /* r31 */) {}

// Range: 0x803EAFC4 -> 0x803EB04C
class RndDrawable * UISlider::CollideShowing(class UISlider * const this /* r28 */, const class Segment & s /* r29 */, float & dist /* r30 */, class Plane & plane /* r31 */) {}

// Range: 0x803EB04C -> 0x803EB0A0
int UISlider::CollidePlane(class UISlider * const this /* r30 */, const class Plane & plane /* r31 */) {}

// Range: 0x803EB0A0 -> 0x803EB0A8
int UISlider::Current() {}

// Range: 0x803EB0A8 -> 0x803EB108
float UISlider::Frame() {}

// Range: 0x803EB108 -> 0x803EB164
void UISlider::SetCurrent(class UISlider * const this /* r5 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x803EB164 -> 0x803EB1AC
void UISlider::SetNumSteps() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x803EB1AC -> 0x803EB210
void UISlider::Update(class UISlider * const this /* r30 */) {}

// Range: 0x803EB210 -> 0x803EB28C
void UISlider::SyncSlider(class UISlider * const this /* r30 */) {}

// Range: 0x803EB28C -> 0x803EB364
void UISlider::SetFrame(class UISlider * const this /* r31 */, float frame /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803EB364 -> 0x803EB368
int UISlider::SelectedAux() {}

// Range: 0x803EB368 -> 0x803EB378
void UISlider::SetSelectedAux() {}

static class Symbol _s; // size: 0x4, address: 0x80A51E14
static class Symbol _s; // size: 0x4, address: 0x80A51E1C
static class Symbol _s; // size: 0x4, address: 0x80A51E24
static class Symbol _s; // size: 0x4, address: 0x80A51E2C
static class Symbol _s; // size: 0x4, address: 0x80A51E34
static class Symbol _s; // size: 0x4, address: 0x80A51E3C
static class Symbol _s; // size: 0x4, address: 0x80A51E44
static class Symbol _s; // size: 0x4, address: 0x80A51E4C
static class Symbol _s; // size: 0x4, address: 0x80A51E54
// Range: 0x803EB378 -> 0x803EC15C
class DataNode UISlider::Handle(class UISlider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x50
    class MessageTimer _mt; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode _n; // r1+0x68
    class DataNode _n; // r1+0x60

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__4User;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

// Range: 0x803EC15C -> 0x803EC57C
class DataNode UISlider::OnMsg(class UISlider * const this /* r28 */, const class ButtonDownMsg & msg /* r29 */) {
    // Local variables
    class Symbol type; // r1+0x18
    int direction; // r3
    int newStep; // r4
    enum JoypadAction action; // r0
    class User * user; // r29

    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__20UIComponentScrollMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
}

// Range: 0x803EC57C -> 0x803EC624
unsigned char UISlider::SyncProperty(class UISlider * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0x174
} __vt__8UISlider; // size: 0x174, address: 0x808E6CA0

