/*
    Compile unit: C:\rockband2\system\src\char\OutfitLoader.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803A9354 -> 0x803AF4D8
*/
class DataArray * types; // size: 0x4, address: 0x80A515A8
unsigned char sDisableAll; // size: 0x1, address: 0x80A515AD
// Range: 0x803A9354 -> 0x803A9394
class Symbol Category::Name() {}

// Range: 0x803A9394 -> 0x803A94F0
int Category::GetOutfitIndex(const struct Category * const this /* r27 */, const class DataNode & n /* r28 */, unsigned char notify /* r29 */) {
    // Local variables
    int i; // r30
    class String s; // r1+0x1C

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803A94F0 -> 0x803A95A4
void Category::Clear(struct Category * const this /* r30 */, unsigned char isChanged /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol none; // size: 0x4, address: 0x80A515B0
// Range: 0x803A95A4 -> 0x803A962C
class Symbol Category::OutfitName(const struct Category * const this /* r30 */, int outfit /* r31 */) {
    // References
    // -> static class Symbol none;
}

// Range: 0x803A962C -> 0x803A976C
class DataNode Category::OutfitList(class DataNode * n /* r30 */, struct Category * const this /* r31 */) {
    // Local variables
    class DataArray * arr; // r29
    int i; // r28
}

static class Timer * _t; // size: 0x4, address: 0x80A515B4
// Range: 0x803A976C -> 0x803A98F8
void Category::SetAllowShowing(struct Category * const this /* r30 */, unsigned char allowed /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0x20
    class iterator i; // r1+0x1C
    class RndDrawable * mesh; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> static class Timer * _t;
}

// Range: 0x803A98F8 -> 0x803A9938
class Symbol Outfit::Name() {}

// Range: 0x803A9938 -> 0x803A9A1C
void * OutfitLoader::OutfitLoader(class OutfitLoader * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __vt__12OutfitLoader;
}

class _List_node : public _List_node_base {
    // total size: 0x1C
public:
    struct LoaderDesc _M_data; // offset 0x8, size 0x14
};
// Range: 0x803A9A1C -> 0x803A9D60
void * OutfitLoader::~OutfitLoader(class OutfitLoader * const this /* r27 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__12OutfitLoader;
}

static class Symbol path; // size: 0x4, address: 0x80A515BC
static class Symbol outfits; // size: 0x4, address: 0x80A515C4
static class DataNode & meVar; // size: 0x4, address: 0x80A515CC
// Range: 0x803A9D60 -> 0x803AA938
void OutfitLoader::SetTypeDef(class OutfitLoader * const this /* r30 */, class DataArray * d /* r31 */) {
    // Local variables
    class DataNode oldMe; // r1+0x78
    class DataArray * cats; // r23
    int i; // r26
    class DataArray * pathData; // r22
    class DataArray * outfitData; // r27
    int j; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<Q23Hmx6Object,9ObjectDir>;
    // -> static class DataNode & meVar;
    // -> static class Symbol outfits;
    // -> static class Symbol path;
}

// Range: 0x803AA938 -> 0x803AAA98
void OutfitLoader::Reset(class OutfitLoader * const this /* r30 */) {
    // Local variables
    int i; // r31
    struct Category & category; // r0
    int j; // r27
}

// Range: 0x803AAA98 -> 0x803AABB0
void OutfitLoader::SetPrefab(class OutfitLoader * const this /* r28 */, const class DataArray * data /* r29 */) {
    // Local variables
    class String s; // r1+0x18
    int i; // r30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x803AABB0 -> 0x803AAC04
struct Category * OutfitLoader::FindCategory(class OutfitLoader * const this /* r31 */) {
    // Local variables
    int i; // r0
}

// Range: 0x803AAC04 -> 0x803AACE8
int OutfitLoader::FindCategoryIndex(class OutfitLoader * const this /* r28 */, class Symbol & name /* r29 */, unsigned char fail /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x803AACE8 -> 0x803AAD7C
int OutfitLoader::FindOutfitIndex(class Symbol & outfit /* r31 */) {
    // Local variables
    struct Category * cat; // r0
}

// Range: 0x803AAD7C -> 0x803AAE80
void OutfitLoader::Select(class OutfitLoader * const this /* r28 */, struct Category * cat /* r29 */, int select /* r30 */, int dir /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x803AAE80 -> 0x803AAF48
void OutfitLoader::Select(class OutfitLoader * const this /* r28 */, class Symbol & outfit /* r30 */, int dir /* r29 */) {
    // Local variables
    struct Category * cat; // r31
    int o; // r30
}

// Range: 0x803AAF48 -> 0x803AB064
unsigned char OutfitLoader::IsMatch(class DataArray * d /* r25 */, struct Category * cat /* r26 */) {
    // Local variables
    int outfit; // r30
    int i; // r29
    class DataArray * e; // r28
    int j; // r27
}

// Range: 0x803AB064 -> 0x803AB0CC
unsigned char OutfitLoader::CanShow() {}

class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x803AB0CC -> 0x803AB288
unsigned char OutfitLoader::TryShow(class OutfitLoader * const this /* r25 */, struct Category * cat /* r26 */, int outfit /* r27 */, unsigned char force /* r28 */) {
    // Local variables
    unsigned char success; // r30
    int first; // r29
    class vector changed; // r1+0x10
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Category * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Category * * _M_start; // offset 0x0, size 0x4
    struct Category * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x803AB288 -> 0x803AB318
void OutfitLoader::ReshowChanged(class OutfitLoader * const this /* r29 */, class vector & changed /* r30 */) {
    // Local variables
    int i; // r31
    struct Category * cat; // r4
}

static class Symbol hide; // size: 0x4, address: 0x80A515D4
static class Symbol unhide; // size: 0x4, address: 0x80A515DC
static class Symbol desire; // size: 0x4, address: 0x80A515E4
// Range: 0x803AB318 -> 0x803AB46C
void OutfitLoader::ChangeRestrictions(class OutfitLoader * const this /* r27 */, struct Category * cat /* r28 */, int delta /* r29 */, class vector & changed /* r30 */) {
    // Local variables
    const class DataArray * data; // r31

    // References
    // -> static class Symbol desire;
    // -> static class Symbol unhide;
    // -> static class Symbol hide;
}

// Range: 0x803AB46C -> 0x803AB590
void OutfitLoader::UpdateExclude(class OutfitLoader * const this /* r26 */, struct Category * cat /* r27 */, int delta /* r28 */, class vector & changed /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x803AB590 -> 0x803AB748
void OutfitLoader::Exclude(class OutfitLoader * const this /* r27 */, class DataArray * d /* r28 */, int delta /* r29 */, class vector & changed /* r30 */) {
    // Local variables
    int i; // r31
    class DataArray * e; // r26
    struct Category * cat; // r1+0x14
    int j; // r5
    int j; // r25
}

// Range: 0x803AB748 -> 0x803AB88C
void OutfitLoader::UpdateDesire(class OutfitLoader * const this /* r26 */, class DataArray * data /* r27 */, int delta /* r28 */, class vector & changed /* r29 */) {
    // Local variables
    int j; // r30
    struct Category * cat; // r1+0x14
}

// Range: 0x803AB88C -> 0x803ABA4C
void OutfitLoader::UpdateHide(class OutfitLoader * const this /* r27 */, class DataArray * d /* r28 */, int delta /* r29 */, class vector & changed /* r30 */) {
    // Local variables
    int j; // r31
    class DataArray * h; // r26
    struct Category * cat; // r1+0x14
    int k; // r5
    int k; // r25
}

// Range: 0x803ABA4C -> 0x803ABA54
void OutfitLoader::StartLoad() {}

static class Message changeOutfit; // size: 0x8, address: 0x8097E078
// Range: 0x803ABA54 -> 0x803ABDB8
void OutfitLoader::StartLoadInternal(class OutfitLoader * const this /* r29 */, unsigned char async /* r30 */, unsigned char loading /* r31 */) {
    // Local variables
    int i; // r28

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> static class Message changeOutfit;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x803ABDB8 -> 0x803ABE64
void OutfitLoader::Clear(class OutfitLoader * const this /* r30 */) {
    // Local variables
    int i; // r31
}

static class Symbol none; // size: 0x4, address: 0x80A515EC
static class Message msg; // size: 0x8, address: 0x8097E090
// Range: 0x803ABE64 -> 0x803AC2B4
void OutfitLoader::CreatePath(class OutfitLoader * const this /* r27 */, class FilePath & p /* r28 */, const struct Category & cat /* r29 */, class Symbol & outfit /* r30 */) {
    // Local variables
    class DataNode ret; // r1+0x58
    class FilePathTracker _fptracker; // r1+0x6C
    class FilePathTracker _fptracker; // r1+0x60

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gNullStr;
    // -> static class Symbol none;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x803AC2B4 -> 0x803AC518
void OutfitLoader::MergeMiloFile(class OutfitLoader * const this /* r30 */, struct Category & cat /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x20
    struct LoaderDesc d; // r1+0x30
    class FilePathTracker _fptracker; // r1+0x24

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std40_List_node<Q212OutfitLoader10LoaderDesc>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std40_List_node<Q212OutfitLoader10LoaderDesc>; // size: 0x8, address: 0x808DE4C8
// Range: 0x803AC518 -> 0x803AC654
void OutfitLoader::NoneFinishedLoading(class OutfitLoader * const this /* r29 */, class Loader * l /* r30 */) {
    // References
    // -> unsigned char sDisableAll;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803AC654 -> 0x803AC728
void OutfitLoader::CheckDone(class OutfitLoader * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803AC728 -> 0x803AC8F0
void OutfitLoader::Save(class OutfitLoader * const this /* r27 */, class BinStream & d /* r28 */) {
    // Local variables
    int i; // r30
    const struct Category & cat; // r0
    int j; // r29

    // References
    // -> class FilePath sRoot;
}

// Range: 0x803AC8F0 -> 0x803AC8F4
void OutfitLoader::PostLoad() {}

// Range: 0x803AC8F4 -> 0x803AC950
void OutfitLoader::Load(class OutfitLoader * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x803AC950 -> 0x803AC9D4
void OutfitLoader::Copy(class OutfitLoader * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class OutfitLoader * s; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitLoader;
}

static class Symbol _s; // size: 0x4, address: 0x80A515F4
static class Symbol _s; // size: 0x4, address: 0x80A515FC
static class Symbol _s; // size: 0x4, address: 0x80A51604
static class Symbol _s; // size: 0x4, address: 0x80A5160C
static class Symbol _s; // size: 0x4, address: 0x80A51614
static class Symbol _s; // size: 0x4, address: 0x80A5161C
static class Symbol _s; // size: 0x4, address: 0x80A51624
static class Symbol _s; // size: 0x4, address: 0x80A5162C
static class Symbol _s; // size: 0x4, address: 0x80A51634
static class Symbol _s; // size: 0x4, address: 0x80A5163C
static class Symbol _s; // size: 0x4, address: 0x80A51644
static class Symbol _s; // size: 0x4, address: 0x80A5164C
static class Symbol _s; // size: 0x4, address: 0x80A51654
static class Symbol _s; // size: 0x4, address: 0x80A5165C
static class Symbol _s; // size: 0x4, address: 0x80A51664
// Range: 0x803AC9D4 -> 0x803ADD2C
class DataNode OutfitLoader::Handle(class OutfitLoader * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0xAC
    class MessageTimer _mt; // r1+0xE0
    class DataNode r; // r1+0xD8
    class DataNode r; // r1+0xD0
    class DataNode r; // r1+0xC8
    class DataNode r; // r1+0xC0
    class DataNode r; // r1+0xB8
    class DataNode _n; // r1+0xB0

    // References
    // -> class Debug TheDebug;
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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x803ADD2C -> 0x803ADEF0
class DataNode OutfitLoader::OnListCategories(class DataNode * n /* r28 */, class OutfitLoader * const this /* r29 */) {
    // Local variables
    class DataArray * cats; // r31
    int i; // r30
}

// Range: 0x803ADEF0 -> 0x803ADF7C
class DataNode OutfitLoader::OnStartLoad(class OutfitLoader * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x803ADF7C -> 0x803ADF8C
class DataNode OutfitLoader::OnMergeBack() {}

// Range: 0x803ADF8C -> 0x803AE0B0
class DataNode OutfitLoader::OnSelectAll(class OutfitLoader * const this /* r30 */, class DataArray * arr /* r31 */) {
    // Local variables
    int s; // r1+0xC
    int i; // r31
}

struct FileStat {
    // total size: 0x14
    unsigned int st_mode; // offset 0x0, size 0x4
    unsigned int st_size; // offset 0x4, size 0x4
    unsigned long st_ctime; // offset 0x8, size 0x4
    unsigned long st_atime; // offset 0xC, size 0x4
    unsigned long st_mtime; // offset 0x10, size 0x4
};
// Range: 0x803AE0B0 -> 0x803AE210
class DataNode OutfitLoader::OnValidate(class OutfitLoader * const this /* r28 */) {
    // Local variables
    int i; // r31
    struct Category & cat; // r30
    int j; // r29
    class FilePath p; // r1+0x10
    struct FileStat fstat; // r1+0x1C

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__8FilePath;
}

static class OutfitLoader * gLoader; // size: 0x4, address: 0x80A51668
static class Symbol _s; // size: 0x4, address: 0x80A51670
static class Symbol _s; // size: 0x4, address: 0x80A51678
static class Symbol _s; // size: 0x4, address: 0x80A51680
static class Symbol _s; // size: 0x4, address: 0x80A51688
static class Symbol _s; // size: 0x4, address: 0x80A51690
static class Symbol _s; // size: 0x4, address: 0x80A51698
// Range: 0x803AE210 -> 0x803AE6A0
unsigned char PropSync(struct Category & _me /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r27 */, enum PropOp _op /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class OutfitLoader * gLoader;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A516A0
static class Symbol _s; // size: 0x4, address: 0x80A516A8
static class Symbol _s; // size: 0x4, address: 0x80A516B0
static class Symbol _s; // size: 0x4, address: 0x80A516B8
// Range: 0x803AE6A0 -> 0x803AE904
unsigned char OutfitLoader::SyncProperty(class OutfitLoader * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> unsigned char sDisableAll;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class OutfitLoader * gLoader;
}

// Range: 0x803AE904 -> 0x803AF418
unsigned char PropSync(class vector & v /* r27 */, class DataNode & n /* r29 */, class DataArray * prop /* r24 */, int i /* r26 */, enum PropOp op /* r25 */) {
    // Local variables
    struct Category * it; // r28
    struct Category tmp; // r1+0x60

    // References
    // -> struct [anonymous] __vt__36ObjPtrList<Q23Hmx6Object,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class NoneLoader : public Loader {
    // total size: 0x18
protected:
    class OutfitLoader * mOutfit; // offset 0x14, size 0x4
};
// Range: 0x803AF418 -> 0x803AF470
void NoneLoader::PollLoading(class NoneLoader * const this /* r31 */) {}

// Range: 0x803AF470 -> 0x803AF4D0
void * NoneLoader::~NoneLoader(class NoneLoader * const this /* r30 */) {}

// Range: 0x803AF4D0 -> 0x803AF4D8
unsigned char NoneLoader::IsLoaded() {}

struct {
    // total size: 0x14
} __vt__10NoneLoader; // size: 0x14, address: 0x808DE890
struct {
    // total size: 0x8
} __RTTI__10NoneLoader; // size: 0x8, address: 0x808DE8C0
struct {
    // total size: 0x84
} __vt__12OutfitLoader; // size: 0x84, address: 0x808DE928
struct {
    // total size: 0x10
} __vt__11MergeFilter; // size: 0x10, address: 0x808DEA38
struct {
    // total size: 0x14
} __vt__Q29DirLoader8Callback; // size: 0x14, address: 0x808DEE18
struct {
    // total size: 0x8
} __RTTI__PPQ212OutfitLoader8Category; // size: 0x8, address: 0x808DEF30
struct {
    // total size: 0x8
} __RTTI__PQ212OutfitLoader6Outfit; // size: 0x8, address: 0x808DEF50
struct {
    // total size: 0x8
} __RTTI__PQ212OutfitLoader8Category; // size: 0x8, address: 0x808DEF78

