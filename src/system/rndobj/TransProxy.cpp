#include "rndobj/TransProxy.h"
#include "obj/Dir.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

INIT_REVS(RndTransProxy)

RndTransProxy::RndTransProxy() : mProxy(this, 0), mPart() {

}

void RndTransProxy::SetProxy(class ObjectDir* dir){
    if(mProxy.Ptr() != dir){
        mProxy = dir;
        Sync();
    }
}

void RndTransProxy::SetPart(Symbol sym){
    if(mPart == sym) return;
    mPart = sym;
    Sync();
}

void RndTransProxy::Sync(){
    SetTransParent(0, false);
    if(mProxy.Ptr() && mPart.Null()){
        RndTransformable* trans = dynamic_cast<RndTransformable*>(mProxy.Ptr());
        if(trans){
            SetTransParent(trans, false);
            return;
        }
    }
    if(mProxy.Ptr()){
        RndTransformable* trans = dynamic_cast<RndTransformable*>(mProxy.Ptr()->FindObject(mPart.Str(), false));
        if(trans){
            SetTransParent(dynamic_cast<RndTransformable*>(trans), false);
            return;
        }
    }
    SetTransParent(0, 0);
}

void RndTransProxy::PreSave(BinStream& bs){
    SetTransParent(0, false);
}

void RndTransProxy::PostSave(BinStream& bs){
    Sync();
}

SAVE_OBJ(RndTransProxy, 0x44);

void RndTransProxy::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    if(gRev != 0) RndTransformable::Load(bs);
    bs >> mProxy;
    bs >> mPart;
    Sync();
}

BEGIN_COPYS(RndTransProxy)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    GET_COPY(RndTransProxy)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mProxy)
        COPY_MEMBER(mPart)
        Sync();
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(RndTransProxy)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x6A)
END_HANDLERS

BEGIN_PROPSYNCS(RndTransProxy)
    // SYNC_PROP_ACTION(proxy, mProxy, kPropSize|kPropGet, Sync())
    if(sym == proxy){
        bool synced = PropSync(mProxy, _val, _prop, _i + 1, _op);
        if(synced){
            if(!(_op & (kPropSize|kPropGet))){ Sync(); } 
            return true;
        }
        else return false;
    }
    SYNC_PROP_ACTION(part, mPart, kPropSize|kPropGet, Sync())
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS