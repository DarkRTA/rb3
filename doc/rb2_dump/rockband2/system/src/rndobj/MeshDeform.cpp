/*
    Compile unit: C:\rockband2\system\src\rndobj\MeshDeform.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804C7074 -> 0x804C9C28
*/
class DataArray * types; // size: 0x4, address: 0x80A53248
class Symbol name; // size: 0x4, address: 0x80A53250
// Range: 0x804C7074 -> 0x804C7124
void BoneDesc::ExportWorldXfm(struct BoneDesc * const this /* r29 */, class Transform & t /* r30 */) {
    // Local variables
    class RndTransformable * exo; // r31
}

// Range: 0x804C7124 -> 0x804C71A4
void * RndMeshDeform::RndMeshDeform(class RndMeshDeform * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__32ObjOwnerPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__13RndMeshDeform;
}

// Range: 0x804C71A4 -> 0x804C731C
void * RndMeshDeform::~RndMeshDeform(class RndMeshDeform * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__32ObjOwnerPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__13RndMeshDeform;
}

// Range: 0x804C731C -> 0x804C764C
void RndMeshDeform::SetNumBones(int bones /* r6 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

// Range: 0x804C764C -> 0x804C76F8
void RndMeshDeform::SetMutable(class RndMeshDeform * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804C76F8 -> 0x804C79F8
void RndMeshDeform::SetMutableAll() {
    // Local variables
    class ObjDirItr d; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndMeshDeform;
}

// Range: 0x804C79F8 -> 0x804C7AA8
void RndMeshDeform::Replace(class RndMeshDeform * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
}

static class RndMeshDeform * last; // size: 0x4, address: 0x80A53254
// Range: 0x804C7AA8 -> 0x804C84E8
void RndMeshDeform::Reskin(class RndMeshDeform * const this /* r28 */, class SyncMeshCB * cb /* r26 */, unsigned char force /* r25 */) {
    // Local variables
    class Transform offsets[64]; // r1+0xD0
    int i; // r26
    class Transform t; // r1+0x90
    int i; // r29
    class Transform trans; // r1+0x50
    float * weights; // r3
    int j; // r4
    class Vector3 a; // r1+0x40
    class Vector3 b; // r1+0x30
    class Vector3 & n; // r0
    class Vector3 tmp; // r1+0x20
    class Vector3 & ndst; // r0

    // References
    // -> static class RndMeshDeform * last;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804C84E8 -> 0x804C8808
void RndMeshDeform::ReskinAll(class SyncMeshCB * cb /* r30 */, unsigned char force /* r31 */) {
    // Local variables
    class ObjDirItr d; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndMeshDeform;
}

// Range: 0x804C8808 -> 0x804C8CF4
void RndMeshDeform::Copy(class RndMeshDeform * const this /* r26 */, const class Object * o /* r25 */) {
    // Local variables
    const class RndMeshDeform * f; // r0
    int size; // r25

    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndMeshDeform;
}

static int MESHDEFORM_REV; // size: 0x4, address: 0x80A53258
// Range: 0x804C8CF4 -> 0x804C8EAC
void __rs(class BinStream & d /* r30 */, struct BoneDesc & b /* r31 */) {}

// Range: 0x804C8EAC -> 0x804C8EF0
void RndMeshDeform::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804C8EF0 -> 0x804C9194
void RndMeshDeform::Print(class RndMeshDeform * const this /* r29 */) {
    // Local variables
    int i; // r30
    int i; // r30
    float * weights; // r26
    int k; // r27

    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A5325C
// Range: 0x804C9194 -> 0x804C9574
void RndMeshDeform::Load(class RndMeshDeform * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int bones; // r1+0x14
    int i; // r31
    float * weights; // r28
    int k; // r27

    // References
    // -> class Debug TheDebug;
    // -> static int MESHDEFORM_REV;
    // -> static int gRev;
}

static class Symbol _s; // size: 0x4, address: 0x80A53264
// Range: 0x804C9574 -> 0x804C9918
class DataNode RndMeshDeform::Handle(class RndMeshDeform * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A5326C
static class Symbol _s; // size: 0x4, address: 0x80A53274
// Range: 0x804C9918 -> 0x804C9ADC
unsigned char RndMeshDeform::SyncProperty(class RndMeshDeform * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x804C9ADC -> 0x804C9C28
unsigned char PropSync(class ObjOwnerPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x54
} __vt__13RndMeshDeform; // size: 0x54, address: 0x808FB3DC
struct {
    // total size: 0x8
} __RTTI__PQ213RndMeshDeform8BoneDesc; // size: 0x8, address: 0x808FB640

