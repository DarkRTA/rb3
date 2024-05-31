#include "meta/Profile.h"
#include "os/Debug.h"
#include "meta/WiiProfileMgr.h"
#include "utl/Symbols.h"

#include "decomp.h"

static const char* profileSymbols[] = { __FILE__, "user" };

Profile::Profile(int pnum) : mDirty(0), mPadNum(pnum), mState(kMetaProfileUnloaded) {

}

Profile::~Profile(){
    DeleteAll();
}

bool Profile::IsAutosaveEnabled() const {
    return mState != kMetaProfileError;
}

bool Profile::HasValidSaveData() const {
    if(mState == kMetaProfileLoaded || mState == kMetaProfileError){
        int padIdx = TheWiiProfileMgr.GetIndexForPad(mPadNum);
        return TheWiiProfileMgr.IsIndexValid(padIdx);
    }
    else return false;
}

#pragma push
#pragma dont_inline on
// Force ordering of GetName/GetPadNum
DECOMP_FORCEFUNC(Profile, Profile, GetName());
DECOMP_FORCEFUNC(Profile, Profile, GetPadNum());
#pragma pop

// const char* Profile::GetName() const {
//     LocalUser* u = TheUserMgr->GetLocalUserFromPadNum(mPadNum);
//     return u->UserName();
// }

// int Profile::GetPadNum() const {
//     return mPadNum;
// }

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

BEGIN_HANDLERS(Profile)
    HANDLE_EXPR(get_pad_num, GetPadNum())
    HANDLE_EXPR(get_name, GetName())
    HANDLE_EXPR(has_cheated, HasCheated())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xC3)
END_HANDLERS
