/*
    Compile unit: C:\rockband2\system\src\char\CharIKFoot.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803738AC -> 0x803742BC
*/
class DataArray * types; // size: 0x4, address: 0x80A51090
// Range: 0x803738AC -> 0x80373A30
void * CharIKFoot::CharIKFoot(class CharIKFoot * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10CharIKFoot,9ObjectDir>;
    // -> struct [anonymous] __vt__10CharIKFoot;
}

// Range: 0x80373A30 -> 0x80373B10
void * CharIKFoot::~CharIKFoot(class CharIKFoot * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__31ObjPtr<10CharIKFoot,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

// Range: 0x80373B10 -> 0x80373B34
void CharIKFoot::Poll() {}

// Range: 0x80373B34 -> 0x80373B38
void CharIKFoot::PollDeps() {}

// Range: 0x80373B38 -> 0x80373BA8
void CharIKFoot::Save(class CharIKFoot * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A51098
// Range: 0x80373BA8 -> 0x80373C8C
void CharIKFoot::Load(class CharIKFoot * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80373C8C -> 0x80373D78
void CharIKFoot::Copy(class CharIKFoot * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class CharIKFoot * f; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10CharIKFoot;
}

// Range: 0x80373D78 -> 0x8037403C
class DataNode CharIKFoot::Handle(class CharIKFoot * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A510A0
static class Symbol _s; // size: 0x4, address: 0x80A510A8
// Range: 0x8037403C -> 0x80374160
unsigned char CharIKFoot::SyncProperty(class CharIKFoot * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80374160 -> 0x803742BC
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10CharIKFoot;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0xE4
} __vt__10CharIKFoot; // size: 0xE4, address: 0x808D7A38
struct {
    // total size: 0x8
} __RTTI__10CharIKFoot; // size: 0x8, address: 0x808D7B68
struct {
    // total size: 0x18
} __vt__31ObjPtr<10CharIKFoot,9ObjectDir>; // size: 0x18, address: 0x808D7B70
struct {
    // total size: 0x8
} __RTTI__31ObjPtr<10CharIKFoot,9ObjectDir>; // size: 0x8, address: 0x808D7BB8

