#include "rndobj/Part.h"
#include "rndobj/Mesh.h"
#include "rndobj/Mat.h"
#include "utl/Symbols.h"

RndParticleSys::~RndParticleSys(){

}

RndParticleSys::RndParticleSys() : mType(t0), mMaxParticles(0), unkd0(0), unkd4(0), unkd8(0), unkdc(0), unke0(0.0f), unke4(0.0f), mMesh(this, 0),
    mMat(this, 0), mRelativeParent(this, 0), mBounce(this, 0), mGrowRatio(0.0f) {

}

bool AngleVectorSync(Vector2&, DataNode&, DataArray*, int, PropOp){

}

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(RndParticleSys)
    SYNC_PROP(mat, mMat)
    SYNC_PROP_SET(max_parts, mMaxParticles, SetPool(_val.Int(0), mType))
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
    SYNC_PROP_SET(fancy, mType, SetPool(mMaxParticles, (Type)_val.Int(0)))
    SYNC_PROP_SET(grow_ratio, mGrowRatio, SetGrowRatio(_val.Float(0)))
    SYNC_PROP_SET(shrink_ratio, mShrinkRatio, SetShrinkRatio(_val.Float(0)))
    SYNC_PROP(drag, mDrag)
    SYNC_PROP(mid_color_ratio, mMidColorRatio)
    SYNC_PROP(mid_color_low, mMidColorLow)
    SYNC_PROP(mid_color_high, mMidColorHigh)
    SYNC_PROP(mid_alpha_low, mMidColorLow.alpha)
    SYNC_PROP(mid_alpha_high, mMidColorHigh.alpha)
    {
        static Symbol _s("bubble");
        if(sym == _s){
            if(_op == kPropSet){ mBubble = _val.Int(0); }
            else _val = DataNode(mBubble);
            return true;
        }
    }
    SYNC_PROP(bubble_period, mBubblePeriod)
    SYNC_PROP(bubble_size, mBubbleSize)
    SYNC_PROP(max_burst, mMaxBurst)
    SYNC_PROP(time_between, mTimeBetween)
    SYNC_PROP(peak_rate, mPeakRate)
    SYNC_PROP(duration, mDuration)
    {
        static Symbol _s("spin");
        if(sym == _s){
            if(_op == kPropSet){ mSpin = _val.Int(0); }
            else _val = DataNode(mSpin);
            return true;
        }
    }
    SYNC_PROP(rpm, mRPM)
    SYNC_PROP(rpm_drag, mRPMDrag)
    SYNC_PROP(start_offset, mStartOffset)
    SYNC_PROP(end_offset, mEndOffset)
    {
        static Symbol _s("random_direction");
        if(sym == _s){
            if(_op == kPropSet){ mRandomDirection = _val.Int(0); }
            else _val = DataNode(mRandomDirection);
            return true;
        }
    }
    {
        static Symbol _s("velocity_align");
        if(sym == _s){
            if(_op == kPropSet){ mVelocityAlign = _val.Int(0); }
            else _val = DataNode(mVelocityAlign);
            return true;
        }
    }
    {
        static Symbol _s("stretch_with_velocity");
        if(sym == _s){
            if(_op == kPropSet){ mStretchWithVelocity = _val.Int(0); }
            else _val = DataNode(mStretchWithVelocity);
            return true;
        }
    }
    SYNC_PROP(stretch_scale, mStretchScale)
    {
        static Symbol _s("constant_area");
        if(sym == _s){
            if(_op == kPropSet){ mConstantArea = _val.Int(0); }
            else _val = DataNode(mConstantArea);
            return true;
        }
    }
    {
        static Symbol _s("perspective");
        if(sym == _s){
            if(_op == kPropSet){ mPerspective = _val.Int(0); }
            else _val = DataNode(mPerspective);
            return true;
        }
    }
    SYNC_PROP_SET(mesh_emitter, mMesh, SetMesh(_val.Obj<RndMesh>(0)))
    SYNC_PROP(box_extent_1, mBoxExtent1)
    SYNC_PROP(box_extent_2, mBoxExtent2)
    {
        static Symbol _s("pitch");
        if(sym == _s){
            AngleVectorSync(mPitch, _val, _prop, _i + 1, _op);
            return true;
        }
    }
    {
        static Symbol _s("yaw");
        if(sym == _s){
            AngleVectorSync(mYaw, _val, _prop, _i + 1, _op);
            return true;
        }
    }
    SYNC_PROP_SET(relative_parent, mRelativeParent, SetRelativeMotion(mRelativeMotion, _val.Obj<RndTransformable>(0)))
    SYNC_PROP_SET(relative_motion, mRelativeMotion, SetRelativeMotion(_val.Float(0), mRelativeParent))
    SYNC_PROP_SET(subsamples, mSubSamples, SetSubSamples(_val.Int(0)))
    SYNC_PROP_SET(frame_drive, mFrameDrive, SetFrameDrive(_val.Int(0)))
    {
        static Symbol _s("pre_spawn");
        if(sym == _s){
            if(_op == kPropSet){ mPreSpawn = _val.Int(0); }
            else _val = DataNode(mPreSpawn);
            return true;
        }
    }
    SYNC_PROP_SET(pause_offscreen, mPauseOffscreen, SetPauseOffscreen(_val.Int(0)))
    SYNC_SUPERCLASS(RndAnimatable)
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
#pragma pop