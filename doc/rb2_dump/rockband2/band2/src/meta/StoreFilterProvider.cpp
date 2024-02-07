/*
    Compile unit: C:\rockband2\band2\src\meta\StoreFilterProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8017CF28 -> 0x8017EF74
*/
static class Symbol sub; // size: 0x4, address: 0x80A4CA8C
static class Symbol options; // size: 0x4, address: 0x80A4CA94
class StoreFilter : public Object {
    // total size: 0x38
    class DataArray * mData; // offset 0x28, size 0x4
    class vector mSubFilters; // offset 0x2C, size 0xC
};
class SubStoreFilter {
    // total size: 0x10
public:
    class Symbol mFilterName; // offset 0x0, size 0x4
    class vector mOptions; // offset 0x4, size 0xC
};
// Range: 0x8017CF28 -> 0x8017D24C
void * StoreFilter::StoreFilter(class StoreFilter * const this /* r29 */, class DataArray * d /* r30 */) {
    // Local variables
    class SubStoreFilter ssf; // r1+0x50
    int i; // r28

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P6Symbol;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> static class Symbol options;
    // -> static class Symbol sub;
    // -> struct [anonymous] __vt__11StoreFilter;
}

class StlNodeAlloc {
    // total size: 0x1
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class SubStoreFilter * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class SubStoreFilter * _M_start; // offset 0x0, size 0x4
    class SubStoreFilter * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x8017D24C -> 0x8017D28C
class Symbol StoreFilter::FilterName() {}

// Range: 0x8017D28C -> 0x8017D2A0
class vector & StoreFilter::SubOptions() {}

// Range: 0x8017D2A0 -> 0x8017D2B8
int StoreFilter::NumSubFilters() {}

// Range: 0x8017D2B8 -> 0x8017D600
void StoreFilter::Filter(const class StoreFilter * const this /* r26 */, const class vector & all_offers /* r27 */, const class SelectedFilter & selected /* r28 */, class vector & filtered /* r29 */) {
    // Local variables
    const class StoreOffer * s; // r31

    // References
    // -> struct [anonymous] __vt__10StoreOffer;
    // -> struct [anonymous] __vt__5Offer;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6ObjRef>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__9TypeProps;
    // -> struct [anonymous] __vt__Q23Hmx6Object;
}

static class Symbol sorts; // size: 0x4, address: 0x80A4CA9C
// Range: 0x8017D68C -> 0x8017D80C
void StoreFilter::GetSorts(const class StoreFilter * const this /* r26 */, const class vector & all /* r30 */, class vector & available /* r31 */) {
    // Local variables
    class DataArray * s; // r28
    int i; // r27
    class StoreSort * const * it; // r26

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol sorts;
}

static class Symbol sorts; // size: 0x4, address: 0x80A4CAA4
// Range: 0x8017D80C -> 0x8017D88C
unsigned char StoreFilter::AllowSortToggle(const class StoreFilter * const this /* r31 */) {
    // References
    // -> static class Symbol sorts;
}

static class Symbol allow_shortcut; // size: 0x4, address: 0x80A4CAAC
// Range: 0x8017D88C -> 0x8017D910
unsigned char StoreFilter::AllowShortcut(const class StoreFilter * const this /* r31 */) {
    // References
    // -> static class Symbol allow_shortcut;
}

static class Symbol sort_difficulty_part; // size: 0x4, address: 0x80A4CAB4
// Range: 0x8017D910 -> 0x8017D98C
class Symbol StoreFilter::SortDifficultyPart(const class StoreFilter * const this /* r31 */) {
    // References
    // -> static class Symbol sort_difficulty_part;
}

static class Symbol show_new_release; // size: 0x4, address: 0x80A4CABC
// Range: 0x8017D98C -> 0x8017DA10
unsigned char StoreFilter::ShowNewRelease(const class StoreFilter * const this /* r31 */) {
    // References
    // -> static class Symbol show_new_release;
}

static class Symbol include; // size: 0x4, address: 0x80A4CAC4
// Range: 0x8017DA10 -> 0x8017DC14
unsigned char StoreFilter::IncludeOffer(const class StoreFilter * const this /* r31 */, const class StoreOffer & offer /* r29 */, const class SelectedFilter & selected /* r30 */) {
    // Local variables
    class DataArrayPtr args; // r1+0x28

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol include;
}

// Range: 0x8017DC14 -> 0x8017DC54
unsigned char __eq(class Symbol & rhs /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4CACC
static class Symbol _s; // size: 0x4, address: 0x80A4CAD4
// Range: 0x8017DC54 -> 0x8017E0B8
class DataNode StoreFilter::Handle(class StoreFilter * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class FilterProvider : public ListProvider, public Object {
    // total size: 0x4C
    const class vector & mAllOffers; // offset 0x2C, size 0x4
    class vector mListFilters; // offset 0x30, size 0xC
    const class vector & mFilters; // offset 0x3C, size 0x4
    const class SelectedFilter & mSelectedFilter; // offset 0x40, size 0x4
    int mDepth; // offset 0x44, size 0x4
    class RndMat * mBgMat; // offset 0x48, size 0x4
};
// Range: 0x8017E0B8 -> 0x8017E0EC
class StoreFilter & FilterProvider::CurFilter() {}

// Range: 0x8017E0EC -> 0x8017E238
void FilterProvider::SetDepth(class FilterProvider * const this /* r31 */, int depth /* r30 */) {
    // Local variables
    const class StoreFilter * i; // r30
}

// Range: 0x8017E238 -> 0x8017E31C
void FilterProvider::InitData(class FilterProvider * const this /* r28 */, class RndDir * dir /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

static class Symbol filter; // size: 0x4, address: 0x80A4CADC
static class Symbol store_coming_soon; // size: 0x4, address: 0x80A4CAE4
// Range: 0x8017E31C -> 0x8017E460
char * FilterProvider::Text(const class FilterProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // Local variables
    const char * filter; // r30

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol store_coming_soon;
    // -> static class Symbol filter;
}

static class Symbol bg; // size: 0x4, address: 0x80A4CAEC
// Range: 0x8017E460 -> 0x8017E4FC
class RndMat * FilterProvider::Mat(const class FilterProvider * const this /* r30 */, class Symbol & slot /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol bg;
}

// Range: 0x8017E4FC -> 0x8017E50C
class Symbol FilterProvider::DataSymbol() {}

// Range: 0x8017E50C -> 0x8017E938
unsigned char FilterProvider::IsActive(const class FilterProvider * const this /* r30 */, int data /* r28 */) {
    // Local variables
    class Symbol filter; // r1+0x68
    class SelectedFilter potential; // r1+0x8C
    class vector filtered; // r1+0x80

    // References
    // -> struct [anonymous] __RTTI__P6Symbol;
    // -> struct [anonymous] __vt__14SelectedFilter;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6ObjRef>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__9TypeProps;
    // -> struct [anonymous] __vt__Q23Hmx6Object;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8017EA0C -> 0x8017EA24
int FilterProvider::NumData() {}

// Range: 0x8017EA24 -> 0x8017EAAC
class StoreFilter & FilterProvider::FindFilter(const class FilterProvider * const this /* r30 */) {
    // Local variables
    const class StoreFilter * f; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4CAF4
static class Symbol _s; // size: 0x4, address: 0x80A4CAFC
// Range: 0x8017EAAC -> 0x8017EF74
class DataNode FilterProvider::Handle(class FilterProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xA0
} __vt__14FilterProvider; // size: 0xA0, address: 0x8089A1B8
struct {
    // total size: 0x8
} __RTTI__14FilterProvider; // size: 0x8, address: 0x8089A288
struct {
    // total size: 0x54
} __vt__11StoreFilter; // size: 0x54, address: 0x8089A290
struct {
    // total size: 0x8
} __RTTI__11StoreFilter; // size: 0x8, address: 0x8089A308
struct {
    // total size: 0x8
} __RTTI__P14SubStoreFilter; // size: 0x8, address: 0x8089A3D8
struct {
    // total size: 0x8
} __RTTI__P10StoreOffer; // size: 0x8, address: 0x8089A408

