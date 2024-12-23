#pragma once
#include "beatmatch/BaseGuitarTrackWatcherImpl.h"
#include "beatmatch/RGGemMatcher.h"

class RealGuitarTrackWatcherImpl : public BaseGuitarTrackWatcherImpl {
public:
    RealGuitarTrackWatcherImpl(int, const UserGuid&, int, SongData*, GameGemList*, TrackWatcherParent*, DataArray*);
    virtual ~RealGuitarTrackWatcherImpl();
    virtual bool Swing(int, bool, bool, GemHitFlags);
    virtual void NonStrumSwing(int, bool, bool);
    virtual void FretButtonUp(int);
    virtual void RGFretButtonDown(int);
    virtual bool IsSwingInRoll(int, unsigned int);
    virtual bool AreSlotsInRoll(unsigned int, int) const;
    virtual void GetNextRoll(int, unsigned int&, int&) const;
    virtual void CheckForTrills(float, int, unsigned int);
    virtual void PollHook(float);
    virtual void JumpHook(float);
    virtual bool InTrill(int) const;
    virtual bool HandleHitsAndMisses(int, int, float, bool, bool, bool, GemHitFlags);
    virtual void RecordFretButtonDown(int);
    virtual void RecordFretButtonUp(int);
    virtual unsigned int GetFretButtonsDown() const;
    virtual bool FretMatch(int, bool, bool) const;
    virtual bool IsChordSubset(int) const;
    virtual bool IsHighestFret(int) const;
    virtual bool InGem(int, const GameGem&) const;
    virtual bool HarmlessFretDown(int, int) const;
    virtual bool IsCoreGuitar() const;

    bool StrumOK(int) const;

    RGGemMatcher mMatcher; // 0xe8
    float unk1f0; // 0x1f0 - mLastMissTime
    float mMissWindowMs; // 0x1f4
    bool mIs22Fret; // 0x1f8
};