/*
    Compile unit: C:\rockband2\band2\src\meta\StoreOffer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80182CBC -> 0x801845B0
*/
class Symbol type; // size: 0x4, address: 0x80A4CB3C
static class Symbol id; // size: 0x4, address: 0x80A4CB44
static class Symbol index; // size: 0x4, address: 0x80A4CB4C
static class Symbol game_code; // size: 0x4, address: 0x80A4CB54
static class Symbol price; // size: 0x4, address: 0x80A4CB5C
// Range: 0x80182CBC -> 0x80182E90
void * StoreOffer::StoreOffer(class StoreOffer * const this /* r30 */, class DataArray * data /* r31 */) {
    // References
    // -> static class Symbol price;
    // -> static class Symbol game_code;
    // -> static class Symbol index;
    // -> static class Symbol id;
    // -> struct [anonymous] __vt__10StoreOffer;
}

static class Symbol name; // size: 0x4, address: 0x80A4CB64
static class Symbol song; // size: 0x4, address: 0x80A4CB6C
// Range: 0x80182E90 -> 0x80182FAC
char * StoreOffer::OfferName(const class StoreOffer * const this /* r29 */) {
    // References
    // -> static class Symbol song;
    // -> static class Symbol name;
}

static class Symbol description; // size: 0x4, address: 0x80A4CB74
// Range: 0x80182FAC -> 0x80183024
char * StoreOffer::Description(const class StoreOffer * const this /* r31 */) {
    // References
    // -> static class Symbol description;
}

static class Symbol new_release; // size: 0x4, address: 0x80A4CB7C
// Range: 0x80183024 -> 0x801830A8
unsigned char StoreOffer::IsNewRelease(const class StoreOffer * const this /* r31 */) {
    // References
    // -> static class Symbol new_release;
}

static class Symbol cover; // size: 0x4, address: 0x80A4CB84
// Range: 0x801830A8 -> 0x80183154
unsigned char StoreOffer::IsCover(const class StoreOffer * const this /* r31 */) {
    // References
    // -> static class Symbol cover;
}

static class Symbol test; // size: 0x4, address: 0x80A4CB8C
// Range: 0x80183154 -> 0x801831E8
unsigned char StoreOffer::IsTest(const class StoreOffer * const this /* r31 */) {
    // Local variables
    class DataArray * t; // r31

    // References
    // -> static class Symbol test;
}

static class Symbol year_released; // size: 0x4, address: 0x80A4CB94
// Range: 0x801831E8 -> 0x80183260
int StoreOffer::YearReleased(const class StoreOffer * const this /* r31 */) {
    // References
    // -> static class Symbol year_released;
}

static class Symbol genre; // size: 0x4, address: 0x80A4CB9C
// Range: 0x80183260 -> 0x801832D8
char * StoreOffer::Genre(const class StoreOffer * const this /* r31 */) {
    // References
    // -> static class Symbol genre;
}

// Range: 0x801832D8 -> 0x801832E8
char * StoreOffer::CostStr(const class StoreOffer * const this /* r4 */) {}

static class Symbol songs; // size: 0x4, address: 0x80A4CBA4
// Range: 0x801832E8 -> 0x80183410
int StoreOffer::NumSongs(const class StoreOffer * const this /* r30 */) {
    // References
    // -> static class Symbol songs;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

static class Symbol songs; // size: 0x4, address: 0x80A4CBAC
// Range: 0x80183410 -> 0x80183488
class DataNode & StoreOffer::Song(const class StoreOffer * const this /* r30 */, int i /* r31 */) {
    // References
    // -> static class Symbol songs;
}

static class Symbol songs; // size: 0x4, address: 0x80A4CBB4
// Range: 0x80183488 -> 0x801836B0
unsigned char StoreOffer::HasSong(const class StoreOffer * const this /* r29 */, const class StoreOffer * o /* r30 */) {
    // Local variables
    class DataArray * s; // r29
    int i; // r31
    class DataNode & song; // r27

    // References
    // -> static class Symbol songs;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

static class Symbol titles; // size: 0x4, address: 0x80A4CBBC
// Range: 0x801836B0 -> 0x80183788
unsigned char StoreOffer::ValidTitle(const class StoreOffer * const this /* r30 */) {
    // Local variables
    class DataArray * t; // r31
    int i; // r30

    // References
    // -> static class Symbol titles;
}

static class Symbol _s; // size: 0x4, address: 0x80A4CBC4
static class Symbol _s; // size: 0x4, address: 0x80A4CBCC
static class Symbol _s; // size: 0x4, address: 0x80A4CBD4
static class Symbol _s; // size: 0x4, address: 0x80A4CBDC
static class Symbol _s; // size: 0x4, address: 0x80A4CBE4
static class Symbol _s; // size: 0x4, address: 0x80A4CBEC
static class Symbol _s; // size: 0x4, address: 0x80A4CBF4
static class Symbol _s; // size: 0x4, address: 0x80A4CBFC
static class Symbol _s; // size: 0x4, address: 0x80A4CC04
static class Symbol _s; // size: 0x4, address: 0x80A4CC0C
static class Symbol _s; // size: 0x4, address: 0x80A4CC14
static class Symbol _s; // size: 0x4, address: 0x80A4CC1C
static class Symbol _s; // size: 0x4, address: 0x80A4CC24
// Range: 0x80183788 -> 0x801845B0
class DataNode StoreOffer::Handle(class StoreOffer * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x5C
    class MessageTimer _mt; // r1+0x78
    class DataNode _n; // r1+0x60

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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x6C
} __vt__10StoreOffer; // size: 0x6C, address: 0x8089AE58
struct {
    // total size: 0x8
} __RTTI__10StoreOffer; // size: 0x8, address: 0x8089AEF0

