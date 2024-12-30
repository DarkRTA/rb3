#pragma once
#include "os/Joypad.h"

int GetWiiJoypadType(int);
int JoypadPollWiiRemotes();
void JoypadWiiOnUserLeft(int, bool);
int GetWiiJoypadDisconnectType(int, JoypadType*, JoypadType*); // change ret type
void JoypadWiiInitCommon(bool);
