#include "meta_band/BandMachineMgr.h"
#include "BandMachine.h"
#include "BandMachineMgr.h"
#include "BandProfile.h"
#include "MetaMessages.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/GameMessages.h"
#include "game/NetGameMsgs.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/Campaign.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SessionMgr.h"
#include "net/NetMessage.h"
#include "obj/Dir.h"
#include "obj/MsgSource.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/User.h"
#include "utl/BinStream.h"
#include "utl/MemStream.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include "utl/TextStream.h"

namespace {
    class SyncMachineMsg : public NetMessage {
    public:
        SyncMachineMsg() : mMachineData(false) {}
        SyncMachineMsg(unsigned int, unsigned char, BandMachine*);
        virtual ~SyncMachineMsg(){}
        virtual void Save(BinStream &) const;
        virtual void Load(BinStream &);
        virtual void Dispatch();
        virtual void Print(TextStream&) const;
        virtual unsigned char ByteCode() const { return TheNetMessageFactory.GetNetMessageByteCode("SyncMachineMsg"); }
        virtual const char* Name() const { return MakeString("SyncMachineMsg"); }

        void GetMachineData(BinStream&) const;

        static NetMessage* NewNetMessage();

        unsigned int mMachineID; // 0x4
        unsigned char mDirtyMask; // 0x8
        MemStream mMachineData; // 0xc
    };

    class SyncLocalMachineMsg : public NetMessage {
    public:
        SyncLocalMachineMsg(){}
        virtual ~SyncLocalMachineMsg(){}
        virtual void Save(BinStream &) const {}
        virtual void Load(BinStream &){}
        virtual void Dispatch(){ TheSessionMgr->mMachineMgr->SyncLocalMachine(-1); }
        virtual unsigned char ByteCode() const { return TheNetMessageFactory.GetNetMessageByteCode("SyncLocalMachineMsg"); }
        virtual const char* Name() const { return MakeString("SyncLocalMachineMsg"); }

        static NetMessage* NewNetMessage();
    };

    NetMessage* SyncMachineMsg::NewNetMessage(){
        return new SyncMachineMsg();
    }

    SyncMachineMsg::SyncMachineMsg(unsigned int ui, unsigned char uc, BandMachine* machine) : mMachineID(ui), mDirtyMask(uc), mMachineData(false) {
        machine->SyncSave(mMachineData, uc);
        mMachineData.Seek(0, BinStream::kSeekBegin);
    }

    void SyncMachineMsg::GetMachineData(BinStream& bs) const {
        bs.Write(&mMachineData.mBuffer[0], mMachineData.mBuffer.size());
    }

    void SyncMachineMsg::Save(BinStream& bs) const {
        bs << mMachineID;
        bs << mDirtyMask;
        bs << mMachineData.mBuffer.size();
        GetMachineData(bs);
    }

    void SyncMachineMsg::Load(BinStream& bs){
        bs >> mMachineID;
        bs >> mDirtyMask;
        int size;
        bs >> size;
        mMachineData.mBuffer.resize(size);
        bs.Read(&mMachineData.mBuffer[0], size);
    }

    void SyncMachineMsg::Dispatch(){
        BandMachineMgr* mgr = TheSessionMgr->mMachineMgr;
        RemoteBandMachine* machine = mgr->GetRemoteMachine(mMachineID, false);
        if(machine){
            static RemoteMachineUpdatedMsg msg(machine, mDirtyMask);
            msg[0] = machine;
            MemStream memstream(false);
            GetMachineData(memstream);
            memstream.Seek(0, BinStream::kSeekBegin);
            machine->SyncLoad(memstream, mDirtyMask);
            if(TheSessionMgr->IsLeaderLocal()){
                std::vector<RemoteBandUser*> remoteusers;
                TheBandUserMgr->GetRemoteBandUsers(&remoteusers, 0x4000);
                for(std::vector<RemoteBandUser*>::iterator it = remoteusers.begin(); it != remoteusers.end(); it){
                    if(mMachineID == (*it)->mMachineID){
                        it = remoteusers.erase(it);
                    }
                    else ++it;
                }
                TheSessionMgr->SendMsg(remoteusers, *this, (PacketType)1);
            }
            mgr->Export(msg, true);
        }
    }

    void SyncMachineMsg::Print(TextStream& ts) const {
        ts << MakeString("MachineID = %i, dirtyMask = %x\n", mMachineID, mDirtyMask);
    }

    NetMessage* SyncLocalMachineMsg::NewNetMessage(){
        return new SyncLocalMachineMsg();
    }
}

void BandMachineMgr::Init(){
    TheNetMessageFactory.RegisterNetMessage("SyncMachineMsg", SyncMachineMsg::NewNetMessage);
    TheNetMessageFactory.RegisterNetMessage("SyncLocalMachineMsg", SyncLocalMachineMsg::NewNetMessage);
}

BandMachineMgr::BandMachineMgr(SessionMgr* smgr, BandUserMgr* umgr) : mSessionMgr(smgr), mUserMgr(umgr) {
    ThePlatformMgr.AddSink(this);
    mSessionMgr->AddSink(this);
    SetName("machine_mgr", ObjectDir::Main());
    mLocalMachine = new LocalBandMachine(this);
    for(int i = 0; i < 3; i++){
        mRemoteMachines.push_back(new RemoteBandMachine());
    }
}

BandMachineMgr::~BandMachineMgr(){
    ThePlatformMgr.RemoveSink(this);
    mSessionMgr->RemoveSink(this);
    RELEASE(mLocalMachine);
}

LocalBandMachine* BandMachineMgr::GetLocalMachine() const { return mLocalMachine; }

void BandMachineMgr::GetMachines(std::vector<BandMachine*>& machines) const {
    machines.push_back(mLocalMachine);
    for(int i = 0; i < mRemoteMachines.size(); i++){
        if(mRemoteMachines[i]->IsActive()){
            machines.push_back(mRemoteMachines[i]);
        }
    }
}

RemoteBandMachine* BandMachineMgr::GetRemoteMachine(unsigned int id, bool fail) const {
    for(int i = 0; i < mRemoteMachines.size(); i++){
        if(mRemoteMachines[i]->IsActive() && mRemoteMachines[i]->GetMachineID() == id){
            return mRemoteMachines[i];
        }
    }
    if(fail) MILO_FAIL("No RemoteMachine with ID %i", id);
    return nullptr;
}

BandMachine* BandMachineMgr::GetUserMachine(const User* user) const {
    if(user->IsLocal()) return mLocalMachine;
    else return GetRemoteMachine(user->mMachineID, true);
}

DataNode BandMachineMgr::OnMsg(const ConnectionStatusChangedMsg&){
    RefreshPrimaryProfileInfo();
    return 1;
}

DataNode BandMachineMgr::OnMsg(const NewRemoteUserMsg& msg){
    RemoteUser* msgUser = msg.GetUser();
    unsigned int userID = msgUser->mMachineID;
    bool found = false;
    for(int i = 0; i < mRemoteMachines.size(); i++){
        if(mRemoteMachines[i]->IsActive() && userID == mRemoteMachines[i]->GetMachineID()){
            found = true;
            break;
        }
    }
    if(!found) AddRemoteMachine(userID);
    return 1;
}

void BandMachineMgr::AddRemoteMachine(unsigned int id){
    RemoteBandMachine* target = nullptr;
    bool found = false;
    for(int i = 0; i < mRemoteMachines.size(); i++){
        if(!mRemoteMachines[i]->IsActive()){
            mRemoteMachines[i]->Activate(id);
            found = true;
            target = mRemoteMachines[i];
            break;
        }
    }
    MILO_ASSERT(found, 0x107);
    static NewRemoteMachineMsg msg(target);
    msg[0] = target;
    Export(msg, true);
}

DataNode BandMachineMgr::OnMsg(const RemoteUserLeftMsg& msg){
    std::vector<BandUser*> bandusers;
    mUserMgr->GetBandUsersInSession(bandusers);
    bool remove = true;
    RemoteUser* target = msg.GetUser();
    unsigned int targetID = target->mMachineID;
    for(int i = 0; i < bandusers.size(); i++){
        if(targetID == bandusers[i]->mMachineID){
            remove = false;
            break;
        }
    }
    if(remove){
        RemoveRemoteMachine(targetID);
    }
    return 1;
}

void BandMachineMgr::RemoveRemoteMachine(unsigned int id){
    RemoteBandMachine* target = nullptr;
    for(int i = 0; i < mRemoteMachines.size(); i++){
        if(mRemoteMachines[i]->IsActive() && mRemoteMachines[i]->GetMachineID() == id){
            mRemoteMachines[i]->Deactivate();
            target = mRemoteMachines[i];
            break;
        }
    }
    if(target){
        static RemoteMachineLeftMsg msg(target);
        msg[0] = target;
        Export(msg, true);
    }
}

void BandMachineMgr::SyncLocalMachine(unsigned char mask){
    if(!mSessionMgr->IsLocal()){
        std::vector<LocalBandUser*> locals;
        mUserMgr->GetLocalBandUsersInSession(locals);
        MILO_ASSERT(!locals.empty(), 0x14B);
        SyncMachineMsg msg(locals.front()->mMachineID, mask, mLocalMachine);
        if(mSessionMgr->IsLeaderLocal()){
            mSessionMgr->SendMsgToAll(msg, (PacketType)1);
        }
        else if(mSessionMgr->GetLeaderUser()){
            mSessionMgr->SendMsg(mSessionMgr->GetLeaderUser(),msg, (PacketType)1);
        }
    }
    LocalBandMachine* machine = mLocalMachine;
    MILO_ASSERT(machine, 0x15D);
    static LocalMachineUpdatedMsg msg(machine, mask);
    Export(msg, true);
}

bool BandMachineMgr::IsSongShared(int songid) const {
    if(mSessionMgr->IsLocal()) return true;
    else {
        std::vector<BandMachine*> machines;
        GetMachines(machines);
        for(std::vector<BandMachine*>::iterator it = machines.begin(); it != machines.end(); ++it){
            if(!(*it)->HasSong(songid)) return false;
        }
    }
    return true;
}

bool BandMachineMgr::IsSongAllowedToHavePart(int songid, Symbol part) const {
    if(part != real_guitar && part != real_bass) return true;
    if(mSessionMgr->IsLocal()) return true;
    BandSongMetadata* data = (BandSongMetadata*)TheSongMgr->Data(songid);
    if(data && !data->IsDownload()) return true;
    std::vector<BandMachine*> machines;
    GetMachines(machines);
    for(std::vector<BandMachine*>::iterator it = machines.begin(); it != machines.end(); ++it){
        if(!(*it)->HasProGuitarOrBass(songid)) return false;
    }
    return true;
}

bool BandMachineMgr::AllMachinesHaveSameNetUIState() const {
    NetUIState target = mLocalMachine->GetNetUIState();
    std::vector<BandMachine*> machines;
    GetMachines(machines);
    for(int i = 0; i < machines.size(); i++){
        if(machines[i]->GetNetUIState() != target) return false;
    }
    return true;
}

DataNode BandMachineMgr::OnMsg(const ProcessedJoinRequestMsg& msg){
    if(msg.GetProcessed()){
        SyncLocalMachine(-1);
        SyncLocalMachineMsg msg;
        mSessionMgr->SendMsgToAll(msg, (PacketType)1);
    }
    return 1;
}

DataNode BandMachineMgr::ForEachMachine(const DataArray* arr){
    DataNode* var = arr->Var(2);
    DataNode local(*var);
    std::vector<BandMachine*> machines;
    GetMachines(machines);
    for(int i = 0; i < machines.size(); i++){
        *var = machines[i];
        for(int j = 3; j < arr->Size(); j++){
            arr->Command(j)->Execute();
        }
    }
    *var = local;
    return 0;
}

bool BandMachineMgr::IsLeaderMachineLocal() const {
    BandMachine* pLeaderMachine = GetLeaderMachine();
    MILO_ASSERT(pLeaderMachine, 0x1C9);
    LocalBandMachine* pLocalMachine = mLocalMachine;
    MILO_ASSERT(pLocalMachine, 0x1CC);
    return pLocalMachine == pLeaderMachine;
}

BandMachine* BandMachineMgr::GetLeaderMachine() const {
    if(TheSessionMgr->HasLeaderUser()){
        BandUser* pLeaderUser = TheSessionMgr->GetLeaderUser();
        MILO_ASSERT(pLeaderUser, 0x1D7);
        BandMachine* pLeaderMachine = GetUserMachine(pLeaderUser);
        MILO_ASSERT(pLeaderMachine, 0x1DA);
        return pLeaderMachine;
    }
    else return mLocalMachine;
}

String BandMachineMgr::GetLeaderPrimaryProfileName() const {
    BandMachine* pLeaderMachine = GetLeaderMachine();
    MILO_ASSERT(pLeaderMachine, 0x1E8);
    return pLeaderMachine->GetPrimaryProfileName();
}

String BandMachineMgr::GetLeaderPrimaryBandName() const {
    BandMachine* pLeaderMachine = GetLeaderMachine();
    MILO_ASSERT(pLeaderMachine, 0x1F0);
    return pLeaderMachine->GetPrimaryBandName();
}

int BandMachineMgr::GetLeaderPrimaryMetaScore() const {
    BandMachine* pLeaderMachine = GetLeaderMachine();
    MILO_ASSERT(pLeaderMachine, 0x1F8);
    return pLeaderMachine->mPrimaryMetaScore;
}

void BandMachineMgr::RefreshPrimaryProfileInfo(){
    BandProfile* profile = TheProfileMgr.GetPrimaryProfile();
    if(profile){
        LocalBandMachine* pLocalMachine = mLocalMachine;
        MILO_ASSERT(pLocalMachine, 0x203);
        pLocalMachine->SetPrimaryProfileName(profile->GetName());
        if(profile->IsBandNameProfanityChecked()){
            pLocalMachine->SetPrimaryBandName(profile->GetBandName());
        }
        else {
            pLocalMachine->SetPrimaryBandName("");
        }
        pLocalMachine->SetPrimaryMetaScore(TheCampaign->GetCampaignMetaScoreForProfile(profile));
    }
}

BEGIN_HANDLERS(BandMachineMgr)
    HANDLE_EXPR(foreach_machine, ForEachMachine(_msg))
    HANDLE_EXPR(get_user_machine, GetUserMachine(_msg->Obj<User>(2)))
    HANDLE_EXPR(get_leader_profile_name, GetLeaderPrimaryProfileName())
    HANDLE_EXPR(all_machines_have_same_net_ui_state, AllMachinesHaveSameNetUIState())
    HANDLE_MESSAGE(NewRemoteUserMsg)
    HANDLE_MESSAGE(RemoteUserLeftMsg)
    HANDLE_MESSAGE(ProcessedJoinRequestMsg)
    HANDLE_MESSAGE(ConnectionStatusChangedMsg)
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x22D)
END_HANDLERS