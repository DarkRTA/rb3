#include "meta_band/BandUI.h"
#include "BandScreen.h"
#include "MetaNetMsgs.h"
#include "SaveLoadManager.h"
#include "WaitingUserGate.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/GameMic.h"
#include "game/GameMicManager.h"
#include "game/GameMode.h"
#include "game/UITransitionNetMsgs.h"
#include "meta/ConnectionStatusPanel.h"
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
#include "net/Server.h"
#include "net_band/RockCentral.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/ContentMgr.h"
#include "os/JoypadMsgs.h"
#include "os/PlatformMgr.h"
#include "rndobj/Overlay.h"
#include "synth/MicManagerInterface.h"
#include "ui/UI.h"
#include "ui/UIComponent.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

MicClientID sNullMicClientID;
BandUI TheBandUI;
UIManager *TheUI = &TheBandUI;

CurrentScreenChangedMsg::CurrentScreenChangedMsg(Symbol s) : Message(Type(), s) {}
Symbol CurrentScreenChangedMsg::GetScreen() const { return mData->Sym(2); }

BandUI::BandUI()
    : unkd4(1), mVignetteOverlay(0), mInviteAccepted(0), mDisbandStatus(kDisbandsEnabled),
      mOvershell(0), mEventDialog(0), mContentLoadingPanel(0), mPassiveMessagesPanel(0),
      mSaveLoadStatusPanel(0), mWaitingUserGate(0), mInterstitialMgr(0),
      mInputInterceptor(0), mAbstractWipePanel(0), unk10c(0), unk10d(0) {}

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
    TheNet.GetSessionSearcher()->RemoveSink(this);
    ThePlatformMgr.RemoveSink(this);
    TheGameMicManager->RemoveSink(this);
    TheSaveLoadMgr->RemoveSink(this);
    TheRockCentral.RemoveSink(this);
    if (mOvershell) {
        if (TheUIEventMgr) {
            TheUIEventMgr->RemoveSink(this);
        }
        mOvershell->RemoveSink(this);
    }
    ThePlatformMgr.RemoveSink(this, NetErrorMsg::Type());
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

        // this part here is inlined, but idk what to name the func
        bool b1 = false;
        if ((unk10c && mTransitionState == kTransitionFrom)
            || (unk10d && mTransitionState == kTransitionTo))
            b1 = true;

        if (b1) {
            static Message msg("check_wipe_done");
            mAbstractWipePanel->HandleType(msg);
        }
        mWaitingUserGate->Poll();
        TheUIEventMgr->Poll();
        UpdateUIOverlay();
    }
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
    if (mDisbandStatus == kDisbandsEnabled) {
        TheUIEventMgr->TriggerEvent(disband, init);
    } else if (mDisbandStatus == kDisbandsMessageOnly || err == kKicked) {
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

DECOMP_FORCEACTIVE(BandUI, "qp_coop")

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

DataNode BandUI::OnMsg(const UIScreenChangeMsg &msg) {
    Export(msg, true);
    return DataNode(kDataUnhandled, 0);
}

DataNode BandUI::OnMsg(const ProcessedJoinRequestMsg &msg) {
    if (msg.GetProcessed()) {
        VerifyBuildVersionMsg msg;
        TheNetSession->SendMsgToAll(msg, kReliable);
    }
    return 0;
}

DataNode BandUI::OnMsg(const ConnectionStatusChangedMsg &msg) {
    if (msg->Int(2) == 0) {
        TheRockCentral.ForceLogout();
        TheSessionMgr->Disconnect();
    }
    return 1;
}

DataNode BandUI::OnMsg(const ServerStatusChangedMsg &msg) {
    if (msg->Int(2) == 0) {
        TheSessionMgr->Disconnect();
    }
    return 1;
}

DataNode BandUI::OnMsg(const DiskErrorMsg &msg) {
    if (TheGameMode->Property("online_play_required", true)->Int()) {
        TheNet.GetNetSession()->Disconnect();
    }
    TheUIEventMgr->TriggerEvent(disc_error, nullptr);
    return 1;
}

DataNode BandUI::OnMsg(const JoypadConnectionMsg &msg) {
    OnOvershellMsgCommon(msg, false);
    return DataNode(kDataUnhandled, 0);
}

DataNode BandUI::OnMsg(const ButtonDownMsg &msg) {
    HAQManager::Print(kHAQType_Button);
    return OnOvershellMsgCommon(msg, true);
}

DataNode BandUI::OnMsg(const ButtonUpMsg &msg) {
    HAQManager::Print(kHAQType_Button);
    return OnOvershellMsgCommon(msg, true);
}

DataNode BandUI::OnMsg(const UIComponentSelectMsg &msg) {
    return OnOvershellMsgCommon(msg, true);
}

DataNode BandUI::OnMsg(const UIComponentSelectDoneMsg &msg) {
    return OnOvershellMsgCommon(msg, true);
}

DataNode BandUI::OnMsg(const UIComponentFocusChangeMsg &msg) {
    HAQManager::Print(kHAQType_Focus);
    return OnOvershellMsgCommon(msg, true);
}

DataNode BandUI::OnMsg(const UIComponentScrollMsg &msg) {
    DataNode ret = OnOvershellMsgCommon(msg, true);
    HAQManager::HandleComponentScroll(msg.GetUIComponent());
    return ret;
}

DataNode BandUI::OnMsg(const GameMicsChangedMsg &msg) {
    return OnOvershellMsgCommon(msg, false);
}

DataNode BandUI::OnOvershellMsgCommon(const Message &msg, bool b2) {
    if (TheUIEventMgr->HasActiveDialogEvent() && EventDialog()) {
        if (EventDialog()->GetState() == UIPanel::kUp) {
            DataNode handled = EventDialog()->Handle(msg, false);
            if (b2 || handled.Type() != kDataUnhandled) {
                return 1;
            }
        }
    }
    DataNode ret(kDataUnhandled, 0);

    if (ret == DataNode(kDataUnhandled, 0) && mOvershell
        && mOvershell->GetState() == UIPanel::kUp) {
        ret = mOvershell->Handle(msg, false);
    }

    if (ret == DataNode(kDataUnhandled, 0) && TheNetSync->IsEnabled()) {
        if (!TheSessionMgr->IsLeaderLocal()) {
            ret = 0;
        }
    }

    return ret;
}

DataNode BandUI::OnMsg(const NetErrorMsg &msg) {
    if (TheNetSession->IsOnlineEnabled()) {
        ShowNetError();
    }
    return 1;
}

bool BandUI::InComponentSelect() {
    if (TheUIEventMgr->HasActiveDialogEvent() && mEventDialog
        && mEventDialog->GetState() == UIPanel::kUp) {
        UIComponent *c = mEventDialog->FocusComponent();
        if (c) {
            return c->GetState() == UIComponent::kSelecting;
        }
    }
    return UIManager::InComponentSelect();
}

UIScreen *BandUI::GetTargetScreen(UIScreen *screen) {
    if (unkd4) {
        UIScreen *toScreen = mInterstitialMgr->CurrentInterstitialToScreen(screen);
        if (toScreen) {
            mInterstitialMgr->PrintOverlay(mCurrentScreen, screen);
            toScreen->SetProperty(dest_screen, screen);
            screen = toScreen;
            mInterstitialMgr->RefreshRandomSelection();
        }
    }
    return screen;
}

void BandUI::GotoScreen(UIScreen *s, bool b2, bool b3) {
    if (TheNetSync->IsTransitionAllowed(s)) {
        UIScreen *screen = GetTargetScreen(s);
        if (b3) {
            WipeOnNextTransition(false);
        }
        UIManager::GotoScreen(screen, b2, b3);
        NetGotoScreenMsg msg(screen, b2, b3);
        TheNetSync->SendStartTransitionMsg(msg);
    }
}

void BandUI::PushScreen(UIScreen *screen) {
    if (TheNetSync->IsTransitionAllowed(screen)) {
        UIManager::PushScreen(screen);
        NetPushScreenMsg msg(screen);
        TheNetSync->SendStartTransitionMsg(msg);
    }
}

void BandUI::PopScreen(UIScreen *screen) {
    if (TheNetSync->IsTransitionAllowed(screen)) {
        UIManager::PopScreen(screen);
        NetPopScreenMsg msg(screen);
        TheNetSync->SendStartTransitionMsg(msg);
    }
}

void BandUI::WriteToVignetteOverlay(const char *str) {
    if (mVignetteOverlay) {
        mVignetteOverlay->Clear();
        *mVignetteOverlay << str;
    }
}

void BandUI::UpdateUIOverlay() {
    if (mUIOverlay && mUIOverlay->Showing()) {
        int lines = 0;
        mUIOverlay->Clear();
        std::vector<UIScreen *> screens;
        GetCurrentScreenState(screens);
        FOREACH (it, screens) {
            *mUIOverlay << "screen " << (*it)->Name() << "\n";
            lines++;
            UIPanel *focusPanel = (*it)->FocusPanel();
            FOREACH (ref, (*it)->GetPanelRefs()) {
                const PanelRef &cur = *ref;
                int refs = cur.mPanel->LoadRefs();
                const char *name = cur.mPanel->Name();
                const char *cc = focusPanel == cur.mPanel ? "* " : "  ";
                bool b4 = cur.mPanel->IsLoaded();
                *mUIOverlay << "panel " << b4 << cc << refs << " " << name << "\n";
                lines++;
            }
        }
        if (mTransitionScreen) {
            *mUIOverlay << "going to screen " << mTransitionScreen->Name() << "\n";
            UIPanel *focusPanel = mTransitionScreen->FocusPanel();
            lines++;
            FOREACH (ref, mTransitionScreen->GetPanelRefs()) {
                const PanelRef &cur = *ref;
                int refs = cur.mPanel->LoadRefs();
                const char *name = cur.mPanel->Name();
                const char *cc = focusPanel == cur.mPanel ? "* " : "  ";
                bool b4 = cur.mPanel->IsLoaded();
                *mUIOverlay << "panel " << b4 << cc << refs << " " << name << "\n";
                lines++;
            }
        }
        if (lines != 0) {
            mUIOverlay->SetLines(lines);
        }
    }
}

DataNode BandUI::OnMsg(const OvershellActiveStatusChangedMsg &) {
    UpdateInputPerformanceMode();
    return 0;
}

DataNode BandUI::OnMsg(const OvershellAllowingInputChangedMsg &) {
    UpdateInputPerformanceMode();
    return 0;
}

DataNode BandUI::OnMsg(const EventDialogStartMsg &) {
    UpdateInputPerformanceMode();
    return 0;
}

DataNode BandUI::OnMsg(const EventDialogDismissMsg &) {
    UpdateInputPerformanceMode();
    return 0;
}

DataNode BandUI::OnMsg(const LocalUserLeftMsg &) {
    UpdateInputPerformanceMode();
    return 0;
}

void BandUI::UpdateInputPerformanceMode() {
    bool inSong = mOvershell->InSong();
    bool allowInput = mOvershell->AreAllLocalSlotsAllowingInputToShell();
    bool noEvent = !TheUIEventMgr->HasActiveDialogEvent();
    bool inMode = TheGameMode->Property(allow_input_performance_mode, true)->Int();
    EnableInputPerformanceMode(inSong && allowInput && noEvent && inMode);
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(BandUI)
    HANDLE_ACTION(init_panels, InitPanels())
    HANDLE_ACTION(set_disband_status, SetDisbandStatus((DisbandStatus)_msg->Int(2)))
    HANDLE_ACTION(set_invite_accepted, SetInviteAccepted(_msg->Int(2)))
    HANDLE_EXPR(get_invite_accepted, GetInviteAccepted())
    HANDLE_ACTION(trigger_disband_event, TriggerDisbandEvent((DisbandError)_msg->Int(2)))
    HANDLE_ACTION(abstract_wipe, WipeOnNextTransition(false))
    HANDLE_ACTION(abstract_wipe_in, WipeOnNextTransition(true))
    HANDLE_ACTION(set_vignettes_showing, unkd4 = _msg->Int(2))
    HANDLE_EXPR(get_vignettes_showing, unkd4)
    HANDLE_ACTION(cycle_vignette_override, mInterstitialMgr->CycleRandomOverride())
    HANDLE_EXPR(get_vignette_override, mInterstitialMgr->mRandomOverride)
    HANDLE_ACTION(write_to_vignette_overlay, WriteToVignetteOverlay(_msg->Str(2)))
    HANDLE_ACTION_IF(
        toggle_vignette_overlay,
        mVignetteOverlay,
        mVignetteOverlay->SetShowing(!mVignetteOverlay->Showing())
    )
    HANDLE_EXPR(vignette_overlay_showing, mVignetteOverlay && mVignetteOverlay->Showing())
    HANDLE_ACTION_IF(
        toggle_ui_overlay, mUIOverlay, mUIOverlay->SetShowing(!mUIOverlay->Showing())
    )
    HANDLE_MESSAGE(UITransitionCompleteMsg)
    HANDLE_MESSAGE(UIScreenChangeMsg)
    HANDLE_MESSAGE(ProcessedJoinRequestMsg)
    HANDLE_MESSAGE(ConnectionStatusChangedMsg)
    HANDLE_MESSAGE(ServerStatusChangedMsg)
    HANDLE_MESSAGE(DiskErrorMsg)
    HANDLE_MESSAGE(ContentReadFailureMsg)
    HANDLE_MESSAGE(UIComponentFocusChangeMsg)
    HANDLE_MEMBER_PTR(TheUIStats)
    HANDLE_MEMBER_PTR(TheNetSync)
    HANDLE_MEMBER_PTR(mInputInterceptor)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_MESSAGE(UIComponentSelectMsg)
    HANDLE_MESSAGE(UIComponentSelectDoneMsg)
    HANDLE_MESSAGE(UIComponentScrollMsg)
    HANDLE_MESSAGE(JoypadConnectionMsg)
    HANDLE_MESSAGE(GameMicsChangedMsg)
    HANDLE_MESSAGE(OvershellActiveStatusChangedMsg)
    HANDLE_MESSAGE(OvershellAllowingInputChangedMsg)
    HANDLE_MESSAGE(EventDialogStartMsg)
    HANDLE_MESSAGE(EventDialogDismissMsg)
    HANDLE_MESSAGE(LocalUserLeftMsg)
    HANDLE_MESSAGE(NetErrorMsg)
    HANDLE_MEMBER_PTR(TheInputMgr)
    HANDLE_SUPERCLASS(UIManager)
    HANDLE_CHECK(0x3F0)
END_HANDLERS
#pragma pop