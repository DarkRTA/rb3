#include "rndobj/Flare.h"

RndFlare::RndFlare() : mPointTest(1), mAreaTest(1), mVisible(0), mSizes(0.1f, 0.1f), mMat(this, 0), mRange(0.0f, 0.0f), mOffset(0.0f), mSteps(1), mStep(0), unkec(0.0f), unk114(1.0f, 1.0f) {
    mTestDone = 0;
    mLastDone = 0;
    mMatrix.Identity();
}
