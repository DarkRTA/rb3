/*
    Compile unit: C:\rockband2\system\src\bandobj\BandMeshLauncher.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80254DD0 -> 0x80257BA4
*/
class DataArray * types; // size: 0x4, address: 0x80A4F018
// Range: 0x80254DD0 -> 0x80254E70
void * MeshInstance::MeshInstance(struct MeshInstance * const this /* r29 */, class Object * owner /* r30 */, class RndTransformable * _parentTrans /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12RndTransAnim,9ObjectDir>;
}

// Range: 0x80254E70 -> 0x80254F34
class Transform MeshInstance::Xfm(class Transform * t /* r30 */, const struct MeshInstance * const this /* r31 */) {}

// Range: 0x80254F34 -> 0x802550C4
void * BandMeshLauncher::BandMeshLauncher(class BandMeshLauncher * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__35ObjPtr<14RndParticleSys,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12RndMultiMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__16BandMeshLauncher;
    // -> struct [anonymous] __vt__11RndPollable;
}

class _List_node : public _List_node_base {
    // total size: 0x24
public:
    struct MeshInstance _M_data; // offset 0x8, size 0x1C
};
// Range: 0x80255138 -> 0x80255184
void BandMeshLauncher::Poll(class BandMeshLauncher * const this /* r31 */) {
    // Local variables
    float dt; // f1

    // References
    // -> class TaskMgr TheTaskMgr;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80255184 -> 0x802552CC
void BandMeshLauncher::UpdateFrames(class BandMeshLauncher * const this /* r29 */, float dt /* f31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x1C

    // References
    // -> struct [anonymous] __vt__33ObjPtr<12RndTransAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x802552CC -> 0x80255414
void BandMeshLauncher::ConstructTransforms(class BandMeshLauncher * const this /* r30 */) {
    // Local variables
    class list & transList; // r0
    struct _List_iterator it; // r1+0x24

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9Transform>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80255414 -> 0x80255580
void BandMeshLauncher::Launch(class BandMeshLauncher * const this /* r31 */, class RndTransAnim * path /* r0 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12RndTransAnim,9ObjectDir>;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std46_List_node<Q216BandMeshLauncher12MeshInstance>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std46_List_node<Q216BandMeshLauncher12MeshInstance>; // size: 0x8, address: 0x808B48A8
// Range: 0x80255580 -> 0x80255918
void BandMeshLauncher::LaunchParticles(class BandMeshLauncher * const this /* r31 */) {
    // Local variables
    class Vector3 posLow; // r1+0x40
    class Vector3 posHigh; // r1+0x30
    class Vector3 partPos; // r1+0x20
    class Vector3 offSet; // r1+0x10
    float val; // f0
}

static int MESHLAUNCHER_REV; // size: 0x4, address: 0x80A46AA0
// Range: 0x80255918 -> 0x8025595C
void BandMeshLauncher::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8025595C -> 0x80255CCC
void BandMeshLauncher::Load(class BandMeshLauncher * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x14

    // References
    // -> class Debug TheDebug;
    // -> static int MESHLAUNCHER_REV;
}

// Range: 0x80255CCC -> 0x80255EFC
void BandMeshLauncher::Copy(class BandMeshLauncher * const this /* r31 */, const class Object * o /* r30 */, enum CopyType type /* r29 */) {
    // Local variables
    const class BandMeshLauncher * m; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16BandMeshLauncher;
}

// Range: 0x80255EFC -> 0x80255FD4
class DataNode BandMeshLauncher::OnLaunch(class BandMeshLauncher * const this /* r29 */, const class DataArray * a /* r30 */) {
    // Local variables
    class RndTransformable * parentTrans; // r31

    // References
    // -> struct [anonymous] __RTTI__12RndTransAnim;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F020
static class Symbol _s; // size: 0x4, address: 0x80A4F028
// Range: 0x80255FD4 -> 0x802565F4
class DataNode BandMeshLauncher::Handle(class BandMeshLauncher * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F030
static class Symbol _s; // size: 0x4, address: 0x80A4F038
static class Symbol _s; // size: 0x4, address: 0x80A4F040
static class Symbol _s; // size: 0x4, address: 0x80A4F048
static class Symbol _s; // size: 0x4, address: 0x80A4F050
static class Symbol _s; // size: 0x4, address: 0x80A4F058
static class Symbol _s; // size: 0x4, address: 0x80A4F060
static class Symbol _s; // size: 0x4, address: 0x80A4F068
static class Symbol _s; // size: 0x4, address: 0x80A4F070
static class Symbol _s; // size: 0x4, address: 0x80A4F078
static class Symbol _s; // size: 0x4, address: 0x80A4F080
static class Symbol _s; // size: 0x4, address: 0x80A4F088
static class Symbol _s; // size: 0x4, address: 0x80A4F090
static class Symbol _s; // size: 0x4, address: 0x80A4F098
static class Symbol _s; // size: 0x4, address: 0x80A4F0A0
static class Symbol _s; // size: 0x4, address: 0x80A4F0A8
static class Symbol _s; // size: 0x4, address: 0x80A4F0B0
static class Symbol _s; // size: 0x4, address: 0x80A4F0B8
static class Symbol _s; // size: 0x4, address: 0x80A4F0C0
static class Symbol _s; // size: 0x4, address: 0x80A4F0C8
static class Symbol _s; // size: 0x4, address: 0x80A4F0D0
static class Symbol _s; // size: 0x4, address: 0x80A4F0D8
static class Symbol _s; // size: 0x4, address: 0x80A4F0E0
static class Symbol _s; // size: 0x4, address: 0x80A4F0E8
static class Symbol _s; // size: 0x4, address: 0x80A4F0F0
static class Symbol _s; // size: 0x4, address: 0x80A4F0F8
// Range: 0x802565F4 -> 0x80257BA4
unsigned char BandMeshLauncher::SyncProperty(class BandMeshLauncher * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
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
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x8C
} __vt__16BandMeshLauncher; // size: 0x8C, address: 0x808B4A9C
struct {
    // total size: 0x8
} __RTTI__16BandMeshLauncher; // size: 0x8, address: 0x808B4B58
struct {
    // total size: 0x18
} __vt__35ObjPtr<14RndParticleSys,9ObjectDir>; // size: 0x18, address: 0x808B4B60
struct {
    // total size: 0x8
} __RTTI__35ObjPtr<14RndParticleSys,9ObjectDir>; // size: 0x8, address: 0x808B4BA8
struct {
    // total size: 0x18
} __vt__33ObjPtr<12RndMultiMesh,9ObjectDir>; // size: 0x18, address: 0x808B4BB0
struct {
    // total size: 0x8
} __RTTI__33ObjPtr<12RndMultiMesh,9ObjectDir>; // size: 0x8, address: 0x808B4BF8
struct {
    // total size: 0x18
} __vt__33ObjPtr<12RndTransAnim,9ObjectDir>; // size: 0x18, address: 0x808B4C00
struct {
    // total size: 0x8
} __RTTI__33ObjPtr<12RndTransAnim,9ObjectDir>; // size: 0x8, address: 0x808B4C48

