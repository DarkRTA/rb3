#ifndef OS_JOYPADCLIENT_H
#define OS_JOYPADCLIENT_H
#include "os/Joypad.h"
#include "os/Timer.h"
#include "obj/Object.h"

class JoypadRepeat {
public:
    JoypadButton mLastBtn;
    JoypadAction mLastAction;
    int mLastPad;
    Timer mHoldTimer;
    Timer mRepeatTimer;

    JoypadRepeat();
    void Start(JoypadButton, JoypadAction, int);
    void Reset(JoypadButton);
};

class JoypadClient : public Hmx::Object {
public:
    int mUser;
    Hmx::Object* mSink;
    int mBtnMask;
    float mHoldMs;
    float mRepeatMs;
    JoypadRepeat mRepeats[8];
    bool mVirtualDpad;

    void SetVirtualDpad(bool);
};

#endif
