#include "char/CharForeTwist.h"
#include "math/Rot.h"
#include "utl/Symbols.h"

INIT_REVS(CharForeTwist)

CharForeTwist::CharForeTwist() : mHand(this, 0), mTwist2(this, 0), mOffset(0.0f), mBias(0.0f) {

}

void CharForeTwist::Poll(){
    if(!mHand || !mTwist2 || !mHand->TransParent() || !mTwist2->TransParent()) return;
    Transform& parentxfm = mHand->TransParent()->WorldXfm();
    Transform& handxfm = mHand->WorldXfm();
    float clamped = Clamp(-1.0f, 1.0f, Dot(handxfm.m.z, parentxfm.m.y));
    Vector3 v98;
    Cross(parentxfm.m.y, handxfm.m.z, v98);
    float clamp2 = Clamp(-1.0f, 1.0f, Dot(parentxfm.m.x, v98));
    float newbias = mBias * DEG2RAD;
    float tan2res = std::atan2(clamp2, clamped);
    float angle = LimitAng(mOffset * DEG2RAD + tan2res + newbias);
    float finalfloat = angle - newbias;
    Hmx::Matrix3 m58;
    m58.RotateAboutX(finalfloat * 0.33333f);
    RndTransformable* twistparent = mTwist2->TransParent();
    Transform tf88;
    tf88.v = parentxfm.v;
    Multiply(m58, parentxfm.m, tf88.m);
    twistparent->SetWorldXfm(tf88);
    RndTransformable* hand = mHand;
    RndTransformable* twist2 = mTwist2;
    Interp(tf88.v, handxfm.v, twist2->mLocalXfm.v.x / hand->mLocalXfm.v.x, tf88.v);
    Multiply(m58, tf88.m, tf88.m);
    mTwist2->SetWorldXfm(tf88);
}

void CharForeTwist::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    changedBy.push_back(mHand);
    change.push_back(mTwist2);
    if(mTwist2) change.push_back(mTwist2->mParent);
}

SAVE_OBJ(CharForeTwist, 0x79)

void CharForeTwist::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(4, 0);
    Hmx::Object::Load(bs);
    bs >> mOffset;
    bs >> mHand;
    bs >> mTwist2;
    if(gRev == 2){
        int dummy;
        bs >> dummy;
    }
    if(gRev > 3) bs >> mBias;
}

BEGIN_COPYS(CharForeTwist)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharForeTwist)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mOffset)
        COPY_MEMBER(mHand)
        COPY_MEMBER(mTwist2)
        COPY_MEMBER(mBias)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharForeTwist)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xA6)
END_HANDLERS

BEGIN_PROPSYNCS(CharForeTwist)
    SYNC_PROP(hand, mHand)
    SYNC_PROP(twist2, mTwist2)
    SYNC_PROP(offset, mOffset)
    SYNC_PROP(bias, mBias)
END_PROPSYNCS