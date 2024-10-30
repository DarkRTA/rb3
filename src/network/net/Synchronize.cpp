#include "net/Synchronize.h"
#include "os/Debug.h"

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
}

void Synchronizable::Unpublish(){
    MILO_ASSERT(mTag.length(), 0x26);
    mTag = "";
}

void Synchronizable::SetSyncDirty(unsigned int ui, bool b){
    if(HasSyncPermission()){
        mDirtyMask |= ui;
        if(b) SynchronizeIfDirty();
    }
    else MILO_WARN("Obj %s cannot SetSyncDirty without permission!", mTag);
}

const char* Synchronizable::GetUniqueTag() const { return mTag.c_str(); }

void Synchronizable::AddDirtyUser(const UserGuid& user){
    mDirtyUsers.push_back(user);
    SynchronizeIfDirty();
}