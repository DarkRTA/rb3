#include "meta_band/ContentDeletePanel.h"
#include "meta_band/BandSongMgr.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/ContentMgr.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

ContentDeletePanel::ContentDeletePanel()
    : unk3c(0), mContent(0), unk44(0), unk45(0), mDeleteFailed(0) {
    mContentNames[0] = gNullStr;
    mContentNames[1] = gNullStr;
}

void ContentDeletePanel::Enter() {
    UIPanel::Enter();
    unk3c = false;
    unk45 = false;
    mDeleteFailed = false;
    TheContentMgr->RegisterCallback(this, false);
}

DataNode ContentDeletePanel::OnMsg(const UITransitionCompleteMsg &msg) {
    const char *name = TheSongMgr.ContentName(mContent);
    bool deleted;
    if (name) {
        mContentNames[0] = name;
        deleted = TheContentMgr->DeleteContent(mContentNames[0].c_str());
        if (!mDeleteFailed) {
            TheSongMgr.ClearFromCache(mContentNames[0].c_str());
        }
    }
    if (!mDeleteFailed) {
        name = TheSongMgr.mUpgradeMgr->ContentName(mContent);
        if (name) {
            mContentNames[1] = name;
            TheContentMgr->DeleteContent(mContentNames[1].c_str());
            if (!mDeleteFailed) {
                Symbol s = mContentNames[1].c_str();
                TheSongMgr.mUpgradeMgr->ClearFromCache(s);
            }
        }
    }
    if (deleted)
        mDeleteFailed = true;
    return DataNode(kDataUnhandled, 0);
}

void ContentDeletePanel::Poll() {
    UIPanel::Poll();
    if (!unk3c && !TheUI.InTransition()) {
        bool handle = mDeleteFailed;
        if (!handle) {
            handle = TheContentMgr->IsDeleteDone(mContentNames[0].c_str());
            if (!mContentNames[1].empty()) {
                bool old = handle;
                handle = false;
                if (old) {
                    if (TheContentMgr->IsDeleteDone(mContentNames[1].c_str()))
                        handle = true;
                }
            }
        }
        if (handle) {
            unk3c = true;
            if (unk44) {
                TheContentMgr->StartRefresh();
                unk45 = true;
                HandleType(refresh_started_msg);
            } else {
                HandleType(refresh_done_msg);
            }
        }
    } else if (unk45 && TheContentMgr->RefreshDone()) {
        unk45 = false;
        HandleType(refresh_done_msg);
    }
}

void ContentDeletePanel::Exit() { TheContentMgr->UnregisterCallback(this, true); }

bool ContentDeletePanel::Exiting() const {
    return UIPanel::Exiting() || !unk3c || !TheContentMgr->RefreshDone();
}

void ContentDeletePanel::SetupDeletion(int i, bool b) {
    mContent = i;
    unk44 = b;
}

void ContentDeletePanel::ContentFailed(const char *cc) {
    if (!unk3c)
        mDeleteFailed = true;
}

BEGIN_HANDLERS(ContentDeletePanel)
    HANDLE_ACTION(setup_deletion, SetupDeletion(_msg->Int(2), _msg->Int(3)))
    HANDLE_EXPR(delete_failed, mDeleteFailed)
    HANDLE_MESSAGE(UITransitionCompleteMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xA2)
END_HANDLERS

BEGIN_PROPSYNCS(ContentDeletePanel)
    SYNC_PROP(content, mContent)
END_PROPSYNCS