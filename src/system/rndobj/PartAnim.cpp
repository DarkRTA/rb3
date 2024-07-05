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

BEGIN_HANDLERS(RndParticleSysAnim)
    HANDLE_ACTION(set_particle_sys, SetParticleSys(_msg->Obj<RndParticleSys>(2)))
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x129)
END_HANDLERS

BEGIN_PROPSYNCS(RndParticleSysAnim)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS