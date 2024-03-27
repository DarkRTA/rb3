#ifndef OS_JOYPADMSGS_H
#define OS_JOYPADMSGS_H
#include "obj/Msg.h"
#include "os/User.h"
#include "os/Joypad.h"

BEGIN_MESSAGE(JoypadConnectionMsg, "joypad_connect", LocalUser*, bool, int);
    LocalUser* GetUser() const;
END_MESSAGE;

BEGIN_MESSAGE(ButtonUpMsg, "button_up", LocalUser*, JoypadButton, JoypadAction, int);
    LocalUser* GetUser() const;
END_MESSAGE;

BEGIN_MESSAGE(ButtonDownMsg, "button_down", LocalUser*, JoypadButton, JoypadAction, int);
    ButtonDownMsg(DataArray* da) : Message(da) {}
    LocalUser* GetUser() const;
END_MESSAGE;

#endif
