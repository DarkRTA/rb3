#include "net/NetSession.h"
#include "MatchmakingSettings.h"
#include "Net.h"
#include "NetMessage.h"
#include "SessionMessages.h"
#include "game/GameMessages.h"
#include "net/NetMessenger.h"
#include "net/SessionMessages.h"
#include "net/SyncStore.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "os/User.h"
#include "os/UserMgr.h"
#include <vector>
#include <algorithm>

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

NetSession::NetSession() : mData(0), mLocalHost(0), mJoinData(0), mSettings(new SessionSettings()), mJobMgr(this), unk44(-1), mGameState(kInLobby), mRevertingJoinResult(0),
    unk58(0), mState(kIdle), mOnlineEnabled(0), unk68(0) {
    SetName("session", ObjectDir::Main());
    DataArray* cfg = SystemConfig("net", "session");
    cfg->FindData("game_start_delay", mGameStartDelay, true);

    RegisterSessionMessages();
    TheDebug.AddExitCallback(DisconnectOnFail);
    MILO_ASSERT(!TheNetSession, 0x5B);
    TheNetSession = this;
}

NetSession::~NetSession(){

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
        JoinRequestMsg(mUsers, 0);
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
    mSettings->Clear();
}

#pragma push
#pragma pool_data off
void NetSession::Disconnect(){
    if(mState == kRequestingNewUser){
        SetState(kIdle);
        static AddUserResultMsg failureMsg(0);
        Handle(failureMsg, false);
    }
    if(mState == kRequestingJoin){
        static JoinResponseMsg response(kCannotConnect, 0);
        OnMsg(response);
    }
    
    for(int jobID = unk44; jobID != -1; ){
        unk44 = -1;
        MILO_ASSERT(mJobMgr.HasJob(jobID), 0x14C);
        mJobMgr.CancelJob(jobID);
    }

    // release quazal object at 0x58

    if(mGameState == kInOnlineGame){
        EndSession(false);
        mGameState = kInLocalGame;
    }

    std::vector<LocalUser*> localusers;
    GetLocalUserList(localusers);
    for(int i = 0; i < localusers.size(); i++){
        RemoveLocalFromSession(localusers[i]);
    }
    mOnlineEnabled = false;
    RELEASE(mRevertingJoinResult);
    mLocalHost = nullptr;
    unk50.clear();
    DeleteSession();
    RELEASE(mJoinData);
    RELEASE(mData);
    for(int i = 0; i < localusers.size(); i++){
        AddLocalToSession(localusers[i]);
    }
    for(int i = 0; i < mUsers.size(); i){
        if(!mUsers[i]->IsLocal()){
            ProcessUserLeftMsg(UserLeftMsg(mUsers[i]));
            i = 0;
        }
        else i++;
    }
    static SessionDisconnectedMsg msg;
    Handle(msg, false);
}
#pragma pop

bool NetSession::IsLocal() const {
    if(mState - 3U <= 3){
        return false;
    }
    else if(!mOnlineEnabled) return true;
    else if(!IsHost()) return false;
    else {
        for(int i = 0; i < mUsers.size(); i++){
            if(!mUsers[i]->IsLocal()) return false;
        }
        return true;
    }
}

bool NetSession::IsOnlineEnabled() const { return mOnlineEnabled; }

namespace {
    void DenyRequest(unsigned int ui, JoinResponseError err, int custom){
        MILO_ASSERT(custom == -1 || err == kCustom, 0x1F2);
        JoinResponseMsg respMsg(err, custom);
        TheNetMessenger.DeliverMsg(ui, respMsg, kReliable);
        ProcessedJoinRequestMsg pjReqMsg(false);
        TheNet->Handle(pjReqMsg, false);
    }
}

void NetSession::UpdateSyncStore(const User* user){
    unsigned int machineID = user->mMachineID;
    TheSyncStore->SyncUser(user);
    SyncUserMsg msg(user);
    SendToAllClientsExcept(msg, kReliable, machineID);
    SyncAllMsg allmsg;
    unsigned int ui = machineID;
    TheNetMessenger.DeliverMsg(ui, allmsg, kReliable);
}

void NetSession::SendMsg(User* destUser, NetMessage& msg, PacketType ptype){
    MILO_ASSERT(destUser, 0x4D1);
    std::vector<RemoteUser*> remoteusers;
    remoteusers.push_back(destUser->GetRemoteUser());
    SendMsg(remoteusers, msg, ptype);
}

void NetSession::SendMsg(const std::vector<RemoteUser*>& users, NetMessage& msg, PacketType ptype){
    if(mOnlineEnabled && unk68){
        std::vector<RemoteUser*> rusers;
        for(int i = 0; i < users.size(); i++){
            std::vector<RemoteUser*>::const_iterator it = std::find(users.begin(), users.end(), users[i]); // probably wrong lol
        }
    }
}

void NetSession::SendMsgToAll(NetMessage& msg, PacketType ptype){
    if(!mOnlineEnabled || !unk68) return;
    SendToAllClientsExcept(msg, ptype, -1);
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

void NetSession::SendToAllClientsExcept(const NetMessage&, PacketType, unsigned int){

}

void NetSession::AddLocalToSession(LocalUser* user){

}

void NetSession::AddRemoteToSession(RemoteUser* user){
    mUsers.push_back(user);
}

void NetSession::RemoveLocalFromSession(LocalUser* user){
    mUsers.erase(std::find(mUsers.begin(), mUsers.end(), user));
}

void NetSession::RemoveRemoteFromSession(RemoteUser* user){
    mUsers.erase(std::find(mUsers.begin(), mUsers.end(), user));
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

void NetSession::RemoveClient(unsigned int ui){
    TheNetMessenger.FlushClientMessages(ui);
    if(IsHost()){
        for(int i = 0; i < mUsers.size(); i){
            User* cur = mUsers[i];
            if(ui == cur->mMachineID){
                UserLeftMsg msg(cur);
                ProcessUserLeftMsg(msg);
                i = 0;
            }
            else i++;
        }
        if(mState == kClientsArbitrating){
            SetDoneArbitrating(ui);
        }
    }
}

void NetSession::HandleSessionMsg(SessionMsg* smsg){
    int targetByteCode = smsg->ByteCode();
    if(targetByteCode == JoinRequestMsg::StaticByteCode()){
        OnMsg(*dynamic_cast<JoinRequestMsg*>(smsg));
    }
    else if(targetByteCode == JoinResponseMsg::StaticByteCode()){
        OnMsg(*dynamic_cast<JoinResponseMsg*>(smsg));
    }
    else if(targetByteCode == NewUserMsg::StaticByteCode()){
        OnMsg(*dynamic_cast<NewUserMsg*>(smsg));
    }
    else if(targetByteCode == AddUserRequestMsg::StaticByteCode()){
        OnMsg(*dynamic_cast<AddUserRequestMsg*>(smsg));
    }
    else if(targetByteCode == AddUserResponseMsg::StaticByteCode()){
        OnMsg(*dynamic_cast<AddUserResponseMsg*>(smsg));
    }
    else if(targetByteCode == UserLeftMsg::StaticByteCode()){
        OnMsg(*dynamic_cast<UserLeftMsg*>(smsg));
    }
    else if(targetByteCode == UpdateUserDataMsg::StaticByteCode()){
        OnMsg(*dynamic_cast<UpdateUserDataMsg*>(smsg));
    }
    else if(targetByteCode == BeginArbitrationMsg::StaticByteCode()){
        OnMsg(*dynamic_cast<BeginArbitrationMsg*>(smsg));
    }
    else if(targetByteCode == FinishedArbitrationMsg::StaticByteCode()){
        OnMsg(*dynamic_cast<FinishedArbitrationMsg*>(smsg));
    }
    else if(targetByteCode == StartGameOnTimeMsg::StaticByteCode()){
        OnMsg(*dynamic_cast<StartGameOnTimeMsg*>(smsg));
    }
    else if(targetByteCode == EndGameMsg::StaticByteCode()){
        OnMsg(*dynamic_cast<EndGameMsg*>(smsg));
    }
    else if(targetByteCode == VoiceDataMsg::StaticByteCode()){
        OnMsg(*dynamic_cast<VoiceDataMsg*>(smsg));
    }
}