#ifndef BEATMATCH_JOYPADCONTROLLER_H
#define BEATMATCH_JOYPADCONTROLLER_H
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"

enum SecondaryPedalFunction {
    kHiHatPedal,
    kSecondKickPedal
};

class JoypadController : public BeatMatchController {
public:
    JoypadController(User*, const DataArray*, BeatMatchControllerSink*, bool, bool);
    virtual ~JoypadController();
    virtual DataNode Handle(DataArray*, bool);
    virtual int ButtonToSlot(JoypadButton) const;
    virtual int SlotToButton(int) const;
    virtual void Disable(bool);
    virtual bool IsDisabled() const;
    virtual float GetWhammyBar() const;
    virtual int GetFretButtons() const;
    virtual int GetVelocityBucket(int) const;
    virtual int GetVirtualSlot(int i) const;
    virtual void UseAlternateMapping(bool);
    virtual bool IsAlternateMapping() const;
    virtual void SetSecondPedalHiHat(bool);
    virtual void SetCymbalConfiguration(int);

    int MapSlot(int) const;
    void ReconcileFretState();
    bool IsCymbal(int) const;

    int OnMsg(const ButtonDownMsg&);
    int OnMsg(const ButtonUpMsg&);

    bool mDisabled;
    bool unk3d;
    bool mAlternateMapping;
    unsigned int mFretMask;
    SecondaryPedalFunction mSecondaryPedalFunction;
    int mCymbalConfiguration;
    JoypadButton mPadShiftButton;
    JoypadButton mCymbalShiftButton;
    JoypadButton mSecondaryPedalButton;
    LocalUser* mLocalUser;
    BeatMatchControllerSink* mSink;
    DataArray* mVelocityAxes;
    DataArray* mVelocityPressures;

};

#endif
