#ifndef RNDOBJ_PART_H
#define RNDOBJ_PART_H

#include "math/Color.h"
#include "math/Vec.h"
#include "rndobj/Trans.h"
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "rndobj/Anim.h"

struct RndParticle {
    Hmx::Color col;
    Hmx::Color colVel;
    Vector4 pos;
    Vector4 vel;
    float deathFrame;
    float birthFrame;
    float size;
    float sizeVel;
    float angle;
    float swingArm;
    RndParticle* prev;
    RndParticle* next;
};

class RndParticleSys : public RndTransformable, public RndDrawable, public RndPollable, public RndAnimatable {

};

#endif // RNDOBJ_PART_H
