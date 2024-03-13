#include "rndobj/Dir.h"

RndDir::RndDir() : mEnv(this, 0) {
    
}

void RndDir::Replace(Hmx::Object* o1, Hmx::Object* o2){
    MsgSource::Replace(o1, o2);
    RndTransformable::Replace(o1, o2);
}

SAVE_OBJ(RndDir, 0x1C1)
