#include "rndobj/LitAnim.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

RndLightAnim::RndLightAnim() : mLight(this, 0), mKeysOwner(this, this) {

}

void RndLightAnim::SetKeysOwner(RndLightAnim* o){
    MILO_ASSERT(o, 0x27);
    mKeysOwner = o;
}

SAVE_OBJ(RndLightAnim, 0x46);

BEGIN_HANDLERS(RndLightAnim)
    HANDLE(copy_keys, OnCopyKeys)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xBF)
END_HANDLERS

BEGIN_PROPSYNCS(RndLightAnim)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
