#include "char/CharSleeve.h"
#include "rndobj/Utl.h"
#include "rndobj/Rnd.h"
#include "utl/Symbols.h"

INIT_REVS(CharSleeve);

CharSleeve::CharSleeve() : mSleeve(this, 0), mTopSleeve(this, 0), mPos(0.0f, 0.0f, 0.0f), mLastPos(0.0f, 0.0f, 0.0f),
    mLastDT(0.0f), mInertia(0.5f), mGravity(1.0f), mRange(0.0f), mNegLength(0.0f), mPosLength(0.0f), mStiffness(0.02f), mMe(this, 0) {

}

CharSleeve::~CharSleeve(){

}

void CharSleeve::SetName(const char* cc, class ObjectDir* dir){
    Hmx::Object::SetName(cc, dir);
    mMe = dynamic_cast<class Character*>(dir);
}

// https://decomp.me/scratch/vVQkq (retail)
void CharSleeve::Poll(){
    if(mSleeve && mSleeve->TransParent()){
        float deltasecs = TheTaskMgr.DeltaSeconds();
        float dvar12 = deltasecs * 60.0f;
        float powed = std::pow(1.0f - mStiffness, dvar12 * dvar12);
        RndTransformable* sleeveparent = mSleeve->TransParent();
        float absed = std::fabs(mSleeve->mLocalXfm.v.z);
        bool b2 = false;
        if(mMe && mMe->Teleported()){
            mPos = mSleeve->WorldXfm().v;
            Vector3 v9c(0.0f, 0.0f, -(absed + mPosLength));
            float dotted = Dot(v9c, sleeveparent->WorldXfm().m.x);
            ClampEq(dotted, -mRange, mRange);
            ScaleAddEq(v9c, sleeveparent->WorldXfm().m.x, dotted);
            mPos += v9c;
            Vector3 va8;
            ScaleAdd(sleeveparent->WorldXfm().v, sleeveparent->WorldXfm().m.x, dotted, va8);
            Subtract(mPos, va8, v9c);
            ScaleToMagnitude(v9c, absed + mPosLength, v9c);
            Add(va8, v9c, mPos);
            mLastPos = mPos;
            b2 = true;
            mLastDT = 0;
        }
        Vector3 vb4(mPos);
        if(mLastDT > 0.0f && deltasecs > 0.0f){
            Vector3 vc0;
            Subtract(mPos, mLastPos, vc0);
            ScaleAddEq(vb4, vc0, (mInertia * deltasecs) / mLastDT);
        }
        vb4.z += mGravity * deltasecs * dvar12 * -3.858268f;
        Vector3 vcc;
        Subtract(vb4, sleeveparent->WorldXfm().v, vcc);
        float dotted2 = Dot(vcc, sleeveparent->WorldXfm().m.x);
        float d4 = dvar12 * (1.0f - (1.0f - powed));
        ClampEq(d4, -mRange, mRange);
        ScaleAddEq(vcc, sleeveparent->WorldXfm().m.x, (d4 - dvar12));
        float len = Length(vcc);
        float interped = Interp(len, absed, 1.0f - powed);
        ClampEq(interped, absed - mNegLength, absed + mPosLength);
        ScaleToMagnitude(vcc, len, vcc);
        Add(sleeveparent->WorldXfm().v, vcc, vb4);
        Transform tf90;
        tf90.v = vb4;
        Scale(vcc, -1.0f, tf90.m.z);
        Cross(tf90.m.z, sleeveparent->WorldXfm().m.x, tf90.m.y);
        Normalize(tf90.m.z, tf90.m.z);
        Normalize(tf90.m.y, tf90.m.y);
        Cross(tf90.m.y, tf90.m.z, tf90.m.x);
        mSleeve->SetWorldXfm(tf90);
        mLastPos = mPos;
        mLastDT = deltasecs;
        mPos = vb4;
        if(b2) mLastPos = mPos;
        if(mTopSleeve){
            float dotcc = Dot(vcc, sleeveparent->WorldXfm().m.x);
            ScaleAddEq(vcc, sleeveparent->WorldXfm().m.x, -dotcc);
            Add(sleeveparent->WorldXfm().v, vcc, tf90.v);
            Scale(vcc, -1.0f, tf90.m.z);
            Cross(tf90.m.z, sleeveparent->WorldXfm().m.x, tf90.m.y);
            Normalize(tf90.m.z, tf90.m.z);
            Normalize(tf90.m.y, tf90.m.y);
            Cross(tf90.m.y, tf90.m.z, tf90.m.x);
            mTopSleeve->SetWorldXfm(tf90);
        }
    }
}

void CharSleeve::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    if(mSleeve){
        changedBy.push_back(mSleeve->mParent);
        change.push_back(mSleeve);
        change.push_back(mTopSleeve);
    }
}

void CharSleeve::Highlight(){
    if(!mSleeve || !mSleeve->TransParent()) return;
    UtilDrawAxes(mSleeve->WorldXfm(), 1.0f, Hmx::Color(0.0f, 1.0f, 0.0f));
    TheRnd->DrawLine(mSleeve->WorldXfm().v, mSleeve->TransParent()->WorldXfm().v, Hmx::Color(0.0f, 1.0f, 0.0f), false);
    if(mTopSleeve){
        UtilDrawAxes(mTopSleeve->WorldXfm(), 1.0f, Hmx::Color(0.0f, 1.0f, 1.0f));
        TheRnd->DrawLine(mTopSleeve->WorldXfm().v, mTopSleeve->TransParent()->WorldXfm().v, Hmx::Color(0.0f, 1.0f, 1.0f), false);
    }
}

SAVE_OBJ(CharSleeve, 0xE1)

void CharSleeve::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    Hmx::Object::Load(bs);
    bs >> mSleeve;
    bs >> mTopSleeve;
    bs >> mInertia;
    bs >> mGravity;
    bs >> mStiffness;
    bs >> mRange;
    bs >> mNegLength;
    bs >> mPosLength;
}

BEGIN_COPYS(CharSleeve)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharSleeve)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mSleeve)
        COPY_MEMBER(mTopSleeve)
        COPY_MEMBER(mInertia)
        COPY_MEMBER(mGravity)
        COPY_MEMBER(mStiffness)
        COPY_MEMBER(mRange)
        COPY_MEMBER(mNegLength)
        COPY_MEMBER(mPosLength)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharSleeve)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x112)
END_HANDLERS

BEGIN_PROPSYNCS(CharSleeve)
    SYNC_PROP(sleeve, mSleeve)
    SYNC_PROP(top_sleeve, mTopSleeve)
    SYNC_PROP(inertia, mInertia)
    SYNC_PROP(gravity, mGravity)
    SYNC_PROP(stiffness, mStiffness)
    SYNC_PROP(range, mRange)
    SYNC_PROP(neg_length, mNegLength)
    SYNC_PROP(pos_length, mPosLength)
END_PROPSYNCS