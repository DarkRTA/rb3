#ifndef OS_JOYPADCLIENT_H
#define OS_JOYPADCLIENT_H
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
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
    void Poll(float, float, Hmx::Object *, int);
};

class JoypadClient : public Hmx::Object {
public:
    JoypadClient(Hmx::Object *sink);
    ~JoypadClient();

    LocalUser *mUser; // 0x1C
    Hmx::Object* mSink; // 0x20
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
    DataNode OnMsg(const ButtonDownMsg &);
    DataNode OnMsg(const ButtonUpMsg &);
};

void JoypadClientPoll();

#endif
