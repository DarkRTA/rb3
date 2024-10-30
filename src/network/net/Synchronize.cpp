#include "net/Synchronize.h"
#include "net/NetSession.h"
#include "net/SyncStore.h"
#include "os/Debug.h"
#include "os/UserMgr.h"

Synchronizable::Synchronizable(const char* cc) : mDirtyMask(0) {
    if(strcmp(cc, "")) Publish(cc);
}

Synchronizable::~Synchronizable(){
    if(mTag.length() != 0) Unpublish();
}

void Synchronizable::Publish(const char* cc){
    MILO_ASSERT(mTag.length() == 0, 0x1E);
    mTag = cc;
    MILO_ASSERT(mTag.length(), 0x20);
    TheSyncStore->AddSyncObj(this, mTag);
}

void Synchronizable::Unpublish(){
    MILO_ASSERT(mTag.length(), 0x26);
    TheSyncStore->RemoveSyncObj(mTag);
    mTag = "";
}

void Synchronizable::SetSyncDirty(unsigned int ui, bool b){
    if(HasSyncPermission()){
        mDirtyMask |= ui;
        if(b) SynchronizeIfDirty();
    }
    else MILO_WARN("Obj %s cannot SetSyncDirty without permission!", mTag);
}

void Synchronizable::SynchronizeIfDirty(){
    while(!mDirtyUsers.empty()){
        User* u = TheUserMgr->GetUser(mDirtyUsers.back(), true);
        if(HasSyncPermission() && u){
            if(TheNetSession->HasUser(u) && ~(mDirtyMask)){
                SyncObjMsg msg(mTag, ~(mDirtyMask), this);
                TheNetSession->SendMsg(u, msg, kReliable);
            }
        }
        mDirtyUsers.pop_back();
    }
    if(mDirtyMask){
        if(HasSyncPermission()){
            SyncObjMsg msg(mTag, mDirtyMask, this);
            TheNetSession->SendMsgToAll(msg, kReliable);
            OnSynchronizing(mDirtyMask);
        }
        mDirtyMask = 0;
    }
}

const char* Synchronizable::GetUniqueTag() const { return mTag.c_str(); }

void Synchronizable::AddDirtyUser(const UserGuid& user){
    mDirtyUsers.push_back(user);
    SynchronizeIfDirty();
}