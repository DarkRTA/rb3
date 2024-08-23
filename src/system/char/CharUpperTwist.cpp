#include "char/CharUpperTwist.h"
#include "math/Rot.h"
#include "utl/Symbols.h"

INIT_REVS(CharUpperTwist)

CharUpperTwist::CharUpperTwist() : mUpperArm(this, 0), mTwist1(this, 0), mTwist2(this, 0) {

}

CharUpperTwist::~CharUpperTwist(){
    
}

// fn_804FAB0C - poll
void CharUpperTwist::Poll(){
    if(!mTwist2 || !mTwist1 || !mUpperArm) return;
    Transform& twist2parentworld = mTwist2->TransParent()->WorldXfm();
    Transform& twist2world = mTwist2->WorldXfm();
    Hmx::Quat q;
    MakeRotQuat(twist2parentworld.m.x, twist2world.m.x, q);
    Vector3 v68;
    Multiply(twist2parentworld.m.y, q, v68);
    Transform tf48;
    tf48.m.x = twist2world.m.x;
    tf48.v = mUpperArm->WorldXfm().v;
    Interp(v68, twist2world.m.y, 0.333f, tf48.m.y);
    LookAt(tf48.m);
    mUpperArm->SetWorldXfm(tf48);
    tf48.v = mTwist1->WorldXfm().v;
    Interp(v68, twist2world.m.y, 0.666f, tf48.m.y);
    LookAt(tf48.m);
    mTwist1->SetWorldXfm(tf48);
}

void CharUpperTwist::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    changedBy.push_back(mTwist2);
    change.push_back(mUpperArm);
    change.push_back(mTwist1);
}

SAVE_OBJ(CharUpperTwist, 0x5D)

void CharUpperTwist::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    bs >> mTwist2;
    bs >> mUpperArm;
    bs >> mTwist1;
}

BEGIN_COPYS(CharUpperTwist)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharUpperTwist)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mTwist2)
        COPY_MEMBER(mUpperArm)
        COPY_MEMBER(mTwist1)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharUpperTwist)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x7E)
END_HANDLERS

// don't ask me why it's this way, it's what matches
BEGIN_PROPSYNCS(CharUpperTwist)
    SYNC_PROP(upper_arm, mTwist2)
    SYNC_PROP(twist1, mUpperArm)
    SYNC_PROP(twist2, mTwist1)
END_PROPSYNCS