#pragma once
#include "utl/Symbol.h"

class DataArray;
class LocalUser;

void EnableKeyCheats(bool);
bool GetEnabledKeyCheats();
void CallQuickCheat(DataArray*, LocalUser*);
bool CheatsInitialized();
Symbol GetCheatMode();
void AppendCheatsLog(char*);
