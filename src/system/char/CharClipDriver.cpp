#include "char/CharClipDriver.h"

CharClipDriver::CharClipDriver(Hmx::Object* owner, CharClip* clip, int mask, float blendwidth, CharClipDriver* next, float f2, float f3, bool multclips) :
    mPlayFlags(clip->mPlayFlags), mBlendWidth(blendwidth), mTimeScale(1.0f), mDBeat(0), mAdvanceBeat(0),
    mClip(owner, clip), mNext(next), mNextEvent(-1), mPlayMultipleClips(multclips) {
    if(mask & 0xF0U) mPlayFlags = mPlayFlags & 0xffffff0f | mask & 0xf0U;
    if(mask & 0xFU) mPlayFlags = mPlayFlags & 0xfffffff0 | mask & 0xfU;
    if(mask & 0xF600U) mPlayFlags = mPlayFlags & 0xffff09ff | mask & 0xf600U;

}

CharClipDriver::~CharClipDriver(){}

CharClipDriver* CharClipDriver::Exit(bool b){
    static Symbol exit("exit");
    if(b && mNext){
        mNext = mNext->Exit(b);
    }
    CharClipDriver* ret = mNext;
    ExecuteEvent(exit);
    RndAnimatable* syncanim = mClip->mSyncAnim;
    if(syncanim) syncanim->EndAnim();
    delete this;
    return ret;
}

void CharClipDriver::DeleteStack(){
    if(mNext) mNext->DeleteStack();
    delete this;
}

CharClipDriver* CharClipDriver::DeleteClip(Hmx::Object* obj){
    if(mClip == obj) return Exit(false);
    else if(mNext) mNext = mNext->DeleteClip(obj);
    return this;
}