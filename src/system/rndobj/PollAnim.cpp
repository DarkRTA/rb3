#include "rndobj/PollAnim.h"
#include "utl/Symbols.h"

INIT_REVS(RndPollAnim)

RndPollAnim::RndPollAnim() : mAnims(this, kObjListNoNull) {
    
}

void RndPollAnim::ListAnimChildren(std::list<RndAnimatable*>& children) const {
    for(ObjPtrList<RndAnimatable, class ObjectDir>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        children.push_back(*it);
    }
}

void RndPollAnim::Enter(){
    for(ObjPtrList<RndAnimatable, class ObjectDir>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        (*it)->StartAnim();
    }
}

void RndPollAnim::Exit(){
    for(ObjPtrList<RndAnimatable, class ObjectDir>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        (*it)->EndAnim();
    }
}

SAVE_OBJ(RndPollAnim, 0x66)

BEGIN_LOADS(RndPollAnim)
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndAnimatable)
    LOAD_SUPERCLASS(RndPollable)
    bs >> mAnims;
END_LOADS

BEGIN_COPYS(RndPollAnim)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_SUPERCLASS(RndPollable)
    GET_COPY(RndPollAnim)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mAnims)
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(RndPollAnim)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x8B)
END_HANDLERS

BEGIN_PROPSYNCS(RndPollAnim)
    SYNC_PROP(anims, mAnims)
    bool super = RndAnimatable::SyncProperty(_val, _prop, _i, _op);
    if(super) return true;
    else return RndPollable::SyncProperty(_val, _prop, _i, _op);
END_PROPSYNCS