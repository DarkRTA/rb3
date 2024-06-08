#include "rndobj/Lit.h"
#include "obj/ObjMacros.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"
#include "os/Debug.h"

INIT_REVS(RndLight)

RndLight::RndLight() : mColor(), mColorOwner(this, this), mRange(1000.0f), mFalloffStart(0.0f), mType(kPoint), 
    mAnimateColorFromPreset(1), mAnimatePositionFromPreset(1), mAnimateRangeFromPreset(1), mShowing(1), mTexture(this, 0),
    unknownint(0), mShadowObjects(this, kObjListNoNull), mTopRadius(0.0f), mBotRadius(30.0f), mProjectedBlend(0), mOnlyProjection(0) {
        mTextureXfm.Reset();
}

SAVE_OBJ(RndLight, 0x33)

BEGIN_LOADS(RndLight)
    LOAD_REVS(bs)
    ASSERT_REVS(16, 1)
    if (gRev > 3) LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndTransformable)
    bs >> mColor;
    if (gRev < 2) {
        float f, g, h, i, j, k, l, m;
        j = k = l = m = f = g = h = i = 1;
        bs >> i >> h >> g >> f >> m >> l >> k >> j;
    }
    if (gRev < 3) {

    }
    bs >> mRange;





    if (gRev > 15) {
        unsigned char x;
        bs >> x;
        mAnimateRangeFromPreset = x;
    } else mAnimateRangeFromPreset = mAnimateColorFromPreset;
END_LOADS

BEGIN_COPYS(RndLight)
    CREATE_COPY_AS(RndLight, l)
    MILO_ASSERT(l, 0xD6);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
END_COPYS

void RndLight::SetTopRadius(float rad){ mTopRadius = rad; }
void RndLight::SetBotRadius(float rad){ mBotRadius = rad; }

BEGIN_HANDLERS(RndLight)
    HANDLE_ACTION(set_showing, mShowing = _msg->Int(2) != 0)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x186)
END_HANDLERS

BEGIN_PROPSYNCS(RndLight)
    SYNC_PROP(animate_color_from_preset, mAnimateColorFromPreset)
    SYNC_PROP(animate_position_from_preset, mAnimatePositionFromPreset)
    SYNC_PROP(animate_range_from_preset, mAnimateRangeFromPreset)
    // SYNC_PROP(type, mType)
    SYNC_PROP(range, mRange)
    SYNC_PROP(falloff_start, mFalloffStart)
END_PROPSYNCS

void RndLight::SetLightType(RndLight::Type ty){ mType = ty; }
void RndLight::SetFalloffStart(float fo){ mFalloffStart = fo; }
