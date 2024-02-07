/*
    Compile unit: C:\rockband2\band2\src\game\Scoring.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80087E4C -> 0x80089968
*/
class Scoring * TheScoring; // size: 0x4, address: 0x80A49E08
// Range: 0x80087E4C -> 0x80088184
void * StarPowerConfig::StarPowerConfig(struct StarPowerConfig * const this /* r30 */, class DataArray * config /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80088184 -> 0x80088608
void * Scoring::Scoring(class Scoring * const this /* r30 */) {
    // Local variables
    class DataArray * error; // r27
    class DataArray * streaks; // r27
    class DataArray * multipliers; // r26
    class DataArray * energies; // r27
    class DataArray * points_array; // r26
    int i; // r25
    enum TrackType type; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Scoring * TheScoring;
}

// Range: 0x80088608 -> 0x800888F0
void * Scoring::~Scoring(class Scoring * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Scoring * TheScoring;
}

// Range: 0x800888F0 -> 0x80088BAC
void Scoring::InitializeStreakList(class vector & list /* r27 */, class DataArray * cfg /* r28 */) {
    // Local variables
    int i; // r29
    int j; // r30
    struct StreakItem info; // r1+0x40

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ27Scoring10StreakItem;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ27Scoring10StreakItem; // size: 0x8, address: 0x80879658
// Range: 0x80088BAC -> 0x80088BBC
int Scoring::GetHeadPoints() {}

// Range: 0x80088BBC -> 0x80088C50
int Scoring::GetTailPoints() {
    // Local variables
    float quarterNotes; // f1
}

static class Symbol defaultSymbol; // size: 0x4, address: 0x80A49E10
// Range: 0x80088C50 -> 0x80088D40
struct StreakList * Scoring::GetStreakList(const class vector & lists /* r28 */, class Symbol & type /* r29 */) {
    // Local variables
    const struct StreakList * default_list; // r30
    int i; // r5

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol defaultSymbol;
}

// Range: 0x80088D40 -> 0x80088D70
struct StreakList * Scoring::GetStreakMultList() {}

// Range: 0x80088D70 -> 0x80088E50
float Scoring::GetStreakData(int notes /* r29 */, class Symbol & streak_type /* r30 */) {
    // Local variables
    float data; // f31
    unsigned char found; // r31
    const class vector & items; // r0
    int i; // r5

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80088E50 -> 0x80088E8C
int Scoring::GetStreakMult() {}

// Range: 0x80088E8C -> 0x80088F50
float Scoring::GetPartialStreakFraction(int notes /* r31 */) {
    // Local variables
    const struct StreakList * list; // r0
    const class vector & items; // r0
    int bottom_notes; // r5
    int i; // r6
}

// Range: 0x80088F50 -> 0x80089034
class DataArray * Scoring::GetCrowdConfig(const class Scoring * const this /* r29 */, enum Difficulty diff /* r31 */, class BandUser * p_cfg /* r30 */) {
    // Local variables
    class DataArray * cfgs; // r31
    class Symbol type; // r1+0x1C
    class DataArray * cfg; // r0
}

// Range: 0x80089034 -> 0x80089068
int NumInstrsInBitfield() {
    // Local variables
    int num; // r4
    int i; // r5
}

// Range: 0x80089068 -> 0x80089110
unsigned char MatchInstruments(int instr_bitfield /* r29 */, const class DataArray * instrs /* r30 */) {
    // Local variables
    int i; // r31
}

static class Symbol star_ratings; // size: 0x4, address: 0x80A49E18
static class Symbol band_thresholds; // size: 0x4, address: 0x80A49E20
// Range: 0x80089110 -> 0x8008924C
class DataArray * Scoring::GetMultiplierThresholds(const class Scoring * const this /* r27 */, int instr_bitfield /* r26 */) {
    // Local variables
    class DataArray * cfg; // r29
    int num_instrs; // r28
    int i; // r27

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol band_thresholds;
    // -> static class Symbol star_ratings;
}

// Range: 0x8008924C -> 0x80089298
int Scoring::GetNumStars() {
    // Local variables
    int numStars; // r1+0x8
}

static class Symbol star_ratings; // size: 0x4, address: 0x80A49E28
static class Symbol difficulty_thresholds; // size: 0x4, address: 0x80A49E30
static class Symbol bonus_thresholds; // size: 0x4, address: 0x80A49E38
// Range: 0x80089298 -> 0x80089524
float Scoring::GetNumStarsFloat(const class Scoring * const this /* r27 */, int score /* r28 */, int instr_bitfield /* r21 */, int max_base /* r29 */, int bonus_base /* r30 */, unsigned char enforce_diff_restrictions /* r31 */) {
    // Local variables
    class DataArray * thresh; // r24
    class DataArray * diff_thresh; // r23
    class DataArray * bonus_thresh; // r22
    enum Difficulty avg_diff; // r0
    float next_star_threshold; // f30
    int i; // r21
    float req_score; // f31
    float fracToNext; // f2

    // References
    // -> class GameConfig * TheGameConfig;
    // -> static class Symbol bonus_thresholds;
    // -> static class Symbol difficulty_thresholds;
    // -> static class Symbol star_ratings;
}

// Range: 0x80089524 -> 0x80089618
class Symbol Scoring::GetStarRating(const class Scoring * const this /* r30 */, int numStars /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x80089618 -> 0x80089674
int Scoring::GetNotesPerMultiplier() {
    // Local variables
    const struct StreakList * streakList; // r0
}

// Range: 0x80089674 -> 0x800897A4
void Scoring::GetSoloAward(class Scoring * const this /* r28 */, int percent /* r24 */, class Symbol & type /* r25 */, int & points /* r26 */, class Symbol & resultToken /* r27 */) {
    // Local variables
    class DataArray * awards; // r29
    int i; // r28

    // References
    // -> class Debug TheDebug;
}

// Range: 0x800897A4 -> 0x80089840
float Scoring::GetSoloGemReward(class Scoring * const this /* r28 */) {}

// Range: 0x80089840 -> 0x800898DC
float Scoring::GetSoloGemPenalty(class Scoring * const this /* r28 */) {}

// Range: 0x800898DC -> 0x80089968
int Scoring::GetScoreForStars(int stars /* r29 */, int max_base /* r30 */) {
    // Local variables
    class DataArray * threshes; // r31
}

struct {
    // total size: 0x8
} __RTTI__PQ27Scoring10StreakList; // size: 0x8, address: 0x808797E8
struct {
    // total size: 0x8
} __RTTI__PQ27Scoring10PointsInfo; // size: 0x8, address: 0x80879808

