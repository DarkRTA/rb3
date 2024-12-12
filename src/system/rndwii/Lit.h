#pragma once

#include "revolution/gx/GXTypes.h"
#include "rndobj/Lit.h"

class WiiLight : public RndLight {
public:
    WiiLight() {}
    virtual ~WiiLight() {}

    void Update(GXLightID);
};
