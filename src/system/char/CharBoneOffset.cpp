#include "char/CharBoneOffset.h"
#include "utl/Symbols.h"

INIT_REVS(CharBoneOffset)

CharBoneOffset::CharBoneOffset() : mDest(this, 0), mOffset(0.0f, 0.0f, 0.0f) {
    
}

SAVE_OBJ(CharBoneOffset, 0x5E)

void CharBoneOffset::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    bs >> mDest;
    bs >> mOffset;
}

BEGIN_COPYS(CharBoneOffset)
    COPY_SUPERCLASS(Hmx::Object)
    GET_COPY(CharBoneOffset)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mDest)
        COPY_MEMBER(mOffset)
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(CharBoneOffset)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x7D)
END_HANDLERS

BEGIN_PROPSYNCS(CharBoneOffset)
    SYNC_PROP(dest, mDest)
    SYNC_PROP(offset, mOffset)
END_PROPSYNCS