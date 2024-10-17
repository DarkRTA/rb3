#ifndef METAGAME_SONGSTATUSMGR_H
#define METAGAME_SONGSTATUSMGR_H

#include "game/Defines.h"
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
    void Clear(ScoreType);
    void SaveSize(int);
    void SaveToStream(BinStream&, ScoreType) const;
    void LoadFromStream(BinStream&, ScoreType);
};

class SongStatus {
    SongStatus();
    ~SongStatus();
    void Clear();
    void SaveSize(int);
    void SaveFixed(FixedSizeSaveableStream&) const;
    void LoadFixed(FixedSizeSaveableStream&, int);
    void SetDirty(ScoreType, Difficulty, bool);
    void SetLastPlayed(int);
    void GetLastPlayed() const;
    void SetPlayCount(int);
    void SetBitmapLessonComplete(unsigned int&, int, bool);
    void SetProGuitarLessonSectionComplete(Difficulty, int, bool);
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
};

#endif // METAGAME_SONGSTATUSMGR_H
