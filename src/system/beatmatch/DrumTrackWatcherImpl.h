#ifndef BEATMATCH_DRUMTRACKWATCHERIMPL_H
#define BEATMATCH_DRUMTRACKWATCHERIMPL_H
#include "beatmatch/TrackWatcherImpl.h"
#include "beatmatch/GameGem.h"

class DrumTrackWatcherImpl : public TrackWatcherImpl {
public:
    DrumTrackWatcherImpl(int, const UserGuid&, int, SongData*, GameGemList*, TrackWatcherParent*, DataArray*);
    virtual ~DrumTrackWatcherImpl();
    virtual void Restart();
    virtual bool Swing(int, bool, bool, GemHitFlags);
    virtual void NonStrumSwing(int, bool, bool);
    virtual void FretButtonDown(int);
    virtual void FretButtonUp(int);
    virtual void PollHook(float);
    virtual void JumpHook(float);
    virtual int NextGemAfter(int, bool);

    int RelevantGem(int, int, int);
    bool CheckCymbal(const GameGem&, GemHitFlags) const;
    void CheckForKickAutoplay(float);
    
    int mNextKickGemToAutoplay; // 0xc0
    unsigned int mGameCymbalLanes; // 0xc4

};

#endif
