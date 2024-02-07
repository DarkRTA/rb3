/*
    Compile unit: C:\rockband2\system\src\char\CharMirror.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80389338 -> 0x8038A488
*/
class DataArray * types; // size: 0x4, address: 0x80A51310
// Range: 0x80389338 -> 0x803894E8
void * CharMirror::CharMirror(class CharMirror * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14CharBonesAlloc;
    // -> struct [anonymous] __vt__15CharBonesObject;
    // -> struct [anonymous] __vt__34ObjPtr<13CharServoBone,9ObjectDir>;
    // -> struct [anonymous] __vt__10CharMirror;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

static class Symbol x; // size: 0x4, address: 0x80A51318
static class Symbol xy; // size: 0x4, address: 0x80A51320
static class Symbol zw; // size: 0x4, address: 0x80A51328
static class Symbol mirror_x; // size: 0x4, address: 0x80A51330
// Range: 0x803894E8 -> 0x803897D8
void CharMirror::Poll(class CharMirror * const this /* r30 */) {
    // Local variables
    float weight; // f31
    struct MirrorOp * m; // r31
    class Vector3 * dv; // r4
    class Quat * dq; // r29
    float * da; // r4

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol mirror_x;
    // -> static class Symbol zw;
    // -> static class Symbol xy;
    // -> static class Symbol x;
}

// Range: 0x803897D8 -> 0x80389858
void CharMirror::SetServo(class CharMirror * const this /* r30 */, class CharServoBone * b /* r31 */) {}

// Range: 0x80389858 -> 0x803898D8
void CharMirror::SetMirrorServo(class CharMirror * const this /* r30 */, class CharServoBone * b /* r31 */) {}

// Range: 0x803898D8 -> 0x80389BE8
void CharMirror::SyncBones(class CharMirror * const this /* r29 */) {
    // Local variables
    class list bones; // r1+0x68
    class DataArray * cd; // r31
    int i; // r27
    int i; // r30
    class Symbol n; // r1+0x40
    class DataArray * d; // r26

    // References
    // -> const char * gNullStr;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std29_List_node<Q29CharBones4Bone>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80389BE8 -> 0x80389C68
void CharMirror::PollDeps() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80389C68 -> 0x80389CE4
void CharMirror::Save(class CharMirror * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A51334
// Range: 0x80389CE4 -> 0x80389DD0
void CharMirror::Load(class CharMirror * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80389DD0 -> 0x80389E6C
void CharMirror::Copy(class CharMirror * const this /* r29 */, const class Object * o /* r30 */, enum CopyType type /* r31 */) {
    // Local variables
    const class CharMirror * b; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10CharMirror;
}

// Range: 0x80389E6C -> 0x8038A258
class DataNode CharMirror::Handle(class CharMirror * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A5133C
static class Symbol _s; // size: 0x4, address: 0x80A51344
// Range: 0x8038A258 -> 0x8038A488
unsigned char CharMirror::SyncProperty(class CharMirror * const this /* r27 */, class DataNode & _val /* r31 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharServoBone;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xB8
} __vt__10CharMirror; // size: 0xB8, address: 0x808DACF8
struct {
    // total size: 0x8
} __RTTI__10CharMirror; // size: 0x8, address: 0x808DADE8
struct {
    // total size: 0x18
} __vt__34ObjPtr<13CharServoBone,9ObjectDir>; // size: 0x18, address: 0x808DADF0
struct {
    // total size: 0x8
} __RTTI__34ObjPtr<13CharServoBone,9ObjectDir>; // size: 0x8, address: 0x808DAE38
struct {
    // total size: 0x8
} __RTTI__PQ210CharMirror8MirrorOp; // size: 0x8, address: 0x808DAE58

