#include "rndobj/EnvAnim.h"
#include "math/MathFuncs.h"
#include "decomp.h"

int ENVANIM_REV = 4;

DECOMP_FORCEACTIVE(EnvAnim,
    __FILE__,
    "o"
)

RndEnvAnim::RndEnvAnim() : mEnviron(this, 0), mKeysOwner(this, this) {

}

void RndEnvAnim::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mKeysOwner.Ptr() == from){
        if(!to) mKeysOwner = this;
        else mKeysOwner = dynamic_cast<RndEnvAnim*>(to)->mKeysOwner.Ptr();
    }
}

SAVE_OBJ(RndEnvAnim, 0x46)

BEGIN_LOADS(RndEnvAnim)
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, ENVANIM_REV)
    if(rev > 3) LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndAnimatable)
    bs >> mEnviron >> mAmbientColorKeys >> mKeysOwner;
    if(!mKeysOwner.Ptr()) mKeysOwner = this;
    if(rev > 1) bs >> mFogColorKeys;
    if(rev > 2) bs >> mFogRangeKeys;
END_LOADS

BEGIN_COPYS(RndEnvAnim)
    CREATE_COPY_AS(RndEnvAnim, l);
    MILO_ASSERT(l, 0x6B);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_MEMBER_FROM(l, mEnviron)
    if(ty == kCopyShallow){
        COPY_MEMBER_FROM(l, mKeysOwner)
    }
    else {
        mKeysOwner = this;
        mAmbientColorKeys = l->mKeysOwner->mAmbientColorKeys;
        mFogColorKeys = l->mKeysOwner->mFogColorKeys;
        mFogRangeKeys = l->mKeysOwner->mFogRangeKeys;
    }
END_COPYS

void RndEnvAnim::Print(){
    TextStream& ts = TheDebug;
    ts << "   environ: " << mEnviron.Ptr() << "\n";
    ts << "   keysOwner: " << mKeysOwner.Ptr() << "\n";
    ts << "   ambientColorKeys: " << mAmbientColorKeys << "\n";
    ts << "   fogColorKeys: " << mFogColorKeys << "\n";
    ts << "   fogRangeKeys: " << mFogRangeKeys << "\n";
}

// fn_805DB064
float RndEnvAnim::EndFrame(){
    return Max(FogColorKeys().LastFrame(), AmbientColorKeys().LastFrame());
}

// fn_805DB174
void RndEnvAnim::SetFrame(float frame, float blend){
    RndAnimatable::SetFrame(frame, blend);
    if(mEnviron){
        if(!AmbientColorKeys().empty()){
            Hmx::Color col(mEnviron->AmbientColor());
            AmbientColorKeys().AtFrame(frame, col);
            if(blend != 1.0f){
                Interp(mEnviron->AmbientColor(), col, blend, col);
            }
            mEnviron->SetAmbientColor(col);
        }
        if(!FogColorKeys().empty()){
            Hmx::Color col(mEnviron->FogColor());
            FogColorKeys().AtFrame(frame, col);
            if(blend != 1.0f){
                Interp(mEnviron->FogColor(), col, blend, col);
            }
            mEnviron->SetFogColor(col);
        }
        if(!FogRangeKeys().empty()){
            Vector2 vec(mEnviron->GetFogStart(), mEnviron->GetFogEnd());
            FogRangeKeys().AtFrame(frame, vec);
            if(blend != 1.0f){
                Interp(mEnviron->GetFogStart(), vec.x, blend, vec.x);
                Interp(mEnviron->GetFogEnd(), vec.y, blend, vec.y);
            }
            mEnviron->SetFogRange(vec.x, vec.y);
        }
    }
}

// fn_805DB940
void RndEnvAnim::SetKey(float frame){
    if(mEnviron){
        FogColorKeys().Add(mEnviron->FogColor(), frame, true);
        FogRangeKeys().Add(Vector2(mEnviron->GetFogStart(), mEnviron->GetFogEnd()), frame, true);
        AmbientColorKeys().Add(mEnviron->AmbientColor(), frame, true);
    }
}

BEGIN_HANDLERS(RndEnvAnim)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xD5)
END_HANDLERS

BEGIN_PROPSYNCS(RndEnvAnim)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
