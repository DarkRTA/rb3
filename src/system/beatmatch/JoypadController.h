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
    virtual bool IsDisabled() const { return mDisabled; }
    virtual float GetWhammyBar() const;
    virtual int GetFretButtons() const { return 0; }
    virtual int GetVelocityBucket(int) const;
    virtual int GetVirtualSlot(int i) const;
    virtual void UseAlternateMapping(bool b){ mAlternateMapping = b; }
    virtual bool IsAlternateMapping() const { return mAlternateMapping; }
    virtual void SetSecondPedalHiHat(bool);
    virtual void SetCymbalConfiguration(int);

    int MapSlot(int) const;
    void ReconcileFretState();
    bool IsCymbal(int) const;

    int OnMsg(const ButtonDownMsg&);
    int OnMsg(const ButtonUpMsg&);

    JoypadData* GetJoypadData() const { return mLocalUser ? JoypadGetPadData(mLocalUser->GetPadNum()) : 0; }
    bool HasYellowCymbal(JoypadData* data) const { return (mCymbalConfiguration & 4) || data->mHasYellowCymbal; }
    bool HasBlueCymbal(JoypadData* data) const { return (mCymbalConfiguration & 8) || data->mHasBlueCymbal; }
    bool HasGreenCymbal(JoypadData* data) const { return (mCymbalConfiguration & 0x10) || data->mHasGreenCymbal; }

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
