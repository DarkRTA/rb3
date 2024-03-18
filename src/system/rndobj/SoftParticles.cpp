#include "rndobj/SoftParticles.h"
#include "obj/ObjPtr_p.h"

INIT_REVS(RndSoftParticles)

RndSoftParticles::RndSoftParticles(){

}

SAVE_OBJ(RndSoftParticles, 0x22)

void RndSoftParticles::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    RndDrawable::Load(bs);
    ObjPtrList<RndDrawable, ObjectDir> pList(0, kObjListNoNull);
    // bs >> pList; whoops forgot to implement this, should probably do that
}

BEGIN_COPYS(RndSoftParticles)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
END_COPYS

BEGIN_HANDLERS(RndSoftParticles)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x3B)
END_HANDLERS

BEGIN_PROPSYNCS(RndSoftParticles)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
