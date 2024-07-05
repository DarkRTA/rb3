#include "rndobj/PartAnim.h"
#include "utl/Symbols.h"

RndParticleSysAnim::RndParticleSysAnim() : mParticleSys(this, 0), mKeysOwner(this, this) {

}

void RndParticleSysAnim::SetParticleSys(RndParticleSys* sys){ mParticleSys = sys; }

BEGIN_HANDLERS(RndParticleSysAnim)
    HANDLE_ACTION(set_particle_sys, SetParticleSys(_msg->Obj<RndParticleSys>(2)))
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x129)
END_HANDLERS

BEGIN_PROPSYNCS(RndParticleSysAnim)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS