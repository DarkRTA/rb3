#include "utl/Cache.h"
#include "os/Debug.h"

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
