/*
    Compile unit: C:\rockband2\system\src\char\CharNeckTwist.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8038B090 -> 0x8038BAA8
*/
class DataArray * types; // size: 0x4, address: 0x80A51348
// Range: 0x8038B090 -> 0x8038B1A8
void * CharNeckTwist::CharNeckTwist(class CharNeckTwist * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__13CharNeckTwist;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x8038B1A8 -> 0x8038B394
void CharNeckTwist::Poll(class CharNeckTwist * const this /* r29 */) {
    // Local variables
    class RndTransformable * neck; // r0
    class Transform localHead; // r1+0x30
    class RndTransformable * bone; // r30
    class Quat q; // r1+0x20
    class Vector3 tmp; // r1+0x10
    float ang; // f30
}

// Range: 0x8038B394 -> 0x8038B490
void CharNeckTwist::PollDeps(class CharNeckTwist * const this /* r29 */, class list & change /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8038B490 -> 0x8038B500
void CharNeckTwist::Save(class CharNeckTwist * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A51350
// Range: 0x8038B500 -> 0x8038B5D8
void CharNeckTwist::Load(class CharNeckTwist * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8038B5D8 -> 0x8038B6D0
void CharNeckTwist::Copy(class CharNeckTwist * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class CharNeckTwist * t; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharNeckTwist;
}

// Range: 0x8038B6D0 -> 0x8038B994
class DataNode CharNeckTwist::Handle(class CharNeckTwist * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A51358
static class Symbol _s; // size: 0x4, address: 0x80A51360
// Range: 0x8038B994 -> 0x8038BAA8
unsigned char CharNeckTwist::SyncProperty(class CharNeckTwist * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x90
} __vt__13CharNeckTwist; // size: 0x90, address: 0x808DAF10

