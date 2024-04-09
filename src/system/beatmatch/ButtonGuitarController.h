#ifndef BEATMATCH_BUTTONGUITARCONTROLLER_H
#define BEATMATCH_BUTTONGUITARCONTROLLER_H
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "obj/Object.h"
#include "os/User.h"
#include "obj/Data.h"
#include "os/Joypad.h"
#include "beatmatch/HitSink.h"
#include "os/JoypadMsgs.h"
#include "os/UsbMidiGuitarMsgs.h"

// for the Mustang
class ButtonGuitarController : public BeatMatchController {
public:
    ButtonGuitarController(User*, const DataArray*, BeatMatchControllerSink*, bool, bool);
    virtual ~ButtonGuitarController();
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll(){}
    virtual void Disable(bool);
    virtual bool IsDisabled() const;
    virtual float GetWhammyBar() const;
    virtual int GetFretButtons() const;
    virtual bool IsShifted() const;
    virtual void SetAutoSoloButtons(bool);

    int OnMsg(const RGSwingMsg&);
    int OnMsg(const ButtonDownMsg&);
    int OnMsg(const ButtonUpMsg&);
    int OnMsg(const RGFretButtonDownMsg&);
    int OnMsg(const RGFretButtonUpMsg&);
    int OnMsg(const RGAccelerometerMsg&);

    int OnMsg(const StringStrummedMsg&){ return 0; }
    int OnMsg(const StringStoppedMsg&){ return 0; }

    int GetCurrentSlot() const;

    bool mDisabled;
    bool mShifted;
    int mSlotMask;
    int unk44;
    BeatMatchControllerSink* mSink;
};

#endif
