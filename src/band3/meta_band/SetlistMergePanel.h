#pragma once
#include "meta_band/BandMachine.h"
#include "meta_band/LockStepMgr.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"

class SetlistMergePanel : public UIPanel {
public:
    SetlistMergePanel();
    OBJ_CLASSNAME(SetlistMergePanel);
    OBJ_SET_TYPE(SetlistMergePanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~SetlistMergePanel();
    virtual void Enter();
    virtual void Exit();

    void SetLocalsMerging(bool);
    void UpdateProgressInfo();
    void StartSetlistMerge();
    void SubmitSetlist();
    void HandleSetlistSubmission(const std::vector<int> &, int);
    void SendSongsToMetaPerformer(const std::vector<int> &);

    static int IntToSetlistIndex(int, int);

    DataNode OnMsg(const UITransitionCompleteMsg &);
    DataNode OnMsg(const LockStepStartMsg &);
    DataNode OnMsg(const ReleasingLockStepMsg &);
    DataNode OnMsg(const LockStepCompleteMsg &);
    DataNode OnMsg(const RemoteMachineUpdatedMsg &);
    DataNode OnMsg(const RemoteMachineLeftMsg &);
    DataNode OnMsg(const NewRemoteMachineMsg &);

    std::vector<std::pair<std::vector<int>, int> > mSetlists; // 0x38
    LockStepMgr *mSetlistMergeLock; // 0x40
};