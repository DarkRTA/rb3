#include "rndobj/Fur.h"
#include "milo_types.h"
#include "obj/Object.h"
#include "rndobj/Wind.h"
#include "utl/BinStream.h"
#include "math/Color.h"

INIT_REVS(RndFur);

RndFur::RndFur() {

}

BEGIN_COPYS(RndFur)
    CREATE_COPY_AS(RndFur, m)
    MILO_ASSERT(m, 23);
    COPY_SUPERCLASS(Hmx::Object)
END_COPYS

SAVE_OBJ(RndFur, 29)

void RndFur::Load(BinStream& bs) {
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0)
    Hmx::Object::Load(bs);
    Hmx::Color color;
    int filler2;
    int filler1;
    ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
    bs >> filler2 >> filler1 >> filler1;
    if(gRev > 1){
        bs >> filler1 >> filler1;
    }
    bs >> filler1 >> filler1 >> filler1 >> filler1;
    bs >> color >> color;
    bs >> texPtr >> filler1;
    if(gRev > 2){
        ObjPtr<RndWind, ObjectDir> windPtr(this, 0);
        bs >> windPtr;
    }
}

BEGIN_HANDLERS(RndFur);
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x3C);
END_HANDLERS;

BEGIN_PROPSYNCS(RndFur);
END_PROPSYNCS;
