#include "char/CharIKMidi.h"
#include "char/Char.h"
#include "math/Rot.h"
#include "math/Utl.h"
#include "obj/Task.h"
#include "obj/Msg.h"
#include "rndobj/Rnd.h"
#include "utl/Symbols.h"

INIT_REVS(CharIKMidi)

CharIKMidi::CharIKMidi()
    : mBone(this), mCurSpot(this), mNewSpot(this), mSpotChanged(0), mAnimBlender(this),
      mMaxAnimBlend(1.0f), mAnimFracPerBeat(0.0f), mAnimFrac(0.0f) {
    Enter();
}

CharIKMidi::~CharIKMidi() {}

void CharIKMidi::Enter() {
    mCurSpot = 0;
    mNewSpot = 0;
    mSpotChanged = false;
    mFrac = 0.0f;
    mFracPerBeat = 0.0f;
    mLocalXfm.Reset();
    mOldLocalXfm.Reset();
    RndPollable::Enter();
}

void CharIKMidi::NewSpot(RndTransformable *t, float f) {
    float f18 = f;
    if (mNewSpot != t) {
        if (!mNewSpot && f18 <= 0)
            mFracPerBeat = kHugeFloat;
        else {
            MaxEq(f18, 0.1f);
            mFracPerBeat = 1.0f / f18;
            if (f18 > 0.2) {
                mAnimFracPerBeat = mMaxAnimBlend / f18;
            }
        }
        mFrac = 0;
        mAnimFrac = 0;
        mSpotChanged = true;
        mNewSpot = t;
    }
}

void CharIKMidi::Poll() {
    if (mBone) {
        if (mSpotChanged) {
            mSpotChanged = false;
            if (!mCurSpot) {
                mCurSpot = mBone;
                mOldLocalXfm.Reset();
            }
            if (mNewSpot) {
                Transform tf48;
                FastInvert(mNewSpot->WorldXfm(), tf48);
                Multiply(mCurSpot->WorldXfm(), tf48, tf48);
                Multiply(mOldLocalXfm, tf48, mLocalXfm);
            }
            mCurSpot = mNewSpot;
        }
        if (mCurSpot) {
            mFrac += mFracPerBeat * TheTaskMgr.DeltaBeat();
            if (IsNaN(mFrac))
                mFrac = 0;
            ClampEq<float>(mFrac, 0, 1);
            float sigmoid = Sigmoid(mFrac);
            if (mAnimFracPerBeat > 0 && mAnimBlender) {
                if (mFrac < 0.5) {
                    mAnimFrac += mAnimFracPerBeat * TheTaskMgr.DeltaBeat();
                } else {
                    mAnimFrac -= mAnimFracPerBeat * TheTaskMgr.DeltaBeat();
                }
                ClampEq<float>(mAnimFrac, 0, mMaxAnimBlend);
                mAnimBlender->SetWeight(mAnimFrac);
            }
            Scale(mLocalXfm.v, 1.0f - sigmoid, mOldLocalXfm.v);
            Hmx::Quat q88(mLocalXfm.m);
            IdentityInterp(q88, sigmoid, q88);
            MakeRotMatrix(q88, mOldLocalXfm.m);
            Transform tf78;
            Multiply(mOldLocalXfm, mCurSpot->WorldXfm(), tf78);
            mBone->SetWorldXfm(tf78);
        }
    }
}

void DoDebugDraws(CharIKMidi *mid, float f) {
    for (ObjDirItr<MsgSource> it(ObjectDir::Main(), true); it != nullptr; ++it) {
        if (it) {
            for (std::list<MsgSource::Sink>::iterator sit = it->mSinks.begin();
                 sit != it->mSinks.end();
                 ++sit) {
                if (sit->obj == mid) {
                    static Message msg("debug_draw", 2.0f, 2.0f);
                    msg[0] = f;
                    msg[1] = TheTaskMgr.Beat();
                    it->Handle(msg, false);
                    return;
                }
            }
        }
    }
}

void CharIKMidi::Highlight() {
#ifdef MILO_DEBUG
    if (gCharHighlightY == -1.0f) {
        CharDeferHighlight(this);
    } else {
        Hmx::Color white(1, 1, 1);
        Vector2 v2(5.0f, gCharHighlightY);
        TheRnd->DrawString(MakeString("%s:", PathName(this)), v2, white, true);
        v2.y += 16.0f;
        TheRnd->DrawString(
            MakeString("frac %.3f new:%s", mFrac, mCurSpot ? mCurSpot->Name() : "NULL"),
            v2,
            white,
            true
        );
        v2.y += 16.0f;
        DoDebugDraws(this, (v2.y + 24.0f) - 12.0f);
        gCharHighlightY += 112.0f;
    }
#endif
}

void CharIKMidi::PollDeps(
    std::list<Hmx::Object *> &changedBy, std::list<Hmx::Object *> &change
) {
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
    if (gRev < 3) {
        ObjVector<ObjPtr<RndTransformable> > vec(this);
        bs >> vec;
    }
    if (gRev == 2 || gRev == 3) {
        String asdf;
        bs >> asdf;
    }
    if (gRev > 4) {
        bs >> mAnimBlender;
        bs >> mMaxAnimBlend;
    }
END_LOADS

BEGIN_COPYS(CharIKMidi)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharIKMidi)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mBone)
        COPY_MEMBER(mAnimBlender)
        COPY_MEMBER(mMaxAnimBlend)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharIKMidi)
    HANDLE_ACTION(
        new_spot,
        NewSpot(Dir()->Find<RndTransformable>(_msg->Str(2), true), _msg->Float(3))
    )
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x11C)
END_HANDLERS

BEGIN_PROPSYNCS(CharIKMidi)
    SYNC_PROP(bone, mBone)
    SYNC_PROP(anim_blend_weightable, mAnimBlender)
    SYNC_PROP(anim_blend_max, mMaxAnimBlend)
    SYNC_PROP_SET(cur_spot, mCurSpot, NewSpot(_val.Obj<RndTransformable>(), 0))
END_PROPSYNCS
