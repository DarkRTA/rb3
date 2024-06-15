#ifndef GAME_SONGDB_H
#define GAME_SONGDB_H

#include "system/beatmatch/SongParserSink.h"

class SongDB : public SongParserSink {
public:
    SongDB();
    virtual ~SongDB();

    virtual void SetNumTracks(int);
    virtual void AddTrack(int, Symbol, SongInfoAudioType, TrackType, bool);
    virtual void AddMultiGem(int, const GameGem&);
    virtual void AddPhrase(BeatmatchPhraseType, int, const Phrase&);

    float GetSongDurationMs();
};

extern SongDB* TheSongDB;

#endif
