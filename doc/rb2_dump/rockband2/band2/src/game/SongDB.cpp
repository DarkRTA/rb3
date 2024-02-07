/*
    Compile unit: C:\rockband2\band2\src\game\SongDB.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008A710 -> 0x8008CC88
*/
class SongDB * TheSongDB; // size: 0x4, address: 0x80A49E40
// Range: 0x8008A710 -> 0x8008A72C
static unsigned char ExtentCmp() {}

class DrumMap : private DrumFillInfo {
    // total size: 0x20
    int mCurrentLanes; // offset 0x1C, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Phrase * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Phrase * _M_start; // offset 0x0, size 0x4
    class Phrase * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class PhraseList {
    // total size: 0xC
    class vector mPhrases; // offset 0x0, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class PhraseList * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class PhraseList * * _M_start; // offset 0x0, size 0x4
    class PhraseList * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class PhraseListCollection {
    // total size: 0xC
    class vector mPhraseLists; // offset 0x0, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class PhraseListCollection * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class PhraseListCollection * * _M_start; // offset 0x0, size 0x4
    class PhraseListCollection * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class PhraseDB {
    // total size: 0x20
    class vector mPhraseListCollections; // offset 0x0, size 0xC
    class vector mCopy; // offset 0xC, size 0x14
};
class GameGemInfoList {
    // total size: 0x10
    int mTrack; // offset 0x0, size 0x4
    class vector mGemInfos; // offset 0x4, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class GameGemInfoList * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class GameGemInfoList * * _M_start; // offset 0x0, size 0x4
    class GameGemInfoList * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class GameGemInfoPlayerDB {
    // total size: 0xC
    class vector mGameGemInfoLists; // offset 0x0, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class GameGemInfoPlayerDB * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class GameGemInfoPlayerDB * * _M_start; // offset 0x0, size 0x4
    class GameGemInfoPlayerDB * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class GameGemInfoDB {
    // total size: 0xC
    class vector mGameGemDBs; // offset 0x0, size 0xC
};
class PhraseAnalyzer {
    // total size: 0x28
    unsigned char mPerformedAnalysis; // offset 0x0, size 0x1
    int mPhraseStartWindow; // offset 0x4, size 0x4
    class vector mPhrases; // offset 0x8, size 0xC
    class vector mRawPhrases; // offset 0x14, size 0xC
    class Symbol mSong; // offset 0x20, size 0x4
    unsigned char mNotify; // offset 0x24, size 0x1
};
// Range: 0x8008A72C -> 0x8008A868
void * SongDB::SongDB(class SongDB * const this /* r30 */) {
    // References
    // -> class GameMode * TheGameMode;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__6SongDB;
}

class Phrase {
    // total size: 0x10
protected:
    float mMs; // offset 0x0, size 0x4
    float mDurationMs; // offset 0x4, size 0x4
    int mTick; // offset 0x8, size 0x4
    int mDurationTicks; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
struct RawPhrase {
    // total size: 0x14
    int track; // offset 0x0, size 0x4
    int start_tick; // offset 0x4, size 0x4
    int end_tick; // offset 0x8, size 0x4
    int independent; // offset 0xC, size 0x4
    int id; // offset 0x10, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct RawPhrase * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct RawPhrase * _M_start; // offset 0x0, size 0x4
    struct RawPhrase * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x8008A868 -> 0x8008ACC0
void * SongDB::~SongDB(class SongDB * const this /* r28 */) {
    // References
    // -> struct [anonymous] __vt__6SongDB;
}

// Range: 0x8008ACC0 -> 0x8008ACC8
void SongDB::PreLoad() {}

// Range: 0x8008ACC8 -> 0x8008AD4C
void SongDB::PostLoad(class SongDB * const this /* r30 */, class DataEventList * events /* r31 */) {}

// Range: 0x8008AD4C -> 0x8008AD88
void SongDB::CorrectBasePoints(class SongDB * const this /* r31 */) {}

// Range: 0x8008AD88 -> 0x8008AD90
int SongDB::TotalBasePoints() {}

// Range: 0x8008AD90 -> 0x8008AD98
float SongDB::GetSongDurationMs() {}

// Range: 0x8008AD98 -> 0x8008ADA0
void SongDB::SetSongDurationMs() {}

// Range: 0x8008ADA0 -> 0x8008ADA8
int SongDB::GetCodaStartTick() {}

// Range: 0x8008ADA8 -> 0x8008ADCC
int SongDB::IsInCoda() {}

// Range: 0x8008ADCC -> 0x8008ADD8
int SongDB::GetNumTracks() {}

// Range: 0x8008ADD8 -> 0x8008AE00
int SongDB::GetNumTrackData() {}

// Range: 0x8008AE00 -> 0x8008AE3C
float SongDB::GetScoreNormalizationFactor() {
    // Local variables
    float val; // f0
}

// Range: 0x8008AE3C -> 0x8008AE6C
int SongDB::GetBaseMaxPoints() {}

// Range: 0x8008AE6C -> 0x8008AE9C
int SongDB::GetBaseMaxStreakPoints() {}

// Range: 0x8008AE9C -> 0x8008AECC
int SongDB::GetBaseBonusPoints() {}

// Range: 0x8008AECC -> 0x8008AED4
class GameGemList & SongDB::GetGemList() {}

// Range: 0x8008AED4 -> 0x8008AEFC
class vector & SongDB::GetGems() {}

// Range: 0x8008AEFC -> 0x8008AF34
class GameGem & SongDB::GetGem(int gem_id /* r31 */) {}

// Range: 0x8008AF34 -> 0x8008AF68
class vector & SongDB::GetGemInfos(int track /* r0 */) {}

// Range: 0x8008AF68 -> 0x8008AF9C
int SongDB::GetTotalGems() {}

// Range: 0x8008AF9C -> 0x8008AFA8
class VocalNoteList * SongDB::GetVocalNoteList() {}

// Range: 0x8008AFA8 -> 0x8008B0E0
unsigned char SongDB::GetPhraseExtents(class SongDB * const this /* r27 */, enum BeatmatchPhraseType type /* r28 */, int track /* r29 */, int tick /* r1+0x8 */, int & start_tick /* r30 */, int & end_tick /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8008B0E0 -> 0x8008B14C
unsigned char SongDB::GetCommonPhraseExtent() {
    // Local variables
    int local_phrase_id; // r0
}

// Range: 0x8008B14C -> 0x8008B1A0
unsigned char SongDB::IsInPhrase(const class SongDB * const this /* r30 */, enum BeatmatchPhraseType type /* r0 */, int gem_id /* r31 */) {}

// Range: 0x8008B1A0 -> 0x8008B33C
void SongDB::DisableCodaGems(class SongDB * const this /* r27 */) {
    // Local variables
    int t; // r31
    class GameGemList & gems; // r30
    class DrumFillInfo * fills; // r0
    int end; // r29
    int gem_id; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8008B33C -> 0x8008B350
class vector & SongDB::GetPhraseIDs() {}

// Range: 0x8008B350 -> 0x8008B358
class vector & SongDB::GetSpotlightPhraseInfo() {}

// Range: 0x8008B358 -> 0x8008B448
int SongDB::GetCommonPhraseID(const class SongDB * const this /* r29 */, int track /* r30 */, int tick /* r31 */) {
    // Local variables
    const class vector & raw_phrases; // r0
    const struct RawPhrase * it; // r4
    int phraseID; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8008B448 -> 0x8008B4A8
class FillInfo * SongDB::GetFillInfo(class SongDB * const this /* r30 */, int track /* r31 */) {}

// Range: 0x8008B4A8 -> 0x8008B4DC
struct MBT SongDB::GetMBT(struct MBT * mbt /* r7 */, const class SongDB * const this /* r6 */) {}

// Range: 0x8008B4DC -> 0x8008B518
int SongDB::GetBeatsPerMeasure() {
    // Local variables
    int measure; // r1+0x14
    int beat; // r1+0x10
    int t; // r1+0xC
    int beatsPerMeasure; // r1+0x8
}

// Range: 0x8008B518 -> 0x8008B520
void SongDB::SetNumTracks() {}

// Range: 0x8008B520 -> 0x8008BBD0
void SongDB::AddTrack(class SongDB * const this /* r26 */, int track /* r27 */, class Symbol & name /* r28 */, class Symbol & instrument /* r29 */, unsigned char independent_gems /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Pi;
    // -> struct [anonymous] __RTTI__PUc;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P6Extent;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8008BBD0 -> 0x8008BC64
void SongDB::AddMultiGem(class SongDB * const this /* r29 */, int track /* r30 */, const class GameGem & gem /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol vocals; // size: 0x4, address: 0x80A49E48
// Range: 0x8008BC64 -> 0x8008BE10
void SongDB::AddPhrase(class SongDB * const this /* r29 */, enum BeatmatchPhraseType type /* r26 */, int track /* r30 */, const class Phrase & phrase /* r31 */) {
    // Local variables
    class vector & phrases; // r3

    // References
    // -> class GameConfig * TheGameConfig;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol vocals;
}

// Range: 0x8008BE10 -> 0x8008BEB0
unsigned char SongDB::IsAlternateGem(int tick /* r29 */, int lane /* r30 */) {
    // Local variables
    class DrumMap * drum_map; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8008BEB0 -> 0x8008BF60
unsigned char SongDB::IsActive(const class SongDB * const this /* r29 */, float ms /* f31 */, int track /* r30 */, int slot /* r31 */) {
    // Local variables
    const class PhraseList & phrases; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8008BF60 -> 0x8008BF64
void SongDB::SpewAllVocalNotes() {}

struct {
    // total size: 0x8
} __RTTI__P9VocalNote; // size: 0x8, address: 0x808798D8
struct {
    // total size: 0x8
} __RTTI__P11VocalPhrase; // size: 0x8, address: 0x808798F0
// Range: 0x8008BF64 -> 0x8008BF68
void SongDB::SpewTrackSizes() {}

static class Symbol coda; // size: 0x4, address: 0x80A49E50
static class Symbol end; // size: 0x4, address: 0x80A49E58
// Range: 0x8008BF68 -> 0x8008C0B8
void SongDB::ParseEvents(class SongDB * const this /* r27 */, class DataEventList * events /* r28 */) {
    // Local variables
    int i; // r29
    const class DataEvent & evt; // r0
    float ms; // f0
    float limitMs; // f0

    // References
    // -> class GameConfig * TheGameConfig;
    // -> class Debug TheDebug;
    // -> static class Symbol end;
    // -> static class Symbol coda;
}

// Range: 0x8008C0B8 -> 0x8008C11C
void SongDB::SetupPhrases(class SongDB * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x8008C11C -> 0x8008C4D8
void SongDB::SetupCommonPhrasesForTrack(class SongDB * const this /* r20 */, int track_num /* r21 */) {
    // Local variables
    const class vector & gems; // r0
    class vector & phrase_ids; // r27
    class vector & phrase_mapping; // r26
    class vector & common_phrases; // r25
    const class vector & raw_phrases; // r0
    int next_phrase_idx; // r24
    int local_phrase_id; // r23
    int gem; // r22
    int phrase_id; // r1+0x28
    int g; // r4
}

// Range: 0x8008C4D8 -> 0x8008C4F0
void SongDB::SetupSoloPhrasesForTrack() {}

// Range: 0x8008C4F0 -> 0x8008C6FC
void SongDB::SetupPhrasesForTrack(class SongDB * const this /* r25 */, class vector & star_phrases /* r26 */, class vector & gem_star_state /* r27 */) {
    // Local variables
    const class vector & gems; // r0
    int phrase; // r29
    int gem; // r28
    unsigned char state; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8008C6FC -> 0x8008C728
unsigned char SongDB::IsInPhrase() {}

// Range: 0x8008C728 -> 0x8008C754
unsigned char SongDB::IsPhraseEnd() {}

// Range: 0x8008C754 -> 0x8008C7C4
class vector & TrackData::GetGemStates(const struct TrackData * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8008C7C4 -> 0x8008C854
int SongDB::NextPhraseIndexAfter(int track_num /* r30 */, int idx /* r31 */) {
    // Local variables
    const class vector & raw_phrases; // r0
    int next; // r6
}

// Range: 0x8008C854 -> 0x8008C86C
class vector & SongDB::GetGemStates(int track /* r0 */) {}

static class Symbol section; // size: 0x4, address: 0x80A49E60
class MemDoTempAllocations {
    // total size: 0x4
    int mOld; // offset 0x0, size 0x4
};
// Range: 0x8008C86C -> 0x8008CC10
void SongDB::SetupPracticeSections(class SongDB * const this /* r29 */) {
    // Local variables
    class DataEventList * events; // r31
    int i; // r30
    const class DataEvent & evt; // r0
    class MemDoTempAllocations dummy_temp_mem_allocation; // r1+0x40
    struct PracticeSection ps; // r1+0x50
    int numSecs; // r5
    int i; // r6

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P15PracticeSection;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> class Game * TheGame;
    // -> static class Symbol section;
}

// Range: 0x8008CC10 -> 0x8008CC18
void SongDB::SetFakeHitGemsInFill() {}

// Range: 0x8008CC18 -> 0x8008CC20
void SongDB::RecalculateGemTimes() {}

// Range: 0x8008CC20 -> 0x8008CC54
void SongDB::CopyGems(int src_track /* r11 */, int player /* r0 */) {}

// Range: 0x8008CC54 -> 0x8008CC5C
void SongDB::EnableGems() {}

struct {
    // total size: 0x1C
} __vt__6SongDB; // size: 0x1C, address: 0x80879978
struct {
    // total size: 0x8
} __RTTI__6SongDB; // size: 0x8, address: 0x808799A8
// Range: 0x8008CC5C -> 0x8008CC88
void _Vector_base::_M_throw_length_error() {}

struct {
    // total size: 0x8
} __RTTI__PQ26SongDB9TrackData; // size: 0x8, address: 0x808799D0

