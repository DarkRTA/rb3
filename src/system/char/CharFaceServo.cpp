#include "char/CharFaceServo.h"
#include "char/CharClip.h"
#include "os/Debug.h"

CharFaceServo::CharFaceServo() : mClips(this, 0), mBaseClip(this, 0), mBlinkClipLeft(this, 0), mBlinkClipLeft2(this, 0), mBlinkClipRight(this, 0), mBlinkClipRight2(this, 0),
    mBlinkWeightLeft(0.0f), mBlinkWeightRight(0.0f), mNeedScaleDown(0), mProceduralBlinkWeight(0.0f), mAppliedProceduralBlink(0) {

}

CharFaceServo::~CharFaceServo(){

}
