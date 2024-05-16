#include "char/CharUpperTwist.h"
#include "utl/Symbols.h"

INIT_REVS(CharUpperTwist)

CharUpperTwist::CharUpperTwist() : mUpperArm(this, 0), mTwist1(this, 0), mTwist2(this, 0) {

}

CharUpperTwist::~CharUpperTwist(){
    
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
    GET_COPY(CharUpperTwist)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mTwist2)
        COPY_MEMBER(mUpperArm)
        COPY_MEMBER(mTwist1)
    END_COPY_CHECKED
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