#include "char/CharMeshHide.h"
#include "decomp.h"
#include "utl/Symbols.h"

INIT_REVS(CharMeshHide)
DECOMP_FORCEACTIVE(CharMeshHide, "ObjPtr_p.h", "f.Owner()", "", __FILE__)

CharMeshHide::Hide::Hide(Hmx::Object* o) : mDraw(o, 0), mFlags(0), mShow(0) {

}

CharMeshHide::Hide::Hide(const CharMeshHide::Hide& hide) : mDraw(hide.mDraw), mFlags(hide.mFlags), mShow(hide.mShow) {

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

void CharMeshHide::HideAll(const ObjPtrList<CharMeshHide, ObjectDir>& pList, int i){
    for(ObjPtrList<CharMeshHide, ObjectDir>::iterator it = pList.begin(); it != pList.end(); ++it){
        i |= (*it)->mFlags;
    }
    for(ObjPtrList<CharMeshHide, ObjectDir>::iterator it = pList.begin(); it != pList.end(); ++it){
        (*it)->HideDraws(i);
    }
}

void CharMeshHide::HideDraws(int x){
    for(int i = 0; i < mHides.size(); i++){
        Hide& theHide = mHides[i];
        if(theHide.mDraw){
            bool b = (x & theHide.mFlags) == 0;
            theHide.mShow = b & theHide.mDraw->Showing();
        }
    }
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

BEGIN_COPYS(CharMeshHide)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharMeshHide)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mFlags)
        if(&mHides != &c->mHides)
            COPY_MEMBER(mHides)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharMeshHide)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xA1)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(CharMeshHide::Hide)
    SYNC_PROP(drawable, o.mDraw)
    SYNC_PROP(flags, o.mFlags)
    SYNC_PROP(show, o.mShow)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(CharMeshHide)
    SYNC_PROP(flags, mFlags)
    SYNC_PROP(hides, mHides)
END_PROPSYNCS