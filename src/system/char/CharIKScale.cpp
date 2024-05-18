#include "char/CharIKScale.h"

CharIKScale::CharIKScale() : mDest(this, 0), mScale(1.0f), mSecondaryTargets(this, kObjListNoNull), mBottomHeight(0.0f), mTopHeight(0.0f), mAutoWeight(0) {

}

CharIKScale::~CharIKScale(){
    
}