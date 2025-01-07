#include "Lit.h"
#include "math/Color.h"
#include "math/Rot.h"
#include "revolution/gx/GXLight.h"
#include "revolution/gx/GXTypes.h"
#include <cmath>

void WiiLight::Update(GXLightID lit) {
    Hmx::Color src_col = GetColor(); src_col.alpha = 0;

    if (!mOnlyProjection) {
        int c = src_col.Pack(); // something like this, not sure
        GXInitLightColor(&mLight, *(GXColor*)&c);
    }

    if (unk_0x15C && !mOnlyProjection) {
        if (mType != kFakeSpot) {
            GXInitLightAttn(&mLight,Intensity(),0,0,1,1 / mRange,0);
        } else {
            GXInitLightDistAttn(&mLight, mRange / 2, 0.3, GX_DA_STEEP);
            GXInitLightSpot(&mLight, GetLightFieldOfView() / 2, GX_SP_FLAT);
        }
        unk_0x15C = 0;
    }
    UpdatePosition();
    if (!mOnlyProjection) {
        GXLoadLightObjImm(&mLight, lit);
    }
}

void WiiLight::UpdatePosition() {
    Transform& t = WorldXfm();
}

float WiiLight::GetLightFieldOfView() {
    Transform t = WorldXfm();

    // this nightmare spaghetti removes 90% of the regswaps. end mii
    float magic_bs = std::atan2(mBotRadius, mRange + mBotRadius / ((mBotRadius - mTopRadius) / mRange));
    return (magic_bs * 2) * 180 / float(PI);
}

Vector3 WiiLight::CalcAdjustedPos() {
    Transform t = WorldXfm();
    float f = (mBotRadius - mTopRadius);
    Vector3 v(0, -(mTopRadius / (f / mRange)), 0);
    Multiply(v, t.m, v);
    Add(v, t.v, v);
    return v;
}
