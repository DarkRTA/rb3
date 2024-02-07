/*
    Compile unit: C:\rockband2\band2\src\meta\OutfitProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801378E0 -> 0x80138D70
*/
// Range: 0x801378E0 -> 0x8013798C
void * OutfitProvider::OutfitProvider(class OutfitProvider * const this /* r28 */, class Symbol & gender /* r29 */, class DataArray * category /* r30 */, class Symbol & catName /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14OutfitProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x8013798C -> 0x801379A4
int OutfitProvider::NumData() {}

static class Symbol disabled; // size: 0x4, address: 0x80A4BE84
// Range: 0x801379A4 -> 0x80137A2C
class Symbol OutfitProvider::State(const class OutfitProvider * const this /* r29 */, int data /* r30 */, class Symbol & component_state /* r31 */) {
    // References
    // -> static class Symbol disabled;
}

// Range: 0x80137A2C -> 0x80137A34
class Symbol OutfitProvider::Gender() {}

// Range: 0x80137A34 -> 0x80137A3C
class Symbol OutfitProvider::Category() {}

// Range: 0x80137A3C -> 0x80137A7C
class Symbol OutfitProvider::CharCategory() {}

// Range: 0x80137A7C -> 0x80137B1C
int OutfitProvider::Cost(const class OutfitProvider * const this /* r30 */, class Symbol & outfit /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80137B1C -> 0x80137BBC
class Symbol OutfitProvider::Token(const class OutfitProvider * const this /* r30 */, class Symbol & outfit /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol closet; // size: 0x4, address: 0x80A4BE8C
// Range: 0x80137BBC -> 0x80137C40
unsigned char OutfitProvider::IsClosetCategory(const class OutfitProvider * const this /* r31 */) {
    // References
    // -> static class Symbol closet;
}

static class Symbol none; // size: 0x4, address: 0x80A4BE94
// Range: 0x80137C40 -> 0x80137CB4
class Symbol OutfitProvider::NoneOutfit(const class OutfitProvider * const this /* r31 */) {
    // Local variables
    class Symbol noneOutfit; // r1+0xC

    // References
    // -> const char * gNullStr;
    // -> static class Symbol none;
}

static class Symbol cam; // size: 0x4, address: 0x80A4BE9C
// Range: 0x80137CB4 -> 0x80137D2C
char * OutfitProvider::CamBaseName(const class OutfitProvider * const this /* r31 */) {
    // Local variables
    const char * base_name; // r1+0x10

    // References
    // -> static class Symbol cam;
}

// Range: 0x80137D2C -> 0x801386D8
void OutfitProvider::SetOutfits(class OutfitProvider * const this /* r18 */, class Symbol & genre /* r19 */, class TourCharLocal * tc /* r20 */, unsigned char closet /* r21 */, unsigned char creator /* r22 */) {
    // Local variables
    class DataArray * outfits; // r27
    int money; // r0
    class DataArray * groups; // r28
    int i; // r27
    struct Outfit o; // r1+0xF0
    unsigned char has_outfit; // r0
    unsigned char allow_none; // r1+0x3A
    unsigned char has_unlocks; // r1+0x39
    const char * filter; // r26
    class DataArray * f; // r24
    int i; // r25
    class DataArray * outfit_genre; // r24
    class DataArray * exclude; // r23
    class DataArray * shop_category_data; // r28
    class DataArray * c; // r23
    class Symbol name; // r1+0xD8
    unsigned char has_outfit; // r23
    unsigned char doFilter; // r24
    class DataArray * f; // r17
    struct Outfit o; // r1+0xE0
    class DataArray * cost; // r17
    class DataArray * token; // r17
    unsigned char sort; // r1+0x38

    // References
    // -> unsigned char sUnlockAll;
    // -> const char * gNullStr;
}

struct OutfitCmp {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x801386D8 -> 0x801386E0
void OutfitProvider::SetShowText() {}

static class Symbol _s; // size: 0x4, address: 0x80A4BEA4
static class Symbol _s; // size: 0x4, address: 0x80A4BEAC
static class Symbol _s; // size: 0x4, address: 0x80A4BEB4
static class Symbol _s; // size: 0x4, address: 0x80A4BEBC
// Range: 0x801386E0 -> 0x80138D70
class DataNode OutfitProvider::Handle(class OutfitProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x44
    class MessageTimer _mt; // r1+0x50
    class DataNode _n; // r1+0x48

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

struct {
    // total size: 0x9C
} __vt__14OutfitProvider; // size: 0x9C, address: 0x80891C70
struct {
    // total size: 0x8
} __RTTI__14OutfitProvider; // size: 0x8, address: 0x80891D38
struct {
    // total size: 0x8
} __RTTI__PQ214OutfitProvider6Outfit; // size: 0x8, address: 0x80891DB0

