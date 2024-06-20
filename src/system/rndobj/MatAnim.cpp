#include "rndobj/MatAnim.h"

INIT_REVS(RndMatAnim)

Hmx::Object* RndMatAnim::sOwner;

RndMatAnim::TexPtr::TexPtr() : ObjPtr<RndTex, ObjectDir>(sOwner, 0) {}
RndMatAnim::TexPtr::TexPtr(RndTex* tex) : ObjPtr<RndTex, ObjectDir>(sOwner, tex) {}
RndMatAnim::TexKeys::TexKeys(Hmx::Object* o) : mOwner(o) {}

RndMatAnim::RndMatAnim() : mMat(this, 0), mKeysOwner(this, this), mTexKeys(this) {

}

void RndMatAnim::SetMat(RndMat* mat){
    mMat = mat;
}

void RndMatAnim::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mKeysOwner == from){
        if(!to) mKeysOwner = this;
        else mKeysOwner = dynamic_cast<RndMatAnim*>(to)->mKeysOwner;
    }
}

SAVE_OBJ(RndMatAnim, 0x6C)

void RndMatAnim::LoadStage(BinStream& bs){
    if(gRev < 2) MILO_WARN("Can't convert old MatAnim stages");
    if(gRev != 0){
        bs >> mTransKeys >> mScaleKeys >> mRotKeys;
    }
    if(gRev > 1) bs >> mTexKeys;
}