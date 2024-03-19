#include "rndobj/CamAnim.h"
#include "obj/PropSync_p.h"

SAVE_OBJ(RndCamAnim, 0x37);

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
