#include "rndobj/MatAnim.h"

Hmx::Object* RndMatAnim::sOwner;

RndMatAnim::TexPtr::TexPtr() : ObjPtr<RndTex, ObjectDir>(sOwner, 0) {}
RndMatAnim::TexPtr::TexPtr(RndTex* tex) : ObjPtr<RndTex, ObjectDir>(sOwner, tex) {}
RndMatAnim::TexKeys::TexKeys(Hmx::Object* o) : mOwner(o) {}

RndMatAnim::RndMatAnim() : mMat(this, 0), mKeysOwner(this, this), mTexKeys(this) {

}