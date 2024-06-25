#include "char/CharDriver.h"
#include "char/CharClip.h"
#include "os/Debug.h"

CharDriver::CharDriver() : mBones(this, 0), mClips(this, 0), mFirst(0), mTestClip(this, 0), mDefaultClip(this, 0),
    mDefaultPlayStarved(0), mStarvedHandler(), mLastNode(0), mOldBeat(1e+30f), mRealign(0), mBeatScale(1.0f), mBlendWidth(1.0f),
    mClipType(), mApply(kApplyBlend), mInternalBones(0), mPlayMultipleClips(0) {

}

CharDriver::~CharDriver(){

}

void CharDriver::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mBones);
}
