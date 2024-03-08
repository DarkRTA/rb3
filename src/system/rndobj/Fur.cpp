#include "rndobj/Fur.h"
#include "milo_types.h"
#include "obj/Object.h"
#include "rndobj/Wind.h"
#include "utl/BinStream.h"

RndFur::RndFur() {
    
}

BEGIN_COPYS(RndFur)
    GET_COPY_AND_ASSERT(RndFur, 23)
    COPY_SUPERCLASS(Hmx::Object)
END_COPYS

SAVE_OBJ(RndFur, 29)

void RndFur::Load(BinStream& bs) {
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0)
    Hmx::Object::Load(bs);

    float dump3 = 1;
    float dump2 = 1;
    float test = 1;
    ObjPtr<RndTex,ObjectDir> tex(this, NULL);
    int dump;

    bs >> test;
    bs >> dump;
    bs >> dump;
    if (gRev > 1) {
        bs >> dump;
        bs >> dump;
    }
    bs >> dump;
    bs >> dump;
    bs >> dump; 
    bs >> dump;
    bs >> test;
    bs >> dump2;

    bs >> tex;
    bs >> dump;
    if (gRev > 2) {
        ObjPtr<RndWind, ObjectDir> wind(this, NULL);
        bs >> wind;
    }
}

BEGIN_HANDLERS(RndFur);
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x3C);
END_HANDLERS;

BEGIN_PROPSYNCS(RndFur);
END_PROPSYNCS;
