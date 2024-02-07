/*
    Compile unit: C:\rockband2\band2\src\meta\BotbPanelHelpers.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8020EB88 -> 0x802115A0
*/
// Range: 0x8020EB88 -> 0x8020EC70
void * BotbScoresProvider::BotbScoresProvider(class BotbScoresProvider * const this /* r29 */, void (* cb)(int) /* r30 */, enum WinMetric winMetric /* r31 */) {
    // References
    // -> struct [anonymous] __vt__18BotbScoresProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

struct pair {
    // total size: 0x8
    int first; // offset 0x0, size 0x4
    int second; // offset 0x4, size 0x4
};
// Range: 0x8020EC70 -> 0x8020EDBC
void * BotbScoresProvider::~BotbScoresProvider(class BotbScoresProvider * const this /* r30 */) {
    // Local variables
    int i; // r28

    // References
    // -> struct [anonymous] __vt__18BotbScoresProvider;
}

// Range: 0x8020EDBC -> 0x8020EDC4
void BotbScoresProvider::SetQueryCallback() {}

struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x8020EDC4 -> 0x8020EEB8
void BotbScoresProvider::SetLruFront(const class BotbScoresProvider * const this /* r30 */, int idx /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x20

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
}

static class BotbBattleResultsRow norow; // size: 0x34, address: 0x8097C9BC
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x8020EEB8 -> 0x8020EFA8
class BotbBattleResultsRow & BotbScoresProvider::Data(const class BotbScoresProvider * const this /* r29 */, int data /* r30 */) {
    // Local variables
    int data_floor; // r31
    struct _Rb_tree_iterator it; // r1+0x14

    // References
    // -> static class BotbBattleResultsRow norow;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8020EFA8 -> 0x8020F08C
struct _Rb_tree_iterator BotbScoresProvider::FindMapIdx(const class BotbScoresProvider * const this /* r7 */) {
    // Local variables
    struct _Rb_tree_iterator ret; // r1+0x1C
}

const char * kPendingData; // size: 0x4, address: 0x80A469B8
const char * kNoRank; // size: 0x4, address: 0x80A469BC
static class Symbol rank; // size: 0x4, address: 0x80A4E874
static class Symbol name; // size: 0x4, address: 0x80A4E87C
static class Symbol score; // size: 0x4, address: 0x80A4E884
static class Symbol star; // size: 0x4, address: 0x80A4E88C
// Range: 0x8020F08C -> 0x8020F244
char * BotbScoresProvider::Text(const class BotbScoresProvider * const this /* r29 */, int data /* r28 */, class Symbol & slot /* r30 */) {
    // Local variables
    const class BotbBattleResultsRow & row; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kNoRank;
    // -> const char * kPendingData;
    // -> static class Symbol star;
    // -> static class Symbol score;
    // -> static class Symbol name;
    // -> static class Symbol rank;
}

// Range: 0x8020F244 -> 0x8020F268
class HxGuid & BotbScoresProvider::BandGuid() {
    // Local variables
    const class BotbBattleResultsRow & row; // r0
}

// Range: 0x8020F268 -> 0x8020F270
void BotbScoresProvider::SetTotalRanked() {}

// Range: 0x8020F270 -> 0x8020F278
void BotbScoresProvider::SetOverallRank() {}

// Range: 0x8020F278 -> 0x8020F280
class RndMat * BotbScoresProvider::Mat() {}

// Range: 0x8020F280 -> 0x8020F2EC
enum TrackType SafeSymToTrackType(class Symbol & s /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x8020F2EC -> 0x8020F420
void * BotbEntryCondition::BotbEntryCondition(class BotbEntryCondition * const this /* r29 */, int & shared_entry_condition_state /* r30 */) {
    // Local variables
    enum TrackType t; // r0
}

// Range: 0x8020F420 -> 0x8020F514
char * BotbEntryCondition::Icon() {
    // References
    // -> class Debug TheDebug;
}

static class Symbol botb_ec_instrument; // size: 0x4, address: 0x80A4E894
static class Symbol botb_ec_drummer; // size: 0x4, address: 0x80A4E89C
static class Symbol botb_ec_bassist; // size: 0x4, address: 0x80A4E8A4
static class Symbol botb_ec_guitarist; // size: 0x4, address: 0x80A4E8AC
static class Symbol botb_ec_vocalist; // size: 0x4, address: 0x80A4E8B4
static class Symbol botb_ec_solo; // size: 0x4, address: 0x80A4E8BC
static class Symbol botb_ec_fans; // size: 0x4, address: 0x80A4E8C4
static class Symbol botb_ec_stars; // size: 0x4, address: 0x80A4E8CC
// Range: 0x8020F514 -> 0x8020F7D4
char * BotbEntryCondition::RuleString(const class BotbEntryCondition * const this /* r30 */) {
    // Local variables
    const char * string; // r29
    class Symbol player; // r1+0x1C

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> static class Symbol botb_ec_stars;
    // -> static class Symbol botb_ec_fans;
    // -> static class Symbol botb_ec_solo;
    // -> static class Symbol botb_ec_vocalist;
    // -> static class Symbol botb_ec_guitarist;
    // -> static class Symbol botb_ec_bassist;
    // -> static class Symbol botb_ec_drummer;
    // -> static class Symbol botb_ec_instrument;
}

static class Symbol botb_ec_instrument_deny; // size: 0x4, address: 0x80A4E8D4
static class Symbol botb_ec_drummer; // size: 0x4, address: 0x80A4E8DC
static class Symbol botb_ec_bassist; // size: 0x4, address: 0x80A4E8E4
static class Symbol botb_ec_guitarist; // size: 0x4, address: 0x80A4E8EC
static class Symbol botb_ec_vocalist; // size: 0x4, address: 0x80A4E8F4
static class Symbol botb_ec_solo_deny; // size: 0x4, address: 0x80A4E8FC
static class Symbol botb_ec_fans_deny; // size: 0x4, address: 0x80A4E904
static class Symbol botb_ec_stars_deny; // size: 0x4, address: 0x80A4E90C
// Range: 0x8020F7D4 -> 0x8020FA94
char * BotbEntryCondition::DenyString(const class BotbEntryCondition * const this /* r30 */) {
    // Local variables
    const char * string; // r29
    class Symbol player; // r1+0x1C

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> static class Symbol botb_ec_stars_deny;
    // -> static class Symbol botb_ec_fans_deny;
    // -> static class Symbol botb_ec_solo_deny;
    // -> static class Symbol botb_ec_vocalist;
    // -> static class Symbol botb_ec_guitarist;
    // -> static class Symbol botb_ec_bassist;
    // -> static class Symbol botb_ec_drummer;
    // -> static class Symbol botb_ec_instrument_deny;
}

// Range: 0x8020FA94 -> 0x8020FDEC
unsigned char BotbEntryCondition::ConditionMet(const class BotbEntryCondition * const this /* r27 */, class BandData * band /* r28 */) {
    // Local variables
    class vector users; // r1+0x24
    int guitar_count; // r30
    class BandUser * * u; // r29
    enum TrackType t; // r28
    enum ControllerType c; // r0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8020FDEC -> 0x8020FE88
void BotbEntryCondition::Apply(class TourEvent * event /* r31 */) {
    // Local variables
    enum TrackType t; // r3

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8020FE88 -> 0x8020FF1C
void * BotbPerformanceModifier::BotbPerformanceModifier(class BotbPerformanceModifier * const this /* r31 */) {}

// Range: 0x8020FF1C -> 0x8020FF2C
void * BotbPerformanceModifier::BotbPerformanceModifier() {}

// Range: 0x8020FF2C -> 0x80210008
char * BotbPerformanceModifier::Icon() {
    // References
    // -> class Debug TheDebug;
}

static class Symbol botb_pm_no_brink; // size: 0x4, address: 0x80A4E914
static class Symbol botb_pm_no_crowd; // size: 0x4, address: 0x80A4E91C
static class Symbol botb_pm_no_overdrive; // size: 0x4, address: 0x80A4E924
static class Symbol botb_pm_difficulty; // size: 0x4, address: 0x80A4E92C
static class Symbol botb_pm_expert_difficulty; // size: 0x4, address: 0x80A4E934
static class Symbol botb_wm_percent_complete; // size: 0x4, address: 0x80A4E93C
static class Symbol botb_wm_streak; // size: 0x4, address: 0x80A4E944
static class Symbol botb_wm_multiplier; // size: 0x4, address: 0x80A4E94C
// Range: 0x80210008 -> 0x80210344
char * BotbPerformanceModifier::Description(const class BotbPerformanceModifier * const this /* r30 */) {
    // Local variables
    const char * string; // r29

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol botb_wm_multiplier;
    // -> static class Symbol botb_wm_streak;
    // -> static class Symbol botb_wm_percent_complete;
    // -> static class Symbol botb_pm_expert_difficulty;
    // -> static class Symbol botb_pm_difficulty;
    // -> static class Symbol botb_pm_no_overdrive;
    // -> static class Symbol botb_pm_no_crowd;
    // -> static class Symbol botb_pm_no_brink;
}

// Range: 0x80210344 -> 0x802103F0
void BotbPerformanceModifier::Apply(const class BotbPerformanceModifier * const this /* r7 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x802103F0 -> 0x80210554
void * BotbMiniRankings::BotbMiniRankings(class BotbMiniRankings * const this /* r31 */) {
    // Local variables
    char * tok; // r0

    // References
    // -> class Debug TheDebug;
}

static class Symbol botb_mini_rank_vs_friend_score; // size: 0x4, address: 0x80A4E954
static class Symbol botb_mini_rank_vs_friend_streak; // size: 0x4, address: 0x80A4E95C
static class Symbol botb_mini_rank_vs_friend_mult; // size: 0x4, address: 0x80A4E964
static class Symbol botb_mini_rank_overall_score; // size: 0x4, address: 0x80A4E96C
static class Symbol botb_mini_rank_overall_streak; // size: 0x4, address: 0x80A4E974
static class Symbol botb_mini_rank_overall_mult; // size: 0x4, address: 0x80A4E97C
static class Symbol botb_mini_rank_top100_score; // size: 0x4, address: 0x80A4E984
static class Symbol botb_mini_rank_top100_streak; // size: 0x4, address: 0x80A4E98C
static class Symbol botb_mini_rank_top100_mult; // size: 0x4, address: 0x80A4E994
static class Symbol botb_mini_rank_champ; // size: 0x4, address: 0x80A4E99C
static class Symbol botb_mini_rank_no_rank; // size: 0x4, address: 0x80A4E9A4
// Range: 0x80210554 -> 0x80210A88
char * BotbMiniRankings::Description(const class BotbMiniRankings * const this /* r29 */, enum WinMetric winMetric /* r30 */) {
    // Local variables
    const char * string; // r28

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol botb_mini_rank_no_rank;
    // -> static class Symbol botb_mini_rank_champ;
    // -> static class Symbol botb_mini_rank_top100_mult;
    // -> static class Symbol botb_mini_rank_top100_streak;
    // -> static class Symbol botb_mini_rank_top100_score;
    // -> static class Symbol botb_mini_rank_overall_mult;
    // -> static class Symbol botb_mini_rank_overall_streak;
    // -> static class Symbol botb_mini_rank_overall_score;
    // -> static class Symbol botb_mini_rank_vs_friend_mult;
    // -> static class Symbol botb_mini_rank_vs_friend_streak;
    // -> static class Symbol botb_mini_rank_vs_friend_score;
}

static class Symbol icon; // size: 0x4, address: 0x80A4E9AC
// Range: 0x80210A88 -> 0x80210B98
char * BotbRulesListProvider::Text(const class BotbRulesListProvider * const this /* r30 */, int data /* r31 */, class Symbol & slot /* r29 */) {
    // References
    // -> static class Symbol icon;
}

// Range: 0x80210B98 -> 0x80210BEC
unsigned char BotbRulesListProvider::IsActive() {}

// Range: 0x80210BEC -> 0x80210BF4
class RndMat * BotbRulesListProvider::Mat() {}

static class Symbol botb_years; // size: 0x4, address: 0x80A4E9B4
static class Symbol botb_days; // size: 0x4, address: 0x80A4E9BC
static class Symbol botb_hours; // size: 0x4, address: 0x80A4E9C4
static class Symbol botb_minutes; // size: 0x4, address: 0x80A4E9CC
static class Symbol botb_seconds; // size: 0x4, address: 0x80A4E9D4
static class Symbol botb_year; // size: 0x4, address: 0x80A4E9DC
static class Symbol botb_day; // size: 0x4, address: 0x80A4E9E4
static class Symbol botb_hour; // size: 0x4, address: 0x80A4E9EC
static class Symbol botb_minute; // size: 0x4, address: 0x80A4E9F4
static class Symbol botb_second; // size: 0x4, address: 0x80A4E9FC
static class Symbol botb_time_value; // size: 0x4, address: 0x80A4EA04
static class Symbol botb_time_value2; // size: 0x4, address: 0x80A4EA0C
// Range: 0x80210BF4 -> 0x80211360
char * SecondsToTimeString(int secondsLeft /* r30 */) {
    // Local variables
    int seconds; // r29
    int minutes; // r28
    int minutesLeft; // r5
    int minutes; // r28
    int hours; // r29
    int hoursLeft; // r5
    int hours; // r28
    int days; // r29
    int daysLeft; // r5
    int days; // r28
    int years; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol botb_time_value2;
    // -> static class Symbol botb_time_value;
    // -> static class Symbol botb_second;
    // -> static class Symbol botb_minute;
    // -> static class Symbol botb_hour;
    // -> static class Symbol botb_day;
    // -> static class Symbol botb_year;
    // -> static class Symbol botb_seconds;
    // -> static class Symbol botb_minutes;
    // -> static class Symbol botb_hours;
    // -> static class Symbol botb_days;
    // -> static class Symbol botb_years;
}

static class Symbol trackPacks[11]; // size: 0x2C, address: 0x8097C9F0
// Range: 0x80211360 -> 0x80211540
unsigned char IsRb1DiskSong(class Symbol & song /* r28 */) {
    // Local variables
    class DataArray * missingSongs; // r29
    class DataArray * songData; // r29
    class DataArray * songPack; // r29
    int i; // r30

    // References
    // -> const char * gNullStr;
    // -> static class Symbol trackPacks[11];
}

struct {
    // total size: 0x98
} __vt__21BotbRulesListProvider; // size: 0x98, address: 0x808AD220
struct {
    // total size: 0x8
} __RTTI__21BotbRulesListProvider; // size: 0x8, address: 0x808AD2F0
struct {
    // total size: 0x98
} __vt__18BotbScoresProvider; // size: 0x98, address: 0x808AD2F8
struct {
    // total size: 0x8
} __RTTI__18BotbScoresProvider; // size: 0x8, address: 0x808AD3C0
struct {
    // total size: 0x98
} __vt__19BotbSetListProvider; // size: 0x98, address: 0x808AD3C8
struct {
    // total size: 0x8
} __RTTI__19BotbSetListProvider; // size: 0x8, address: 0x808AD490
struct {
    // total size: 0x8
} __RTTI__PP20BotbBattleResultsRow; // size: 0x8, address: 0x808AD4F8
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std42_Rb_tree_node<Q211stlpmtx_std10pair<Ci,i>>; // size: 0x8, address: 0x808AD540
// Range: 0x80211540 -> 0x80211588
static void __sinit_\BotbPanelHelpers_cpp() {
    // References
    // -> static class BotbBattleResultsRow norow;
}


