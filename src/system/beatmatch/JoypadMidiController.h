#ifndef BEATMATCH_JOYPADMIDICONTROLLER_H
#define BEATMATCH_JOYPADMIDICONTROLLER_H
#include "beatmatch/JoypadController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"
#include "os/UsbMidiKeyboardMsgs.h"

class JoypadMidiController : public JoypadController {
public:
    JoypadMidiController(User*, const DataArray*, BeatMatchControllerSink*, bool);
    virtual ~JoypadMidiController();
    virtual DataNode Handle(DataArray*, bool);
    virtual float GetWhammyBar() const;
    virtual float GetCapStrip() const;

    JoypadButton MidiNoteToButton(int) const;
    int OnMsg(const KeyboardKeyPressedMsg&);
    int OnMsg(const KeyboardKeyReleasedMsg&);
    int OnMsg(const KeyboardSustainMsg&);
    int OnMsg(const KeyboardModMsg&);
    int OnMsg(const ButtonDownMsg&);

    float mWhammy;
};

#endif
