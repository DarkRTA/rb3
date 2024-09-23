#include "bandobj/BandIKEffector.h"
#include "utl/Symbols.h"

INIT_REVS(BandIKEffector);
CharClip* BandIKEffector::sDeformClip;

BandIKEffector::Constraint::Constraint(Hmx::Object* o) : mTarget(o, 0), mFinger(o, 0), mWeight(1.0f) {

}

BandIKEffector::Constraint::Constraint(const BandIKEffector::Constraint& c) : mTarget(c.mTarget), mFinger(c.mFinger), mWeight(c.mWeight) {

}

BandIKEffector::Constraint& BandIKEffector::Constraint::operator=(const BandIKEffector::Constraint& c){
    mTarget = c.mTarget;
    mFinger = c.mFinger;
    mWeight = c.mWeight;
    return *this;
}

BandIKEffector::BandIKEffector() : mEffector(this, 0), mGround(this, 0), mMore(this, 0), mElbow(this, 0), mConstraints(this), unk64(this, 0) {

}

BandIKEffector::~BandIKEffector(){
    
}

void BandIKEffector::SetName(const char* cc, ObjectDir* dir){
    Hmx::Object::SetName(cc, dir);
    unk64 = dynamic_cast<BandCharacter*>(dir);
}

void BandIKEffector::SetDeformClip(Hmx::Object* o){
    static Symbol bc("BandCharacter");
    if(o->ClassName() == bc){
        sDeformClip = BandCharDesc::GetDeformClip(dynamic_cast<BandCharacter*>(o)->mGender);
    }
    else sDeformClip = 0;
}

void BandIKEffector::NeutralWorldXfm(RndTransformable* trans, Transform& tf){
    RndTransformable* parent = trans->TransParent();
    if(!parent){
        SetDeformClip(trans);
        NeutralLocalXfm(trans, tf);
    }
    else {
        Transform tf38;
        NeutralWorldXfm(parent, tf);
        NeutralLocalXfm(trans, tf38);
        Multiply(tf38, tf, tf);
    }
}

void BandIKEffector::Highlight(){}

BinStream& operator>>(BinStream& bs, BandIKEffector::Constraint& c){
    bs >> c.mTarget;
    bs >> c.mFinger;
    if(BandIKEffector::gRev > 2) bs >> c.mWeight;
    return bs;
}

SAVE_OBJ(BandIKEffector, 0x354);

BEGIN_LOADS(BandIKEffector)
    LOAD_REVS(bs)
    ASSERT_REVS(4, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(CharWeightable)
    bs >> mEffector;
    bs >> mMore;
    if(gRev > 1) bs >> mElbow;
    if(gRev < 1){ int i; bs >> i; }
    bs >> mConstraints;
    if(gRev > 3) bs >> mGround;
END_LOADS

BEGIN_COPYS(BandIKEffector)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    CREATE_COPY(BandIKEffector)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mEffector)
        COPY_MEMBER(mMore)
        COPY_MEMBER(mElbow)
        COPY_MEMBER(mConstraints)
        COPY_MEMBER(mGround)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(BandIKEffector)
    HANDLE_SUPERCLASS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x388)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(BandIKEffector::Constraint)
    SYNC_PROP(target, o.mTarget)
    SYNC_PROP(finger, o.mFinger)
    SYNC_PROP(weight, o.mWeight)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(BandIKEffector)
    SYNC_PROP(effector, mEffector)
    SYNC_PROP(ground, mGround)
    SYNC_PROP(more, mMore)
    SYNC_PROP(elbow, mElbow)
    SYNC_PROP(constraints, mConstraints)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS