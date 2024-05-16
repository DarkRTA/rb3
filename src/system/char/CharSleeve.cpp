#include "char/CharSleeve.h"
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

void CharSleeve::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    if(mSleeve){
        changedBy.push_back(mSleeve->mParent);
        change.push_back(mSleeve);
        change.push_back(mTopSleeve);
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
    GET_COPY(CharSleeve)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mSleeve)
        COPY_MEMBER(mTopSleeve)
        COPY_MEMBER(mInertia)
        COPY_MEMBER(mGravity)
        COPY_MEMBER(mStiffness)
        COPY_MEMBER(mRange)
        COPY_MEMBER(mNegLength)
        COPY_MEMBER(mPosLength)
    END_COPY_CHECKED
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