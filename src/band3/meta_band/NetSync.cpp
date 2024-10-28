#include "meta_band/NetSync.h"
#include "BandMachine.h"
#include "LockStepMgr.h"
#include "game/NetGameMsgs.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/UIEventMgr.h"
#include "net/NetSession.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "ui/UI.h"
#include "ui/UIMessages.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

NetSync* TheNetSync;

namespace {
    void RegisterNetMessages(){

    }
}

void NetSync::Init(){
    MILO_ASSERT(!TheNetSync, 0x37);
    TheNetSync = new NetSync();
    TheNetSync->SetName("net_sync", ObjectDir::Main());
    RegisterNetMessages();
}

void NetSync::Terminate(){
    MILO_ASSERT(TheNetSync, 0x40);
    RELEASE(TheNetSync);
}

NetSync::NetSync() : unk1c(1), mDestinationScreen(0), mDestinationDepth(-1), unk28(0), unk29(0), mUILockStep(new LockStepMgr("ui_lock_step", this)) {

}

NetSync::~NetSync(){
    delete mUILockStep;
}

bool NetSync::IsBlockingTransition() const { return mUILockStep->InLock(); }

bool NetSync::IsBlockingEvent(Symbol event) const {
    if(!event.Null()){
        static Message msg("block_event", gNullStr);
        msg[0] = event;
        DataNode n30;
        for(ObjDirItr<UIPanel> it(ObjectDir::Main(), true); it != 0; ++it){
            if(it->GetState() == UIPanel::kUp){
                n30 = it->Handle(msg, false);
                if(n30 != DataNode(kDataUnhandled, 0) && n30.Int()){
                    return true;
                }
            }
        }
        UIScreen* curscreen = TheUI->CurrentScreen();
        if(curscreen){
            n30 = curscreen->Handle(msg, false);
            if(n30 != DataNode(kDataUnhandled, 0) && n30.Int()){
                return true;
            }
        }

        if(TheUI->PushDepth() > 0){
            UIScreen* bottomscreen = TheUI->BottomScreen();
            if(bottomscreen){
                n30 = bottomscreen->Handle(msg, false);
                if(n30 != DataNode(kDataUnhandled, 0) && n30.Int()){
                    return true;
                }
            }
        }
    }
    return false;
}

bool NetSync::IsEnabled() const { return GetUIState() == kNetUI_Synchronized; }

NetUIState NetSync::GetUIState() const {
    return TheSessionMgr->mMachineMgr->GetLocalMachine()->GetNetUIState();
}

void NetSync::Poll(){
    if(TheUI->IsTransitioning()){
        UIScreen* cur = TheUI->CurrentScreen();
        if(!TheUI->TransitionScreen() || TheUI->TransitionScreen()->IsLoaded()){
            if(!cur || !cur->Exiting()){
                if(mUILockStep->InLock() && !mUILockStep->unk28){
                    mUILockStep->RespondToLock(true);
                }
            }
        }
    }
    else {
        if(mDestinationScreen && TheUI->CurrentScreen()){
            AttemptTransition(mDestinationScreen, mDestinationDepth);
        }
    }
}

void NetSync::Enable(){ SetUIState(kNetUI_Synchronized); }
void NetSync::Disable(){ SetUIState(kNetUI_None); }

void NetSync::SetUIState(NetUIState state){
    TheSessionMgr->mMachineMgr->GetLocalMachine()->SetNetUIState(state);
}

DataNode NetSync::OnMsg(const UITransitionCompleteMsg&){
    if(IsEnabled() && mUILockStep->InLock() && !mUILockStep->unk28){
        mUILockStep->RespondToLock(true);
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode NetSync::OnMsg(const UIComponentFocusChangeMsg& msg){
    if(!IsEnabled() || TheUIEventMgr->HasActiveDialogEvent()){
        return DataNode(kDataUnhandled, 0);
    }
    else {
        BandUser* leader = TheSessionMgr->GetLeaderUser();
        if(leader && TheNetSession->HasUser(leader) && leader->IsLocal()){
            SendNetFocus(leader, msg->Obj<UIComponent>(2));
        }
        return DataNode(kDataUnhandled, 0);
    }
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