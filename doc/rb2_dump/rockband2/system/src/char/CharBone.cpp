/*
    Compile unit: C:\rockband2\system\src\char\CharBone.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80319EAC -> 0x8031B158
*/
class DataArray * types; // size: 0x4, address: 0x80A509C8
// Range: 0x80319EAC -> 0x80319FD0
void * CharBone::CharBone(class CharBone * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8CharBone,9ObjectDir>;
    // -> struct [anonymous] __vt__8CharBone;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x80319FD0 -> 0x80319FE0
class Symbol CharBone::ChannelName() {}

class _List_node : public _List_node_base {
    // total size: 0x10
public:
    struct Bone _M_data; // offset 0x8, size 0x8
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
// Range: 0x80319FE0 -> 0x8031A19C
void CharBone::StuffBones(const class CharBone * const this /* r30 */, class list & bones /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std29_List_node<Q29CharBones4Bone>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std29_List_node<Q29CharBones4Bone>; // size: 0x8, address: 0x808CFF68
// Range: 0x8031A19C -> 0x8031A1D0
unsigned char CharBone::Used() {}

// Range: 0x8031A1D0 -> 0x8031A324
unsigned char CharBone::UsedRecurse(class CharBone * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x2C
    class CharBone * bone; // r0
    struct _List_iterator i; // r1+0x28
    class CharBone * child; // r0

    // References
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharBone;
}

static int gRev; // size: 0x4, address: 0x80A509D0
// Range: 0x8031A324 -> 0x8031A3F8
void CharBone::Save(class CharBone * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x8031A3F8 -> 0x8031A490
class BinStream & __ls(class BinStream & d /* r30 */, const class ObjPtr & f /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8031A490 -> 0x8031A664
void CharBone::Load(class CharBone * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int deltaRotation; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8031A664 -> 0x8031A74C
void CharBone::Copy(class CharBone * const this /* r29 */, const class Object * o /* r30 */, enum CopyType type /* r31 */) {
    // Local variables
    const class CharBone * s; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharBone;
}

// Range: 0x8031A74C -> 0x8031AB44
class DataNode CharBone::Handle(class CharBone * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A509D8
static class Symbol _s; // size: 0x4, address: 0x80A509E0
static class Symbol _s; // size: 0x4, address: 0x80A509E8
static class Symbol _s; // size: 0x4, address: 0x80A509F0
static class Symbol _s; // size: 0x4, address: 0x80A509F8
// Range: 0x8031AB44 -> 0x8031AFF0
unsigned char CharBone::SyncProperty(class CharBone * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x8031AFF0 -> 0x8031B158
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharBone;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x9C
} __vt__8CharBone; // size: 0x9C, address: 0x808D0030
struct {
    // total size: 0x8
} __RTTI__8CharBone; // size: 0x8, address: 0x808D0100
struct {
    // total size: 0x18
} __vt__28ObjPtr<8CharBone,9ObjectDir>; // size: 0x18, address: 0x808D0108
struct {
    // total size: 0x8
} __RTTI__28ObjPtr<8CharBone,9ObjectDir>; // size: 0x8, address: 0x808D0148

