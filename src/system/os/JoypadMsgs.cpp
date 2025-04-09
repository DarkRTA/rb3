#include "os/JoypadMsgs.h"

ButtonDownMsg::ButtonDownMsg(LocalUser *user, JoypadButton butt, JoypadAction act, int i)
    : Message(Type(), user, butt, act, i) {}

LocalUser *ButtonDownMsg::GetUser() const { return mData->Obj<LocalUser>(2); }

ButtonUpMsg::ButtonUpMsg(LocalUser *user, JoypadButton butt, JoypadAction act, int i)
    : Message(Type(), user, butt, act, i) {}

LocalUser *ButtonUpMsg::GetUser() const { return mData->Obj<LocalUser>(2); }

JoypadConnectionMsg::JoypadConnectionMsg(LocalUser *user, bool b, int i)
    : Message(Type(), user, b, i) {}

LocalUser *JoypadConnectionMsg::GetUser() const { return mData->Obj<LocalUser>(2); }
