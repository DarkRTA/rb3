/*
    Compile unit: C:\rockband2\band2\src\meta\TourWorld.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801DA4F4 -> 0x801E0748
*/
static class Symbol display_song; // size: 0x4, address: 0x80A4DF0C
static class Symbol fame; // size: 0x4, address: 0x80A4DF14
static class Symbol town; // size: 0x4, address: 0x80A4DF1C
static class Symbol world; // size: 0x4, address: 0x80A4DF24
static class Symbol buzz; // size: 0x4, address: 0x80A4DF2C
static class Symbol item; // size: 0x4, address: 0x80A4DF34
static class Symbol award_item; // size: 0x4, address: 0x80A4DF3C
static class Symbol warning_screen; // size: 0x4, address: 0x80A4DF44
static class Symbol allow_moments; // size: 0x4, address: 0x80A4DF4C
// Range: 0x801DA4F4 -> 0x801DA894
void * TourWorldEvent::TourWorldEvent(class TourWorldEvent * const this /* r29 */, class Symbol & town_name /* r27 */, class Symbol & venue_name /* r28 */, class DataArray * cfg /* r30 */) {
    // Local variables
    class DataArray * f; // r28
    class DataArray * i; // r28

    // References
    // -> static class Symbol allow_moments;
    // -> static class Symbol warning_screen;
    // -> static class Symbol award_item;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol item;
    // -> static class Symbol buzz;
    // -> static class Symbol world;
    // -> static class Symbol town;
    // -> static class Symbol fame;
    // -> static class Symbol display_song;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__14TourWorldEvent;
}

// Range: 0x801DA894 -> 0x801DA940
char * TourWorldEvent::DisplayName(const class TourWorldEvent * const this /* r31 */) {
    // Local variables
    class Symbol song; // r1+0x14

    // References
    // -> const char * gNullStr;
}

static class Symbol tour_song_set; // size: 0x4, address: 0x80A4DF54
// Range: 0x801DA940 -> 0x801DAA24
char * TourWorldEvent::Description(const class TourWorldEvent * const this /* r31 */) {
    // Local variables
    class Symbol song; // r1+0x14

    // References
    // -> const char * gNullStr;
    // -> static class Symbol tour_song_set;
}

// Range: 0x801DAA24 -> 0x801DAA2C
class Symbol TourWorldEvent::VenueVariant() {}

// Range: 0x801DAA2C -> 0x801DAA78
unsigned char TourWorldEvent::IsOpportunity() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x801DAA78 -> 0x801DAA80
class Symbol TourWorldEvent::BuzzVenue() {}

// Range: 0x801DAA80 -> 0x801DAB20
class Symbol TourWorldEvent::EventToken() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x801DAB20 -> 0x801DAB28
class Symbol TourWorldEvent::Venue() {}

// Range: 0x801DAB28 -> 0x801DAB30
class Symbol TourWorldEvent::Town() {}

// Range: 0x801DAB30 -> 0x801DAB38
int TourWorldEvent::TownFameRequired() {}

// Range: 0x801DAB38 -> 0x801DAB40
int TourWorldEvent::WorldFameRequired() {}

// Range: 0x801DAB40 -> 0x801DAB48
int TourWorldEvent::BuzzRequired() {}

// Range: 0x801DAB48 -> 0x801DAB50
class Symbol TourWorldEvent::ItemRequired() {}

// Range: 0x801DAB50 -> 0x801DAB58
class Symbol TourWorldEvent::AwardItem() {}

// Range: 0x801DAB58 -> 0x801DAB60
unsigned char TourWorldEvent::AllowMoments() {}

// Range: 0x801DAB60 -> 0x801DAB6C
void TourWorldEvent::SetVenueVariant() {}

// Range: 0x801DAB6C -> 0x801DAB78
void TourWorldEvent::SetBuzzVenue() {}

// Range: 0x801DAB78 -> 0x801DAB80
void TourWorldEvent::SetDisplaySong() {}

// Range: 0x801DAB80 -> 0x801DAC8C
class Symbol TourWorldEvent::DisplaySong(const class TourWorldEvent * const this /* r28 */) {
    // Local variables
    const class EventSong & es; // r29
    class Symbol song; // r1+0x10

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801DAC8C -> 0x801DAD70
void TourWorldEvent::Validate(const class TourWorldEvent * const this /* r28 */) {
    // Local variables
    class DataArray * items; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4DF5C
static class Symbol _s; // size: 0x4, address: 0x80A4DF64
static class Symbol _s; // size: 0x4, address: 0x80A4DF6C
static class Symbol _s; // size: 0x4, address: 0x80A4DF74
static class Symbol _s; // size: 0x4, address: 0x80A4DF7C
static class Symbol _s; // size: 0x4, address: 0x80A4DF84
// Range: 0x801DAD70 -> 0x801DB3F4
unsigned char TourWorldEvent::SyncProperty(class TourWorldEvent * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x801DB3F4 -> 0x801DB444
void * TourVenue::TourVenue(class TourVenue * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x801DB444 -> 0x801DB55C
void * TourVenue::~TourVenue(class TourVenue * const this /* r28 */) {}

// Range: 0x801DB5B8 -> 0x801DB998
void * TourTier::TourTier(class TourTier * const this /* r27 */, const class SongMgr & song_mgr /* r28 */, class DataArray * cfg /* r29 */) {
    // Local variables
    int j; // r30
    class vector events; // r1+0x64
    int k; // r24
    class TourWorldEvent * e; // r1+0x54

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP14TourWorldEvent;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
}

struct _OKToMemCpy {
    // total size: 0x1
};
// Range: 0x801DB998 -> 0x801DBB38
void * TourTier::~TourTier(class TourTier * const this /* r30 */) {
    // Local variables
    class vector * v; // r27
}

static class Symbol order; // size: 0x4, address: 0x80A4DF8C
static class Symbol continent; // size: 0x4, address: 0x80A4DF94
static class Symbol unlocks; // size: 0x4, address: 0x80A4DF9C
static class Symbol played; // size: 0x4, address: 0x80A4DFA4
static class Symbol completed; // size: 0x4, address: 0x80A4DFAC
static class Symbol male; // size: 0x4, address: 0x80A4DFB4
static class Symbol female; // size: 0x4, address: 0x80A4DFBC
static class Symbol venues; // size: 0x4, address: 0x80A4DFC4
// Range: 0x801DBB38 -> 0x801DC0D4
void * TourTown::TourTown(class TourTown * const this /* r27 */, const class SongMgr & sm /* r28 */, class DataArray * cfg /* r29 */) {
    // Local variables
    class DataArray * u; // r30
    class DataArray * p; // r25
    class DataArray * c; // r25
    class DataArray * venue_array; // r30
    int i; // r31
    class DataArray * venue_data; // r25
    class Symbol venue_name; // r1+0x8C
    class TourVenue * venue; // r1+0x88
    int j; // r29
    class TourWorldEvent * e; // r1+0x84

    // References
    // -> static class Symbol venues;
    // -> static class Symbol female;
    // -> static class Symbol male;
    // -> static class Symbol completed;
    // -> static class Symbol played;
    // -> static class Symbol unlocks;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol continent;
    // -> static class Symbol order;
    // -> const char * gNullStr;
}

// Range: 0x801DC0D4 -> 0x801DC1D8
void * TourTown::~TourTown(class TourTown * const this /* r28 */) {}

// Range: 0x801DC1D8 -> 0x801DC1F0
unsigned char __eq() {}

// Range: 0x801DC1F0 -> 0x801DC240
class TourVenue * TourTown::FindVenue(const class TourTown * const this /* r31 */) {
    // Local variables
    class TourVenue * const * v; // r0
}

// Range: 0x801DC240 -> 0x801DC2D4
int TourTown::FindVenuePos() {
    // Local variables
    class TourVenue * const * v; // r7

    // References
    // -> class Debug TheDebug;
}

// Range: 0x801DC2D4 -> 0x801DC354
void * TourStaff::TourStaff(class TourStaff * const this /* r30 */, class Symbol & staff_name /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__9TourStaff;
}

static class Symbol prereqs; // size: 0x4, address: 0x80A4DFCC
static class Symbol stars; // size: 0x4, address: 0x80A4DFD4
static class Symbol buzz; // size: 0x4, address: 0x80A4DFDC
static class Symbol item; // size: 0x4, address: 0x80A4DFE4
static class Symbol modifiers; // size: 0x4, address: 0x80A4DFEC
static class Symbol money; // size: 0x4, address: 0x80A4DFF4
static class Symbol buzz_lost; // size: 0x4, address: 0x80A4DFFC
static class Symbol buzz_required; // size: 0x4, address: 0x80A4E004
static class Symbol moment_freq; // size: 0x4, address: 0x80A4E00C
static class Symbol towns; // size: 0x4, address: 0x80A4E014
// Range: 0x801DC354 -> 0x801DC85C
void * TourStaff::TourStaff(class TourStaff * const this /* r29 */, class DataArray * cfg /* r30 */) {
    // Local variables
    class DataArray * p; // r28
    class DataArray * m; // r30
    class DataArray * b; // r28
    class DataArray * t; // r28
    int i; // r27
    class DataArray * f; // r27

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class Symbol towns;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol moment_freq;
    // -> static class Symbol buzz_required;
    // -> static class Symbol buzz_lost;
    // -> static class Symbol money;
    // -> static class Symbol modifiers;
    // -> static class Symbol item;
    // -> static class Symbol buzz;
    // -> static class Symbol stars;
    // -> static class Symbol prereqs;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__9TourStaff;
}

// Range: 0x801DC85C -> 0x801DC888
void TourStaff::Init() {}

// Range: 0x801DC888 -> 0x801DC890
class Symbol TourStaff::StaffName() {}

// Range: 0x801DC890 -> 0x801DC898
int TourStaff::StarsRequired() {}

// Range: 0x801DC898 -> 0x801DC8A0
int TourStaff::BuzzRequired() {}

// Range: 0x801DC8A0 -> 0x801DC8A8
class Symbol TourStaff::ItemRequired() {}

// Range: 0x801DC8A8 -> 0x801DCA04
float TourStaff::BuzzModifier(const class TourStaff * const this /* r31 */) {
    // Local variables
    class DataArrayPtr args; // r1+0x18

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

// Range: 0x801DCA04 -> 0x801DCA0C
float TourStaff::BuzzLostModifier() {}

// Range: 0x801DCA0C -> 0x801DCB68
float TourStaff::MoneyPerStarModifier(const class TourStaff * const this /* r31 */) {
    // Local variables
    class DataArrayPtr args; // r1+0x18

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

// Range: 0x801DCB68 -> 0x801DCC0C
float TourStaff::BuzzRequiredModifier(const class TourStaff * const this /* r30 */) {}

// Range: 0x801DCC0C -> 0x801DCC14
int TourStaff::MinMomentFreq() {}

// Range: 0x801DCC14 -> 0x801DCC1C
int TourStaff::MaxMomentFreq() {}

// Range: 0x801DCC1C -> 0x801DCC24
class list & TourStaff::BuzzRequiredTowns() {}

static class Symbol _s; // size: 0x4, address: 0x80A4E01C
static class Symbol _s; // size: 0x4, address: 0x80A4E024
static class Symbol _s; // size: 0x4, address: 0x80A4E02C
static class Symbol _s; // size: 0x4, address: 0x80A4E034
static class Symbol _s; // size: 0x4, address: 0x80A4E03C
// Range: 0x801DCC24 -> 0x801DD354
class DataNode TourStaff::Handle(class TourStaff * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x40
    class MessageTimer _mt; // r1+0x50
    class DataNode _n; // r1+0x48

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x801DD354 -> 0x801DD394
unsigned char __eq(class Symbol & rhs /* r31 */) {}

class Symbol sNullName; // size: 0x4, address: 0x80A4E040
// Range: 0x801DD394 -> 0x801DD414
void * TourMoment::TourMoment(class TourMoment * const this /* r30 */, class Symbol & name /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> class Symbol sNullName;
    // -> struct [anonymous] __vt__10TourMoment;
}

static class Symbol min_vehicle; // size: 0x4, address: 0x80A4E048
static class Symbol max_vehicle; // size: 0x4, address: 0x80A4E050
static class Symbol loading_screen; // size: 0x4, address: 0x80A4E058
static class Symbol disable_staff; // size: 0x4, address: 0x80A4E060
static class Symbol disable_overdrive; // size: 0x4, address: 0x80A4E068
static class Symbol random; // size: 0x4, address: 0x80A4E070
static class Symbol any; // size: 0x4, address: 0x80A4E078
static class Symbol additional_song; // size: 0x4, address: 0x80A4E080
static class Symbol replace_song; // size: 0x4, address: 0x80A4E088
static class Symbol opportunity; // size: 0x4, address: 0x80A4E090
static class Symbol venue; // size: 0x4, address: 0x80A4E098
static class Symbol buzz_venue; // size: 0x4, address: 0x80A4E0A0
static class Symbol any; // size: 0x4, address: 0x80A4E0A8
static class Symbol stars_required; // size: 0x4, address: 0x80A4E0B0
static class Symbol buzz_required; // size: 0x4, address: 0x80A4E0B8
// Range: 0x801DD414 -> 0x801DDA80
void * TourMoment::TourMoment(class TourMoment * const this /* r29 */, class DataArray * cfg /* r27 */, const class SongMgr & sm /* r30 */, int num_vehicles /* r26 */) {
    // Local variables
    class DataArray * a; // r27
    class DataArray * a; // r27
    class DataArray * a; // r26
    class DataArray * v; // r27
    int i; // r26

    // References
    // -> static class Symbol buzz_required;
    // -> static class Symbol stars_required;
    // -> static class Symbol any;
    // -> static class Symbol buzz_venue;
    // -> static class Symbol venue;
    // -> static class Symbol opportunity;
    // -> static class Symbol replace_song;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol additional_song;
    // -> static class Symbol any;
    // -> static class Symbol random;
    // -> static class Symbol disable_overdrive;
    // -> static class Symbol disable_staff;
    // -> static class Symbol loading_screen;
    // -> static class Symbol max_vehicle;
    // -> static class Symbol min_vehicle;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__10TourMoment;
}

// Range: 0x801DDA80 -> 0x801DDBB8
void * TourMoment::~TourMoment(class TourMoment * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__10TourMoment;
}

// Range: 0x801DDBB8 -> 0x801DDBE8
void TourMoment::Init() {}

// Range: 0x801DDBE8 -> 0x801DDC00
unsigned char TourMoment::IsNull() {
    // References
    // -> class Symbol sNullName;
}

// Range: 0x801DDC00 -> 0x801DDC08
class Symbol TourMoment::MomentName() {}

static class Symbol money_per_star; // size: 0x4, address: 0x80A4E0C0
// Range: 0x801DDC08 -> 0x801DDE68
int TourMoment::MoneyPerStar(const class TourMoment * const this /* r31 */, int stars /* r29 */, int money /* r30 */) {
    // Local variables
    class DataArray * modifier; // r31
    class DataArrayPtr args; // r1+0x28
    int money; // r31

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol money_per_star;
}

static class Symbol buzz_change; // size: 0x4, address: 0x80A4E0C8
// Range: 0x801DDE68 -> 0x801DE068
int TourMoment::BuzzChange(const class TourMoment * const this /* r31 */, int stars /* r29 */, int buzz /* r30 */) {
    // Local variables
    class DataArray * modifier; // r31
    class DataArrayPtr args; // r1+0x28

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol buzz_change;
}

// Range: 0x801DE068 -> 0x801DE070
char * TourMoment::LoadingScreen() {}

// Range: 0x801DE070 -> 0x801DE078
unsigned char TourMoment::DisableStaff() {}

// Range: 0x801DE078 -> 0x801DE080
unsigned char TourMoment::DisableOverdrive() {}

// Range: 0x801DE080 -> 0x801DE088
class EventSong * TourMoment::AdditionalSong() {}

// Range: 0x801DE088 -> 0x801DE090
class TourWorldEvent * TourMoment::Opportunity() {}

// Range: 0x801DE090 -> 0x801DE098
class EventSong * TourMoment::ReplaceSong() {}

// Range: 0x801DE098 -> 0x801DE164
unsigned char TourMoment::IsValid(const class TourMoment * const this /* r11 */) {}

// Range: 0x801DE164 -> 0x801DE18C
unsigned char TourMoment::IsTriggerable() {}

static class Symbol _s; // size: 0x4, address: 0x80A4E0D0
static class Symbol _s; // size: 0x4, address: 0x80A4E0D8
static class Symbol _s; // size: 0x4, address: 0x80A4E0E0
static class Symbol _s; // size: 0x4, address: 0x80A4E0E8
// Range: 0x801DE18C -> 0x801DE7B4
class DataNode TourMoment::Handle(class TourMoment * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x40
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

static class Symbol tour_staff_none; // size: 0x4, address: 0x80A4E0F0
static class Symbol null_moment; // size: 0x4, address: 0x80A4E0F8
static class Symbol tiers; // size: 0x4, address: 0x80A4E100
static class Symbol towns; // size: 0x4, address: 0x80A4E108
static class Symbol staff; // size: 0x4, address: 0x80A4E110
static class Symbol vehicles; // size: 0x4, address: 0x80A4E118
static class Symbol moments; // size: 0x4, address: 0x80A4E120
// Range: 0x801DE7B4 -> 0x801DF010
void * TourWorld::TourWorld(class TourWorld * const this /* r24 */, const class SongMgr & song_mgr /* r25 */, class DataArray * cfg /* r26 */) {
    // Local variables
    class DataArray * tier_array; // r28
    int i; // r29
    class DataArray * town_array; // r28
    int i; // r27
    class TourTown * t; // r1+0xA0
    struct MappedTowns mt; // r1+0xB0
    class DataArray * staff_array; // r28
    int i; // r29
    int num_vehicles; // r27
    class DataArray * m_array; // r28
    int i; // r29
    struct MappedTowns * t; // r27
    class TourTown * * v; // r25
    class Symbol town_name; // r1+0x9C
    struct VehicleTown vt; // r1+0xA4

    // References
    // -> static class Symbol moments;
    // -> static class Symbol vehicles;
    // -> static class Symbol staff;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P11VehicleTown;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> static class Symbol towns;
    // -> static class Symbol tiers;
    // -> static class Symbol null_moment;
    // -> static class Symbol tour_staff_none;
    // -> struct [anonymous] __vt__9TourWorld;
}

struct MappedTownsCmp {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__P11VehicleTown; // size: 0x8, address: 0x808A5A58
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
struct VehicleTownCmp {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x801DF010 -> 0x801DF4EC
void * TourWorld::~TourWorld(class TourWorld * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__9TourWorld;
}

// Range: 0x801DF55C -> 0x801DF574
unsigned char __eq() {}

// Range: 0x801DF574 -> 0x801DF68C
void TourWorld::FindTierEvents(const class TourWorld * const this /* r26 */, class vector & events /* r31 */, class Symbol & hometown /* r27 */, class Symbol & town /* r28 */, class Symbol & venue /* r29 */) {
    // Local variables
    const struct MappedTowns * mt; // r4
    const struct VehicleTown & vt; // r0
    int venue_pos; // r0
}

// Range: 0x801DF68C -> 0x801DF728
class TourTier * TourWorld::FindTier(const class TourWorld * const this /* r29 */, class Symbol & town /* r30 */) {
    // Local variables
    const struct MappedTowns * mt; // r31
    const struct VehicleTown & vt; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct pair {
    // total size: 0x8
    const struct MappedTowns * first; // offset 0x0, size 0x4
    const struct MappedTowns * second; // offset 0x4, size 0x4
};
// Range: 0x801DF728 -> 0x801DF784
struct MappedTowns * TourWorld::FindMappedTowns() {
    // Local variables
    struct pair p; // r1+0x18
}

struct pair {
    // total size: 0x8
    const struct VehicleTown * first; // offset 0x0, size 0x4
    const struct VehicleTown * second; // offset 0x4, size 0x4
};
// Range: 0x801DF784 -> 0x801DF7D4
class TourTown * TourWorld::FindTown(const class TourWorld * const this /* r31 */) {
    // Local variables
    class TourTown * const * t; // r0
}

// Range: 0x801DF7D4 -> 0x801DF824
class TourTown * TourWorld::FindTown(class TourWorld * const this /* r31 */) {
    // Local variables
    class TourTown * * t; // r0
}

// Range: 0x801DF824 -> 0x801DF83C
unsigned char __eq() {}

// Range: 0x801DF83C -> 0x801DF88C
class TourTier * TourWorld::FindTier(const class TourWorld * const this /* r31 */) {
    // Local variables
    class TourTier * const * t; // r0
}

// Range: 0x801DF88C -> 0x801DF934
class TourTown * TourWorld::TierTown(const class TourWorld * const this /* r28 */, class Symbol & hometown /* r29 */, class Symbol & tier_name /* r30 */) {
    // Local variables
    class TourTown * const * t; // r31
    const class TourTier * tier; // r0
}

// Range: 0x801DF934 -> 0x801DF93C
class vector & TourWorld::TownList() {}

// Range: 0x801DF93C -> 0x801DFA04
class Symbol TourWorld::FindEventTown(const class TourWorld * const this /* r28 */, class Symbol & hometown /* r29 */, const class TourWorldEvent * e /* r30 */) {
    // Local variables
    const class TourTown * t; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801DFA04 -> 0x801DFA0C
class vector & TourWorld::Staff() {}

// Range: 0x801DFA0C -> 0x801DFA18
class TourStaff * TourWorld::NullStaff() {}

// Range: 0x801DFA18 -> 0x801DFA20
class vector & TourWorld::Moments() {}

// Range: 0x801DFA20 -> 0x801DFA60
unsigned char __eq(class Symbol & name /* r31 */) {}

// Range: 0x801DFA60 -> 0x801DFBC0
void TourWorld::ValidMoments(const class TourWorld * const this /* r24 */, class vector & moments /* r25 */, int level /* r26 */, int stars /* r27 */, int buzz /* r28 */, int num_songs /* r29 */, const class vector & exclude /* r30 */, unsigned char opportunity /* r31 */) {
    // Local variables
    class TourMoment * const * mit; // r23
    class TourMoment * m; // r22
}

// Range: 0x801DFBC0 -> 0x801DFCC8
void TourWorld::GetLiveBattles(const class TourWorld * const this /* r30 */, class list & battles /* r31 */) {
    // Local variables
    class TourTown * const * t; // r29
    class TourVenue * const * v; // r28
    class TourWorldEvent * const * e; // r27

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x801DFCC8 -> 0x801DFDE4
void TourWorld::FindTowns(const class TourWorld * const this /* r28 */, class vector & towns /* r29 */, class Symbol & continent /* r30 */) {
    // Local variables
    class TourTown * const * t; // r31
}

struct TownOrderCmp {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x801DFDE4 -> 0x801DFFD8
void TourWorld::DisableBattles(class TourWorld * const this /* r27 */, const class list * shared /* r28 */) {
    // Local variables
    class TourWorldEvent * * c; // r26
    class TourTown * const * t; // r31
    class TourVenue * const * v; // r30
    class TourWorldEvent * * e; // r29
}

// Range: 0x801DFFD8 -> 0x801E0154
void TourWorld::ClearBattles(class TourWorld * const this /* r31 */) {
    // Local variables
    class TourWorldEvent * * c; // r30
    class TourTown * const * t; // r29
    class TourVenue * const * v; // r28
    class TourWorldEvent * * e; // r27
}

static class Symbol screen; // size: 0x4, address: 0x80A4E128
// Range: 0x801E0154 -> 0x801E0678
void TourWorld::Validate(const class TourWorld * const this /* r29 */) {
    // Local variables
    class TourTier * const * t; // r28
    class vector * v; // r30
    class TourWorldEvent * const * e; // r27
    class vector orders; // r1+0x78
    class TourTown * const * t; // r30
    int order; // r1+0x74
    class TourVenue * const * v; // r27
    const class vector & events; // r0
    class TourWorldEvent * const * e; // r26
    class DataArray * hints; // r26
    int i; // r27
    class DataArray * s; // r30
    class DataArray * items; // r27
    int i; // r30
    class Symbol item; // r1+0x70
    class TourHintNewItem new_item; // r1+0x84
    class TourStaff * const * s; // r26
    class Symbol item; // r1+0x6C
    class list & towns; // r28
    struct _List_iterator t; // r1+0x68

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> class ObjectDir * sMainDir;
    // -> static class Symbol screen;
    // -> class Debug TheDebug;
}

// Range: 0x801E0678 -> 0x801E073C
void TourWorld::ValidateEvent(const class TourWorld * const this /* r29 */, const class TourWorldEvent * e /* r30 */) {
    // Local variables
    class TourMoment * const * m; // r31
    class TourWorldEvent * op; // r0

    // References
    // -> class Debug TheDebug;
}

struct {
    // total size: 0xC
} __vt__9TourWorld; // size: 0xC, address: 0x808A5C90
struct {
    // total size: 0x8
} __RTTI__9TourWorld; // size: 0x8, address: 0x808A5CA8
struct {
    // total size: 0x54
} __vt__10TourMoment; // size: 0x54, address: 0x808A5CB0
struct {
    // total size: 0x54
} __vt__9TourStaff; // size: 0x54, address: 0x808A5D30
struct {
    // total size: 0x68
} __vt__14TourWorldEvent; // size: 0x68, address: 0x808A5DB0
struct {
    // total size: 0x8
} __RTTI__P11MappedTowns; // size: 0x8, address: 0x808A5EE0
struct {
    // total size: 0x8
} __RTTI__PP8TourTier; // size: 0x8, address: 0x808A5EF8
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std74vector<P14TourWorldEvent,Q211stlpmtx_std31StlNodeAlloc<P14TourWorldEvent>>; // size: 0x8, address: 0x808A5F58
struct {
    // total size: 0x8
} __RTTI__PP10TourMoment; // size: 0x8, address: 0x808A5F70
struct {
    // total size: 0x8
} __RTTI__PP9TourStaff; // size: 0x8, address: 0x808A5F88
struct {
    // total size: 0x8
} __RTTI__PP9TourVenue; // size: 0x8, address: 0x808A5FA0
struct {
    // total size: 0x8
} __RTTI__PPC8TourTown; // size: 0x8, address: 0x808A5FC0
struct {
    // total size: 0x8
} __RTTI__PP8TourTown; // size: 0x8, address: 0x808A5FD8
struct _IsPOD {
    // total size: 0x1
};
// Range: 0x801E073C -> 0x801E0748
static void __sinit_\TourWorld_cpp() {
    // References
    // -> class Symbol sNullName;
    // -> const char * gNullStr;
}


