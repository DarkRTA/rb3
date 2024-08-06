#include "utl/Cache.h"
#include "os/Debug.h"
#include "os/Timer.h"
#include "os/ThreadCall.h"

int CacheID::GetDeviceID() const {
    MILO_FAIL("CacheID::GetDeviceID() not supported on this platform.\n");
    return -1;
}

Cache::Cache() : mOpCur(kOpNone), mLastResult(kCache_NoError) {

}

Cache::~Cache(){

}

bool Cache::IsDone(){
    return mOpCur == kOpNone;
}

CacheResult Cache::GetLastResult(){
    return mLastResult;
}

CacheResult Cache::WaitForResult() {
    while (mOpCur != kOpNone) {
        Timer::Sleep(0);
        ThreadCallPoll();
    }
    return mLastResult;
}
