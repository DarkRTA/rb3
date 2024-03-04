#include "rndobj/AmbientOcclusion.h"

RndAmbientOcclusion::RndAmbientOcclusion(){
    
}

void RndAmbientOcclusion::Save(BinStream&){
    MILO_ASSERT(0, 0x28);
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
