#include "rndobj/Lit.h"
#include "obj/ObjMacros.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"
#include "os/Debug.h"

INIT_REVS(RndLight)

RndLight::RndLight() : mColor(1.0f,1.0f,1.0f), mColorOwner(this, this), mRange(1000.0f), mFalloffStart(0.0f), mType(kPoint), 
    mAnimateColorFromPreset(1), mAnimatePositionFromPreset(1), mAnimateRangeFromPreset(1), mShowing(1), mTexture(this, 0),
    mShadowOverride(0), mShadowObjects(this, kObjListNoNull), mTopRadius(0.0f), mBotRadius(30.0f), mProjectedBlend(0), mOnlyProjection(0) {
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
        Hmx::Color col1, col2;
        bs >> col1 >> col2;
    }
    if (gRev < 3) {
        int i, j;
        bs >> i >> j;
    }
    bs >> mRange;
    if(gRev < 3){
        int i, j, k;
        bs >> i >> j >> k;
    }
    if(gRev != 0){
        int count;
        bs >> count;
        if(gRev < 0xE){
            if(count > 1) count--;
        }
        mType = (Type)count;
    }
    if(gRev > 0xB){
        bs >> mFalloffStart;
    }
    if(gRev > 5){
        bs >> mAnimateColorFromPreset >> mAnimatePositionFromPreset;
    }
    if(gRev > 6){
        bs >> mTopRadius >> mBotRadius;
        if(gRev < 0xE){
            int i, j;
            bs >> i >> j;
        }
    }
    if(gRev > 7){
        bs >> mTexture;
        if(gRev == 9){
            ObjPtrList<RndDrawable, ObjectDir> drawList(this, kObjListNoNull);
            bs >> drawList;
        }
        else if(gRev == 8){
            ObjPtr<RndDrawable, ObjectDir> drawPtr(this, 0);
            bs >> drawPtr;
        }
    }
    if(gRev > 10){
        bs >> mColorOwner;
        if(!mColorOwner) mColorOwner = this;
    }
    if(gRev > 0xC) bs >> mTextureXfm;
    if(gRev > 0xD){
        ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
        bs >> texPtr;
    }
    if(gAltRev != 0){
        bs >> mOnlyProjection;
    }
    if(gRev > 0xE){
        bs >> mShadowObjects;
        bs >> mProjectedBlend;
    }
    if(gRev > 0xF) bs >> mAnimateRangeFromPreset;
    else mAnimateRangeFromPreset = mAnimateColorFromPreset;
END_LOADS

BEGIN_COPYS(RndLight)
    CREATE_COPY_AS(RndLight, l)
    MILO_ASSERT(l, 0xD6);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    COPY_MEMBER_FROM(l, mColor)
    COPY_MEMBER_FROM(l, mType)
    COPY_MEMBER_FROM(l, mAnimateColorFromPreset)
    COPY_MEMBER_FROM(l, mAnimatePositionFromPreset)
    COPY_MEMBER_FROM(l, mAnimateRangeFromPreset)
    if(ty != kCopyFromMax) COPY_MEMBER_FROM(l, mRange)
    COPY_MEMBER_FROM(l, mFalloffStart)
    COPY_MEMBER_FROM(l, mTopRadius)
    COPY_MEMBER_FROM(l, mBotRadius)
    COPY_MEMBER_FROM(l, mTexture)
    COPY_MEMBER_FROM(l, mShadowOverride)
    COPY_MEMBER_FROM(l, mShadowObjects)
    COPY_MEMBER_FROM(l, mProjectedBlend)
    if(ty == kCopyShallow || (ty == kCopyFromMax && l->mColorOwner != l)){
        COPY_MEMBER_FROM(l, mColorOwner)
    }
    else {
        mColorOwner = this;
        COPY_MEMBER_FROM(l, mColor)
    }
END_COPYS

void RndLight::Replace(Hmx::Object* from, Hmx::Object* to){
    RndTransformable::Replace(from, to);
    if(mColorOwner == from){
        RndLight* lit = dynamic_cast<RndLight*>(to);
        if(lit){
            mColorOwner = lit->mColorOwner;
        }
        else mColorOwner = this;
    }
}

void RndLight::SetPackedColor(int packed, float scalar){
    Hmx::Color col;
    col.Unpack(packed);
    Multiply(col, scalar, col);
    SetColor(col);
}

int RndLight::PackedColor() const {
    Hmx::Color col;
    Multiply(GetColor(), 1.0f / Intensity(), col);
    return col.Pack();
}

float RndLight::Intensity() const {
    Hmx::Color col(GetColor());
    return Max(1.0f, Max(col.red, col.green, col.blue));
}

void RndLight::SetTopRadius(float rad){ mTopRadius = rad; }
void RndLight::SetBotRadius(float rad){ mBotRadius = rad; }
void RndLight::SetShadowOverride(ObjPtrList<RndDrawable, ObjectDir>* l){ mShadowOverride = l; }

BEGIN_HANDLERS(RndLight)
    HANDLE_ACTION(set_showing, SetShowing(_msg->Int(2)))
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x186)
END_HANDLERS

BEGIN_PROPSYNCS(RndLight)
    SYNC_PROP(animate_color_from_preset, mAnimateColorFromPreset)
    SYNC_PROP(animate_position_from_preset, mAnimatePositionFromPreset)
    SYNC_PROP(animate_range_from_preset, mAnimateRangeFromPreset)
    SYNC_PROP_SET(type, mType, SetLightType((Type)_val.Int(0)))
    SYNC_PROP_SET(range, mRange, SetRange(_val.Float(0)))
    SYNC_PROP_SET(falloff_start, mFalloffStart, SetFalloffStart(_val.Float(0)))
    SYNC_PROP_SET(color, PackedColor(), SetPackedColor(_val.Int(0), Intensity()))
    SYNC_PROP_SET(intensity, Intensity(), SetPackedColor(PackedColor(), _val.Float(0)))
    SYNC_PROP_SET(topradius, mTopRadius, SetTopRadius(_val.Float(0)))
    SYNC_PROP_SET(botradius, mBotRadius, SetBotRadius(_val.Float(0)))
    SYNC_PROP(color_owner, mColorOwner)
    SYNC_PROP(texture, mTexture)
    SYNC_PROP(texture_xfm, mTextureXfm)
    SYNC_PROP(only_projection, mOnlyProjection)
    SYNC_PROP_SET(projected_blend, mProjectedBlend, SetProjectedBlend(_val.Int(0)))
    SYNC_PROP(shadow_objects, mShadowObjects)
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS

void RndLight::SetLightType(RndLight::Type ty){ mType = ty; }
void RndLight::SetFalloffStart(float fo){ mFalloffStart = fo; }
