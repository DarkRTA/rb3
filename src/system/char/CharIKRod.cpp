#include "char/CharIKRod.h"

CharIKRod::CharIKRod() : mLeftEnd(this, 0), mRightEnd(this, 0), mDestPos(0.5f), mSideAxis(this, 0), mVertical(0), mDest(this, 0) {

}

CharIKRod::~CharIKRod(){

}