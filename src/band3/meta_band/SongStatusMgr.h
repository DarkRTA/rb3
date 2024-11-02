#ifndef METAGAME_SONGSTATUSMGR_H
#define METAGAME_SONGSTATUSMGR_H

#include "game/Defines.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/MetaPerformer.h"
#include "obj/Object.h"
#include "system/utl/BinStream.h"
#include "system/meta/FixedSizeSaveableStream.h"
#include "game/BandUser.h"

enum SongStatusFlagType {
    kSongStatusFlagNone = 0,
    kSongStatusFlag_HitBRE = 1,
    kSongStatusFlag_ChordbookComplete = 2,
    kSongStatusFlag_FullCombo = 4,
    kSongStatusFlag_LessonComplete = 8,
    kSongStatusFlag_PerfectDrumRolls = 0x10,
    kSongStatusFlag_AllDoubleAwesomes = 0x20,
    kSongStatusFlag_AllTripleAwesomes = 0x40,
    kSongStatusFlag_Dirty = 0x80
};

// i got this from bank 5 don't get mad at me about the union implementation
// personally i would've rather made this an anonymous union with the SongStatusData class declaration
union SongStatusInstrumentUnion {
    struct {
        unsigned char mHoposPercentage;
        unsigned char mSoloPercentage;
    } mGuitarDrums;

    struct {
        unsigned char mAwesomes;
        unsigned char mDoubleAwesomes;
        unsigned char mTripleAwesomes;
    } mVocals;
};

class SongStatusData {
public:
    void Clear(ScoreType);
    void SaveToStream(BinStream&, ScoreType) const;
    void LoadFromStream(BinStream&, ScoreType);

    static int SaveSize(int);

    unsigned char mStars; // 0x0
    unsigned char mAccuracy; // 0x1
    unsigned short mStreak; // 0x2
    unsigned char mFlags; // 0x4
    SongStatusInstrumentUnion mShared; // 0x5-0x7
};

class SongStatus : public FixedSizeSaveable {
public:
    SongStatus();
    virtual ~SongStatus();
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    void Clear();
    void SetLastPlayed(int);
    int GetLastPlayed() const;
    void SetPlayCount(int);
    void SetBitmapLessonComplete(unsigned int&, int, bool);
    void SetProGuitarLessonSectionComplete(Difficulty, int, bool);
    void SetProBassLessonSectionComplete(Difficulty, int, bool);
    void SetProKeyboardLessonSectionComplete(Difficulty, int, bool);
    void SetID(int);
    int GetID() const;
    void SetReview(unsigned char);
    void SetInstrumentMask(unsigned short);
    void SetDirty(ScoreType, Difficulty, bool);
    void SetFlag(SongStatusFlagType, ScoreType, Difficulty);
    void ClearFlag(SongStatusFlagType, ScoreType, Difficulty);
    unsigned char GetSoloPercent(ScoreType, Difficulty) const;
    unsigned char GetHOPOPercent(ScoreType, Difficulty) const;
    unsigned char GetAwesomes(ScoreType, Difficulty) const;
    unsigned char GetDoubleAwesomes(ScoreType, Difficulty) const;
    unsigned char GetTripleAwesomes(ScoreType, Difficulty) const;
    bool UpdateScore(ScoreType, Difficulty, int);
    bool UpdateStars(ScoreType, Difficulty, unsigned char);
    bool UpdateAccuracy(ScoreType, Difficulty, unsigned char);
    bool UpdateStreak(ScoreType, Difficulty, unsigned short);
    bool UpdateSoloPercent(ScoreType, Difficulty, unsigned char);
    bool UpdateHOPOPercent(ScoreType, Difficulty, unsigned char);
    bool UpdateAwesomes(ScoreType, Difficulty, unsigned char);
    bool UpdateDoubleAwesomes(ScoreType, Difficulty, unsigned char);
    bool UpdateTripleAwesomes(ScoreType, Difficulty, unsigned char);

    static int SaveSize(int);

    int mSongID; // 0x8
    unsigned short mBandScoreInstrumentMask; // 0xc
    unsigned char mReview; // 0xe
    int mLastPlayed; // 0x10
    int mPlayCount; // 0x14
    unsigned int mProGuitarLessonParts[4]; // 0x18
    unsigned int mProBassLessonParts[4]; // 0x28
    unsigned int mProKeyboardLessonParts[4]; // 0x38
    int mHighScores[11]; // 0x48
    Difficulty mHighScoreDiffs[11]; // 0x74
    SongStatusData mSongData[11][4]; // 0x48
};

class SongStatusLookup {
public:
    SongStatusLookup();
    ~SongStatusLookup();
    void Clear();
    void Save(FixedSizeSaveableStream&) const;
    void Load(FixedSizeSaveableStream&, int);
    bool Empty() const { return mSongID == 0; }

    int mSongID; // 0x0
    int mLastPlayed; // 0x4
};

class SongStatusCacheMgr : public FixedSizeSaveable {
public:
    SongStatusCacheMgr(const LocalBandUser**);
    virtual ~SongStatusCacheMgr();
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    void Clear();
    SongStatus** GetFullCachePtr();
    int GetSongID(int);
    int GetSongStatusIndex(int);
    SongStatus* GetSongStatusPtrForIndex(int);
    void SetLastPlayed(int);
    bool HasSongStatus(int);
    SongStatus* AccessSongStatus(int);
    SongStatus* CreateOrAccessSongStatus(int);
    int GetEmptyIndex();
    int ClearLeastImportantSongStatusEntry();
    void ClearIndex(int);
    SongStatus* GetSongStatus(int);

    static int SaveSize(int);

    SongStatusLookup mLookups[1000];
    SongStatus* mpSongStatusFull; // 0x1f48
    int mCurrentIndex; // 0x1f4c
    const LocalBandUser** mUser; // 0x1f50
    bool unk1f54; // 0x1f54
};

class BandSongMgr;

class SongStatusMgr : public Hmx::Object, public FixedSizeSaveable {
public:
    SongStatusMgr(LocalBandUser*, BandSongMgr*);
    virtual ~SongStatusMgr();
    virtual DataNode Handle(DataArray*, bool);
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    void Clear();
    int GetScore(int, ScoreType) const;
    int GetStars(int, ScoreType, Difficulty) const;
    int GetBestStars(int, ScoreType, Difficulty) const;
    int GetBestAccuracy(int, ScoreType, Difficulty) const;
    int GetBestStreak(int, ScoreType, Difficulty) const;
    int GetBestHOPOPercent(int, ScoreType, Difficulty) const;
    int GetBestSoloPercent(int, ScoreType, Difficulty) const;
    int GetBestAwesomes(int, ScoreType, Difficulty) const;
    int GetBestDoubleAwesomes(int, ScoreType, Difficulty) const;
    int GetBestTripleAwesomes(int, ScoreType, Difficulty) const;
    int GetBestSongStatusFlag(Symbol, SongStatusFlagType, ScoreType, Difficulty) const;
    bool IsProGuitarSongLessonComplete(int, Difficulty) const;
    bool IsProBassSongLessonComplete(int, Difficulty) const;
    bool IsProKeyboardSongLessonComplete(int, Difficulty) const;
    int GetCachedTotalScore(ScoreType) const;
    int GetCachedTotalDiscScore(ScoreType) const;
    int CalculateTotalScore(ScoreType, Symbol) const;
    int GetTotalSongs(ScoreType, Symbol) const;
    int GetCompletedSongs(ScoreType, Difficulty, Symbol) const;
    int GetPossibleStars(ScoreType, Symbol) const;
    int GetTotalBestStars(ScoreType, Difficulty, Symbol) const;
    bool UpdateSongStats(ScoreType, Difficulty, const PerformerStatsInfo&, SongStatus*);
    void UpdateCachedTotalStars(ScoreType);
    bool UpdateSong(int, const PerformerStatsInfo&, bool);
    void UpdateCachedTotalDiscScore(ScoreType);
    void UpdateCachedTotalScore(ScoreType);
    unsigned short GetBandInstrumentMask(int) const;
    Difficulty GetHighScoreDifficulty(int, ScoreType) const;
    int GetHighScore(int, ScoreType) const;
    bool IsSongPlayed(int, ScoreType, Difficulty) const;
    bool IsSongPlayedAtMinDifficulty(int, ScoreType, Difficulty) const;
    int GetAccuracy(int, ScoreType, Difficulty) const;
    int GetStreak(int, ScoreType, Difficulty) const;
    int GetSoloPercent(int, ScoreType, Difficulty) const;
    int GetHOPOPercent(int, ScoreType, Difficulty) const;
    int GetAwesomes(int, ScoreType, Difficulty) const;
    int GetDoubleAwesomes(int, ScoreType, Difficulty) const;
    int GetTripleAwesomes(int, ScoreType, Difficulty) const;

    static int SaveSize(int);

    LocalBandUser* mLocalUser; // 0x24
    BandSongMgr* mSongMgr; // 0x28
    mutable SongStatusCacheMgr mCacheMgr; // 0x2c
    int unk1f84[11];
    int unk1fb0[11];
    int unk1fdc[11];
    SongStatus* mUpdatingStatus; // 0x2008
    ScoreType mUpdatingScoreType; // 0x200c
    Difficulty mUpdatingDifficulty; // 0x2010
};

#endif // METAGAME_SONGSTATUSMGR_H