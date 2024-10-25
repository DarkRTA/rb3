#include "meta_band/BandMachineMgr.h"
#include "BandMachine.h"
#include "game/BandUserMgr.h"
#include "game/NetGameMsgs.h"
#include "meta_band/SessionMgr.h"
#include "net/NetMessage.h"
#include "obj/Dir.h"
#include "os/PlatformMgr.h"
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