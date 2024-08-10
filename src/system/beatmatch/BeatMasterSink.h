#ifndef BEATMATCH_BEATMASTERSINK_H
#define BEATMATCH_BEATMASTERSINK_H
#include "beatmatch/SongPos.h"

class BeatMasterSink {
public:
    BeatMasterSink(){}
    virtual ~BeatMasterSink(){}
    virtual void Beat(int, int) = 0;
    virtual void UpdateSongPos(const SongPos&) = 0;
    virtual void HandleSubmix(int, const char*) = 0;
};

#endif
