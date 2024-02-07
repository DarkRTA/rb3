/*
    Compile unit: C:\rockband2\system\src\rndobj\Draw.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80487B18 -> 0x80489214
*/
class DataArray * types; // size: 0x4, address: 0x80A52B98
enum HighlightStyle sHighlightStyle; // size: 0x4, address: 0x80A52BA0
float sNormalDisplayLength; // size: 0x4, address: 0x80A47190
// Range: 0x80487B18 -> 0x80487BF8
void * RndDrawable::RndDrawable(class RndDrawable * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__11RndDrawable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

static class Timer * _t; // size: 0x4, address: 0x80A52BA4
// Range: 0x80487BF8 -> 0x80487DC0
void RndDrawable::Draw(class RndDrawable * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0x14
    class Sphere s; // r1+0x20

    // References
    // -> class RndCam * sCurrent;
    // -> static class Timer * _t;
}

// Range: 0x80487DC0 -> 0x80487E74
void RndDrawable::Highlight() {
    // Local variables
    class Sphere s; // r1+0x20

    // References
    // -> class RndCam * sCurrent;
    // -> enum HighlightStyle sHighlightStyle;
}

// Range: 0x80487E74 -> 0x80487F58
void RndDrawable::Copy(class RndDrawable * const this /* r30 */, enum CopyType type /* r31 */) {
    // Local variables
    const class RndDrawable * d; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndDrawable;
}

static int DRAW_REV; // size: 0x4, address: 0x80A47194
// Range: 0x80487F58 -> 0x80487F9C
void RndDrawable::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80487F9C -> 0x80488158
void RndDrawable::Load(class RndDrawable * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0x14
    float order; // r1+0x10

    // References
    // -> unsigned char gLoadingProxyFromDisk;
    // -> class Debug TheDebug;
    // -> static int DRAW_REV;
}

// Range: 0x80488158 -> 0x804881EC
unsigned char RndDrawable::CollideSphere(const class Segment & s /* r31 */) {
    // Local variables
    class Sphere sphere; // r1+0x10
}

static class Timer * _t; // size: 0x4, address: 0x80A52BAC
// Range: 0x804881EC -> 0x80488354
class RndDrawable * RndDrawable::Collide(class RndDrawable * const this /* r28 */, const class Segment & s /* r29 */, float & dist /* r30 */, class Plane & plane /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> static class Timer * _t;
}

// Range: 0x80488354 -> 0x80488430
int RndDrawable::CollidePlane(const class Plane & plane /* r31 */) {
    // Local variables
    class Sphere sphere; // r1+0x10
}

// Range: 0x80488430 -> 0x80488520
void RndDrawable::CollideList(class list & collisions /* r31 */) {
    // Local variables
    float dist; // r1+0x14
    class Plane plane; // r1+0x20
    class RndDrawable * o; // r0

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std37_List_node<Q211RndDrawable9Collision>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std37_List_node<Q211RndDrawable9Collision>; // size: 0x8, address: 0x808F52D8
static class Symbol _s; // size: 0x4, address: 0x80A52BB4
static class Symbol _s; // size: 0x4, address: 0x80A52BBC
static class Symbol _s; // size: 0x4, address: 0x80A52BC4
static class Symbol _s; // size: 0x4, address: 0x80A52BCC
static class Symbol _s; // size: 0x4, address: 0x80A52BD4
// Range: 0x80488520 -> 0x80488D00
class DataNode RndDrawable::Handle(class RndDrawable * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80488D00 -> 0x80488EB4
class DataNode RndDrawable::OnGetSphere(class RndDrawable * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x80488EB4 -> 0x80488F24
class DataNode RndDrawable::OnSetShowing(class RndDrawable * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x80488F24 -> 0x80488F38
class DataNode RndDrawable::OnShowing() {}

// Range: 0x80488F38 -> 0x80488F5C
class DataNode RndDrawable::OnZeroSphere() {}

static class Symbol _s; // size: 0x4, address: 0x80A52BDC
static class Symbol _s; // size: 0x4, address: 0x80A52BE4
static class Symbol _s; // size: 0x4, address: 0x80A52BEC
// Range: 0x80488F5C -> 0x80489214
unsigned char RndDrawable::SyncProperty(class RndDrawable * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xB8
} __vt__11RndDrawable; // size: 0xB8, address: 0x808F5350

