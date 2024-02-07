/*
    Compile unit: C:\rockband2\system\src\bandobj\OutfitConfig.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80290668 -> 0x80292818
*/
class DataArray * types; // size: 0x4, address: 0x80A4F920
class DataArray * types; // size: 0x4, address: 0x80A4F928
class Symbol name; // size: 0x4, address: 0x80A4F930
// Range: 0x80290668 -> 0x80290718
class BinStream & __rs(class BinStream & d /* r30 */, struct ColorSet & s /* r31 */) {}

// Range: 0x80290718 -> 0x80290764
void * ColorPalette::ColorPalette(class ColorPalette * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12ColorPalette;
}

// Range: 0x80290764 -> 0x802907C8
void ColorPalette::Save(class ColorPalette * const this /* r30 */, class BinStream & d /* r31 */) {}

class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct ColorSet * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct ColorSet * _M_start; // offset 0x0, size 0x4
    struct ColorSet * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x802907C8 -> 0x802908A4
void ColorPalette::Sync(class ColorPalette * const this /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18
    class Object * o; // r31
    class OutfitConfig * oc; // r0
    class BandSwatch * bs; // r0

    // References
    // -> struct [anonymous] __RTTI__10BandSwatch;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitConfig;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F938
// Range: 0x802908A4 -> 0x802909A0
unsigned char ColorPalette::SyncProperty(class ColorPalette * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
}

// Range: 0x802909A0 -> 0x80290A30
void * MatOption::MatOption() {
    // References
    // -> struct [anonymous] __vt__33ObjPtr<12ColorPalette,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
}

// Range: 0x80290A30 -> 0x80290A64
void * ColorOption::ColorOption() {}

class _List_node : public _List_node_base {
    // total size: 0x3C
public:
    struct MatOption _M_data; // offset 0x8, size 0x34
};
// Range: 0x80290A64 -> 0x80290AF8
void OutfitConfig::Init() {
    // References
    // -> class Symbol name;
    // -> class Symbol name;
}

// Range: 0x80290AF8 -> 0x80290BB0
void * OutfitConfig::OutfitConfig(class OutfitConfig * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12OutfitConfig;
    // -> struct [anonymous] __vt__11RndPollable;
}

static int gRev; // size: 0x4, address: 0x80A4F93C
// Range: 0x80290BB0 -> 0x80290C10
class BinStream & __ls(class BinStream & d /* r30 */, const struct MatOption & m /* r31 */) {}

// Range: 0x80290C10 -> 0x80290C7C
class BinStream & __rs(class BinStream & d /* r30 */, struct MatOption & m /* r31 */) {
    // References
    // -> static int gRev;
}

// Range: 0x80290C7C -> 0x80290CD4
class BinStream & __ls(class BinStream & d /* r30 */, const struct ColorOption & c /* r31 */) {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80290CD4 -> 0x80290D20
class BinStream & __rs(class BinStream & d /* r30 */, struct ColorOption & c /* r31 */) {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80290D20 -> 0x80290D84
void OutfitConfig::Save(class OutfitConfig * const this /* r30 */, class BinStream & d /* r31 */) {}

class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
// Range: 0x80290D84 -> 0x80290FE8
void OutfitConfig::Load(class OutfitConfig * const this /* r28 */, class BinStream & d /* r29 */) {
    // Local variables
    class ObjVector old_patches; // r1+0x48
    class ObjVector old_patches; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndTexRenderer * mPtr; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjPtr * _M_start; // offset 0x0, size 0x4
    class ObjPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x80290FE8 -> 0x80291300
void OutfitConfig::Copy(class OutfitConfig * const this /* r26 */, enum CopyType type /* r25 */) {
    // Local variables
    const class OutfitConfig * oc; // r27

    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12ColorPalette,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitConfig;
}

// Range: 0x80291300 -> 0x80291348
void OutfitConfig::Enter(class OutfitConfig * const this /* r31 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80291348 -> 0x802914AC
class DataArray * OutfitConfig::MakeColorConfig(class OutfitConfig * const this /* r30 */) {
    // Local variables
    class DataArray * colors; // r31
    int i; // r29
}

// Range: 0x802914AC -> 0x802914C4
int OutfitConfig::NumColors() {}

// Range: 0x802914C4 -> 0x80291578
class ColorPalette * OutfitConfig::Palette(class OutfitConfig * const this /* r30 */, int option_index /* r31 */) {
    // Local variables
    class ObjList & mats; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80291578 -> 0x80291600
int OutfitConfig::ColorIndex(const class OutfitConfig * const this /* r30 */, int option_index /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80291600 -> 0x80291824
void OutfitConfig::Apply(class OutfitConfig * const this /* r28 */) {
    // Local variables
    struct ColorOption * c; // r30
    int idx; // r29
    struct _List_iterator m; // r1+0x10

    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80291824 -> 0x802918C4
void OutfitConfig::Randomize(class OutfitConfig * const this /* r30 */) {
    // Local variables
    struct ColorOption * c; // r31
    class ColorPalette * p; // r5
}

// Range: 0x802918C4 -> 0x80291A38
void OutfitConfig::CompositeColors(class OutfitConfig * const this /* r30 */) {
    // Local variables
    class vector composite_mats; // r1+0x20
    struct ColorOption * c; // r31
    struct _List_iterator m; // r1+0x1C
    class RndMat * mat; // r1+0x18
    class RndMat * * it; // r29
}

// Range: 0x80291A38 -> 0x80291BAC
void OutfitConfig::FinalizeColors(class OutfitConfig * const this /* r30 */) {
    // Local variables
    class vector finalize_mats; // r1+0x20
    struct ColorOption * c; // r31
    struct _List_iterator m; // r1+0x1C
    class RndMat * mat; // r1+0x18
    class RndMat * * it; // r29
}

// Range: 0x80291BAC -> 0x80291BD4
void OutfitConfig::SetColorIndex() {}

static class Symbol _s; // size: 0x4, address: 0x80A4F944
static class Symbol _s; // size: 0x4, address: 0x80A4F94C
static class Symbol _s; // size: 0x4, address: 0x80A4F954
static class Symbol _s; // size: 0x4, address: 0x80A4F95C
// Range: 0x80291BD4 -> 0x80292334
class DataNode OutfitConfig::Handle(class OutfitConfig * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class OutfitConfig * gOwner; // size: 0x4, address: 0x80A4F960
static class Symbol _s; // size: 0x4, address: 0x80A4F968
static class Symbol _s; // size: 0x4, address: 0x80A4F970
static class Symbol _s; // size: 0x4, address: 0x80A4F978
static class Symbol _s; // size: 0x4, address: 0x80A4F980
// Range: 0x80292334 -> 0x80292570
unsigned char PropSync(struct MatOption & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class OutfitConfig * gOwner;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F988
static class Symbol _s; // size: 0x4, address: 0x80A4F990
// Range: 0x80292570 -> 0x8029273C
unsigned char PropSync(struct ColorOption & _me /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class OutfitConfig * gOwner;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x8
} __RTTI__P26ObjPtr<6RndTex,9ObjectDir>; // size: 0x8, address: 0x808BE0E8
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_List_node<9MatOption>; // size: 0x8, address: 0x808BE118
static class Symbol _s; // size: 0x4, address: 0x80A4F998
// Range: 0x8029273C -> 0x80292818
unsigned char OutfitConfig::SyncProperty(class OutfitConfig * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class OutfitConfig * gOwner;
}

struct {
    // total size: 0x18
} __vt__35ObjPtr<14RndTexRenderer,9ObjectDir>; // size: 0x18, address: 0x808BE168
struct {
    // total size: 0x8
} __RTTI__35ObjPtr<14RndTexRenderer,9ObjectDir>; // size: 0x8, address: 0x808BE1B0
struct {
    // total size: 0x8C
} __vt__12OutfitConfig; // size: 0x8C, address: 0x808BE490
struct {
    // total size: 0x54
} __vt__12ColorPalette; // size: 0x54, address: 0x808BE5A0
struct {
    // total size: 0x8
} __RTTI__P11ColorOption; // size: 0x8, address: 0x808BE7D8
struct ColorSet {
    // total size: 0x20
    class Color mPrimary; // offset 0x0, size 0x10
    class Color mSecondary; // offset 0x10, size 0x10
};
struct {
    // total size: 0x8
} __RTTI__P35ObjPtr<14RndTexRenderer,9ObjectDir>; // size: 0x8, address: 0x808BE808
struct {
    // total size: 0x8
} __RTTI__P26ObjPtr<6RndDir,9ObjectDir>; // size: 0x8, address: 0x808BE830
struct {
    // total size: 0x8
} __RTTI__P8ColorSet; // size: 0x8, address: 0x808BE848

