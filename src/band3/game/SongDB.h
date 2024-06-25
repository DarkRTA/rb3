#ifndef GAME_SONGDB_H
#define GAME_SONGDB_H

#include "system/beatmatch/SongData.h"
#include "system/beatmatch/SongParserSink.h"
#include <vector>

class SongDB : public SongParserSink {
public:
    SongDB();
    virtual ~SongDB();

    virtual void SetNumTracks(int);
    virtual void AddTrack(int, Symbol, SongInfoAudioType, TrackType, bool);
    virtual void AddMultiGem(int, const GameGem&);
    virtual void AddPhrase(BeatmatchPhraseType, int, const Phrase&);

    float GetSongDurationMs();

    SongData* GetSongData() { return mSongData; }

    SongData* mSongData;
    std::vector<int> mTrackData; // todo: type
    float mSongDurationMs;
    int mCodaStartTick;
    int mMultiplayerAnalyzer; // MultiplayerAnalyzer*
    std::vector<int> mPracticeSections; // todo: type
    int mUnk1;
    int mUnk2;
};

extern SongDB* TheSongDB;

#endif
