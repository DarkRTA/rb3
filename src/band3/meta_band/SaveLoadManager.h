#pragma once
#include "obj/Msg.h"

class SaveLoadManager : public MsgSource {
public:
    void AutoSave();
    void Poll();
    void AutoSaveNow();

    static void Init();
};

extern SaveLoadManager *TheSaveLoadMgr;