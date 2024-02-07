/*
    Compile unit: C:\rockband2\system\src\char\CharLookAt.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803845B4 -> 0x80386974
*/
class DataArray * types; // size: 0x4, address: 0x80A51268
static float kMaxAng; // size: 0x4, address: 0x80A56E20
// Range: 0x803845B4 -> 0x80384720
static void DrawBounds(class Vector3 & dir /* r0 */) {
    // Local variables
    float kSize; // f7
}

// Range: 0x80384720 -> 0x8038491C
void * CharLookAt::CharLookAt(class CharLookAt * const this /* r31 */) {
    // References
    // -> static float kMaxAng;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__10CharLookAt;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8038491C -> 0x80384A9C
void * CharLookAt::~CharLookAt(class CharLookAt * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__40ObjOwnerPtr<14CharWeightable,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

// Range: 0x80384A9C -> 0x80384AB8
void CharLookAt::Enter() {}

// Range: 0x80384AB8 -> 0x80384D34
void CharLookAt::Highlight(class CharLookAt * const this /* r29 */) {
    // Local variables
    class RndGraph * g; // r31
    class Matrix3 m; // r1+0xA0
    const class Vector3 & v; // r30
}

// Range: 0x80384D34 -> 0x80385368
void CharLookAt::Poll(class CharLookAt * const this /* r29 */) {
    // Local variables
    class RndTransformable * source; // r30
    float dt; // f0
    class Vector3 delta; // r1+0x70
    float weight; // f30
    class Vector3 a; // r1+0x60
    class Vector3 b; // r1+0x50
    float yawDot; // f3
    float yaw; // f0
    float w; // f28
    float yawVel; // r1+0x10
    class Transform worldPivot; // r1+0xE0
    class Quat q; // r1+0x40
    class Matrix3 m; // r1+0xB0
    int which; // r0
    class Quat q; // r1+0x30
    class Matrix3 m; // r1+0x80
    class Matrix3 & m; // r30

    // References
    // -> class DebugFailer TheDebugFailer;
    // -> const char * kAssertStr;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80385368 -> 0x80385370
void CharLookAt::SetMinYaw() {}

// Range: 0x80385370 -> 0x80385378
void CharLookAt::SetMaxYaw() {}

// Range: 0x80385378 -> 0x80385380
void CharLookAt::SetMinPitch() {}

// Range: 0x80385380 -> 0x80385388
void CharLookAt::SetMaxPitch() {}

// Range: 0x80385388 -> 0x80385594
void CharLookAt::SyncLimits(class CharLookAt * const this /* r31 */) {
    // Local variables
    float maxYaw; // r1+0x1C
    float maxPitch; // r1+0x18
    float maxAng; // f1

    // References
    // -> static float kMaxAng;
}

// Range: 0x80385594 -> 0x80385714
void CharLookAt::PollDeps(class CharLookAt * const this /* r30 */, class list & changedBy /* r28 */, class list & change /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80385714 -> 0x80385874
void CharLookAt::Save(class CharLookAt * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A51270
// Range: 0x80385874 -> 0x80385A34
void CharLookAt::Load(class CharLookAt * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80385A34 -> 0x80385BD4
void CharLookAt::Copy(class CharLookAt * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class CharLookAt * b; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10CharLookAt;
}

// Range: 0x80385BD4 -> 0x80385FC0
class DataNode CharLookAt::Handle(class CharLookAt * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A51278
static class Symbol _s; // size: 0x4, address: 0x80A51280
static class Symbol _s; // size: 0x4, address: 0x80A51288
static class Symbol _s; // size: 0x4, address: 0x80A51290
static class Symbol _s; // size: 0x4, address: 0x80A51298
static class Symbol _s; // size: 0x4, address: 0x80A512A0
static class Symbol _s; // size: 0x4, address: 0x80A512A8
static class Symbol _s; // size: 0x4, address: 0x80A512B0
static class Symbol _s; // size: 0x4, address: 0x80A512B8
static class Symbol _s; // size: 0x4, address: 0x80A512C0
static class Symbol _s; // size: 0x4, address: 0x80A512C8
static class Symbol _s; // size: 0x4, address: 0x80A512D0
static class Symbol _s; // size: 0x4, address: 0x80A512D8
// Range: 0x80385FC0 -> 0x80386974
unsigned char CharLookAt::SyncProperty(class CharLookAt * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
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
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xE8
} __vt__10CharLookAt; // size: 0xE8, address: 0x808DA4D8

