#pragma once
#include "meta_band/LockStepMgr.h"
#include "meta_band/SessionMgr.h"
#include "net/NetSession.h"
#include "ui/UIPanel.h"

class SyncGameStartPanel : public UIPanel {
public:
    enum State {
        kWaitingForSessionStart = 3,
        kStartingSession = 4
    };
    SyncGameStartPanel();
    OBJ_CLASSNAME(SyncGameStartPanel);
    OBJ_SET_TYPE(SyncGameStartPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~SyncGameStartPanel();
    virtual void Load();
    virtual bool IsLoaded() const;
    virtual void PollForLoading();

    void PollIsSynced();
    void StartSync(bool);
    bool CheckIsSynced();
    void SetExternalBlock(bool);

    DataNode OnMsg(const SyncStartGameMsg &);
    DataNode OnMsg(const SessionDisconnectedMsg &);
    DataNode OnMsg(const LockStepStartMsg &);
    DataNode OnMsg(const LockStepCompleteMsg &);

    int mState; // 0x38 - state - should be an anonymous enum
    LockStepMgr mLockStepMgr; // 0x3c
    bool mExternalBlock; // 0x6c
    Timer mStartGameResendTimer; // 0x70
};