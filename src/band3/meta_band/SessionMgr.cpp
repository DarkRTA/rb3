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
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/Joypad.h"

void SessionMgr::Init(){
    InitJunkMsg();
}

SessionMgr::SessionMgr(BandUserMgr* umgr, Matchmaker* mm) : Synchronizable("session_mgr"), mBandUserMgr(umgr), mMatchMaker(mm), mCritUserListener(0), mBandNetGameData(new BandNetGameData()), unk5c(0), unk70(0) {
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
    unk68 = false;
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
    if((int)mSession->unk20.size() < 1){
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