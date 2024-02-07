/*
    Compile unit: C:\rockband2\system\src\char\CharForeTwist.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8035C538 -> 0x8035D4D8
*/
class DataArray * types; // size: 0x4, address: 0x80A50F68
// Range: 0x8035C538 -> 0x8035C65C
void * CharForeTwist::CharForeTwist(class CharForeTwist * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__13CharForeTwist;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x8035C65C -> 0x8035CA04
void CharForeTwist::Poll(class CharForeTwist * const this /* r31 */) {
    // Local variables
    class Quat q; // r1+0x50
    class Vector3 tmp; // r1+0x40
    float ang; // f30
}

// Range: 0x8035CA04 -> 0x8035CB6C
void CharForeTwist::PollDeps(class CharForeTwist * const this /* r29 */, class list & change /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8035CB6C -> 0x8035CB88
void CharForeTwist::MeasureLengthScale() {}

// Range: 0x8035CB88 -> 0x8035CC28
void CharForeTwist::Save(class CharForeTwist * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A50F70
// Range: 0x8035CC28 -> 0x8035CD38
void CharForeTwist::Load(class CharForeTwist * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8035CD38 -> 0x8035CE40
void CharForeTwist::Copy(class CharForeTwist * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class CharForeTwist * t; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharForeTwist;
}

static class Symbol _s; // size: 0x4, address: 0x80A50F78
// Range: 0x8035CE40 -> 0x8035D1E4
class DataNode CharForeTwist::Handle(class CharForeTwist * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A50F80
static class Symbol _s; // size: 0x4, address: 0x80A50F88
static class Symbol _s; // size: 0x4, address: 0x80A50F90
static class Symbol _s; // size: 0x4, address: 0x80A50F98
// Range: 0x8035D1E4 -> 0x8035D4D8
unsigned char CharForeTwist::SyncProperty(class CharForeTwist * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x90
} __vt__13CharForeTwist; // size: 0x90, address: 0x808D6AE0

