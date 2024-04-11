#ifndef OS_JOYPADMSGS_H
#define OS_JOYPADMSGS_H
#include "obj/Msg.h"
#include "os/User.h"
#include "os/Joypad.h"

BEGIN_MESSAGE(JoypadConnectionMsg, "joypad_connect", LocalUser*, bool, int);
    LocalUser* GetUser() const;
END_MESSAGE;

BEGIN_MESSAGE(ButtonUpMsg, "button_up", LocalUser*, JoypadButton, JoypadAction, int);
    MESSAGE_ARRAY_CTOR(ButtonUpMsg)
    LocalUser* GetUser() const;
    JoypadButton GetButton() const { return (JoypadButton)mData->Int(3); }
    JoypadAction GetAction() const { return (JoypadAction)mData->Int(4); }
    int GetPadNum() const { return mData->Int(5); }
END_MESSAGE;

BEGIN_MESSAGE(ButtonDownMsg, "button_down", LocalUser*, JoypadButton, JoypadAction, int);
    MESSAGE_ARRAY_CTOR(ButtonDownMsg)
    LocalUser* GetUser() const;
    JoypadButton GetButton() const { return (JoypadButton)mData->Int(3); }
    JoypadAction GetAction() const { return (JoypadAction)mData->Int(4); }
    int GetPadNum() const { return mData->Int(5); }
END_MESSAGE;

#endif
