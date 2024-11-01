#ifndef METAGAME_SONGSTATUSMGR_H
#define METAGAME_SONGSTATUSMGR_H

#include "game/Defines.h"
#include "meta/FixedSizeSaveable.h"
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
    kSongStatusFlag_AllTripleAwesomes = 0x40
};

class SongStatusData {
public:
    void Clear(ScoreType);
    void SaveToStream(BinStream&, ScoreType) const;
    void LoadFromStream(BinStream&, ScoreType);

    static int SaveSize(int);
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

    static int SaveSize(int);

    int mSongID; // 0x8
    unsigned short mBandScoreInstrumentMask; // 0xc
    unsigned char mReview; // 0xe
    int mLastPlayed; // 0x10
    int mPlayCount; // 0x14
    unsigned int mProGuitarLessonParts[4]; // 0x18
    unsigned int mProBassLessonParts[4]; // 0x28
    unsigned int mProKeyboardLessonParts[4]; // 0x38
};

class SongStatusLookup {
    SongStatusLookup();
    ~SongStatusLookup();
    void Clear();
    void Save(FixedSizeSaveableStream&) const;
    void Load(FixedSizeSaveableStream&, int);
};

class SongStatusCacheMgr {

};

class BandSongMgr;

class SongStatusMgr {
public:
    SongStatusMgr(LocalBandUser*, BandSongMgr*);
    ~SongStatusMgr();
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
};

#endif // METAGAME_SONGSTATUSMGR_H
