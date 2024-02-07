/*
    Compile unit: C:\rockband2\band2\src\meta\TourWorldProviders.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801E6684 -> 0x801E9400
*/
// Range: 0x801E6684 -> 0x801E66FC
void * EventProvider::EventProvider(class EventProvider * const this /* r30 */, const class TourWorld & world /* r31 */) {
    // References
    // -> struct [anonymous] __vt__13EventProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x801E66FC -> 0x801E69B0
void EventProvider::InitData(class EventProvider * const this /* r30 */) {
    // Local variables
    const class TourTown * t; // r27
    class vector events; // r1+0x3C
    class TourWorldEvent * * e; // r28
    struct EventData ed; // r1+0x48

    // References
    // -> const char * gNullStr;
}

struct WorldEventCmp {
    // total size: 0x1
};
class _Temporary_buffer {
    // total size: 0xC
    long _M_original_len; // offset 0x0, size 0x4
    long _M_len; // offset 0x4, size 0x4
    class TourWorldEvent * * _M_buffer; // offset 0x8, size 0x4
};
struct _OKToSwap {
    // total size: 0x1
};
static class Symbol disabled; // size: 0x4, address: 0x80A4E134
// Range: 0x801E69B0 -> 0x801E6A38
class Symbol EventProvider::State(const class EventProvider * const this /* r29 */, int data /* r30 */, class Symbol & component_state /* r31 */) {
    // References
    // -> static class Symbol disabled;
}

static class Symbol event; // size: 0x4, address: 0x80A4E13C
static class Symbol stars; // size: 0x4, address: 0x80A4E144
static class Symbol fame; // size: 0x4, address: 0x80A4E14C
static class Symbol new_sym; // size: 0x4, address: 0x80A4E154
static class Symbol songs; // size: 0x4, address: 0x80A4E15C
static class Symbol item; // size: 0x4, address: 0x80A4E164
static class Symbol tour_new; // size: 0x4, address: 0x80A4E16C
// Range: 0x801E6A38 -> 0x801E6CFC
char * EventProvider::Text(const class EventProvider * const this /* r28 */, class Symbol & slot /* r29 */) {
    // Local variables
    int fame; // r27

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol tour_new;
    // -> const char * gNullStr;
    // -> static class Symbol item;
    // -> static class Symbol songs;
    // -> static class Symbol new_sym;
    // -> static class Symbol fame;
    // -> static class Symbol stars;
    // -> static class Symbol event;
}

static class Symbol playerdiff; // size: 0x4, address: 0x80A4E174
// Range: 0x801E6CFC -> 0x801E6DB4
void EventProvider::Custom(const class EventProvider * const this /* r27 */, int data /* r28 */, class Symbol & slot /* r29 */, class Object * o /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol playerdiff;
}

// Range: 0x801E6DB4 -> 0x801E6E00
class RndMat * EventProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801E6E00 -> 0x801E6E2C
int EventProvider::NumData() {}

// Range: 0x801E6E2C -> 0x801E6E88
class Symbol EventProvider::DataSymbol() {}

// Range: 0x801E6E88 -> 0x801E6E90
void EventProvider::SetBand() {}

// Range: 0x801E6E90 -> 0x801E6EFC
void * EventSongProvider::EventSongProvider(class EventSongProvider * const this /* r30 */, const class SongMgr & song_mgr /* r31 */) {
    // References
    // -> struct [anonymous] __vt__17EventSongProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

static class Symbol random; // size: 0x4, address: 0x80A4E17C
static class Symbol any; // size: 0x4, address: 0x80A4E184
static class Symbol tour_random_song; // size: 0x4, address: 0x80A4E18C
static class Symbol tour_any_song; // size: 0x4, address: 0x80A4E194
// Range: 0x801E6EFC -> 0x801E7040
char * EventSongProvider::Text(const class EventSongProvider * const this /* r29 */, int data /* r30 */) {
    // Local variables
    class Symbol song; // r1+0x14

    // References
    // -> static class Symbol tour_any_song;
    // -> static class Symbol tour_random_song;
    // -> static class Symbol any;
    // -> static class Symbol random;
}

// Range: 0x801E7040 -> 0x801E7048
void EventSongProvider::SetBand() {}

// Range: 0x801E7048 -> 0x801E7094
class RndMat * EventSongProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801E7094 -> 0x801E70B0
int EventSongProvider::NumData() {}

// Range: 0x801E70B0 -> 0x801E70C4
class Symbol EventSongProvider::DataSymbol() {}

// Range: 0x801E70C4 -> 0x801E713C
void * TownProvider::TownProvider(class TownProvider * const this /* r30 */, const class TourWorld & world /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12TownProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x801E713C -> 0x801E7498
void TownProvider::InitData(class TownProvider * const this /* r30 */) {
    // Local variables
    class vector towns; // r1+0x68
    class vector v_states; // r1+0x5C
    const class TourTown * * t; // r28
    struct TownData td; // r1+0x74

    // References
    // -> const char * gNullStr;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
static class Symbol disabled; // size: 0x4, address: 0x80A4E19C
// Range: 0x801E7498 -> 0x801E752C
class Symbol TownProvider::State(const class TownProvider * const this /* r29 */, int data /* r30 */, class Symbol & component_state /* r31 */) {
    // References
    // -> static class Symbol disabled;
}

static class Symbol town; // size: 0x4, address: 0x80A4E1A4
static class Symbol new_sym; // size: 0x4, address: 0x80A4E1AC
static class Symbol item; // size: 0x4, address: 0x80A4E1B4
static class Symbol tour_new; // size: 0x4, address: 0x80A4E1BC
// Range: 0x801E752C -> 0x801E76C8
char * TownProvider::Text(const class TownProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
    // -> static class Symbol tour_new;
    // -> static class Symbol item;
    // -> static class Symbol new_sym;
    // -> static class Symbol town;
}

static class Symbol playerdiff; // size: 0x4, address: 0x80A4E1C4
// Range: 0x801E76C8 -> 0x801E7780
void TownProvider::Custom(const class TownProvider * const this /* r27 */, int data /* r28 */, class Symbol & slot /* r29 */, class Object * o /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol playerdiff;
}

// Range: 0x801E7780 -> 0x801E77CC
class RndMat * TownProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801E77CC -> 0x801E77F8
int TownProvider::NumData() {}

// Range: 0x801E77F8 -> 0x801E7808
class Symbol TownProvider::DataSymbol() {}

// Range: 0x801E7808 -> 0x801E7810
void TownProvider::SetBand() {}

static class Symbol _s; // size: 0x4, address: 0x80A4E1CC
// Range: 0x801E7810 -> 0x801E7BC0
class DataNode TownProvider::Handle(class TownProvider * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x801E7BC0 -> 0x801E7C34
void * VenueProvider::VenueProvider(class VenueProvider * const this /* r30 */, const class TourWorld & world /* r31 */) {
    // References
    // -> struct [anonymous] __vt__13VenueProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x801E7C34 -> 0x801E7F58
void VenueProvider::InitData(class VenueProvider * const this /* r29 */) {
    // Local variables
    class vector e_states; // r1+0x54
    const class TourTown * t; // r31
    class TourVenue * const * v; // r30
    struct VenueData vd; // r1+0x60

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol disabled; // size: 0x4, address: 0x80A4E1D4
// Range: 0x801E7F58 -> 0x801E7FE0
class Symbol VenueProvider::State(const class VenueProvider * const this /* r29 */, int data /* r30 */, class Symbol & component_state /* r31 */) {
    // References
    // -> static class Symbol disabled;
}

static class Symbol town; // size: 0x4, address: 0x80A4E1DC
static class Symbol new_sym; // size: 0x4, address: 0x80A4E1E4
static class Symbol item; // size: 0x4, address: 0x80A4E1EC
static class Symbol tour_new; // size: 0x4, address: 0x80A4E1F4
// Range: 0x801E7FE0 -> 0x801E817C
char * VenueProvider::Text(const class VenueProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
    // -> static class Symbol tour_new;
    // -> static class Symbol item;
    // -> static class Symbol new_sym;
    // -> static class Symbol town;
}

static class Symbol playerdiff; // size: 0x4, address: 0x80A4E1FC
// Range: 0x801E817C -> 0x801E8234
void VenueProvider::Custom(const class VenueProvider * const this /* r27 */, int data /* r28 */, class Symbol & slot /* r29 */, class Object * o /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol playerdiff;
}

// Range: 0x801E8234 -> 0x801E8280
class RndMat * VenueProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801E8280 -> 0x801E8298
int VenueProvider::NumData() {}

// Range: 0x801E8298 -> 0x801E82A8
class Symbol VenueProvider::DataSymbol() {}

// Range: 0x801E82A8 -> 0x801E82B0
void VenueProvider::SetBand() {}

static class Symbol icon; // size: 0x4, address: 0x80A4E204
static class Symbol description; // size: 0x4, address: 0x80A4E20C
static class Symbol instrument; // size: 0x4, address: 0x80A4E214
// Range: 0x801E82B0 -> 0x801E843C
char * RequirementProvider::Text(const class RequirementProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol instrument;
    // -> static class Symbol description;
    // -> static class Symbol icon;
}

// Range: 0x801E843C -> 0x801E8488
class RndMat * RequirementProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801E8488 -> 0x801E84B0
int RequirementProvider::NumData() {}

// Range: 0x801E84B0 -> 0x801E84C0
unsigned char RequirementProvider::IsActive() {}

// Range: 0x801E84C0 -> 0x801E852C
void RequirementProvider::SetByVenue(class RequirementProvider * const this /* r30 */, const class TourBand * band /* r31 */) {}

// Range: 0x801E852C -> 0x801E8594
void RequirementProvider::SetByEvent(class RequirementProvider * const this /* r29 */, const class TourBand * band /* r30 */, const class TourWorldEvent * e /* r31 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x801E8594 -> 0x801E85A8
void RequirementProvider::SetByStaff(class RequirementProvider * const this /* r6 */) {}

// Range: 0x801E85A8 -> 0x801E85BC
void RequirementProvider::SetByChallenge(class RequirementProvider * const this /* r6 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4E21C
static class Symbol _s; // size: 0x4, address: 0x80A4E224
static class Symbol _s; // size: 0x4, address: 0x80A4E22C
static class Symbol _s; // size: 0x4, address: 0x80A4E234
// Range: 0x801E85BC -> 0x801E8D60
class DataNode RequirementProvider::Handle(class RequirementProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__18TourChallengeEvent;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__9TourStaff;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__14TourWorldEvent;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8TourBand;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x801E8D60 -> 0x801E8E70
void * HometownProvider::HometownProvider(class HometownProvider * const this /* r29 */, const class vector & towns /* r30 */) {
    // Local variables
    class TourTown * const * t; // r31
    const class TourTown * town; // r5

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__16HometownProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x801E8E70 -> 0x801E8EA8
char * HometownProvider::Text() {}

// Range: 0x801E8EA8 -> 0x801E8EF4
class RndMat * HometownProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801E8EF4 -> 0x801E8F0C
int HometownProvider::NumData() {}

// Range: 0x801E8F0C -> 0x801E8F1C
class Symbol HometownProvider::DataSymbol() {}

// Range: 0x801E8F1C -> 0x801E8F80
void * StaffProvider::StaffProvider(class StaffProvider * const this /* r30 */, const class vector & staff /* r31 */) {
    // References
    // -> struct [anonymous] __vt__13StaffProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x801E8F80 -> 0x801E8FC0
char * StaffProvider::Text() {}

// Range: 0x801E8FC0 -> 0x801E900C
class RndMat * StaffProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801E900C -> 0x801E9028
int StaffProvider::NumData() {}

// Range: 0x801E9028 -> 0x801E903C
class Symbol StaffProvider::DataSymbol() {}

static class Symbol _s; // size: 0x4, address: 0x80A4E23C
// Range: 0x801E903C -> 0x801E9400
class DataNode StaffProvider::Handle(class StaffProvider * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x9C
} __vt__13StaffProvider; // size: 0x9C, address: 0x808A6470
struct {
    // total size: 0x8
} __RTTI__13StaffProvider; // size: 0x8, address: 0x808A6538
struct {
    // total size: 0x98
} __vt__16HometownProvider; // size: 0x98, address: 0x808A6540
struct {
    // total size: 0x8
} __RTTI__16HometownProvider; // size: 0x8, address: 0x808A6608
struct {
    // total size: 0x9C
} __vt__19RequirementProvider; // size: 0x9C, address: 0x808A6610
struct {
    // total size: 0x8
} __RTTI__19RequirementProvider; // size: 0x8, address: 0x808A66E0
struct {
    // total size: 0x98
} __vt__13VenueProvider; // size: 0x98, address: 0x808A66E8
struct {
    // total size: 0x8
} __RTTI__13VenueProvider; // size: 0x8, address: 0x808A67B8
struct {
    // total size: 0x9C
} __vt__12TownProvider; // size: 0x9C, address: 0x808A67C0
struct {
    // total size: 0x8
} __RTTI__12TownProvider; // size: 0x8, address: 0x808A6890
struct {
    // total size: 0x98
} __vt__17EventSongProvider; // size: 0x98, address: 0x808A6898
struct {
    // total size: 0x8
} __RTTI__17EventSongProvider; // size: 0x8, address: 0x808A6960
struct {
    // total size: 0x98
} __vt__13EventProvider; // size: 0x98, address: 0x808A6968
struct {
    // total size: 0x8
} __RTTI__13EventProvider; // size: 0x8, address: 0x808A6A38
struct {
    // total size: 0x8
} __RTTI__14WorldStateBase; // size: 0x8, address: 0x808A6A50
struct {
    // total size: 0x8
} __RTTI__PQ213VenueProvider9VenueData; // size: 0x8, address: 0x808A6B78
struct {
    // total size: 0x8
} __RTTI__PQ212TownProvider8TownData; // size: 0x8, address: 0x808A6BA0
struct {
    // total size: 0x8
} __RTTI__PQ213EventProvider9EventData; // size: 0x8, address: 0x808A6BC8

