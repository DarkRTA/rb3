#include "char/CharIKMidi.h"

CharIKMidi::CharIKMidi() : mBone(this, 0), mCurSpot(this, 0), mNewSpot(this, 0), mSpotChanged(0), mAnimBlender(this, 0), mMaxAnimBlend(1.0f), mAnimFracPerBeat(0.0f), mAnimFrac(0.0f) {
    Enter();
}

CharIKMidi::~CharIKMidi(){

}

void CharIKMidi::Enter(){
    mCurSpot = 0;
    mNewSpot = 0;
    mSpotChanged = false;
    mFrac = 0.0f;
    mFracPerBeat = 0.0f;
    mLocalXfm.Reset();
    mOldLocalXfm.Reset();
    RndPollable::Enter();
}

void CharIKMidi::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mBone);
    changedBy.push_back(mBone);
    changedBy.push_back(mCurSpot);
}

SAVE_OBJ(CharIKMidi, 0xEA);