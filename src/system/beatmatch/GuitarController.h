#ifndef BEATMATCH_GUITARCONTROLLER_H
#define BEATMATCH_GUITARCONTROLLER_H
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
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
    GuitarController(User*, const DataArray*, BeatMatchControllerSink*, bool, bool);
    virtual ~GuitarController();
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Disable(bool);
    virtual bool IsDisabled() const { return mDisabled; }
    virtual float GetWhammyBar() const;
    virtual float GetCapStrip() const;
    virtual int GetFretButtons() const { return mFretMask; }
    virtual bool IsShifted() const;
    virtual void SetAutoSoloButtons(bool b){ mAutoSoloButtons = b; }

    int GetCurrentSlot() const;
    int OnMsg(const ButtonDownMsg&);
    int OnMsg(const ButtonUpMsg&);
    void ReconcileFretState();
    
    bool mDisabled;
    bool mAutoSoloButtons;
    int mFretMask;
    int mShiftButtonMask;
    BeatMatchControllerSink* mSink;
    ControllerStyle mControllerStyle;
    std::vector<int> mStrumBarButtons;
    int unk58;
};

#endif
