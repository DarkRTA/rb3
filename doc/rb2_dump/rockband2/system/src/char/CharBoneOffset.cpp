/*
    Compile unit: C:\rockband2\system\src\char\CharBoneOffset.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80320374 -> 0x80320CE8
*/
class DataArray * types; // size: 0x4, address: 0x80A50A30
// Range: 0x80320374 -> 0x8032046C
void * CharBoneOffset::CharBoneOffset(class CharBoneOffset * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__14CharBoneOffset;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x8032046C -> 0x80320590
void CharBoneOffset::Poll(class CharBoneOffset * const this /* r30 */) {
    // Local variables
    class Transform local; // r1+0x50
    class Transform world; // r1+0x10
}

// Range: 0x80320590 -> 0x8032069C
void CharBoneOffset::PollDeps(class CharBoneOffset * const this /* r29 */, class list & changedBy /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8032069C -> 0x80320748
void CharBoneOffset::Save(class CharBoneOffset * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A50A38
// Range: 0x80320748 -> 0x80320844
void CharBoneOffset::Load(class CharBoneOffset * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80320844 -> 0x80320910
void CharBoneOffset::Copy(class CharBoneOffset * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class CharBoneOffset * b; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14CharBoneOffset;
}

// Range: 0x80320910 -> 0x80320BD4
class DataNode CharBoneOffset::Handle(class CharBoneOffset * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A50A40
static class Symbol _s; // size: 0x4, address: 0x80A50A48
// Range: 0x80320BD4 -> 0x80320CE8
unsigned char CharBoneOffset::SyncProperty(class CharBoneOffset * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x90
} __vt__14CharBoneOffset; // size: 0x90, address: 0x808D0930
struct {
    // total size: 0x8
} __RTTI__14CharBoneOffset; // size: 0x8, address: 0x808D09F8

