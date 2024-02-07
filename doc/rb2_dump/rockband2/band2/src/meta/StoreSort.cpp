/*
    Compile unit: C:\rockband2\band2\src\meta\StoreSort.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80191030 -> 0x8019275C
*/
static class Message init; // size: 0x8, address: 0x80979EC0
// Range: 0x80191030 -> 0x80191174
void StoreSort::Init(class StoreSort * const this /* r31 */) {
    // References
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
}

static class Message cmp; // size: 0x8, address: 0x80979ED8
// Range: 0x80191174 -> 0x80191544
unsigned char StoreSort::__cl(class StoreSort * const this /* r28 */, const class Offer & lhs /* r29 */, const class Offer & rhs /* r30 */) {
    // Local variables
    unsigned char invert; // r31
    class Symbol cmp_type; // r1+0x1C
    class Offer * p_lhs; // [invalid]
    class Offer * r_lhs; // [invalid]
    int ret; // r27

    // References
    // -> static class Message cmp;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

static class Symbol artist; // size: 0x4, address: 0x80A4CF64
static class Symbol name; // size: 0x4, address: 0x80A4CF6C
static class Symbol pack_name; // size: 0x4, address: 0x80A4CF74
static class Symbol year_released; // size: 0x4, address: 0x80A4CF7C
static class Symbol decade; // size: 0x4, address: 0x80A4CF84
static class Symbol rank; // size: 0x4, address: 0x80A4CF8C
static class Symbol genre; // size: 0x4, address: 0x80A4CF94
static class Symbol origin; // size: 0x4, address: 0x80A4CF9C
static class Symbol pack; // size: 0x4, address: 0x80A4CFA4
static class DataArray * oneArg; // size: 0x4, address: 0x80A4CFA8
static class DataArray * twoArgs; // size: 0x4, address: 0x80A4CFB0
enum StoreSortType {
    kSTArtist = 0,
    kSTPackName = 1,
    kSTName = 2,
    kSTYearReleased = 3,
    kSTDecade = 4,
    kSTRank = 5,
    kSTGenre = 6,
    kSTOrigin = 7,
    kSTLeftSide = 8,
};
// Range: 0x80191544 -> 0x80191D4C
class DataNode StoreSort::OnCmp(class StoreSort * const this /* r25 */, class DataArray * a /* r26 */) {
    // Local variables
    class Offer * lhs; // r29
    class Offer * rhs; // r28
    int i; // r27
    int r; // r23
    enum StoreSortType t; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__5Offer;
    // -> static class DataArray * twoArgs;
    // -> static class DataArray * oneArg;
    // -> static class Symbol pack;
    // -> static class Symbol origin;
    // -> static class Symbol genre;
    // -> static class Symbol rank;
    // -> static class Symbol decade;
    // -> static class Symbol year_released;
    // -> static class Symbol pack_name;
    // -> static class Symbol name;
    // -> static class Symbol artist;
}

static class Symbol cmp_song_to_song; // size: 0x4, address: 0x80A4CFB8
static class Symbol cmp_song_to_album; // size: 0x4, address: 0x80A4CFC0
static class Symbol cmp_song_to_pack; // size: 0x4, address: 0x80A4CFC8
static class Symbol cmp_album_to_album; // size: 0x4, address: 0x80A4CFD0
static class Symbol cmp_album_to_pack; // size: 0x4, address: 0x80A4CFD8
static class Symbol cmp_pack_to_pack; // size: 0x4, address: 0x80A4CFE0
static class Symbol song; // size: 0x4, address: 0x80A4CFE8
static class Symbol album; // size: 0x4, address: 0x80A4CFF0
static class Symbol pack; // size: 0x4, address: 0x80A4CFF8
// Range: 0x80191D4C -> 0x80191F84
class Symbol StoreSort::FindOfferCmp(const class Offer & lhs /* r29 */, const class Offer & rhs /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> static class Symbol pack;
    // -> static class Symbol album;
    // -> static class Symbol song;
    // -> static class Symbol cmp_pack_to_pack;
    // -> static class Symbol cmp_album_to_pack;
    // -> static class Symbol cmp_album_to_album;
    // -> static class Symbol cmp_song_to_pack;
    // -> static class Symbol cmp_song_to_album;
    // -> static class Symbol cmp_song_to_song;
}

// Range: 0x80191F84 -> 0x80192004
int StoreSort::AlphaCmp(class Offer * lhs /* r28 */, class DataArray * fields /* r29 */, unsigned char skip_the /* r30 */) {}

// Range: 0x80192004 -> 0x801920A4
int StoreSort::NumericCmp(class Offer * rhs /* r29 */, class DataArray * fields /* r30 */, unsigned char ascending /* r31 */) {
    // Local variables
    float f_lhs; // f0
    float f_rhs; // f0
}

static class Symbol decade; // size: 0x4, address: 0x80A4D000
// Range: 0x801920A4 -> 0x801921A8
int StoreSort::DecadeCmp(class Offer * lhs /* r31 */, class Offer * rhs /* r29 */, class DataArray * fields /* r30 */) {
    // Local variables
    const char * ldc; // r0
    const char * rdc; // r0
    int ld; // r5
    int rd; // r3

    // References
    // -> static class Symbol decade;
}

static class Symbol download; // size: 0x4, address: 0x80A4D008
static class Symbol rb2_icon; // size: 0x4, address: 0x80A4D010
static class Symbol rb1_icon; // size: 0x4, address: 0x80A4D018
// Range: 0x801921A8 -> 0x80192300
int StoreSort::OriginCmp(class Offer * lhs /* r29 */, class Offer * rhs /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol rb1_icon;
    // -> static class Symbol rb2_icon;
    // -> static class Symbol download;
}

static class Symbol _s; // size: 0x4, address: 0x80A4D020
// Range: 0x80192300 -> 0x801926FC
class DataNode StoreSort::Handle(class StoreSort * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x801926FC -> 0x8019275C
unsigned char __eq(class Symbol & rhs /* r30 */) {}

struct {
    // total size: 0x54
} __vt__9StoreSort; // size: 0x54, address: 0x8089C838
struct {
    // total size: 0x8
} __RTTI__9StoreSort; // size: 0x8, address: 0x8089C8B0

