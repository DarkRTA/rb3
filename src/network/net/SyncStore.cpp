#include "net/SyncStore.h"
#include "NetMessage.h"
#include "os/Debug.h"
#include "utl/BinStream.h"

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

SyncObjMsg::SyncObjMsg(String& tag, unsigned int mask, Synchronizable* sync) : mObjTag(tag), mDirtyMask(mask), mObjData(false) {
    sync->SyncSave(mObjData, mask);
    mObjData.Seek(0, BinStream::kSeekBegin);
}
