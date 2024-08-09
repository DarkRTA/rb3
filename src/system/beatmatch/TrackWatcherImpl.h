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
    // what RB2 has
    // int mTick; // offset 0x0, size 0x4
    // int mNoStrum; // offset 0x4, size 0x4
    // int mPlayers; // offset 0x8, size 0x4

    // actually a byte, word, and float
    bool mInUse;
    int mGemID;
    float unk8;
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
    virtual void RGFretButtonDown(int){}
    virtual void OutOfRangeSwing(){}
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
    virtual void RegisterFill(int){}
    virtual void ResetFill(){}
    virtual void FillSwing(int, int, int, bool){}
    virtual void CodaSwing(int, int);
    virtual void FillStop(){}
    virtual bool IsSwingInRoll(int, unsigned int);
    virtual bool AreSlotsInRoll(unsigned int, int) const;
    virtual void GetNextRoll(int, unsigned int&, int&) const;
    virtual void CheckForTrills(float, int, unsigned int);
    virtual void PollHook(float);
    virtual void JumpHook(float);
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
    void KillSustainForSlot(int);
    void KillSustain(int);
    void NoteSwing(unsigned int, int);
    bool InSlopWindow(float, float) const;
    bool Playable(int);
    bool IsTrillActive() const;
    void SetAllGemsUnplayed();
    void EndSustainedNote(GemInProgress&);
    bool HasAnyGemInProgress() const;
    GemInProgress* GetGemInProgressWithID(int);
    GemInProgress* GetGemInProgressWithSlot(int);
    GemInProgress* GetUnusedGemInProgress(float);

    void CheckForSustainedNoteTimeout(float);
    void CheckForRolls(float, int);
    void CheckForTrillTimeout(float);
    void CheckForAutoplay(float);
    void CheckForPasses(float);
    void CheckForGemsSeen(float);
    void CheckForPitchBend(float);
    void CheckForCodaLanes(int);

    void HitGem(float, int, unsigned int, GemHitFlags);
    void SendSwingAtHopo(float, int);
    void SendHopo(float, int);

    UserGuid mUserGuid; // 0x4
    bool mIsLocalUser; // 0x14
    int mPlayerSlot; // 0x18
    GameGemList* mGemList; // 0x1c
    TrackWatcherParent* mParent; // 0x20
    float mSlop; // 0x24
    int mLastGemHit; // 0x28
    bool mIsCurrentTrack; // 0x2c
    std::vector<GemInProgress> mGemsInProgress; // 0x30
    float mSyncOffset; // 0x38
    bool mSucceeding; // 0x3c
    bool mEnabled; // 0x3d
    std::vector<BeatMatchSink*> mSinks; // 0x40
    SongData* mSongData; // 0x48
    bool mTrillSucceeding; // 0x4c
    int mTrillNextSlot; // 0x50
    float mTrillLastFretMs; // 0x54
    float mTrillIntervalMs; // 0x58
    DataArray* mRollIntervalsConfig; // 0x5c
    int mTrack; // 0x60
    bool mButtonMashingMode; // 0x64
    int mLastGemPassed; // 0x68
    int mLastGemSeen; // 0x6c
    float mLastMiss; // 0x70
    bool mCheating; // 0x74
    bool mAutoplayCoda; // 0x75
    int mCheatError; // 0x78
    int mNextCheatError; // 0x7c
    float mLastCheatCodaSwing; // 0x80
    int mNextGemToAutoplay; // 0x84
    float mAutoplayAccuracy; // 0x88
    int mCymbalAutoplayMs; // 0x8c
    GemHitFlags mLastPlayedHitFlags; // 0x90
    bool mPitchBendReady; // 0x94
    int mPitchBendRange; // 0x98
    int mPitchBendMsToFull; // 0x9c
    float mPitchBendMsHit; // 0xa0
    float mBiggestWhammy; // 0xa4
    std::vector<float> mRollSlotsLastSwingMs; // 0xa8
    int mRollActiveSlots; // 0xb0
    float mRollIntervalMs; // 0xb4
    int mRollEndTick; // 0xb8
    DataArray* mTrillIntervalsConfig; // 0xbc

};

TrackWatcherImpl* NewTrackWatcherImpl(int, const UserGuid&, int, Symbol, SongData*, TrackWatcherParent*, DataArray*);

#endif
