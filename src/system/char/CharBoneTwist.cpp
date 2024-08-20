#include "char/CharBoneTwist.h"
#include "utl/Symbols.h"

INIT_REVS(CharBoneTwist);

CharBoneTwist::CharBoneTwist() : mBone(this, 0), mTargets(this, kObjListNoNull) {

}

// fn_804B42D0 - poll
void CharBoneTwist::Poll(){
    if(!mBone || mTargets.size() == 0) return;
    Vector3 v58;
    v58.Zero();
    for(ObjPtrList<RndTransformable, ObjectDir>::iterator it = mTargets.begin(); it != mTargets.end(); ++it){
        Vector3 v64((*it)->WorldXfm().v);
        Add(v64, v58, v58);
    }
    Scale(v58, 1.0f / mTargets.size(), v58);
    Transform tf48(mBone->WorldXfm());
    Vector3 v70;
    Subtract(v58, mBone->WorldXfm().v, v70);
    Vector3 v7c;
    Scale(tf48.m.x, Dot(tf48.m.x, v70), v7c);
    Subtract(v70, v7c, v7c);
    Normalize(v7c, v7c);

    Interp(tf48.m.y, v7c, Weight(), tf48.m.y);
    Normalize(tf48.m.y, tf48.m.y);
    Cross(tf48.m.x, tf48.m.y, tf48.m.z);
    Normalize(tf48.m.z, tf48.m.z);
    Scale(tf48.m.z, Length(tf48.m.x), tf48.m.z);
    mBone->SetWorldXfm(tf48);
}

void CharBoneTwist::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mBone);
    for(ObjPtrList<RndTransformable, class ObjectDir>::iterator it = mTargets.begin(); it != mTargets.end(); ++it){
        changedBy.push_back(*it);
    }
}

SAVE_OBJ(CharBoneTwist, 0x59)

void CharBoneTwist::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    Hmx::Object::Load(bs);
    CharWeightable::Load(bs);
    bs >> mBone;
    bs >> mTargets;
}

BEGIN_COPYS(CharBoneTwist)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    CREATE_COPY(CharBoneTwist)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mBone)
        COPY_MEMBER(mTargets)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharBoneTwist)
    HANDLE_SUPERCLASS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x7A)
END_HANDLERS

BEGIN_PROPSYNCS(CharBoneTwist)
    SYNC_PROP(bone, mBone)
    SYNC_PROP(targets, mTargets)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS