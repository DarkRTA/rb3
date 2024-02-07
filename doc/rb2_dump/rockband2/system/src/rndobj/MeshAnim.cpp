/*
    Compile unit: C:\rockband2\system\src\rndobj\MeshAnim.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804BFDB4 -> 0x804C17C0
*/
class DataArray * types; // size: 0x4, address: 0x80A53238
class Symbol name; // size: 0x4, address: 0x80A53240
class Keys : public vector {
    // total size: 0xC
};
class Keys : public vector {
    // total size: 0xC
};
class Keys : public vector {
    // total size: 0xC
};
class RndMeshAnim : public RndAnimatable {
    // total size: 0x78
protected:
    class ObjPtr mMesh; // offset 0x10, size 0xC
    class Keys mVertPointsKeys; // offset 0x1C, size 0xC
    class Keys mVertTexsKeys; // offset 0x28, size 0xC
    class Keys mVertColorsKeys; // offset 0x34, size 0xC
    class ObjOwnerPtr mKeysOwner; // offset 0x40, size 0xC
};
// Range: 0x804BFDB4 -> 0x804BFEBC
void * RndMeshAnim::RndMeshAnim(class RndMeshAnim * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjOwnerPtr<11RndMeshAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__11RndMeshAnim;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Key * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Key * _M_start; // offset 0x0, size 0x4
    class Key * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Key * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Key * _M_start; // offset 0x0, size 0x4
    class Key * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Key * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Key * _M_start; // offset 0x0, size 0x4
    class Key * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndMeshAnim * mPtr; // offset 0x8, size 0x4
};
// Range: 0x804BFEBC -> 0x804BFFA4
void RndMeshAnim::Replace(class RndMeshAnim * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndMeshAnim;
}

static int MESHANIM_REV; // size: 0x4, address: 0x80A47288
// Range: 0x804BFFA4 -> 0x804BFFE8
void RndMeshAnim::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804BFFE8 -> 0x804C0138
void RndMeshAnim::Load(class RndMeshAnim * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> static int MESHANIM_REV;
}

// Range: 0x804C0138 -> 0x804C02DC
float RndMeshAnim::EndFrame(class RndMeshAnim * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804C02DC -> 0x804C0580
static void InterpVerts(const class vector & a /* r29 */, const class vector & b /* r30 */, float r /* f30 */, class VertVector & c /* r31 */, float blend /* f31 */) {
    // Local variables
    const class Vector2 * pa; // r4
    const class Vector2 * pb; // r5
    const class Vector2 * aEnd; // r6
    class Vert * pc; // r7
    class Vector2 t; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804C0580 -> 0x804C0924
static void InterpVerts(const class vector & a /* r29 */, const class vector & b /* r30 */, float r /* f30 */, class VertVector & c /* r31 */, float blend /* f31 */) {
    // Local variables
    const class Color * pa; // r4
    const class Color * pb; // r5
    const class Color * aEnd; // r6
    class Vert * pc; // r7
    class Color c; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class DebugWarner _dw; // size: 0x100, address: 0x809802D0
// Range: 0x804C0924 -> 0x804C1324
void RndMeshAnim::SetFrame(class RndMeshAnim * const this /* r30 */, float frame /* f30 */, float blend /* f31 */) {
    // Local variables
    int sync; // r31
    const class vector * prev; // r23
    const class vector * next; // r22
    float r; // f29
    const class vector * prev; // r22
    const class vector * next; // r23
    float r; // f29
    const class vector * prev; // r22
    const class vector * next; // r23
    float r; // f29

    // References
    // -> static class DebugWarner _dw;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804C1324 -> 0x804C1328
void RndMeshAnim::SetKey() {}

// Range: 0x804C1328 -> 0x804C1714
class DataNode RndMeshAnim::Handle(class RndMeshAnim * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

// Range: 0x804C1714 -> 0x804C1794
unsigned char RndMeshAnim::SyncProperty(class RndMeshAnim * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xA8
} __vt__11RndMeshAnim; // size: 0xA8, address: 0x808FAD60
struct {
    // total size: 0x8
} __RTTI__11RndMeshAnim; // size: 0x8, address: 0x808FAE30
struct {
    // total size: 0x18
} __vt__37ObjOwnerPtr<11RndMeshAnim,9ObjectDir>; // size: 0x18, address: 0x808FAE38
struct {
    // total size: 0x8
} __RTTI__37ObjOwnerPtr<11RndMeshAnim,9ObjectDir>; // size: 0x8, address: 0x808FAE80
// Range: 0x804C1794 -> 0x804C17C0
void _Vector_base::_M_throw_out_of_range() {}

struct {
    // total size: 0x8
} __RTTI__P78Key<Q211stlpmtx_std56vector<7Vector3,Q211stlpmtx_std22StlNodeAlloc<7Vector3>>>; // size: 0x8, address: 0x808FB070
struct {
    // total size: 0x8
} __RTTI__P78Key<Q211stlpmtx_std56vector<7Vector2,Q211stlpmtx_std22StlNodeAlloc<7Vector2>>>; // size: 0x8, address: 0x808FB0C0
struct {
    // total size: 0x8
} __RTTI__P86Key<Q211stlpmtx_std64vector<Q23Hmx5Color,Q211stlpmtx_std26StlNodeAlloc<Q23Hmx5Color>>>; // size: 0x8, address: 0x808FB118
class Key {
    // total size: 0x10
public:
    class vector value; // offset 0x0, size 0xC
    float frame; // offset 0xC, size 0x4
};
class Key {
    // total size: 0x10
public:
    class vector value; // offset 0x0, size 0xC
    float frame; // offset 0xC, size 0x4
};
class Key {
    // total size: 0x10
public:
    class vector value; // offset 0x0, size 0xC
    float frame; // offset 0xC, size 0x4
};

