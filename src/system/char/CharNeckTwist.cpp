#include "char/CharNeckTwist.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

INIT_REVS(CharNeckTwist);

CharNeckTwist::CharNeckTwist() : mTwist(this, 0), mHead(this, 0) {

}

void CharNeckTwist::Poll() {
    if (mTwist || mHead) return; else {
        
    }
}

void CharNeckTwist::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    changedBy.push_back(mHead);
    change.push_back(mTwist);
}

SAVE_OBJ(CharNeckTwist, 0x4A);

void CharNeckTwist::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    bs >> mHead;
    bs >> mTwist;
}

BEGIN_COPYS(CharNeckTwist)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharNeckTwist)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mHead)
        COPY_MEMBER(mTwist)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharNeckTwist)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x65)
END_HANDLERS

BEGIN_PROPSYNCS(CharNeckTwist)
    SYNC_PROP(head, mHead)
    SYNC_PROP(twist, mTwist)
END_PROPSYNCS
