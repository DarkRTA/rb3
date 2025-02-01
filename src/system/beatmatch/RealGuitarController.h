#pragma once
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"
#include "os/UsbMidiGuitarMsgs.h"
#include "beatmatch/RGUtl.h"

// for the Squier
class RealGuitarController : public BeatMatchController {
public:
    RealGuitarController(User *, const DataArray *, BeatMatchControllerSink *, bool, bool);
    virtual ~RealGuitarController();
    virtual DataNode Handle(DataArray *, bool);
    virtual void Poll();
    virtual void Disable(bool);
    virtual bool IsDisabled() const;
    virtual float GetWhammyBar() const;
    virtual int GetFretButtons() const;
    virtual bool IsShifted() const;
    virtual void SetAutoSoloButtons(bool);
    virtual int GetRGFret(int) const;

    int OnMsg(const StringStrummedMsg &);
    int OnMsg(const RGSwingMsg &);
    int OnMsg(const ButtonDownMsg &);
    int OnMsg(const ButtonUpMsg &);
    int OnMsg(const RGAccelerometerMsg &);
    int OnMsg(const StringStoppedMsg &) { return 0; }

    bool mDisabled; // 0x3c
    int unk40; // 0x40 - usbmidiguitar* mguitar?
    BeatMatchControllerSink *mSink; // 0x44
    int mStrings[kNumRGStrings]; // 0x48
};
