#include "bandobj/BandRetargetVignette.h"
#include "utl/Symbols.h"

BandRetargetVignette::BandRetargetVignette() : mPlayer("player0"), mBone("bone_R-hand"), mProp(this, 0) {

}

BandRetargetVignette::~BandRetargetVignette(){
    
}

BEGIN_HANDLERS(BandRetargetVignette)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xD1)
END_HANDLERS

BEGIN_PROPSYNCS(BandRetargetVignette)
    SYNC_PROP(effectors, mEffectors)
    SYNC_PROP(player, mPlayer)
    SYNC_PROP(bone, mBone)
    SYNC_PROP(prop, mProp)
END_PROPSYNCS