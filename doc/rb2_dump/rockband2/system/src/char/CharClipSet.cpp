/*
    Compile unit: C:\rockband2\system\src\char\CharClipSet.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80335408 -> 0x8033BB1C
*/
class DataArray * types; // size: 0x4, address: 0x80A50C58
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class CharClip * _M_data; // offset 0x8, size 0x4
};
struct AlphaSort {
    // total size: 0x1
};
// Range: 0x80335408 -> 0x803354D8
void CharClipSet::ResetPreviewState(class CharClipSet * const this /* r31 */) {
    // References
    // -> class FilePath sRoot;
}

// Range: 0x803354D8 -> 0x80335A5C
void * CharClipSet::~CharClipSet(class CharClipSet * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__32ObjPtrList<8CharBone,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndDir,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

// Range: 0x80335A5C -> 0x80335B50
void CharClipSet::AddedObject(class CharClipSet * const this /* r31 */) {
    // Local variables
    class CharClip * clip; // r1+0x10

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<P8CharClip>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_List_node<P8CharClip>; // size: 0x8, address: 0x808D25B8
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80335B50 -> 0x80335C8C
void CharClipSet::RemovingObject(class CharClipSet * const this /* r30 */, class Object * o /* r31 */) {
    // Local variables
    int i; // r7
    struct _List_iterator it; // r1+0x24
}

// Range: 0x80335C8C -> 0x80335DA8
static void StuffGroups(class CharClip * clip /* r29 */, class CharClipSet * dir /* r30 */, class vector & groups /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x20
    class Object * o; // r0
    class CharClipGroup * group; // r1+0x1C

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
}

// Range: 0x80335DA8 -> 0x80335E60
static unsigned char ClipUnique(class CharClip * c /* r28 */, int mask /* r29 */, class vector & groups /* r30 */) {
    // Local variables
    int i; // r31
}

class vector : protected _Vector_base {
    // total size: 0xC
};
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
// Range: 0x80335E60 -> 0x803363C8
int CharClipSet::DeleteVariants(class CharClipSet * const this /* r21 */, int mask /* r22 */, class CharClipSet * dst /* r23 */, class DataArray * limits /* r24 */) {
    // Local variables
    class vector clips; // r1+0xA4
    int saved; // r30
    class vector groups; // r1+0x98
    class map limitMap; // r1+0xB0
    int i; // r20
    class Symbol name; // r1+0x54
    int i; // r29
    class CharClip * c; // r28
    unsigned char remove; // r27
    int flags; // r26
    int j; // r25
    int numDupes; // r0
    class Symbol groupName; // r1+0x50
    class DataArray * limitArr; // r19
    int limit; // r18
    int k; // r17
    int j; // r17

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP8CharClip;
    // -> unsigned char gStlAllocNameLookup;
}

struct ClipSizeSort {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PP8CharClip; // size: 0x8, address: 0x808D2670
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class CharClipGroup * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class CharClipGroup * * _M_start; // offset 0x0, size 0x4
    class CharClipGroup * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
struct pair {
    // total size: 0x8
    class Symbol first; // offset 0x0, size 0x4
    class DataArray * second; // offset 0x4, size 0x4
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
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
// Range: 0x803363C8 -> 0x80336734
int CharClipSet::TotalSize(class CharClipSet * const this /* r29 */) {
    // Local variables
    int total; // r31
    int i; // r30
    class ObjDirItr t; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x80336734 -> 0x8033685C
void CharClipSet::SetLRU(class CharClipSet * const this /* r30 */) {
    // Local variables
    int i; // r31
    class CharClip * c; // r29

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<P8CharClip>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8033685C -> 0x80336890
void CharClipSet::ResetEditorState(class CharClipSet * const this /* r31 */) {}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class CharClip * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
struct SortClips {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std31_List_node<P16RndTransformable>; // size: 0x8, address: 0x808D2718
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class CharClipGroup * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x80336890 -> 0x80336B90
void CharClipSet::RandomizeGroups() {
    // Local variables
    class ObjDirItr g; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
}

// Range: 0x80336B90 -> 0x80336E90
void CharClipSet::SortGroups() {
    // Local variables
    class ObjDirItr g; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
}

// Range: 0x80336E90 -> 0x80337228
void Recenter::Sync(class Recenter * const this /* r30 */) {
    // Local variables
    class CharClipSet * clips; // r31
    struct _List_iterator it; // r1+0x2C
    class CharBone * b; // r0
    class CharClipSet * clips; // r31
    struct _List_iterator it; // r1+0x28
    class CharBone * b; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__8CharBone;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharClipSet;
}

static int gRev; // size: 0x4, address: 0x80A50C60
// Range: 0x80337228 -> 0x8033732C
int CharClipSet::TypeVersion(class CharClipSet * const this /* r29 */) {
    // Local variables
    int version; // r30
    const class DataNode * vp; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

// Range: 0x8033732C -> 0x80337370
void CharClipSet::PreSave() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80337370 -> 0x803378C0
void CharClipSet::PostSave(class CharClipSet * const this /* r30 */) {
    // Local variables
    class list loaders; // r1+0x58
    class ObjDirItr l; // r1+0x60
    struct _List_iterator l; // r1+0x2C
    class Object * milo; // r29

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class ObjectDir * sMainDir;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std27_List_node<P12OutfitLoader>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitLoader;
    // -> class LoadMgr TheLoadMgr;
}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class CharClipSamples * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x803378C0 -> 0x80337BC0
void CharClipSet::RecenterAll() {
    // Local variables
    class ObjDirItr clip; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__15CharClipSamples;
}

// Range: 0x80337BC0 -> 0x80337EF4
class BinStream & __rs(class BinStream & d /* r29 */, class Recenter & r /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static int gRev;
}

// Range: 0x80337EF4 -> 0x80337F54
class BinStream & __ls(class BinStream & d /* r30 */, class Recenter & r /* r31 */) {}

// Range: 0x80337F54 -> 0x80337F58
void CharClipSet::Load() {}

// Range: 0x80337F58 -> 0x80338150
void CharClipSet::Save(class CharClipSet * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int i; // r29
    class CharClip * c; // r28
    class CharClipSamples * cs; // r0

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __RTTI__8CharClip;
    // -> struct [anonymous] __RTTI__15CharClipSamples;
}

static class Message filterClips; // size: 0x8, address: 0x8097DFA0
// Range: 0x80338150 -> 0x80338948
void CharClipSet::PostLoad(class CharClipSet * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int blendWidth; // r1+0x68
    int playFlags; // r1+0x64
    int flags; // r1+0x60
    class FilePath dummy; // r1+0x98
    class String oldGeomPath; // r1+0x8C
    int size; // r1+0x5C
    int i; // r26
    class ObjPtr clip; // r1+0x80
    int flags; // r1+0x58
    int size; // r1+0x54
    int size; // r1+0x50
    int i; // r26
    class Symbol s; // r1+0x4C

    // References
    // -> static class Message filterClips;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static int gRev;
    // -> class list sRevs;
}

// Range: 0x80338948 -> 0x80338A60
void CharClipSet::Copy(class CharClipSet * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class CharClipSet * c; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharClipSet;
}

// Range: 0x80338A60 -> 0x80338AD0
void CharClipSet::StuffBones(class CharBones & bones /* r30 */) {
    // Local variables
    class list bs; // r1+0x18
}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class CharBone * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x80338AD0 -> 0x80338FF0
void CharClipSet::ListBones(class CharClipSet * const this /* r28 */, class list & l /* r29 */, unsigned char includeDelta /* r30 */) {
    // Local variables
    class ObjDirItr bone; // r1+0x58

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharBone;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std29_List_node<Q29CharBones4Bone>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80338FF0 -> 0x80339010
void CharClipSet::DrawShowing() {}

// Range: 0x80339038 -> 0x80339054
float CharClipSet::StartFrame() {}

// Range: 0x80339054 -> 0x80339070
float CharClipSet::EndFrame() {}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class CharPollable * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x80339070 -> 0x803393B0
int CharClipSet::PruneCharBones() {
    // Local variables
    int count; // r31
    class ObjDirItr bone; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharBone;
}

// Range: 0x803393B0 -> 0x803399EC
void CharClipSet::GrabLoadPose(class CharClipSet * const this /* r27 */) {
    // Local variables
    class ObjDirItr bone; // r1+0x30

    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

static class Symbol _s; // size: 0x4, address: 0x80A50C68
static class Symbol _s; // size: 0x4, address: 0x80A50C70
static class Symbol _s; // size: 0x4, address: 0x80A50C78
static class Symbol _s; // size: 0x4, address: 0x80A50C80
static class Symbol _s; // size: 0x4, address: 0x80A50C88
static class Symbol _s; // size: 0x4, address: 0x80A50C90
static class Symbol _s; // size: 0x4, address: 0x80A50C98
static class Symbol _s; // size: 0x4, address: 0x80A50CA0
static class Symbol _s; // size: 0x4, address: 0x80A50CA8
static class Symbol _s; // size: 0x4, address: 0x80A50CB0
static class Symbol _s; // size: 0x4, address: 0x80A50CB8
static class Symbol _s; // size: 0x4, address: 0x80A50CC0
// Range: 0x803399EC -> 0x8033A8D0
class DataNode CharClipSet::Handle(class CharClipSet * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x50
    class MessageTimer _mt; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode _n; // r1+0x58

    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A50CC8
static class Symbol _s; // size: 0x4, address: 0x80A50CD0
static class Symbol _s; // size: 0x4, address: 0x80A50CD8
// Range: 0x8033A8D0 -> 0x8033AAE4
unsigned char PropSync(class Recenter & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x8033AAE4 -> 0x8033B19C
unsigned char PropSync(class ObjPtrList & l /* r26 */, class DataNode & n /* r27 */, class DataArray * prop /* r28 */, int i /* r29 */, enum PropOp op /* r30 */) {
    // Local variables
    class iterator it; // r1+0x1C
    int which; // r3
    class CharBone * obj; // r31
    class CharBone * obj; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharBone;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A50CE0
static class Symbol _s; // size: 0x4, address: 0x80A50CE8
static class Symbol _s; // size: 0x4, address: 0x80A50CF0
static class Symbol _s; // size: 0x4, address: 0x80A50CF8
static class Symbol _s; // size: 0x4, address: 0x80A50D00
static class Symbol _s; // size: 0x4, address: 0x80A50D08
static class Symbol _s; // size: 0x4, address: 0x80A50D10
static class Symbol _s; // size: 0x4, address: 0x80A50D18
static class Symbol _s; // size: 0x4, address: 0x80A50D20
static class Symbol _s; // size: 0x4, address: 0x80A50D28
static class Symbol _s; // size: 0x4, address: 0x80A50D30
static class Symbol _s; // size: 0x4, address: 0x80A50D38
// Range: 0x8033B19C -> 0x8033B9C0
unsigned char CharClipSet::SyncProperty(class CharClipSet * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x8033B9C0 -> 0x8033BB1C
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__13CharNeckTwist; // size: 0x8, address: 0x808D2D08
struct {
    // total size: 0x8
} __RTTI__14CharUpperTwist; // size: 0x8, address: 0x808D2D48
struct {
    // total size: 0x174
} __vt__11CharClipSet; // size: 0x174, address: 0x808D2E78
struct {
    // total size: 0x18
} __vt__32ObjPtrList<8CharBone,9ObjectDir>; // size: 0x18, address: 0x808D3080
struct {
    // total size: 0x8
} __RTTI__32ObjPtrList<8CharBone,9ObjectDir>; // size: 0x8, address: 0x808D30C8
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
struct {
    // total size: 0x8
} __RTTI__PP13CharClipGroup; // size: 0x8, address: 0x808D35D0
struct _OKToMemCpy {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211CharClipSet7BoneXfm; // size: 0x8, address: 0x808D3618
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std58_Rb_tree_node<Q211stlpmtx_std26pair<C6Symbol,P9DataArray>>; // size: 0x8, address: 0x808D3670

