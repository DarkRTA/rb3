#include "rndobj/CamAnim.h"
#include "obj/PropSync_p.h"
#include "rndobj/Utl.h"

INIT_REVS(RndCamAnim);

BEGIN_COPYS(RndCamAnim)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    GET_COPY(RndCamAnim)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mCam)
        if(ty == kCopyShallow || ty == kCopyFromMax && c->mKeysOwner != c){
            COPY_MEMBER(mKeysOwner)
        }
        else {
            mKeysOwner = this;
            mFovKeys = c->mKeysOwner->mFovKeys;
        }
    END_COPY_CHECKED
END_COPYS

void RndCamAnim::Print(){
    TextStream& ts = TheDebug;
    ts << "   cam: " << mCam.Ptr() << "\n";
    ts << "   keysOwner: " << mKeysOwner.Ptr() << "\n";
    ts << "   fovKeys: " << mFovKeys << "\n";
}

SAVE_OBJ(RndCamAnim, 0x37);

void RndCamAnim::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    if(gRev != 0) Hmx::Object::Load(bs);
    RndAnimatable::Load(bs);
    bs >> mCam >> mFovKeys >> mKeysOwner;
    if(gRev < 2){
        for(Keys<float, float>::iterator it = mFovKeys.begin(); it != mFovKeys.end(); it++){
            it->value = ConvertFov(it->value, 0.75f);
        }
    }
    if(!mKeysOwner.Ptr()) mKeysOwner = this;
}

void RndCamAnim::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mKeysOwner == from){
        if(!to) mKeysOwner = this;
        else mKeysOwner = dynamic_cast<RndCamAnim*>(to)->mKeysOwner;
    }
}

float RndCamAnim::EndFrame(){
    Keys<float, float>& theKeys = mKeysOwner->mFovKeys;
    if(!theKeys.empty()) return theKeys.back().frame;
    else return 0.0f;
}

RndCamAnim::~RndCamAnim(){

}

RndCamAnim::RndCamAnim() : mCam(this, 0), mKeysOwner(this, this) {

}

BEGIN_HANDLERS(RndCamAnim)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xC5)
END_HANDLERS

BEGIN_PROPSYNCS(RndCamAnim)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
