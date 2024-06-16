#ifndef UI_UTL_H
#define UI_UTL_H
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"

JoypadAction ScrollDirection(const ButtonDownMsg&, Symbol, bool, int);
bool IsNavAction(JoypadAction);

#endif