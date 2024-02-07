/*
    Compile unit: C:\rockband2\system\src\rndobj\Distort.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80485FF4 -> 0x804876A0
*/
class DataArray * types; // size: 0x4, address: 0x80A52B28
class Symbol name; // size: 0x4, address: 0x80A52B30
class RndDistort : public RndDrawable {
    // total size: 0xB0
protected:
    class ObjPtrList mDistortions; // offset 0x34, size 0x14
    float mShine; // offset 0x48, size 0x4
    class Vector2 mCenter; // offset 0x4C, size 0x8
    float mStrength; // offset 0x54, size 0x4
    float mDuration; // offset 0x58, size 0x4
    float mYRange; // offset 0x5C, size 0x4
    float mXScale; // offset 0x60, size 0x4
    float mWaveLength; // offset 0x64, size 0x4
    float mGlint; // offset 0x68, size 0x4
    unsigned char mSingle; // offset 0x6C, size 0x1
};
// Range: 0x80485FF4 -> 0x804860BC
void RndDistort::ListDrawChildren(class list & l /* r30 */) {
    // Local variables
    class iterator distIter; // r1+0x24
    class iterator distEnd; // r1+0x20

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndDrawable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x804860BC -> 0x80486480
void RndDistort::Copy(class RndDistort * const this /* r29 */, const class Object * o /* r27 */) {
    // Local variables
    const class RndDistort * f; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndDistort;
}

// Range: 0x80486480 -> 0x80486484
void RndDistort::DrawShowing() {}

// Range: 0x80486484 -> 0x804866BC
void * RndDistort::~RndDistort(class RndDistort * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
}

// Range: 0x804866BC -> 0x80486808
void * RndDistort::RndDistort(class RndDistort * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__10RndDistort;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

static class Symbol _s; // size: 0x4, address: 0x80A52B38
static class Symbol _s; // size: 0x4, address: 0x80A52B40
// Range: 0x80486808 -> 0x80486DD4
class DataNode RndDistort::Handle(class RndDistort * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A52B48
static class Symbol _s; // size: 0x4, address: 0x80A52B50
static class Symbol _s; // size: 0x4, address: 0x80A52B58
static class Symbol _s; // size: 0x4, address: 0x80A52B60
static class Symbol _s; // size: 0x4, address: 0x80A52B68
static class Symbol _s; // size: 0x4, address: 0x80A52B70
static class Symbol _s; // size: 0x4, address: 0x80A52B78
static class Symbol _s; // size: 0x4, address: 0x80A52B80
static class Symbol _s; // size: 0x4, address: 0x80A52B88
static class Symbol _s; // size: 0x4, address: 0x80A52B90
// Range: 0x80486DD4 -> 0x804876A0
unsigned char RndDistort::SyncProperty(class RndDistort * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xC0
} __vt__10RndDistort; // size: 0xC0, address: 0x808F4E20
struct {
    // total size: 0x8
} __RTTI__10RndDistort; // size: 0x8, address: 0x808F4F10

