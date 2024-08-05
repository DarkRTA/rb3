#include "rndobj/Trans.h"
#include "math/Rot.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "obj/PropSync_p.h"
#include "os/Debug.h"
#include "rndobj/Cam.h"
#include "rndobj/TransAnim.h"
#include "rndobj/Utl.h"
#include "utl/STLHelpers.h"
#include <algorithm>
#include "utl/Symbols.h"

Plane RndTransformable::sShadowPlane;

void RndTransformable::Init() {
    Register();
    DataArray* dingus_da = SystemConfig("rnd");
    dingus_da->FindData("shadow_plane", sShadowPlane, true);
}

RndTransformable::RndTransformable() : mParent(this, NULL),  mTarget(this, NULL), mConstraint(kNone), mPreserveScale(0) {
    mLocalXfm.Reset();
    mWorldXfm.Reset();
    mCache = new DirtyCache();
    mCache->Set((u32)mCache);
}

RndTransformable::~RndTransformable() {
    if(mParent){
        RemoveSwap(mParent->mChildren, this);
        RemoveSwap(mParent->mCache->mChildren, mCache);
    }
    for(std::vector<RndTransformable*>::iterator it = mChildren.begin(); it != mChildren.end(); it++){
        (*it)->mParent = 0;
        (*it)->mCache->Set(0);
        (*it)->mCache->SetDirty();
    }
    delete mCache;
}

void RndTransformable::TransformTransAnims(const Transform& tf){
    std::vector<RndTransformable*>::const_reverse_iterator it = mChildren.rbegin();
    std::vector<RndTransformable*>::const_reverse_iterator itEnd = mChildren.rend();
    for(; it != itEnd; it++){
        RndTransAnim* trans = dynamic_cast<RndTransAnim*>((*it)->RefOwner());
        if(trans && trans->mTrans == this){
            TransformKeys(trans,tf);
        }
    }
}

void RndTransformable::SetTransParent(RndTransformable* newParent, bool b){
    MILO_ASSERT(newParent != this, 0xBB);
    if(mParent == newParent) SetDirty();
    else {
        if(b){
            Transform tf48;
            Transform tf78;
            if(mParent) tf48 = mParent->WorldXfm();
            else tf48.Reset();
            if(newParent) tf78 = newParent->WorldXfm();
            else tf78.Reset();
            Invert(tf78, tf78);
            Multiply(tf48, tf78, tf78);
            Multiply(mLocalXfm, tf78, mLocalXfm);
            TransformTransAnims(tf78);
        }
        if(mParent){
            RemoveSwap(mParent->TransChildren(), this);
            RemoveSwap(mParent->mCache->mChildren, mCache);
        }
        mParent = newParent;
        unsigned int newflags = newParent ? (unsigned int)newParent->mCache : 0;
        mCache->Set(newflags);
        if(b){
            newParent->mChildren.push_back(this);
            newParent->mCache->mChildren.push_back(mCache);
        }
        SetDirty();
    }
}

void RndTransformable::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mParent == from){
        SetTransParent(dynamic_cast<RndTransformable*>(to), false);
    }
}

void DirtyCache::SetDirty_Force(){
    SetLastBit(1);
    if(!mChildren.empty()){
        for(std::vector<DirtyCache*>::iterator it = mChildren.begin(); it != mChildren.end(); it++){
            (*it)->SetDirty();
        }
    }
}

void RndTransformable::SetWorldXfm(const Transform& tf){
    mWorldXfm = tf;
    mCache->SetLastBit(0);
    UpdatedWorldXfm();
    for(std::vector<RndTransformable*>::iterator it = mChildren.begin(); it != mChildren.end(); it++){
        (*it)->SetDirty();
    }
}

void RndTransformable::SetWorldPos(const Vector3& vec){
    mWorldXfm.v = vec;
    UpdatedWorldXfm();
    for(std::vector<RndTransformable*>::iterator it = mChildren.begin(); it != mChildren.end(); it++){
        (*it)->SetDirty();
    }
}

Transform& RndTransformable::WorldXfm_Force(){
    START_AUTO_TIMER("updateworldxfm");
    mCache->SetLastBit(0);
    if(!mParent){
        mWorldXfm = mLocalXfm;
    }
    else if(mConstraint == kParentWorld){
        mWorldXfm = mParent->WorldXfm();
    }
    else if(mConstraint == kLocalRotate){
        Multiply(mLocalXfm.v, mParent->WorldXfm(), mWorldXfm.v);
        mWorldXfm.m = mLocalXfm.m;
    }
    else {
        Multiply(mLocalXfm, mParent->WorldXfm(), mWorldXfm);
    }
    if(HasDynamicConstraint()) ApplyDynamicConstraint();
    else UpdatedWorldXfm();
    return mWorldXfm;
}

void RndTransformable::ApplyDynamicConstraint(){
    if(mConstraint == kTargetWorld){
        mWorldXfm = mTarget->WorldXfm();
    }
    else if(mConstraint == kShadowTarget){
        Transform tf40;
        Transpose(mTarget->WorldXfm(), tf40);
        Multiply(mWorldXfm, tf40, mWorldXfm);
        Plane pl50;
        Multiply(sShadowPlane, tf40, pl50);
        tf40.m.Set(1.0f, 0,0,0,0,0,0,0,0);
        tf40.v.Set(0, -pl50.d / pl50.b, 0);
        Multiply(mWorldXfm, tf40, mWorldXfm);
        Multiply(mWorldXfm, mTarget->WorldXfm(), mWorldXfm);
    }
    else if(RndCam::sCurrent){
        Vector3 v60;
        const Transform& currentWorld = RndCam::sCurrent->WorldXfm();
        if(mPreserveScale){
            MakeScale(mWorldXfm.m, v60);
        }
        switch(mConstraint){
            case kFastBillboardXYZ:
                mWorldXfm.m = currentWorld.m;
                break;
            case kBillboardXYZ:
                Subtract(mWorldXfm.v, currentWorld.v, mWorldXfm.m.y);
                mWorldXfm.m.z = currentWorld.m.z;
                Normalize(mWorldXfm.m, mWorldXfm.m);
                break;
            case kBillboardZ:
                Subtract(mWorldXfm.v, currentWorld.v, mWorldXfm.m.y);
                if(mPreserveScale) Normalize(mWorldXfm.m.z, mWorldXfm.m.z);
                Cross(mWorldXfm.m.y, mWorldXfm.m.z, mWorldXfm.m.x);
                Normalize(mWorldXfm.m.x, mWorldXfm.m.x);
                Cross(mWorldXfm.m.z, mWorldXfm.m.x, mWorldXfm.m.y);
                break;
            case kBillboardXZ:
                Subtract(mWorldXfm.v, currentWorld.v, mWorldXfm.m.y);
                Normalize(mWorldXfm.m.y, mWorldXfm.m.y);
                Cross(mWorldXfm.m.y, mWorldXfm.m.z, mWorldXfm.m.x);
                Normalize(mWorldXfm.m.x, mWorldXfm.m.x);
                Cross(mWorldXfm.m.x, mWorldXfm.m.y, mWorldXfm.m.z);
                break;
            case kLookAtTarget:
                Subtract(mTarget->WorldXfm().v, mWorldXfm.v, mWorldXfm.m.y);
                Normalize(mWorldXfm.m, mWorldXfm.m);
                break;
        }
        if(mPreserveScale) Scale(v60, mWorldXfm.m, mWorldXfm.m);
    }
    mCache->SetLastBit(1);
}

void RndTransformable::SetTransConstraint(Constraint cst, RndTransformable* t, bool b){
    MILO_ASSERT(t != this, 0x1C1);
    mConstraint = cst;
    mPreserveScale = b;
    mTarget = t;
    SetDirty();
}

namespace {
    bool HorizontalCmp(const RndTransformable* t1, const RndTransformable* t2){
        return t1->mLocalXfm.v.x < t2->mLocalXfm.v.x;
    }

    bool VerticalCmp(const RndTransformable* t1, const RndTransformable* t2){
        return t1->mLocalXfm.v.z > t2->mLocalXfm.v.z;
    }
}

void RndTransformable::DistributeChildren(bool b, float f){
    std::vector<RndTransformable*> vec;
    for(std::vector<RndTransformable*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it){
        vec.push_back(*it);
    }
    int count = vec.size();
    if(count < 2) return;
    else {
        if(b) std::sort(vec.begin(), vec.end(), HorizontalCmp);
        else std::sort(vec.begin(), vec.end(), VerticalCmp);
    }
    float at = vec[0]->LocalXfm().v[~-b & 2];
    for(int i = 1; i < count; i++){
        Transform t = vec[i]->LocalXfm();
        t.v[~-b & 2] = f * i + at;
        vec[i]->SetLocalXfm(t);
    }
}

BEGIN_COPYS(RndTransformable)
    if(ClassName() == StaticClassName()) COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(RndTransformable)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mWorldXfm)
        COPY_MEMBER(mLocalXfm)
        if(ty != kCopyFromMax){
            COPY_MEMBER(mPreserveScale)
            COPY_MEMBER(mConstraint)
            COPY_MEMBER(mTarget)
        }
        else if(mConstraint == c->mConstraint){
            COPY_MEMBER(mTarget)
        }
        SetTransParent(c->mParent, false);
    END_COPYING_MEMBERS
END_COPYS

void RndTransformable::Print() {
    TextStream* ts = &TheDebug;
    *ts << "   localXfm: " << mLocalXfm << "\n";
    *ts << "   worldXfm: " << mWorldXfm << "\n";
    *ts << "   constraint: " << mConstraint << "\n";
    *ts << "   preserveScale: " << mPreserveScale << "\n";
    *ts << "   parent: " << mParent << "\n";
}

void RndTransformable::Highlight(){
    Transform& tf = (mCache->mFlags & 1) ? WorldXfm_Force() : mWorldXfm;
    Hmx::Color col;
    UtilDrawAxes(tf, 3.0f, col);
}

SAVE_OBJ(RndTransformable, 586)

BEGIN_LOADS(RndTransformable)
    LOAD_REVS(bs)
    ASSERT_REVS(9, 0)
    if (ClassName() == StaticClassName()) Hmx::Object::Load(bs);
    if (gLoadingProxyFromDisk) {
        Transform t;
        bs >> t >> t;
    } else {
        bs >> mLocalXfm >> mWorldXfm;
    }
    if (gRev < 9) {
        ObjPtrList<RndTransformable, ObjectDir> l(this, kObjListNoNull);
        bs >> l;
        for (ObjPtrList<RndTransformable, ObjectDir>::iterator it = l.begin(); it != l.end(); ++it) {
            (*it)->SetTransParent(this, false);
        }
    }


    if (TransConstraint() == kParentWorld) SetTransParent(mTarget, false);
END_LOADS

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(RndTransformable)
    HANDLE(copy_local_to, OnCopyLocalTo)
    HANDLE(set_constraint, OnSetTransConstraint)
    HANDLE(set_local_rot, OnSetLocalRot)
    HANDLE(set_local_rot_index, OnSetLocalRotIndex)
    HANDLE(set_local_rot_mat, OnSetLocalRotMat)
    HANDLE(set_local_pos, OnSetLocalPos)
    HANDLE(set_local_pos_index, OnSetLocalPosIndex)
    HANDLE(get_local_rot, OnGetLocalRot)
    HANDLE(get_local_rot_index, OnGetLocalRotIndex)
    HANDLE(get_local_pos, OnGetLocalPos)
    HANDLE(get_local_pos_index, OnGetLocalPosIndex)
    HANDLE(set_local_scale, OnSetLocalScale)
    HANDLE(set_local_scale_index, OnSetLocalScaleIndex)
    HANDLE(get_local_scale, OnGetLocalScale)
    HANDLE(get_local_scale_index, OnGetLocalScaleIndex)
    HANDLE_ACTION(normalize_local, Normalize(mLocalXfm.m, mLocalXfm.m))
    HANDLE(get_world_forward, OnGetWorldForward)
    HANDLE(get_world_pos, OnGetWorldPos)
    HANDLE(get_world_rot, OnGetWorldRot)
    HANDLE_ACTION(set_trans_parent, SetTransParent(_msg->Obj<RndTransformable>(2), _msg->Size() > 3 ? _msg->Int(3) != 0 : false))
    HANDLE_EXPR(trans_parent, mParent)
    HANDLE_ACTION(reset_xfm, DirtyLocalXfm().Reset())
    HANDLE_ACTION(distribute_children, DistributeChildren(_msg->Int(2) != 0, _msg->Float(3)))
    HANDLE(get_children, OnGetChildren)
    if(ClassName() == StaticClassName()){
        HANDLE_SUPERCLASS(Hmx::Object)
    }
    HANDLE_CHECK(0x357)
END_HANDLERS
#pragma pop

DataNode RndTransformable::OnCopyLocalTo(const DataArray* da){
    DataArray* arr = da->Array(2);
    for(int i = arr->Size() - 1; i >= 0; i--){
        RndTransformable* t = arr->Obj<RndTransformable>(i);
        t->SetLocalXfm(LocalXfm());
    }
    return DataNode(0);
}

DataNode RndTransformable::OnGetWorldForward(const DataArray* da){
    *da->Var(2) = DataNode(WorldXfm().m.y.X());
    *da->Var(3) = DataNode(WorldXfm().m.y.Y());
    *da->Var(4) = DataNode(WorldXfm().m.y.Z());
    return DataNode(0);
}

DataNode RndTransformable::OnGetWorldPos(const DataArray* da) {
    *da->Var(2) = DataNode(WorldXfm().v.X());
    *da->Var(3) = DataNode(WorldXfm().v.Y());
    *da->Var(4) = DataNode(WorldXfm().v.Z());
    return DataNode(0);
}

DataNode RndTransformable::OnGetLocalPos(const DataArray* da) {
    *da->Var(2) = LocalXfm().v.X();
    *da->Var(3) = LocalXfm().v.Y();
    *da->Var(4) = LocalXfm().v.Z();
    return DataNode();
}

DataNode RndTransformable::OnGetLocalPosIndex(const DataArray* a) {
    MILO_ASSERT(a->Int(2) < 3, 896);
    return DataNode(LocalXfm().v[a->Int(2)]);
}

DataNode RndTransformable::OnGetLocalRot(const DataArray* da){
    Vector3 v40;
    Hmx::Matrix3 m34(LocalXfm().m);
    Normalize(m34, m34);
    MakeEuler(m34, v40);
    v40 *= RAD2DEG;
    *da->Var(2) = DataNode(v40.x);
    *da->Var(3) = DataNode(v40.y);
    *da->Var(4) = DataNode(v40.z);
    return DataNode(0);
}

DataNode RndTransformable::OnSetLocalPos(const DataArray* da) {
    mLocalXfm.v.Set(da->Float(2), da->Float(3), da->Float(4));
    mCache->SetDirty();
    return DataNode();
}

DataNode RndTransformable::OnSetLocalPosIndex(const DataArray* a) {
    MILO_ASSERT(a->Int(2) < 3, 943);
    mLocalXfm.v[a->Int(2)] = a->Float(3);
    mCache->SetDirty();
}

void RndTransformable::SetLocalRot(Vector3) {

}

DataNode RndTransformable::OnSetLocalRot(const DataArray* da) {
    Vector3 v(da->Float(2), da->Float(3), da->Float(4));
    SetLocalRot(v);
    return DataNode();
}

BEGIN_PROPSYNCS(RndTransformable)
    SYNC_PROP_SET(trans_parent, mParent, SetTransParent(_val.Obj<RndTransformable>(0), true))
    SYNC_PROP_SET(trans_constraint, mConstraint, SetTransConstraint((Constraint)_val.Int(0), mTarget, mPreserveScale))
    SYNC_PROP_SET(trans_target, (Hmx::Object*)mTarget, SetTransConstraint((Constraint)mConstraint, _val.Obj<RndTransformable>(0), mPreserveScale))
    SYNC_PROP_SET(preserve_scale, mPreserveScale, SetTransConstraint((Constraint)mConstraint, mTarget, _val.Int(0)))
END_PROPSYNCS
