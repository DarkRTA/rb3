#pragma once
#include "rndobj/Draw.h"
#include "rndobj/Env.h"

class RndShadowMap {
public:
    static bool PrepShadow(RndDrawable *, RndEnviron *);
    static void EndShadow();
};