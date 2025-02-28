#include "meta_band/BandUI.h"
#include "BandScreen.h"
#include "SaveLoadManager.h"
#include "WaitingUserGate.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/GameMic.h"
#include "game/GameMicManager.h"
#include "meta/HAQManager.h"
#include "meta_band/BandScreen.h"
#include "meta_band/CharSync.h"
#include "meta_band/InputMgr.h"
#include "meta_band/InterstitialMgr.h"
#include "meta_band/LockStepMgr.h"
#include "meta_band/NetSync.h"
#include "meta_band/OvershellPanel.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/ShellInputInterceptor.h"
#include "meta_band/UIEventMgr.h"
#include "meta_band/UIStats.h"
#include "net/Net.h"
#include "net/NetSession.h"
#include "net_band/RockCentral.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/ContentMgr.h"
#include "os/PlatformMgr.h"
#include "rndobj/Overlay.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

CurrentScreenChangedMsg::CurrentScreenChangedMsg(Symbol s) : Message(Type(), s) {}
Symbol CurrentScreenChangedMsg::GetScreen() const { return mData->Sym(2); }

BandUI::BandUI()
    : unkd4(1), mVignetteOverlay(0), unke0(0), unke4(2), mOvershell(0), mEventDialog(0),
      mContentLoadingPanel(0), mPassiveMessagesPanel(0), mSaveLoadStatusPanel(0),
      mWaitingUserGate(0), mInterstitialMgr(0), mInputInterceptor(0),
      mAbstractWipePanel(0), unk10c(0), unk10d(0) {}

BandUI::~BandUI() {}

void BandUI::Init() {
    TheNetSession->AddSink(this, ProcessedJoinRequestMsg::Type());
    TheNetSession->AddSink(this, LocalUserLeftMsg::Type());
    TheNet.GetSessionSearcher()->AddSink(this, InviteAcceptedMsg::Type());
    ThePlatformMgr.AddSink(this, "connection_status_changed");
    ThePlatformMgr.AddSink(this, "disk_error");
    TheGameMicManager->AddSink(this, GameMicsChangedMsg::Type());
    TheSaveLoadMgr->AddSink(this);
    TheRockCentral.AddSink(this);
    ThePlatformMgr.AddSink(this, NetErrorMsg::Type());

    TheContentMgr->SetReadFailureHandler(this);
    NetSync::Init();
    UIEventMgr::Init();
    InputMgr::Init();
    LockStepMgr::Init();
    mInterstitialMgr = new InterstitialMgr();
    UIManager::Init();
    for (ObjDirItr<UIScreen> it(ObjectDir::sMainDir, true); it != nullptr; ++it) {
        BandScreen *screen = dynamic_cast<BandScreen *>(&*it);
        if (!screen) {
            const DataArray *t = it->TypeDef();
            if (!t || !strstr(t->File(), "system/run")) {
                MILO_WARN("UIScreen %s is not a BandScreen", it->Name());
            }
        }
    }
    mVignetteOverlay = RndOverlay::Find(vignette, false);
    mUIOverlay = RndOverlay::Find(ui, false);
    WaitingUserGate::Init();
    mWaitingUserGate = new WaitingUserGate();
    mInputInterceptor = new ShellInputInterceptor(TheBandUserMgr);
    TheUIStats->Init();
}

void BandUI::Terminate() {
    TheUIStats->Terminate();
    RELEASE(mInputInterceptor);
    RELEASE(mWaitingUserGate);
    UIManager::Terminate();
    RELEASE(mInterstitialMgr);
    InputMgr::Terminate();
    UIEventMgr::Terminate();
    NetSync::Terminate();
    TheNet.GetNetSession()->RemoveSink(this);
    TheNet.GetServer()->RemoveSink(this);
    ThePlatformMgr.RemoveSink(this);
    TheGameMicManager->RemoveSink(this);
    TheRockCentral.RemoveSink(this);
    ThePlatformMgr.RemoveSink(this);
}

namespace {
    UIPanel *FindPanel(const char *cc) {
        UIPanel *p = ObjectDir::sMainDir->Find<UIPanel>(cc, true);
        MILO_ASSERT(p->CheckIsLoaded(), 0xD1);
        MILO_ASSERT(p->LoadedDir(), 0xD2);
        return p;
    }
}

void BandUI::InitPanels() {
    if (!mOvershell) {
        mOvershell = dynamic_cast<OvershellPanel *>(FindPanel("overshell"));
        mEventDialog = FindPanel("event_dialog_panel");
        mContentLoadingPanel = FindPanel("content_loading_panel");
        mPassiveMessagesPanel = FindPanel("passive_messages_panel");
        mSaveLoadStatusPanel = FindPanel("saveload_status_panel");
        mAbstractWipePanel = FindPanel("abstract_wipe_panel");
        TheUIEventMgr->AddSink(this, EventDialogStartMsg::Type());
        TheUIEventMgr->AddSink(this, EventDialogDismissMsg::Type());
        mOvershell->AddSink(this, OvershellAllowingInputChangedMsg::Type());
        mOvershell->AddSink(this, OvershellActiveStatusChangedMsg::Type());
    }
}

void BandUI::Draw() {
    UIManager::Draw();
    if (mOvershell) {
        if (mOvershell->Showing()
            && (mOvershell->GetState() == UIPanel::kUp || mOvershell->Exiting())) {
            mOvershell->Draw();
        }
        if (TheUIEventMgr->HasActiveDialogEvent()) {
            mEventDialog->Draw();
        }
        if (mPassiveMessagesPanel->GetState() == UIPanel::kUp
            || mPassiveMessagesPanel->Exiting()) {
            mPassiveMessagesPanel->Draw();
        }
        if (mContentLoadingPanel->Showing()) {
            mContentLoadingPanel->Draw();
        }
        if (mSaveLoadStatusPanel->Showing()) {
            mSaveLoadStatusPanel->Draw();
        }
    }
}

void BandUI::Poll() {
    TheNetSync->Poll();
    UIManager::Poll();
    TheSessionMgr->Poll();
    if (mOvershell) {
        if (mOvershell->GetState() == UIPanel::kUp || mOvershell->Exiting()) {
            mOvershell->Poll();
        }
        mPassiveMessagesPanel->Poll();
        if (mContentLoadingPanel->Showing()) {
            mContentLoadingPanel->Poll();
        }
        if (mEventDialog->GetState() == UIPanel::kUp) {
            mEventDialog->Poll();
        }
        if (mSaveLoadStatusPanel->GetState() == UIPanel::kUp) {
            mSaveLoadStatusPanel->Poll();
        }
        mAbstractWipePanel->Poll();
    }

    // clang-format off
    // iVar3 = *(this + 0xe8);
    // if (iVar3 != 0) {
    
    //   bVar1 = false;
    //   if (((this[0x10c] != 0x0) && (*(this + 8) == 2)) || ((this[0x10d] != 0x0 && (*(this + 8) == 1) ))
    //      ) {
    //     bVar1 = true;
    //   }
    //   if (bVar1) {
    //     if (@GUARD@Poll__6BandUIFv@msg == '\0') {
    //       Symbol::Symbol(local_28,s_check_wipe_done_80b8f081);
    //       @LOCAL@Poll__6BandUIFv@msg = Message::__vt;
    //       this_00 = _PoolAlloc(0x10,0x10,1);
    //       if (this_00 != 0x0) {
    //         this_00 = DataArray::DataArray(this_00,2);
    //       }
    //       local_20.mType = kDataSymbol;
    //       local_20.mValue.symbol = local_28[0].mStr;
    //       DAT_80c8fa04 = this_00;
    //       this_01 = DataArray::Node(this_00,1);
    //       DataNode::operator_=(this_01,&local_20);
    //       if ((local_20.mType & 0x10) != 0) {
    //         sVar2 = *(local_20.mValue.symbol + 10);
    //         *(local_20.mValue.symbol + 10) = sVar2 + -1;
    //         if (sVar2 + -1 == 0) {
    //           DataArray::~DataArray(local_20.mValue.symbol);
    //         }
    //       }
    //       __register_global_object(&@LOCAL@Poll__6BandUIFv@msg,Message::~Message,@49524);
    //       @GUARD@Poll__6BandUIFv@msg = '\x01';
    //     }
    //     Hmx::Object::HandleType(&local_18,**(this + 0x108));
    //     if ((local_14 & 0x10) != 0) {
    //       sVar2 = local_18->mRefs + -1;
    //       local_18->mRefs = sVar2;
    //       if (sVar2 == 0) {
    //         DataArray::~DataArray(local_18);
    //       }
    //     }
    //   }

    //   WaitingUserGate::Poll(*(this + 0xfc));
    //   UIEventMgr::Poll(TheUIEventMgr);
    //   UpdateUIOverlay(this);

    // }
    // return;
    // clang-format on
}

bool BandUI::IsBlockingTransition() { return TheNetSync->IsBlockingTransition(); }

bool BandUI::IsTimelineResetAllowed() const {
    if (mOvershell) {
        return mOvershell->GetState() != UIPanel::kUp && !mOvershell->Exiting();
    } else
        return true;
}

DataNode BandUI::OnMsg(const ContentReadFailureMsg &msg) {
    if (!TheUIEventMgr->HasActiveDestructiveEvent()) {
        if (!streq(CurrentScreen()->Name(), "song_select_screen")) {
            static Message init("init", 0, 0);
            init[0] = msg.GetBool();
            init[1] = msg.GetStr();
            TheUIEventMgr->TriggerEvent(data_error, init);
        }
    }
    return 1;
}

void BandUI::TriggerDisbandEvent(BandUI::DisbandError err) {
    static Message init("init", -1);
    init[0] = err;
    if (unke4 == 2) {
        TheUIEventMgr->TriggerEvent(disband, init);
    } else if (unke4 == 1 || err == kKicked) {
        TheUIEventMgr->TriggerEvent(disband_error, init);
    }
}

void BandUI::GetCurrentScreenState(std::vector<UIScreen *> &screens) {
    if (PushDepth() > 0) {
        screens.push_back(BottomScreen());
    }
    UIScreen *cur = CurrentScreen();
    if (cur)
        screens.push_back(cur);
}

UIScreen *BandUI::GetJoinEntryPointForFlowType(UIFlowType ft) const {
    DataArray *flowDef = TypeDef()->FindArray("ui_flows", true)->FindArray(ft, true);
    DataArray *joinArr = flowDef->FindArray("join_entry_point", false);
    return joinArr ? joinArr->Obj<UIScreen>(1) : nullptr;
}

void BandUI::TriggerOnFinishedJoin(UIFlowType ft) {
    DataArray *flowDef = TypeDef()->FindArray("ui_flows", true)->FindArray(ft, true);
    DataArray *joinArr = flowDef->FindArray("on_finished_join", false);
    if (joinArr) {
        joinArr->ExecuteScript(1, nullptr, nullptr, 1);
    }
}

void BandUI::WipeOnNextTransition(bool b1) {
    unk10c = true;
    if (!b1)
        unk10d = true;
    unkb5 = true;
}

void BandUI::WipeInIfNecessary() {
    if (unk10c) {
        static Message wipeInMsg("wipe_in", 0);
        wipeInMsg[0] = mWentBack;
        mAbstractWipePanel->HandleType(wipeInMsg);
    }
}

void BandUI::WipeOutIfNecessary() {
    if (unk10d) {
        static Message wipeOutMsg("wipe_out", 0);
        wipeOutMsg[0] = mWentBack;
        mAbstractWipePanel->HandleType(wipeOutMsg);
    }
}

bool BandUI::WipingIn() const {
    static Message wipingInMsg("wiping_in");
    return mAbstractWipePanel->HandleType(wipingInMsg).Int();
}

bool BandUI::WipingOut() const {
    static Message wipingOutMsg("wiping_out");
    return mAbstractWipePanel->HandleType(wipingOutMsg).Int();
}

void BandUI::SendTransitionComplete(UIScreen *s1, UIScreen *s2) {
    UIManager::SendTransitionComplete(s1, s2);
    if (TheCharSync)
        TheCharSync->UpdateCharCache();
}

DataNode BandUI::OnMsg(const UITransitionCompleteMsg &msg) {
    HAQManager::Print(kHAQType_Screen);
    HAQManager::Print(kHAQType_Focus);
    Symbol s38 = gNullStr;
    UIScreen *screen = msg.GetScreen1();
    if (screen) {
        s38 = screen->Name();
        DataNode *prop = screen->Property("disable_screen_saver", false);
        ThePlatformMgr.SetScreenSaver(!prop || prop->Int() == 0);
    }
    if (TheUIEventMgr->HasActiveTransitionEvent()
        && TheUIEventMgr->IsTransitionEventFinished()) {
        TheUIEventMgr->DismissTransitionEvent();
    }
    TheSessionMgr->UpdateInvitesAllowed();
    if (mOvershell->GetState() == UIPanel::kUp) {
        mOvershell->UpdateAll();
    }
    CurrentScreenChangedMsg cscMsg(s38);
    Export(cscMsg, true);
    unk10c = false;
    unk10d = false;
    static Message blockingMsg("set_blocking", 0);
    mContentLoadingPanel->Handle(blockingMsg, true);
    unkb5 = false;
    return DataNode(kDataUnhandled, 0);
}