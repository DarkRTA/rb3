#pragma once

#include <revolution/GX.h>
#include "rndobj/Lit.h"

class WiiLight : public RndLight {
public:
    WiiLight() {}
    virtual ~WiiLight() {}

    void Update(GXLightID);
    void UpdatePosition();
    float GetLightFieldOfView();
    Vector3 CalcAdjustedPos();

    u16 _pad;
    GXLightObj mLight; // 0x11C
    bool unk_0x15C;
};
