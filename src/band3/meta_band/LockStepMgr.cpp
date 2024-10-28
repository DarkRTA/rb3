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

LockStepMgr::LockStepMgr(const char* cc, Hmx::Object* o) : mLockMachine(0), unk28(0), unk2c(o) {
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