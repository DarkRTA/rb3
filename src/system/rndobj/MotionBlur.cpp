#include "rndobj/MotionBlur.h"
#include "rndobj/Mesh.h"
#include "rndobj/Dir.h"
#include "rndobj/Group.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

INIT_REVS(RndMotionBlur);

RndMotionBlur::RndMotionBlur() : mDrawList(this, kObjListNoNull) {

}

BEGIN_COPYS(RndMotionBlur)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
    CREATE_COPY(RndMotionBlur)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mDrawList)
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(RndMotionBlur, 0x2B)

void RndMotionBlur::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    RndDrawable::Load(bs);
    bs >> mDrawList;
}

bool RndMotionBlur::CanMotionBlur(RndDrawable* draw){
    if(dynamic_cast<RndMesh*>(draw) || dynamic_cast<RndDir*>(draw) || dynamic_cast<RndGroup*>(draw)) return true;
    else return false;
}

BEGIN_HANDLERS(RndMotionBlur)
    HANDLE(allowed_drawable, OnAllowedDrawable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x83)
END_HANDLERS

BEGIN_PROPSYNCS(RndMotionBlur)
    SYNC_PROP(draw_list, mDrawList)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
