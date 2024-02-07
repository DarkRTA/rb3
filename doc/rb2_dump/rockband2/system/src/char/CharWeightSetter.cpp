/*
    Compile unit: C:\rockband2\system\src\char\CharWeightSetter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8039D1D8 -> 0x8039E68C
*/
class DataArray * types; // size: 0x4, address: 0x80A51470
// Range: 0x8039D1D8 -> 0x8039D35C
void * CharWeightSetter::CharWeightSetter(class CharWeightSetter * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__31ObjPtr<10CharDriver,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16CharWeightSetter,9ObjectDir>;
    // -> struct [anonymous] __vt__16CharWeightSetter;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x8039D35C -> 0x8039D368
void CharWeightSetter::SetWeight() {}

// Range: 0x8039D368 -> 0x8039D500
void CharWeightSetter::Poll(class CharWeightSetter * const this /* r30 */) {
    // Local variables
    float delta; // f2

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8039D500 -> 0x8039D73C
void CharWeightSetter::PollDeps(class CharWeightSetter * const this /* r30 */, class list & changedBy /* r28 */, class list & change /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x28
    class CharWeightable * w; // r3

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14CharWeightable;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8039D73C -> 0x8039D83C
void CharWeightSetter::Save(class CharWeightSetter * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A51478
struct Node {
    // total size: 0xC
    class CharWeightable * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
// Range: 0x8039D83C -> 0x8039DC40
void CharWeightSetter::Load(class CharWeightSetter * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    class ObjPtrList w; // r1+0x24
    class iterator it; // r1+0x20

    // References
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__39ObjPtrList<14CharWeightable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8039DC40 -> 0x8039DDA0
void CharWeightSetter::Copy(class CharWeightSetter * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class CharWeightSetter * b; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16CharWeightSetter;
}

// Range: 0x8039DDA0 -> 0x8039E064
class DataNode CharWeightSetter::Handle(class CharWeightSetter * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A51480
static class Symbol _s; // size: 0x4, address: 0x80A51488
static class Symbol _s; // size: 0x4, address: 0x80A51490
static class Symbol _s; // size: 0x4, address: 0x80A51498
static class Symbol _s; // size: 0x4, address: 0x80A514A0
static class Symbol _s; // size: 0x4, address: 0x80A514A8
static class Symbol _s; // size: 0x4, address: 0x80A514B0
static class Symbol _s; // size: 0x4, address: 0x80A514B8
// Range: 0x8039E064 -> 0x8039E68C
unsigned char CharWeightSetter::SyncProperty(class CharWeightSetter * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
}

struct {
    // total size: 0x18
} __vt__39ObjPtrList<14CharWeightable,9ObjectDir>; // size: 0x18, address: 0x808DD0C8
struct {
    // total size: 0x8
} __RTTI__39ObjPtrList<14CharWeightable,9ObjectDir>; // size: 0x8, address: 0x808DD118
struct {
    // total size: 0xB8
} __vt__16CharWeightSetter; // size: 0xB8, address: 0x808DD120

