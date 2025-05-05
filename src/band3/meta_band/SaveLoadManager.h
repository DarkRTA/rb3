#pragma once
#include "game/BandUser.h"
#include "meta/Profile.h"
#include "net_band/RockCentralMsgs.h"
#include "obj/Msg.h"
#include "os/Memcard.h"

class SaveLoadManager : public MsgSource {
public:
    SaveLoadManager();
    virtual ~SaveLoadManager();
    void AutoSave();
    void AutoLoad();
    void EnableAutosave(LocalBandUser *);
    void DisableAutosave(LocalBandUser *);
    void ManualSave(LocalBandUser *);
    void ManualDelete();
    bool IsAutosaveEnabled(LocalBandUser *);
    void GetDialogMsg();
    Symbol GetDialogOpt1();
    Symbol GetDialogOpt2();
    Symbol GetDialogOpt3();
    int GetDialogFocusOption();
    bool IsInititalLoadDone();
    bool IsIdle();
    void Activate();
    void PrintoutSaveSizeInfo();
    void Poll();
    void AutoSaveNow();
    virtual DataNode Handle(DataArray *, bool);
    void HandleEventResponseStart(int i1);
    void HandleEventResponse(LocalUser *, int i1);

    static void Init();

    DataNode OnMsg(const ProfileSwappedMsg &);
    DataNode OnMsg(const DeviceChosenMsg &);
    DataNode OnMsg(const NoDeviceChosenMsg &);
    DataNode OnMsg(const MCResultMsg &);
    DataNode OnMsg(const RockCentralOpCompleteMsg &);
    DataNode OnMsg(const SigninChangedMsg &);
};

DECLARE_MESSAGE(SaveLoadMgrStatusUpdateMsg, "saveloadmgr_status_update_msg")
END_MESSAGE

extern SaveLoadManager *TheSaveLoadMgr;