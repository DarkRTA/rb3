/*
    Compile unit: C:\rockband2\system\src\char\CharTransCopy.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8039122C -> 0x80391D24
*/
class DataArray * types; // size: 0x4, address: 0x80A513E0
// Range: 0x8039122C -> 0x80391344
void * CharTransCopy::CharTransCopy(class CharTransCopy * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__13CharTransCopy;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x80391344 -> 0x8039143C
void * CharTransCopy::~CharTransCopy(class CharTransCopy * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

// Range: 0x8039143C -> 0x803914EC
void CharTransCopy::Poll() {}

// Range: 0x803914EC -> 0x803915E8
void CharTransCopy::PollDeps(class CharTransCopy * const this /* r29 */, class list & changedBy /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x803915E8 -> 0x80391658
void CharTransCopy::Save(class CharTransCopy * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A513E8
// Range: 0x80391658 -> 0x80391730
void CharTransCopy::Load(class CharTransCopy * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80391730 -> 0x80391828
void CharTransCopy::Copy(class CharTransCopy * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class CharTransCopy * i; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharTransCopy;
}

// Range: 0x80391828 -> 0x80391C14
class DataNode CharTransCopy::Handle(class CharTransCopy * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A513F0
static class Symbol _s; // size: 0x4, address: 0x80A513F8
// Range: 0x80391C14 -> 0x80391D24
unsigned char CharTransCopy::SyncProperty(class CharTransCopy * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x90
} __vt__13CharTransCopy; // size: 0x90, address: 0x808DBDA8
struct {
    // total size: 0x8
} __RTTI__13CharTransCopy; // size: 0x8, address: 0x808DBE70

