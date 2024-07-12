#include "char/CharBoneOffset.h"
#include "math/Rot.h"
#include "utl/Symbols.h"

INIT_REVS(CharBoneOffset)

CharBoneOffset::CharBoneOffset() : mDest(this, 0), mOffset(0.0f, 0.0f, 0.0f) {
    
}

// fn_804AF7B4
void CharBoneOffset::Poll(){
    if(!mDest || !mDest->TransParent()) return;
    Transform tf(mDest->LocalXfm());
    tf.v += mOffset;
    Transform tRes;
    Multiply(tf, mDest->TransParent()->WorldXfm(), tRes);
    mDest->SetWorldXfm(tRes);
}

void CharBoneOffset::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mDest);
    if(mDest && mDest->mParent) changedBy.push_back(mDest->mParent);
}

void CharBoneOffset::Highlight(){}

void CharBoneOffset::ApplyToLocal(){
    if(mDest) mDest->DirtyLocalXfm().v += mOffset;
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
    CREATE_COPY(CharBoneOffset)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mDest)
        COPY_MEMBER(mOffset)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharBoneOffset)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x7D)
END_HANDLERS

BEGIN_PROPSYNCS(CharBoneOffset)
    SYNC_PROP(dest, mDest)
    SYNC_PROP(offset, mOffset)
END_PROPSYNCS

DECOMP_FORCEFUNC(CharBoneOffset, CharBoneOffset, SetType)