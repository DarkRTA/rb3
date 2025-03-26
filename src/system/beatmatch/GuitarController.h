#pragma once
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include "os/UsbMidiGuitarMsgs.h"
#include <vector>

enum ControllerStyle {
    kPS2 = 0,
    kPS3 = 1,
    kHxXbox = 2,
    kRoXbox = 3,
    kRoPS3 = 4,
    kHxWii = 5,
};

// for 5 lane guitars
class GuitarController : public BeatMatchController {
public:
    GuitarController(User *, const DataArray *, BeatMatchControllerSink *, bool, bool);
    virtual ~GuitarController();
    virtual DataNode Handle(DataArray *, bool);
    virtual void Poll();
    virtual void Disable(bool);
    virtual bool IsDisabled() const { return mDisabled; }
    virtual float GetWhammyBar() const;
    virtual float GetCapStrip() const;
    virtual int GetFretButtons() const { return mFretMask; }
    virtual bool IsShifted() const;
    virtual void SetAutoSoloButtons(bool b) { mAutoSoloButtons = b; }

    int GetCurrentSlot() const;
    int OnMsg(const ButtonDownMsg &);
    int OnMsg(const ButtonUpMsg &);
    void ReconcileFretState();

    bool mDisabled; // 0x3c
    bool mAutoSoloButtons; // 0x3d
    int mFretMask; // 0x40
    int mShiftButtonMask; // 0x44
    BeatMatchControllerSink *mSink; // 0x48
    ControllerStyle mControllerStyle; // 0x4c
    std::vector<int> mStrumBarButtons; // 0x50
    JoypadButton mMercuryButton; // 0x58
};
