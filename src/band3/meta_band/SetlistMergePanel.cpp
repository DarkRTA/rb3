#include "meta_band/SetlistMergePanel.h"
#include "decomp.h"
#include "game/BandUserMgr.h"
#include "game/NetGameMsgs.h"
#include "meta_band/BandMachine.h"
#include "meta_band/LockMessages.h"
#include "meta_band/LockStepMgr.h"
#include "meta_band/MusicLibrary.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/Utl.h"
#include "net/NetSession.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/Messages2.h"
#include "utl/Symbol.h"
#include "utl/Symbols2.h"

SetlistMergePanel::SetlistMergePanel() : mSetlistMergeLock(0) {
    mSetlistMergeLock = new LockStepMgr("setlist_merge_lock", this);
}

SetlistMergePanel::~SetlistMergePanel() { delete mSetlistMergeLock; }

void SetlistMergePanel::Enter() {
    UIPanel::Enter();
    TheSessionMgr->GetMachineMgr()->AddSink(this);
}

void SetlistMergePanel::Exit() {
    TheSessionMgr->GetMachineMgr()->RemoveSink(this);
    UIPanel::Exit();
}

DataNode SetlistMergePanel::OnMsg(const UITransitionCompleteMsg &) {
    SetLocalsMerging(true);
    UpdateProgressInfo();
    return DataNode(kDataUnhandled, 0);
}

void SetlistMergePanel::StartSetlistMerge() {
    MILO_ASSERT(IsLeaderLocal(), 0x40);
    mSetlists.clear();
    BasicStartLockMsg msg;
    mSetlistMergeLock->StartLock(msg);
}

void SetlistMergePanel::SubmitSetlist() {
    MILO_ASSERT(GetState() == kUp, 0x49);
    MILO_ASSERT(mSetlistMergeLock->InLock(), 0x4A);
    std::vector<int> setlist = TheMusicLibrary->GetSetlist();
    if (IsLeaderLocal()) {
        HandleSetlistSubmission(setlist, TheBandUserMgr->GetNumLocalPlayers());
    } else {
        if (setlist.size() > 75)
            setlist.resize(75);
        SetlistSubmissionMsg msg(setlist, TheBandUserMgr->GetNumLocalPlayers());
        TheSessionMgr->SendMsg(TheSessionMgr->GetLeaderUser(), msg, kReliable);
    }
}

void SetlistMergePanel::HandleSetlistSubmission(
    const std::vector<int> &setlist, int numplayers
) {
    MILO_ASSERT(IsLeaderLocal(), 0x61);
    MILO_ASSERT(mSetlistMergeLock->InLock(), 0x62);
    mSetlists.push_back(std::make_pair(setlist, numplayers));
}

UNPOOL_DATA
void SetlistMergePanel::UpdateProgressInfo() {
    static Message setMsg("set_machine_info", 0, gNullStr, 0, 0);
    static Message hideMsg("hide_machine_info", 0);

    BandMachineMgr *mgr = TheSessionMgr->GetMachineMgr();
    std::vector<BandMachine *> machines;
    mgr->GetMachines(machines);
    bool b2 = true;
    int i4 = 0;
    FOREACH (it, machines) {
        int param = (*it)->GetNetUIStateParam();
        bool gt1 = param > 0;
        if (gt1 == 0) {
            b2 = false;
        }
        setMsg[0] = i4;
        setMsg[1] = "";
        setMsg[2] = gt1;
        setMsg[3] = Abs(param);
        HandleType(setMsg);
        i4++;
    }

    for (; i4 < 4; i4++) {
        hideMsg[0] = i4;
        HandleType(hideMsg);
    }

    if (IsLeaderLocal() && b2) {
        StartSetlistMerge();
    }
}
END_UNPOOL_DATA

DECOMP_FORCEACTIVE(SetlistMergePanel, "setlist_merge_screen")

void SetlistMergePanel::SetLocalsMerging(bool b1) {
    int size = TheMusicLibrary->SetlistSize();
    if (!b1)
        size = -size;
    TheSessionMgr->GetMachineMgr()->GetLocalMachine()->SetNetUIStateParam(size);
}

int SetlistMergePanel::IntToSetlistIndex(int i, int setlistSize) {
    MILO_ASSERT_RANGE(i, 0, 100, 0xA9);
    MILO_ASSERT_RANGE_EQ(setlistSize, 1, 100, 0xB8);

    int index = -1;
    for (int i3 = 0; i3 < setlistSize; i3++) {
        index = i3;
        if (i != (int)std::floor(100.0f / setlistSize) * i3)
            break;
    }

    MILO_ASSERT(index < setlistSize, 0xB8);
    MILO_ASSERT(i != 0 || index == 0, 0xB9);
    return index;
}

DataNode SetlistMergePanel::OnMsg(const ReleasingLockStepMsg &) {}

void SetlistMergePanel::SendSongsToMetaPerformer(const std::vector<int> &) {}

DataNode SetlistMergePanel::OnMsg(const LockStepStartMsg &) {
    UIScreen *screen = ObjectDir::Main()->Find<UIScreen>("setlist_merge_screen", true);
    if (!TheUI.InTransition() && TheUI.CurrentScreen() == screen) {
        SubmitSetlist();
        mSetlistMergeLock->RespondToLock(true);
    } else
        mSetlistMergeLock->RespondToLock(false);
    return 1;
}

DataNode SetlistMergePanel::OnMsg(const LockStepCompleteMsg &msg) {
    if (msg->Int(2)) {
        HandleType(move_on_msg);
    }
    return 1;
}

DataNode SetlistMergePanel::OnMsg(const RemoteMachineUpdatedMsg &msg) {
    if (msg.GetMask() & 1) {
        UpdateProgressInfo();
    }
    return 1;
}

DataNode SetlistMergePanel::OnMsg(const RemoteMachineLeftMsg &) {
    UpdateProgressInfo();
    return 1;
}

DataNode SetlistMergePanel::OnMsg(const NewRemoteMachineMsg &) {
    UpdateProgressInfo();
    return 1;
}

BEGIN_HANDLERS(SetlistMergePanel)
    HANDLE_ACTION(cancel_merge, SetLocalsMerging(false))
    HANDLE_MESSAGE(UITransitionCompleteMsg)
    HANDLE_MESSAGE(LockStepStartMsg)
    HANDLE_MESSAGE(ReleasingLockStepMsg)
    HANDLE_MESSAGE(LockStepCompleteMsg)
    HANDLE_MESSAGE(RemoteMachineUpdatedMsg)
    HANDLE_MESSAGE(NewRemoteMachineMsg)
    HANDLE_MESSAGE(RemoteMachineLeftMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x16C)
END_HANDLERS