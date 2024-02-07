/*
    Compile unit: C:\rockband2\system\src\char\CharPollGroup.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8038D2A8 -> 0x8038E6E4
*/
class DataArray * types; // size: 0x4, address: 0x80A51390
// Range: 0x8038D2A8 -> 0x8038D390
void * CharPollGroup::CharPollGroup(class CharPollGroup * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtrList<12CharPollable,9ObjectDir>;
    // -> struct [anonymous] __vt__13CharPollGroup;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

struct Node {
    // total size: 0xC
    class CharPollable * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
// Range: 0x8038D390 -> 0x8038D594
void * CharPollGroup::~CharPollGroup(class CharPollGroup * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__37ObjPtrList<12CharPollable,9ObjectDir>;
}

class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
// Range: 0x8038D594 -> 0x8038D600
void CharPollGroup::Enter() {
    // Local variables
    class iterator it; // r1+0x18
}

// Range: 0x8038D600 -> 0x8038D66C
void CharPollGroup::Exit() {
    // Local variables
    class iterator it; // r1+0x18
}

// Range: 0x8038D66C -> 0x8038D6D8
void CharPollGroup::Poll() {
    // Local variables
    class iterator it; // r1+0x18
}

// Range: 0x8038D6D8 -> 0x8038D794
void CharPollGroup::ListPollChildren(class list & l /* r30 */) {
    // Local variables
    class iterator it; // r1+0x1C

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndPollable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8038D794 -> 0x8038D820
void CharPollGroup::PollDeps(class list & changedBy /* r30 */, class list & change /* r31 */) {
    // Local variables
    class iterator it; // r1+0x18
}

// Range: 0x8038D820 -> 0x8038D884
void CharPollGroup::Save(class CharPollGroup * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A51398
// Range: 0x8038D884 -> 0x8038D950
void CharPollGroup::Load(class CharPollGroup * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8038D950 -> 0x8038DCB8
void CharPollGroup::Copy(class CharPollGroup * const this /* r29 */, const class Object * o /* r27 */) {
    // Local variables
    const class CharPollGroup * p; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharPollGroup;
}

// Range: 0x8038DCB8 -> 0x8038DF7C
class DataNode CharPollGroup::Handle(class CharPollGroup * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A513A0
// Range: 0x8038DF7C -> 0x8038E040
unsigned char CharPollGroup::SyncProperty(class CharPollGroup * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
}

// Range: 0x8038E040 -> 0x8038E6E4
unsigned char PropSync(class ObjPtrList & l /* r26 */, class DataNode & n /* r27 */, class DataArray * prop /* r28 */, int i /* r29 */, enum PropOp op /* r30 */) {
    // Local variables
    class iterator it; // r1+0x1C
    int which; // r3
    class CharPollable * obj; // r31
    class CharPollable * obj; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12CharPollable;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x90
} __vt__13CharPollGroup; // size: 0x90, address: 0x808DB1F0
struct {
    // total size: 0x8
} __RTTI__13CharPollGroup; // size: 0x8, address: 0x808DB2B8
struct {
    // total size: 0x18
} __vt__37ObjPtrList<12CharPollable,9ObjectDir>; // size: 0x18, address: 0x808DB2C0
struct {
    // total size: 0x8
} __RTTI__37ObjPtrList<12CharPollable,9ObjectDir>; // size: 0x8, address: 0x808DB308

