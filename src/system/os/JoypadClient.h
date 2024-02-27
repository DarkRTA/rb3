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

class Joypad : public Hmx::Object {

};

// class JoypadClient : public Object {
//     // total size: 0x448
//     int mUser; // offset 0x28, size 0x4
//     class Object * mSink; // offset 0x2C, size 0x4
//     int mBtnMask; // offset 0x30, size 0x4
//     float mHoldMs; // offset 0x34, size 0x4
//     float mRepeatMs; // offset 0x38, size 0x4
//     struct JoypadRepeat mRepeats[8]; // offset 0x40, size 0x400
//     unsigned char mVirtualDpad; // offset 0x440, size 0x1
// };

#endif
