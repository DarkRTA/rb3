#include "char/CharMeshHide.h"

INIT_REVS(CharMeshHide)

CharMeshHide::Hide::Hide(Hmx::Object* o) : mDraw(o, 0), mFlags(0), mShow(0) {

}

CharMeshHide::Hide::Hide(const CharMeshHide::Hide& hide) : mDraw(hide.mDraw.Owner(), hide.mDraw.Ptr()), mFlags(hide.mFlags), mShow(hide.mShow) {

}

CharMeshHide::Hide& CharMeshHide::Hide::operator=(const CharMeshHide::Hide& hide){
    mDraw = hide.mDraw;
    mFlags = hide.mFlags;
    mShow = hide.mShow;
    return *this;
}

void CharMeshHide::Init(){
    Hmx::Object::RegisterFactory(StaticClassName(), NewObject);
}

CharMeshHide::CharMeshHide() : mHides(this), mFlags(0) {

}

CharMeshHide::~CharMeshHide(){

}

BinStream& operator>>(BinStream& bs, CharMeshHide::Hide& hide){
    bs >> hide.mDraw;
    bs >> hide.mFlags;
    if(CharMeshHide::gRev > 1) bs >> hide.mShow;
    return bs;
}

SAVE_OBJ(CharMeshHide, 0x6A);

void CharMeshHide::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    Hmx::Object::Load(bs);
    bs >> mFlags >> mHides;
}

BEGIN_HANDLERS(CharMeshHide)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xA1)
END_HANDLERS