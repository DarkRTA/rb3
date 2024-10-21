#include "meta_band/ShellInputInterceptor.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include "ui/UI.h"

ShellInputInterceptor::ShellInputInterceptor(BandUserMgr* mgr) : mBandUserMgr(mgr), mButtonDownSwitch(1), mButtonUpSwitch(1) {
    mTime.Start();
    for(int i = 0; i < 4; i++) mLastUpDown[i] = 0;
}

DataNode ShellInputInterceptor::OnMsg(const ButtonDownMsg& msg){
    LocalBandUser* user = BandUserMgr::GetLocalBandUser(msg.GetUser());
    if(mButtonDownSwitch){
        JoypadAction filteredAction = FilterAction(user, msg.GetAction());
        JoypadAction rawAction = msg.GetAction();
        if(filteredAction != rawAction){
            static ButtonDownMsg new_msg(nullptr, kPad_Xbox_A, kAction_Confirm, 0);
            new_msg[0] = user;
            new_msg[1] = msg.GetButton();
            new_msg[2] = filteredAction;
            new_msg[3] = msg.GetPadNum();
            mButtonDownSwitch = false;
            TheUI->Handle(new_msg, false);
            mButtonDownSwitch = true;
            return 0;
        }
    }
    if(IsDoubleStrum(user, msg.GetButton())){
        return 1;
    }
    else return DataNode(kDataUnhandled, 0);
}

DataNode ShellInputInterceptor::OnMsg(const ButtonUpMsg& msg){
    LocalBandUser* user = BandUserMgr::GetLocalBandUser(msg.GetUser());
    if(mButtonUpSwitch){
        JoypadAction filteredAction = FilterAction(user, msg.GetAction());
        JoypadAction rawAction = msg.GetAction();
        if(filteredAction != rawAction){
            static ButtonUpMsg new_msg(nullptr, kPad_Xbox_A, kAction_Confirm, 0);
            new_msg[0] = user;
            new_msg[1] = msg.GetButton();
            new_msg[2] = filteredAction;
            new_msg[3] = msg.GetPadNum();
            mButtonUpSwitch = false;
            TheUI->Handle(new_msg, false);
            mButtonUpSwitch = true;
            return 0;
        }
    }
    return DataNode(kDataUnhandled, 0);
}

BEGIN_HANDLERS(ShellInputInterceptor)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_CHECK(0xBE)
END_HANDLERS