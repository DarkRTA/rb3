/*
    Compile unit: C:\rockband2\band2\src\meta\StoreOfferProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801846C8 -> 0x80186BA4
*/
class StoreOfferProvider : public OfferProvider {
    // total size: 0x74
    class vector & mAllOffers; // offset 0x48, size 0x4
    class FilterProvider & mFilterProvider; // offset 0x4C, size 0x4
    const class SelectedFilter & mSelectedFilter; // offset 0x50, size 0x4
    class vector mFilteredOffers; // offset 0x54, size 0xC
    class vector mElements; // offset 0x60, size 0xC
    class RndMat * mGroupBgMat; // offset 0x6C, size 0x4
    class RndMat * mSongBgMat; // offset 0x70, size 0x4
};
// Range: 0x801846C8 -> 0x80184764
void * StoreOfferProvider::StoreOfferProvider(class StoreOfferProvider * const this /* r28 */, class vector & all_offers /* r29 */, class FilterProvider & filter_provider /* r30 */, const class SelectedFilter & selected_filter /* r31 */) {
    // References
    // -> struct [anonymous] __vt__18StoreOfferProvider;
}

class StlNodeAlloc {
    // total size: 0x1
};
struct Element {
    // total size: 0xC
    const class StoreOffer * mOffer; // offset 0x0, size 0x4
    class Symbol mGroupHeading; // offset 0x4, size 0x4
    unsigned char mCover; // offset 0x8, size 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Element * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Element * * _M_start; // offset 0x0, size 0x4
    struct Element * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x80184764 -> 0x80184924
void * StoreOfferProvider::~StoreOfferProvider(class StoreOfferProvider * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__18StoreOfferProvider;
}

static class Symbol group; // size: 0x4, address: 0x80A4CC2C
static class Symbol famousby; // size: 0x4, address: 0x80A4CC34
static class Symbol famousby_group; // size: 0x4, address: 0x80A4CC3C
static class Symbol album; // size: 0x4, address: 0x80A4CC44
static class Symbol song; // size: 0x4, address: 0x80A4CC4C
static class Symbol cost; // size: 0x4, address: 0x80A4CC54
static class Symbol new_sym; // size: 0x4, address: 0x80A4CC5C
static class Symbol purchased; // size: 0x4, address: 0x80A4CC64
static class Symbol pack; // size: 0x4, address: 0x80A4CC6C
static class Symbol store_famous_by; // size: 0x4, address: 0x80A4CC74
static class Symbol new_release; // size: 0x4, address: 0x80A4CC7C
static class Symbol store_new; // size: 0x4, address: 0x80A4CC84
static class Symbol store_purchased; // size: 0x4, address: 0x80A4CC8C
static class Symbol store_downloaded; // size: 0x4, address: 0x80A4CC94
// Range: 0x80184924 -> 0x80184E00
char * StoreOfferProvider::Text(const class StoreOfferProvider * const this /* r28 */, int data /* r30 */, class Symbol & slot /* r29 */) {
    // Local variables
    const struct Element * e; // r27
    const class StoreOffer * offer; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol store_downloaded;
    // -> static class Symbol store_purchased;
    // -> const char * gNullStr;
    // -> static class Symbol store_new;
    // -> static class Symbol new_release;
    // -> static class Symbol store_famous_by;
    // -> static class Symbol pack;
    // -> static class Symbol purchased;
    // -> static class Symbol new_sym;
    // -> static class Symbol cost;
    // -> static class Symbol song;
    // -> static class Symbol album;
    // -> static class Symbol famousby_group;
    // -> static class Symbol famousby;
    // -> static class Symbol group;
}

// Range: 0x80184E00 -> 0x80184E20
unsigned char StoreOfferProvider::IsActive() {}

// Range: 0x80184E20 -> 0x80184E88
class Symbol StoreOfferProvider::DataSymbol() {
    // References
    // -> const char * gNullStr;
}

static class Symbol group_bg; // size: 0x4, address: 0x80A4CC9C
static class Symbol album_bg; // size: 0x4, address: 0x80A4CCA4
static class Symbol song_bg; // size: 0x4, address: 0x80A4CCAC
static class Symbol album; // size: 0x4, address: 0x80A4CCB4
static class Symbol pack; // size: 0x4, address: 0x80A4CCBC
static class Symbol song; // size: 0x4, address: 0x80A4CCC4
// Range: 0x80184E88 -> 0x801850D4
class RndMat * StoreOfferProvider::Mat(const class StoreOfferProvider * const this /* r30 */, int data /* r28 */, class Symbol & slot /* r29 */) {
    // Local variables
    const struct Element * e; // r4
    const class StoreOffer * o; // r29
    const class StoreOffer * o; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol song;
    // -> static class Symbol pack;
    // -> static class Symbol album;
    // -> static class Symbol song_bg;
    // -> static class Symbol album_bg;
    // -> static class Symbol group_bg;
}

static class Symbol shortcut_group; // size: 0x4, address: 0x80A4CCCC
// Range: 0x801850D4 -> 0x80185364
void StoreOfferProvider::GetRepresentedShortcuts(const class StoreOfferProvider * const this /* r30 */, class vector & rep /* r31 */) {
    // Local variables
    class DataArray * a; // r28
    const class StoreOffer * s; // r27
    class Symbol shortcut; // r1+0x30
    int i; // r27
    struct Element * e; // r28

    // References
    // -> const char * gNullStr;
    // -> static class Symbol shortcut_group;
}

// Range: 0x80185364 -> 0x801853AC
void StoreOfferProvider::getSorts(const class vector & all /* r30 */, class vector & available /* r31 */) {
    // Local variables
    const class StoreFilter & f; // r0
}

static class Symbol shortcut_group; // size: 0x4, address: 0x80A4CCD4
// Range: 0x801853AC -> 0x80185528
class Symbol StoreOfferProvider::PosToShortcut(const class StoreOfferProvider * const this /* r30 */, int pos /* r31 */) {
    // Local variables
    struct Element * e; // r29
    class DataArray * a; // r5

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol shortcut_group;
}

static class Symbol shortcut_group; // size: 0x4, address: 0x80A4CCDC
// Range: 0x80185528 -> 0x801856A8
int StoreOfferProvider::ShortcutToPos(const class StoreOfferProvider * const this /* r28 */, class Symbol & group /* r29 */) {
    // Local variables
    class DataArray * a; // r31
    class Symbol shortcut; // r1+0x10
    int i; // r30
    const class Offer * offer; // r4

    // References
    // -> const char * gNullStr;
    // -> static class Symbol shortcut_group;
}

// Range: 0x801856A8 -> 0x801856F8
class StoreOffer * StoreOfferProvider::FindOffer(const class StoreOfferProvider * const this /* r31 */) {
    // Local variables
    class StoreOffer * i; // r0
}

static class Symbol pack; // size: 0x4, address: 0x80A4CCE4
// Range: 0x801856F8 -> 0x80185854
class StoreOffer * StoreOfferProvider::FindPack(const class StoreOfferProvider * const this /* r30 */, const class StoreOffer * song /* r31 */) {
    // Local variables
    class StoreOffer * i; // r29

    // References
    // -> static class Symbol pack;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

static class Symbol album; // size: 0x4, address: 0x80A4CCEC
// Range: 0x80185854 -> 0x801859B0
class StoreOffer * StoreOfferProvider::FindAlbum(const class StoreOfferProvider * const this /* r30 */, const class StoreOffer * song /* r31 */) {
    // Local variables
    class StoreOffer * i; // r29

    // References
    // -> static class Symbol album;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

static class Symbol song; // size: 0x4, address: 0x80A4CCF4
static class Symbol album; // size: 0x4, address: 0x80A4CCFC
static class Symbol pack; // size: 0x4, address: 0x80A4CD04
// Range: 0x801859B0 -> 0x80185C44
unsigned char StoreOfferProvider::ShowBrowserPurchased(const class StoreOfferProvider * const this /* r29 */, const class StoreOffer * o /* r30 */) {
    // Local variables
    class StoreOffer * a; // r28
    class StoreOffer * p; // r28
    int i; // r27
    class DataNode & song; // r0
    class StoreOffer * s; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol pack;
    // -> static class Symbol album;
    // -> static class Symbol song;
}

static class Symbol browser_group; // size: 0x4, address: 0x80A4CD0C
static class Symbol browser_cover; // size: 0x4, address: 0x80A4CD14
static class Symbol album; // size: 0x4, address: 0x80A4CD1C
static class Symbol pack; // size: 0x4, address: 0x80A4CD24
// Range: 0x80185C44 -> 0x8018630C
void StoreOfferProvider::applySort(class StoreOfferProvider * const this /* r27 */) {
    // Local variables
    struct SortCmp cmp; // r1+0x70
    struct Element * cur_group; // r30
    class StoreOffer * s; // r29
    class DataArrayPtr args; // r1+0x90
    class DataArray * a; // r0
    class Symbol group; // r1+0x6C
    unsigned char cover; // r28
    class DataArray * c; // r4
    struct Element * group_element; // r1+0x68
    struct Element * offer_element; // r1+0x64
    struct Element * * e; // r28
    const class StoreOffer * o; // r29
    int i; // r26
    class DataNode & song; // r30
    const class StoreOffer * sit; // r25
    struct Element * s; // r1+0x60

    // References
    // -> static class Symbol pack;
    // -> static class Symbol album;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol browser_cover;
    // -> static class Symbol browser_group;
    // -> class Debug TheDebug;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
static class Symbol _s; // size: 0x4, address: 0x80A4CD2C
static class Symbol _s; // size: 0x4, address: 0x80A4CD34
static class Symbol _s; // size: 0x4, address: 0x80A4CD3C
static class Symbol _s; // size: 0x4, address: 0x80A4CD44
static class Symbol _s; // size: 0x4, address: 0x80A4CD4C
static class Symbol _s; // size: 0x4, address: 0x80A4CD54
// Range: 0x8018630C -> 0x80186BA4
class DataNode StoreOfferProvider::Handle(class StoreOfferProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x48
    class MessageTimer _mt; // r1+0x58
    class DataNode _n; // r1+0x50

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10StoreOffer;
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

struct {
    // total size: 0xC0
} __vt__18StoreOfferProvider; // size: 0xC0, address: 0x8089B258
struct {
    // total size: 0x8
} __RTTI__18StoreOfferProvider; // size: 0x8, address: 0x8089B350
struct {
    // total size: 0x8
} __RTTI__PPQ218StoreOfferProvider7Element; // size: 0x8, address: 0x8089B490
struct _OKToMemCpy {
    // total size: 0x1
};

