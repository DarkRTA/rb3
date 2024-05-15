#include "char/CharSleeve.h"

CharSleeve::CharSleeve() : mSleeve(this, 0), mTopSleeve(this, 0), mPos(0.0f, 0.0f, 0.0f), mLastPos(0.0f, 0.0f, 0.0f),
    mLastDT(0.0f), mInertia(0.5f), mGravity(1.0f), mRange(0.0f), mNegLength(0.0f), mPosLength(0.0f), mStiffness(0.02f), mMe(this, 0) {

}

CharSleeve::~CharSleeve(){

}

void CharSleeve::SetName(const char* cc, ObjectDir* dir){
    Hmx::Object::SetName(cc, dir);
    mMe = dynamic_cast<Character*>(dir);
}