#include "char/CharIKSliderMidi.h"
#include "utl/Symbols.h"

INIT_REVS(CharIKSliderMidi)

CharIKSliderMidi::CharIKSliderMidi() : mTarget(this, 0), mFirstSpot(this, 0), mSecondSpot(this, 0), mTargetPercentage(1.0f), mPercentageChanged(0), mResetAll(1), mMe(this, 0), mTolerance(0.0f) {
    Enter();
}

CharIKSliderMidi::~CharIKSliderMidi(){

}

void CharIKSliderMidi::Enter(){
    mPercentageChanged = false;
    mFrac = 0.0f;
    mFracPerBeat = 0.0f;
    RndPollable::Enter();
}

void CharIKSliderMidi::SetName(const char* cc, class ObjectDir* dir){
    Hmx::Object::SetName(cc, dir);
    mMe = dynamic_cast<class Character*>(dir);
}

void CharIKSliderMidi::SetupTransforms(){ mResetAll = true; }

void CharIKSliderMidi::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mTarget);
    changedBy.push_back(mTarget);
    changedBy.push_back(mFirstSpot);
    changedBy.push_back(mSecondSpot);
}

SAVE_OBJ(CharIKSliderMidi, 0xC4)

void CharIKSliderMidi::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    Hmx::Object::Load(bs);
    if(gRev > 1) CharWeightable::Load(bs);
    bs >> mTarget;
    bs >> mFirstSpot;
    bs >> mSecondSpot;
    bs >> mTolerance;
}

BEGIN_COPYS(CharIKSliderMidi)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    GET_COPY(CharIKSliderMidi)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mTarget)
        COPY_MEMBER(mFirstSpot)
        COPY_MEMBER(mSecondSpot)
        COPY_MEMBER(mTolerance)
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(CharIKSliderMidi)
    HANDLE_ACTION(set_fraction, SetFraction(_msg->Float(2), _msg->Float(3)))
    HANDLE_ACTION(reset, SetupTransforms())
    HANDLE_SUPERCLASS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xF8)
END_HANDLERS

BEGIN_PROPSYNCS(CharIKSliderMidi)
    SYNC_PROP_MODIFY(target, mTarget, SetupTransforms())
    SYNC_PROP_MODIFY(first_spot, mFirstSpot, SetupTransforms())
    SYNC_PROP_MODIFY(second_spot, mSecondSpot, SetupTransforms())
    SYNC_PROP(tolerance, mTolerance)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS