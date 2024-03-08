#ifndef RNDOBJ_PART_H
#define RNDOBJ_PART_H

#include "rndobj/Trans.h"
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "rndobj/Anim.h"

struct RndParticle {
    float a;
    float b;
    float c;
    float d;
    float e;
    float f;
    float g;
    float h;
};

class RndParticleSys : public RndTransformable, public RndDrawable, public RndPollable, public RndAnimatable {

};

#endif // RNDOBJ_PART_H
