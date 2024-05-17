#include "char/CharForeTwist.h"
#include "utl/Symbols.h"

INIT_REVS(CharForeTwist)

CharForeTwist::CharForeTwist() : mHand(this, 0), mTwist2(this, 0), mOffset(0.0f), mBias(0.0f) {

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
    GET_COPY(CharForeTwist)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mOffset)
        COPY_MEMBER(mHand)
        COPY_MEMBER(mTwist2)
        COPY_MEMBER(mBias)
    END_COPY_CHECKED
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