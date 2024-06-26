#ifndef UTL_CHEATS_H
#define UTL_CHEATS_H

class DataArray;
class LocalUser;

void EnableKeyCheats(bool);
bool GetEnabledKeyCheats();
void CallQuickCheat(DataArray*, LocalUser*);

void AppendCheatsLog(char*);

#endif // UTL_CHEATS_H
