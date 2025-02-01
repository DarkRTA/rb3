#ifndef UI_UTL_H
#define UI_UTL_H
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"

int ScrollDirection(const ButtonDownMsg &, Symbol, bool, int);
int PageDirection(JoypadAction);
bool IsNavAction(JoypadAction);

#endif