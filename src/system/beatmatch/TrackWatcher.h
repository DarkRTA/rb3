#pragma once
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
    TrackWatcher(int, const UserGuid &, int, Symbol, SongData *, TrackWatcherParent *, DataArray *);
    ~TrackWatcher();
    void SetImpl();
    void ReplaceImpl(Symbol);
    void RecalcGemList();
    void SetIsCurrentTrack(bool);
    void AddSink(BeatMatchSink *);
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

    TrackWatcherImpl *mImpl; // 0x0
    std::vector<BeatMatchSink *> mSinks; // 0x4
    int mTrack; // 0xc
    bool mIndependentSlots; // 0x10
    UserGuid mUserGuid; // 0x14
    int mPlayerSlot; // 0x24
    Symbol mControllerType; // 0x28
    SongData *mSongData; // 0x2c
    TrackWatcherParent *mParent; // 0x30
    DataArray *mCfg; // 0x34
};

Symbol ControllerTypeToTrackWatcherType(Symbol);
