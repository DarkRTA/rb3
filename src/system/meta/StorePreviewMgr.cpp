#include "meta/StorePreviewMgr.h"
#include "utl/NetCacheMgr.h"
#include "obj/Task.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

StorePreviewMgr::StorePreviewMgr()
    : mStreamPlayer(0), mNetCacheLoader(0), mRequestedPreview(0), mIsPreviewPlaying(0) {
    mStreamPlayer = new StreamPlayer();
    MILO_ASSERT(mStreamPlayer, 0x22);
    SetName("store_preview_mgr", ObjectDir::Main());
}

StorePreviewMgr::~StorePreviewMgr() {
    RELEASE(mStreamPlayer);
    if (mNetCacheLoader) {
        TheNetCacheMgr->DeleteNetCacheLoader(mNetCacheLoader);
        mNetCacheLoader = 0;
    }
}

void StorePreviewMgr::ClearCurrentPreview() {
    if (mNetCacheLoader) {
        TheNetCacheMgr->DeleteNetCacheLoader(mNetCacheLoader);
        mNetCacheLoader = 0;
    }
    if (!mStrPathCur.empty()) {
        mStrPathCur = gNullStr;
        PlayCurrentPreview();
    }
}

void StorePreviewMgr::SetCurrentPreviewFile(const String &str) {
    if (mStrPathCur == str)
        return;
    mStrPathCur = str;
    mRequestedPreview = false;
    PlayCurrentPreview();
}

void StorePreviewMgr::DownloadPreviewFile(const String &str) { AddToDownloadQueue(str); }

bool StorePreviewMgr::IsDownloadingFile(const String &str) {
    if (mNetCacheLoader) {
        if (str == mNetCacheLoader->GetRemotePath()) {
            return true;
        }
    }
    return mDownloadQueue.end()
        != std::find(mDownloadQueue.begin(), mDownloadQueue.end(), str);
}

void StorePreviewMgr::Poll() {
    MILO_ASSERT(mStreamPlayer, 0x89);
    mStreamPlayer->Poll();
    if (mRequestedPreview)
        PlayCurrentPreview();
    if (mNetCacheLoader) {
        static PreviewDownloadCompleteMsg msg(true);
        if (mNetCacheLoader->IsLoaded()) {
            TheNetCacheMgr->DeleteNetCacheLoader(mNetCacheLoader);
            mNetCacheLoader = nullptr;
            mRequestedPreview = false;
            PlayCurrentPreview();
            msg[0] = true;
            MsgSource::Handle(msg, false);
        } else if (mNetCacheLoader->HasFailed()) {
            TheNetCacheMgr->DeleteNetCacheLoader(mNetCacheLoader);
            mNetCacheLoader = nullptr;
            msg[0] = false;
            MsgSource::Handle(msg, false);
            TheUI.ShowNetError();
        }
    }
    while (!mDownloadQueue.empty()) {
        if (!TheNetCacheMgr->IsLocalFile(mDownloadQueue.front().c_str()))
            break;
        mDownloadQueue.pop_front();
    }
    if (!mNetCacheLoader && !mDownloadQueue.empty()) {
        mStrPathCur = mDownloadQueue.front().c_str();
        MILO_ASSERT(!TheNetCacheMgr->IsLocalFile(mStrPathCur.c_str()), 0xD1);
        mNetCacheLoader =
            TheNetCacheMgr->AddNetCacheLoader(mStrPathCur.c_str(), (NetLoaderPos)0);
        mDownloadQueue.pop_front();
    }
}

bool StorePreviewMgr::AllowPreviewDownload(const String &str) {
    if (mNetCacheLoader) {
        if (str == mNetCacheLoader->GetRemotePath()) {
            return false;
        }
    }
    if (TheNetCacheMgr->IsLocalFile(str.c_str()))
        return false;
    else
        return std::find(mDownloadQueue.begin(), mDownloadQueue.end(), str)
            == mDownloadQueue.end();
}

void StorePreviewMgr::PlayCurrentPreview() {
    MILO_ASSERT(mStreamPlayer, 0xFE);
    if (mStrPathCur.empty() || !TheNetCacheMgr->IsLocalFile(mStrPathCur.c_str())) {
        mStreamPlayer->StopPlaying();
    } else {
        if (mIsPreviewPlaying) {
            mIsPreviewPlaying = false;
            mStreamPlayer->StopPlaying();
        }
        if (!mRequestedPreview) {
            mRequestedPreview = true;
            mPreviewRequestedSeconds = TheTaskMgr.UISeconds();
        } else if (TheTaskMgr.UISeconds() - mPreviewRequestedSeconds < 1.5f)
            return;
        mRequestedPreview = false;
        String str(mStrPathCur.c_str());
        int len = str.length();
        if (str.find(".mogg", len - 5) != String::npos) {
            str.erase(len - 5);
        } else if (str.find(".bik", len - 4) != String::npos) {
            str.erase(len - 4);
        }
        mStreamPlayer->PlayFile(str.c_str(), -3.0f, 0, true);
    }
}

void StorePreviewMgr::AddToDownloadQueue(const String &str) {
    if (mNetCacheLoader) {
        if (str == mNetCacheLoader->GetRemotePath()) {
            return;
        }
    }
    if (!TheNetCacheMgr->IsLocalFile(str.c_str())) {
        if (std::find(mDownloadQueue.begin(), mDownloadQueue.end(), str)
            == mDownloadQueue.end()) {
            mDownloadQueue.push_back(str);
        }
    }
}

BEGIN_HANDLERS(StorePreviewMgr)
    HANDLE_ACTION(clear_current_preview, ClearCurrentPreview())
    HANDLE_ACTION(set_current_preview_file, SetCurrentPreviewFile(_msg->Str(2)))
    HANDLE_ACTION(download_preview_file, DownloadPreviewFile(_msg->Str(2)))
    HANDLE_EXPR(is_downloading_file, IsDownloadingFile(_msg->Str(2)))
    HANDLE_EXPR(allow_preview_download, AllowPreviewDownload(_msg->Str(2)))
    HANDLE_CHECK(0x172)
END_HANDLERS