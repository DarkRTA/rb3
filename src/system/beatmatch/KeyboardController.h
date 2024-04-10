#ifndef BEATMATCH_KEYBOARDCONTROLLER_H
#define BEATMATCH_KEYBOARDCONTROLLER_H
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"

class KeyboardController : public BeatMatchController {
public:
    KeyboardController(User*, const DataArray*, BeatMatchControllerSink*, bool, bool);
    virtual ~KeyboardController();
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Disable(bool);
    virtual bool IsDisabled() const;
    virtual float GetWhammyBar() const;
    virtual float GetCapStrip() const;
    virtual int GetFretButtons() const;

    int dummy;

};

#endif
