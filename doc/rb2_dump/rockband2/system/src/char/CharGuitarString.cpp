/*
    Compile unit: C:\rockband2\system\src\char\CharGuitarString.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803B86DC -> 0x803B9670
*/
class DataArray * types; // size: 0x4, address: 0x80A51708
// Range: 0x803B86DC -> 0x803B885C
void * CharGuitarString::CharGuitarString(class CharGuitarString * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__16CharGuitarString;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x803B885C -> 0x803B89AC
void * CharGuitarString::~CharGuitarString(class CharGuitarString * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

// Range: 0x803B89AC -> 0x803B8C44
void CharGuitarString::Poll(class CharGuitarString * const this /* r28 */) {
    // Local variables
    class Transform t; // r1+0x30
    const class Vector3 & nut; // r0
    const class Vector3 & bridge; // r0
    const class Vector3 & target; // r0
    class Vector3 c; // r1+0x20
    class Vector3 b; // r1+0x10
    float frac; // f4
}

// Range: 0x803B8C44 -> 0x803B8E0C
void CharGuitarString::PollDeps(class CharGuitarString * const this /* r29 */, class list & changedBy /* r30 */, class list & change /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x803B8E0C -> 0x803B8E94
void CharGuitarString::Save(class CharGuitarString * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A51710
// Range: 0x803B8E94 -> 0x803B8F84
void CharGuitarString::Load(class CharGuitarString * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x803B8F84 -> 0x803B9104
void CharGuitarString::Copy(class CharGuitarString * const this /* r31 */, const class Object * o /* r29 */) {
    // Local variables
    const class CharGuitarString * p; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16CharGuitarString;
}

static class Symbol _s; // size: 0x4, address: 0x80A51718
// Range: 0x803B9104 -> 0x803B94C4
class DataNode CharGuitarString::Handle(class CharGuitarString * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A51720
static class Symbol _s; // size: 0x4, address: 0x80A51728
static class Symbol _s; // size: 0x4, address: 0x80A51730
static class Symbol _s; // size: 0x4, address: 0x80A51738
// Range: 0x803B94C4 -> 0x803B9670
unsigned char CharGuitarString::SyncProperty(class CharGuitarString * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x90
} __vt__16CharGuitarString; // size: 0x90, address: 0x808DF7F0
struct {
    // total size: 0x8
} __RTTI__16CharGuitarString; // size: 0x8, address: 0x808DF8B8

