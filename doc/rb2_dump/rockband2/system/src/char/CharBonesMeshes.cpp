/*
    Compile unit: C:\rockband2\system\src\char\CharBonesMeshes.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8032102C -> 0x80321EF0
*/
// Range: 0x8032102C -> 0x803211A0
void * CharBonesMeshes::CharBonesMeshes(class CharBonesMeshes * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__15CharBonesMeshes;
    // -> struct [anonymous] __vt__14CharBonesAlloc;
    // -> struct [anonymous] __vt__15CharBonesObject;
}

// Range: 0x803211A0 -> 0x803213E0
void * CharBonesMeshes::~CharBonesMeshes(class CharBonesMeshes * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__15CharBonesMeshes;
}

// Range: 0x803213E0 -> 0x80321520
void CharBonesMeshes::Replace(class CharBonesMeshes * const this /* r29 */) {
    // Local variables
    class ObjOwnerPtr * it; // r30

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x80321520 -> 0x80321A64
void CharBonesMeshes::PoseMeshes(class CharBonesMeshes * const this /* r29 */) {
    // Local variables
    class ObjOwnerPtr * bone; // r31
    const class Vector3 * pend; // r28
    class Vector3 * p; // r30
    const class Quat * qend; // r28
    class Quat * q; // r27
    float * a; // r30
    const float * xend; // r27
    const float * yend; // r27
    const float * end; // r27
    const class Vector3 * send; // r27
    class Vector3 * s; // r30
    class Vector3 blendScale; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80321A64 -> 0x80321B48
void CharBonesMeshes::StuffMeshes(class CharBonesMeshes * const this /* r29 */, class list & l /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

static class Symbol _s; // size: 0x4, address: 0x80A50A54
// Range: 0x80321B48 -> 0x80321C20
unsigned char CharBonesMeshes::SyncProperty(class CharBonesMeshes * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
}

// Range: 0x80321C20 -> 0x80321EF0
unsigned char PropSync(class ObjVector & v /* r29 */, class DataNode & n /* r30 */, class DataArray * prop /* r26 */, int i /* r28 */, enum PropOp op /* r27 */) {
    // Local variables
    class ObjOwnerPtr * it; // r31
    class ObjOwnerPtr tmp; // r1+0x20

    // References
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x80
} __vt__15CharBonesMeshes; // size: 0x80, address: 0x808D0AF0
struct {
    // total size: 0x8
} __RTTI__P42ObjOwnerPtr<16RndTransformable,9ObjectDir>; // size: 0x8, address: 0x808D0D80

