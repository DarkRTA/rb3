#include "rndobj/Part.h"
#include "rndobj/Mesh.h"
#include "rndobj/Mat.h"
#include "rndobj/Utl.h"
#include "utl/MemMgr.h"
#include "obj/DataFunc.h"
#include "utl/Symbols.h"

PartOverride gNoPartOverride;
ParticleCommonPool* gParticlePool;

namespace {
    int ParticlePoolSize(){
        return SystemConfig("rnd", "particlesys", "global_limit")->Int(1);
    }

    DataNode PrintParticlePoolSize(DataArray* da){
        MILO_LOG("Particle Pool Size:\n");
        if(gParticlePool){
            int size = ParticlePoolSize();
            MILO_LOG("   %d particles can be allocated, %.1f KB.\n", size, (float)size);
            MILO_LOG("   %d particles active, %d is the high water mark.\n", gParticlePool->mNumActiveParticles, gParticlePool->mHighWaterMark);
            MILO_LOG("   Adding 30%%, suggesting a particle global limit of %d (set in default.dta).\n", (int)(gParticlePool->mHighWaterMark * 1.3f));
        }
        return DataNode(0);
    }
}

void InitParticleSystem(){
    if(!gParticlePool) gParticlePool = new ParticleCommonPool();
    if(gParticlePool) gParticlePool->InitPool();
    DataRegisterFunc("print_particle_pool_size", PrintParticlePoolSize);
}

int GetParticleHighWaterMark(){
    int ret = 0;
    if(gParticlePool) ret = gParticlePool->mHighWaterMark;
    return ret;
}

void ParticleCommonPool::InitPool(){
    static int x = MemFindHeap("main");
    MemPushHeap(x);
    mPoolParticles = new RndFancyParticle[0xb0];
}

SAVE_OBJ(RndParticleSys, 0x13D)

BinStream& operator>>(BinStream&, RndParticle&);

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
        if(!mesh->KeepMeshData()){
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

DataNode RndParticleSys::OnSetStartColor(const DataArray* da){
    DataArray* arr1 = da->Array(2);
    DataArray* arr2 = da->Array(3);
    SetStartColor(Hmx::Color(arr1->Float(0), arr1->Float(1), arr1->Float(2), arr1->Float(3)),
        Hmx::Color(arr2->Float(0), arr2->Float(1), arr2->Float(2), arr2->Float(3)));
    return DataNode(0);
}

DataNode RndParticleSys::OnSetStartColorInt(const DataArray* da){
    Hmx::Color col1(da->Int(2));
    Hmx::Color col2(da->Int(3));
    col1.alpha = da->Float(4);
    col2.alpha = da->Float(5);
    SetStartColor(col1,col2);
    return DataNode(0);
}

DataNode RndParticleSys::OnSetEmitRate(const DataArray* da){
    SetEmitRate(da->Float(2), da->Float(3));
    return DataNode(0);
}

DataNode RndParticleSys::OnAddEmitRate(const DataArray* da){
    float add = da->Float(2);
    mEmitRate.x = Max(0.0f, mEmitRate.x + add);
    mEmitRate.y = Max(0.0f, mEmitRate.y + add);
    return DataNode(!mEmitRate);
}

DataNode RndParticleSys::OnSetBurstInterval(const DataArray* da){
    SetMaxBurst(da->Int(2));
    SetTimeBetweenBursts(da->Float(3), da->Float(4));
    return DataNode(0);
}

DataNode RndParticleSys::OnSetBurstPeak(const DataArray* da){
    SetPeakRate(da->Float(2), da->Float(3));
    return DataNode(0);
}

DataNode RndParticleSys::OnSetBurstLength(const DataArray* da){
    SetDuration(da->Float(2), da->Float(3));
    return DataNode(0);
}

DataNode RndParticleSys::OnExplicitPart(const DataArray* da){
    ExplicitParticles(1, false, gNoPartOverride);
    return DataNode(0);
}

DataNode RndParticleSys::OnExplicitParts(const DataArray* da){
    bool b = false;
    if(da->Size() >= 4 && da->Int(3) != 0) b = true;
    ExplicitParticles(da->Int(2), b, gNoPartOverride);
    return DataNode(0);
}

DataNode RndParticleSys::OnSetLife(const DataArray* da){
    SetLife(da->Float(2), da->Float(3));
    return DataNode(0);
}

DataNode RndParticleSys::OnSetSpeed(const DataArray* da){
    SetSpeed(da->Float(2), da->Float(3));
    return DataNode(0);
}

DataNode RndParticleSys::OnSetRotate(const DataArray* da){
    SetSpin(da->Int(2));
    SetRPM(da->Float(3), da->Float(4));
    SetRPMDrag(da->Float(4));
    return DataNode(0);
}

DataNode RndParticleSys::OnSetSwingArm(const DataArray* da){
    SetStartOffset(da->Float(2), da->Float(3));
    SetEndOffset(da->Float(4), da->Float(5));
    return DataNode(0);
}

DataNode RndParticleSys::OnSetDrag(const DataArray* da){
    SetDrag(da->Float(2));
    return DataNode(0);
}

DataNode RndParticleSys::OnSetAlignment(const DataArray* da){
    SetVelocityAlign(da->Int(2));
    SetStretchWithVelocity(da->Int(3));
    SetConstantArea(da->Int(4));
    SetStretchScale(da->Float(5));
    return DataNode(0);
}

DataNode RndParticleSys::OnSetStartSize(const DataArray* da){
    SetStartSize(da->Float(2), da->Float(3));
    return DataNode(0);
}

DataNode RndParticleSys::OnSetMat(const DataArray* da){
    SetMat(da->Obj<RndMat>(2));
    return DataNode(0);
}

DataNode RndParticleSys::OnSetPos(const DataArray* da){
    SetBoxExtent(Vector3(da->Float(2), da->Float(3), da->Float(4)), Vector3(da->Float(5), da->Float(6), da->Float(7)));
    return DataNode(0);
}

DataNode RndParticleSys::OnActiveParticles(const DataArray* da){
    return DataNode(unkd8 != 0);
}

BinStream& operator>>(BinStream& bs, RndParticle& part){
    bs >> part.pos >> part.col >> part.size;
    return bs;
}

bool AngleVectorSync(Vector2& vec, DataNode& _val, DataArray* _prop, int _i, PropOp _op){
    if(_i == _prop->Size()) return true;
    else {
        Symbol sym = _prop->Sym(_i);
        if(sym == x){
            if(_op == kPropSet) vec.x = DegreesToRadians(_val.Float());
            else if(_op == kPropGet) _val = DataNode(RadiansToDegrees(vec.x));
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
    SYNC_PROP_SET(max_parts, mMaxParticles, SetPool(_val.Int(), GetType()))
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
    SYNC_PROP_SET(fancy, mType, SetPool(mMaxParticles, (Type)_val.Int()))
    SYNC_PROP_SET(grow_ratio, mGrowRatio, SetGrowRatio(_val.Float()))
    SYNC_PROP_SET(shrink_ratio, mShrinkRatio, SetShrinkRatio(_val.Float()))
    SYNC_PROP(drag, mDrag)
    SYNC_PROP(mid_color_ratio, mMidColorRatio)
    SYNC_PROP(mid_color_low, mMidColorLow)
    SYNC_PROP(mid_color_high, mMidColorHigh)
    SYNC_PROP(mid_alpha_low, mMidColorLow.alpha)
    SYNC_PROP(mid_alpha_high, mMidColorHigh.alpha)
    {
        static Symbol _s("bubble");
        if(sym == _s){
            if(_op == kPropSet){ mBubble = _val.Int(); }
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
            if(_op == kPropSet){ mSpin = _val.Int(); }
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
            if(_op == kPropSet){ mRandomDirection = _val.Int(); }
            else _val = DataNode(mRandomDirection);
            return true;
        }
    }
    {
        static Symbol _s("velocity_align");
        if(sym == _s){
            if(_op == kPropSet){ mVelocityAlign = _val.Int(); }
            else _val = DataNode(mVelocityAlign);
            return true;
        }
    }
    {
        static Symbol _s("stretch_with_velocity");
        if(sym == _s){
            if(_op == kPropSet){ mStretchWithVelocity = _val.Int(); }
            else _val = DataNode(mStretchWithVelocity);
            return true;
        }
    }
    SYNC_PROP(stretch_scale, mStretchScale)
    {
        static Symbol _s("constant_area");
        if(sym == _s){
            if(_op == kPropSet){ mConstantArea = _val.Int(); }
            else _val = DataNode(mConstantArea);
            return true;
        }
    }
    {
        static Symbol _s("perspective");
        if(sym == _s){
            if(_op == kPropSet){ mPerspective = _val.Int(); }
            else _val = DataNode(mPerspective);
            return true;
        }
    }
    SYNC_PROP_SET(mesh_emitter, mMesh, SetMesh(_val.Obj<RndMesh>()))
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
    SYNC_PROP_SET(relative_parent, mRelativeParent, SetRelativeMotion(mRelativeMotion, _val.Obj<RndTransformable>()))
    SYNC_PROP_SET(relative_motion, mRelativeMotion, SetRelativeMotion(_val.Float(), mRelativeParent))
    SYNC_PROP_SET(subsamples, mSubSamples, SetSubSamples(_val.Int()))
    SYNC_PROP_SET(frame_drive, mFrameDrive, SetFrameDrive(_val.Int()))
    {
        static Symbol _s("pre_spawn");
        if(sym == _s){
            if(_op == kPropSet){ mPreSpawn = _val.Int(); }
            else _val = DataNode(mPreSpawn);
            return true;
        }
    }
    SYNC_PROP_SET(pause_offscreen, mPauseOffscreen, SetPauseOffscreen(_val.Int()))
    SYNC_SUPERCLASS(RndAnimatable)
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
#pragma pop
