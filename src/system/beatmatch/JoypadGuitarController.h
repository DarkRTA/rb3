#ifndef BEATMATCH_JOYPADGUITARCONTROLLER_H
#define BEATMATCH_JOYPADGUITARCONTROLLER_H
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"

class JoypadGuitarController : public BeatMatchController {
public:
    JoypadGuitarController(User*, const DataArray*, BeatMatchControllerSink*, bool, bool);
    virtual ~JoypadGuitarController();
    virtual DataNode Handle(DataArray*, bool);
    virtual void Disable(bool);
    virtual bool IsDisabled() const { return mDisabled; }
    virtual float GetWhammyBar() const;
    virtual int GetFretButtons() const { return mFretMask; }

    int OnMsg(const ButtonDownMsg&);
    int OnMsg(const ButtonUpMsg&);
    void ReconcileFretState();

    bool mDisabled;
    bool mDpadForNavigation;
    int mFretMask;
    BeatMatchControllerSink* mSink;

};

#endif
