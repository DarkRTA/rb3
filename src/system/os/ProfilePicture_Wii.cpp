#include "os/ProfilePicture.h"
#include "os/Debug.h"

ProfilePicture::ProfilePicture(int padnum, Hmx::Object* obj) : mState(kIdle), mUserID(), mUserPicture(0), mPadNum(padnum), mCallback(obj) {
    
}

void ProfilePicture::FetchUserData(){
    MILO_ASSERT(mState == kFetchingUserData, 0x18);
}

bool ProfilePicture::ReceiveUserData(){
    MILO_ASSERT(mState == kFetchingUserData, 0x1F);
    return true;
}

void ProfilePicture::FetchUserPicture(){
    MILO_ASSERT(mState == kFetchingUserPicture, 0x26);
}

bool ProfilePicture::ReceiveUserPicture(){
    MILO_ASSERT(mState == kFetchingUserPicture, 0x2D);
    return false;
}
