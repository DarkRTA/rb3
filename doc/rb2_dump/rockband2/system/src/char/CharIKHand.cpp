/*
    Compile unit: C:\rockband2\system\src\char\CharIKHand.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80374908 -> 0x80377A3C
*/
class DataArray * types; // size: 0x4, address: 0x80A510B0
// Range: 0x80374908 -> 0x80374AC4
void * CharIKHand::CharIKHand(class CharIKHand * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__41ObjPtrList<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__10CharIKHand;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x80374AC4 -> 0x80374D80
void * CharIKHand::~CharIKHand(class CharIKHand * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__40ObjOwnerPtr<14CharWeightable,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__41ObjPtrList<16RndTransformable,9ObjectDir>;
}

// Range: 0x80374D80 -> 0x80375420
void CharIKHand::Poll(class CharIKHand * const this /* r31 */) {
    // Local variables
    float weight; // f31
    class Vector3 destPos; // r1+0xC0
    class Quat destQuat; // r1+0xB0
    class Matrix3 m; // r1+0x2D0
    int i; // r28
    float weights[16]; // r1+0x290
    float total; // f30
    class iterator it; // r1+0x28
    float leftover; // f0
    class iterator it; // r1+0x24
    float w; // f29
    const class Transform & t; // r29
    class Matrix3 m; // r1+0x260
    class Quat tmp; // r1+0xA0
    class Transform dest; // r1+0x220
    class Transform x; // r1+0x1E0
    class RndTransformable * shoulder; // r28
    class RndTransformable * elbow; // r29
    class Transform t; // r1+0x1A0
    class Quat q; // r1+0x90
    class Vector3 oldFingerPos; // r1+0x80
    class Matrix3 elbowWorld; // r1+0x170
    class Matrix3 handWorld; // r1+0x140
    class Vector3 xAxis; // r1+0x70
    class Vector3 yAxis; // r1+0x60
    class Vector3 zAxis; // r1+0x50
    float angle; // f29
    class Quat q; // r1+0x40
    class Transform newWorld; // r1+0x100
    class Matrix3 m; // r1+0xD0
    class Vector3 fingerDiff; // r1+0x30
}

// Range: 0x80375420 -> 0x80375AF4
void CharIKHand::IKElbow(class CharIKHand * const this /* r28 */, class RndTransformable * elbow /* r29 */, class RndTransformable * shoulder /* r30 */) {
    // Local variables
    float c2; // f0
    float cosc; // f31
    float sinc; // f30
    class Vector3 localDst; // r1+0x90
    class Vector3 localSrc; // r1+0x80
    class Vector2 s; // r1+0x20
    class Vector2 d; // r1+0x18
    float val; // f6
    float f; // f0
    class Quat q; // r1+0x70
    class Matrix3 m; // r1+0xA0
}

// Range: 0x80375AF4 -> 0x80375B70
void CharIKHand::SetHand(class CharIKHand * const this /* r30 */, class RndTransformable * hand /* r31 */) {}

// Range: 0x80375B70 -> 0x80375BC0
void CharIKHand::UpdateHand(class CharIKHand * const this /* r31 */) {}

// Range: 0x80375BC0 -> 0x80375CC0
void CharIKHand::MeasureLengths() {
    // Local variables
    float l; // f0
}

// Range: 0x80375CC0 -> 0x803760C8
void CharIKHand::PollDeps(class CharIKHand * const this /* r29 */, class list & changedBy /* r30 */, class list & change /* r31 */) {
    // Local variables
    class iterator it; // r1+0x3C

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x803760C8 -> 0x80376210
void CharIKHand::Save(class CharIKHand * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A510B8
// Range: 0x80376210 -> 0x80376778
void CharIKHand::Load(class CharIKHand * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    class ObjPtr dest; // r1+0x1C

    // References
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80376778 -> 0x80376B94
void CharIKHand::Copy(class CharIKHand * const this /* r29 */, const class Object * o /* r28 */, enum CopyType type /* r27 */) {
    // Local variables
    const class CharIKHand * i; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10CharIKHand;
}

static class Symbol _s; // size: 0x4, address: 0x80A510C0
// Range: 0x80376B94 -> 0x80377060
class DataNode CharIKHand::Handle(class CharIKHand * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A510C8
static class Symbol _s; // size: 0x4, address: 0x80A510D0
static class Symbol _s; // size: 0x4, address: 0x80A510D8
static class Symbol _s; // size: 0x4, address: 0x80A510E0
static class Symbol _s; // size: 0x4, address: 0x80A510E8
static class Symbol _s; // size: 0x4, address: 0x80A510F0
static class Symbol _s; // size: 0x4, address: 0x80A510F8
static class Symbol _s; // size: 0x4, address: 0x80A51100
static class Symbol _s; // size: 0x4, address: 0x80A51108
static class Symbol _s; // size: 0x4, address: 0x80A51110
static class Symbol _s; // size: 0x4, address: 0x80A51118
// Range: 0x80377060 -> 0x80377A3C
unsigned char CharIKHand::SyncProperty(class CharIKHand * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xE4
} __vt__10CharIKHand; // size: 0xE4, address: 0x808D7DD4

