/*
    Compile unit: C:\rockband2\system\src\char\CharBlendBone.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803175B4 -> 0x80318F98
*/
class DataArray * types; // size: 0x4, address: 0x80A50988
class Symbol name; // size: 0x4, address: 0x80A50990
class DataArray * types; // size: 0x4, address: 0x80A50994
// Range: 0x803175B4 -> 0x803176C4
void * CharBlendBone::CharBlendBone(class CharBlendBone * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__13CharBlendBone;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x8031774C -> 0x80317928
void CharBlendBone::Replace(class CharBlendBone * const this /* r28 */, class Object * from /* r29 */, class Object * to /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x80317928 -> 0x80317C24
void CharBlendBone::Poll(class CharBlendBone * const this /* r28 */) {
    // Local variables
    class Transform dst; // r1+0x40
    class Quat q; // r1+0x30
    float weight; // f31
    int i; // r29
    class Quat tmp; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80317C24 -> 0x80317D58
void CharBlendBone::PollDeps(class CharBlendBone * const this /* r30 */, class list & changedBy /* r31 */) {
    // Local variables
    int i; // r28

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80317D58 -> 0x80317E64
void CharBlendBone::Save(class CharBlendBone * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int i; // r28
}

static int gRev; // size: 0x4, address: 0x80A5099C
// Range: 0x80317E64 -> 0x80318208
void CharBlendBone::Load(class CharBlendBone * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int size; // r1+0x28
    int i; // r26
    class Transform t; // r1+0x40

    // References
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80318208 -> 0x803184E4
void CharBlendBone::Copy(class CharBlendBone * const this /* r29 */, const class Object * o /* r25 */) {
    // Local variables
    const class CharBlendBone * b; // r0
    int i; // r30

    // References
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharBlendBone;
}

// Range: 0x803184E4 -> 0x803187A8
class DataNode CharBlendBone::Handle(class CharBlendBone * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A509A4
static class Symbol _s; // size: 0x4, address: 0x80A509AC
// Range: 0x803187A8 -> 0x80318960
unsigned char PropSync(class BoneEntry & _me /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x80318960 -> 0x80318AAC
unsigned char PropSync(class ObjOwnerPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A509B4
static class Symbol _s; // size: 0x4, address: 0x80A509BC
static class Symbol _s; // size: 0x4, address: 0x80A509C4
// Range: 0x80318AAC -> 0x80318CC0
unsigned char CharBlendBone::SyncProperty(class CharBlendBone * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80318CC0 -> 0x80318F98
unsigned char PropSync(class ObjVector & v /* r29 */, class DataNode & n /* r30 */, class DataArray * prop /* r26 */, int i /* r28 */, enum PropOp op /* r27 */) {
    // Local variables
    class BoneEntry * it; // r31
    class BoneEntry tmp; // r1+0x20

    // References
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x94
} __vt__13CharBlendBone; // size: 0x94, address: 0x808CFD28
struct {
    // total size: 0x8
} __RTTI__13CharBlendBone; // size: 0x8, address: 0x808CFDF0
struct {
    // total size: 0x80
} __vt__12CharPollable; // size: 0x80, address: 0x808CFDF8
struct {
    // total size: 0x8
} __RTTI__PQ213CharBlendBone9BoneEntry; // size: 0x8, address: 0x808CFE98

