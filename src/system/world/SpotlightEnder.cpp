#include "world/SpotlightEnder.h"

INIT_REVS(SpotlightEnder)

SpotlightEnder::SpotlightEnder(){
    mOrder = -900.0f;
}

SpotlightEnder::~SpotlightEnder(){

}

void SpotlightEnder::DrawShowing(){
    
}

BEGIN_LOADS(SpotlightEnder)
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndDrawable)
END_LOADS

SAVE_OBJ(SpotlightEnder, 0x2F)

BEGIN_COPYS(SpotlightEnder)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
END_COPYS

BEGIN_HANDLERS(SpotlightEnder)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x3F)
END_HANDLERS

BEGIN_PROPSYNCS(SpotlightEnder)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS