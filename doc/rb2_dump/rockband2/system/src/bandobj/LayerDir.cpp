/*
    Compile unit: C:\rockband2\system\src\bandobj\LayerDir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802860A8 -> 0x80288A90
*/
class Symbol name; // size: 0x4, address: 0x80A4F82C
class DataArray * types; // size: 0x4, address: 0x80A4F830
class Symbol name; // size: 0x4, address: 0x80A4F838
class RndCam * sCam; // size: 0x4, address: 0x80A4F83C
class ObjList : public list {
    // total size: 0xC
    class Object * mOwner; // offset 0x8, size 0x4
};
class LayerDir : public RndDir {
    // total size: 0x240
public:
    class ObjList mLayers; // offset 0x1F4, size 0xC
    unsigned char mUseFreeCam; // offset 0x200, size 0x1
};
// Range: 0x802860A8 -> 0x802861A0
void LayerDir::Init() {
    // References
    // -> class Symbol name;
    // -> class RndCam * sCam;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndCam;
    // -> class Symbol name;
}

// Range: 0x802861A0 -> 0x802862DC
void * LayerDir::LayerDir(class LayerDir * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__8LayerDir;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

class _List_node : public _List_node_base {
    // total size: 0x90
public:
    struct Layer _M_data; // offset 0x10, size 0x80
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
// Range: 0x802862DC -> 0x8028632C
void LayerDir::DrawShowing(class LayerDir * const this /* r31 */) {
    // References
    // -> class RndCam * sCam;
}

// Range: 0x8028632C -> 0x80286348
class RndCam * LayerDir::CamOverride() {
    // References
    // -> class RndCam * sCam;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80286348 -> 0x80286504
class DataNode LayerDir::RandomizeColors(class LayerDir * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x20
    int idx; // r27
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80286504 -> 0x80286B54
void LayerDir::RefreshLayer(class LayerDir * const this /* r29 */, struct Layer & ct /* r30 */) {
    // Local variables
    class String dif; // r1+0xCC
    class String difbmp; // r1+0xC0
    class String norm; // r1+0xB4
    class String spec; // r1+0xA8
    class String normbmp; // r1+0x9C
    class String specbmp; // r1+0x90
    struct _List_iterator i; // r1+0x44
    const char * f; // r27
    struct _List_iterator i; // r1+0x40
    class RndTexRenderer * t; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14RndTexRenderer;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

static int gRev; // size: 0x4, address: 0x80A4F840
// Range: 0x80286B54 -> 0x80286EA0
class BinStream & __rs(class BinStream & d /* r30 */, struct Layer & e /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> static int gRev;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

// Range: 0x80286EA0 -> 0x80286EE4
void LayerDir::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80286EE4 -> 0x80286FD4
void LayerDir::PreLoad(class LayerDir * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> static int gRev;
}

class _List_node : public _List_node_base {
    // total size: 0x14
public:
    class FilePath _M_data; // offset 0x8, size 0xC
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
// Range: 0x80286FD4 -> 0x80287094
void LayerDir::PostLoad(class LayerDir * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> static int gRev;
    // -> class list sRevs;
}

// Range: 0x80287094 -> 0x802870FC
void LayerDir::Copy(class LayerDir * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class LayerDir * d; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8LayerDir;
}

// Range: 0x802870FC -> 0x80287508
class DataNode LayerDir::GetBitmapList(class LayerDir * const this /* r31 */) {
    // Local variables
    class DataArray * path; // r29
    class DataNode n; // r1+0x68
    const char * name; // r28
    struct _List_iterator i; // r1+0x40
    class DataArrayPtr da; // r1+0x60
    int y; // r28
    struct _List_iterator x; // r1+0x3C
    class String t; // r1+0x7C

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

static class LayerDir * gOwner; // size: 0x4, address: 0x80A4F844
static class Symbol _s; // size: 0x4, address: 0x80A4F84C
static class Symbol _s; // size: 0x4, address: 0x80A4F854
static class Symbol _s; // size: 0x4, address: 0x80A4F85C
static class Symbol _s; // size: 0x4, address: 0x80A4F864
static class Symbol _s; // size: 0x4, address: 0x80A4F86C
static class Symbol _s; // size: 0x4, address: 0x80A4F874
static class Symbol _s; // size: 0x4, address: 0x80A4F87C
static class Symbol _s; // size: 0x4, address: 0x80A4F884
static class Symbol _s; // size: 0x4, address: 0x80A4F88C
static class Symbol _s; // size: 0x4, address: 0x80A4F894
static class Symbol _s; // size: 0x4, address: 0x80A4F89C
static class Symbol _s; // size: 0x4, address: 0x80A4F8A4
static class Symbol _s; // size: 0x4, address: 0x80A4F8AC
static class Symbol _s; // size: 0x4, address: 0x80A4F8B4
static class Symbol _s; // size: 0x4, address: 0x80A4F8BC
// Range: 0x80287508 -> 0x80288080
unsigned char PropSync(struct Layer & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class LayerDir * gOwner;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80288080 -> 0x8028832C
unsigned char PropSync(class list & l /* r27 */, class DataNode & n /* r31 */, class DataArray * prop /* r28 */, int i /* r29 */, enum PropOp op /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x2C
    int which; // r3
    class FilePath tmp; // r1+0x38

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std21_List_node<8FilePath>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std21_List_node<8FilePath>; // size: 0x8, address: 0x808BC918
static class Symbol _s; // size: 0x4, address: 0x80A4F8C4
static class Symbol _s; // size: 0x4, address: 0x80A4F8CC
// Range: 0x8028832C -> 0x80288520
unsigned char LayerDir::SyncProperty(class LayerDir * const this /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class LayerDir * gOwner;
}

struct Layer {
    // total size: 0x80
    class String mName; // offset 0x0, size 0xC
    class ObjPtr mMat; // offset 0xC, size 0xC
    unsigned char mActive; // offset 0x18, size 0x1
    class Color mColor; // offset 0x20, size 0x10
    int mColorIdx; // offset 0x30, size 0x4
    float mAlpha; // offset 0x34, size 0x4
    class String mBitmap; // offset 0x38, size 0xC
    class FilePath mProxyFile; // offset 0x44, size 0xC
    unsigned char mOptional; // offset 0x50, size 0x1
    unsigned char mAllowColor; // offset 0x51, size 0x1
    class ObjPtr mColorPalette; // offset 0x54, size 0xC
    unsigned char mAllowAlpha; // offset 0x60, size 0x1
    float mAlphaMin; // offset 0x64, size 0x4
    float mAlphaMax; // offset 0x68, size 0x4
    class list mBitmapList; // offset 0x6C, size 0x8
    class ObjPtr mProxy; // offset 0x74, size 0xC
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std29_List_node<Q28LayerDir5Layer>; // size: 0x8, address: 0x808BC990
static class Symbol _s; // size: 0x4, address: 0x80A4F8D4
static class Symbol _s; // size: 0x4, address: 0x80A4F8DC
// Range: 0x80288520 -> 0x80288A90
class DataNode LayerDir::Handle(class LayerDir * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode r; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x220
} __vt__8LayerDir; // size: 0x220, address: 0x808BC9D8
struct {
    // total size: 0x8
} __RTTI__8LayerDir; // size: 0x8, address: 0x808BCC58
struct {
    // total size: 0x18
} __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>; // size: 0x18, address: 0x808BCCA8
struct {
    // total size: 0x8
} __RTTI__32ObjPtr<Q23Hmx6Object,9ObjectDir>; // size: 0x8, address: 0x808BCCF0
struct {
    // total size: 0x8
} __RTTI__6RndCam; // size: 0x8, address: 0x808BCF30

