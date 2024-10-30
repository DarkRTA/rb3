#include "meta_band/SessionMgr.h"
#include "BandMachineMgr.h"
#include "BandNetGameData.h"
#include "MetaMessages.h"
#include "MetaNetMsgs.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/GameMessages.h"
#include "game/GameMode.h"
#include "math/Rand.h"
#include "meta_band/BandMachine.h"
#include "meta_band/CharSync.h"
#include "meta_band/CriticalUserListener.h"
#include "meta_band/Matchmaker.h"
#include "meta_band/ProfileMgr.h"
#include "net/NetSession.h"
#include "net/Synchronize.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/MsgSource.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/User.h"
#include "utl/HxGuid.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include <vector>

void SessionMgr::Init(){
    InitJunkMsg();
}

SessionMgr::SessionMgr(BandUserMgr* umgr, Matchmaker* mm) : Synchronizable("session_mgr"), mBandUserMgr(umgr), mMatchMaker(mm), mCritUserListener(0), mBandNetGameData(new BandNetGameData()), mUserLeader(0), mInvitesAllowed(0) {
    mMachineMgr = new BandMachineMgr(this, mBandUserMgr);
    mCritUserListener = new CriticalUserListener(this);
    mNewPlayer.mUser = 0;
    mNewPlayer.mCt = kControllerNone;
    mNewPlayer.mSlot = 0;
    SetName("session_mgr", ObjectDir::Main());
    mBandUserMgr->unk78 = this;
    mSession = TheNetSession;
    mSession->AddSink(this, SessionDisconnectedMsg::Type());
    mSession->AddSink(this, SessionBusyMsg::Type());
    mSession->AddSink(this, SigninChangedMsg::Type());
    mSession->AddSink(this, JoinResultMsg::Type());
    mSession->AddSink(this, ProcessedJoinRequestMsg::Type());
    mSession->AddSink(this, NewRemoteUserMsg::Type());
    mSession->AddSink(this, RemoteUserLeftMsg::Type());
    mSession->AddSink(this, LocalUserLeftMsg::Type());
    if(TheGameMode){
        TheGameMode->AddSink(this);
    }
    mActiveRosterSet = false;
    mNetRandomSeed = RandomInt();
}

SessionMgr::~SessionMgr(){
    mSession->RemoveSink(this, SigninChangedMsg::Type());
    mSession->RemoveSink(this, SessionDisconnectedMsg::Type());
    mSession->RemoveSink(this, SessionBusyMsg::Type());
    mSession->RemoveSink(this, JoinResultMsg::Type());
    mSession->RemoveSink(this, ProcessedJoinRequestMsg::Type());
    mSession->RemoveSink(this, NewRemoteUserMsg::Type());
    mSession->RemoveSink(this, RemoteUserLeftMsg::Type());
    mSession->RemoveSink(this, LocalUserLeftMsg::Type());
    if(TheGameMode){
        TheGameMode->RemoveSink(this);
    }
    delete mMatchMaker;
    delete mBandNetGameData;
    delete mMachineMgr;
    delete mCritUserListener;
    SetName(0, ObjectDir::Main());
}

void SessionMgr::Poll(){
    mMatchMaker->Poll();
    mBandNetGameData->Poll();
}

void SessionMgr::AddLocalUser(LocalBandUser* pUser){
    MILO_ASSERT(pUser, 0x76);
    MILO_ASSERT(mNewPlayer.mUser == NULL, 0x77);
    if((int)mSession->mUsers.size() < 1){
        SetLeaderUser(pUser);
    }
    mNewPlayer.mUser = pUser;
    ControllerType ty = pUser->ConnectedControllerType();
    pUser->SetControllerType(ty);
    pUser->SetHasButtonGuitar(UserHasButtonGuitar(pUser));
    pUser->SetHas22FretGuitar(UserHas22FretGuitar(pUser));
    if(ty == kControllerRealGuitar){
        TheProfileMgr.SetHasConnectedProGuitar(true);
    }
    AddLocalUserImpl(pUser);
}

void SessionMgr::AddLocalUserImpl(LocalBandUser* user){
    mSession->AddSink(this, AddUserResultMsg::Type());
    mSession->AddLocalUser(user);
}

void SessionMgr::RemoveLocalUser(LocalBandUser* pUser){
    MILO_ASSERT(pUser, 0xB7);
    pUser->mParticipating = false;
    RemoveLocalUserImpl(pUser);
    UpdateLeader();
    if(HasSyncPermission()){
        SetSyncDirty(-1, false);
    }
}

DataNode SessionMgr::OnMsg(const LocalUserLeftMsg& msg){
    UpdateLeader();
    Export(msg, true);
    if(TheCharSync) TheCharSync->UpdateCharCache();
    return 0;
}

void SessionMgr::RemoveLocalUserImpl(LocalBandUser* user){
    mSession->RemoveLocalUser(user);
}

void SessionMgr::RegisterOnline(){
    mSession->AddSink(this, SessionReadyMsg::Type());
    mSession->RegisterOnline();
}

void SessionMgr::Disconnect(){
    mSession->Disconnect();
}

bool SessionMgr::IsOnlineEnabled() const {
    return mSession->IsOnlineEnabled();
}

bool SessionMgr::IsLocal() const {
    return mSession->IsLocal();
}

bool SessionMgr::HasRemoteUsers() const {
    std::vector<RemoteBandUser*> users;
    mBandUserMgr->GetRemoteBandUsers(&users, 0x4000);
    return !users.empty();
}

LocalBandUser* SessionMgr::GetLocalHost() const {
    return BandUserMgr::GetLocalBandUser(mSession->GetLocalHost());
}

void SessionMgr::SendMsg(BandUser* user, NetMessage& msg, PacketType ty){
    mSession->SendMsg(user, msg, ty);
}

void SessionMgr::SendMsg(RemoteBandMachine* machine, NetMessage& msg, PacketType ty){
    std::vector<BandUser*> bandusers;
    mBandUserMgr->GetParticipatingBandUsers(bandusers);
    for(int i = 0; i < bandusers.size(); i++){
        unsigned int curID = bandusers[i]->mMachineID;
        if(curID == machine->GetMachineID()){
            mSession->SendMsg(bandusers[i], msg, ty);
            break;
        }
    }
}

void SessionMgr::SendMsg(const std::vector<RemoteBandUser*>& remotebandusers, NetMessage& msg, PacketType ty){
    std::vector<RemoteUser*> users;
    for(int i = 0; i < remotebandusers.size(); i++){
        users.push_back(remotebandusers[i]);
    }
    mSession->SendMsg(users, msg, ty);
}

void SessionMgr::SendMsgToAll(NetMessage& msg, PacketType ty){
    mSession->SendMsgToAll(msg, ty);
}

void SessionMgr::UpdateLeader(){
    if(mUserLeader && HasUser(mUserLeader)) return;
    LocalBandUser* newleader = nullptr;
    std::vector<LocalUser*> localusers;
    GetLocalUserListImpl(localusers);
    if(!localusers.empty()){
        newleader = BandUserMgr::GetLocalBandUser(localusers.front());
    }
    SetLeaderUser(newleader);
}

BandUser* SessionMgr::GetLeaderUser() const {
    if(mSession && mSession->IsJoining()) return nullptr;
    else return mUserLeader;
}

bool SessionMgr::HasLeaderUser() const { return mUserLeader; }

void SessionMgr::ClearLeader(){
    SetLeaderUser(0);
}

void SessionMgr::SetLeaderUser(BandUser* user){
    if(mUserLeader != user){
        mUserLeader = user;
        if(HasSyncPermission()){
            SetSyncDirty(-1, false);
        }
    }
}

bool SessionMgr::IsLeaderLocal() const {
    if(mBandUserMgr->GetNumParticipants() == 0) return true;
    else if(mSession && mSession->IsJoining()){
        return false;
    }
    else {
        BandUser* leader = GetLeaderUser();
        return leader && leader->IsLocal();
    }
}

bool SessionMgr::IsLocalToLeader(const BandUser* user) const {
    BandUser* leader = GetLeaderUser();
    return leader && (leader->mMachineID == user->mMachineID);
}

bool SessionMgr::HasUser(const User* user) const {
    return mSession->HasUser(user);
}

bool SessionMgr::IsBusy() const {
    return mSession->IsBusy();
}

int SessionMgr::NumOpenSlots() const {
    return mSession->NumOpenSlots();
}

DataNode SessionMgr::OnMsg(const SessionReadyMsg& msg){
    mSession->RemoveSink(this, SessionReadyMsg::Type());
    if(msg->Int(2)){
        mSession->SetInvitesAllowed(mInvitesAllowed);
        mMatchMaker->UpdateMatchmakingSettings();
    }
    Export(msg, true);
    return 0;
}

DataNode SessionMgr::OnMsg(const SessionDisconnectedMsg& msg){
    UpdateLeader();
    mMatchMaker->CancelFind();
    Export(msg, true);
    return 1;
}

DataNode SessionMgr::OnMsg(const SessionBusyMsg& msg){
    Export(msg, true);
    return 1;
}

DataNode SessionMgr::OnMsg(const AddUserResultMsg& msg){
    mSession->RemoveSink(this, AddUserResultMsg::Type());
    static AddLocalUserResultMsg msgAddLocalResult(0, 0);
    if(msg.GetResult()){
        msgAddLocalResult[0] = 1;
        msgAddLocalResult[1] = mNewPlayer.mUser;
        mNewPlayer.mUser->mParticipating = true;
    }
    else {
        msgAddLocalResult[0] = 0;
        msgAddLocalResult[1] = 0;
    }
    mNewPlayer.mUser = nullptr;
    Handle(msgAddLocalResult, false);
    return 0;
}

DataNode SessionMgr::OnMsg(const SigninChangedMsg& msg){
    if(IsOnlineEnabled()){
        if(mNewPlayer.mUser && !mNewPlayer.mUser->IsSignedIn()){
            Disconnect();
        }
        std::vector<LocalUser*> localusers;
        GetLocalUserListImpl(localusers);
        do {
            std::vector<LocalUser*> localusers2;
            GetLocalUserListImpl(localusers2);
            std::vector<LocalUser*>::iterator it;
            for(it = localusers2.begin(); it != localusers2.end(); ++it){
                if(!(*it)->IsSignedIn()){
                    RemoveLocalUser(BandUserMgr::GetLocalBandUser(*it));
                    break;
                }
            }
            if(it == localusers2.end()) goto next;
        } while(true);
        goto end;
next:
        for(int i = 0; i < localusers.size(); i++){
            LocalUser* user = localusers[i];
            user->GetPadNum();
            if(!user->HasOnlinePrivilege()){
                Disconnect();
                break;
            }
        }
    }
end:
    Export(msg, true);
    return 0;
}

DataNode SessionMgr::OnMsg(const ModeChangedMsg&){
    UpdateInvitesAllowed();
    return 1;
}

void SessionMgr::GetLocalUserListImpl(std::vector<LocalUser*>& users) const {
    mSession->GetLocalUserList(users);
}

DataNode SessionMgr::OnMsg(const NewRemoteUserMsg& msg){
    RemoteBandUser* user = BandUserMgr::GetRemoteBandUser(msg.GetUser());
    user->mParticipating = true;
    if(IsLeaderLocal()){
        mWaitingUsers.push_back(user);
        mMatchMaker->UpdateMatchmakingSettings();
    }
    Export(msg, true);
    if(TheCharSync) TheCharSync->UpdateCharCache();
    if(DataVariable("send_fake_patches").Int()){
        SendJunkPatchesToUser(user);
    }
    return 0;
}

DataNode SessionMgr::OnMsg(const RemoteUserLeftMsg& msg){
    RemoteBandUser* user = BandUserMgr::GetRemoteBandUser(msg.GetUser());
    std::vector<RemoteBandUser*>::iterator it = std::find(mWaitingUsers.begin(), mWaitingUsers.end(), user);
    if(it != mWaitingUsers.end()){
        mWaitingUsers.erase(it);
    }
    user->mParticipating = false;
    static RemoteLeaderLeftMsg leaderLeftMsg;
    BandUser* leader = mUserLeader;
    UpdateLeader();
    if(user == leader){
        Export(leaderLeftMsg, true);
    }
    Export(msg, true);
    mMatchMaker->UpdateMatchmakingSettings();
    if(!mActiveRosterSet){
        MILO_ASSERT(user, 0x243);
        user->Reset();
    }
    if(TheCharSync) TheCharSync->UpdateCharCache();
    return 0;
}

void SessionMgr::GetWaitingUsers(std::vector<RemoteBandUser*>& users){
    users = mWaitingUsers;
}

void SessionMgr::ClearWaitingUsers(){
    mWaitingUsers.clear();
}

DataNode SessionMgr::OnMsg(const JoinResultMsg& msg){
    if(!msg->Int(2)){
        ClearLeader();
        // TheBandUI setting
        mSession->SetInvitesAllowed(mInvitesAllowed);
    }
    return 1;
}

DataNode SessionMgr::OnMsg(const ProcessedJoinRequestMsg& msg){
    Export(msg, true);
    return 1;
}

void SessionMgr::SetActiveRoster(bool b){
    if(HasSyncPermission()){
        if(!b){
            std::vector<BandUser*> users;
            mBandUserMgr->GetParticipatingBandUsers(users);
            for(int i = 0; i < users.size(); i++){
                if(!HasUser(users[i])){
                    users[i]->Reset();
                    mMatchMaker->UpdateMatchmakingSettings();
                }
            }
        }
        mActiveRosterSet = b;
        SetSyncDirty(-1, false);
    }
}

void SessionMgr::ChangeRandomSeed(){
    if(HasSyncPermission()){
        mNetRandomSeed = RandomInt();
        SetSyncDirty(-1, false);
    }
}

void SessionMgr::UpdateInvitesAllowed(){
    bool allowed = AreInvitesAllowed();
    if(allowed != mInvitesAllowed){
        mInvitesAllowed = allowed;
        if(mSession->IsOnlineEnabled()){
            mSession->SetInvitesAllowed(mInvitesAllowed);
        }
    }
}

void SessionMgr::SyncSave(BinStream& bs, unsigned int) const {
    bs << mActiveRosterSet;
    bs << mNetRandomSeed;
    BandUser* leader = GetLeaderUser();
    if(leader) bs << leader->mUserGuid;
    else bs << gNullUserGuid;
    for(int i = 0; i < 4; i++){
        BandUser* user = mBandUserMgr->GetUserFromSlot(i);
        if(user) bs << user->mUserGuid;
        else bs << gNullUserGuid;
    }
}

void SessionMgr::SyncLoad(BinStream& bs, unsigned int){
    bs >> mActiveRosterSet;
    bs >> mNetRandomSeed;
    UserGuid leaderguid;
    bs >> leaderguid;
    mUserLeader = mBandUserMgr->GetBandUser(leaderguid, false);
    mBandUserMgr->ResetSlots();
    for(int i = 0; i < 4; i++){
        UserGuid guid;
        bs >> guid;
        BandUser* user = mBandUserMgr->GetBandUser(guid, false);
        if(user && (!user->IsLocal() || user->IsParticipating())){
            mBandUserMgr->SetSlot(user, i);
        }
    }
    TheCharSync->UpdateCharCache();
}

bool SessionMgr::HasSyncPermission() const { return IsLeaderLocal(); }

void SessionMgr::OnSynchronized(unsigned int ui){
    static SessionMgrUpdatedMsg msg;
    Export(msg, true);
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(SessionMgr)
    HANDLE_ACTION(add_local_user, AddLocalUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_ACTION(remove_local_user, RemoveLocalUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_ACTION(disconnect, Disconnect())
    HANDLE_EXPR(get_leader_user, GetLeaderUser())
    HANDLE_EXPR(has_leader_user, HasLeaderUser())
    HANDLE_ACTION(set_leader_user, SetLeaderUser(_msg->Obj<BandUser>(2)))
    HANDLE_EXPR(is_online_enabled, IsOnlineEnabled())
    HANDLE_EXPR(is_local, IsLocal())
    HANDLE_EXPR(has_remote_users, HasRemoteUsers())
    HANDLE_EXPR(is_leader_local, IsLeaderLocal())
    HANDLE_EXPR(is_busy, IsBusy())
    HANDLE_ACTION(set_active_roster, SetActiveRoster(_msg->Int(2)))
    HANDLE_EXPR(get_net_random_seed, mNetRandomSeed)
    HANDLE_EXPR(are_invites_allowed, AreInvitesAllowed())
    HANDLE_MESSAGE(SessionReadyMsg)
    HANDLE_MESSAGE(SessionDisconnectedMsg)
    HANDLE_MESSAGE(SessionBusyMsg)
    HANDLE_MESSAGE(AddUserResultMsg)
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE_MESSAGE(NewRemoteUserMsg)
    HANDLE_MESSAGE(RemoteUserLeftMsg)
    HANDLE_MESSAGE(LocalUserLeftMsg)
    HANDLE_MESSAGE(JoinResultMsg)
    HANDLE_MESSAGE(ProcessedJoinRequestMsg)
    HANDLE_MESSAGE(ModeChangedMsg)
    HANDLE_MEMBER_PTR(mBandNetGameData)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0x32A)
END_HANDLERS
#pragma pop