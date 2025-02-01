#include "char/CharIKSliderMidi.h"
#include "math/Utl.h"
#include "obj/Task.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

INIT_REVS(CharIKSliderMidi)

CharIKSliderMidi::CharIKSliderMidi()
    : mTarget(this, 0), mFirstSpot(this, 0), mSecondSpot(this, 0),
      mTargetPercentage(1.0f), mPercentageChanged(0), mResetAll(1), mMe(this, 0),
      mTolerance(0.0f) {
    Enter();
}

CharIKSliderMidi::~CharIKSliderMidi() {}

void CharIKSliderMidi::Enter() {
    mPercentageChanged = false;
    mFrac = 0.0f;
    mFracPerBeat = 0.0f;
    RndPollable::Enter();
}

void CharIKSliderMidi::SetName(const char *cc, class ObjectDir *dir) {
    Hmx::Object::SetName(cc, dir);
    mMe = dynamic_cast<class Character *>(dir);
}

void CharIKSliderMidi::SetupTransforms() { mResetAll = true; }

void CharIKSliderMidi::SetFraction(float f1, float f2) {
    if (f1 != mTargetPercentage) {
        if (std::fabs(f1 - mTargetPercentage) < mTolerance)
            return;
        else {
            mOldPercentage = mTargetPercentage;
            mTargetPercentage = f1;
            if (f2 <= 0)
                mFracPerBeat = kHugeFloat;
            else {
                MaxEq(f2, 0.1f);
                mFracPerBeat = 1.0f / f2;
            }
            mFrac = 0;
            mPercentageChanged = true;
        }
    }
}

void CharIKSliderMidi::Poll() {
    if (!mTarget || !mFirstSpot || !mSecondSpot)
        return;
    else {
        float weight = Weight();
        if (weight != 0) {
            if (mMe && mMe->Teleported())
                mResetAll = true;
            if (mResetAll) {
                Interp(
                    mFirstSpot->WorldXfm().v,
                    mSecondSpot->WorldXfm().v,
                    mTargetPercentage,
                    mOldPos
                );
                Interp(
                    mFirstSpot->WorldXfm().v,
                    mSecondSpot->WorldXfm().v,
                    mTargetPercentage,
                    mDestPos
                );
                mResetAll = false;
            }
            if (mPercentageChanged) {
                mPercentageChanged = false;
                mOldPos = mDestPos;
            }
            Interp(
                mFirstSpot->WorldXfm().v,
                mSecondSpot->WorldXfm().v,
                mTargetPercentage,
                mDestPos
            );
            mFrac += mFracPerBeat * TheTaskMgr.DeltaBeat();
            ClampEq<float>(mFrac, 0, 1);
            Interp(mOldPos, mDestPos, Sigmoid(mFrac), mCurPos);
            if (weight < 1.0f) {
                Interp(mTarget->WorldXfm().v, mCurPos, weight, mCurPos);
            }
            Transform tf48;
            Invert(mTarget->TransParent()->WorldXfm(), tf48);
            Vector3 v58;
            Multiply(mCurPos, tf48, v58);
            mTarget->SetLocalPos(v58);
        }
    }
}

void CharIKSliderMidi::Highlight() {
#ifdef MILO_DEBUG
    UtilDrawSphere(mFirstSpot->WorldXfm().v, 1.0f, Hmx::Color(1, 1, 1));
    UtilDrawSphere(mSecondSpot->WorldXfm().v, 1.0f, Hmx::Color(1, 1, 1));
    UtilDrawSphere(mDestPos, 1.0f, Hmx::Color(1, 0, 0));
    UtilDrawSphere(mCurPos, 1.0f, Hmx::Color(0, 1, 0));
#endif
}

void CharIKSliderMidi::PollDeps(
    std::list<Hmx::Object *> &changedBy, std::list<Hmx::Object *> &change
) {
    change.push_back(mTarget);
    changedBy.push_back(mTarget);
    changedBy.push_back(mFirstSpot);
    changedBy.push_back(mSecondSpot);
}

SAVE_OBJ(CharIKSliderMidi, 0xC4)

void CharIKSliderMidi::Load(BinStream &bs) {
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    Hmx::Object::Load(bs);
    if (gRev > 1)
        CharWeightable::Load(bs);
    bs >> mTarget;
    bs >> mFirstSpot;
    bs >> mSecondSpot;
    bs >> mTolerance;
}

BEGIN_COPYS(CharIKSliderMidi)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    CREATE_COPY(CharIKSliderMidi)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mTarget)
        COPY_MEMBER(mFirstSpot)
        COPY_MEMBER(mSecondSpot)
        COPY_MEMBER(mTolerance)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharIKSliderMidi)
    HANDLE_ACTION(set_fraction, SetFraction(_msg->Float(2), _msg->Float(3)))
    HANDLE_ACTION(reset, SetupTransforms())
    HANDLE_SUPERCLASS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xF8)
END_HANDLERS

BEGIN_PROPSYNCS(CharIKSliderMidi)
    SYNC_PROP_MODIFY_ALT(target, mTarget, SetupTransforms())
    SYNC_PROP_MODIFY_ALT(first_spot, mFirstSpot, SetupTransforms())
    SYNC_PROP_MODIFY_ALT(second_spot, mSecondSpot, SetupTransforms())
    SYNC_PROP(tolerance, mTolerance)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS