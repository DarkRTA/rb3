#include "game/SyncGameStartPanel.h"
#include "game/Game.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/Utl.h"
#include "net/NetSession.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "ui/UIPanel.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

SyncGameStartPanel::SyncGameStartPanel()
    : mState(5), mLockStepMgr("sync_game_start", this), mExternalBlock(0) {
    TheNetSession->AddSink(this);
}

SyncGameStartPanel::~SyncGameStartPanel() { TheNetSession->RemoveSink(this); }

void SyncGameStartPanel::Load() {
    UIPanel::Load();
    StartSync(false);
}

void SyncGameStartPanel::PollForLoading() { PollIsSynced(); }

bool SyncGameStartPanel::IsLoaded() const {
    return UIPanel::IsLoaded() ? mState == 5 : false;
}

void SyncGameStartPanel::StartSync(bool b1) {
    mExternalBlock = b1;
    mState = 0;
}

bool SyncGameStartPanel::CheckIsSynced() {
    PollIsSynced();
    return mState == 5;
}

void SyncGameStartPanel::PollIsSynced() {
    int state = mState;
    if (state - 3U > 2) {
        switch (state) {
        case 0:
            mState = 1;
            if (IsLeaderLocal()) {
                mLockStepMgr.StartLock();
            }
            break;
        case 1:
            if (TheGame && !TheGame->IsWaiting()) {
                mState = 2;
            }
            break;
        case 2:
            if (!mExternalBlock && mLockStepMgr.InLock()) {
                mState = 3;
                mLockStepMgr.RespondToLock(true);
            }
            break;
        default:
            MILO_FAIL("Invalid state in SyncGameStartPanel\n");
            break;
        }
    }
}

void SyncGameStartPanel::SetExternalBlock(bool b1) { mExternalBlock = b1; }

DataNode SyncGameStartPanel::OnMsg(const SyncStartGameMsg &msg) {
    if (IsLeaderLocal()) {
        MILO_ASSERT(mState == kStartingSession, 0x77);
    } else
        MILO_ASSERT(mState == kWaitingForSessionStart, 0x79);
    mState = 5;
    return 1;
}

DataNode SyncGameStartPanel::OnMsg(const SessionDisconnectedMsg &msg) {
    if (mState - 1U <= 1 && !mLockStepMgr.InLock()) {
        mLockStepMgr.StartLock();
    }
    if (mState == kWaitingForSessionStart && !mLockStepMgr.InLock()) {
        mState = kStartingSession;
        if (!TheNetSession->IsStartingGame()) {
            TheNetSession->StartGame();
        }
    }
    return 1;
}

DataNode SyncGameStartPanel::OnMsg(const LockStepStartMsg &msg) { return 1; }

DataNode SyncGameStartPanel::OnMsg(const LockStepCompleteMsg &msg) {
    if (IsLeaderLocal()) {
        MILO_ASSERT(mState == kWaitingForSessionStart, 0xA2);
        mState = kStartingSession;
        TheNetSession->StartGame();
    }
    return 1;
}

BEGIN_HANDLERS(SyncGameStartPanel)
    HANDLE_ACTION(start_sync, StartSync(false))
    HANDLE_ACTION(start_sync_with_external_block, StartSync(true))
    HANDLE_ACTION(clear_external_block, SetExternalBlock(false))
    HANDLE_EXPR(check_is_synced, CheckIsSynced())
    HANDLE_MESSAGE(SyncStartGameMsg)
    HANDLE_MESSAGE(SessionDisconnectedMsg)
    HANDLE_MESSAGE(LockStepStartMsg)
    HANDLE_MESSAGE(LockStepCompleteMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xBB)
END_HANDLERS