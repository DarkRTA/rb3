#ifndef BEATMATCH_TRACKWATCHERIMPL_H
#define BEATMATCH_TRACKWATCHERIMPL_H
#include "utl/HxGuid.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include <vector>

// forward decs
class SongData;
class GameGemList;
class TrackWatcherParent;
class DataArray;
class BeatMatchSink;

struct GemInProgress {
    // total size: 0xC
    int mTick; // offset 0x0, size 0x4
    int mNoStrum; // offset 0x4, size 0x4
    int mPlayers; // offset 0x8, size 0x4
};

class TrackWatcherState {
public:
    int mLastGemHit;
    bool mAutoplayCoda;
    bool mIsCurrentTrack;
    std::vector<GemInProgress> mGemsInProgress;
    float mSyncOffset;
    int mTrack;
    bool mEnabled;
    int mLastGemPassed;
    int mLastGemSeen;
    float mLastMiss;
    bool mCheating;
    int mCheatError;
    int mNextCheatError;
    int mNextGemToAutoplay;
    bool mPitchBendReady;
    int mPitchBendRange;
    int mPitchBendMsToFull;
    float mPitchBendMsHit;
    float mBiggestWhammy;
    int mCymbalAutoplayMs;
    bool mSucceeding;
};

class TrackWatcherImpl {
public:
    TrackWatcherImpl(int, const UserGuid&, int, SongData*, GameGemList*, TrackWatcherParent*, DataArray*, int);
    virtual ~TrackWatcherImpl();
    virtual void Init();
    virtual void HandleDifficultyChange();
    virtual void SetIsCurrentTrack(bool);
    virtual void AddSink(BeatMatchSink*);
    virtual void Jump(float);
    virtual void Restart();
    virtual void Poll(float);
    virtual bool Swing(int, bool, bool, GemHitFlags) = 0;
    virtual void NonStrumSwing(int, bool, bool) = 0;
    virtual void FretButtonDown(int) = 0;
    virtual void FretButtonUp(int) = 0;
    virtual void RGFretButtonDown(int);
    virtual void OutOfRangeSwing();
    virtual void SetGemsPlayedUntil(int);
    virtual void Enable(bool);
    virtual bool IsCheating() const;
    virtual void SetCheating(bool);
    virtual void SetAutoplayError(int);
    virtual void SetSyncOffset(float);
    virtual void OnHit(float, int, int, unsigned int, GemHitFlags);
    virtual void OnMiss(float, int, int, unsigned int, GemHitFlags);
    virtual void OnPass(float, int);
    virtual void FakeHitGem(float, int, GemHitFlags);
    virtual void RegisterFill(int);
    virtual void ResetFill();
    virtual void FillSwing(int, int, int, bool);
    virtual void CodaSwing(int, int);
    virtual void FillStop();
    virtual bool IsSwingInRoll(int, unsigned int);
    virtual bool AreSlotsInRoll(unsigned int, int) const;
    virtual void GetNextRoll(int, unsigned int&, int&) const;
    virtual void CheckForTrills(float, int, unsigned int);
    virtual float PollHook(float);
    virtual float JumpHook(float);
    virtual float HitGemHook(float, int, GemHitFlags);
    virtual bool ShouldAutoplayGem(float, int);
    virtual bool GemCanBePassed(int);
    virtual int NextGemAfter(int, bool);
    virtual float Slop(int);
    virtual int ClosestUnplayedGem(float, int);
    virtual int SustainedGemToKill(int);
    virtual bool InTrill(int) const;

    void EndAllSustainedNotes();
    void LoadState(TrackWatcherState&);
    void SaveState(TrackWatcherState&);
    void RecalcGemList();
    void SetAutoplayCoda(bool);
    float CycleAutoplayAccuracy();
    void SetAutoplayAccuracy(float);
    void E3CheatIncSlop();
    void E3CheatDecSlop();

    UserGuid mUserGuid;
    bool mIsLocalUser;
    int mPlayerSlot;
    GameGemList* mGemList;
    TrackWatcherParent* mParent;
    float mSlop;
    int mLastGemHit;
    bool mIsCurrentTrack;
    std::vector<GemInProgress> mGemsInProgress; // instead of int, the type is GemInProgress
    float mSyncOffset;
    bool mSucceeding;
    bool mEnabled;
    std::vector<BeatMatchSink*> mSinks;
    SongData* mSongData;
    bool mTrillSucceeding;
    int mTrillNextSlot;
    float mTrillLastFretMs;
    float mTrillIntervalMs;
    DataArray* mRollIntervalsConfig;
    int mTrack;
    bool mButtonMashingMode;
    int mLastGemPassed;
    int mLastGemSeen;
    float mLastMiss;
    bool mCheating;
    bool mAutoplayCoda;
    int mCheatError;
    int mNextCheatError;
    float mLastCheatCodaSwing;
    int mNextGemToAutoplay;
    float mAutoplayAccuracy;
    int mCymbalAutoplayMs;
    GemHitFlags mLastPlayedHitFlags;
    bool mPitchBendReady;
    int mPitchBendRange;
    int mPitchBendMsToFull;
    float mPitchBendMsHit;
    float mBiggestWhammy;
    std::vector<int> mRollSlotsLastSwingMs;
    int mRollActiveSlots;
    float mRollIntervalMs;
    int mRollEndTick;
    DataArray* mTrillIntervalsConfig;

};

TrackWatcherImpl* NewTrackWatcherImpl(int, const UserGuid&, int, Symbol, SongData*, TrackWatcherParent*, DataArray*);

#endif
