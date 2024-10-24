#include "meta_band/InputMgr.h"
#include "MetaMessages.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/GameMessages.h"
#include "meta_band/ModifierMgr.h"
#include "meta_band/NetSync.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/UIEventMgr.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/MsgSource.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include "os/PlatformMgr.h"
#include "os/VirtualKeyboard.h"
#include "ui/UI.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

InputMgr* TheInputMgr;

void InputMgr::Init(){
    MILO_ASSERT(!TheInputMgr, 0x28);
    TheInputMgr = new InputMgr(TheBandUserMgr, TheUIEventMgr, TheNetSync, TheSessionMgr);
    TheInputMgr->SetName("input_mgr", ObjectDir::Main());
}

void InputMgr::Terminate(){
    RELEASE(TheInputMgr);
}

InputMgr::InputMgr(BandUserMgr* umgr, UIEventMgr* emgr, NetSync* sync, SessionMgr* smgr) : mBandUserMgr(umgr), mEventMgr(emgr), mNetSync(sync), mSessionMgr(smgr), mAutoVocalsConfirmAllowed(0), unk2d(0), mUser(0) {
    if(mSessionMgr){
        mSessionMgr->AddSink(this, LocalUserLeftMsg::Type());
        mSessionMgr->AddSink(this, SigninChangedMsg::Type());
    }
}

InputMgr::~InputMgr(){
    if(mSessionMgr){
        mSessionMgr->RemoveSink(this, SigninChangedMsg::Type());
        mSessionMgr->RemoveSink(this, LocalUserLeftMsg::Type());
    }
}

bool InputMgr::IsActiveAndConnected(ControllerType ct) const {
    MILO_ASSERT(( kControllerDrum) <= (ct) && (ct) < ( kControllerNone), 0x50);
    bool canexitremotely = AllowRemoteExit();
    std::vector<BandUser*> bandusers;
    if(mBandUserMgr){
        mBandUserMgr->GetBandUsers(&bandusers, 0);
    }
    for(std::vector<BandUser*>::iterator it = bandusers.begin(); it != bandusers.end(); ++it){
        BandUser* cur = *it;
        if(cur->IsLocal()){
            LocalBandUser* localUser = cur->GetLocalBandUser();
            if(HasValidController(localUser, ct)){
                if(AllowInput(cur)) return true;
                if(canexitremotely){
                    if(mSessionMgr->HasUser(cur)) return true;
                }
            }
        }
    }
    return false;
}

void InputMgr::CheckTriggerAutoVocalsConfirm(){
    if(!TheModifierMgr->IsModifierActive(mod_auto_vocals) && mAutoVocalsConfirmAllowed && !unk2d){
        int i1 = 0;
        MILO_ASSERT(mBandUserMgr, 0x82);
        std::vector<LocalBandUser*> users;
        mBandUserMgr->GetLocalUsersWithAnyController(users);
        for(int i = 0; i < users.size(); i++){
            ControllerType ty = users[i]->ConnectedControllerType();
            if(ty - 3U <= 1 || ty == 1) i1++;
        }
        if(i1 >= 3){
            unk2d = true;
            TheUIEventMgr->TriggerEvent(auto_vocals_confirm, 0);
        }
    }
}

BandUser* InputMgr::GetUser(){ return mUser; }

void InputMgr::SetUser(BandUser* user){
    mUser = user;
    ExportStatusChangedMsg();
}

LocalBandUser* InputMgr::GetUserWithInvalidController() const {
    if(DataVariable(fake_controllers).Int()) return nullptr;
    if(!mUser) return nullptr;
    bool b1 = false;
    if(mUser && mUser->IsLocal()) b1 = true;
    BandUser* user = b1 ? mUser : 0;
    std::vector<LocalBandUser*> users;
    if(mBandUserMgr) mBandUserMgr->GetLocalBandUsers(&users, 0);
    for(std::vector<LocalBandUser*>::iterator it = users.begin(); it != users.end(); ++it){
        LocalBandUser* cur = *it;
        if(mSessionMgr->HasUser(cur) || (user == cur)){
            cur->GetControllerType();
            if(!HasValidController(cur, cur->GetControllerType())) return cur;
        }
    }
    return nullptr;
}

void InputMgr::SetInvalidMessageSink(Hmx::Object*){}
void InputMgr::ClearInvalidMessageSink(){}

bool InputMgr::AllowRemoteExit() const {

}

DataNode InputMgr::OnMsg(const LocalUserLeftMsg& msg){
    if(mUser && mUser->IsLocal()){
        if(mUser->GetLocalUser() == msg.GetUser()){
            ExportUserLeftMsg();
        }
    }
    return 1;
}

DataNode InputMgr::OnMsg(const SigninChangedMsg& msg){
    if(mUser && mUser->IsLocal()){
        if(!mUser->GetLocalBandUser()->CanSaveData()){
            ExportUserLeftMsg();
        }
    }
    return 1;
}

DataNode InputMgr::OnMsg(const JoypadConnectionMsg& msg){
    ExportStatusChangedMsg();
    CheckTriggerAutoVocalsConfirm();
    return DataNode(kDataUnhandled, 0);
}

DataNode InputMgr::OnMsg(const ButtonDownMsg& msg){
    MILO_ASSERT(mBandUserMgr, 0x125);
    BandUser* pUser = BandUserMgr::GetBandUser(msg.GetUser());
    MILO_ASSERT(pUser && pUser->IsLocal(), 0x127);
    LocalBandUser* pLocalBandUser = pUser->GetLocalBandUser();
    if(msg.GetAction() == kAction_Cancel && mEventMgr && !mEventMgr->HasActiveDialogEvent() &&
        TheUI->GetTransitionState() == kTransitionNone && !TheUI->InComponentSelect() && AllowRemoteExit()){
        if(mSessionMgr->HasUser(pLocalBandUser) && pLocalBandUser->mOvershellState == 5){
            mEventMgr->TriggerEvent(remote_exit, 0);
            return 0;
        }
    }
    if(!AllowInput(pLocalBandUser)) return 0;
    else return DataNode(kDataUnhandled, 0);
}

DataNode InputMgr::OnMsg(const ButtonUpMsg& msg){
    BandUser* pUser = BandUserMgr::GetBandUser(msg.GetUser());
    MILO_ASSERT(pUser && pUser->IsLocal(), 0x146);
    LocalBandUser* pLocalBandUser = pUser->GetLocalBandUser();
    if(!AllowInput(pLocalBandUser)) return 0;
    else return DataNode(kDataUnhandled, 0);
}

void InputMgr::ExportStatusChangedMsg(){
    static InputStatusChangedMsg msg;
    Export(msg, false);
}

void InputMgr::ExportUserLeftMsg(){
    static InputUserLeftMsg msg;
    Export(msg, false);
}

bool InputMgr::HasValidController(LocalBandUser* user, ControllerType ty) const {
    if(!user->IsJoypadConnected()) return false;
    else if(!mUser || (mEventMgr && mEventMgr->HasActiveEvent())){
        bool ret = false;
        if(ty == 5 || ty == user->ConnectedControllerType()) ret = true;
        return ret;
    }
    else {
        ControllerType uTy = user->GetControllerType();
        bool ret = false;
        if((uTy == 5 || uTy == ty) && (ty == 5 || ty == user->ConnectedControllerType())) ret = true;
        return ret;
    }
}

bool InputMgr::AllowInput(BandUser* user) const {
    if(mNetSync && mNetSync->IsBlockingTransition()) return false;
    if(ThePlatformMgr.mHomeMenuWii->mHomeMenuActive || TheVirtualKeyboard.IsKeyboardShowing()) return false;
    if(mEventMgr && mEventMgr->HasActiveDialogEvent()) return true;
    else if(mUser) return user == mUser;
    else return true;
}

bool InputMgr::IsValidButtonForShell(JoypadButton btn, LocalBandUser* user){
    ControllerType userType = user->ConnectedControllerType();
    switch(btn){
        case kPad_L2:
        case kPad_R2:
        case kPad_L1:
        case kPad_Tri:
        case kPad_Circle:
        case kPad_X:
        case kPad_Square:
        case kPad_Select:
        case kPad_L3:
        case kPad_R3:
        case kPad_Start:
        case kPad_DUp:
        case kPad_DRight:
        case kPad_DDown:
        case kPad_DLeft:
        case kPad_LStickUp:
        case kPad_LStickRight:
        case kPad_LStickDown:
        case kPad_LStickLeft:
            return true;
        case kPad_R1:
        case kPad_RStickUp:
        case kPad_RStickRight:
        case kPad_RStickDown:
        case kPad_RStickLeft:
            ControllerType overrideType = TheBandUserMgr->DebugGetControllerTypeOverride(user->GetPadNum());
            if(overrideType != kControllerNone) return true;
            else return userType > kControllerGuitar;
        default:
            return false;
    }
}

BEGIN_HANDLERS(InputMgr)
    HANDLE_MESSAGE(LocalUserLeftMsg)
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE_MESSAGE(JoypadConnectionMsg)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_EXPR(has_user, mUser != nullptr)
    HANDLE_EXPR(get_user, mUser)
    HANDLE_ACTION(set_user, SetUser(_msg->Obj<BandUser>(2)))
    HANDLE_ACTION(clear_user, SetUser(nullptr))
    HANDLE_EXPR(get_user_with_invalid_controller, GetUserWithInvalidController())
    HANDLE_EXPR(allow_remote_exit, AllowRemoteExit())
    HANDLE_EXPR(is_valid_button_for_shell, IsValidButtonForShell((JoypadButton)_msg->Int(2), _msg->Obj<LocalBandUser>(3)))
    HANDLE_ACTION(check_trigger_auto_vocals_confirm, CheckTriggerAutoVocalsConfirm())
    HANDLE_ACTION(set_auto_vocals_confirm_allowed, mAutoVocalsConfirmAllowed = true)
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0x2B1)
END_HANDLERS