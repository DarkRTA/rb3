/*
    Compile unit: C:\rockband2\band2\src\meta\TourBand.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8019BF50 -> 0x801A8C18
*/
struct ChallengeCmp {
    // total size: 0x4
    const class TourBand & mBand; // offset 0x0, size 0x4
};
// Range: 0x8019BF50 -> 0x8019BF58
void * ChallengeCmp::ChallengeCmp() {}

// Range: 0x8019BF58 -> 0x8019C0CC
unsigned char ChallengeCmp::__cl(const struct ChallengeCmp * const this /* r30 */, class TourChallengeEvent * lhs /* r27 */, class TourChallengeEvent * rhs /* r28 */) {
    // Local variables
    enum TourStatus lhs_status; // r0
    enum TourStatus rhs_status; // r0
    enum ChallengeEventType lhs_type; // r0
    enum ChallengeEventType rhs_type; // r0
}

enum TourEventType sEventType; // size: 0x4, address: 0x80A4D1C8
int sVer; // size: 0x4, address: 0x80A4D1CC
class DataArray * sWorldConfig; // size: 0x4, address: 0x80A4D1D0
class DataArray * sVehicles; // size: 0x4, address: 0x80A4D1D4
class DataArray * sChallengeConfig; // size: 0x4, address: 0x80A4D1D8
class String sRivalLogo; // size: 0xC, address: 0x80979F04
class PersistentGameData sPersistentGameData; // size: 0x4C, address: 0x80979F10
// Range: 0x8019C0CC -> 0x8019C10C
unsigned char __eq() {}

// Range: 0x8019C10C -> 0x8019C124
unsigned char __eq() {}

// Range: 0x8019C124 -> 0x8019C154
unsigned char __eq() {}

// Range: 0x8019C154 -> 0x8019C16C
unsigned char __eq() {}

static class Symbol tour; // size: 0x4, address: 0x80A4D1E0
static class Symbol max_stars_per_song; // size: 0x4, address: 0x80A4D1E8
static class Symbol botb_loading_screen; // size: 0x4, address: 0x80A4D1F0
static class Symbol world; // size: 0x4, address: 0x80A4D1F8
static class Symbol vehicles; // size: 0x4, address: 0x80A4D200
static class Symbol challenge; // size: 0x4, address: 0x80A4D208
// Range: 0x8019C16C -> 0x8019C330
void TourBand::Init() {
    // Local variables
    class DataArray * cfg; // r30

    // References
    // -> class DataArray * sChallengeConfig;
    // -> static class Symbol challenge;
    // -> class DataArray * sVehicles;
    // -> static class Symbol vehicles;
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol world;
    // -> static class Symbol botb_loading_screen;
    // -> static class Symbol max_stars_per_song;
    // -> static class Symbol tour;
}

// Range: 0x8019C330 -> 0x8019C334
void TourBand::Terminate() {}

// Range: 0x8019C334 -> 0x8019C610
void * TourBand::TourBand(class TourBand * const this /* r26 */, class TourWorld & world /* r27 */, class TourChallenge & challenge /* r28 */, const class SongMgr & sm /* r29 */, class BandUserMgr & bum /* r30 */) {
    // Local variables
    int i; // r5

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__8TourBand;
    // -> struct [anonymous] __vt__8BandData;
}

class _List_node : public _List_node_base {
    // total size: 0x14
public:
    struct OpportunityLoc _M_data; // offset 0x8, size 0xC
};
class _List_node : public _List_node_base {
    // total size: 0x20
public:
    struct ChallengeState _M_data; // offset 0x8, size 0x18
};
// Range: 0x8019C610 -> 0x8019CC68
void * TourBand::~TourBand(class TourBand * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__8TourBand;
}

// Range: 0x8019CCC4 -> 0x8019CCD4
unsigned char TourBand::HasWritePermission() {}

// Range: 0x8019CCD4 -> 0x8019CDD4
void TourBand::GetTopSongs(const class TourBand * const this /* r28 */, class vector & songs /* r29 */, int numSongs /* r30 */) {}

// Range: 0x8019CDD4 -> 0x8019CDDC
enum TourEventType TourBand::EventType() {
    // References
    // -> enum TourEventType sEventType;
}

// Range: 0x8019CDDC -> 0x8019CDE4
char * TourBand::BandName() {}

// Range: 0x8019CDE4 -> 0x8019CDF8
struct DateTime TourBand::GetCreationDate(const class TourBand * const this /* r4 */) {}

// Range: 0x8019CDF8 -> 0x8019CE00
class HxGuid & TourBand::Guid() {}

// Range: 0x8019CE00 -> 0x8019CE64
unsigned char TourBand::IsLive() {}

// Range: 0x8019CE64 -> 0x8019CF34
void TourBand::BotbChallenges(const class TourBand * const this /* r29 */, class vector & tier /* r30 */) {
    // Local variables
    class TourChallengeEvent * * c; // r31
}

// Range: 0x8019CF34 -> 0x8019D094
int TourBand::Reward(const class TourBand * const this /* r27 */, unsigned char use_moment /* r28 */) {
    // Local variables
    class TourEvent * e; // r31
    int total_reward; // r30
    int i; // r29
    int stars; // r26
    int money_per_star; // r25

    // References
    // -> enum TourEventType sEventType;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol hardcore_item; // size: 0x4, address: 0x80A4D210
// Range: 0x8019D094 -> 0x8019D1B8
unsigned char TourBand::IsHardcoreWinning(const class TourBand * const this /* r30 */) {
    // Local variables
    class TourWorldEvent * e; // r30

    // References
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol hardcore_item;
    // -> enum TourEventType sEventType;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8019D1B8 -> 0x8019D244
class TourStaff * TourBand::Staff(const class TourBand * const this /* r31 */) {
    // Local variables
    const class vector & staff; // r0
    class TourStaff * const * s; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8019D244 -> 0x8019D290
class TourStaff * TourBand::ModifierStaff(const class TourBand * const this /* r31 */) {}

static class Symbol tour_met_town_stars; // size: 0x4, address: 0x80A4D218
static class Symbol tour_more_town_stars; // size: 0x4, address: 0x80A4D220
// Range: 0x8019D290 -> 0x8019D728
unsigned char TourBand::WorldEventReqs(const class TourBand * const this /* r25 */, const class TourWorldEvent * e /* r26 */, class vector * reqs /* r27 */, class Symbol & town /* r28 */, int town_stars /* r29 */, int world_stars /* r30 */) {
    // Local variables
    unsigned char met; // r22
    const class TourTown * t; // r0
    int town_stars_required; // r0
    struct TourRequirement r; // r1+0x48
    int buzz_required; // r0

    // References
    // -> static class Symbol tour_more_town_stars;
    // -> static class Symbol tour_met_town_stars;
    // -> const char * gNullStr;
}

// Range: 0x8019D728 -> 0x8019D8E4
unsigned char TourBand::WorldStaffReqs(const class TourBand * const this /* r28 */, const class TourStaff * s /* r29 */, class vector * reqs /* r30 */) {
    // Local variables
    unsigned char met; // r0
}

// Range: 0x8019D8E4 -> 0x8019D934
class TourHint * TourBand::Hint() {
    // Local variables
    class vector & hints; // r0

    // References
    // -> unsigned char sUnlockAll;
}

// Range: 0x8019D934 -> 0x8019D994
class TourHint * TourBand::FindHint(class Symbol & name /* r30 */) {
    // Local variables
    class vector & hints; // r0
    class TourHint * const * h; // r0
}

// Range: 0x8019D994 -> 0x8019D9B0
class vector & TourBand::Hints() {
    // References
    // -> enum TourEventType sEventType;
}

// Range: 0x8019D9B0 -> 0x8019D9B8
enum Difficulty TourBand::WinDifficulty() {}

// Range: 0x8019D9B8 -> 0x8019D9C0
int TourBand::TourScore() {}

// Range: 0x8019D9C0 -> 0x8019DA9C
int TourBand::Fame(const class TourBand * const this /* r28 */, const class TourWorldEvent * e /* r29 */, class Symbol & venue /* r30 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x8019DA9C -> 0x8019DAD0
int TourBand::EventStars() {
    // Local variables
    const struct WorldState * f; // r0
}

// Range: 0x8019DAD0 -> 0x8019DB10
char * TourBand::EventStarsStr() {
    // Local variables
    int stars; // r4

    // References
    // -> const char * gNullStr;
    // -> class Scoring * TheScoring;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8019DB10 -> 0x8019DCF8
int TourBand::VenueFame(const class TourBand * const this /* r28 */, class Symbol & town /* r29 */, class Symbol & venue /* r30 */) {
    // Local variables
    class Symbol tier_name; // r1+0x3C
    const class TourTier * tier; // r0
    int stars; // r31
    struct _List_iterator o; // r1+0x38
    struct WorldState * s; // r0

    // References
    // -> const char * gNullStr;
}

// Range: 0x8019DCF8 -> 0x8019DD44
int TourBand::TownFame(const class TourBand * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x8019DD44 -> 0x8019DD90
int TourBand::TotalTownFame(const class TourBand * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x8019DD90 -> 0x8019DE90
int TourBand::TotalVenueFame(const class TourBand * const this /* r26 */, class Symbol & venue_name /* r27 */) {
    // Local variables
    const class TourTown * town; // r31
    int total; // r30
    class vector events; // r1+0x10
    class TourVenue * const * v; // r29
    class TourWorldEvent * * e; // r28

    // References
    // -> const char * gNullStr;
}

// Range: 0x8019DE90 -> 0x8019DF90
int TourBand::WorldFame(const class TourBand * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x8019DF90 -> 0x8019E098
int TourBand::TotalWorldFame(const class TourBand * const this /* r27 */) {
    // Local variables
    int total; // r30
    const class vector & towns; // r0
    class TourTown * const * t; // r29
    const class vector & moments; // r0
    class TourMoment * const * m; // r29
    class TourWorldEvent * op; // r28
}

// Range: 0x8019E098 -> 0x8019E100
class String TourBand::GetLogoPatchDir(const class TourBand * const this /* r31 */) {
    // References
    // -> class String sDefaultLogo;
}

// Range: 0x8019E100 -> 0x8019E18C
class CharData * TourBand::StandIn(const class TourBand * const this /* r30 */, enum TrackType tt /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8019E18C -> 0x8019E28C
class String TourBand::GetBandLogo(const class TourBand * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> class String sDefaultLogo;
}

// Range: 0x8019E28C -> 0x8019E330
class String TourBand::GetBandLogoName(const class TourBand * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> class String sDefaultLogo;
}

// Range: 0x8019E330 -> 0x8019E340
int TourBand::GetBandLogoPos() {}

// Range: 0x8019E340 -> 0x8019E348
char * TourBand::GetMotto() {}

// Range: 0x8019E348 -> 0x8019E488
class Symbol TourBand::VenueVariant(const class TourBand * const this /* r28 */) {
    // Local variables
    class TourEvent * e; // r31
    class Symbol vv; // r1+0x1C
    const class TourTown * town; // r29
    const class TourVenue * venue; // r0

    // References
    // -> enum TourEventType sEventType;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8019E488 -> 0x8019E4B8
int TourBand::HighScore() {}

// Range: 0x8019E4B8 -> 0x8019E500
unsigned char TourBand::HasItem() {}

static class Symbol items; // size: 0x4, address: 0x80A4D228
// Range: 0x8019E500 -> 0x8019E5E8
unsigned char TourBand::HasAllItems(const class TourBand * const this /* r28 */) {
    // Local variables
    class DataArray * item_array; // r30
    int i; // r29

    // References
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol items;
}

// Range: 0x8019E5E8 -> 0x8019E744
enum TourStatus TourBand::WorldEventStatus(const class TourBand * const this /* r25 */, class TourWorldEvent * e /* r26 */, class Symbol & town /* r27 */, class Symbol & venue /* r28 */, int town_stars /* r29 */, int world_stars /* r30 */) {
    // References
    // -> unsigned char sUnlockAll;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8019E744 -> 0x8019E7F8
void TourBand::FindTowns(const class TourBand * const this /* r29 */, class vector & towns /* r30 */) {
    // Local variables
    int level; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
    // -> class DataArray * sVehicles;
    // -> unsigned char sUnlockAll;
}

// Range: 0x8019E7F8 -> 0x8019EA94
void TourBand::FindWorldEvents(const class TourBand * const this /* r26 */, class vector & events /* r27 */, const class TourTown * town /* r28 */, const class TourVenue * venue /* r29 */, unsigned char include_botb /* r30 */) {
    // Local variables
    class TourWorldEvent * const * it; // r23
    struct _List_iterator o; // r1+0x44
    class TourMoment * m; // r0
    class TourWorldEvent * opportunity; // r1+0x40

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x8019EA94 -> 0x8019EE84
enum TourStatus TourBand::TownStatus(const class TourBand * const this /* r24 */, const class TourTown * t /* r25 */, class vector & v_states /* r26 */, int world_stars /* r27 */) {
    // Local variables
    int town_stars; // r28
    enum TourStatus status; // r30
    class TourVenue * const * v; // r31
    struct VenueState vs; // r1+0x68

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P10EventState;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__P10EventState; // size: 0x8, address: 0x8089E940
// Range: 0x8019EE84 -> 0x8019F1C0
enum TourStatus TourBand::VenueStatus(const class TourBand * const this /* r21 */, const class TourTown * town /* r22 */, const class TourVenue * venue /* r23 */, class vector & e_states /* r24 */, int town_stars /* r25 */, int world_stars /* r26 */) {
    // Local variables
    struct SeenVenue sv; // r1+0x40
    unsigned char seen; // r31
    class vector events; // r1+0x48
    unsigned char played; // r30
    unsigned char locked; // r29
    unsigned char is_new; // r28
    class TourWorldEvent * * e; // r27
    struct EventState es; // r1+0x38

    // References
    // -> const char * gNullStr;
}

// Range: 0x8019F1C0 -> 0x8019F1C8
int TourBand::NumUnlockedVenues() {}

// Range: 0x8019F1C8 -> 0x8019F25C
int TourBand::NumNewTownEvents(const class TourBand * const this /* r27 */, class Symbol & town /* r28 */) {
    // Local variables
    int num_new_events; // r30
    const class TourTown * t; // r0
    class TourVenue * const * v; // r29
}

// Range: 0x8019F25C -> 0x8019F3F4
int TourBand::NumNewVenueEvents(const class TourBand * const this /* r28 */, class Symbol & venue /* r29 */) {
    // Local variables
    class vector e_states; // r1+0x38
    const class TourTown * t; // r30
    int num; // r30
    struct EventState * e; // r5
}

// Range: 0x8019F3F4 -> 0x8019F3FC
unsigned char TourBand::JustPlayedAllVenues() {}

static class Symbol item_achievements; // size: 0x4, address: 0x80A4D230
// Range: 0x8019F3FC -> 0x8019F4E4
class Symbol TourBand::ItemAchievement(const class TourBand * const this /* r30 */) {
    // Local variables
    const class Symbol * i; // r31

    // References
    // -> const char * gNullStr;
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol item_achievements;
}

static class Symbol region_achievements; // size: 0x4, address: 0x80A4D238
// Range: 0x8019F4E4 -> 0x8019F5F0
class Symbol TourBand::RegionAchievement(const class TourBand * const this /* r27 */) {
    // Local variables
    class DataArray * a; // r31
    int i; // r30
    class DataArray * r; // r29
    int j; // r28

    // References
    // -> const char * gNullStr;
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol region_achievements;
}

// Range: 0x8019F5F0 -> 0x8019F5F8
unsigned char TourBand::IsIronBladder() {}

// Range: 0x8019F5F8 -> 0x8019F604
void TourBand::ResetIronBladder() {}

// Range: 0x8019F604 -> 0x8019F610
void TourBand::FailIronBladder() {}

static class Symbol buzz; // size: 0x4, address: 0x80A4D240
static class Symbol venue_diff; // size: 0x4, address: 0x80A4D248
// Range: 0x8019F610 -> 0x8019F7B8
int TourBand::BuzzBase(const class TourBand * const this /* r28 */, const class TourWorldEvent * e /* r29 */) {
    // Local variables
    class Symbol venue; // r1+0x20
    class DataArray * a; // r31
    int base_players; // r30
    class vector users; // r1+0x24
    class BandUser * const * u; // r29

    // References
    // -> class DataArray * sWorldConfig;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
    // -> static class Symbol venue_diff;
    // -> static class Symbol buzz;
}

static class Symbol buzz; // size: 0x4, address: 0x80A4D250
static class Symbol win_modifiers; // size: 0x4, address: 0x80A4D258
static class Symbol stars; // size: 0x4, address: 0x80A4D260
static class Symbol event_replayed; // size: 0x4, address: 0x80A4D268
static class Symbol staff; // size: 0x4, address: 0x80A4D270
// Range: 0x8019F7B8 -> 0x8019FCC0
int TourBand::BuzzChangeSong(const class TourBand * const this /* r24 */, const class TourWorldEvent * e /* r25 */, int num_stars /* r26 */) {
    // Local variables
    float modifier; // f31
    class DataArray * buzz_cfg; // r29
    class DataArray * modifiers; // r28
    int i; // r27
    class Symbol mod_type; // r1+0x20
    class DataArray * star_range; // r22
    class DataArrayPtr args; // r1+0x58
    class DataArrayPtr args; // r1+0x50

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol staff;
    // -> static class Symbol event_replayed;
    // -> static class Symbol stars;
    // -> static class Symbol win_modifiers;
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol buzz;
}

class _List_node : public _List_node_base {
    // total size: 0x14
public:
    struct ChallengePrereq _M_data; // offset 0x8, size 0xC
};
// Range: 0x8019FCC0 -> 0x8019FCD8
int TourBand::Buzz() {}

// Range: 0x8019FCD8 -> 0x8019FCE0
int TourBand::Fans() {}

// Range: 0x8019FCE0 -> 0x8019FCF8
int TourBand::FansChange() {}

static class Symbol tour_band_fans_gained; // size: 0x4, address: 0x80A4D278
static class Symbol tour_band_fans_lost; // size: 0x4, address: 0x80A4D280
static class Symbol tour_band_fans_cap; // size: 0x4, address: 0x80A4D288
static class Symbol tour_band_fans_maxcap; // size: 0x4, address: 0x80A4D290
static class Symbol tour_band_fans_nochange; // size: 0x4, address: 0x80A4D298
// Range: 0x8019FCF8 -> 0x8019FE8C
class Symbol TourBand::FansUpdateToken() {
    // Local variables
    class Symbol token; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
    // -> static class Symbol tour_band_fans_nochange;
    // -> static class Symbol tour_band_fans_maxcap;
    // -> static class Symbol tour_band_fans_cap;
    // -> static class Symbol tour_band_fans_lost;
    // -> static class Symbol tour_band_fans_gained;
}

// Range: 0x8019FE8C -> 0x8019FF3C
class Sequence * TourBand::FansUpdateSfx(class ObjectDir * dir /* r6 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Sequence;
}

// Range: 0x8019FF3C -> 0x801A0000
int TourBand::FansLostOnFail(const class TourBand * const this /* r29 */) {
    // Local variables
    class TourWorldEvent * e; // r31
    int new_buzz; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol buzz; // size: 0x4, address: 0x80A4D2A0
static class Symbol caps; // size: 0x4, address: 0x80A4D2A8
static class Symbol cap; // size: 0x4, address: 0x80A4D2B0
// Range: 0x801A0000 -> 0x801A00FC
int TourBand::BuzzCap(enum Difficulty diff /* r30 */) {
    // References
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol cap;
    // -> static class Symbol caps;
    // -> static class Symbol buzz;
}

static class Symbol buzz; // size: 0x4, address: 0x80A4D2B8
static class Symbol buzz_achievement; // size: 0x4, address: 0x80A4D2C0
// Range: 0x801A00FC -> 0x801A01B0
int TourBand::BuzzAchievement() {
    // References
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol buzz_achievement;
    // -> static class Symbol buzz;
}

// Range: 0x801A01B0 -> 0x801A02AC
void TourBand::TownMaxPlayersDiff(const class TourBand * const this /* r26 */, class Symbol & town /* r27 */, int & players /* r28 */, enum Difficulty & diff /* r29 */) {
    // Local variables
    enum Difficulty v_diff; // r1+0x18
    int v_players; // r1+0x14
    const class TourTown * t; // r0
    class TourVenue * const * v; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801A02AC -> 0x801A03F4
void TourBand::VenueMaxPlayersDiff(const class TourBand * const this /* r27 */, class Symbol & venue /* r28 */, int & players /* r29 */, enum Difficulty & diff /* r30 */) {
    // Local variables
    enum Difficulty e_diff; // r1+0x1C
    int e_players; // r1+0x18
    class vector events; // r1+0x20
    const class TourTown * t; // r31
    class TourWorldEvent * * e; // r31
}

// Range: 0x801A03F4 -> 0x801A0474
void TourBand::AdjustMaxPlayerDiff(int new_players /* r1+0x8 */) {}

// Range: 0x801A0474 -> 0x801A04D8
void TourBand::WorldEventMaxPlayersDiff(int & players /* r30 */, enum Difficulty & diff /* r31 */) {
    // Local variables
    const struct WorldState * f; // r0
}

// Range: 0x801A04D8 -> 0x801A0578
class Symbol TourBand::AvailableItem(const class TourBand * const this /* r29 */, class TourWorldEvent * e /* r30 */) {
    // Local variables
    enum TourStatus s; // r0

    // References
    // -> const char * gNullStr;
}

// Range: 0x801A0578 -> 0x801A0660
char * TourBand::TownIcon(const class TourBand * const this /* r26 */, class Symbol & town /* r27 */) {
    // Local variables
    const class TourTown * t; // r0
    const char * icon; // r29
    const char * botb_icon; // r0
    class TourVenue * const * v; // r28
    const char * venue_icon; // r3

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801A0660 -> 0x801A08A8
char * TourBand::VenueIcon(const class TourBand * const this /* r26 */, class Symbol & venue /* r27 */) {
    // Local variables
    class vector events; // r1+0x50
    const class TourTown * t; // r30
    const char * icon; // r31
    const char * botb_icon; // r0
    class vector e_states; // r1+0x44
    enum TourStatus venue_status; // r0
    class TourWorldEvent * * e; // r27
    const char * event_icon; // r30

    // References
    // -> const char * gNullStr;
}

// Range: 0x801A08A8 -> 0x801A0928
char * TourBand::WorldEventIcon(const class TourBand * const this /* r30 */, class TourWorldEvent * e /* r31 */) {
    // Local variables
    class Symbol item; // r1+0x10

    // References
    // -> const char * gNullStr;
}

static class Symbol items; // size: 0x4, address: 0x80A4D2C8
static class Symbol icon; // size: 0x4, address: 0x80A4D2D0
// Range: 0x801A0928 -> 0x801A0A40
char * TourBand::ItemToStr(class Symbol & item /* r30 */) {
    // Local variables
    class DataArray * item_array; // r0
    class DataArray * i; // r0

    // References
    // -> class Debug TheDebug;
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol icon;
    // -> static class Symbol items;
    // -> const char * gNullStr;
}

static class Symbol botb_icon; // size: 0x4, address: 0x80A4D2D8
// Range: 0x801A0A40 -> 0x801A0AB4
char * TourBand::BotbIcon() {
    // References
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol botb_icon;
}

static class Symbol items; // size: 0x4, address: 0x80A4D2E0
// Range: 0x801A0AB4 -> 0x801A0D14
class TourWorldEvent * TourBand::NextItemEvent(const class TourBand * const this /* r29 */) {
    // Local variables
    class DataArray * item_progression; // r31
    int i; // r30
    class Symbol item; // r1+0x30
    const class vector & towns; // r0
    class vector venues; // r1+0x40
    class vector events; // r1+0x34
    class TourTown * const * t; // r26
    const class vector & venues; // r0
    class TourVenue * const * v; // r25
    class TourWorldEvent * * e; // r24

    // References
    // -> class Debug TheDebug;
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol items;
}

// Range: 0x801A0D14 -> 0x801A0DD4
class Symbol TourBand::NextItemTown(const class TourBand * const this /* r30 */) {
    // Local variables
    class TourWorldEvent * event; // r31

    // References
    // -> const char * gNullStr;
}

static class Symbol buzz; // size: 0x4, address: 0x80A4D2E8
static class Symbol lose_modifiers; // size: 0x4, address: 0x80A4D2F0
// Range: 0x801A0DD4 -> 0x801A0FBC
int TourBand::BuzzLosePenalty(const class TourBand * const this /* r28 */) {
    // Local variables
    class TourWorldEvent * world_event; // r29
    int base_buzz_change; // r0
    class Symbol venue; // r1+0x1C
    class DataArray * l; // r29
    float modifier; // f2

    // References
    // -> class DataArray * sWorldConfig;
    // -> const char * gNullStr;
    // -> static class Symbol lose_modifiers;
    // -> static class Symbol buzz;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801A0FBC -> 0x801A1010
int TourBand::NewBuzz(int old_buzz /* r31 */) {}

static class Symbol none; // size: 0x4, address: 0x80A4D2F8
// Range: 0x801A1010 -> 0x801A1090
class Symbol TourBand::Vehicle(const class TourBand * const this /* r31 */) {
    // Local variables
    int level; // r4

    // References
    // -> class DataArray * sVehicles;
    // -> static class Symbol none;
}

// Range: 0x801A1090 -> 0x801A1128
int TourBand::VehicleLevel(const class TourBand * const this /* r28 */) {
    // Local variables
    int level; // r31
    const class DataArray * vehicles; // r30
    int i; // r29

    // References
    // -> class DataArray * sVehicles;
}

// Range: 0x801A1128 -> 0x801A1130
class TourMoment * TourBand::Moment() {}

class Interpolator {
    // total size: 0x14
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    float mY0; // offset 0x4, size 0x4
    float mY1; // offset 0x8, size 0x4
    float mX0; // offset 0xC, size 0x4
    float mX1; // offset 0x10, size 0x4
};
class LinearInterpolator : public Interpolator {
    // total size: 0x1C
protected:
    float mSlope; // offset 0x14, size 0x4
    float mB; // offset 0x18, size 0x4
};
// Range: 0x801A1130 -> 0x801A134C
int TourBand::BuzzToFans(int buzz /* r27 */) {
    // Local variables
    float min_fans; // f31
    float max_fans; // f30
    float min_buzz; // f29
    float max_buzz; // f28
    class DataArray * f; // r29
    int i; // r28
    float upper_buzz; // f27
    float upper_fans; // f1
    class LinearInterpolator interp; // r1+0xC

    // References
    // -> class DataArray * sWorldConfig;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801A138C -> 0x801A13D8
class Symbol TourBand::VenueToken() {}

// Range: 0x801A13D8 -> 0x801A1598
class Symbol TourBand::FirstLockedVenue(const class TourBand * const this /* r29 */) {
    // Local variables
    const class TourTown * t; // r31
    class vector e_states; // r1+0x40
    class TourVenue * const * v; // r30

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801A1598 -> 0x801A1630
unsigned char TourBand::CanLeaveHometown() {
    // Local variables
    class vector towns; // r1+0xC
}

// Range: 0x801A1630 -> 0x801A17E8
unsigned char TourBand::CanLeaveHomeVenue(const class TourBand * const this /* r28 */) {
    // Local variables
    class vector e_states; // r1+0x34
    const class TourTown * h; // r31
    int num_playable; // r30
    class TourVenue * const * v; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801A17E8 -> 0x801A1A38
class TourWorldEvent * TourBand::FindWorldEvent(const class TourBand * const this /* r28 */, class Symbol & name /* r31 */) {
    // Local variables
    class vector events; // r1+0x24
    const class TourTown * t; // r30
    class TourWorldEvent * const * e; // r30
    const class vector & moments; // r0
    class TourMoment * const * m; // r29
    class TourWorldEvent * e; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x801A1A38 -> 0x801A1B30
class Symbol TourBand::Song(const class TourBand * const this /* r30 */) {
    // Local variables
    class TourEvent * e; // r0
    int num_complete; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

static class Symbol win_item; // size: 0x4, address: 0x80A4D300
// Range: 0x801A1B30 -> 0x801A1C98
unsigned char TourBand::IsWinning(const class TourBand * const this /* r29 */) {
    // Local variables
    class TourWorldEvent * e; // r30

    // References
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol win_item;
    // -> enum TourEventType sEventType;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801A1C98 -> 0x801A1CDC
class PersistentGameData * TourBand::GetPersistentGameData() {
    // Local variables
    class TourEvent * e; // r0

    // References
    // -> class PersistentGameData sPersistentGameData;
}

// Range: 0x801A1CDC -> 0x801A1D4C
void TourBand::SetBotbRivalBandData(class TourBand * const this /* r29 */, int score /* r30 */, int stars /* r31 */) {}

// Range: 0x801A1D4C -> 0x801A1D98
char * TourBand::GetBotbRivalBandName(const class TourBand * const this /* r31 */) {
    // Local variables
    class TourEvent * e; // r0

    // References
    // -> const char * gNullStr;
}

// Range: 0x801A1D98 -> 0x801A1DF0
int TourBand::GetBotbRivalBandScore(const class TourBand * const this /* r31 */) {
    // Local variables
    class TourEvent * e; // r0
}

// Range: 0x801A1DF0 -> 0x801A1E3C
int TourBand::GetBotbRivalBandStars(const class TourBand * const this /* r31 */) {
    // Local variables
    class TourEvent * e; // r0
}

// Range: 0x801A1E3C -> 0x801A1E44
char * TourBand::GetBotbScoreString() {}

// Range: 0x801A1E44 -> 0x801A1EA0
unsigned char TourBand::GetBotbBattleIsBrandNew(const class TourBand * const this /* r31 */) {
    // Local variables
    class TourEvent * e; // r0
}

// Range: 0x801A1EA0 -> 0x801A1EB0
class String TourBand::GetBandIcon() {}

// Range: 0x801A1EB0 -> 0x801A1F80
class String TourBand::GetBotbRivalBandIcon() {
    // Local variables
    class TourEvent * e; // r0

    // References
    // -> class Debug TheDebug;
    // -> class String sDefaultLogo;
    // -> class String sRivalLogo;
}

// Range: 0x801A1F80 -> 0x801A20C0
class String TourBand::GetBotbRivalBandIconPath() {
    // Local variables
    class TourEvent * e; // r0

    // References
    // -> class Debug TheDebug;
    // -> class String sDefaultLogo;
    // -> class String sRivalLogo;
}

// Range: 0x801A20C0 -> 0x801A2234
float TourBand::GetBotbTargetStartAccumScore(const class TourBand * const this /* r29 */) {
    // Local variables
    class TourEvent * e; // r0

    // References
    // -> class Debug TheDebug;
}

// Range: 0x801A2234 -> 0x801A23A8
float TourBand::GetBotbTargetEndAccumScore(const class TourBand * const this /* r29 */) {
    // Local variables
    class TourEvent * e; // r0

    // References
    // -> class Debug TheDebug;
}

// Range: 0x801A23A8 -> 0x801A2404
unsigned char TourBand::GetNoOverdrive(const class TourBand * const this /* r31 */) {
    // Local variables
    class TourEvent * e; // r0
}

// Range: 0x801A2404 -> 0x801A2438
unsigned char TourBand::GetNoCrowdMeter() {
    // Local variables
    class TourEvent * e; // r0
}

// Range: 0x801A2438 -> 0x801A246C
unsigned char TourBand::GetNoBackFromBrink() {
    // Local variables
    class TourEvent * e; // r0
}

// Range: 0x801A246C -> 0x801A24A0
enum WinMetric TourBand::GetWinMetric() {
    // Local variables
    class TourEvent * e; // r0
}

// Range: 0x801A24A0 -> 0x801A260C
class Symbol TourBand::RequiredPart(const class TourBand * const this /* r29 */) {
    // Local variables
    class Symbol part; // r1+0x20
    class vector users; // r1+0x24
    int num_guitarists; // r31
    class BandUser * * u; // r30
    class TourEvent * e; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x801A260C -> 0x801A2670
enum Difficulty TourBand::MinDifficultySelect() {
    // Local variables
    class TourEvent * e; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801A2670 -> 0x801A2678
class Symbol TourBand::Hometown() {}

// Range: 0x801A2678 -> 0x801A2680
class Symbol TourBand::Town() {}

// Range: 0x801A2680 -> 0x801A2688
class Symbol TourBand::Venue() {}

// Range: 0x801A2688 -> 0x801A26AC
class TourEvent * TourBand::CurEvent() {
    // References
    // -> enum TourEventType sEventType;
}

// Range: 0x801A26AC -> 0x801A26EC
class TourWorldEvent * TourBand::CurWorldEvent() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x801A26EC -> 0x801A2730
class TourChallengeEvent * TourBand::CurChallengeEvent() {
    // References
    // -> const char * gNullStr;
}

static class DebugWarner _dw; // size: 0x100, address: 0x80979F60
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x801A2730 -> 0x801A293C
enum TourStatus TourBand::ChallengeStatus(const class TourBand * const this /* r29 */, class TourChallengeEvent * e /* r24 */, class list * states /* r30 */) {
    // Local variables
    const class list & prereqs; // r31
    struct _List_iterator p; // r1+0x5C
    unsigned char all; // r0
    struct _List_iterator s; // r1+0x58
    unsigned char prereq_ok; // r24
    class Symbol event_name; // r1+0x54

    // References
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
    // -> unsigned char sUnlockAll;
}

static class Symbol band; // size: 0x4, address: 0x80A4D308
// Range: 0x801A293C -> 0x801A2D24
int TourBand::NumNewChallenges(const class TourBand * const this /* r27 */, class TourChallengeEvent * e /* r28 */) {
    // Local variables
    class list new_states; // r1+0x70
    class vector & songs; // r29
    int i; // r26
    struct SongState ss; // r1+0x68
    int new_num; // r26
    class vector tier; // r1+0x78
    int i; // r29
    class TourChallengeEvent * * c; // r30

    // References
    // -> static class Symbol band;
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__PQ214ChallengeState9SongState;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<14ChallengeState>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ214ChallengeState9SongState; // size: 0x8, address: 0x8089ECD0
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std28_List_node<14ChallengeState>; // size: 0x8, address: 0x8089ED08
// Range: 0x801A2D24 -> 0x801A2D4C
int TourBand::ChallengeMaxPlayers() {}

// Range: 0x801A2D4C -> 0x801A2D74
enum Difficulty TourBand::ChallengeMaxDiff() {}

// Range: 0x801A2D74 -> 0x801A2E18
int TourBand::ChallengeStars(class TourChallengeEvent * e /* r28 */) {
    // Local variables
    const class vector & songs; // r0
    int total; // r30
    int i; // r29
    const struct SongState * s; // r0
}

// Range: 0x801A2E18 -> 0x801A2E74
unsigned char TourBand::IsChallengeSongPlayed(class Symbol & song /* r30 */) {
    // Local variables
    const class vector & songs; // r0
}

// Range: 0x801A2E74 -> 0x801A2E7C
class list & TourBand::NewChallengeUnlocks() {}

// Range: 0x801A2E7C -> 0x801A2ED0
int TourBand::NumNewChallengeUnlocks() {}

static class Symbol tour_challenge_min_players; // size: 0x4, address: 0x80A4D310
static class Symbol tour_challenge_req_instruments; // size: 0x4, address: 0x80A4D318
// Range: 0x801A2ED0 -> 0x801A33D0
unsigned char TourBand::ChallengeEventReqs(const class TourBand * const this /* r28 */, const class TourChallengeEvent * e /* r29 */, class vector * reqs /* r30 */) {
    // Local variables
    class vector users; // r1+0x4C
    int min_players; // r31
    unsigned char met; // r25
    struct TourRequirement r; // r1+0x80
    class Symbol track; // r1+0x48
    enum TrackType track_type; // r25
    unsigned char met; // r26
    class BandUser * * u; // r27
    struct TourRequirement r; // r1+0x58

    // References
    // -> static class Symbol tour_challenge_req_instruments;
    // -> static class Symbol tour_challenge_min_players;
    // -> const char * gNullStr;
}

// Range: 0x801A33D0 -> 0x801A34E4
unsigned char TourBand::IsChallengeIncomplete(const class TourBand * const this /* r26 */, class TourChallengeEvent * e /* r27 */) {
    // Local variables
    unsigned char played_any; // r30
    unsigned char played_all; // r29
    int num_songs; // r0
    int i; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801A34E4 -> 0x801A3568
unsigned char TourBand::IsChallengeImpossible(const class TourBand * const this /* r31 */, class TourChallengeEvent * e /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801A3568 -> 0x801A3570
enum ChallengeFocus TourBand::GetChallengeFocus() {}

// Range: 0x801A3570 -> 0x801A3608
unsigned char TourBand::HasUnlockedImpossibleChallenge(const class TourBand * const this /* r31 */) {
    // Local variables
    struct _List_iterator n; // r1+0x1C
}

// Range: 0x801A3608 -> 0x801A3658
struct ChallengeState & TourBand::FindChallengeState(const class TourBand * const this /* r30 */, class list * states /* r31 */) {}

// Range: 0x801A3658 -> 0x801A3670
unsigned char __eq() {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x801A3670 -> 0x801A38B4
struct ChallengeState & TourBand::FindChallengeState(class Symbol & event_name /* r28 */, class list * states /* r30 */) {
    // Local variables
    struct _List_iterator c; // r1+0x3C
    struct ChallengeState cs; // r1+0x40

    // References
    // -> struct [anonymous] __RTTI__PQ214ChallengeState9SongState;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<14ChallengeState>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
}

// Range: 0x801A38B4 -> 0x801A390C
unsigned char TourBand::IsChallengeCompleted(const class TourBand * const this /* r30 */, class list * states /* r31 */) {
    // Local variables
    class TourChallengeEvent * e; // r0
}

// Range: 0x801A390C -> 0x801A3A00
unsigned char TourBand::IsChallengeCompleted(const class TourBand * const this /* r27 */, class TourChallengeEvent * e /* r28 */, class list * states /* r29 */) {
    // Local variables
    int num_songs; // r0
    int i; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol tour_band_outfit; // size: 0x4, address: 0x80A4D320
static class Symbol mic; // size: 0x4, address: 0x80A4D328
static class Symbol vocals; // size: 0x4, address: 0x80A4D330
static class Symbol tour_band_outfit; // size: 0x4, address: 0x80A4D338
static class Symbol win_item; // size: 0x4, address: 0x80A4D340
static class Symbol win_instruments; // size: 0x4, address: 0x80A4D348
static class Symbol vocals; // size: 0x4, address: 0x80A4D350
static class Symbol mic; // size: 0x4, address: 0x80A4D358
static class Symbol none; // size: 0x4, address: 0x80A4D360
static class Symbol tour_band_win_instruments; // size: 0x4, address: 0x80A4D368
// Range: 0x801A3A00 -> 0x801A41E8
void TourBand::CompleteEvent(class TourBand * const this /* r25 */) {
    // Local variables
    class TourEvent * e; // r29
    class vector users; // r1+0x90
    const class vector & outfits; // r0
    const struct EventOutfit * o; // r28
    class BandUser * * u; // r27
    class TourCharLocal * tc; // r26
    const class vector & insts; // r0
    const struct EventInstrument * i; // r26
    class BandUser * * u; // r27
    class TourCharLocal * tc; // r28
    class Symbol track; // r1+0x8C
    enum Difficulty min_diff; // r24
    class BandUser * * m; // r27
    class BandUser * u; // r28
    const class TourTown * town; // r0
    class TourWorldEvent * world_event; // r24
    class DataArray * instruments; // r26
    class BandUser * * m; // r27
    class BandUser * user; // r24
    class TourCharLocal * tc; // r28
    class Symbol track; // r1+0x88
    class DataArray * i; // r24
    class Symbol cat; // r1+0x84

    // References
    // -> static class Symbol tour_band_win_instruments;
    // -> static class Symbol none;
    // -> static class Symbol mic;
    // -> static class Symbol vocals;
    // -> static class Symbol win_instruments;
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol win_item;
    // -> enum TourEventType sEventType;
    // -> static class Symbol tour_band_outfit;
    // -> static class Symbol vocals;
    // -> static class Symbol mic;
    // -> static class Symbol tour_band_outfit;
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol botb_result_streak; // size: 0x4, address: 0x80A4D370
static class Symbol botb_result_score; // size: 0x4, address: 0x80A4D378
static class Symbol botb_result_mult; // size: 0x4, address: 0x80A4D380
// Range: 0x801A41E8 -> 0x801A4578
void TourBand::CompleteSong(class TourBand * const this /* r23 */, int stars /* r24 */, int score /* r25 */, int accumulated_score /* r26 */, int longest_streak /* r27 */, float total_stars /* f31 */, unsigned char cheat /* r28 */) {
    // Local variables
    class TourEvent * e; // r29
    int val; // r31
    enum WinMetric m; // r21

    // References
    // -> class RockCentralGateway RockCentral;
    // -> class Net TheNet;
    // -> static class Symbol botb_result_mult;
    // -> static class Symbol botb_result_score;
    // -> static class Symbol botb_result_streak;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__26TourChallengeCompletePanel;
    // -> class ObjectDir * sMainDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801A4578 -> 0x801A4770
void TourBand::UnlockNewChallengeSongs(class TourBand * const this /* r28 */) {
    // Local variables
    struct _List_iterator n; // r1+0x2C
    class TourChallengeEvent * new_event; // r30
    int i; // r29
    class Symbol song; // r1+0x28

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> enum TourEventType sEventType;
}

// Range: 0x801A4770 -> 0x801A4838
void TourBand::AddMoney(int money /* r30 */) {
    // Local variables
    class vector members; // r1+0xC
    class BandUser * * m; // r31
    class TourCharLocal * c; // r0

    // References
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
}

// Range: 0x801A4838 -> 0x801A48F4
struct WorldState * TourBand::FindWorldState(const class TourBand * const this /* r30 */, const class TourWorldEvent * e /* r31 */) {
    // Local variables
    class Symbol town; // r1+0x24
    class Symbol venue; // r1+0x20

    // References
    // -> const char * gNullStr;
}

// Range: 0x801A48F4 -> 0x801A4A00
struct WorldState * TourBand::FindWorldState(const class TourBand * const this /* r31 */) {
    // Local variables
    struct WorldState search; // r1+0x14
    const struct WorldState * f; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

static class Symbol torso; // size: 0x4, address: 0x80A4D388
static class Symbol male; // size: 0x4, address: 0x80A4D390
static class Symbol tour_band_city_shirt; // size: 0x4, address: 0x80A4D398
// Range: 0x801A4A00 -> 0x801A4C20
void TourBand::AwardTownShirt(class TourBand * const this /* r27 */, const struct TownUnlock & u /* r28 */) {
    // Local variables
    class vector members; // r1+0x28
    class BandUser * * m; // r30
    class BandUser * user; // r26
    class TourCharLocal * tc; // r29
    class Symbol shirt; // r1+0x24

    // References
    // -> static class Symbol tour_band_city_shirt;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
    // -> static class Symbol male;
    // -> static class Symbol torso;
}

static class Symbol tour_band_multiple_char; // size: 0x4, address: 0x80A4D3A0
// Range: 0x801A4C20 -> 0x801A4C9C
void TourBand::AddCharUnlock(class TourBand * const this /* r31 */) {
    // References
    // -> static class Symbol tour_band_multiple_char;
    // -> const char * gNullStr;
}

// Range: 0x801A4C9C -> 0x801A4D5C
int TourBand::TotalStars(const class TourBand * const this /* r29 */, unsigned char cap /* r28 */) {
    // Local variables
    const int * end_star; // r30
    int total; // r31
    const int * sit; // r29
}

// Range: 0x801A4D5C -> 0x801A4F70
unsigned char TourBand::IsLastEvent(const class TourBand * const this /* r27 */) {
    // Local variables
    const class TourEvent * last_event; // r31
    class vector venues; // r1+0x2C
    class vector events; // r1+0x20
    const class TourTown * t; // r30
    class TourVenue * const * v; // r29
    class TourWorldEvent * * e; // r28

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801A4F70 -> 0x801A4FAC
unsigned char TourBand::CheckReqs() {
    // Local variables
    const struct TourRequirement * r; // r3
}

// Range: 0x801A4FAC -> 0x801A5134
unsigned char TourBand::ItemReq(class Symbol & item /* r30 */, class vector * reqs /* r28 */) {
    // Local variables
    unsigned char met; // r29
    struct TourRequirement r; // r1+0x20

    // References
    // -> const char * gNullStr;
}

static class Symbol tour_met_fans; // size: 0x4, address: 0x80A4D3A8
static class Symbol tour_more_fans; // size: 0x4, address: 0x80A4D3B0
// Range: 0x801A5134 -> 0x801A535C
unsigned char TourBand::BuzzReq(const class TourBand * const this /* r28 */, int buzz_required /* r29 */, class vector * reqs /* r30 */) {
    // Local variables
    unsigned char met; // r31
    struct TourRequirement r; // r1+0x18
    int fans_required; // r29

    // References
    // -> static class Symbol tour_more_fans;
    // -> static class Symbol tour_met_fans;
    // -> const char * gNullStr;
}

static class Symbol tour_more_stars; // size: 0x4, address: 0x80A4D3B8
// Range: 0x801A535C -> 0x801A553C
unsigned char TourBand::WorldStarsReq(int stars_required /* r28 */, class vector * reqs /* r29 */, int world_stars /* r31 */) {
    // Local variables
    unsigned char met; // r30
    struct TourRequirement r; // r1+0x18

    // References
    // -> static class Symbol tour_more_stars;
    // -> const char * gNullStr;
}

// Range: 0x801A553C -> 0x801A55F4
void TourBand::ClearStandIns(class TourBand * const this /* r27 */) {
    // Local variables
    int i; // r30
    class TourCharRemote * tcr; // r29
    int i; // r28

    // References
    // -> class CharCache * TheCharCache;
}

// Range: 0x801A55F4 -> 0x801A56A0
class BinStream & __ls(class BinStream & s /* r30 */, const struct WorldState & f /* r31 */) {}

// Range: 0x801A56A0 -> 0x801A5770
class BinStream & __rs(class BinStream & s /* r29 */, struct WorldState & f /* r30 */) {
    // Local variables
    int prev_star_crap; // r1+0xC
    int max_diff; // r1+0x8

    // References
    // -> int sVer;
}

// Range: 0x801A5770 -> 0x801A57B8
class BinStream & __ls(class BinStream & s /* r30 */, const struct SeenVenue & vs /* r31 */) {}

// Range: 0x801A57B8 -> 0x801A5800
class BinStream & __rs(class BinStream & s /* r30 */, struct SeenVenue & vs /* r31 */) {}

class Symbol mName; // size: 0x4, address: 0x80A4D3BC
class vector : protected _Vector_base {
    // total size: 0xC
};
class vector mSongs; // size: 0xC, address: 0x8097A06C
// Range: 0x801A5800 -> 0x801A58D4
class BinStream & __ls(class BinStream & s /* r29 */, const struct ChallengeState & cs /* r30 */) {
    // Local variables
    const struct SongState * sit; // r31
}

// Range: 0x801A58D4 -> 0x801A5B40
class BinStream & __rs(class BinStream & s /* r30 */, struct ChallengeState & cs /* r31 */) {
    // Local variables
    int diff; // r1+0x34
    unsigned int size; // r1+0x30
    int i; // r29
    struct SongState ss; // r1+0x38
    class vector crap; // r1+0x40
    int old_accum_score; // r1+0x2C
    int crap; // r1+0x28

    // References
    // -> const char * gNullStr;
    // -> int sVer;
}

// Range: 0x801A5B40 -> 0x801A5B8C
class BinStream & __ls(class BinStream & s /* r30 */, const struct OpportunityLoc & f /* r31 */) {}

// Range: 0x801A5B8C -> 0x801A5BD8
class BinStream & __rs(class BinStream & s /* r30 */, struct OpportunityLoc & f /* r31 */) {}

// Range: 0x801A5BD8 -> 0x801A5D98
void TourBand::SaveCommon(const class TourBand * const this /* r29 */, class BinStream & s /* r30 */, unsigned int dirtyMask /* r31 */) {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
static class Symbol hints; // size: 0x4, address: 0x80A4D3C4
// Range: 0x801A5D98 -> 0x801A6174
void TourBand::LoadCommon(class TourBand * const this /* r28 */, class BinStream & s /* r29 */, unsigned int dirtyMask /* r30 */) {
    // Local variables
    class Symbol restore_crap; // r1+0x48
    class vector unlocked_venues_crap; // r1+0x58
    int diff; // r1+0x44
    class vector hints_seen_crap; // r1+0x4C
    class Symbol unlocked_item_crap; // r1+0x40
    int bs; // r1+0x3C

    // References
    // -> class DataArray * sChallengeConfig;
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol hints;
    // -> int sVer;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x801A6174 -> 0x801A6208
void TourBand::SaveHints(class BinStream & s /* r29 */, const class vector & hints /* r30 */) {
    // Local variables
    class TourHint * const * h; // r31
}

// Range: 0x801A6208 -> 0x801A6344
void TourBand::LoadHints(class BinStream & s /* r27 */, class vector & hints /* r28 */, class DataArray * cfg /* r29 */) {
    // Local variables
    int num_hints; // r1+0x20
    int i; // r30
}

// Range: 0x801A6344 -> 0x801A6448
class TourWorldEvent * TourBand::FirstEvent(const class TourBand * const this /* r28 */, class Symbol & venue /* r29 */) {
    // Local variables
    class vector events; // r1+0x18
    const class TourTown * t; // r30
}

// Range: 0x801A6448 -> 0x801A65E8
void TourBand::GetRoster(const class TourBand * const this /* r29 */, class vector & members /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x801A65E8 -> 0x801A6684
class DataNode TourBand::OnTownFame(class TourBand * const this /* r30 */, class DataArray * a /* r31 */) {
    // Local variables
    class Symbol town; // r1+0x18
}

// Range: 0x801A6684 -> 0x801A6724
class DataNode TourBand::OnTotalTownFame(class TourBand * const this /* r30 */, class DataArray * a /* r31 */) {
    // Local variables
    class Symbol town; // r1+0x18
}

// Range: 0x801A6724 -> 0x801A682C
class DataNode TourBand::OnWorldEventStatus(class TourBand * const this /* r29 */, class DataArray * a /* r31 */) {
    // Local variables
    class TourWorldEvent * e; // r30

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14TourWorldEvent;
}

// Range: 0x801A682C -> 0x801A6938
class DataNode TourBand::OnVenueStatus(class TourBand * const this /* r28 */, class DataArray * a /* r29 */) {
    // Local variables
    class vector e_states; // r1+0x28
    const class TourTown * t; // r30
}

// Range: 0x801A6938 -> 0x801A6AA0
class DataNode TourBand::OnTownStatus(class TourBand * const this /* r31 */) {
    // Local variables
    class vector vs; // r1+0x34
}

static class Symbol _s; // size: 0x4, address: 0x80A4D3CC
static class Symbol _s; // size: 0x4, address: 0x80A4D3D4
static class Symbol _s; // size: 0x4, address: 0x80A4D3DC
static class Symbol _s; // size: 0x4, address: 0x80A4D3E4
static class Symbol _s; // size: 0x4, address: 0x80A4D3EC
static class Symbol _s; // size: 0x4, address: 0x80A4D3F4
static class Symbol _s; // size: 0x4, address: 0x80A4D3FC
static class Symbol _s; // size: 0x4, address: 0x80A4D404
static class Symbol _s; // size: 0x4, address: 0x80A4D40C
static class Symbol _s; // size: 0x4, address: 0x80A4D414
static class Symbol _s; // size: 0x4, address: 0x80A4D41C
static class Symbol _s; // size: 0x4, address: 0x80A4D424
static class Symbol _s; // size: 0x4, address: 0x80A4D42C
static class Symbol _s; // size: 0x4, address: 0x80A4D434
static class Symbol _s; // size: 0x4, address: 0x80A4D43C
static class Symbol _s; // size: 0x4, address: 0x80A4D444
static class Symbol _s; // size: 0x4, address: 0x80A4D44C
static class Symbol _s; // size: 0x4, address: 0x80A4D454
static class Symbol _s; // size: 0x4, address: 0x80A4D45C
static class Symbol _s; // size: 0x4, address: 0x80A4D464
static class Symbol _s; // size: 0x4, address: 0x80A4D46C
static class Symbol _s; // size: 0x4, address: 0x80A4D474
static class Symbol _s; // size: 0x4, address: 0x80A4D47C
static class Symbol _s; // size: 0x4, address: 0x80A4D484
static class Symbol _s; // size: 0x4, address: 0x80A4D48C
static class Symbol _s; // size: 0x4, address: 0x80A4D494
static class Symbol _s; // size: 0x4, address: 0x80A4D49C
static class Symbol _s; // size: 0x4, address: 0x80A4D4A4
static class Symbol _s; // size: 0x4, address: 0x80A4D4AC
static class Symbol _s; // size: 0x4, address: 0x80A4D4B4
static class Symbol _s; // size: 0x4, address: 0x80A4D4BC
static class Symbol _s; // size: 0x4, address: 0x80A4D4C4
static class Symbol _s; // size: 0x4, address: 0x80A4D4CC
static class Symbol _s; // size: 0x4, address: 0x80A4D4D4
static class Symbol _s; // size: 0x4, address: 0x80A4D4DC
static class Symbol _s; // size: 0x4, address: 0x80A4D4E4
static class Symbol _s; // size: 0x4, address: 0x80A4D4EC
static class Symbol _s; // size: 0x4, address: 0x80A4D4F4
static class Symbol _s; // size: 0x4, address: 0x80A4D4FC
static class Symbol _s; // size: 0x4, address: 0x80A4D504
static class Symbol _s; // size: 0x4, address: 0x80A4D50C
static class Symbol _s; // size: 0x4, address: 0x80A4D514
static class Symbol _s; // size: 0x4, address: 0x80A4D51C
static class Symbol _s; // size: 0x4, address: 0x80A4D524
static class Symbol _s; // size: 0x4, address: 0x80A4D52C
static class Symbol _s; // size: 0x4, address: 0x80A4D534
static class Symbol _s; // size: 0x4, address: 0x80A4D53C
static class Symbol _s; // size: 0x4, address: 0x80A4D544
static class Symbol _s; // size: 0x4, address: 0x80A4D54C
static class Symbol _s; // size: 0x4, address: 0x80A4D554
static class Symbol _s; // size: 0x4, address: 0x80A4D55C
static class Symbol _s; // size: 0x4, address: 0x80A4D564
static class Symbol _s; // size: 0x4, address: 0x80A4D56C
static class Symbol _s; // size: 0x4, address: 0x80A4D574
static class Symbol _s; // size: 0x4, address: 0x80A4D57C
static class Symbol _s; // size: 0x4, address: 0x80A4D584
static class Symbol _s; // size: 0x4, address: 0x80A4D58C
static class Symbol _s; // size: 0x4, address: 0x80A4D594
static class Symbol _s; // size: 0x4, address: 0x80A4D59C
static class Symbol _s; // size: 0x4, address: 0x80A4D5A4
static class Symbol _s; // size: 0x4, address: 0x80A4D5AC
static class Symbol _s; // size: 0x4, address: 0x80A4D5B4
static class Symbol _s; // size: 0x4, address: 0x80A4D5BC
static class Symbol _s; // size: 0x4, address: 0x80A4D5C4
static class Symbol _s; // size: 0x4, address: 0x80A4D5CC
static class Symbol _s; // size: 0x4, address: 0x80A4D5D4
static class Symbol _s; // size: 0x4, address: 0x80A4D5DC
static class Symbol _s; // size: 0x4, address: 0x80A4D5E4
static class Symbol _s; // size: 0x4, address: 0x80A4D5EC
static class Symbol _s; // size: 0x4, address: 0x80A4D5F4
static class Symbol _s; // size: 0x4, address: 0x80A4D5FC
static class Symbol _s; // size: 0x4, address: 0x80A4D604
static class Symbol _s; // size: 0x4, address: 0x80A4D60C
static class Symbol _s; // size: 0x4, address: 0x80A4D614
static class Symbol _s; // size: 0x4, address: 0x80A4D61C
static class Symbol _s; // size: 0x4, address: 0x80A4D624
// Range: 0x801A6AA0 -> 0x801A8B5C
class DataNode TourBand::Handle(class TourBand * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x80
    class MessageTimer _mt; // r1+0xD8
    class DataNode r; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode _n; // r1+0x90
    class DataNode _n; // r1+0x88

    // References
    // -> class DebugNotifier TheDebugNotifier;
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
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> const char * gNullStr;
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
    // -> enum TourEventType sEventType;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x8
} __RTTI__26TourChallengeCompletePanel; // size: 0x8, address: 0x8089F4A8
struct {
    // total size: 0x8
} __RTTI__9TourStaff; // size: 0x8, address: 0x8089F518
struct {
    // total size: 0x8
} __RTTI__14TourWorldEvent; // size: 0x8, address: 0x8089F550
struct {
    // total size: 0x8
} __RTTI__18TourChallengeEvent; // size: 0x8, address: 0x8089F588
struct {
    // total size: 0x8
} __RTTI__9TourEvent; // size: 0x8, address: 0x8089F5B0
struct {
    // total size: 0x1AC
} __vt__8TourBand; // size: 0x1AC, address: 0x8089F680
struct {
    // total size: 0x8
} __RTTI__P10VenueState; // size: 0x8, address: 0x8089F9A8
struct {
    // total size: 0x8
} __RTTI__PP8TourHint; // size: 0x8, address: 0x8089F9C0
struct {
    // total size: 0x8
} __RTTI__P15TourRequirement; // size: 0x8, address: 0x8089F9E0
struct {
    // total size: 0x8
} __RTTI__PP14TourWorldEvent; // size: 0x8, address: 0x8089FA00
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std28_List_node<14OpportunityLoc>; // size: 0x8, address: 0x8089FA50
struct {
    // total size: 0x8
} __RTTI__P9SeenVenue; // size: 0x8, address: 0x8089FA68
struct {
    // total size: 0x8
} __RTTI__P10WorldState; // size: 0x8, address: 0x8089FA80
// Range: 0x801A8B5C -> 0x801A8C18
static void __sinit_\TourBand_cpp() {
    // References
    // -> class vector mSongs;
    // -> class Symbol mName;
    // -> const char * gNullStr;
    // -> class PersistentGameData sPersistentGameData;
    // -> class String sRivalLogo;
}

class StlNodeAlloc {
    // total size: 0x1
};
struct SongState {
    // total size: 0x8
    class Symbol mSong; // offset 0x0, size 0x4
    int mStars; // offset 0x4, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct SongState * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct SongState * _M_start; // offset 0x0, size 0x4
    struct SongState * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};

