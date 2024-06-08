#include "ui/UIProxy.h"

UIProxy::UIProxy() : mDir(0), mEnv(this, 0), mMainTrans(0), mSyncOnMove(0), mPolled(0) {
    mOldXfm.Reset();
    mOldXfm.v.x = -1.0E+30f;
}