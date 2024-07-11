#include "rndobj/Part.h"
#include "rndobj/Mesh.h"
#include "rndobj/Mat.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

RndParticleSys::~RndParticleSys(){

}

RndParticleSys::RndParticleSys() : mType(t0), mMaxParticles(0), unkd0(0), unkd4(0), unkd8(0), unkdc(0), unke0(0.0f), unke4(0.0f), unke8(0), unkec(0.0f),
    mBubblePeriod(10.0f, 10.0f), mBubbleSize(1.0f, 1.0f), mLife(100.0f, 100.0f), mBoxExtent1(0.0f, 0.0f, 0.0f), mBoxExtent2(0.0f, 0.0f, 0.0f),
    mSpeed(1.0f, 1.0f), mPitch(0.0f, 0.0f), mYaw(0.0f, 0.0f), mEmitRate(1.0f, 1.0f), mStartSize(1.0f, 1.0f), mDeltaSize(0.0f, 0.0f),
    mMesh(this, 0), mMat(this, 0), mPreserveParticles(0), mRelativeParent(this, 0), mBounce(this, 0), mForceDir(0.0f, 0.0f, 0.0f), mDrag(0.0f),
    mRPM(0.0f, 0.0f), mRPMDrag(0.0f), mStartOffset(0.0f, 0.0f), mEndOffset(0.0f, 0.0f), mStretchScale(1.0f), mScreenAspect(1.0f), mSubSamples(0),
    mGrowRatio(0.0f), mShrinkRatio(1.0f), mMidColorRatio(0.5f), mMaxBurst(0), unk2c8(0.0f), mTimeBetween(15.0f, 35.0f), mPeakRate(4.0f, 8.0f),
    mDuration(20.0f, 30.0f), unk2e4(0), unk2e8(0.0f) {
    SetRelativeMotion(0.0f, this);
    SetSubSamples(0);
}

void RndParticleSys::Replace(Hmx::Object* from, Hmx::Object* to){
    RndTransformable::Replace(from, to);
    if(from == mRelativeParent){
        RndTransformable* t = dynamic_cast<RndTransformable*>(to);
        SetRelativeMotion(mRelativeMotion, t);
    }
}

void RndParticleSys::SetMat(RndMat* mat){ mMat = mat; }

void RndParticleSys::SetMesh(RndMesh* mesh){
    if(mesh){
        SetTransParent(mesh, false);
        SetTransConstraint(RndTransformable::kParentWorld, 0, false);
        if(!mesh->mKeepMeshData){
            MILO_WARN("keep_mesh_data should be checked for %s.  It's the mesh emitter for %s.\n", PathName(mesh), PathName(this));
        }
    }
    else if(mMesh){
        SetTransParent(0, false);
        SetTransConstraint(RndTransformable::kNone, 0, false);
    }
    mMesh = mesh;
}

void RndParticleSys::SetGrowRatio(float f){
    if(f >= 0.0f && f <= mShrinkRatio) mGrowRatio = f;
}

void RndParticleSys::SetShrinkRatio(float f){
    if(f >= mGrowRatio && f <= 1.0f) mShrinkRatio = f;
}

void RndParticleSys::Mats(std::list<class RndMat*>& mats, bool b){
    if(mMat){
        mMat->mShaderOptions = GetDefaultMatShaderOpts(this, mMat);
        mats.push_back(mMat);
    }
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(RndParticleSys)
    HANDLE_EXPR(hi_emit_rate, Max(mEmitRate.x, mEmitRate.y))
    HANDLE(set_start_color, OnSetStartColor)
    HANDLE(set_end_color, OnSetEndColor)
    HANDLE(set_start_color_int, OnSetStartColorInt)
    HANDLE(set_end_color_int, OnSetEndColorInt)
    HANDLE(set_emit_rate, OnSetEmitRate)
    HANDLE(set_burst_interval, OnSetBurstInterval)
    HANDLE(set_burst_peak, OnSetBurstPeak)
    HANDLE(set_burst_length, OnSetBurstLength)
    HANDLE(add_emit_rate, OnAddEmitRate)
    HANDLE(launch_part, OnExplicitPart)
    HANDLE(launch_parts, OnExplicitParts)
    HANDLE(set_life, OnSetLife)
    HANDLE(set_speed, OnSetSpeed)
    HANDLE(set_rotate, OnSetRotate)
    HANDLE(set_swing_arm, OnSetSwingArm)
    HANDLE(set_drag, OnSetDrag)
    HANDLE(set_alignment, OnSetAlignment)
    HANDLE(set_start_size, OnSetStartSize)
    HANDLE(set_mat, OnSetMat)
    HANDLE(set_pos, OnSetPos)
    HANDLE_ACTION(set_mesh, SetMesh(_msg->Obj<RndMesh>(2)))
    HANDLE(active_particles, OnActiveParticles)
    HANDLE_EXPR(max_particles, MaxParticles())
    HANDLE_ACTION(set_relative_parent, SetRelativeMotion(mRelativeMotion, _msg->Obj<RndTransformable>(2)))
    HANDLE_ACTION(clear_all_particles, FreeAllParticles())
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x7B6)
END_HANDLERS
#pragma pop

bool AngleVectorSync(Vector2& vec, DataNode& _val, DataArray* _prop, int _i, PropOp _op){
    if(_i == _prop->Size()) return true;
    else {
        Symbol sym = _prop->Sym(_i);
        if(sym == x){
            if(_op == kPropSet) vec.x = _val.Float(0) * 0.017453292f;
            else if(_op == kPropGet) _val = DataNode(vec.x * 57.295776f);
            else return false;
        }
        else if(sym == y){
            vec.x = vec.y;
        }
        else return false;
    }
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