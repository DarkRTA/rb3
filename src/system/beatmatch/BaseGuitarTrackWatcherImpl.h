#pragma once
#include "beatmatch/TrackWatcherImpl.h"
#include "beatmatch/GameGem.h"

class BaseGuitarTrackWatcherImpl : public TrackWatcherImpl {
public:
    BaseGuitarTrackWatcherImpl(int, const UserGuid &, int, SongData *, GameGemList *, TrackWatcherParent *, DataArray *);
    virtual ~BaseGuitarTrackWatcherImpl();
    virtual void HandleDifficultyChange();
    virtual bool Swing(int, bool, bool, GemHitFlags);
    virtual void NonStrumSwing(int, bool, bool);
    virtual void FretButtonDown(int);
    virtual void FretButtonUp(int);
    virtual void PollHook(float);
    virtual void JumpHook(float);
    virtual float HitGemHook(float, int, GemHitFlags);
    virtual bool GemCanBePassed(int);
    virtual float Slop(int);
    virtual int SustainedGemToKill(int);
    virtual void AutoCaptureHook();
    virtual void ResetGemNotFretted();
    virtual bool HandleHitsAndMisses(
        int gemID,
        int slot,
        float ms,
        bool guitar,
        bool provisional,
        bool inCodaFreestyle,
        GemHitFlags flags
    ) = 0;
    virtual void RecordFretButtonDown(int slot) = 0;
    virtual void RecordFretButtonUp(int slot) = 0;
    virtual unsigned int GetFretButtonsDown() const = 0;
    virtual bool FretMatch(int gemID, bool, bool) const = 0;
    virtual bool IsChordSubset(int gemID) const = 0;
    virtual bool IsHighestFret(int slot) const = 0;
    virtual bool InGem(int slot, const GameGem &gem) const = 0;
    virtual bool HarmlessFretDown(int slot, int gemID) const = 0;
    virtual bool IsCoreGuitar() const = 0;

    void CheckForFretTimeout(float);
    void CheckForHopoTimeout(float);
    void TryToHopo(float ms, int slot, bool, bool);
    void TryToFinishSwing(float, int);
    void SetLastNoStrumGem(float, int);
    bool CanHopo(int) const;

    float mLastLateGemHit; // 0xc0
    int mLastNoStrumGemHit; // 0xc4
    int mLastNoStrumGemSwung; // 0xc8
    float mMostRecentHit; // 0xcc
    int mGemNotFretted; // 0xd0
    int mFretWhenStrummed; // 0xd4
    float mFretWaitTimeout; // 0xd8
    bool mHarmlessSwing; // 0xdc
    float mFretSlop; // 0xe0
    GemHitFlags mBaseGuitarFlags; // 0xe4 - change the name of this var cuz it probably
                                  // ain't the clearest
};
