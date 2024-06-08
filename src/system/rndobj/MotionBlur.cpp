#include "rndobj/MotionBlur.h"
#include "rndobj/Mesh.h"
#include "rndobj/Dir.h"
#include "rndobj/Group.h"
#include "obj/DirItr.h"
#include "obj/PropSync_p.h"
#include "utl/Symbols.h"

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

void RndMotionBlur::DrawShowing(){}

bool RndMotionBlur::CanMotionBlur(RndDrawable* draw){
    if(dynamic_cast<RndMesh*>(draw) || dynamic_cast<RndDir*>(draw) || dynamic_cast<RndGroup*>(draw)) return true;
    else return false;
}

DataNode RndMotionBlur::OnAllowedDrawable(const DataArray* da){
    int allowcount = 0;
    for(ObjDirItr<RndDrawable> it(Dir(), true); it != 0; ++it){
        if(CanMotionBlur(it)) allowcount++;
    }
    DataArrayPtr ptr(new DataArray(allowcount));
    allowcount = 0;
    for(ObjDirItr<RndDrawable> it(Dir(), true); it != 0; ++it){
        if(CanMotionBlur(it)){
            ptr.Node(allowcount++) = DataNode(it);
        }
    }
    return DataNode(ptr);
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

DECOMP_FORCEFUNC(MotionBlur, RndMotionBlur, SetType)