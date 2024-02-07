/*
    Compile unit: C:\rockband2\system\src\char\Character.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8030C55C -> 0x8031227C
*/
class DataArray * types; // size: 0x4, address: 0x80A508F0
class DataArray * types; // size: 0x4, address: 0x80A508F8
class Symbol name; // size: 0x4, address: 0x80A50900
// Range: 0x8030C55C -> 0x8030C690
class DataNode OnCharSyncEnd(class DataArray * msg /* r30 */) {
    // Local variables
    float length; // f31
    int i; // r31
    float l; // f0
    int i; // r31
    float frame; // f0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9Character;
}

// Range: 0x8030C690 -> 0x8030C6E8
class BinStream & __ls(class BinStream & d /* r30 */, const class Lod & l /* r31 */) {}

static class Character * gMe; // size: 0x4, address: 0x80A50904
static int gRev; // size: 0x4, address: 0x80A50908
struct Node {
    // total size: 0xC
    class RndDrawable * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
// Range: 0x8030C6E8 -> 0x8030CA40
class BinStream & __rs(class BinStream & d /* r30 */, class Lod & l /* r31 */) {
    // Local variables
    class ObjPtrList draws; // r1+0x20
    class iterator it; // r1+0x1C

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> static class Character * gMe;
    // -> static int gRev;
}

// Range: 0x8030CA40 -> 0x8030CA6C
void * Lod::Lod() {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
}

// Range: 0x8030CA6C -> 0x8030CAD4
void * Lod::Lod(class Lod * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
}

// Range: 0x8030CAD4 -> 0x8030CB4C
class Lod & Lod::__as(class Lod * const this /* r30 */) {}

// Range: 0x8030CB4C -> 0x8030CB64
void Lod::Sync() {}

struct BoneXfm {
    // total size: 0x50
    class ObjPtr bone; // offset 0x0, size 0xC
    class Transform xfm; // offset 0x10, size 0x40
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct BoneXfm * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct BoneXfm * _M_start; // offset 0x0, size 0x4
    struct BoneXfm * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharClipGroup * mPtr; // offset 0x8, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class CharacterTest : public Callback {
    // total size: 0xD8
protected:
    class Character * mMe; // offset 0x4, size 0x4
    class ObjVector mLoadPose; // offset 0x8, size 0x10
    class ObjPtr mDriver; // offset 0x18, size 0xC
    class ObjPtr mClip1; // offset 0x24, size 0xC
    class ObjPtr mClip2; // offset 0x30, size 0xC
    class ObjPtr mFilterGroup; // offset 0x3C, size 0xC
    class ObjPtr mTeleportTo; // offset 0x48, size 0xC
    class ObjPtrList mWalkPath; // offset 0x54, size 0x14
    int mLod; // offset 0x68, size 0x4
    class Symbol mShowDistMap; // offset 0x6C, size 0x4
    int mTransition; // offset 0x70, size 0x4
    unsigned char mCycleTransition; // offset 0x74, size 0x1
    unsigned char mMetronome; // offset 0x75, size 0x1
    unsigned char mZeroTravel; // offset 0x76, size 0x1
    unsigned char mShowScreenSize; // offset 0x77, size 0x1
    class Symbol mFootSteps; // offset 0x78, size 0x4
    unsigned char mFootExtents; // offset 0x7C, size 0x1
    unsigned char mClip2RealTime; // offset 0x7D, size 0x1
    int mBpm; // offset 0x80, size 0x4
    int mInternalTransition; // offset 0x84, size 0x4
    class ClipDistMap * mDistMap; // offset 0x88, size 0x4
    class Symbol mCycleCategory; // offset 0x8C, size 0x4
    float mCycleWait; // offset 0x90, size 0x4
    class Timer mCycleTimer; // offset 0x98, size 0x38
    class RndOverlay * mOverlay; // offset 0xD0, size 0x4
};
// Range: 0x8030CB64 -> 0x8030CBD8
void Character::Init() {
    // References
    // -> class Symbol name;
}

// Range: 0x8030CBD8 -> 0x8030CBDC
void Character::Terminate() {}

// Range: 0x8030CBDC -> 0x8030CDD8
void * Character::Character(class Character * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__9Character;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

class ShadowBone : public RndTransformable {
    // total size: 0x100
protected:
    class ObjPtr mParent; // offset 0xB8, size 0xC
};
// Range: 0x8030CDD8 -> 0x8030D30C
void * Character::~Character(class Character * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndPollable,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__9Character;
}

// Range: 0x8030D30C -> 0x8030D354
void Character::Enter(class Character * const this /* r31 */) {}

// Range: 0x8030D354 -> 0x8030D360
void Character::Exit() {}

static class Timer * _t; // size: 0x4, address: 0x80A5090C
// Range: 0x8030D360 -> 0x8030D434
void Character::Poll(class Character * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> static class Timer * _t;
}

// Range: 0x8030D434 -> 0x8030D4D4
void Character::DrawLod(class Character * const this /* r31 */) {
    // References
    // -> class Rnd & TheRnd;
}

static class Timer * _t; // size: 0x4, address: 0x80A50914
// Range: 0x8030D4D4 -> 0x8030D65C
void Character::DrawShowing(class Character * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0x10
    float screenSize; // f0
    int lod; // r4
    float scale; // f2

    // References
    // -> class RndCam * sCurrent;
    // -> static class Timer * _t;
}

// Range: 0x8030D65C -> 0x8030D7E0
void Character::UpdateSphere(class Character * const this /* r30 */) {
    // Local variables
    class Sphere s; // r1+0x20
    class Transform t; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static char * boneNames[5]; // size: 0x14, address: 0x808CEAA8
// Range: 0x8030D7E0 -> 0x8030DAE0
void Character::CalcBoundingSphere(class Character * const this /* r28 */) {
    // Local variables
    int i; // r29
    class RndTransformable * clav; // r29
    class RndTransformable * hand; // r30
    class Vector3 v; // r1+0x20
    float length; // f0
    class Vector3 v; // r1+0x10
    float length; // f0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> static char * boneNames[5];
}

// Range: 0x8030DAE0 -> 0x8030DC10
unsigned char Character::MakeWorldSphere(class Character * const this /* r29 */, class Sphere & s /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8030DC10 -> 0x8030DD9C
void Character::SetSphereBase(class Character * const this /* r30 */, class RndTransformable * t /* r31 */) {
    // Local variables
    class Sphere s; // r1+0x10
}

// Range: 0x8030DD9C -> 0x8030DDA4
void Character::SetMinLod() {}

// Range: 0x8030DDA4 -> 0x8030DEE0
void Character::SetShadow(class Character * const this /* r30 */, class RndGroup * shadow /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8030DEE0 -> 0x8030E15C
void Character::DrawShadow(class Character * const this /* r31 */, const class Transform & light /* r29 */, const class Plane & shadowPlane /* r28 */) {
    // Local variables
    class Transform invLight; // r1+0xB0
    class Plane p; // r1+0x20
    class Transform planeLight; // r1+0x70
    class Transform worldToShadow; // r1+0x30
    int i; // r29
    class ShadowBone * s; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8030E15C -> 0x8030E190
class CharServoBone * Character::BoneServo() {
    // References
    // -> struct [anonymous] __RTTI__15CharBonesObject;
    // -> struct [anonymous] __RTTI__13CharServoBone;
}

// Range: 0x8030E190 -> 0x8030E4A0
void Character::Teleport(class Character * const this /* r30 */, class Waypoint * w /* r31 */) {
    // Local variables
    class Transform t; // r1+0x10
}

// Range: 0x8030E4A0 -> 0x8030E5F4
float Character::ComputeScreenSize(class RndCam * cam /* r31 */) {
    // Local variables
    class Sphere s; // r1+0x10
}

// Range: 0x8030E5F4 -> 0x8030E634
class RndGroup * Character::CurGroup() {}

// Range: 0x8030E634 -> 0x8030E698
void Character::SetLod(class Character * const this /* r30 */, int lod /* r31 */) {
    // Local variables
    class RndGroup * old; // r0
    class RndGroup * c; // r0
}

// Range: 0x8030E698 -> 0x8030E714
void Character::SyncLods(class Character * const this /* r30 */) {
    // Local variables
    int j; // r31
    class RndGroup * c; // r0
}

// Range: 0x8030E714 -> 0x8030E954
class ShadowBone * Character::AddShadowBone(class Character * const this /* r29 */, class RndTransformable * b /* r30 */) {
    // Local variables
    int i; // r6

    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__10ShadowBone;
    // -> struct [anonymous] __vt__16RndHighlightable;
    // -> class Symbol name;
}

// Range: 0x8030E954 -> 0x8030EA9C
void Character::UnhookShadow(class Character * const this /* r31 */) {
    // Local variables
    int i; // r29
    class ShadowBone * s; // r30
    class ObjRef * r; // r3
}

// Range: 0x8030EB7C -> 0x8030EC9C
void Character::Replace(class Character * const this /* r29 */, class Object * from /* r30 */, class Object * to /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x8030EC9C -> 0x8030EDE8
void Character::SyncShadow(class Character * const this /* r28 */) {
    // Local variables
    const class vector & draws; // r0
    class RndDrawable * const * it; // r30
    class RndMesh * m; // r29
    int b; // r27

    // References
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> struct [anonymous] __RTTI__7RndMesh;
}

// Range: 0x8030EDE8 -> 0x8030EE9C
unsigned char Character::ShouldStrip() {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
// Range: 0x8030EE9C -> 0x8030F7CC
void Character::ConvertBonesToTranses(class Character * const this /* r31 */) {
    // Local variables
    class list meshes; // r1+0x50
    class ObjDirItr mesh; // r1+0x6C
    class ObjDirItr trans; // r1+0x58

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> class Symbol name;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std21_List_node<P7RndMesh>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class RndMesh * _M_data; // offset 0x8, size 0x4
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
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std21_List_node<P7RndMesh>; // size: 0x8, address: 0x808CEB88
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std39_List_node<PQ218CharPollableSorter3Dep>; // size: 0x8, address: 0x808CEBC8
int sSearchID; // size: 0x4, address: 0x80A5091C
class CharPollableSorter {
    // total size: 0x1C
protected:
    class map mDeps; // offset 0x0, size 0x18
    struct Dep * mTarget; // offset 0x18, size 0x4
};
// Range: 0x8030F7CC -> 0x8030FD5C
void Character::SyncObjects(class Character * const this /* r31 */) {
    // Local variables
    class CharPollableSorter sorter; // r1+0xF8

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__11RndPollable;
    // -> struct [anonymous] __RTTI__12CharPollable;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
}

struct Dep {
    // total size: 0x14
    class Object * obj; // offset 0x0, size 0x4
    class list changedBy; // offset 0x4, size 0x8
    class RndPollable * poll; // offset 0xC, size 0x4
    int searchID; // offset 0x10, size 0x4
};
struct pair {
    // total size: 0x18
    class Object * const first; // offset 0x0, size 0x4
    struct Dep second; // offset 0x4, size 0x14
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Dep * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Dep * * _M_start; // offset 0x0, size 0x4
    struct Dep * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    struct Dep * _M_data; // offset 0x8, size 0x4
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
class list : public _List_base {
    // total size: 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8030FD5C -> 0x8031009C
void CharPollableSorter::AddDeps(class CharPollableSorter * const this /* r26 */, struct Dep * me /* r27 */, const class list & odeps /* r28 */, class list & toDo /* r29 */, unsigned char changedBy /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x60
    class Object * b; // r31

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std39_List_node<PQ218CharPollableSorter3Dep>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8031009C -> 0x803102A8
unsigned char CharPollableSorter::ChangedBy(class CharPollableSorter * const this /* r29 */, struct Dep * b /* r30 */) {
    // References
    // -> int sSearchID;
}

// Range: 0x803102A8 -> 0x80310498
unsigned char CharPollableSorter::ChangedByRecurse(class CharPollableSorter * const this /* r29 */, struct Dep * a /* r30 */) {
    // Local variables
    struct _List_iterator j; // r1+0x28

    // References
    // -> int sSearchID;
}

struct AlphaSort {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x80310498 -> 0x80310578
void Character::AddedObject(class Character * const this /* r28 */, class Object * obj /* r29 */) {
    // Local variables
    class CharPollable * p; // r0
    class CharDriver * d; // r0
    class CharWalk * w; // r0

    // References
    // -> struct [anonymous] __RTTI__8CharWalk;
    // -> struct [anonymous] __RTTI__10CharDriver;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12CharPollable;
}

// Range: 0x80310578 -> 0x803105C0
void Character::RemovingObject() {}

// Range: 0x803105C0 -> 0x803108DC
void Character::PreSave(class Character * const this /* r31 */) {
    // Local variables
    class ObjDirItr it; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitLoader;
}

class list : public _List_base {
    // total size: 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x803108DC -> 0x80310CA4
void Character::PostSave() {
    // Local variables
    class list loaders; // r1+0x38
    class ObjDirItr l; // r1+0x40
    struct _List_iterator l; // r1+0x24

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std27_List_node<P12OutfitLoader>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitLoader;
    // -> class LoadMgr TheLoadMgr;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class OutfitLoader * _M_data; // offset 0x8, size 0x4
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
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std27_List_node<P12OutfitLoader>; // size: 0x8, address: 0x808CEC58
// Range: 0x80310CA4 -> 0x80310E58
void Character::Save(class Character * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    class ObjPtr p; // r1+0x20

    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjVector * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjVector * _M_start; // offset 0x0, size 0x4
    class ObjVector * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x80310E58 -> 0x803110B8
void Character::Copy(class Character * const this /* r30 */, const class Object * o /* r27 */, enum CopyType type /* r26 */) {
    // Local variables
    const class Character * c; // r0

    // References
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9Character;
}

static class Symbol _s; // size: 0x4, address: 0x80A50924
static class Symbol _s; // size: 0x4, address: 0x80A5092C
static class Symbol _s; // size: 0x4, address: 0x80A50934
static class Symbol _s; // size: 0x4, address: 0x80A5093C
static class Symbol _s; // size: 0x4, address: 0x80A50944
// Range: 0x803110B8 -> 0x80311894
class DataNode Character::Handle(class Character * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Waypoint;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80311894 -> 0x80311998
class DataNode Character::OnPlayClip(class Character * const this /* r29 */, class DataArray * msg /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A5094C
static class Symbol _s; // size: 0x4, address: 0x80A50954
// Range: 0x80311998 -> 0x80311B50
unsigned char PropSync(class Lod & _me /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A5095C
static class Symbol _s; // size: 0x4, address: 0x80A50964
static class Symbol _s; // size: 0x4, address: 0x80A5096C
static class Symbol _s; // size: 0x4, address: 0x80A50974
static class Symbol _s; // size: 0x4, address: 0x80A5097C
static class Symbol _s; // size: 0x4, address: 0x80A50984
// Range: 0x80311B50 -> 0x80312010
unsigned char Character::SyncProperty(class Character * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> static class Symbol _s;
}

// Range: 0x80312010 -> 0x8031227C
unsigned char PropSync(class ObjVector & v /* r31 */, class DataNode & n /* r26 */, class DataArray * prop /* r27 */, int i /* r30 */, enum PropOp op /* r29 */) {
    // Local variables
    class Lod * it; // r28
    class Lod tmp; // r1+0x20

    // References
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x9C
} __vt__10ShadowBone; // size: 0x9C, address: 0x808CEDA0
struct {
    // total size: 0x8
} __RTTI__10ShadowBone; // size: 0x8, address: 0x808CEE70
struct {
    // total size: 0x18
} __vt__36ObjPtrList<11RndDrawable,9ObjectDir>; // size: 0x18, address: 0x808CEE78
struct {
    // total size: 0x8
} __RTTI__36ObjPtrList<11RndDrawable,9ObjectDir>; // size: 0x8, address: 0x808CEEC0
struct {
    // total size: 0x8
} __RTTI__13CharServoBone; // size: 0x8, address: 0x808CEFB8
struct {
    // total size: 0x8
} __RTTI__8CharWalk; // size: 0x8, address: 0x808CEFF0
struct {
    // total size: 0x8
} __RTTI__15CharBonesMeshes; // size: 0x8, address: 0x808CF038
struct {
    // total size: 0x8
} __RTTI__14CharBonesAlloc; // size: 0x8, address: 0x808CF128
struct {
    // total size: 0x8
} __RTTI__15CharBonesObject; // size: 0x8, address: 0x808CF160
struct {
    // total size: 0x8
} __RTTI__9CharBones; // size: 0x8, address: 0x808CF178
struct {
    // total size: 0x21C
} __vt__9Character; // size: 0x21C, address: 0x808CF1C0
struct {
    // total size: 0x8
} __RTTI__PPQ218CharPollableSorter3Dep; // size: 0x8, address: 0x808CF8E0
struct {
    // total size: 0x8
} __RTTI__PP10ShadowBone; // size: 0x8, address: 0x808CF8F8
struct {
    // total size: 0x8
} __RTTI__PQ29Character3Lod; // size: 0x8, address: 0x808CF930
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__P27ObjVector<Q29Character3Lod>; // size: 0x8, address: 0x808CF958
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std80_Rb_tree_node<Q211stlpmtx_std48pair<CPQ23Hmx6Object,Q218CharPollableSorter3Dep>>; // size: 0x8, address: 0x808CF9C0

