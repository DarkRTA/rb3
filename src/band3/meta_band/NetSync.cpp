#include "meta_band/NetSync.h"
#include "BandMachine.h"
#include "LockStepMgr.h"
#include "decomp.h"
#include "game/NetGameMsgs.h"
#include "game/UISyncNetMsgs.h"
#include "game/UITransitionNetMsgs.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/UIEventMgr.h"
#include "net/Net.h"
#include "net/NetMessage.h"
#include "net/NetSession.h"
#include "net/SyncStore.h"
#include "net_band/RockCentral.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/User.h"
#include "ui/UI.h"
#include "ui/UIComponent.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

NetSync *TheNetSync;

NetMessage *ComponentFocusNetMsg::NewNetMessage() { return new ComponentFocusNetMsg(); }
NetMessage *ComponentSelectNetMsg::NewNetMessage() { return new ComponentSelectNetMsg(); }
NetMessage *ComponentScrollNetMsg::NewNetMessage() { return new ComponentScrollNetMsg(); }
NetMessage *NetGotoScreenMsg::NewNetMessage() { return new NetGotoScreenMsg(); }
NetMessage *NetPushScreenMsg::NewNetMessage() { return new NetPushScreenMsg(); }
NetMessage *NetPopScreenMsg::NewNetMessage() { return new NetPopScreenMsg(); }
NetMessage *NetSyncScreenMsg::NewNetMessage() { return new NetSyncScreenMsg(); }

namespace {
    void RegisterNetMessages() {
        ComponentFocusNetMsg::Register();
        ComponentSelectNetMsg::Register();
        ComponentScrollNetMsg::Register();
        NetGotoScreenMsg::Register();
        NetPushScreenMsg::Register();
        NetPopScreenMsg::Register();
        NetSyncScreenMsg::Register();
    }
}

void NetSync::Init() {
    MILO_ASSERT(!TheNetSync, 0x37);
    TheNetSync = new NetSync();
    TheNetSync->SetName("net_sync", ObjectDir::Main());
    RegisterNetMessages();
}

void NetSync::Terminate() {
    MILO_ASSERT(TheNetSync, 0x40);
    RELEASE(TheNetSync);
}

NetSync::NetSync()
    : unk1c(1), mDestinationScreen(0), mDestinationDepth(-1), unk28(0), unk29(0),
      mUILockStep(new LockStepMgr("ui_lock_step", this)) {}

NetSync::~NetSync() { delete mUILockStep; }

FORCE_LOCAL_INLINE
bool NetSync::IsBlockingTransition() const { return mUILockStep->InLock(); }
END_FORCE_LOCAL_INLINE

bool NetSync::IsBlockingEvent(Symbol event) const {
    if (!event.Null()) {
        static Message msg("block_event", gNullStr);
        msg[0] = event;
        DataNode n30;
        for (ObjDirItr<UIPanel> it(ObjectDir::Main(), true); it != 0; ++it) {
            if (it->GetState() == UIPanel::kUp) {
                n30 = it->Handle(msg, false);
                if (n30 != DataNode(kDataUnhandled, 0) && n30.Int()) {
                    return true;
                }
            }
        }
        UIScreen *curscreen = TheUI.CurrentScreen();
        if (curscreen) {
            n30 = curscreen->Handle(msg, false);
            if (n30 != DataNode(kDataUnhandled, 0) && n30.Int()) {
                return true;
            }
        }

        if (TheUI.PushDepth() > 0) {
            UIScreen *bottomscreen = TheUI.BottomScreen();
            if (bottomscreen) {
                n30 = bottomscreen->Handle(msg, false);
                if (n30 != DataNode(kDataUnhandled, 0) && n30.Int()) {
                    return true;
                }
            }
        }
    }
    return false;
}

FORCE_LOCAL_INLINE
bool NetSync::IsEnabled() const { return GetUIState() == kNetUI_Synchronized; }
END_FORCE_LOCAL_INLINE

NetUIState NetSync::GetUIState() const {
    return TheSessionMgr->mMachineMgr->GetLocalMachine()->GetNetUIState();
}

void NetSync::Poll() {
    if (TheUI.InTransition()) {
        UIScreen *cur = TheUI.CurrentScreen();
        if (!TheUI.TransitionScreen() || TheUI.TransitionScreen()->IsLoaded()) {
            if (!cur || !cur->Exiting()) {
                if (mUILockStep->InLock() && !mUILockStep->HasResponded()) {
                    mUILockStep->RespondToLock(true);
                }
            }
        }
    } else {
        if (mDestinationScreen && TheUI.CurrentScreen()) {
            AttemptTransition(mDestinationScreen, mDestinationDepth);
        }
    }
}

bool NetSync::AttemptTransition(UIScreen *screen, int destination_depth) {
    MILO_ASSERT(destination_depth >= 0, 0xAD);
    if (!TheUI.InTransition() && !TheNetSession->IsBusy()
        && !IsBlockingEvent(TheUIEventMgr->CurrentTransitionEvent())) {
        TheRockCentral.FailAllOutstandingCalls();
        if (ObjectDir::sMainDir->Find<UIPanel>("meta_loading", true)->GetState()
            == UIPanel::kUp) {
            destination_depth = 0;
        }
        bool old28 = unk28;
        bool old29 = unk29;
        unk28 = true;
        unk29 = true;
        if (TheUI.CurrentScreen() == TheUI.BottomScreen()) {
            if (destination_depth != 0) {
                TheUI.PushScreen(screen);
            } else {
                TheUI.GotoScreen(screen, false, false);
            }
        } else if (destination_depth != 0) {
            TheUI.GotoScreen(screen, false, false);
        } else {
            TheUI.PopScreen(screen);
        }
        unk28 = old28;
        unk29 = old29;
        mDestinationScreen = nullptr;
        mDestinationDepth = -1;
        return true;
    } else {
        mDestinationScreen = screen;
        mDestinationDepth = destination_depth;
        return false;
    }
}

void NetSync::Enable() { SetUIState(kNetUI_Synchronized); }
void NetSync::Disable() { SetUIState(kNetUI_None); }

void NetSync::SetUIState(NetUIState state) {
    TheSessionMgr->mMachineMgr->GetLocalMachine()->SetNetUIState(state);
}

void NetSync::SendNetFocus(User *u, UIComponent *c) {
    if (u && TheNetSession->HasUser(u) && !u->IsLocal())
        return;
    if (IsEnabled() && c) {
        ComponentFocusNetMsg msg(u, c);
        TheNet.GetNetSession()->SendMsgToAll(msg, kReliable);
    }
}

void NetSync::SyncScreen(UIScreen *s, int i2) {
    BandUser *u = TheSessionMgr->GetLeaderUser();
    bool b2 = true;
    if (u) {
        bool b1 = false;
        if (u->IsLocal() && TheNetSession->HasUser(u)) {
            b1 = true;
        }
        if (!b1)
            b2 = false;
    }
    if (IsTransitionAllowed(s) && (b2 || unk28) && !mDestinationScreen) {
        Enable();
        AttemptTransition(s, i2);
        if (u && b2) {
            MILO_ASSERT(!IsBlockingTransition(), 0x11C);
            NetSyncScreenMsg msg(s, i2);
            TheSyncStore->Poll();
            mUILockStep->StartLock(msg);
        }
    }
}

bool NetSync::IsTransitionAllowed(UIScreen *s) const {
    if (unk28)
        return true;
    else if (!TheUIEventMgr->IsTransitionAllowed(s))
        return false;
    else {
        BandUser *u = TheSessionMgr->GetLeaderUser();
        return (IsEnabled() && u) || (TheNetSession->HasUser(u) && u->IsLocal());
    }
}

void NetSync::SendStartTransitionMsg(StartTransitionMsg &msg) {
    if (!unk29) {
        BandUser *u = TheSessionMgr->GetLeaderUser();
        if (TheUI.InTransition() && IsEnabled() && u) {
            if (TheNetSession->HasUser(u) && u->IsLocal()) {
                MILO_ASSERT(!IsBlockingTransition(), 0x145);
                TheSyncStore->Poll();
                mUILockStep->StartLock(msg);
            }
        }
    }
}

DataNode NetSync::OnMsg(const UITransitionCompleteMsg &) {
    if (IsEnabled() && mUILockStep->InLock() && !mUILockStep->HasResponded()) {
        mUILockStep->RespondToLock(true);
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode NetSync::OnMsg(const UIComponentFocusChangeMsg &msg) {
    if (!IsEnabled() || TheUIEventMgr->HasActiveDialogEvent()) {
        return DataNode(kDataUnhandled, 0);
    } else {
        BandUser *leader = TheSessionMgr->GetLeaderUser();
        if (leader && TheNetSession->HasUser(leader) && leader->IsLocal()) {
            SendNetFocus(leader, msg->Obj<UIComponent>(2));
        }
        return DataNode(kDataUnhandled, 0);
    }
}

DataNode NetSync::OnMsg(const UIComponentSelectMsg &msg) {
    if (unk1c && IsEnabled() && !TheUIEventMgr->HasActiveDialogEvent()) {
        unk1c = false;
        TheUI.Handle(msg, false);
        unk1c = true;
        if (TheNetSession->HasUser(msg.GetUser())) {
            UIComponent *c = msg.GetComponent();
            ComponentSelectNetMsg netMsg(
                msg.GetUser(),
                c,
                c->GetState() == UIComponent::kFocused
                    || c->GetState() == UIComponent::kSelecting
            );
            TheNet.GetNetSession()->SendMsgToAll(netMsg, kReliable);
        }
        return 1;

    } else
        return DataNode(kDataUnhandled, 0);
}

DataNode NetSync::OnMsg(const UIComponentScrollMsg &msg) {
    if (!IsEnabled())
        return DataNode(kDataUnhandled, 0);
    else {
        UIScreen *screen = TheUI.CurrentScreen();
        if (screen) {
            DataNode handled = screen->HandleType(net_sync_scroll_msg);
            if (handled != DataNode(kDataUnhandled, 0) && handled.Int() == 0) {
                return DataNode(kDataUnhandled, 0);
            }
        }
        LocalUser *user = msg.GetUser();
        if (user) {
            if (TheNetSession->HasUser(user)) {
                ComponentScrollNetMsg netMsg(user, msg.GetUIComponent());
                TheNet.GetNetSession()->SendMsgToAll(netMsg, kReliable);
            }
        }
        return DataNode(kDataUnhandled, 0);
    }
}

void NetSync::HandleStartTransitionMsg(StartTransitionMsg *msg) {
    MILO_ASSERT(msg, 0x1B0);
    if (msg->ByteCode() == NetSyncScreenMsg::StaticByteCode()) {
        Enable();
    } else if (!IsEnabled())
        return;

    BandUser *pUserLeader = TheSessionMgr->GetLeaderUser();
    MILO_ASSERT(pUserLeader == NULL || !pUserLeader->IsLocal(), 0x1B9);

    bool old28 = unk28;
    unk28 = true;
    if (msg->ByteCode() == NetGotoScreenMsg::StaticByteCode()) {
        NetGotoScreenMsg *gotoMsg = dynamic_cast<NetGotoScreenMsg *>(msg);
        MILO_ASSERT(gotoMsg, 0x1C2);
        TheUI.GotoScreen(msg->GetScreen(), gotoMsg->mForce, gotoMsg->mBack);
    } else if (msg->ByteCode() == NetPushScreenMsg::StaticByteCode()) {
        TheUI.PushScreen(msg->GetScreen());
    } else if (msg->ByteCode() == NetPopScreenMsg::StaticByteCode()) {
        TheUI.PopScreen(msg->GetScreen());
    } else if (msg->ByteCode() == NetSyncScreenMsg::StaticByteCode()) {
        NetSyncScreenMsg *syncMsg = dynamic_cast<NetSyncScreenMsg *>(msg);
        MILO_ASSERT(syncMsg, 0x1D1);
        SyncScreen(syncMsg->GetScreen(), syncMsg->mDepth);
    } else
        MILO_FAIL("Unknown transition type");
    unk28 = old28;
}

DataNode NetSync::OnMsg(const LockStepStartMsg &msg) {
    if (!TheSessionMgr->IsLeaderLocal()) {
        HandleStartTransitionMsg(dynamic_cast<StartTransitionMsg *>(msg.GetLockData()));
    }
    return 1;
}

DataNode NetSync::OnMsg(const LockStepCompleteMsg &msg) {
    if (TheUI.InTransition()) {
        TheUI.Poll();
    }
    return 1;
}

BEGIN_HANDLERS(NetSync)
    HANDLE_EXPR(is_enabled, IsEnabled())
    HANDLE_EXPR(get_ui_state, GetUIState())
    HANDLE_ACTION(enable, Enable())
    HANDLE_ACTION(disable, Disable())
    HANDLE_ACTION(set_ui_state, SetUIState((NetUIState)_msg->Int(2)))
    HANDLE_ACTION(sync_screen, SyncScreen(_msg->Obj<UIScreen>(2), _msg->Int(3)))
    HANDLE_MESSAGE(UIComponentFocusChangeMsg)
    HANDLE_MESSAGE(UIComponentSelectMsg)
    HANDLE_MESSAGE(UIComponentScrollMsg)
    HANDLE_MESSAGE(UITransitionCompleteMsg)
    HANDLE_MESSAGE(LockStepStartMsg)
    HANDLE_MESSAGE(LockStepCompleteMsg)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x20E)
END_HANDLERS