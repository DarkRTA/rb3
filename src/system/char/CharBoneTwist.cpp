#include "char/CharBoneTwist.h"
#include "utl/Symbols.h"

INIT_REVS(CharBoneTwist);

CharBoneTwist::CharBoneTwist() : mBone(this, 0), mTargets(this, kObjListNoNull) {

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
    GET_COPY(CharBoneTwist)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mBone)
        COPY_MEMBER(mTargets)
    END_COPY_CHECKED
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