#ifndef METAGAME_SONGSTATUSMGR_H
#define METAGAME_SONGSTATUSMGR_H

#include "game/Defines.h"
#include "system/utl/BinStream.h"
#include "system/meta/FixedSizeSaveableStream.h"
#include "game/BandUser.h"

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

class SongStatusMgr {
    // SongStatusMgr(LocalBandUser*, BandSongMgr*);
    ~SongStatusMgr();
    void Clear();
    void GetScore(int, ScoreType) const;
    void GetStars(int, ScoreType, Difficulty) const;
    void GetBestStars(int, ScoreType, Difficulty) const;
};

#endif // METAGAME_SONGSTATUSMGR_H
