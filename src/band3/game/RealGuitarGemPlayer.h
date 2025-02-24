#pragma once
#include "beatmatch/RGState.h"
#include "game/GemPlayer.h"

class RealGuitarGemPlayer : public GemPlayer {
public:
    RealGuitarGemPlayer(BandUser *, BeatMaster *, Band *, int, BandPerformer *);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~RealGuitarGemPlayer();
    virtual void Restart(bool);
    virtual void ResetController(bool);
    virtual void Swing(int, int, float, bool, bool);
    virtual void FretButtonDown(int, float);
    virtual void FretButtonUp(int, float);
    virtual int GetNumRolls() const;
    virtual void GetRollInfo(int, int &, int &) const;
    virtual int GetNumTrills() const;
    virtual void GetTrillInfo(int, int &, int &) const;
    virtual int GetTrackSlot(int) const;
    virtual void SwingHook(int, int, float, bool, bool);
    virtual void HitHook(int, float, int, unsigned int, GemHitFlags);
    virtual void MissHook(int, int, float, int, int);
    virtual void PassHook(int, float, int, bool);
    virtual void SeeGemHook(int, float, int);
    virtual unsigned int GetRollSlots(int) const;
    virtual bool GetTrillSlots(int, std::pair<int, int> &) const;

    void E3CheatIncSlop();
    void E3CheatDecSlop();
    const RGState &GetRGState() const;
    void SetRGState(const RGState &);

    RGState mRGState; // 0x40c
};