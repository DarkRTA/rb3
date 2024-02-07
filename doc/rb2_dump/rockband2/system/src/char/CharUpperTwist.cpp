/*
    Compile unit: C:\rockband2\system\src\char\CharUpperTwist.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8039519C -> 0x803963BC
*/
class DataArray * types; // size: 0x4, address: 0x80A51418
// Range: 0x8039519C -> 0x803952E4
void * CharUpperTwist::CharUpperTwist(class CharUpperTwist * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__14CharUpperTwist;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x803952E4 -> 0x80395408
void * CharUpperTwist::~CharUpperTwist(class CharUpperTwist * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

// Range: 0x80395408 -> 0x80395BA0
void CharUpperTwist::Poll(class CharUpperTwist * const this /* r31 */) {
    // Local variables
    class Quat q; // r1+0xB0
    class Vector3 tmp; // r1+0xA0
    float ang; // f0
    class Matrix3 mat; // r1+0xF0
    class Matrix3 mat; // r1+0xC0
}

// Range: 0x80395BA0 -> 0x80395CFC
void CharUpperTwist::PollDeps(class CharUpperTwist * const this /* r29 */, class list & change /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80395CFC -> 0x80395D78
void CharUpperTwist::Save(class CharUpperTwist * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A51420
// Range: 0x80395D78 -> 0x80395E5C
void CharUpperTwist::Load(class CharUpperTwist * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80395E5C -> 0x80395F98
void CharUpperTwist::Copy(class CharUpperTwist * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class CharUpperTwist * t; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14CharUpperTwist;
}

// Range: 0x80395F98 -> 0x8039625C
class DataNode CharUpperTwist::Handle(class CharUpperTwist * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A51428
static class Symbol _s; // size: 0x4, address: 0x80A51430
static class Symbol _s; // size: 0x4, address: 0x80A51438
// Range: 0x8039625C -> 0x803963BC
unsigned char CharUpperTwist::SyncProperty(class CharUpperTwist * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x90
} __vt__14CharUpperTwist; // size: 0x90, address: 0x808DC210

