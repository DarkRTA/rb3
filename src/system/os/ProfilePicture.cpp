#include "os/ProfilePicture.h"
#include "os/PlatformMgr.h"

void ProfilePicture::Update(){

    switch(mState){
        case kComplete:
            OnlineID id;
            ThePlatformMgr.GetOnlineID(mPadNum, &id);
            if(id == mUserID) return;
            mUserID = id;
        case kIdle:
            mState = kFetchingUserData;
            FetchUserData();
            break;
        default: break;
    }
}

void ProfilePicture::Poll(){
    switch(mState){
        case kFetchingUserData:
            if(ReceiveUserData()){
                mState = kFetchingUserPicture;
                FetchUserPicture();
            }
            break;
        case kFetchingUserPicture:
            if(ReceiveUserPicture()){
                mState = kComplete;
                Succeed();
            }
            break;
        default: break;
    }
}

void ProfilePicture::Succeed(){
    MILO_ASSERT(mState == kComplete, 0x4A);
    ProfilePictureFetchedMsg msg(1);
    mCallback->Handle(msg.Data(), false);
}
