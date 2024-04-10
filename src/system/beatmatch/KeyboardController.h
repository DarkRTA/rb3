#ifndef BEATMATCH_KEYBOARDCONTROLLER_H
#define BEATMATCH_KEYBOARDCONTROLLER_H
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"
#include "os/UsbMidiKeyboardMsgs.h"

class KeyboardController : public BeatMatchController {
public:
    KeyboardController(User*, const DataArray*, BeatMatchControllerSink*, bool);
    virtual ~KeyboardController();
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Disable(bool);
    virtual bool IsDisabled() const { return mDisabled; }
    virtual float GetWhammyBar() const;
    virtual float GetCapStrip() const;
    virtual int GetFretButtons() const { return mFretButtons; }

    int OnMsg(const KeyboardKeyPressedMsg&);
    int OnMsg(const KeyboardKeyReleasedMsg&);
    int OnMsg(const KeyboardSustainMsg&);
    int OnMsg(const KeyboardModMsg&);
    int OnMsg(const ButtonDownMsg&);

    int MidiNoteToSlot(int) const;

    bool mDisabled;
    int mFretButtons;
    float mWhammy;
    BeatMatchControllerSink* mSink;

};

#endif
