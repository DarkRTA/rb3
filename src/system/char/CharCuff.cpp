#include "char/CharCuff.h"

CharCuff::CharCuff() : mOpenEnd(0), mIgnore(this, kObjListNoNull), mBone(this, 0), mEccentricity(1.0f), mCategory() {
    mShape[0].offset = -2.9f;
    mShape[0].radius = 1.9f;

    mShape[1].offset = 0.0f;
    mShape[1].radius = 2.6f;

    mShape[2].offset = 2.0f;
    mShape[2].radius = 3.5f;

    mOuterRadius = 2.6f + 0.5f;
}

CharCuff::~CharCuff(){
    
}