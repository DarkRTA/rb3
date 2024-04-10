#ifndef BEATMATCH_REALGUITARCONTROLLER_H
#define BEATMATCH_REALGUITARCONTROLLER_H
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"

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

    int dummy;

};

#endif
