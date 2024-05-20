#include "char/CharLipSync.h"

INIT_REVS(CharLipSync)

CharLipSync::Generator::Generator() : mLipSync(0), mLastCount(0), mWeights() {

}

CharLipSync::CharLipSync() : mPropAnim(this, 0), mFrames(0) {

}

CharLipSync::~CharLipSync(){

}

SAVE_OBJ(CharLipSync, 0x155)

BEGIN_LOADS(CharLipSync)
    LOAD_REVS(bs)
    ASSERT_REVS(1, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mVisemes;
    bs >> mFrames;
    bs >> mData;
    if(gRev != 0) bs >> mPropAnim;
END_LOADS