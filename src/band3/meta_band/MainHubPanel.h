#pragma once
#include "meta_band/BandMachineMgr.h"
#include "meta_band/LockStepMgr.h"
#include "net_band/DataResults.h"
#include "os/Timer.h"
#include "ui/UIPanel.h"
#include "utl/Str.h"

class MainHubMessageProvider;

class MainHubPanel : public UIPanel {
public:
    enum MainHubState {
        kMainHubState_None = 0,
        kMainHubState_Main = 1,
        kMainHubState_PlayNow = 2,
        kMainHubState_Quickplay = 3,
        kMainHubState_Tour = 4,
        kMainHubState_Training = 5
    };

    enum MainHubOverride {
        kMainHubOverride_None = 0,
        kMainHubOverride_ChooseBand = 1,
        kMainHubOverride_Waiting = 2,
        kMainHubOverride_Finding = 3
    };

    MainHubPanel();
    OBJ_CLASSNAME(MainHubPanel);
    OBJ_SET_TYPE(MainHubPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~MainHubPanel();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void Unload();

    MainHubState mHubState; // 0x38
    MainHubOverride mHubOverride; // 0x3c
    MainHubMessageProvider* mMessageProvider; // 0x40
    int mCurrentMessage; // 0x44
    float mMessageRotationMs; // 0x48
    Timer mMessageTimer; // 0x50
    BandMachineMgr* mMachineMgr; // 0x80
    LockStepMgr* mWaitingStateLock; // 0x84
    String mMotd; // 0x88
    String unk94; // 0x94
    DataResultList mLabelUpdateResults; // 0xa0
    bool unkb8; // 0xb8
    int unkbc; // 0xbc
    int unkc0; // 0xc0
};