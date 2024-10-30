#include "net/NetSession.h"
#include "NetMessage.h"
#include "SessionMessages.h"
#include "game/GameMessages.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/User.h"
#include "os/UserMgr.h"
#include <vector>

std::vector<LocalUser*> gLocalUsersRemovedThisFrame;

NetMessage* JoinRequestMsg::NewNetMessage(){ return new JoinRequestMsg(); }
NetMessage* JoinResponseMsg::NewNetMessage(){ return new JoinResponseMsg(kSuccess, 0); }
NetMessage* NewUserMsg::NewNetMessage(){ return new NewUserMsg(); }
NetMessage* UserLeftMsg::NewNetMessage(){ return new UserLeftMsg(); }
NetMessage* AddUserRequestMsg::NewNetMessage(){ return new AddUserRequestMsg(); }
NetMessage* AddUserResponseMsg::NewNetMessage(){ return new AddUserResponseMsg(); }
NetMessage* UpdateUserDataMsg::NewNetMessage(){ return new UpdateUserDataMsg(); }
NetMessage* BeginArbitrationMsg::NewNetMessage(){ return new BeginArbitrationMsg(); }
NetMessage* FinishedArbitrationMsg::NewNetMessage(){ return new FinishedArbitrationMsg(); }
NetMessage* StartGameOnTimeMsg::NewNetMessage(){ return new StartGameOnTimeMsg(); }
NetMessage* EndGameMsg::NewNetMessage(){ return new EndGameMsg(); }
NetMessage* VoiceDataMsg::NewNetMessage(){ return new VoiceDataMsg(); }
NetMessage* DataArrayMsg::NewNetMessage(){ return new DataArrayMsg(); }

namespace {
    void RegisterSessionMessages(){
        JoinRequestMsg::Register();
        JoinResponseMsg::Register();
        NewUserMsg::Register();
        AddUserRequestMsg::Register();
        AddUserResponseMsg::Register();
        UserLeftMsg::Register();
        UpdateUserDataMsg::Register();
        BeginArbitrationMsg::Register();
        FinishedArbitrationMsg::Register();
        StartGameOnTimeMsg::Register();
        EndGameMsg::Register();
        VoiceDataMsg::Register();
        DataArrayMsg::Register();
    }

    void DisconnectOnFail(){}
}

NetSession::NetSession() : unk1c(0), mLocalHost(0), unk2c(0), mJobMgr(this), unk44(-1), mGameState(kInLobby), mRevertingJoinResult(0), unk58(0), mState(kIdle), mOnlineEnabled(0), unk68(0) {
    RegisterSessionMessages();
    TheDebug.AddExitCallback(DisconnectOnFail);
    MILO_ASSERT(!TheNetSession, 0x5B);
    TheNetSession = this;
}

void NetSession::AssignLocalOwner(){
    MILO_ASSERT(!mLocalHost, 0x89);
    std::vector<LocalUser*> users;
    GetLocalUserList(users);
    mLocalHost = TheUserMgr->GetLocalUserFromPadNum(ThePlatformMgr.GetOwnerOfGuest(0));
    MILO_ASSERT(mLocalHost, 0xA5);
}

void NetSession::OnCreateSessionJobComplete(bool b){
    MILO_ASSERT(mState == kCreatingHostSession || mState == kCreatingJoinSession || mState == kRevertingToHost, 0xAC);
    if(mState == kCreatingHostSession){
        if(b){
            SetState(kRegisteringHostSession);
            PrepareRegisterHostSessionJob();
            mJobMgr.QueueJob(0);
        }
        else {
            SetState(kIdle);
            static SessionReadyMsg msg(0);
            Handle(msg, false);
        }
    }
    else if(mState == kCreatingJoinSession){
        if(b){
            SetState(kConnectingToSession);
            PrepareConnectSessionJob();
            mJobMgr.QueueJob(0);
        }
        else {
            OnMsg(JoinResponseMsg(kCannotConnect, 0));
        }
    }
    else {
        SetState(kIdle);
        MILO_ASSERT(mRevertingJoinResult, 0xD2);
        JoinResultMsg msg = *mRevertingJoinResult;
        RELEASE(mRevertingJoinResult);
        Handle(msg, false);
        if(!b) Disconnect();
    }
}

void NetSession::OnRegisterSessionJobComplete(bool b){
    MILO_ASSERT(mState == kRegisteringHostSession, 0xE0);
    SetState(kIdle);
    if(b){
        std::vector<LocalUser*> users;
        GetLocalUserList(users);
        for(int i = 0; i < users.size(); i++){
            RemoveLocalFromSession(users[i]);
        }
        mOnlineEnabled = true;
        MILO_ASSERT(mLocalHost, 0xEF);
        AddLocalToSession(mLocalHost);
        for(int i = 0; i < users.size(); i++){
            if(users[i] != mLocalHost){
                AddLocalToSession(users[i]);
            }
        }
    }
    else Disconnect();

    SessionReadyMsg msg(b);
    MsgSource::Handle(msg, false);
}

void NetSession::OnConnectSessionJobComplete(bool b){
    MILO_ASSERT(mState == kConnectingToSession, 0x103);
    if(b){
        if(!mOnlineEnabled){
            std::vector<LocalUser*> users;
            GetLocalUserList(users);
            for(int i = 0; i < users.size(); i++){
                users[i]->UpdateOnlineID();
            }
        }
        SetState(kRequestingJoin);
        JoinRequestMsg(unk20, 0);
    }
    else {
        static JoinResponseMsg response(kCannotConnect, 0);
        OnMsg(response);
    }
}

void NetSession::Clear(){
    Disconnect();
    std::vector<LocalUser*> users;
    GetLocalUserList(users);
    for(int i = 0; i < users.size(); i++){
        RemoveLocalUser(users[i]);
    }
    SetState(kIdle);
    mGameState = kInLobby;
}

DataNode NetSession::OnSendMsg(DataArray* a){
    User* destUser = a->Obj<User>(2);
    DataArray* arr = a->Array(3);
    int i = a->Int(4);
    DataArrayMsg msg(arr);
    SendMsg(destUser, msg, (PacketType)i);
    return 1;
}

DataNode NetSession::OnSendMsgToAll(DataArray* a){
    DataArray* arr = a->Array(2);
    int i = a->Int(3);
    DataArrayMsg msg(arr);
    SendMsgToAll(msg, (PacketType)i);
    return 1;
}

void NetSession::EnterInGameState(){
    MILO_ASSERT(mGameState == kStartingGame, 0x552);
    if(mOnlineEnabled){
        mGameState = kInOnlineGame;
        StartSession();
    }
    else {
        mGameState = kInLocalGame;
    }
    static SyncStartGameMsg start;
    Handle(start, false);
}