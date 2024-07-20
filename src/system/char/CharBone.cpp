#include "char/CharBone.h"
#include "char/CharBoneDir.h"
#include "rndobj/TransRemover.h"
#include "utl/Symbols.h"

INIT_REVS(CharBone);

CharBone::CharBone() : mPositionContext(0), mScaleContext(0), mRotation(CharBones::TYPE_END), mRotationContext(0), mTarget(this, 0), mWeights(), mTrans(this, 0), mBakeOutAsTopLevel(0) {

}

void CharBone::StuffBones(std::list<CharBones::Bone>& bonelist, int i) const {
    if(mPositionContext & i){
        bonelist.push_back(CharBones::Bone(ChannelName(Name(), CharBones::TYPE_POS), GetWeight(i)));
    }
    if(mScaleContext & i){
        bonelist.push_back(CharBones::Bone(ChannelName(Name(), CharBones::TYPE_SCALE), GetWeight(i)));
    }
    if(mRotation != CharBones::TYPE_END && mRotationContext & i){
        bonelist.push_back(CharBones::Bone(ChannelName(Name(), mRotation), GetWeight(i)));
    }
}

void CharBone::ClearContext(int i){
    int mask = ~i;
    mPositionContext &= mask;
    mScaleContext &= mask;
    mRotationContext &= mask;
}

float CharBone::GetWeight(int i) const {
    const WeightContext* ctx = FindWeight(i);
    if(ctx) return ctx->mWeight;
    else return 1.0f;
}

const CharBone::WeightContext* CharBone::FindWeight(int i) const {
    for(std::vector<WeightContext>::const_iterator it = mWeights.begin(); it != mWeights.end(); ++it){
        if((*it).mContext & i) return it;
    }
    return 0;
}

BinStream& operator>>(BinStream& bs, CharBone::WeightContext& ctx){
    bs >> ctx.mContext >> ctx.mWeight;
    return bs;
}

SAVE_OBJ(CharBone, 0xBF)

BEGIN_LOADS(CharBone)
    LOAD_REVS(bs);
    ASSERT_REVS(10, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    if(gRev < 9){
        RndTransformableRemover remover;
        remover.Load(bs);
    }
    if(gRev > 6) bs >> mPositionContext;
    else {
        bool b;
        bs >> b;
        mPositionContext = b;
    }
    if(gRev > 6) bs >> mScaleContext;
    else if(gRev > 1){
        bool b;
        bs >> b;
        mScaleContext = b;
    }
    bs >> (int&)mRotation;
    if(gRev < 5){
        int i; bs >> i;
    }
    if(gRev < 2){
        mScaleContext = 0;
        mRotation = (CharBones::Type)(mRotation + 1);
    }
    if(gRev < 5 && mRotation > CharBones::TYPE_END){
        mRotation = CharBones::TYPE_END;
    }
    if(gRev > 6) bs >> mRotationContext;
    else mRotationContext = mRotation != CharBones::TYPE_END;
    if(gRev == 3 || gRev == 4 || gRev == 5 || gRev == 6 || gRev == 7){
        int i; bs >> i;
    }
    if(gRev > 3) bs >> mTarget;
    if(gRev == 6){
        int ctx; bs >> ctx;
        if(mPositionContext != 0) mPositionContext = ctx;
        if(mScaleContext != 0) mScaleContext = ctx;
        if(mRotationContext != 0) mRotationContext = ctx;
    }
    if(gRev > 7) bs >> mWeights;
    if(gRev > 8) bs >> mTrans;
    if(gRev > 9) bs >> mBakeOutAsTopLevel;
END_LOADS

BEGIN_COPYS(CharBone)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharBone)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mRotationContext)
        COPY_MEMBER(mScaleContext)
        COPY_MEMBER(mPositionContext)
        COPY_MEMBER(mRotation)
        COPY_MEMBER(mTarget)
        COPY_MEMBER(mWeights)
        COPY_MEMBER(mTrans)
        COPY_MEMBER(mBakeOutAsTopLevel)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharBone)
    HANDLE_ACTION(clear_context, ClearContext(_msg->Int(2)))
    HANDLE(get_context_flags, OnGetContextFlags)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x152)
END_HANDLERS

DataNode CharBone::OnGetContextFlags(DataArray* da){
    CharBoneDir* dir = dynamic_cast<CharBoneDir*>(Dir());
    if(dir) return dir->GetContextFlags();
    else {
        MILO_WARN("CharBone: No CharBoneDir for context flags.");
        DataArrayPtr ptr;
        return DataNode(ptr);
    }
}

BEGIN_CUSTOM_PROPSYNC(CharBone::WeightContext)
    SYNC_PROP(context, o.mContext)
    SYNC_PROP(weight, o.mWeight)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(CharBone)
    SYNC_PROP(position_context, mPositionContext)
    SYNC_PROP(scale_context, mScaleContext)
    SYNC_PROP(rotation, (int&)mRotation)
    SYNC_PROP(rotation_context, mRotationContext)
    SYNC_PROP(target, mTarget)
    SYNC_PROP(weights, mWeights)
    SYNC_PROP(trans, mTrans)
    SYNC_PROP(bake_out_as_top_level, mBakeOutAsTopLevel)
    SYNC_SUPERCLASS(Hmx::Object)
END_PROPSYNCS