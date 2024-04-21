#ifndef BEATMATCH_PLAYBACK_H
#define BEATMATCH_PLAYBACK_H
#include "utl/Str.h"

// forward decs
class BeatMatcher;
class DataArray;

class Playback {
public:
    Playback();
    virtual ~Playback();
    void Poll(float);
    void DoCommand(DataArray*);
    bool LoadFile(const String&);
    void AddSink(BeatMatcher*);
    void Jump(float);
    int GetPlaybackNum(BeatMatcher*);

    int mPlayerIndex;
    BeatMatcher* mPlayerSinks[8];
    DataArray* mCommands;
    int mCommandIndex;
    float mTime;
};

extern Playback TheBeatMatchPlayback;

#endif
