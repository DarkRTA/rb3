#include "rndobj/TransAnim.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "rndobj/Anim.h"
#include "rndobj/Draw.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

static int TRANSANIM_REV = 7;

RndTransAnim::RndTransAnim() : mTrans(this, 0), mTransSpline(0), mScaleSpline(0), mRotSlerp(0), mRotSpline(0), 
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
        int x;
        bs >> x;
        if (rev != 2 || x != 0) {

        }
    }

    if (rev > 1) {
        bs >> mFollowPath;
    } else {
        mFollowPath = mKeysOwner->mFollowPath;
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
    ts << "   trans: " << mTrans.Ptr() << "\n";
    ts << "   framesOwner: " << mKeysOwner.Ptr() << "\n";
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

void RndTransAnim::MakeTransform(float, Transform&, bool, float) {
    bool prev = 0;
    MILO_ASSERT(prev, 50);
}

void RndTransAnim::SetFrame(float frame, float blend) {
    RndAnimatable::SetFrame(frame, blend);
    if(mTrans){
        Transform tf(mTrans->LocalXfm());
        MakeTransform(frame, tf, false, blend);
        mTrans->SetLocalXfm(tf);
    }
}

void RndTransAnim::SetKey(float frame) {
    if(mTrans){
        TransKeys().Add(mTrans->LocalXfm().v, frame, true);
        Hmx::Matrix3 mtx;
        Normalize(mTrans->LocalXfm().m, mtx);
        Hmx::Quat q(mtx);
        RotKeys().Add(q, frame, true);
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
    return DataNode(0);
}

DataNode RndTransAnim::OnSetScaleSpline(const DataArray* da) {
    SetScaleSpline(da->Int(2));
    return DataNode(0);
}

DataNode RndTransAnim::OnSetRotSlerp(const DataArray* da) {
    SetRotSlerp(da->Int(2));
    return DataNode(0);
}

DataNode RndTransAnim::OnTrans(const DataArray*) {
    return DataNode(mTrans);
}

DataNode RndTransAnim::OnNumTransKeys(const DataArray*) {
    return DataNode(TransKeys().NumKeys());
}

DataNode RndTransAnim::OnNumRotKeys(const DataArray*) {
    return DataNode(RotKeys().NumKeys());
}

DataNode RndTransAnim::OnNumScaleKeys(const DataArray*) {
    return DataNode(ScaleKeys().NumKeys());
}

DataNode RndTransAnim::OnAddTransKey(const DataArray* da) {
    // float frame = da->Float(5);
    // Vector3 vec(da->Float(2), da->Float(3), da->Float(4));
    TransKeys().Add(Vector3(da->Float(2), da->Float(3), da->Float(4)), da->Float(5), false);
    return DataNode(0);
}

DataNode RndTransAnim::OnAddScaleKey(const DataArray* da) {
    // float frame = da->Float(5);
    // Vector3 vec(da->Float(2), da->Float(3), da->Float(4));
    ScaleKeys().Add(Vector3(da->Float(2), da->Float(3), da->Float(4)), da->Float(5), false);
    return DataNode(0);
}

DataNode RndTransAnim::OnAddRotKey(const DataArray* da) {
    Vector3 vec(da->Float(2), da->Float(3), da->Float(4));
    vec *= DEG2RAD;
    float frame = da->Float(5);
    Hmx::Quat q(vec);
    RotKeys().Add(q, frame, false);
    return DataNode(0);
}

DataNode RndTransAnim::OnSplice(const DataArray* da) {
    SpliceKeys(da->Obj<RndTransAnim>(2), this, da->Float(3), da->Float(4));
    return DataNode(0);
}

// fn_80653C5C
DataNode RndTransAnim::OnRemoveRotKeys(const DataArray* da) {
    RotKeys().Remove(da->Float(2), da->Float(3));
    return DataNode(0);
}

DataNode RndTransAnim::OnRemoveTransKeys(const DataArray* da) {
    TransKeys().Remove(da->Float(2), da->Float(3));
    return DataNode(0);
}

DataNode RndTransAnim::OnLinearize(const DataArray* da) {
    float a,b;
    if (da->Size() > 7) { a = da->Float(6); b = da->Float(7); }
    else { a = b = 0; }
    LinearizeKeys(this, da->Float(2), da->Float(3) * DEG2RAD, da->Float(4), a, b);
    return DataNode(0);
}

DataNode RndTransAnim::OnSetTrans(const DataArray* da) {
    SetTrans(da->Obj<RndTransformable>(2));
    return DataNode(0);
}

BEGIN_PROPSYNCS(RndTransAnim)
    SYNC_PROP_SET(keys_owner, mKeysOwner, SetKeysOwner(_val.Obj<RndTransAnim>(NULL)))
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
