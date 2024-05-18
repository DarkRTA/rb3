#include "char/CharLipSync.h"

CharLipSync::Generator::Generator() : mLipSync(0), mLastCount(0), mWeights() {

}

CharLipSync::CharLipSync() : mPropAnim(this, 0), mFrames(0) {

}

CharLipSync::~CharLipSync(){

}

SAVE_OBJ(CharLipSync, 0x155)