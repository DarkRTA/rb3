#include "meta/Profile.h"
#include "os/Debug.h"

Profile::Profile(int pnum) : mDirty(0), mPadNum(pnum), mState(kMetaProfileUnloaded) {
    
}

Profile::~Profile(){
    DeleteAll();
}

bool Profile::IsAutosaveEnabled() const {
    return mState != kMetaProfileError;
}

int Profile::GetPadNum() const {
    return mPadNum;
}

ProfileSaveState Profile::GetSaveState() const {
    return mState;
}

void Profile::SetSaveState(ProfileSaveState state){
    MILO_ASSERT(mState != kMetaProfileUnchanged, 0x88);
    if(state != kMetaProfileUnchanged) mState = state;
}

bool Profile::IsUnsaved() const {
    bool cheated = HasCheated();
    if(!cheated) return mDirty;
    else return false;
}

void Profile::SaveLoadComplete(ProfileSaveState state){
    SetSaveState(state);
}

bool Profile::HasSomethingToUpload(){
    return false;
}

void Profile::DeleteAll(){
    mDirty = true;
}

void Profile::MakeDirty(){
    mDirty = true;
}
