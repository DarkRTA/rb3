#include "char/CharIKMidi.h"

INIT_REVS(CharIKMidi)

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

BEGIN_LOADS(CharIKMidi)
    LOAD_REVS(bs)
    ASSERT_REVS(5, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mBone;
    if(gRev < 3){
        ObjVector<ObjPtr<RndTransformable, ObjectDir> > vec(this);
        bs >> vec;
        for(std::vector<ObjPtr<RndTransformable, ObjectDir> >::iterator it = vec.begin(); it != vec.end(); it++){
            delete (*it).Owner();
        }
    }
    if(gRev - 2 < 2){
        String asdf;
        bs >> asdf;
    }
    if(gRev > 4){
        bs >> mAnimBlender;
        bs >> mMaxAnimBlend;
    }
END_LOADS