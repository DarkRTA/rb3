#include "rndobj/TexBlender.h"
#include "utl/Symbols.h"

INIT_REVS(RndTexBlender);

RndTexBlender::RndTexBlender() : mBaseMap(this, 0), mNearMap(this, 0), mFarMap(this, 0), mOutputTextures(this, 0), mControllerList(this, kObjListNoNull), 
    mOwner(this, 0), mControllerInfluence(1.0f), unk70(0) {
    unk9p6 = 1;
}

SAVE_OBJ(RndTexBlender, 0x52);

void RndTexBlender::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    Hmx::Object::Load(bs);
    RndDrawable::Load(bs);
    bs >> mOutputTextures;
    bs >> mBaseMap;
    bs >> mNearMap;
    bs >> mFarMap;
    bs >> mControllerList;
    bs >> mOwner;
    if(gRev > 1) bs >> mControllerInfluence;
    else mControllerInfluence = 0.7071068f;
    unk70 = 0;
}

BEGIN_HANDLERS(RndTexBlender)
    HANDLE(get_render_textures, OnGetRenderTextures)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x1A5)
END_HANDLERS
