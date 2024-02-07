/*
    Compile unit: C:\rockband2\band2\src\game\MultiplayerAnalyzer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80072B28 -> 0x80073B2C
*/
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class MidiReceiver * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class MidiReceiver * * _M_start; // offset 0x0, size 0x4
    class MidiReceiver * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct PartInfo {
    // total size: 0x14
    class Symbol part; // offset 0x0, size 0x4
    class Symbol mode; // offset 0x4, size 0x4
    class Symbol instrument; // offset 0x8, size 0x4
    class Symbol original_name; // offset 0xC, size 0x4
    enum BeatmatchTrackType type; // offset 0x10, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct PartInfo * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct PartInfo * _M_start; // offset 0x0, size 0x4
    struct PartInfo * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct GemInProgress {
    // total size: 0xC
    int mTick; // offset 0x0, size 0x4
    int mNoStrum; // offset 0x4, size 0x4
    int mPlayers; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct GemInProgress * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct GemInProgress * _M_start; // offset 0x0, size 0x4
    struct GemInProgress * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class DifficultyInfo {
    // total size: 0x20
public:
    class vector mGemsInProgress; // offset 0x0, size 0xC
    unsigned char mActivePlayers; // offset 0xC, size 0x1
    int mForceHopoOnStart; // offset 0x10, size 0x4
    int mForceHopoOnEnd; // offset 0x14, size 0x4
    int mForceHopoOffStart; // offset 0x18, size 0x4
    int mForceHopoOffEnd; // offset 0x1C, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class DifficultyInfo * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class DifficultyInfo * _M_start; // offset 0x0, size 0x4
    class DifficultyInfo * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum /* @enum$9069MultiplayerAnalyzer_cpp */ {
    kIgnore = 0,
    kGems = 1,
    kVocalNotes = 2,
    kBeat = 3,
};
enum ReadingState {
    kReadingBeat = 0,
    kReadingNonParts = 1,
    kReadingParts = 2,
    kDoneReading = 3,
};
class SongParser : public MidiReceiver {
    // total size: 0x138
    int mNumSlots; // offset 0x8, size 0x4
    int mPlayerSlot; // offset 0xC, size 0x4
    int mLowVocalPitch; // offset 0x10, size 0x4
    int mHighVocalPitch; // offset 0x14, size 0x4
    class TempoMap * & mTempoMap; // offset 0x18, size 0x4
    class MeasureMap * & mMeasureMap; // offset 0x1C, size 0x4
    class MidiReader * mMidiReader; // offset 0x20, size 0x4
    class BinStream * mFile; // offset 0x24, size 0x4
    const char * mFilename; // offset 0x28, size 0x4
    class vector mReceivers; // offset 0x2C, size 0xC
    class InternalSongParserSink & mSink; // offset 0x38, size 0x4
    class DataArray * mTracks; // offset 0x3C, size 0x4
    class DataArray * mTrackNameMapping; // offset 0x40, size 0x4
    int mNumPlayers; // offset 0x44, size 0x4
    int mNumDifficulties; // offset 0x48, size 0x4
    int mTrack; // offset 0x4C, size 0x4
    int mCurTrackIndex; // offset 0x50, size 0x4
    class vector mParts; // offset 0x54, size 0xC
    class vector mDifficultyInfos; // offset 0x60, size 0xC
    int mCommonPhraseInProgress; // offset 0x6C, size 0x4
    int mSoloPhraseInProgress; // offset 0x70, size 0x4
    int mDrumFillInProgress; // offset 0x74, size 0x4
    int mPlayerFocusInProgress[2]; // offset 0x78, size 0x8
    enum /* @enum$9069MultiplayerAnalyzer_cpp */ {
        kIgnore = 0,
        kGems = 1,
        kVocalNotes = 2,
        kBeat = 3,
    } mState; // offset 0x80, size 0x4
    class Symbol mTrackName; // offset 0x84, size 0x4
    int mCurrentFillLanes; // offset 0x88, size 0x4
    unsigned char mSeparateParts; // offset 0x8C, size 0x1
    unsigned char mIgnoreGemDurations; // offset 0x8D, size 0x1
    class list mDrumStyleInstruments; // offset 0x90, size 0x8
    class list mVocalStyleInstruments; // offset 0x98, size 0x8
    unsigned char mDrumStyleGems; // offset 0xA0, size 0x1
    unsigned char mForceDrumStyleGems; // offset 0xA1, size 0x1
    int mSectionStartTick; // offset 0xA4, size 0x4
    int mSectionEndTick; // offset 0xA8, size 0x4
    class vector mTrackNames; // offset 0xAC, size 0xC
    class Symbol mPartSuffix; // offset 0xB8, size 0x4
    unsigned char mLyricPitchSet; // offset 0xBC, size 0x1
    unsigned char mLyricTextSet; // offset 0xBD, size 0x1
    unsigned char mLyricBends; // offset 0xBE, size 0x1
    int mNextLyricTextTick; // offset 0xC0, size 0x4
    class String mNextLyric; // offset 0xC4, size 0xC
    class VocalNote mCurVocalNote; // offset 0xD0, size 0x30
    class VocalNote mPrevVocalNote; // offset 0x100, size 0x30
    enum ReadingState mReadingState; // offset 0x130, size 0x4
    int mPartToReadIdx; // offset 0x134, size 0x4
};
class MultiplayerAnalyzer : public SongParserSink {
    // total size: 0x60
    const char * mName; // offset 0x4, size 0x4
    class SongData * mSongData; // offset 0x8, size 0x4
    int mMaxStreakMultiplier; // offset 0xC, size 0x4
    int mHeadScore; // offset 0x10, size 0x4
    int mTailScore; // offset 0x14, size 0x4
    class vector mMaxScoresWithStreak; // offset 0x18, size 0xC
    class vector mMaxScores; // offset 0x24, size 0xC
    class vector mBonusScores; // offset 0x30, size 0xC
    class vector mEqualBonusScores; // offset 0x3C, size 0xC
    class vector mGemScoreVectors; // offset 0x48, size 0xC
    class PlayerTrackConfigList * mConfig; // offset 0x54, size 0x4
    int mNumPlayers; // offset 0x58, size 0x4
    int mNumActivePlayers; // offset 0x5C, size 0x4
};
enum NoStrumState {
    kForceOn = 0,
    kForceOff = 1,
    kDefault = 2,
};
class MultiGemInfo {
    // total size: 0x24
public:
    int track; // offset 0x0, size 0x4
    int slots; // offset 0x4, size 0x4
    float ms; // offset 0x8, size 0x4
    float duration_ms; // offset 0xC, size 0x4
    int tick; // offset 0x10, size 0x4
    int duration_ticks; // offset 0x14, size 0x4
    unsigned char ignore_duration; // offset 0x18, size 0x1
    int players; // offset 0x1C, size 0x4
    enum NoStrumState no_strum; // offset 0x20, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class vector * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class vector * * _M_start; // offset 0x0, size 0x4
    class vector * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x80072B28 -> 0x80072B64
void MultiplayerAnalyzer::PostLoad(class MultiplayerAnalyzer * const this /* r31 */) {}

// Range: 0x80072B64 -> 0x80072DD4
void MultiplayerAnalyzer::Configure(class MultiplayerAnalyzer * const this /* r30 */, class PlayerTrackConfigList * config_list /* r31 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class StlNodeAlloc {
    // total size: 0x1
};
struct GemScore {
    // total size: 0x8
    int mTick; // offset 0x0, size 0x4
    float mPoints; // offset 0x4, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct GemScore * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct GemScore * _M_start; // offset 0x0, size 0x4
    struct GemScore * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x80072DD4 -> 0x80072E94
float MultiplayerAnalyzer::GetNormalizationFactor(const class MultiplayerAnalyzer * const this /* r30 */) {
    // Local variables
    int p0; // r0
    int p1; // r0
    float s0; // f2
    float s1; // f1

    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80072E94 -> 0x80072EA4
float MultiplayerAnalyzer::GetMaxPoints() {}

// Range: 0x80072EA4 -> 0x80072EB4
float MultiplayerAnalyzer::GetMaxStreakPoints() {}

// Range: 0x80072EB4 -> 0x80072ED0
float MultiplayerAnalyzer::GetBonusPoints() {}

// Range: 0x80072ED0 -> 0x80072FE0
void MultiplayerAnalyzer::CorrectBasePoints(class MultiplayerAnalyzer * const this /* r31 */, int player /* r27 */, int baseMax /* r28 */, int baseMaxWithStreak /* r29 */, int baseBonus /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80072FE0 -> 0x8007310C
void MultiplayerAnalyzer::AddTrack(class MultiplayerAnalyzer * const this /* r27 */, class Symbol & instrument /* r28 */) {
    // Local variables
    class DataArray * arr; // r29

    // References
    // -> const char * gNullStr;
}

// Range: 0x8007310C -> 0x80073310
void MultiplayerAnalyzer::AddMultiGem(class MultiplayerAnalyzer * const this /* r27 */, int track /* r28 */, const class GameGem & gem /* r29 */) {
    // Local variables
    unsigned char separate_parts; // r0
    int player; // r30
    int player_slot; // r0
    int head_score; // r26
    float tail_score; // f0
    float score; // f0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
}

// Range: 0x80073310 -> 0x800733C4
void MultiplayerAnalyzer::AddSolo(class MultiplayerAnalyzer * const this /* r29 */, int num_solo_gems /* r30 */, int player /* r31 */) {
    // Local variables
    int points_per_gem; // r1+0x10
    class Symbol result; // r1+0xC

    // References
    // -> class Scoring * TheScoring;
    // -> const char * gNullStr;
}

// Range: 0x800733C4 -> 0x800735D4
void MultiplayerAnalyzer::AddGuitarSolos(class MultiplayerAnalyzer * const this /* r23 */) {
    // Local variables
    unsigned char separate_parts; // r0
    int player; // r28
    int track; // r27
    class GameGemList & gems; // r0
    int num_gems; // r26
    int player_slot; // r0
    int num_solo_gems; // r25
    int g; // r24

    // References
    // -> class SongDB * TheSongDB;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
}

// Range: 0x800735D4 -> 0x800736CC
void MultiplayerAnalyzer::GetCodaExtents(class MultiplayerAnalyzer * const this /* r28 */, int player /* r31 */, int & start /* r29 */, int & end /* r30 */) {
    // Local variables
    int coda_start; // r0
    class DrumFillInfo * fill_info; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongDB * TheSongDB;
}

// Range: 0x800736CC -> 0x8007390C
void MultiplayerAnalyzer::AddGems(class MultiplayerAnalyzer * const this /* r29 */) {
    // Local variables
    int player; // r31
    int num_gems; // r30
    int start; // r1+0x24
    int end; // r1+0x20
    class vector * gems; // r3
    int g; // r4
    int tick; // r5
    int multiplier; // r9
    int i; // r30
}

// Range: 0x8007390C -> 0x80073B2C
void MultiplayerAnalyzer::AddCodas(class MultiplayerAnalyzer * const this /* r27 */) {
    // Local variables
    class DataArray * coda_cfg; // r23
    float coda_point_rate; // f0
    int coda_start; // r0
    int player; // r29
    class DrumFillInfo * fill_info; // r0
    const class vector & fills; // r0
    int f; // r28
    float start_ms; // f0
    float end_ms; // f0
    float length_ms; // f1

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongDB * TheSongDB;
}

struct {
    // total size: 0x1C
} __vt__19MultiplayerAnalyzer; // size: 0x1C, address: 0x80877674
struct {
    // total size: 0x8
} __RTTI__19MultiplayerAnalyzer; // size: 0x8, address: 0x808776B0
struct {
    // total size: 0x1C
} __vt__14SongParserSink; // size: 0x1C, address: 0x808776B8
struct {
    // total size: 0x8
} __RTTI__14SongParserSink; // size: 0x8, address: 0x808776E8
class vector : protected _Vector_base {
    // total size: 0xC
};
struct {
    // total size: 0x8
} __RTTI__PPQ211stlpmtx_std104vector<Q219MultiplayerAnalyzer8GemScore,Q211stlpmtx_std46StlNodeAlloc<Q219MultiplayerAnalyzer8GemScore>>; // size: 0x8, address: 0x80877760
struct {
    // total size: 0x8
} __RTTI__PQ219MultiplayerAnalyzer8GemScore; // size: 0x8, address: 0x80877788

