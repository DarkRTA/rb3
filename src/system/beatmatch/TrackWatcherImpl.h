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

    UserGuid mUserGuid;
    bool mIsLocalUser;
    int mPlayerSlot;
    GameGemList* mGemList;
    TrackWatcherParent* mParent;
    float mSlop;
    int mLastGemHit;
    bool mIsCurrentTrack;
    std::vector<int> mGemsInProgress;
    float mSyncOffset;
    bool mSucceeding;
    bool mEnabled;
    std::vector<int> mSinks;
    SongData* mSongData;
    bool mTrillSucceeding;
    int mTrillNextSlot;
    float mTrillLastFretMs;
    float mTrillIntervalMs;
    DataArray* mRollIntervalsConfig;

    int unk60;
    int unk64;

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

#endif
