#include "meta_band/BandMachineMgr.h"
#include "BandMachine.h"
#include "BandMachineMgr.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/NetGameMsgs.h"
#include "meta_band/SessionMgr.h"
#include "net/NetMessage.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/User.h"
#include "utl/BinStream.h"
#include "utl/MemStream.h"
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
        virtual int ByteCode() const { return TheNetMessageFactory.GetNetMessageByteCode("SyncMachineMsg"); }
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
        virtual void Dispatch(){ TheSessionMgr->unk50->SyncLocalMachine(-1); }
        virtual int ByteCode() const { return TheNetMessageFactory.GetNetMessageByteCode("SyncLocalMachineMsg"); }
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
        BandMachineMgr* mgr = TheSessionMgr->unk50;
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