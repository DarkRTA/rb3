#pragma once
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include "os/Timer.h"
#include "obj/Object.h"

class JoypadRepeat {
public:
    JoypadButton mLastBtn; // 0x0
    JoypadAction mLastAction; // 0x4
    int mLastPad; // 0x8
    Timer mHoldTimer; // 0x10
    Timer mRepeatTimer; // 0x40

    JoypadRepeat();
    void Start(JoypadButton, JoypadAction, int);
    void Reset(JoypadButton);
    void Poll(float, float, Hmx::Object *, int);
    void SendRepeat(Hmx::Object *, int);
};

class JoypadClient : public Hmx::Object {
public:
    JoypadClient(Hmx::Object *sink);
    ~JoypadClient();

    LocalUser *mUser; // 0x1C
    Hmx::Object *mSink; // 0x20
    int mBtnMask; // 0x24
    float mHoldMs; // 0x28
    float mRepeatMs; // 0x2C
    JoypadRepeat mRepeats[4]; // 0x30
    bool mVirtualDpad; // 0x1F0
    bool mFilterAllButStart; // 0x1F1

    virtual DataNode Handle(DataArray *, bool);

    void Init();
    void SetFilterAllButStart(bool);
    void SetRepeatMask(int);
    void SetVirtualDpad(bool);
    void Poll();
    bool OnMsg(const ButtonDownMsg &);
    bool OnMsg(const ButtonUpMsg &);
};

void JoypadClientPoll();
