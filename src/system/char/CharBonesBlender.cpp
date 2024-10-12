#include "char/CharBonesBlender.h"
#include "char/CharBoneDir.h"
#include "utl/Symbols.h"

INIT_REVS(CharBonesBlender)

CharBonesBlender::CharBonesBlender() : mDest(this, 0), mClipType("") {

}

CharBonesBlender::~CharBonesBlender(){

}

void CharBonesBlender::Enter(){
    CharBones::Enter();
}

void CharBonesBlender::Poll(){
    if(mBones.empty() || !mDest) return;
    Blend(*mDest);
    CharBones::Enter();
}

void CharBonesBlender::SetDest(CharBonesObject* obj){
    if(obj != mDest){
        mDest = obj;
        if(mDest) mDest->AddBones(mBones);
    }
}

void CharBonesBlender::SetClipType(Symbol s){
    if(s != mClipType){
        mClipType = s;
        ClearBones();
        CharBoneDir::StuffBones(*this, mClipType);
    }
}

void CharBonesBlender::ReallocateInternal(){
    CharBonesAlloc::ReallocateInternal();
    if(mDest) mDest->AddBones(mBones);
    CharBones::Enter();
}

void CharBonesBlender::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mDest);
}

SAVE_OBJ(CharBonesBlender, 0x58);

BEGIN_LOADS(CharBonesBlender)
    LOAD_REVS(bs)
    ASSERT_REVS(2, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    ObjPtr<CharBonesObject, ObjectDir> boneObjPtr(this, 0);
    bs >> boneObjPtr;
    Symbol s;
    if(gRev > 1) bs >> s;
    SetClipType(s);
    SetDest(boneObjPtr);
END_LOADS

BEGIN_COPYS(CharBonesBlender)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharBonesBlender)
    BEGIN_COPYING_MEMBERS
        SetClipType(c->mClipType);
        SetDest(c->mDest);
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharBonesBlender)
    HANDLE_SUPERCLASS(CharPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x81)
END_HANDLERS

BEGIN_PROPSYNCS(CharBonesBlender)
    SYNC_PROP_SET(dest, mDest, SetDest(_val.Obj<CharBonesObject>()))
    SYNC_PROP_SET(clip_type, mClipType, SetClipType(_val.Sym()))
    SYNC_SUPERCLASS(CharBonesObject)
END_PROPSYNCS
