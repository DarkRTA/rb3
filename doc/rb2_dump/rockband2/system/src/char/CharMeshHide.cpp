/*
    Compile unit: C:\rockband2\system\src\char\CharMeshHide.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80386DD4 -> 0x803882B8
*/
class DataArray * types; // size: 0x4, address: 0x80A512E0
class Symbol name; // size: 0x4, address: 0x80A512E8
// Range: 0x80386DD4 -> 0x80386E28
class BinStream & __ls(class BinStream & d /* r30 */, const class Hide & h /* r31 */) {}

// Range: 0x80386E28 -> 0x80386E74
class BinStream & __rs(class BinStream & d /* r30 */, class Hide & h /* r31 */) {}

class Hide {
    // total size: 0x10
public:
    class ObjPtr mDraw; // offset 0x0, size 0xC
    int mFlags; // offset 0xC, size 0x4
};
// Range: 0x80386E74 -> 0x80386EB8
void * Hide::Hide() {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
}

// Range: 0x80386EB8 -> 0x80386F2C
void * Hide::Hide(class Hide * const this /* r30 */, const class Hide & h /* r31 */) {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
}

// Range: 0x80386F2C -> 0x80386FB8
class Hide & Hide::__as(class Hide * const this /* r29 */, const class Hide & h /* r30 */) {}

// Range: 0x80386FB8 -> 0x8038702C
static class DataNode OnCharMeshHide(class DataArray * msg /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
}

class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class CharMeshHide : public Object {
    // total size: 0x3C
protected:
    class ObjVector mHides; // offset 0x28, size 0x10
    int mFlags; // offset 0x38, size 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class CharMeshHide * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8038702C -> 0x803873F8
void CharMeshHide::HideAll() {
    // Local variables
    class list hides; // r1+0x38
    int flags; // r31
    class ObjDirItr h; // r1+0x40
    struct _List_iterator it; // r1+0x24

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std27_List_node<P12CharMeshHide>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12CharMeshHide;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class CharMeshHide * _M_data; // offset 0x8, size 0x4
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
} __RTTI__PQ211stlpmtx_std27_List_node<P12CharMeshHide>; // size: 0x8, address: 0x808DAAA0
// Range: 0x803873F8 -> 0x8038744C
void CharMeshHide::HideDraws() {
    // Local variables
    int i; // r7
}

// Range: 0x8038744C -> 0x803874A0
void * CharMeshHide::CharMeshHide(class CharMeshHide * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12CharMeshHide;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Hide * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Hide * _M_start; // offset 0x0, size 0x4
    class Hide * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x803874A0 -> 0x803875B4
void * CharMeshHide::~CharMeshHide(class CharMeshHide * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
}

static int gRev; // size: 0x4, address: 0x80A512EC
// Range: 0x803875B4 -> 0x80387630
void CharMeshHide::Save(class CharMeshHide * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x80387630 -> 0x803876F4
void CharMeshHide::Load(class CharMeshHide * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x803876F4 -> 0x803878A8
void CharMeshHide::Copy(class CharMeshHide * const this /* r30 */, const class Object * o /* r26 */) {
    // Local variables
    const class CharMeshHide * h; // r0

    // References
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12CharMeshHide;
}

// Range: 0x803878A8 -> 0x80387B50
class DataNode CharMeshHide::Handle(class CharMeshHide * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A512F4
static class Symbol _s; // size: 0x4, address: 0x80A512FC
// Range: 0x80387B50 -> 0x80387D0C
unsigned char PropSync(class Hide & _me /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80387D0C -> 0x80387E74
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A51304
static class Symbol _s; // size: 0x4, address: 0x80A5130C
// Range: 0x80387E74 -> 0x80388044
unsigned char CharMeshHide::SyncProperty(class CharMeshHide * const this /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x80388044 -> 0x803882B8
unsigned char PropSync(class ObjVector & v /* r31 */, class DataNode & n /* r26 */, class DataArray * prop /* r27 */, int i /* r30 */, enum PropOp op /* r29 */) {
    // Local variables
    class Hide * it; // r28
    class Hide tmp; // r1+0x20

    // References
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x54
} __vt__12CharMeshHide; // size: 0x54, address: 0x808DAB48
struct {
    // total size: 0x8
} __RTTI__12CharMeshHide; // size: 0x8, address: 0x808DABC0
struct {
    // total size: 0x8
} __RTTI__PQ212CharMeshHide4Hide; // size: 0x8, address: 0x808DABE0

