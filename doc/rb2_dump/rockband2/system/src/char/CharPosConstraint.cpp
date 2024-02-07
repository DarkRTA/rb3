/*
    Compile unit: C:\rockband2\system\src\char\CharPosConstraint.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8038BE18 -> 0x8038D030
*/
class DataArray * types; // size: 0x4, address: 0x80A51368
// Range: 0x8038BE18 -> 0x8038BF80
void * CharPosConstraint::CharPosConstraint(class CharPosConstraint * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__41ObjPtrList<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__17CharPosConstraint;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x8038BF80 -> 0x8038C1B4
void * CharPosConstraint::~CharPosConstraint(class CharPosConstraint * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__41ObjPtrList<16RndTransformable,9ObjectDir>;
}

// Range: 0x8038C1B4 -> 0x8038C3C0
void CharPosConstraint::Poll(class CharPosConstraint * const this /* r29 */) {
    // Local variables
    const class Vector3 & pos; // r0
    class iterator it; // r1+0x20
    class Transform t; // r1+0x30
    float delta; // f0
    float delta; // f0
    float delta; // f0
}

// Range: 0x8038C3C0 -> 0x8038C568
void CharPosConstraint::PollDeps(class CharPosConstraint * const this /* r28 */, class list & changedBy /* r30 */, class list & change /* r31 */) {
    // Local variables
    class iterator it; // r1+0x24

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8038C568 -> 0x8038C668
void CharPosConstraint::Save(class CharPosConstraint * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A51370
// Range: 0x8038C668 -> 0x8038C810
void CharPosConstraint::Load(class CharPosConstraint * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8038C810 -> 0x8038CC0C
void CharPosConstraint::Copy(class CharPosConstraint * const this /* r29 */, const class Object * o /* r27 */) {
    // Local variables
    const class CharPosConstraint * p; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__17CharPosConstraint;
}

// Range: 0x8038CC0C -> 0x8038CED0
class DataNode CharPosConstraint::Handle(class CharPosConstraint * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A51378
static class Symbol _s; // size: 0x4, address: 0x80A51380
static class Symbol _s; // size: 0x4, address: 0x80A51388
// Range: 0x8038CED0 -> 0x8038D030
unsigned char CharPosConstraint::SyncProperty(class CharPosConstraint * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x90
} __vt__17CharPosConstraint; // size: 0x90, address: 0x808DB020
struct {
    // total size: 0x8
} __RTTI__17CharPosConstraint; // size: 0x8, address: 0x808DB0E8

