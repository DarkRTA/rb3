#include "rndobj/Fur.h"

RndFur::RndFur(){
    
}

void RndFur::Copy(const Hmx::Object* o, Hmx::Object::CopyType ty){
    const RndFur* m = dynamic_cast<const RndFur*>(o);
    MILO_ASSERT(m, 0x17);
    Hmx::Object::Copy(o, ty);
}

void RndFur::Save(BinStream&){
    MILO_ASSERT(0, 0x1D);
}

BEGIN_HANDLERS(RndFur);
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x3C);
END_HANDLERS;

BEGIN_PROPSYNCS(RndFur);
END_PROPSYNCS;
