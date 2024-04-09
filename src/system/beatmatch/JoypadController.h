#ifndef BEATMATCH_JOYPADCONTROLLER_H
#define BEATMATCH_JOYPADCONTROLLER_H
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"

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

    void ReconcileFretState();

    int OnMsg(const ButtonDownMsg&);
    int OnMsg(const ButtonUpMsg&);

    bool unk3c;
    bool unk3d;
    bool unk3e;
    int unk40;
    int unk44;
    int unk48;
    JoypadButton mPadShiftButton;
    JoypadButton mCymbalShiftButton;
    JoypadButton mSecondaryPedalButton;
    LocalUser* mLocalUser;
    BeatMatchControllerSink* mSink;
    DataArray* mVelocityAxes;
    DataArray* mVelocityPressures;

};

#endif
