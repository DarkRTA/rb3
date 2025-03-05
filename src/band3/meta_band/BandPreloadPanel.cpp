#include "meta_band/BandPreloadPanel.h"
#include "meta/PreloadPanel.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/LockStepMgr.h"
#include "meta_band/SessionMgr.h"
#include "obj/ObjMacros.h"

BandPreloadPanel::BandPreloadPanel() {
    static int preloadIndex;
    mLockInProgress = false;
    const char *lockName = MakeString("preload_lock%i", preloadIndex++);
    mPreloadLock = new LockStepMgr(lockName, this);
}

BandPreloadPanel::~BandPreloadPanel() { delete mPreloadLock; }

void BandPreloadPanel::Load() {
    PreloadPanel::Load();
    mLockInProgress = true;
    if (TheSessionMgr->IsLeaderLocal()) {
        mPreloadLock->StartLock();
    }
}

void BandPreloadPanel::PollForLoading() {
    PreloadPanel::PollForLoading();
    if (PreloadPanel::IsLoaded() && mPreloadLock->InLock()
        && !mPreloadLock->HasResponded()) {
        bool success = mPreloadResult == kPreloadSuccess;
        if (mPreloadResult == kPreloadSuccess && !TheSessionMgr->IsLocal()) {
            if (TheSongMgr.IsDemo(TheSongMgr.GetSongIDFromShortName(CurrentSong(), true)
                )) {
                success = false;
            }
        }
        mPreloadLock->RespondToLock(success);
    }
}

bool BandPreloadPanel::IsLoaded() const {
    return !PreloadPanel::IsLoaded() ? false : !mLockInProgress;
}

DataNode BandPreloadPanel::OnMsg(const LockStepStartMsg &) { return 1; }

DataNode BandPreloadPanel::OnMsg(const LockStepCompleteMsg &msg) {
    if (!msg->Int(2) && mPreloadResult == kPreloadSuccess) {
        mPreloadResult = kPreloadFailure;
    }
    mLockInProgress = false;
    return 1;
}

BEGIN_HANDLERS(BandPreloadPanel)
    HANDLE_MESSAGE(LockStepStartMsg)
    HANDLE_MESSAGE(LockStepCompleteMsg)
    HANDLE_SUPERCLASS(PreloadPanel)
    HANDLE_CHECK(0x62)
END_HANDLERS