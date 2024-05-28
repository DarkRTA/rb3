#include "os/PlatformMgr.h"

PlatformMgr::PlatformMgr() : mSigninMask(0), mSigninChangeMask(0), mGuideShowing(0), mConnected(0), unk2a(0), unk2b(0), mRegion(kRegionNone), unk30(0), 
    mTimer(), unk6a(0), unk6d(0), unk68(0), unk69(0), unk6b(0), unk6c(0), unk70(0), unk74(0), unk43a0(0), unk43a1(0), unk43a2(0), unk43a3(0),
    unkca10(0), unkca11(0), unkca12(0), unkca14(0), unkce4c(0), unkce55(0), unkce56(0), unkce57(0), unkce58(0), unkce59(0), unkce5a(0),
    unkce5c(0), unkce60(0), unkce64(0), unkce68(1), unkce69(0), unkce6a(0) {
    unkca18 = 0;
}