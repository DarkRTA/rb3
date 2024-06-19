#include "rndobj/Part.h"
#include "rndobj/Mesh.h"
#include "rndobj/Mat.h"
#include "utl/Symbols.h"

RndParticleSys::~RndParticleSys(){

}

RndParticleSys::RndParticleSys() : unkc8(0), mMaxParticles(0), unkd0(0), unkd4(0), unkd8(0), unkdc(0), unke0(0.0f), unke4(0.0f), mMesh(this, 0),
    mMat(this, 0), unk210(this, 0), mBounce(this, 0), mGrowRatio(0.0f) {

}

BEGIN_PROPSYNCS(RndParticleSys)
    SYNC_PROP(mat, mMat)
    SYNC_PROP_SET(max_parts, mMaxParticles, SetPool(_val.Int(0), (Type)unkc8))
    SYNC_PROP(emit_rate, mEmitRate)
    SYNC_PROP(screen_aspect, mScreenAspect)
    SYNC_PROP(life, mLife)
    SYNC_PROP(speed, mSpeed)
    SYNC_PROP(start_size, mStartSize)
    SYNC_PROP(delta_size, mDeltaSize)
    SYNC_PROP(force_dir, mForceDir)
    SYNC_PROP(bounce, mBounce)
    SYNC_PROP(start_color_low, mStartColorLow)
    SYNC_PROP(start_color_high, mStartColorHigh)
    SYNC_PROP(start_alpha_low, mStartColorLow.alpha)
    SYNC_PROP(start_alpha_high, mStartColorHigh.alpha)
    SYNC_PROP(end_color_low, mEndColorLow)
    SYNC_PROP(end_color_high, mEndColorHigh)
    SYNC_PROP(end_alpha_low, mEndColorLow.alpha)
    SYNC_PROP(end_alpha_high, mEndColorHigh.alpha)
    SYNC_PROP(preserve, mPreserveParticles)
    SYNC_PROP_SET(fancy, unkc8, SetPool(mMaxParticles, (Type)_val.Int(0)))
    SYNC_PROP_SET(grow_ratio, mGrowRatio, SetGrowRatio(_val.Float(0)))
    SYNC_PROP_SET(shrink_ratio, mShrinkRatio, SetShrinkRatio(_val.Float(0)))
    SYNC_PROP(drag, mDrag)
    SYNC_PROP(mid_color_ratio, mMidColorRatio)
    SYNC_PROP(mid_color_low, mMidColorLow)
    SYNC_PROP(mid_color_high, mMidColorHigh)
    SYNC_PROP(mid_alpha_low, mMidColorLow.alpha)
    SYNC_PROP(mid_alpha_high, mMidColorHigh.alpha)
END_PROPSYNCS