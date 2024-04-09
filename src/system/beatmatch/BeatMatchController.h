#ifndef BEATMATCH_BEATMATCHCONTROLLER_H
#define BEATMATCH_BEATMATCHCONTROLLER_H
#include "obj/Object.h"
#include "obj/Data.h"
#include "os/Joypad.h"
#include "beatmatch/HitSink.h"

class User; // forward dec

enum BeatMatchControllerGemMapping {
    kDefaultGemMapping,
    kDrumGemMapping
};

class BeatMatchController : public Hmx::Object {
public:
    BeatMatchController(User*, const DataArray*, bool);
    virtual ~BeatMatchController(){}
    virtual int ButtonToSlot(JoypadButton) const;
    virtual int SlotToButton(int) const;
    virtual void Poll(){}
    virtual void Disable(bool) = 0;
    virtual bool IsDisabled() const = 0;
    virtual float GetWhammyBar() const = 0;
    virtual float GetCapStrip() const { return 0.0f; }
    virtual int GetFretButtons() const = 0;
    virtual void EnableShift(bool){}
    virtual bool IsShifted() const { return false; }
    virtual int GetVelocityBucket(int) const;
    virtual int GetVirtualSlot(int i) const;
    virtual void UseAlternateMapping(bool){}
    virtual bool IsAlternateMapping() const { return false; }
    virtual void SetSecondPedalHiHat(bool){}
    virtual void SetCymbalConfiguration(int){}
    virtual void SetAutoSoloButtons(bool){}
    virtual void SetHitSink(HitSink* sink){ mHitSink = sink; }
    virtual int GetRGFret(int) const { return -1; }

    int ButtonToSlot(JoypadButton, const DataArray*) const;
    void RegisterHit(HitType) const;
    void RegisterKey(int) const;
    void RegisterRGFret(int, int) const;
    void RegisterRGStrum(int) const;
    bool IsOurPadNum(int) const;

    User* mUser;
    int mForceMercuryBut;
    bool mLefty;
    bool unk25;
    BeatMatchControllerGemMapping mGemMapping;
    HitSink* mHitSink;
    DataArray* mSlots;
    DataArray* mLeftySlots;
    DataArray* mRightySlots;
};

#endif
