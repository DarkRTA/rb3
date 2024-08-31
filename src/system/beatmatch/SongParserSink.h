#ifndef BEATMATCH_SONGPARSERSINK_H
#define BEATMATCH_SONGPARSERSINK_H
#include "utl/Symbol.h"
#include "beatmatch/GameGem.h"
#include "beatmatch/InternalSongParserSink.h"
#include "beatmatch/Phrase.h"

class SongParserSink {
public:
    SongParserSink(){}
    virtual ~SongParserSink(){}
    virtual void SetNumTracks(int){}
    virtual void AddTrack(int, Symbol, SongInfoAudioType, TrackType, bool) = 0;
    virtual void AddMultiGem(int, const GameGem&) = 0;
    virtual void AddPhrase(BeatmatchPhraseType, int, const Phrase&) = 0;
};

#endif