#include "StoreEnumeration.h"

WiiEnumeration::WiiEnumeration(int i) : mLoading(true) {
    if (i != 0) mState = kEnumWaiting;
    else mState = kPreSuccess;
}

void WiiEnumeration::Start() {

}

bool WiiEnumeration::IsSuccess() const {
    return mState == kSuccess;
}

int WiiEnumeration::IsEnumerating() const {
    return (mState != kSuccess && mState != kFail) ? true : false;
}

void WiiEnumeration::Poll() {
    if (mState == kEnumWaiting) {
        
    }
}
