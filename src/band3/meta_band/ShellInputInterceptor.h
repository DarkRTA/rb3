#pragma once
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "obj/Object.h"
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include "os/Timer.h"

class ShellInputInterceptor : public Hmx::Object {
public:
    ShellInputInterceptor(BandUserMgr*);
    virtual ~ShellInputInterceptor(){}
    virtual DataNode Handle(DataArray*, bool);

    DataNode OnMsg(const ButtonDownMsg&);
    DataNode OnMsg(const ButtonUpMsg&);
    JoypadAction FilterAction(LocalBandUser*, JoypadAction);
    bool IsDoubleStrum(LocalBandUser*, int);

    BandUserMgr* mBandUserMgr; // 0x1c
    bool mButtonDownSwitch; // 0x20
    bool mButtonUpSwitch; // 0x21
    int unk24; // 0x24
    Timer mTime; // 0x28
    float mLastUpDown[4]; // 0x58
};