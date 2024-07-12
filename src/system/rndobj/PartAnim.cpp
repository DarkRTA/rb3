#include "rndobj/PartAnim.h"
#include "utl/Symbols.h"

int PARTANIM_REV = 3;

DECOMP_FORCEACTIVE(PartAnim, __FILE__, "o", "0")

RndParticleSysAnim::RndParticleSysAnim() : mParticleSys(this, 0), mKeysOwner(this, this) {

}

void RndParticleSysAnim::SetParticleSys(RndParticleSys* sys){ mParticleSys = sys; }

void RndParticleSysAnim::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mKeysOwner == from){
        if(!to) mKeysOwner = this;
        else mKeysOwner = dynamic_cast<RndParticleSysAnim*>(to)->mKeysOwner;
    }
}

SAVE_OBJ(RndParticleSysAnim, 0x45)

BEGIN_LOADS(RndParticleSysAnim)
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, PARTANIM_REV)
    if(rev > 2) LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndAnimatable)
    bs >> mParticleSys >> mStartColorKeys >> mEndColorKeys;
    if(rev < 2){
        float f = 1.0f;
        Keys<float, float> fKeys;
        bs >> fKeys >> mKeysOwner;
        if(rev == 1) bs >> f;
        mEmitRateKeys.clear();
        mEmitRateKeys.reserve(fKeys.size());
        for(Keys<float, float>::iterator kIt = fKeys.begin(); kIt != fKeys.end(); ++kIt){
            Key<Vector2> toPush;
            toPush.value = Vector2((*kIt).value, (*kIt).value * f);
            mEmitRateKeys.push_back(toPush);
        }
    }
    else bs >> mEmitRateKeys >> mKeysOwner;
    if(!mKeysOwner) mKeysOwner = this;
    if(rev > 1) bs >> mSpeedKeys >> mLifeKeys >> mStartSizeKeys;
END_LOADS

BEGIN_COPYS(RndParticleSysAnim)
    CREATE_COPY_AS(RndParticleSysAnim, l);
    MILO_ASSERT(l, 0x80);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_MEMBER_FROM(l, mParticleSys)
    if(ty == kCopyShallow || (ty == kCopyFromMax && l->mKeysOwner != l)){
        COPY_MEMBER_FROM(l, mKeysOwner)
    }
    else {
        mKeysOwner = this;
        mStartColorKeys = l->mKeysOwner->mStartColorKeys;
        mEndColorKeys = l->mKeysOwner->mEndColorKeys;
        mEmitRateKeys = l->mKeysOwner->mEmitRateKeys;
        mSpeedKeys = l->mKeysOwner->mSpeedKeys;
        mLifeKeys = l->mKeysOwner->mLifeKeys;
        mStartSizeKeys = l->mKeysOwner->mStartSizeKeys;
    }
END_COPYS

void RndParticleSysAnim::Print(){
    TextStream& ts = TheDebug;
    ts << "   particleSys: " << mParticleSys << "\n";
    ts << "   framesOwner: " << mKeysOwner << "\n";
    ts << "   startColorKeys: " << mStartColorKeys << "\n";
    ts << "   endColorKeys: " << mEndColorKeys << "\n";
    ts << "   emitRateKeys: " << mEmitRateKeys << "\n";
    ts << "   speedKeys: " << mSpeedKeys << "\n";
    ts << "   startSizeKeys: " << mStartSizeKeys << "\n";
    ts << "   lifeKeys: " << mLifeKeys << "\n";
}

// fn_80620E00
float RndParticleSysAnim::EndFrame(){
    float last = Max(StartColorKeys().LastFrame(), EndColorKeys().LastFrame(), EmitRateKeys().LastFrame());
    last = Max(last, SpeedKeys().LastFrame(), LifeKeys().LastFrame());
    last = Max(last, StartSizeKeys().LastFrame());
    return last;
}

#pragma push
#pragma dont_inline on
void RndParticleSysAnim::SetFrame(float frame, float blend){
    RndAnimatable::SetFrame(frame, blend);
    if(mParticleSys){
        if(!StartColorKeys().empty()){
            Hmx::Color colorlow(mParticleSys->StartColorLow());
            Hmx::Color colorhigh(mParticleSys->StartColorHigh());
            StartColorKeys().AtFrame(frame, colorlow);
            Add(colorlow, mParticleSys->StartColorHigh(), colorhigh);
            Subtract(colorhigh, mParticleSys->StartColorLow(), colorhigh);
            if(blend != 1.0f){
                Interp(mParticleSys->StartColorLow(), colorlow, blend, colorlow);
                Interp(mParticleSys->StartColorHigh(), colorhigh, blend, colorhigh);
            }
            mParticleSys->SetStartColor(colorlow, colorhigh);
        }
        if(!EndColorKeys().empty()){
            Hmx::Color colorlow(mParticleSys->EndColorLow());
            Hmx::Color colorhigh(mParticleSys->EndColorHigh());
            EndColorKeys().AtFrame(frame, colorlow);
            Add(colorlow, mParticleSys->EndColorHigh(), colorhigh);
            Subtract(colorhigh, mParticleSys->EndColorLow(), colorhigh);
            if(blend != 1.0f){
                Interp(mParticleSys->StartColorLow(), colorlow, blend, colorlow);
                Interp(mParticleSys->StartColorHigh(), colorhigh, blend, colorhigh);
            }
            mParticleSys->SetEndColor(colorlow, colorhigh);
        }
        if(!EmitRateKeys().empty()){
            Vector2 rate(mParticleSys->EmitRate());
            EmitRateKeys().AtFrame(frame, rate);
            if(blend != 1.0f){
                Interp(mParticleSys->EmitRate(), rate, blend, rate);
            }
            mParticleSys->SetEmitRate(rate.x, rate.y);
        }
        if(!SpeedKeys().empty()){
            Vector2 speed(mParticleSys->Speed());
            SpeedKeys().AtFrame(frame, speed);
            if(blend != 1.0f){
                Interp(mParticleSys->Speed(), speed, blend, speed);
            }
            mParticleSys->SetSpeed(speed.x, speed.y);
        }
        if(!LifeKeys().empty()){
            Vector2 life(mParticleSys->Life());
            LifeKeys().AtFrame(frame, life);
            if(blend != 1.0f){
                Interp(mParticleSys->Life(), life, blend, life);
            }
            mParticleSys->SetLife(life.x, life.y);
        }        
        if(!StartSizeKeys().empty()){
            Vector2 startsize(mParticleSys->StartSize());
            StartSizeKeys().AtFrame(frame, startsize);
            if(blend != 1.0f){
                Interp(mParticleSys->StartSize(), startsize, blend, startsize);
            }
            mParticleSys->SetStartSize(startsize.x, startsize.y);
        }
    }
}
#pragma pop

void RndParticleSysAnim::SetKey(float frame){
    if(mParticleSys){
        StartColorKeys().Add(mParticleSys->StartColorLow(), frame, true);
        EndColorKeys().Add(mParticleSys->EndColorLow(), frame, true);
        EmitRateKeys().Add(mParticleSys->EmitRate(), frame, true);
        SpeedKeys().Add(mParticleSys->Speed(), frame, true);
        LifeKeys().Add(mParticleSys->Life(), frame, true);
        StartSizeKeys().Add(mParticleSys->StartSize(), frame, true);
    }
}

BEGIN_HANDLERS(RndParticleSysAnim)
    HANDLE_ACTION(set_particle_sys, SetParticleSys(_msg->Obj<RndParticleSys>(2)))
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x129)
END_HANDLERS

BEGIN_PROPSYNCS(RndParticleSysAnim)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS