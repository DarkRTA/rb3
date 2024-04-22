#ifndef BEATMATCH_TRACKWATCHER_H
#define BEATMATCH_TRACKWATCHER_H
#include "utl/HxGuid.h"
#include "utl/Symbol.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include <vector>

// forward decs
class SongData;
class GameGemList;
class TrackWatcherParent;
class DataArray;
class BeatMatchSink;
class TrackWatcherImpl;

class TrackWatcher {
public:
    TrackWatcher(int, const UserGuid&, int, Symbol, SongData*, TrackWatcherParent*, DataArray*);
    ~TrackWatcher();
    void SetImpl();
    void ReplaceImpl(Symbol);
    void RecalcGemList();
    void SetIsCurrentTrack(bool);
    void AddSink(BeatMatchSink*);
    void Poll(float);
    void Jump(float);
    void Restart();
    bool Swing(int, bool, bool, GemHitFlags);
    void NonStrumSwing(int, bool, bool);
    void FretButtonDown(int);
    void FretButtonUp(int);
    void RGFretButtonDown(int);
    void Enable(bool);
    void SetCheating(bool);
    void SetAutoplayError(int);
    void SetAutoplayCoda(bool);
    float CycleAutoplayAccuracy();
    void SetAutoplayAccuracy(float);
    void SetSyncOffset(float);
    void E3CheatIncSlop();
    void E3CheatDecSlop();

    TrackWatcherImpl* mImpl;
    std::vector<BeatMatchSink*> mSinks;
    int mTrack;
    bool mIndependentSlots;
    UserGuid mUserGuid;
    int mPlayerSlot;
    Symbol mControllerType;
    SongData* mSongData;
    TrackWatcherParent* mParent;
    DataArray* mCfg;
    DataArray* mSongCfg;
};

Symbol ControllerTypeToTrackWatcherType(Symbol);

#endif
