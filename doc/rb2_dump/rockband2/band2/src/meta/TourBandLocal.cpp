/*
    Compile unit: C:\rockband2\band2\src\meta\TourBandLocal.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801AC67C -> 0x801B3B04
*/
// Range: 0x801AC67C -> 0x801AC718
void * MomentJukebox::MomentJukebox(class MomentJukebox * const this /* r30 */, const class TourWorld & world /* r31 */) {}

// Range: 0x801AC718 -> 0x801AC74C
void MomentJukebox::ClearNextMoment(class MomentJukebox * const this /* r31 */) {}

// Range: 0x801AC74C -> 0x801AC764
void MomentJukebox::Advance() {}

static class Symbol tour; // size: 0x4, address: 0x80A4D62C
static class Symbol default_hometown; // size: 0x4, address: 0x80A4D634
static class Symbol welcome; // size: 0x4, address: 0x80A4D63C
static class Symbol hints; // size: 0x4, address: 0x80A4D644
// Range: 0x801AC764 -> 0x801ACBA0
void * TourBandLocal::TourBandLocal(class TourBandLocal * const this /* r30 */, class TourWorld & world /* r25 */, class TourChallenge & challenge /* r26 */, const class SongMgr & sm /* r27 */, class BandUserMgr & bum /* r28 */) {
    // References
    // -> class DataArray * sChallengeConfig;
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol hints;
    // -> static class Symbol welcome;
    // -> static class Symbol default_hometown;
    // -> static class Symbol tour;
    // -> struct [anonymous] __vt__13TourBandLocal;
}

// Range: 0x801ACBA0 -> 0x801ACD08
void * TourBandLocal::TourBandLocal(class TourBandLocal * const this /* r25 */, class TourWorld & world /* r26 */, class TourChallenge & challenge /* r27 */, const class SongMgr & sm /* r28 */, class BandUserMgr & bum /* r29 */, class BinStream & s /* r30 */) {
    // References
    // -> struct [anonymous] __vt__13TourBandLocal;
}

// Range: 0x801ACD08 -> 0x801AD0A4
void * TourBandLocal::~TourBandLocal(class TourBandLocal * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__13TourBandLocal;
}

static class Symbol moments; // size: 0x4, address: 0x80A4D64C
static class Symbol moment_freq; // size: 0x4, address: 0x80A4D654
static class Symbol tour; // size: 0x4, address: 0x80A4D65C
static class Symbol rating_history_size; // size: 0x4, address: 0x80A4D664
// Range: 0x801AD0A4 -> 0x801AD274
void TourBandLocal::InitData(class TourBandLocal * const this /* r31 */) {
    // Local variables
    class DataArray * f; // r28

    // References
    // -> static class Symbol rating_history_size;
    // -> static class Symbol tour;
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol moment_freq;
    // -> static class Symbol moments;
}

// Range: 0x801AD274 -> 0x801AD314
void TourBandLocal::SetDirty(class TourBandLocal * const this /* r28 */, unsigned char val /* r29 */, int flags /* r30 */) {
    // References
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x801AD314 -> 0x801AD3A0
class HxGuid & TourBandLocal::StandInGuid(const class TourBandLocal * const this /* r30 */, enum TrackType tt /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801AD3A0 -> 0x801AD3A8
class TourMoment * TourBandLocal::NextMoment() {}

// Range: 0x801AD3A8 -> 0x801AD444
int TourBandLocal::StarRating() {
    // Local variables
    int size; // r6
    float total; // f2
    float avg; // f1
}

// Range: 0x801AD444 -> 0x801AD4E8
enum Difficulty TourBandLocal::DifficultyRating() {
    // Local variables
    float total; // f2
    float avg; // f1
}

// Range: 0x801AD4E8 -> 0x801AD4F8
void TourBandLocal::SetEventType() {
    // References
    // -> enum TourEventType sEventType;
}

// Range: 0x801AD4F8 -> 0x801AD508
void TourBandLocal::SetChallengeFocus() {}

// Range: 0x801AD508 -> 0x801AD580
void TourBandLocal::SetBandName(class TourBandLocal * const this /* r30 */, const char * name /* r31 */) {}

// Range: 0x801AD580 -> 0x801AD640
void TourBandLocal::SetHometown(class TourBandLocal * const this /* r30 */, class Symbol & hometown /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

// Range: 0x801AD640 -> 0x801AD7C8
void TourBandLocal::SetTown(class TourBandLocal * const this /* r31 */, class Symbol & town /* r28 */, unsigned char force /* r30 */) {
    // Local variables
    const class TourTown * t; // r0

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

// Range: 0x801AD7C8 -> 0x801AD8E8
void TourBandLocal::SetVenue(class TourBandLocal * const this /* r30 */, class Symbol & venue /* r31 */) {
    // Local variables
    const class TourTown * t; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x801AD8E8 -> 0x801AD9E4
void TourBandLocal::UpdateCharName(class TourBandLocal * const this /* r31 */, const class HxGuid & charGuid /* r26 */, const char * charName /* r27 */, unsigned char charNameUnchecked /* r28 */) {
    // Local variables
    int i; // r29
}

// Range: 0x801AD9E4 -> 0x801ADEB0
void TourBandLocal::Init(class TourBandLocal * const this /* r28 */) {
    // Local variables
    class vector & users; // r0
    class BandUser * * it; // r26
    class BandUser * user; // r27
    class CharData * pChar; // r27
    struct BandMember member; // r1+0x70
    class TourCharLocal * localChar; // r0
    class vector towns; // r1+0x64
    class vector e_states; // r1+0x58
    const class TourTown * * t; // r26
    class TourVenue * const * v; // r27
    struct SeenVenue sv; // r1+0x50

    // References
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x801ADEB0 -> 0x801ADFE0
void TourBandLocal::AddMember(class TourBandLocal * const this /* r29 */, const struct BandMember & member /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801ADFE0 -> 0x801AE174
void TourBandLocal::RemoveMember(class TourBandLocal * const this /* r31 */, const class HxGuid & charGuid /* r30 */) {
    // Local variables
    int i; // r28
    unsigned char found; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801AE174 -> 0x801AE27C
void TourBandLocal::SetStaff(class TourBandLocal * const this /* r28 */, class Symbol & staff_name /* r29 */) {
    // Local variables
    class TourStaff * old_staff; // r31
    int old_min_freq; // r0
    int old_max_freq; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801AE27C -> 0x801AE304
void TourBandLocal::RevertStaff(class TourBandLocal * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x801AE304 -> 0x801AE640
void TourBandLocal::SetMoment(class TourBandLocal * const this /* r31 */, class TourMoment * m /* r28 */, unsigned char accept /* r29 */) {
    // Local variables
    class TourWorldEvent * o; // r29
    class TourWorldEvent * cur_event; // r0
    struct OpportunityLoc ol; // r1+0x34
    const class EventSong * replace; // r0
    const class EventSong * additional; // r0

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<14OpportunityLoc>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801AE640 -> 0x801AE67C
void TourBandLocal::AdvanceSong(class TourBandLocal * const this /* r31 */) {}

// Range: 0x801AE67C -> 0x801AE768
void TourBandLocal::AddRating(int new_rating /* r1+0x8 */) {
    // Local variables
    int i; // r6
    int j; // r7
}

// Range: 0x801AE768 -> 0x801AE7BC
void TourBandLocal::UpdateLiveBattles(class TourBandLocal * const this /* r31 */) {}

// Range: 0x801AE7BC -> 0x801AE7C4
void TourBandLocal::UpdateLeaderboards() {}

static class Symbol item_achievements; // size: 0x4, address: 0x80A4D66C
static class Symbol random; // size: 0x4, address: 0x80A4D674
static class Symbol any; // size: 0x4, address: 0x80A4D67C
// Range: 0x801AE7C4 -> 0x801AF4A8
void TourBandLocal::SetEvent(class TourBandLocal * const this /* r21 */, class TourEvent * e /* r22 */) {
    // Local variables
    int num_songs; // r29
    class TourWorldEvent * world_event; // r28
    class DataArray * a; // r24
    int i; // r25
    class Symbol item; // r1+0x10C
    class vector towns; // r1+0x134
    const class vector & all; // r0
    class vector v_states; // r1+0x128
    int world_stars; // r27
    class TourTown * const * t; // r26
    struct VenueState * v; // r25
    unsigned char played_venue; // r24
    class vector & e_states; // r0
    struct EventState * e; // r23
    const class vector & staff; // r0
    class TourStaff * const * sit; // r24
    const class TourStaff * s; // r1+0x108
    int i; // r23
    const class EventSong & song; // r0
    unsigned char has_any; // r23
    int i; // r24
    const class EventSong & song; // r25
    class vector playable; // r1+0x11C
    int i; // r25
    class vector exclude; // r1+0x110
    struct _List_iterator o; // r1+0x104
    class Symbol item; // r1+0x100

    // References
    // -> class SyncStore * TheSyncStore;
    // -> static class Symbol any;
    // -> static class Symbol random;
    // -> struct [anonymous] __RTTI__18TourChallengeEvent;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol item_achievements;
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__9TourEvent;
    // -> struct [anonymous] __RTTI__14TourWorldEvent;
    // -> enum TourEventType sEventType;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801AF4A8 -> 0x801AF7CC
void TourBandLocal::InitTour(class TourBandLocal * const this /* r31 */, unsigned char battle /* r29 */) {
    // Local variables
    class vector events; // r1+0x3C
    const class TourTown * t; // r29
    class vector botb_tier; // r1+0x30
    int i; // r29
    class TourCharLocal * c; // r30
    class DataArrayPtr data; // r1+0x28

    // References
    // -> class SyncStore * TheSyncStore;
    // -> class GameConfig * TheGameConfig;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> class ProfileMgr TheProfileMgr;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> enum TourEventType sEventType;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x801AF7CC -> 0x801AF8C0
unsigned char TourBandLocal::SkipSong(const class TourBandLocal * const this /* r28 */, class Symbol & song /* r29 */) {
    // Local variables
    class TourChallengeEvent * ce; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__9TourEvent;
    // -> struct [anonymous] __RTTI__18TourChallengeEvent;
    // -> enum TourEventType sEventType;
}

// Range: 0x801AF8C0 -> 0x801AF960
void TourBandLocal::ConfirmEvent(class TourBandLocal * const this /* r31 */) {
    // Local variables
    class TourEvent * e; // r0

    // References
    // -> class GameConfig * TheGameConfig;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol random; // size: 0x4, address: 0x80A4D684
// Range: 0x801AF960 -> 0x801AFA94
void TourBandLocal::SetRandomSongs(class TourBandLocal * const this /* r29 */) {
    // Local variables
    class TourEvent * e; // r30
    float min; // r1+0x10
    float max; // r1+0xC
    int i; // r31
    const class EventSong & es; // r0

    // References
    // -> static class Symbol random;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801AFA94 -> 0x801AFDB4
void TourBandLocal::SetTargetScores(class TourBandLocal * const this /* r30 */) {
    // Local variables
    class vector base_points_per_song; // r1+0x28
    int total_base_points; // r31
    int num_songs_with_base_points; // r28
    int i; // r27
    int base_points; // r0
    int i; // r6
    int i; // r6
    int i; // r6

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801AFDB4 -> 0x801AFF44
void TourBandLocal::SelectSong(class TourBandLocal * const this /* r31 */, int index /* r28 */, class Symbol & song /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol any; // size: 0x4, address: 0x80A4D68C
// Range: 0x801AFF44 -> 0x801B0078
int TourBandLocal::PreviousSongSelection(const class TourBandLocal * const this /* r29 */) {
    // Local variables
    class TourEvent * e; // r30
    int i; // r31

    // References
    // -> static class Symbol any;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol any; // size: 0x4, address: 0x80A4D694
// Range: 0x801B0078 -> 0x801B0120
class Symbol TourBandLocal::RevertSongSelection(class TourBandLocal * const this /* r30 */) {
    // Local variables
    int i; // r0
    class Symbol reverted; // r1+0x8

    // References
    // -> const char * gNullStr;
    // -> static class Symbol any;
}

static class Symbol first_manager; // size: 0x4, address: 0x80A4D69C
static class Symbol new_venue; // size: 0x4, address: 0x80A4D6A4
static class Symbol first_event; // size: 0x4, address: 0x80A4D6AC
// Range: 0x801B0120 -> 0x801B1018
void TourBandLocal::CompleteEvent(class TourBandLocal * const this /* r21 */, unsigned char cheat /* r22 */) {
    // Local variables
    class TourEvent * e; // r19
    class TourWorldEvent * world_event; // r29
    enum Difficulty min_diff; // r1+0x114
    class vector users; // r1+0x16C
    class BandUser * * it; // r19
    class BandUser * u; // r20
    class CharData * cd; // r23
    enum ControllerType ct; // r0
    int new_fame; // r1+0x110
    int total_stars; // r1+0x10C
    int buzz_change; // r19
    int i; // r20
    class Symbol award; // r1+0x108
    struct WorldState * f; // r0
    int num_players; // r1+0x104
    class Symbol town; // r1+0x100
    class Symbol venue; // r1+0xFC
    class vector towns; // r1+0x160
    class vector v_states; // r1+0x154
    int num_towns; // r29
    class list new_events; // r1+0x130
    unsigned char played_all_venues; // r28
    const class vector & all; // r0
    int world_stars; // r27
    class TourTown * const * t; // r26
    struct VenueState * v; // r25
    struct SeenVenue sv; // r1+0x128
    class vector & e_states; // r0
    unsigned char played_venue; // r24
    struct EventState * e; // r23
    class Symbol tok; // r1+0xF8
    class Symbol item; // r1+0xF4
    const class vector & staff; // r0
    class vector new_staff; // r1+0x148
    class TourStaff * const * sit; // r20
    const class TourStaff * s; // r1+0xF0
    class TourChallengeEvent * tce; // r20
    struct ChallengeState & cs; // r0
    enum Difficulty min_diff; // r0
    int num_players; // r1+0xEC

    // References
    // -> class SyncStore * TheSyncStore;
    // -> static class Symbol first_event;
    // -> class RockCentralGateway RockCentral;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class Symbol new_venue;
    // -> static class Symbol first_manager;
    // -> const char * gNullStr;
    // -> enum TourEventType sEventType;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801B1018 -> 0x801B1100
void TourBandLocal::LoseSong(class TourBandLocal * const this /* r30 */) {
    // Local variables
    class TourEvent * e; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> enum TourEventType sEventType;
}

// Range: 0x801B1100 -> 0x801B11C8
void TourBandLocal::UpdateEventBuzz(class TourBandLocal * const this /* r26 */, int buzz_change /* r27 */, int new_stars /* r28 */) {
    // Local variables
    enum Difficulty diff; // r31
    int buzz_cap; // r30
    int max_buzz_cap; // r29
}

static class Symbol first_fans_lost; // size: 0x4, address: 0x80A4D6B4
static class Symbol buzz; // size: 0x4, address: 0x80A4D6BC
static class Symbol caps; // size: 0x4, address: 0x80A4D6C4
static class Symbol trickle; // size: 0x4, address: 0x80A4D6CC
static class Symbol first_buzz_maxcap; // size: 0x4, address: 0x80A4D6D4
static class Symbol first_buzz_cap; // size: 0x4, address: 0x80A4D6DC
// Range: 0x801B11C8 -> 0x801B153C
void TourBandLocal::ApplyBuzzChange(class TourBandLocal * const this /* r25 */, int buzz_change /* r1+0x8 */, int buzz_cap /* r26 */, int max_buzz_cap /* r27 */, enum Difficulty diff /* r28 */, struct BuzzInfo * bi /* r29 */) {
    // Local variables
    unsigned char positive_buzz; // r30

    // References
    // -> static class Symbol first_buzz_cap;
    // -> static class Symbol first_buzz_maxcap;
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol trickle;
    // -> static class Symbol caps;
    // -> static class Symbol buzz;
    // -> static class Symbol first_fans_lost;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801B153C -> 0x801B16B8
void TourBandLocal::CheatWin(class TourBandLocal * const this /* r27 */, int avg_stars /* r28 */) {
    // Local variables
    int i; // r31
    int accum_score; // r30
    int score; // r29
    float total_stars; // f31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x801B16B8 -> 0x801B1844
void TourBandLocal::CheatVehicle(class TourBandLocal * const this /* r30 */, int amt /* r28 */) {
    // Local variables
    int rank; // r31
    int i; // r28
    class Symbol vehicle; // r1+0x24
    class Symbol * it; // r3

    // References
    // -> class DataArray * sVehicles;
}

// Range: 0x801B1844 -> 0x801B1B8C
class Symbol TourBandLocal::CheatCycleNextMoment(class TourBandLocal * const this /* r31 */) {
    // Local variables
    class vector moments; // r1+0x48
    class vector exclude; // r1+0x3C
    class Symbol next_moment; // r1+0x38
    class TourMoment * cur_moment; // r29
    class Symbol * m; // r30

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801B1B8C -> 0x801B1BC8
void TourBandLocal::SetWinDiff(class TourBandLocal * const this /* r31 */) {}

// Range: 0x801B1BC8 -> 0x801B1C40
void TourBandLocal::SetMotto(class TourBandLocal * const this /* r30 */, const char * motto /* r31 */) {}

// Range: 0x801B1C40 -> 0x801B1CF4
void TourBandLocal::SetBandLogo(class TourBandLocal * const this /* r30 */, class String & band_logo /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x801B1CF4 -> 0x801B1D50
void TourBandLocal::SetBandLogoPos(class TourBandLocal * const this /* r31 */) {}

static class Symbol lose_staff; // size: 0x4, address: 0x80A4D6E4
// Range: 0x801B1D50 -> 0x801B1F2C
void TourBandLocal::AdjustBuzz(class TourBandLocal * const this /* r31 */, int delta_buzz /* r28 */, struct BuzzInfo * bi /* r29 */) {
    // Local variables
    int prev_fans; // r0
    class TourHint * * h; // r30

    // References
    // -> static class Symbol lose_staff;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801B1F2C -> 0x801B20F8
void TourBandLocal::HintAdvance(class TourBandLocal * const this /* r31 */) {
    // Local variables
    class vector & hints; // r0
    class vector & hints_seen; // r28
    class TourHint * h; // r1+0x18

    // References
    // -> class SyncStore * TheSyncStore;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801B20F8 -> 0x801B2244
void TourBandLocal::HintAdd(class TourBandLocal * const this /* r29 */, class TourHint * hint /* r1+0x8 */) {
    // Local variables
    class vector & hints; // r31
    class vector & hints_seen; // r30
}

struct TourHintCmp {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x801B2244 -> 0x801B22C4
unsigned char TourBandLocal::HasHint(class TourHint * hint /* r29 */, const class vector & hints /* r30 */) {
    // Local variables
    class TourHint * const * h; // r31
}

// Range: 0x801B22C4 -> 0x801B22E0
class vector & TourBandLocal::HintsSeen() {
    // References
    // -> enum TourEventType sEventType;
}

static class Symbol hints; // size: 0x4, address: 0x80A4D6EC
// Range: 0x801B22E0 -> 0x801B2360
class DataArray * TourBandLocal::HintCfg() {
    // References
    // -> class DataArray * sChallengeConfig;
    // -> class DataArray * sWorldConfig;
    // -> enum TourEventType sEventType;
    // -> static class Symbol hints;
}

// Range: 0x801B2360 -> 0x801B2368
class Profile * TourBandLocal::GetOwner() {}

// Range: 0x801B2368 -> 0x801B23D8
void TourBandLocal::SetOwner(class TourBandLocal * const this /* r30 */, class Profile * pOwner /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801B23D8 -> 0x801B24C4
void TourBandLocal::SetStandInGuid(class TourBandLocal * const this /* r29 */, enum TrackType tt /* r31 */, const class HxGuid & guid /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801B24C4 -> 0x801B2584
class OnlineID * TourBandLocal::OwnerID(const class TourBandLocal * const this /* r29 */) {
    // Local variables
    int padNum; // r30

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801B2584 -> 0x801B2638
char * TourBandLocal::OwnerName(const class TourBandLocal * const this /* r30 */) {
    // Local variables
    int padNum; // r30

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801B2638 -> 0x801B2788
void TourBandLocal::Save(const class TourBandLocal * const this /* r30 */, class BinStream & s /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol hints; // size: 0x4, address: 0x80A4D6F4
// Range: 0x801B2788 -> 0x801B2AB8
void TourBandLocal::Load(class TourBandLocal * const this /* r30 */, class BinStream & s /* r31 */) {
    // References
    // -> class DataArray * sChallengeConfig;
    // -> class DataArray * sWorldConfig;
    // -> static class Symbol hints;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> int sVer;
}

// Range: 0x801B2AB8 -> 0x801B2E8C
void TourBandLocal::SyncSave(const class TourBandLocal * const this /* r29 */, class BinStream & dest /* r30 */, unsigned int dirtyMask /* r31 */) {
    // Local variables
    unsigned char hasOwner; // r28
    class String ownerName; // r1+0x48
    int i; // r28
    class TourCharRemote * r; // r27
    class DataArrayPtr char_data; // r1+0x40

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> enum TourEventType sEventType;
}

// Range: 0x801B2E8C -> 0x801B2EE4
class BinStream & __ls(class BinStream & s /* r30 */, const class MomentJukebox & mj /* r31 */) {}

// Range: 0x801B2EE4 -> 0x801B2F34
class BinStream & __rs(class BinStream & s /* r30 */, class MomentJukebox & mj /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4D6FC
static class Symbol _s; // size: 0x4, address: 0x80A4D704
static class Symbol _s; // size: 0x4, address: 0x80A4D70C
static class Symbol _s; // size: 0x4, address: 0x80A4D714
static class Symbol _s; // size: 0x4, address: 0x80A4D71C
static class Symbol _s; // size: 0x4, address: 0x80A4D724
static class Symbol _s; // size: 0x4, address: 0x80A4D72C
static class Symbol _s; // size: 0x4, address: 0x80A4D734
static class Symbol _s; // size: 0x4, address: 0x80A4D73C
static class Symbol _s; // size: 0x4, address: 0x80A4D744
static class Symbol _s; // size: 0x4, address: 0x80A4D74C
static class Symbol _s; // size: 0x4, address: 0x80A4D754
static class Symbol _s; // size: 0x4, address: 0x80A4D75C
static class Symbol _s; // size: 0x4, address: 0x80A4D764
static class Symbol _s; // size: 0x4, address: 0x80A4D76C
static class Symbol _s; // size: 0x4, address: 0x80A4D774
static class Symbol _s; // size: 0x4, address: 0x80A4D77C
static class Symbol _s; // size: 0x4, address: 0x80A4D784
static class Symbol _s; // size: 0x4, address: 0x80A4D78C
static class Symbol _s; // size: 0x4, address: 0x80A4D794
static class Symbol _s; // size: 0x4, address: 0x80A4D79C
static class Symbol _s; // size: 0x4, address: 0x80A4D7A4
static class Symbol _s; // size: 0x4, address: 0x80A4D7AC
static class Symbol _s; // size: 0x4, address: 0x80A4D7B4
// Range: 0x801B2F34 -> 0x801B3B04
class DataNode TourBandLocal::Handle(class TourBandLocal * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

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
}

struct {
    // total size: 0x8
} __RTTI__10TourMoment; // size: 0x8, address: 0x808A0428
struct {
    // total size: 0x1E8
} __vt__13TourBandLocal; // size: 0x1E8, address: 0x808A0568
struct {
    // total size: 0x8
} __RTTI__PPC9TourStaff; // size: 0x8, address: 0x808A0970
struct {
    // total size: 0x8
} __RTTI__P6HxGuid; // size: 0x8, address: 0x808A09C8

