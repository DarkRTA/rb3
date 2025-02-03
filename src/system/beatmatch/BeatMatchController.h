#pragma once
#include "obj/Object.h"
#include "obj/Data.h"
#include "os/Joypad.h"
#include "beatmatch/HitSink.h"
#include "beatmatch/TrackType.h"

// forward decs
class BeatMatchControllerSink;
class User;

enum BeatMatchControllerGemMapping {
    kDefaultGemMapping,
    kDrumGemMapping
};

class BeatMatchController : public Hmx::Object {
public:
    BeatMatchController(User *, const DataArray *, bool);
    virtual ~BeatMatchController() {}
    virtual int ButtonToSlot(JoypadButton button) const;
    virtual int SlotToButton(int slot) const;
    virtual void Poll() {}
    virtual void Disable(bool) = 0;
    virtual bool IsDisabled() const = 0;
    virtual float GetWhammyBar() const = 0;
    virtual float GetCapStrip() const { return 0.0f; }
    virtual int GetFretButtons() const = 0;
    virtual void EnableShift(bool) {}
    virtual bool IsShifted() const { return false; }
    virtual int GetVelocityBucket(int slot) const;
    virtual int GetVirtualSlot(int slot) const;
    virtual void UseAlternateMapping(bool) {}
    virtual bool IsAlternateMapping() const { return false; }
    virtual void SetSecondPedalHiHat(bool) {}
    virtual void SetCymbalConfiguration(int) {}
    virtual void SetAutoSoloButtons(bool) {}
    virtual void SetHitSink(HitSink *sink) { mHitSink = sink; }
    virtual int GetRGFret(int) const { return -1; }

    int ButtonToSlot(JoypadButton, const DataArray *) const;
    void RegisterHit(HitType) const;
    void RegisterKey(int) const;
    void RegisterRGFret(int, int) const;
    void RegisterRGStrum(int) const;
    bool IsOurPadNum(int) const;
    User *GetUser() const { return mUser; }

    User *mUser; // 0x1c
    int mForceMercuryBut; // 0x20
    bool mLefty; // 0x24
    bool unk25; // 0x25
    BeatMatchControllerGemMapping mGemMapping; // 0x28
    HitSink *mHitSink; // 0x2c
    DataArray *mSlots; // 0x30
    DataArray *mLeftySlots; // 0x34
    DataArray *mRightySlots; // 0x38
};

BeatMatchController *
NewController(User *, const DataArray *, BeatMatchControllerSink *, bool, bool, TrackType);
