#include "rndobj/EnvAnim.h"

int ENVANIM_REV = 4;

static const char* unused(int o){
    MILO_ASSERT(o, 0x69);
}

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

void RndEnvAnim::Load(BinStream& bs){
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, ENVANIM_REV)
    if(rev > 3) Hmx::Object::Load(bs);
    RndAnimatable::Load(bs);
    bs >> mEnviron >> mAmbientColorKeys >> mKeysOwner;
    if(!mKeysOwner.Ptr()) mKeysOwner = this;
    if(rev > 1) bs >> mFogColorKeys;
    if(rev > 2) bs >> mFogRangeKeys;
}

BEGIN_COPYS(RndEnvAnim)
    const RndEnvAnim* l = dynamic_cast<const RndEnvAnim*>(o);
    MILO_ASSERT(l, 0x6B);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    mEnviron = l->mEnviron;
    if(ty == kCopyShallow){
        mKeysOwner = l->mKeysOwner;
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

BEGIN_HANDLERS(RndEnvAnim)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xD5)
END_HANDLERS

BEGIN_PROPSYNCS(RndEnvAnim)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
