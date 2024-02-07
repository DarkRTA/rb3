/*
    Compile unit: C:\rockband2\system\src\rndobj\Mesh.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804B6AE8 -> 0x804BC56C
*/
class DataArray * types; // size: 0x4, address: 0x80A531B8
class list : public _List_base {
    // total size: 0x8
};
class list sStriperResults; // size: 0x8, address: 0x809802B0
class vector : protected _Vector_base {
    // total size: 0xC
};
static class vector gPatchVerts; // size: 0xC, address: 0x809802C4
static int gRev; // size: 0x4, address: 0x80A531C0
// Range: 0x804B6AE8 -> 0x804B6B18
int RndMesh::MaxBones() {}

// Range: 0x804B6B18 -> 0x804B70C0
class RndDrawable * RndMesh::CollideShowing(class RndMesh * const this /* r27 */, const class Segment & s /* r24 */, float & dist /* r28 */, class Plane & plane /* r29 */) {
    // Local variables
    class Segment s2; // r1+0x30
    class Transform t; // r1+0x90
    unsigned char hit; // r31
    class Face * f; // r30
    class Triangle t; // r1+0x50
    float d; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804B70C0 -> 0x804B72BC
int RndMesh::CollidePlane(class RndMesh * const this /* r26 */, const class Face & f /* r27 */, const class Plane & pl /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804B72BC -> 0x804B7528
int RndMesh::CollidePlane(class RndMesh * const this /* r29 */, const class Plane & plane /* r30 */) {
    // Local variables
    int collide; // r0
    class Plane pl; // r1+0x20
    class Transform t; // r1+0x30
    class Face * f; // r31
    int inside; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804B7528 -> 0x804B7680
void RndMesh::UpdateSphere(class RndMesh * const this /* r30 */) {
    // Local variables
    class Sphere s; // r1+0x20
    class Transform t; // r1+0x40
}

// Range: 0x804B7680 -> 0x804B7970
unsigned char RndMesh::MakeWorldSphere(class RndMesh * const this /* r29 */, class Sphere & s /* r30 */) {
    // Local variables
    class Box b; // r1+0x50
    const class Transform & w; // r0
    class Vert * v; // r31
    class Vector3 p; // r1+0x40
    class Vector3 v2; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class Polygon {
    // total size: 0xC
public:
    class vector points; // offset 0x0, size 0xC
};
class BSPFace {
    // total size: 0x60
public:
    class Polygon p; // offset 0x0, size 0xC
    class Transform t; // offset 0x10, size 0x40
    float area; // offset 0x50, size 0x4
    class list planes; // offset 0x54, size 0x8
};
// Range: 0x804B7970 -> 0x804B874C
void RndMesh::SetVolume(class RndMesh * const this /* r28 */, enum Volume c /* r25 */) {
    // Local variables
    class Box b; // r1+0xD0
    class Vert * v; // r25
    class BSPNode * n; // r25
    int i; // r26
    class Vector3 v; // r1+0xA0
    class list faces; // r1+0x90
    int i; // r29
    class BSPFace t; // r1+0xF0
    class Box b; // r1+0xB0
    class Vert * v; // r25
    int num; // r1+0x5C
    int maxDepth; // r1+0x58

    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std18_List_node<5Plane>;
    // -> struct [anonymous] __RTTI__P7Vector2;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<7BSPFace>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _List_node : public _List_node_base {
    // total size: 0x70
public:
    class BSPFace _M_data; // offset 0x10, size 0x60
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Vector2 * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Vector2 * _M_start; // offset 0x0, size 0x4
    class Vector2 * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_node : public _List_node_base {
    // total size: 0x20
public:
    class Plane _M_data; // offset 0x10, size 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
struct {
    // total size: 0x8
} __RTTI__P7Vector2; // size: 0x8, address: 0x808FA360
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std18_List_node<5Plane>; // size: 0x8, address: 0x808FA390
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std20_List_node<7BSPFace>; // size: 0x8, address: 0x808FA3C0
// Range: 0x804B874C -> 0x804B87B4
void RndMesh::SetMat(class RndMesh * const this /* r30 */, class RndMat * m /* r31 */) {}

// Range: 0x804B87B4 -> 0x804B8904
void RndMesh::SetBone(class RndMesh * const this /* r27 */, class RndTransformable * bone /* r28 */, unsigned char calcOffset /* r29 */) {
    // Local variables
    class Transform t; // r1+0x20
}

// Range: 0x804B8904 -> 0x804B8AC0
void * RndMesh::RndMesh(class RndMesh * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__32ObjOwnerPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__7RndMesh;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x804B8AC0 -> 0x804B8FE8
void * RndMesh::~RndMesh(class RndMesh * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjOwnerPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__7RndMesh;
}

// Range: 0x804B8FE8 -> 0x804B9174
void VertVector::resize(class VertVector * const this /* r27 */, int n /* r1+0x8 */) {
    // Local variables
    class Vert * old; // r31
    class Vert * in; // r30
    class Vert * end; // r29
    class Vert * out; // r3
}

// Range: 0x804B9174 -> 0x804B92BC
void VertVector::__as(class VertVector * const this /* r29 */, const class VertVector & c /* r30 */) {
    // Local variables
    class Vert * in; // r4
    class Vert * out; // r5
    class Vert * end; // r6
}

// Range: 0x804B92BC -> 0x804B9344
class BinStream & __rs(class BinStream & d /* r29 */, class VertVector & c /* r30 */) {
    // Local variables
    unsigned int s; // r1+0x8
    class Vert * t; // r31
}

// Range: 0x804B9344 -> 0x804B939C
unsigned char RndMesh::CacheStrips() {
    // References
    // -> class LoadMgr TheLoadMgr;
}

static int MESH_REV; // size: 0x4, address: 0x80A47274
// Range: 0x804B939C -> 0x804B93E0
void RndMesh::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804B93E0 -> 0x804B9BE4
void RndMesh::Load(class RndMesh * const this /* r25 */, class BinStream & d /* r26 */) {
    // Local variables
    unsigned char * p; // r24
    struct STRIPERRESULT s; // r1+0x30

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std27_List_node<13STRIPERRESULT>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * kAssertStr;
    // -> class list sStriperResults;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> static int MESH_REV;
    // -> static int gRev;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std27_List_node<13STRIPERRESULT>; // size: 0x8, address: 0x808FA4C0
// Range: 0x804B9BE4 -> 0x804B9C80
void RndMesh::SetZeroWeightBones() {
    // Local variables
    int i; // r5
}

// Range: 0x804B9C80 -> 0x804B9EB4
class BinStream & __rs(class BinStream & d /* r30 */, class Vert & c /* r31 */) {
    // Local variables
    float w1; // r1+0x14
    float w2; // r1+0x10
    class Vector2 t2; // r1+0x18
    class Vector4 tng; // r1+0x20

    // References
    // -> static int gRev;
}

// Range: 0x804B9EB4 -> 0x804BA3D4
void RndMesh::Copy(class RndMesh * const this /* r26 */, const class Object * o /* r25 */, enum CopyType type /* r27 */) {
    // Local variables
    const class RndMesh * m; // r0

    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
}

// Range: 0x804BA3D4 -> 0x804BA4E8
void RndMesh::Replace(class RndMesh * const this /* r29 */, class Object * from /* r30 */, class Object * to /* r31 */) {
    // Local variables
    class RndMesh * toMesh; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
}

// Range: 0x804BA4E8 -> 0x804BA594
class BinStream & __rs(class BinStream & d /* r30 */, class Face & c /* r31 */) {
    // Local variables
    class Vector3 n; // r1+0x10

    // References
    // -> static int gRev;
}

// Range: 0x804BA594 -> 0x804BA5E8
static int FindPatchVert() {
    // Local variables
    int i; // r4

    // References
    // -> static class vector gPatchVerts;
}

// Range: 0x804BA5E8 -> 0x804BA6E8
static void FaceCenter(class RndMesh * mesh /* r27 */, class Face * face /* r28 */, class Vector3 & center /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804BA6E8 -> 0x804BA74C
unsigned char RndMesh::PatchOkay() {}

// Range: 0x804BA74C -> 0x804BA804
void RndMesh::Mats(class RndMesh * const this /* r31 */, class list & mats /* r30 */) {
    // Local variables
    struct MatShaderOptions opts; // r1+0xC

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6RndMat>;
    // -> unsigned char gStlAllocNameLookup;
}

static class Symbol _s; // size: 0x4, address: 0x80A531C8
static class Symbol _s; // size: 0x4, address: 0x80A531D0
static class Symbol _s; // size: 0x4, address: 0x80A531D8
static class Symbol _s; // size: 0x4, address: 0x80A531E0
static class Symbol _s; // size: 0x4, address: 0x80A531E8
static class Symbol _s; // size: 0x4, address: 0x80A531F0
static class Symbol _s; // size: 0x4, address: 0x80A531F8
static class Symbol _s; // size: 0x4, address: 0x80A53200
static class Symbol _s; // size: 0x4, address: 0x80A53208
static class Symbol _s; // size: 0x4, address: 0x80A53210
static class Symbol _s; // size: 0x4, address: 0x80A53218
static class Symbol _s; // size: 0x4, address: 0x80A53220
static class Symbol _s; // size: 0x4, address: 0x80A53228
static class Symbol _s; // size: 0x4, address: 0x80A53230
// Range: 0x804BA804 -> 0x804BB16C
class DataNode RndMesh::Handle(class RndMesh * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x14
    class MessageTimer _mt; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode _n; // r1+0x28
    class DataNode _n; // r1+0x20
    class DataNode _n; // r1+0x18

    // References
    // -> class DebugNotifier TheDebugNotifier;
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
}

// Range: 0x804BB16C -> 0x804BB350
class DataNode RndMesh::OnPointCollide(class RndMesh * const this /* r29 */, const class DataArray * a /* r31 */) {
    // Local variables
    class Vector3 v; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804BB350 -> 0x804BBEB4
class DataNode RndMesh::OnCompareEdgeVerts(class RndMesh * const this /* r26 */, const class DataArray * a /* r27 */) {
    // Local variables
    class vector sharedVerts; // r1+0xFC
    class list edgeVerts; // r1+0xE8
    class vector connectVerts; // r1+0xF0
    int i; // r29
    int j; // r30
    class Face * f; // r29
    int v1; // r30
    int v2; // r31
    int v3; // r28
    struct _List_iterator j; // r1+0xA8
    int matches; // r9
    struct _List_iterator k; // r1+0xA4
    struct _List_iterator l; // r1+0xA0
    struct _List_iterator j; // r1+0x9C

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std40list<i,Q211stlpmtx_std15StlNodeAlloc<i>>;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__Pi;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804BBEB4 -> 0x804BBEC8
class DataNode RndMesh::OnNumVerts() {}

// Range: 0x804BBEF0 -> 0x804BBF20
class DataNode RndMesh::OnNumFaces() {}

// Range: 0x804BBF20 -> 0x804BBFA0
class DataNode RndMesh::OnVolume(class RndMesh * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804BBFA0 -> 0x804BC00C
class DataNode RndMesh::OnSetVolume(class RndMesh * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804BC00C -> 0x804BC020
class DataNode RndMesh::OnMat() {}

// Range: 0x804BC020 -> 0x804BC0A8
class DataNode RndMesh::OnSetMat(class RndMesh * const this /* r30 */, const class DataArray * a /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

// Range: 0x804BC0A8 -> 0x804BC238
class DataNode RndMesh::OnResizeFaces(class RndMesh * const this /* r31 */, const class DataArray * a /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804BC238 -> 0x804BC2DC
class DataNode RndMesh::OnSetMutable(class RndMesh * const this /* r30 */, const class DataArray * a /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804BC2DC -> 0x804BC438
class DataNode RndMesh::OnUnitizeNormals(class RndMesh * const this /* r30 */) {
    // Local variables
    class Vert * v; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804BC438 -> 0x804BC4E0
unsigned char RndMesh::SyncProperty(class RndMesh * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xFC
} __vt__7RndMesh; // size: 0xFC, address: 0x808FA6C0
struct {
    // total size: 0x18
} __vt__32ObjOwnerPtr<7RndMesh,9ObjectDir>; // size: 0x18, address: 0x808FA800
struct {
    // total size: 0x8
} __RTTI__32ObjOwnerPtr<7RndMesh,9ObjectDir>; // size: 0x8, address: 0x808FA848
struct {
    // total size: 0x8
} __RTTI__PUs; // size: 0x8, address: 0x808FAA70
struct {
    // total size: 0x8
} __RTTI__P7RndBone; // size: 0x8, address: 0x808FAAB8
// Range: 0x804BC4E0 -> 0x804BC56C
static void __sinit_\Mesh_cpp() {
    // References
    // -> static class vector gPatchVerts;
    // -> class list sStriperResults;
}

class _List_node : public _List_node_base {
    // total size: 0x18
public:
    struct STRIPERRESULT _M_data; // offset 0x8, size 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    unsigned short * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    unsigned short * _M_start; // offset 0x0, size 0x4
    unsigned short * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};

