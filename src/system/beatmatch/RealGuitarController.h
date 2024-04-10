#ifndef BEATMATCH_REALGUITARCONTROLLER_H
#define BEATMATCH_REALGUITARCONTROLLER_H
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"
#include "os/UsbMidiGuitarMsgs.h"

#define kNumRGStrings 6

class RealGuitarController : public BeatMatchController {
public:
    RealGuitarController(User*, const DataArray*, BeatMatchControllerSink*, bool, bool);
    virtual ~RealGuitarController();
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Disable(bool);
    virtual bool IsDisabled() const;
    virtual float GetWhammyBar() const;
    virtual int GetFretButtons() const;
    virtual bool IsShifted() const;
    virtual void SetAutoSoloButtons(bool);
    virtual int GetRGFret(int) const;

    int OnMsg(const StringStrummedMsg&);
    int OnMsg(const RGSwingMsg&);
    int OnMsg(const ButtonDownMsg&);
    int OnMsg(const ButtonUpMsg&);
    int OnMsg(const RGAccelerometerMsg&);
    int OnMsg(const StringStoppedMsg&){ return 0; }

    bool mDisabled;
    int unk40;
    BeatMatchControllerSink* mSink;
    int mStrings[kNumRGStrings];

};

#endif
