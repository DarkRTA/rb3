/*
    Compile unit: C:\rockband2\system\src\world\Reflection.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8044A378 -> 0x8044B700
*/
class DataArray * types; // size: 0x4, address: 0x80A52570
class Symbol name; // size: 0x4, address: 0x80A52578
class WorldReflection : public RndDrawable, public RndTransformable {
    // total size: 0x160
    class ObjPtrList mDraws; // offset 0xF8, size 0x14
    float mVerticalStretch; // offset 0x10C, size 0x4
    class list mCulling; // offset 0x110, size 0x8
    class RndCam * mCam; // offset 0x118, size 0x4
};
// Range: 0x8044A378 -> 0x8044A624
void * WorldReflection::~WorldReflection(class WorldReflection * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__15WorldReflection;
}

static class Message startReflect; // size: 0x8, address: 0x8097F020
static class Message endReflect; // size: 0x8, address: 0x8097F038
// Range: 0x8044A624 -> 0x8044AB78
void WorldReflection::DrawShowing(class WorldReflection * const this /* r29 */) {
    // Local variables
    class Transform w; // r1+0x100
    class Transform iw; // r1+0xC0
    class Transform ref; // r1+0x80
    class iterator it; // r1+0x30
    class Character * c; // r28

    // References
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> struct [anonymous] __RTTI__9Character;
    // -> class RndCam * sCurrent;
    // -> static class Message endReflect;
    // -> static class Message startReflect;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8044AB78 -> 0x8044ABBC
void WorldReflection::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A52580
// Range: 0x8044ABBC -> 0x8044AC44
void WorldReflection::Load(class WorldReflection * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> static int gRev;
}

// Range: 0x8044AC44 -> 0x8044AFEC
void WorldReflection::Copy(class WorldReflection * const this /* r29 */, const class Object * o /* r28 */, enum CopyType type /* r27 */) {
    // Local variables
    const class WorldReflection * t; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__15WorldReflection;
}

// Range: 0x8044AFEC -> 0x8044B50C
class DataNode WorldReflection::Handle(class WorldReflection * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A52588
static class Symbol _s; // size: 0x4, address: 0x80A52590
// Range: 0x8044B50C -> 0x8044B700
unsigned char WorldReflection::SyncProperty(class WorldReflection * const this /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xF0
} __vt__15WorldReflection; // size: 0xF0, address: 0x808EDE60
struct {
    // total size: 0x8
} __RTTI__15WorldReflection; // size: 0x8, address: 0x808EDF90

