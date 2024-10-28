#include "meta_band/LockStepMgr.h"
#include "LockMessages.h"
#include "LockStepMgr.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/NetGameMsgs.h"
#include "meta_band/BandMachine.h"
#include "meta_band/SessionMgr.h"
#include "net/NetSession.h"
#include "obj/Dir.h"
#include "os/Debug.h"

NetMessage* BasicStartLockMsg::NewNetMessage(){ return new BasicStartLockMsg(); }
NetMessage* LockResponseMsg::NewNetMessage(){ return new LockResponseMsg(); }
NetMessage* EndLockMsg::NewNetMessage(){ return new EndLockMsg(); }

LockStepStartMsg::LockStepStartMsg(LockData* data) : Message(Type(), data){}
LockData* LockStepStartMsg::GetLockData() const { return mData->Obj<LockData>(2); }

void LockStepMgr::Init(){
    BasicStartLockMsg::Register();
    LockResponseMsg::Register();
    EndLockMsg::Register();
}

LockStepMgr::LockStepMgr(const char* cc, Hmx::Object* o) : mLockMachine(0), mHasResponded(0), mCallback(o) {
    SetName(cc, ObjectDir::Main());
    TheNetSession->AddSink(this);
    if(TheSessionMgr){
        TheSessionMgr->mMachineMgr->AddSink(this);
    }
}

LockStepMgr::~LockStepMgr(){
    if(TheSessionMgr) TheSessionMgr->mMachineMgr->RemoveSink(this);
    TheNetSession->RemoveSink(this);
}

bool LockStepMgr::InLock() const { return mLockMachine; }

void LockStepMgr::StartLock(){
    BasicStartLockMsg msg;
    StartLock(msg);
}

void LockStepMgr::StartLock(StartLockMsg& msg){
    MILO_ASSERT(!mLockMachine, 0x4B);
    unk29 = true;
    std::vector<BandMachine*> machines;
    TheSessionMgr->mMachineMgr->GetMachines(machines);
    for(int i = 0; i < machines.size(); i++){
        mWaitList.AddMachine(machines[i]);
    }
    LocalBandMachine* localmachine = TheSessionMgr->mMachineMgr->GetLocalMachine();
    msg.SetLockInfo(localmachine, Name());
    TheNetSession->SendMsgToAll(msg, kReliable);
    OnStartLockMsg(localmachine, msg.GetLockData());
}

void LockStepMgr::OnStartLockMsg(BandMachine* machine, LockData* data){
    MILO_ASSERT(!mLockMachine, 0x64);
    mLockMachine = machine;
    static LockStepStartMsg startMsg(data);
    startMsg[0] = data;
    mCallback->Handle(startMsg, true);
}

void LockStepMgr::RespondToLock(bool b){
    MILO_ASSERT(mLockMachine, 0x70);
    MILO_ASSERT(!HasResponded(), 0x71);
    mHasResponded = true;
    LocalBandMachine* localmachine = TheSessionMgr->mMachineMgr->GetLocalMachine();
    if(mLockMachine->IsLocal()){
        OnLockResponseMsg(b, localmachine);
    }
    else {
        RemoteBandMachine* remoteLockMachine = dynamic_cast<RemoteBandMachine*>(mLockMachine);
        MILO_ASSERT(remoteLockMachine, 0x80);
        LockResponseMsg msg(b, localmachine, Name());
        TheSessionMgr->SendMsg(remoteLockMachine, msg, kReliable);
    }
}

void LockStepMgr::OnLockResponseMsg(bool b, BandMachine* machine){
    MILO_ASSERT(mLockMachine, 0x89);
    MILO_ASSERT(mLockMachine->IsLocal(), 0x8A);
    if(!b) unk29 = false;
    mWaitList.MarkMachineResponded(machine);
    CheckAllMachinesResponded();
}

void LockStepMgr::CheckAllMachinesResponded(){
    MILO_ASSERT(mLockMachine, 0x97);
    MILO_ASSERT(mLockMachine->IsLocal(), 0x98);
    if(mWaitList.HaveAllMachinesResponded()){
        static ReleasingLockStepMsg releaseMsg(false);
        releaseMsg[0] = unk29;
        mCallback->Handle(releaseMsg, false);
        EndLockMsg msg(Name(), unk29);
        TheNetSession->SendMsgToAll(msg, kReliable);
        ReleaseLock(unk29);
    }
}

void StartLockMsg::SetLockInfo(LocalBandMachine* machine, const char* name){
    std::vector<LocalBandUser*> users;
    TheBandUserMgr->GetLocalParticipants(users);
    if(users.empty()) mLockMachineID = 0;
    else mLockMachineID = users.front()->mMachineID;
    mLockStepName = name;
}

void StartLockMsg::Save(BinStream& bs) const {
    bs << mLockMachineID;
    bs << mLockStepName;
}

void StartLockMsg::Load(BinStream& bs){
    bs >> mLockMachineID;
    bs >> mLockStepName;
}

void StartLockMsg::Dispatch(){
    RemoteBandMachine* machine = TheSessionMgr->mMachineMgr->GetRemoteMachine(mLockMachineID, true);
    LockStepMgr* mgr = ObjectDir::Main()->Find<LockStepMgr>(mLockStepName.c_str(), true);
    mgr->OnStartLockMsg(machine, GetLockData());
}