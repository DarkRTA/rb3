#include "rndobj/PropKeys.h"

unsigned short PropKeys::gRev = 0;

PropKeys::PropKeys(Hmx::Object* o1, Hmx::Object* o2) : mTarget(o1, o2), mProp(0), mKeysType(kFloat), mInterpHandler(), mLastKeyFrameIndex(-2) {
    
}

PropKeys::~PropKeys(){
    if(mProp){
        mProp->Release();
        mProp = 0;
    }
}
