/*
    Compile unit: C:\rockband2\system\src\rndobj\MultiMesh.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804D1414 -> 0x804D4710
*/
class DataArray * types; // size: 0x4, address: 0x80A532E8
class Symbol name; // size: 0x4, address: 0x80A532F0
class list sProxyPool; // size: 0x8, address: 0x809803E0
// Range: 0x804D1414 -> 0x804D1490
void RndMultiMesh::Terminate() {
    // Local variables
    struct _List_iterator it; // r1+0x10

    // References
    // -> class list sProxyPool;
}

// Range: 0x804D159C -> 0x804D16B4
void RndMultiMesh::Copy(class RndMultiMesh * const this /* r28 */, const class Object * o /* r29 */, enum CopyType type /* r30 */) {
    // Local variables
    const class RndMultiMesh * f; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndMultiMesh;
}

// Range: 0x804D16B4 -> 0x804D1770
void RndMultiMesh::Print(class RndMultiMesh * const this /* r28 */) {
    // Local variables
    class TextStream & d; // r29

    // References
    // -> class Debug TheDebug;
}

// Range: 0x804D1770 -> 0x804D1878
class TextStream & __ls(class TextStream & d /* r29 */, const class list & c /* r30 */) {
    // Local variables
    int i; // r31
    struct _List_iterator t; // r1+0x30
}

static int MMESH_REV; // size: 0x4, address: 0x80A472F0
// Range: 0x804D1878 -> 0x804D18BC
void RndMultiMesh::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A532F4
// Range: 0x804D18BC -> 0x804D19B4
void RndMultiMesh::Load(class RndMultiMesh * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int MMESH_REV;
    // -> static int gRev;
}

// Range: 0x804D19B4 -> 0x804D1A98
void RndMultiMesh::InvalidateProxies(class RndMultiMesh * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x14

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class list sProxyPool;
    // -> class LoadMgr TheLoadMgr;
}

static int stamp; // size: 0x4, address: 0x80A532F8
// Range: 0x804D1A98 -> 0x804D1E24
void RndMultiMesh::CollideList(class RndMultiMesh * const this /* r28 */, const class Segment & seg /* r29 */, class list & collisions /* r30 */) {
    // Local variables
    struct _List_iterator t; // r1+0x44
    float dist; // r1+0x40
    class Plane plane; // r1+0x50
    class RndMultiMeshProxy * proxy; // r31
    struct _List_iterator it; // r1+0x3C
    struct _List_iterator it; // r1+0x38

    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std37_List_node<Q211RndDrawable9Collision>;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std57_List_node<Q211stlpmtx_std28pair<P17RndMultiMeshProxy,i>>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__17RndMultiMeshProxy;
    // -> class Symbol name;
    // -> class list sProxyPool;
    // -> static int stamp;
    // -> class LoadMgr TheLoadMgr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std57_List_node<Q211stlpmtx_std28pair<P17RndMultiMeshProxy,i>>; // size: 0x8, address: 0x808FC028
// Range: 0x804D1E24 -> 0x804D1EB4
void RndMultiMesh::DrawShowing(class RndMultiMesh * const this /* r31 */) {
    // Local variables
    struct _List_iterator t; // r1+0x14
}

// Range: 0x804D1EB4 -> 0x804D1F80
void RndMultiMesh::Mats(class RndMultiMesh * const this /* r31 */, class list & mats /* r30 */) {
    // Local variables
    struct MatShaderOptions opts; // r1+0xC

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6RndMat>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x804D1F80 -> 0x804D1FFC
void RndMultiMesh::ListDrawChildren() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndDrawable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x804D1FFC -> 0x804D207C
void RndMultiMesh::UpdateSphere(class RndMultiMesh * const this /* r31 */) {
    // Local variables
    class Sphere s; // r1+0x10
}

// Range: 0x804D207C -> 0x804D22C0
unsigned char RndMultiMesh::MakeWorldSphere(class RndMultiMesh * const this /* r29 */, class Sphere & s /* r30 */) {
    // Local variables
    class Sphere s2; // r1+0x50
    class Transform t; // r1+0x70
    struct _List_iterator t; // r1+0x1C
    class Sphere s3; // r1+0x30
}

// Range: 0x804D22C0 -> 0x804D23E4
void * RndMultiMesh::RndMultiMesh(class RndMultiMesh * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__12RndMultiMesh;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x804D23E4 -> 0x804D2458
void RndMultiMesh::SetMesh(class RndMultiMesh * const this /* r30 */, class RndMesh * m /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A53300
static class Symbol _s; // size: 0x4, address: 0x80A53308
static class Symbol _s; // size: 0x4, address: 0x80A53310
static class Symbol _s; // size: 0x4, address: 0x80A53318
static class Symbol _s; // size: 0x4, address: 0x80A53320
static class Symbol _s; // size: 0x4, address: 0x80A53328
static class Symbol _s; // size: 0x4, address: 0x80A53330
static class Symbol _s; // size: 0x4, address: 0x80A53338
static class Symbol _s; // size: 0x4, address: 0x80A53340
static class Symbol _s; // size: 0x4, address: 0x80A53348
static class Symbol _s; // size: 0x4, address: 0x80A53350
static class Symbol _s; // size: 0x4, address: 0x80A53358
// Range: 0x804D2458 -> 0x804D3800
class DataNode RndMultiMesh::Handle(class RndMultiMesh * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x54
    class MessageTimer _mt; // r1+0xC0
    class DataNode r; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode _n; // r1+0x60
    class DataNode _n; // r1+0x58

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x804D3800 -> 0x804D399C
class DataNode RndMultiMesh::OnGetPos(class RndMultiMesh * const this /* r28 */, const class DataArray * a /* r31 */) {
    // Local variables
    const class Vector3 & v; // r0
}

// Range: 0x804D399C -> 0x804D3A88
class DataNode RndMultiMesh::OnSetPos(class RndMultiMesh * const this /* r31 */, const class DataArray * a /* r30 */) {
    // Local variables
    class Vector3 & v; // r0
}

// Range: 0x804D3A88 -> 0x804D3C60
class DataNode RndMultiMesh::OnGetRot(class RndMultiMesh * const this /* r29 */, const class DataArray * a /* r31 */) {
    // Local variables
    class Vector3 e; // r1+0x30
}

// Range: 0x804D3C60 -> 0x804D3D70
class DataNode RndMultiMesh::OnSetRot(class RndMultiMesh * const this /* r31 */, const class DataArray * a /* r30 */) {}

// Range: 0x804D3D70 -> 0x804D3F20
class DataNode RndMultiMesh::OnGetScale(class RndMultiMesh * const this /* r29 */, const class DataArray * a /* r31 */) {
    // Local variables
    class Vector3 e; // r1+0x30
}

// Range: 0x804D3F20 -> 0x804D4218
class DataNode RndMultiMesh::OnSetScale(class RndMultiMesh * const this /* r31 */, const class DataArray * a /* r30 */) {}

// Range: 0x804D4218 -> 0x804D438C
class DataNode RndMultiMesh::OnAddXfm(class RndMultiMesh * const this /* r29 */, const class DataArray * a /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9Transform>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndMultiMesh;
}

// Range: 0x804D438C -> 0x804D4508
class DataNode RndMultiMesh::OnAddXfms(class RndMultiMesh * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class Transform ident; // r1+0x20

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9Transform>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x804D4508 -> 0x804D45B0
class DataNode RndMultiMesh::OnRemoveXfm(class RndMultiMesh * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804D45B0 -> 0x804D4610
class DataNode RndMultiMesh::OnNumXfms() {}

// Range: 0x804D4610 -> 0x804D4634
class DataNode RndMultiMesh::OnMesh() {}

// Range: 0x804D4634 -> 0x804D46B4
unsigned char RndMultiMesh::SyncProperty(class RndMultiMesh * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0x8
} __RTTI__17RndMultiMeshProxy; // size: 0x8, address: 0x808FC1D8
struct {
    // total size: 0xBC
} __vt__12RndMultiMesh; // size: 0xBC, address: 0x808FC230
// Range: 0x804D46B4 -> 0x804D4710
static void __sinit_\MultiMesh_cpp() {
    // References
    // -> class list sProxyPool;
}


