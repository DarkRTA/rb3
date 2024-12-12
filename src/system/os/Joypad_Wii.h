#ifndef OS_JOYPAD_WII_H
#define OS_JOYPAD_WII_H
#include "os/Joypad.h"

int GetWiiJoypadType(int);
int JoypadPollWiiRemotes();
void JoypadWiiOnUserLeft(int, bool);
int GetWiiJoypadDisconnectType(int, JoypadType*, JoypadType*); // change ret type
void JoypadWiiInitCommon(bool);

#endif
