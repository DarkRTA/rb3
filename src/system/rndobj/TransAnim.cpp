#include "rndobj/TransAnim.h"
#include "math/Key.h"
#include "math/Mtx.h"
#include "math/Rot.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "rndobj/Anim.h"
#include "rndobj/Draw.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

static int TRANSANIM_REV = 7;

RndTransAnim::RndTransAnim() : mTrans(this), mTransSpline(0), mScaleSpline(0), mRotSlerp(0), mRotSpline(0),
    mRotKeys(), mTransKeys(), mScaleKeys(), mKeysOwner(this, this), mRepeatTrans(0), mFollowPath(0) {

}

void RndTransAnim::SetTrans(RndTransformable* trans){
    mTrans = trans;
}

void RndTransAnim::SetKeysOwner(RndTransAnim* o){
    MILO_ASSERT(o, 0x2C);
    mKeysOwner = o;
}

void RndTransAnim::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mKeysOwner == from){
        if(!to) mKeysOwner = this;
        else mKeysOwner = dynamic_cast<RndTransAnim*>(to)->mKeysOwner;
    }
}

SAVE_OBJ(RndTransAnim, 0x4B)

// matches on retail with the right inline settings: https://decomp.me/scratch/PZBku
void RndTransAnim::Load(BinStream& bs){
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, TRANSANIM_REV);
    if(rev > 4) LOAD_SUPERCLASS(Hmx::Object);
    LOAD_SUPERCLASS(RndAnimatable);
    if(rev < 6) RndDrawable::DumpLoad(bs);
    bs >> mTrans;
    if(rev != 2){
        bs >> mRotKeys >> mTransKeys;
    }
    bs >> mKeysOwner;
    if(!mKeysOwner) mKeysOwner = this;
    if (rev < 3) {
        int numKeys;
        bs >> numKeys;
        if(rev == 2 || numKeys != 0){
            mTransKeys.resize(numKeys);
            for(Keys<Vector3, Vector3>::iterator it = mTransKeys.begin(); it != mTransKeys.end(); ++it){
                int i1, i2, i3;
                Vector3 v1, v2;
                bs >> it->value >> i1 >> i2 >> i3 >> v1 >> v2 >> it->frame;
            }
        }
        bs >> numKeys;
        if(rev == 2 || numKeys != 0){
            mRotKeys.resize(numKeys);
            for(Keys<Hmx::Quat, Hmx::Quat>::iterator it = mRotKeys.begin(); it != mRotKeys.end(); ++it){
                int i1, i2, i3;
                Hmx::Quat v1, v2;
                bs >> it->value >> i1 >> i2 >> i3 >> v1 >> v2 >> it->frame;
            }
        }
        int c0; bs >> c0;
    }
    if(rev > 3) bs >> mTransSpline;
    else {
        int c4; bs >> c4;
        mTransSpline = c4;
    }
    bs >> mRepeatTrans;
    if(rev > 3){
        bs >> mScaleKeys >> mScaleSpline;
    }
    else if(rev > 0){
        if(rev != 2){
            bs >> mScaleKeys;
        }
        if(rev < 3){
            int numKeys;
            bs >> numKeys;
            if(rev == 2 || numKeys != 0){
                mScaleKeys.resize(numKeys);
                for(Keys<Vector3, Vector3>::iterator it = mScaleKeys.begin(); it != mScaleKeys.end(); ++it){
                    int i1, i2, i3;
                    Vector3 v1, v2;
                    bs >> it->value >> i1 >> i2 >> i3 >> v1 >> v2 >> it->frame;
                }
            }
        }
        int splinebool;
        bs >> splinebool;
        mScaleSpline = splinebool;
    }
    if(rev > 1){
        bs >> mFollowPath;
    }
    else {
        bool follow = false;
        if(RotKeys().empty() && TransKeys().size() > 1) follow = true;
        mFollowPath = follow;
    }
    if (rev > 3) bs >> mRotSlerp;
    if (rev > 6) bs >> mRotSpline;
}

BEGIN_COPYS(RndTransAnim)
    CREATE_COPY_AS(RndTransAnim, t)
    MILO_ASSERT(t, 0xE8);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    mTrans = t->mTrans;
    if(ty == kCopyShallow || ty == kCopyFromMax && t->mKeysOwner != t){
        mKeysOwner = t->mKeysOwner;
    }
    else {
        mKeysOwner = this;
        mTransKeys = t->mKeysOwner->mTransKeys;
        mRotKeys = t->mKeysOwner->mRotKeys;
        mScaleKeys = t->mKeysOwner->mScaleKeys;
        mTransSpline = t->mKeysOwner->mTransSpline;
        mRepeatTrans = t->mKeysOwner->mRepeatTrans;
        mScaleSpline = t->mKeysOwner->mScaleSpline;
        mFollowPath = t->mKeysOwner->mFollowPath;
        mRotSlerp = t->mKeysOwner->mRotSlerp;
        mRotSpline = t->mKeysOwner->mRotSpline;
    }
END_COPYS

void RndTransAnim::Print(){
    TextStream& ts = TheDebug;
    ts << "   trans: " << mTrans << "\n";
    ts << "   framesOwner: " << mKeysOwner << "\n";
    ts << "   rotKeys: " << mRotKeys << "\n";
    ts << "   transKeys: " << mTransKeys << "\n";
    ts << "   scaleKeys: " << mScaleKeys << "\n";
    ts << "   transSpline: " << mTransSpline << "\n";
    ts << "   scaleSpline: " << mScaleSpline << "\n";
    ts << "   rotSlerp: " << mRotSlerp << "\n";
    ts << "   rotSpline: " << mRotSpline << "\n";
    ts << "   repeatTrans: " << mRepeatTrans << "\n";
    ts << "   followPath: " << mFollowPath << "\n";
}

float RndTransAnim::EndFrame() {
    return Max(TransKeys().LastFrame(), RotKeys().LastFrame(), ScaleKeys().LastFrame());
}

float RndTransAnim::StartFrame() {
    return Min(TransKeys().FirstFrame(), RotKeys().FirstFrame(), ScaleKeys().FirstFrame());
}

// matches in retail with the right inline settings: https://decomp.me/scratch/vtXKh
void RndTransAnim::MakeTransform(float frame, Transform& tf, bool whole, float blend) {
    float f5 = frame;
    if(mKeysOwner != this){
        mKeysOwner->MakeTransform(frame, tf, whole, blend);
    }
    else {
        Vector3 v4c;
        if(!mTransKeys.empty()){
            Vector3 v58(0,0,0);
            if(mRepeatTrans){
                int iac;
                float& backFrame = mTransKeys.back().frame;
                float& frontFrame = mTransKeys.front().frame;
                f5 = Limit(frontFrame, backFrame, frame, iac);
                Vector3& frontVec = mTransKeys.front().value;
                Vector3& backVec = mTransKeys.back().value;
                Subtract(backVec, frontVec, v58);
                v58 *= iac;
            }
            if(blend != 1.0f){
                Vector3 v64;
                InterpVector(mTransKeys, mTransSpline, f5, v64, mFollowPath ? &v4c : nullptr);
                if(mRepeatTrans){
                    ::Add(v64, v58, v64);
                }
                Interp(tf.v, v64, blend, tf.v);
            }
            else {
                InterpVector(mTransKeys, mTransSpline, f5, tf.v, mFollowPath ? &v4c : nullptr);
                if(mRepeatTrans){
                    ::Add(tf.v, v58, tf.v);
                }
            }
        }
        else if(whole){
            tf.v.Zero();
        }
        Vector3 v70;
        if(!mRotKeys.empty()){
            Hmx::Quat q80;
            const Key<Hmx::Quat>* prev;
            const Key<Hmx::Quat>* next;
            float ref = 0;
            mRotKeys.AtFrame(f5, prev, next, ref);
            if(mRotSpline) QuatSpline(mRotKeys, prev, next, ref, q80);
            else {
                MILO_ASSERT(prev, 0x16F);
                if(mRotSlerp) Interp(prev->value, next->value, ref, q80);
                else FastInterp(prev->value, next->value, ref, q80);
            }
            if(blend != 1.0f){
                if(!mScaleKeys.empty()){
                    MakeScale(tf.m, v70);
                    tf.m.x *= 1.0f / v70.x;
                    tf.m.y *= 1.0f / v70.y;
                    tf.m.z *= 1.0f / v70.z;
                }
                Hmx::Quat q90(tf.m);
                if(mRotSlerp || mRotSpline){
                    Interp(q90, q80, blend, q80);
                }
                else {
                    FastInterp(q90, q80, blend, q80);
                }
            }
            MakeRotMatrix(q80, tf.m);
        }
        else if(whole) tf.m.Identity();
        if(mFollowPath && !mTransKeys.empty()){
            if(!mRotKeys.empty()){
                MakeRotMatrix(v4c, tf.m.z, tf.m);
            }
            else {
                MakeRotMatrix(v4c, Vector3(0,0,1), tf.m);
            }
        }
        if(!mScaleKeys.empty()){
            Vector3 v9c;
            InterpVector(mScaleKeys, mScaleSpline, f5, v9c, 0);
            if(blend != 1.0f){
                Interp(v70, v9c, blend, v9c);
            }
            Scale(v9c, tf.m, tf.m);
        }
    }
}

void RndTransAnim::SetFrame(float frame, float blend) {
    RndAnimatable::SetFrame(frame, blend);
    if(mTrans){
        Transform tf(mTrans->LocalXfm());
        MakeTransform(frame, tf, false, blend);
        mTrans->SetLocalXfm(tf);
    }
}

// matches in retail with the right inline settings: https://decomp.me/scratch/05Ytm
void RndTransAnim::SetKey(float frame) {
    if(mTrans){
        TransKeys().Add(mTrans->LocalXfm().v, frame, true);
        Hmx::Matrix3 mtx;
        Normalize(mTrans->LocalXfm().m, mtx);
        RotKeys().Add(Hmx::Quat(mtx), frame, true);
        Vector3 vec;
        MakeScale(mTrans->LocalXfm().m, vec);
        ScaleKeys().Add(vec, frame, true);
    }
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(RndTransAnim)
    HANDLE(trans, OnTrans)
    HANDLE(splice, OnSplice)
    HANDLE(linearize, OnLinearize)
    HANDLE(set_trans, OnSetTrans)
    HANDLE(remove_rot_keys, OnRemoveRotKeys)
    HANDLE(remove_trans_keys, OnRemoveTransKeys)
    HANDLE(num_trans_keys, OnNumTransKeys)
    HANDLE(num_rot_keys, OnNumRotKeys)
    HANDLE(num_scale_keys, OnNumScaleKeys)
    HANDLE(add_trans_key, OnAddTransKey)
    HANDLE(add_rot_key, OnAddRotKey)
    HANDLE(add_scale_key, OnAddScaleKey)
    HANDLE(set_trans_spline, OnSetTransSpline)
    HANDLE(set_scale_spline, OnSetScaleSpline)
    HANDLE(set_rot_slerp, OnSetRotSlerp)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(489)
END_HANDLERS
#pragma pop

DataNode RndTransAnim::OnSetTransSpline(const DataArray* da) {
    SetTransSpline(da->Int(2));
    return 0;
}

DataNode RndTransAnim::OnSetScaleSpline(const DataArray* da) {
    SetScaleSpline(da->Int(2));
    return 0;
}

DataNode RndTransAnim::OnSetRotSlerp(const DataArray* da) {
    SetRotSlerp(da->Int(2));
    return 0;
}

DataNode RndTransAnim::OnTrans(const DataArray*) {
    return mTrans.Ptr();
}

DataNode RndTransAnim::OnNumTransKeys(const DataArray*) {
    return TransKeys().NumKeys();
}

DataNode RndTransAnim::OnNumRotKeys(const DataArray*) {
    return RotKeys().NumKeys();
}

DataNode RndTransAnim::OnNumScaleKeys(const DataArray*) {
    return ScaleKeys().NumKeys();
}

DataNode RndTransAnim::OnAddTransKey(const DataArray* da) {
    TransKeys().Add(Vector3(da->Float(2), da->Float(3), da->Float(4)), da->Float(5), false);
    return 0;
}

DataNode RndTransAnim::OnAddScaleKey(const DataArray* da) {
    ScaleKeys().Add(Vector3(da->Float(2), da->Float(3), da->Float(4)), da->Float(5), false);
    return 0;
}

DataNode RndTransAnim::OnAddRotKey(const DataArray* da) {
    Vector3 vec(da->Float(2), da->Float(3), da->Float(4));
    vec *= DEG2RAD;
    RotKeys().Add(Hmx::Quat(vec), da->Float(5), false);
    return 0;
}

DataNode RndTransAnim::OnSplice(const DataArray* da) {
    SpliceKeys(da->Obj<RndTransAnim>(2), this, da->Float(3), da->Float(4));
    return 0;
}

// fn_80653C5C
DataNode RndTransAnim::OnRemoveRotKeys(const DataArray* da) {
    RotKeys().Remove(da->Float(2), da->Float(3));
    return 0;
}

DataNode RndTransAnim::OnRemoveTransKeys(const DataArray* da) {
    TransKeys().Remove(da->Float(2), da->Float(3));
    return 0;
}

DataNode RndTransAnim::OnLinearize(const DataArray* da) {
    float a,b;
    if (da->Size() > 7) { a = da->Float(6); b = da->Float(7); }
    else { a = b = 0; }
    LinearizeKeys(this, da->Float(2), da->Float(3) * DEG2RAD, da->Float(4), a, b);
    return 0;
}

DataNode RndTransAnim::OnSetTrans(const DataArray* da) {
    SetTrans(da->Obj<RndTransformable>(2));
    return 0;
}

BEGIN_PROPSYNCS(RndTransAnim)
    SYNC_PROP_SET(keys_owner, mKeysOwner, SetKeysOwner(_val.Obj<RndTransAnim>()))
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
