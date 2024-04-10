#ifndef BEATMATCH_JOYPADMIDICONTROLLER_H
#define BEATMATCH_JOYPADMIDICONTROLLER_H
#include "beatmatch/JoypadController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"

class JoypadMidiController : public JoypadController {
public:
    JoypadMidiController(User*, const DataArray*, BeatMatchControllerSink*, bool, bool);
    virtual ~JoypadMidiController();
    virtual DataNode Handle(DataArray*, bool);
    virtual float GetWhammyBar() const;
    virtual float GetCapStrip() const;

    int dummy;

};

#endif
