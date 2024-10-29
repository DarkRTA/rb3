#include "net/SyncStore.h"
#include "NetMessage.h"
#include "net/Synchronize.h"
#include "os/Debug.h"
#include "os/User.h"
#include "os/UserMgr.h"
#include "utl/BinStream.h"
#include "utl/MakeString.h"
#include "utl/MemStream.h"

SyncStore* TheSyncStore;

NetMessage* SyncObjMsg::NewNetMessage(){ return new SyncObjMsg(); }
NetMessage* SyncUserMsg::NewNetMessage(){ return new SyncUserMsg(); }
NetMessage* SyncAllMsg::NewNetMessage(){ return new SyncAllMsg(); }

SyncStore::SyncStore(){
    MILO_ASSERT(!TheSyncStore, 0x13);
    TheSyncStore = this;
    SyncObjMsg::Register();
    SyncUserMsg::Register();
    SyncAllMsg::Register();
}

void SyncStore::Poll(){
    for(int i = 0; i < mSyncObjs.size(); i++){
        mSyncObjs[i]->SynchronizeIfDirty();
    }
}

void SyncStore::AddSyncObj(Synchronizable* sync, String& str){
    for(int i = 0; i < mSyncObjs.size(); i++){
        if(str == mSyncObjs[i]->GetUniqueTag()){
            MILO_FAIL("A sync obj already has the ID %s", str);
        }
    }
    mSyncObjs.push_back(sync);
}

void SyncStore::RemoveSyncObj(String& str){
    for(std::vector<Synchronizable*>::iterator it = mSyncObjs.begin(); it != mSyncObjs.end(); ++it){
        if(str == (*it)->GetUniqueTag()){
            mSyncObjs.erase(it);
            return;
        }
    }
    MILO_FAIL("Cannot find obj %s to remove from sync obj store", str);
}

Synchronizable* SyncStore::GetSyncObj(String& str){
    for(int i = 0; i < mSyncObjs.size(); i++){
        if(str == mSyncObjs[i]->GetUniqueTag()) return mSyncObjs[i];
    }
    MILO_FAIL("Sync Obj %s is not in our store", str);
    return nullptr;
}

void SyncStore::SyncUser(const User* user){
    for(int i = 0; i < mSyncObjs.size(); i++){
        if(mSyncObjs[i]->HasSyncPermission()){
            mSyncObjs[i]->AddDirtyUser(user->mUserGuid);
        }
    }
}

void SyncStore::SyncAllUsers(){
    for(int i = 0; i < mSyncObjs.size(); i++){
        if(mSyncObjs[i]->HasSyncPermission()){
            mSyncObjs[i]->SetSyncDirty(-1, false);
        }
    }
}

SyncObjMsg::SyncObjMsg(String& tag, unsigned int mask, Synchronizable* sync) : mObjTag(tag), mDirtyMask(mask), mObjData(false) {
    sync->SyncSave(mObjData, mask);
    mObjData.Seek(0, BinStream::kSeekBegin);
}

void SyncObjMsg::GetObjData(BinStream& bs) const {
    bs.Write(mObjData.Buffer(), mObjData.BufferSize());
}

void SyncObjMsg::Save(BinStream& bs) const {
    bs << mObjTag;
    bs << mDirtyMask;
    bs << mObjData.BufferSize();
    GetObjData(bs);
}

void SyncObjMsg::Load(BinStream& bs){
    bs >> mObjTag;
    bs >> mDirtyMask;
    int size;
    bs >> size;
    mObjData.Resize(size);
    bs.Read((void*)mObjData.Buffer(), size);
}

void SyncObjMsg::Dispatch(){
    Synchronizable* syncObj = TheSyncStore->GetSyncObj(mObjTag);
    MemStream stream(false);
    GetObjData(stream);
    stream.Seek(0, BinStream::kSeekBegin);
    syncObj->SyncLoad(stream, mDirtyMask);
    if(syncObj->HasSyncPermission()){
        MILO_WARN("Obj %s has sync permission on multiple machines!", mObjTag);
    }
    syncObj->OnSynchronized(mDirtyMask);
}

void SyncObjMsg::Print(TextStream& ts) const {
    ts << MakeString("SyncObj tag = %s, dirtyMask = %x\n", mObjTag, mDirtyMask);
}

SyncUserMsg::SyncUserMsg(const User* user){
    mUserGuid = user->mUserGuid;
}

void SyncUserMsg::Save(BinStream& bs) const {
    bs << mUserGuid;
}

void SyncUserMsg::Load(BinStream& bs){
    bs >> mUserGuid;
}

void SyncUserMsg::Dispatch(){
    User* user = TheUserMgr->GetUser(mUserGuid, true);
    MILO_ASSERT(user, 0xA8);
    MILO_ASSERT(!user->IsLocal(), 0xA9);
    TheSyncStore->SyncUser(user);
}

void SyncAllMsg::Dispatch(){
    TheSyncStore->SyncAllUsers();
}