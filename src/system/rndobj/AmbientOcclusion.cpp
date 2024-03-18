#include "rndobj/AmbientOcclusion.h"
#include "obj/ObjPtr_p.h"

INIT_REVS(RndAmbientOcclusion);

RndAmbientOcclusion::RndAmbientOcclusion(){
    
}

SAVE_OBJ(RndAmbientOcclusion, 0x28);

void RndAmbientOcclusion::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(4, 0);
    Hmx::Object::Load(bs);
    int i, j;
    unsigned char c, d, e, f;
    ObjPtrList<Hmx::Object, ObjectDir> pList(this, kObjListNoNull);
    bs >> pList;
    bs >> pList;
    bs >> pList;
    bs >> c;
    bs >> d;
    bs >> e;
    bs >> f;
    if(gRev > 1){
        bs >> i;
        bs >> j;
        bs >> j;
        bs >> j;
    }
    if(gRev > 2) bs >> i;
}

void RndAmbientOcclusion::Copy(const Hmx::Object* o, Hmx::Object::CopyType ty){
    Hmx::Object::Copy(o, ty);
}

BEGIN_HANDLERS(RndAmbientOcclusion);
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x55);
END_HANDLERS;

BEGIN_PROPSYNCS(RndAmbientOcclusion);
END_PROPSYNCS;

static void rndacsettype(RndAmbientOcclusion* ac){
    ac->SetType(Symbol());
}
