#include "char/CharMirror.h"
#include "utl/Symbols.h"

INIT_REVS(CharMirror)

CharMirror::CharMirror() : mServo(this, 0), mMirrorServo(this, 0), mBones(), mOps() {

}

void CharMirror::Poll(){
    float weight = Weight();
    if(weight && mBones.TotalSize() != 0){
        mBones.ScaleDown(*mServo.Ptr(), 1.0f - weight);
    }
}

void CharMirror::SetServo(CharServoBone* bone){
    if(bone != mServo){
        mServo = bone;
        SyncBones();
    }
}

void CharMirror::SetMirrorServo(CharServoBone* bone){
    if(bone != mMirrorServo){
        mMirrorServo = bone;
        SyncBones();
    }
}

void CharMirror::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mServo);
}

SAVE_OBJ(CharMirror, 0x90)

void CharMirror::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    CharWeightable::Load(bs);
    bs >> mMirrorServo;
    bs >> mServo;
    SyncBones();
}

BEGIN_COPYS(CharMirror)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    CREATE_COPY(CharMirror)
    BEGIN_COPYING_MEMBERS
        SetMirrorServo(c->mMirrorServo);
        SetServo(c->mServo);
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharMirror)
    HANDLE_SUPERCLASS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xB8)
END_HANDLERS

BEGIN_PROPSYNCS(CharMirror)
    SYNC_PROP_SET(servo, (Hmx::Object*)mServo, SetServo(_val.Obj<CharServoBone>()));
    SYNC_PROP_SET(mirror_servo, (Hmx::Object*)mMirrorServo, SetMirrorServo(_val.Obj<CharServoBone>()));
    SYNC_SUPERCLASS(CharWeightable);
END_PROPSYNCS
