#ifndef BEATMATCH_BASEGUITARTRACKWATCHERIMPL_H
#define BEATMATCH_BASEGUITARTRACKWATCHERIMPL_H
#include "beatmatch/TrackWatcherImpl.h"
#include "beatmatch/GameGem.h"

class BaseGuitarTrackWatcherImpl : public TrackWatcherImpl {
public:
    BaseGuitarTrackWatcherImpl(int, const UserGuid&, int, SongData*, GameGemList*, TrackWatcherParent*, DataArray*);
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
    virtual bool HandleHitsAndMisses(int, int, float, bool, bool, bool, GemHitFlags) = 0;
    virtual void RecordFretButtonDown(int) = 0;
    virtual void RecordFretButtonUp(int) = 0;
    virtual unsigned int GetFretButtonsDown() const = 0;
    virtual bool FretMatch(int, bool, bool) const = 0;
    virtual bool IsChordSubset(int) const = 0;
    virtual bool IsHighestFret(int) const = 0;
    virtual bool InGem(int, const GameGem&) const = 0;
    virtual bool HarmlessFretDown(int, int) const = 0;
    virtual bool IsCoreGuitar(void) const = 0;

    void CheckForFretTimeout(float);
    void CheckForHopoTimeout(float);
    void TryToHopo(float, int, bool, bool);
    void TryToFinishSwing(float, int);
    void SetLastNoStrumGem(float, int);
    bool CanHopo(int) const;

    float mLastLateGemHit;
    int mLastNoStrumGemHit;
    int mLastNoStrumGemSwung;
    float mMostRecentHit;
    int mGemNotFretted;
    int mFretWhenStrummed;
    float mFretWaitTimeout;
    bool mHarmlessSwing;
    float mFretSlop;
    GemHitFlags mBaseGuitarFlags; // change the name of this var cuz it probably ain't the clearest
};

#endif
