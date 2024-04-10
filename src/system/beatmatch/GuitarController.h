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
    virtual bool IsDisabled() const;
    virtual float GetWhammyBar() const;
    virtual int GetFretButtons() const;
    virtual bool IsShifted() const;
    virtual void SetAutoSoloButtons(bool);

    void ReconcileFretState();
    
    bool mDisabled;
    bool unk3d;
    int mFretMask;
    int mShiftButtonMask;
    BeatMatchControllerSink* mSink;
    ControllerStyle mControllerStyle;
    std::vector<int> mStrumBarButtons;
    int unk58;
};

#endif
