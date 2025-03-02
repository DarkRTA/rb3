#pragma once
#include "obj/Msg.h"

class SaveLoadManager : public MsgSource {
public:
    void AutoSave();
};

extern SaveLoadManager *TheSaveLoadMgr;