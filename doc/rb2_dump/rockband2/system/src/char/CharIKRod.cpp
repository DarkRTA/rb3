/*
    Compile unit: C:\rockband2\system\src\char\CharIKRod.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8037ACE8 -> 0x8037C3C0
*/
class DataArray * types; // size: 0x4, address: 0x80A51158
// Range: 0x8037ACE8 -> 0x8037AE70
void * CharIKRod::CharIKRod(class CharIKRod * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__9CharIKRod;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x8037AE70 -> 0x8037AFC0
void * CharIKRod::~CharIKRod(class CharIKRod * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

// Range: 0x8037AFC0 -> 0x8037B024
void CharIKRod::Poll(class CharIKRod * const this /* r31 */) {
    // Local variables
    class Transform rod; // r1+0x50
    class Transform t; // r1+0x10
}

// Range: 0x8037B024 -> 0x8037B43C
unsigned char CharIKRod::ComputeRod(class CharIKRod * const this /* r28 */, class Transform & t /* r31 */) {}

// Range: 0x8037B43C -> 0x8037B528
void CharIKRod::SyncBones(class CharIKRod * const this /* r30 */) {
    // Local variables
    class Transform rod; // r1+0x20
}

// Range: 0x8037B528 -> 0x8037B6E4
void CharIKRod::PollDeps(class CharIKRod * const this /* r30 */, class list & changedBy /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8037B6E4 -> 0x8037B8BC
void CharIKRod::Save(class CharIKRod * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A51160
// Range: 0x8037B8BC -> 0x8037BAA0
void CharIKRod::Load(class CharIKRod * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8037BAA0 -> 0x8037BCB0
void CharIKRod::Copy(class CharIKRod * const this /* r30 */, const class Object * o /* r29 */) {
    // Local variables
    const class CharIKRod * r; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9CharIKRod;
}

// Range: 0x8037BCB0 -> 0x8037BF74
class DataNode CharIKRod::Handle(class CharIKRod * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A51168
static class Symbol _s; // size: 0x4, address: 0x80A51170
static class Symbol _s; // size: 0x4, address: 0x80A51178
static class Symbol _s; // size: 0x4, address: 0x80A51180
static class Symbol _s; // size: 0x4, address: 0x80A51188
static class Symbol _s; // size: 0x4, address: 0x80A51190
// Range: 0x8037BF74 -> 0x8037C3C0
unsigned char CharIKRod::SyncProperty(class CharIKRod * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x90
} __vt__9CharIKRod; // size: 0x90, address: 0x808D8BD8
struct {
    // total size: 0x8
} __RTTI__9CharIKRod; // size: 0x8, address: 0x808D8C98

