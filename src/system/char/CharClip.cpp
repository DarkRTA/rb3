#include "char/CharClip.h"

CharClip::Transitions::Transitions(Hmx::Object* o) : mNodeStart(0), mNodeEnd(0), mOwner(o) {

}

CharClip::CharClip() : mTransitions(this), mFramesPerSec(30.0f), mBeatTrack(), mFlags(0), mPlayFlags(0), mRange(0.0f), 
    mDirty(1), mDoNotCompress(0), unk42(-1), mRelative(this, 0), mBeatEvents(), mSyncAnim(this, 0), mFull(), mOne(), mFacing() {
    mBeatTrack.push_back(Key<float>());
    mBeatTrack.front().frame = 0.0f;
    mBeatTrack.front().value = 0.0f;
}