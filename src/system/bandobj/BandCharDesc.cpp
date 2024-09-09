#include "bandobj/BandCharDesc.h"

BandCharDesc::Outfit::Outfit(){
    
}

BandCharDesc::BandCharDesc() : mGender("male"), mSkinColor(3) {

}

BandCharDesc::Head::Head() : mHide(0), mEyeColor(0), mShape(0), mChin(0), mChinWidth(0.5f), mChinHeight(0.5f), mJawWidth(0.5f), mJawHeight(0.5f),
    mNose(0), mNoseWidth(0.5f), mNoseHeight(0.5f), mEye(0), mEyeSeparation(0.5f), mEyeHeight(0.5f), mEyeRotation(0.5f), mMouth(0),
    mMouthWidth(0.5f), mMouthHeight(0.5f), mBrowSeparation(0.5f), mBrowHeight(0.5f) {
    // mSaveSizeMethod = &SaveSize;
}