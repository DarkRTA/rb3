#ifndef BEATMATCH_GUITARCONTROLLER_H
#define BEATMATCH_GUITARCONTROLLER_H
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "os/JoypadMsgs.h"
#include "os/UsbMidiGuitarMsgs.h"

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
    
    int dummy;
};

#endif
