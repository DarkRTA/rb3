#pragma once
#include "OvershellPanel.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/NetGameMsgs.h"
#include "meta_band/BandMachine.h"
#include "meta_band/BandMachineMgr.h"
#include "meta_band/BandProfile.h"
#include "meta_band/LockStepMgr.h"
#include "meta_band/Matchmaker.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/SessionMgr.h"
#include "net/NetSession.h"
#include "net_band/DataResults.h"
#include "net_band/RockCentralMsgs.h"
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
        kMainHubOverride_Waiting = 1,
        kMainHubOverride_Finding = 2,
        kMainHubOverride_ChooseBand = 3
    };

    MainHubPanel();
    OBJ_CLASSNAME(MainHubPanel);
    OBJ_SET_TYPE(MainHubPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~MainHubPanel();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void Unload();

    void RefreshData();
    void SetMainHubOverride(MainHubOverride);
    void UpdateStateView(MainHubState, MainHubState, MainHubOverride, MainHubOverride);
    void PrepareProfilesAndMessages();
    void UpdateHeader();
    void CycleNextMessage();
    void ReloadMessages();
    void UpdateMessageProvider();
    bool CheckProfileForTicker();
    void UpdatePoolInfo();
    void SetMainHubState(MainHubState);
    void CheckStartWaitingLock();
    void StartFinding();
    void AdvanceFromFinding();
    void AdvanceAll(NetUIState);
    void SetMotd(const char *);
    const char *GetMotd();
    void SetDLCMotd(const char *);
    const char *GetDLCMotd();
    MainHubMessageProvider *GetMessageProvider() { return mMessageProvider; }
    MainHubState GetMainHubState() const { return mHubState; }
    MainHubOverride GetMainHubOverride() { return mHubOverride; }

    DataNode OnMsg(const OvershellOverrideEndedMsg &);
    DataNode OnMsg(const SessionDisconnectedMsg &);
    DataNode OnMsg(const PrimaryProfileChangedMsg &);
    DataNode OnMsg(const ProcessedJoinRequestMsg &);
    DataNode OnMsg(const NewRemoteMachineMsg &);
    DataNode OnMsg(const RemoteMachineLeftMsg &);
    DataNode OnMsg(const SessionMgrUpdatedMsg &);
    DataNode OnMsg(const RemoteMachineUpdatedMsg &);
    DataNode OnMsg(const MatchmakerChangedMsg &);
    DataNode OnMsg(const LockStepStartMsg &);
    DataNode OnMsg(const LockStepCompleteMsg &);
    DataNode OnMsg(const ReleasingLockStepMsg &);
    DataNode OnMsg(const RockCentralOpCompleteMsg &);
    DataNode OnMsg(const UserLoginMsg &);
    NEW_OBJ(MainHubPanel);
    static void Init() { REGISTER_OBJ_FACTORY(MainHubPanel); }

    MainHubState mHubState; // 0x38
    MainHubOverride mHubOverride; // 0x3c
    MainHubMessageProvider *mMessageProvider; // 0x40
    int mCurrentMessage; // 0x44
    float mMessageRotationMs; // 0x48
    Timer mMessageTimer; // 0x50
    BandMachineMgr *mMachineMgr; // 0x80
    LockStepMgr *mWaitingStateLock; // 0x84
    String mMotd; // 0x88
    String unk94; // 0x94
    DataResultList mLabelUpdateResults; // 0xa0
    bool unkb8; // 0xb8
    BandProfile *unkbc; // 0xbc
    ScoreType unkc0; // 0xc0
};