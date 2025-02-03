#pragma once
#include "beatmatch/TrackWatcherImpl.h"

class JoypadTrackWatcherImpl : public TrackWatcherImpl {
public:
    JoypadTrackWatcherImpl(
        int,
        const UserGuid &,
        int,
        SongData *,
        GameGemList *,
        TrackWatcherParent *,
        DataArray *,
        int
    );
    virtual ~JoypadTrackWatcherImpl();
    virtual bool Swing(int, bool, bool, GemHitFlags);
    virtual void NonStrumSwing(int, bool, bool) {}
    virtual void FretButtonDown(int) {}
    virtual void FretButtonUp(int);
    virtual void PollHook(float);
    virtual void JumpHook(float);
    virtual float HitGemHook(float, int, GemHitFlags);
    virtual bool AllowAllInputInRolls() const;
    virtual void CheckForChordTimeout(float ms);

    void ResetChordInProgress();
    void TryToCompleteChord(float ms, int slot);

    float mChordSlop; // 0xc0
    int mChordGemInProgress; // 0xc4
    int mChordSlotsInProgress; // 0xc8
    int mChordLastSlot; // 0xcc
    float mChordTimeout; // 0xd0
};
