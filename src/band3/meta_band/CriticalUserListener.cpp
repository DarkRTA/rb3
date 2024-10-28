#include "meta_band/CriticalUserListener.h"
#include "MetaMessages.h"
#include "SessionMgr.h"
#include "game/BandUser.h"
#include "game/GameMessages.h"
#include "meta_band/UIEventMgr.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/User.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"

CriticalUserListener::CriticalUserListener(SessionMgr* mgr) : mCriticalUser(0), mSessionMgr(mgr), mCanSaveData(0) {
    SetName("critical_user_listener", ObjectDir::Main());
    if(mSessionMgr){
        mSessionMgr->AddSink(this, LocalUserLeftMsg::Type());
        mSessionMgr->AddSink(this, SigninChangedMsg::Type());
    }
}

CriticalUserListener::~CriticalUserListener(){
    if(mSessionMgr){
        mSessionMgr->RemoveSink(this, SigninChangedMsg::Type());
        mSessionMgr->RemoveSink(this, LocalUserLeftMsg::Type());
    }
}

void CriticalUserListener::SetCriticalUser(LocalBandUser* user){
    MILO_ASSERT(user, 0x2D);
    mCanSaveData = user->CanSaveData();
    mCriticalUser = user;
}

void CriticalUserListener::ClearCriticalUser(){
    mCanSaveData = false;
    mCriticalUser = nullptr;
}

DataNode CriticalUserListener::OnMsg(const LocalUserLeftMsg& msg){
    LocalUser* userleft = msg.GetUser();
    if(userleft == mCriticalUser){
        TheUIEventMgr->TriggerEvent(critical_user_drop_out, 0);
        mCanSaveData = false;
    }
    return 1;
}

DataNode CriticalUserListener::OnMsg(const SigninChangedMsg& msg){
    if(!mCanSaveData) return 1;
    else {
        int msgInt = msg->Int(3); // TODO: figure out what this int represents
        if(mCriticalUser){
            int padnum = mCriticalUser->GetPadNum();
            if(msgInt & (1 << padnum)){
                static Message init("init", 0);
                init[0] = 0;
                TheUIEventMgr->TriggerEvent(sign_out, init);
            }
        }
        return 1;
    }
}

BEGIN_HANDLERS(CriticalUserListener)
    HANDLE_ACTION(clear_critical_user, ClearCriticalUser())
    HANDLE_ACTION(set_critical_user, SetCriticalUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(get_critical_user, mCriticalUser)
    HANDLE_MESSAGE(LocalUserLeftMsg)
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x68)
END_HANDLERS