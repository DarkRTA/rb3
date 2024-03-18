#include "char/CharTransCopy.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

INIT_REVS(CharTransCopy);

CharTransCopy::CharTransCopy() : mSrc(this, 0), mDest(this, 0) {

}

CharTransCopy::~CharTransCopy(){

}

SAVE_OBJ(CharTransCopy, 0x2D);

void CharTransCopy::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    bs >> mSrc;
    bs >> mDest;
}

BEGIN_COPYS(CharTransCopy)
    COPY_SUPERCLASS(Hmx::Object)
    GET_COPY(CharTransCopy)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mSrc)
        COPY_MEMBER(mDest)
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(CharTransCopy)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x4C)
END_HANDLERS

BEGIN_PROPSYNCS(CharTransCopy)
    SYNC_PROP(src, mSrc)
    SYNC_PROP(dest, mDest)
END_PROPSYNCS
