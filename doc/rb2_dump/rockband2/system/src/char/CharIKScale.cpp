/*
    Compile unit: C:\rockband2\system\src\char\CharIKScale.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8037C638 -> 0x8037E040
*/
class DataArray * types; // size: 0x4, address: 0x80A51198
// Range: 0x8037C638 -> 0x8037C784
void * CharIKScale::CharIKScale(class CharIKScale * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__41ObjPtrList<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__11CharIKScale;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x8037C784 -> 0x8037C9FC
void * CharIKScale::~CharIKScale(class CharIKScale * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__40ObjOwnerPtr<14CharWeightable,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__41ObjPtrList<16RndTransformable,9ObjectDir>;
}

// Range: 0x8037C9FC -> 0x8037CDA8
void CharIKScale::Poll(class CharIKScale * const this /* r30 */) {
    // Local variables
    float weight; // f31
    float height; // f1
    class Transform t; // r1+0xA0
    class Vector3 v; // r1+0x50
    float scale; // f0
    class Vector3 v2; // r1+0x40
    class Vector3 diff; // r1+0x30
    class iterator tar; // r1+0x20
    class Transform t2; // r1+0x60

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8037CDA8 -> 0x8037CDC0
void CharIKScale::CaptureBefore() {}

// Range: 0x8037CDC0 -> 0x8037CDE0
void CharIKScale::CaptureAfter() {}

// Range: 0x8037CDE0 -> 0x8037CF84
void CharIKScale::PollDeps(class CharIKScale * const this /* r29 */, class list & changedBy /* r30 */, class list & change /* r31 */) {
    // Local variables
    class iterator tar; // r1+0x24

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8037CF84 -> 0x8037D060
void CharIKScale::Save(class CharIKScale * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A511A0
// Range: 0x8037D060 -> 0x8037D1B0
void CharIKScale::Load(class CharIKScale * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8037D1B0 -> 0x8037D5A0
void CharIKScale::Copy(class CharIKScale * const this /* r29 */, const class Object * o /* r28 */, enum CopyType type /* r27 */) {
    // Local variables
    const class CharIKScale * i; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharIKScale;
}

static class Symbol _s; // size: 0x4, address: 0x80A511A8
static class Symbol _s; // size: 0x4, address: 0x80A511B0
// Range: 0x8037D5A0 -> 0x8037DB48
class DataNode CharIKScale::Handle(class CharIKScale * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A511B8
static class Symbol _s; // size: 0x4, address: 0x80A511C0
static class Symbol _s; // size: 0x4, address: 0x80A511C8
static class Symbol _s; // size: 0x4, address: 0x80A511D0
static class Symbol _s; // size: 0x4, address: 0x80A511D8
static class Symbol _s; // size: 0x4, address: 0x80A511E0
// Range: 0x8037DB48 -> 0x8037E040
unsigned char CharIKScale::SyncProperty(class CharIKScale * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
    // total size: 0xB8
} __vt__11CharIKScale; // size: 0xB8, address: 0x808D90F8

