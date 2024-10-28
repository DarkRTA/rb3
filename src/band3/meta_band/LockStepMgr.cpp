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
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include <cstddef>
#include <vector>

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
    mLockSuccess = true;
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
    if(!b) mLockSuccess = false;
    mWaitList.MarkMachineResponded(machine);
    CheckAllMachinesResponded();
}

void LockStepMgr::CheckAllMachinesResponded(){
    MILO_ASSERT(mLockMachine, 0x97);
    MILO_ASSERT(mLockMachine->IsLocal(), 0x98);
    if(mWaitList.HaveAllMachinesResponded()){
        static ReleasingLockStepMsg releaseMsg(false);
        releaseMsg[0] = mLockSuccess;
        mCallback->Handle(releaseMsg, false);
        EndLockMsg msg(Name(), mLockSuccess);
        TheNetSession->SendMsgToAll(msg, kReliable);
        ReleaseLock(mLockSuccess);
    }
}

void LockStepMgr::ReleaseLock(bool b){
    mLockMachine = nullptr;
    mWaitList.Clear();
    mHasResponded = false;
    static LockStepCompleteMsg lsc(false);
    lsc[0] = b;
    mCallback->Handle(lsc, true);
}

void LockStepMgr::OnEndLockMsg(bool b){
    ReleaseLock(b);
}

DataNode LockStepMgr::OnMsg(const RemoteMachineLeftMsg& msg){
    if(mLockMachine){
        RemoteBandMachine* machine = msg.GetMachine();
        if(mLockMachine->IsLocal() && mWaitList.GetWaitingMachine(machine)){
            mWaitList.RemoveMachine(machine);
            CheckAllMachinesResponded();
        }
        else {
            if(mLockMachine == machine){
                ReleaseLock(mLockSuccess);
            }
        }
    }
    return 1;
}

BEGIN_HANDLERS(LockStepMgr)
    HANDLE_ACTION(start_lock, StartLock())
    HANDLE_EXPR(in_lock, mLockMachine != nullptr)
    HANDLE_MESSAGE(RemoteMachineLeftMsg)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xDB)
END_HANDLERS

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

LockResponseMsg::LockResponseMsg(bool locked, LocalBandMachine* machine, const char* name){
    std::vector<LocalBandUser*> users;
    TheBandUserMgr->GetLocalParticipants(users);
    if(users.empty()) mResponseMachineID = 0;
    else mResponseMachineID = users.front()->mMachineID;
    mLocked = locked;
    mLockStepName = name;
}

void LockResponseMsg::Save(BinStream& bs) const {
    bs << mLocked;
    bs << mResponseMachineID;
    bs << mLockStepName;
}

void LockResponseMsg::Load(BinStream& bs){
    bs >> mLocked;
    bs >> mResponseMachineID;
    bs >> mLockStepName;
}

void LockResponseMsg::Dispatch(){
    RemoteBandMachine* machine = TheSessionMgr->mMachineMgr->GetRemoteMachine(mResponseMachineID, true);
    LockStepMgr* mgr = ObjectDir::Main()->Find<LockStepMgr>(mLockStepName.c_str(), true);
    mgr->OnLockResponseMsg(mLocked, machine);
}

EndLockMsg::EndLockMsg(const char* name, bool success) : mLockStepName(name), mSuccess(success) {

}

void EndLockMsg::Save(BinStream& bs) const {
    bs << mLockStepName;
    bs << mSuccess;
}

void EndLockMsg::Load(BinStream& bs){
    bs >> mLockStepName;
    bs >> mSuccess;
}

void EndLockMsg::Dispatch(){
    LockStepMgr* mgr = ObjectDir::Main()->Find<LockStepMgr>(mLockStepName.c_str(), true);
    mgr->OnEndLockMsg(mSuccess);
}

void LockStepMgr::WaitList::AddMachine(BandMachine* machine){
    WaitingMachine wm(machine);
    mList.push_back(wm);
}

void LockStepMgr::WaitList::RemoveMachine(BandMachine* machine){
    for(std::vector<WaitingMachine>::iterator it = mList.begin(); it != mList.end(); ++it){
        if(it->mMachine == machine){
            mList.erase(it);
            return;
        }
    }
    MILO_FAIL("Machine is not in WaitList");
}

void LockStepMgr::WaitList::MarkMachineResponded(BandMachine* machine){
    MILO_ASSERT(GetWaitingMachine(machine) != NULL, 0x168);
    for(int i = 0; i < mList.size(); i++){
        if(mList[i].mMachine == machine){
            mList[i].mResponded = true;
        }
    }
}

void LockStepMgr::WaitList::Clear(){
    mList.clear();
}

bool LockStepMgr::WaitList::HaveAllMachinesResponded() const {
    for(int i = 0; i < mList.size(); i++){
        if(!mList[i].mResponded) return false;
    }
    return true;
}

const LockStepMgr::WaitList::WaitingMachine* LockStepMgr::WaitList::GetWaitingMachine(BandMachine* machine) const {
    for(int i = 0; i < mList.size(); i++){
        if(mList[i].mMachine == machine) return &mList[i];
    }
    return nullptr;
}