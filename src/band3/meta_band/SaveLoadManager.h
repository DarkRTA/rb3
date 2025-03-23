#pragma once
#include "obj/Msg.h"

class SaveLoadManager : public MsgSource {
public:
    void AutoSave();
    void Poll();
    void AutoSaveNow();

    static void Init();
};

DECLARE_MESSAGE(SaveLoadMgrStatusUpdateMsg, "saveloadmgr_status_update_msg")
END_MESSAGE

extern SaveLoadManager *TheSaveLoadMgr;