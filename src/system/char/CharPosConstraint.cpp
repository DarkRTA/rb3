#include "char/CharPosConstraint.h"
#include "utl/Symbols.h"

INIT_REVS(CharPosConstraint)

CharPosConstraint::CharPosConstraint() : mSrc(this, 0), mTargets(this, kObjListNoNull) {
    mBox.mMin.Set(1.0f, 1.0f, 1.0f);
    mBox.mMax.Set(-1.0f, -1.0f, -1.0f);
}

CharPosConstraint::~CharPosConstraint(){
    
}

void CharPosConstraint::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    changedBy.push_back(mSrc);
    for(ObjPtrList<RndTransformable, class ObjectDir>::iterator it = mTargets.begin(); it != mTargets.end(); ++it){
        change.push_back(*it);
        changedBy.push_back(*it);
    }
}

SAVE_OBJ(CharPosConstraint, 0x64)

void CharPosConstraint::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    Hmx::Object::Load(bs);
    bs >> mTargets;
    bs >> mSrc;
    if(gRev > 1){
        bs >> mBox;
    }
    else {
        mBox.mMin.Set(1.0f, 1.0f, 0.0f);
        mBox.mMax.Set(-1.0f, -1.0f, 1000.0f);
    }
}

BEGIN_COPYS(CharPosConstraint)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharPosConstraint)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mTargets)
        COPY_MEMBER(mSrc)
        COPY_MEMBER(mBox)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharPosConstraint)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x8B)
END_HANDLERS

BEGIN_PROPSYNCS(CharPosConstraint)
    SYNC_PROP(source, mSrc)
    SYNC_PROP(targets, mTargets)
    SYNC_PROP(box, mBox)
END_PROPSYNCS