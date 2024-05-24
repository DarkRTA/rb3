#include "rndobj/Trans.h"
#include "math/Rot.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

Plane RndTransformable::sShadowPlane;

void RndTransformable::Init() {
    Hmx::Object::RegisterFactory(StaticClassName(), NewObject);
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
        (*it)->mCache->SetDirty();
    }
}

void RndTransformable::SetWorldPos(const Vector3& vec){
    mWorldXfm.v = vec;
    UpdatedWorldXfm();
    for(std::vector<RndTransformable*>::iterator it = mChildren.begin(); it != mChildren.end(); it++){
        (*it)->mCache->SetDirty();
    }
}

void RndTransformable::SetTransConstraint(Constraint cst, RndTransformable* t, bool b){
    MILO_ASSERT(t != this, 0x1C1);
    mConstraint = cst;
    mPreserveScale = b;
    mTarget = t;
    mCache->SetDirty();
}

namespace {
    bool HorizontalCmp(const RndTransformable* t1, const RndTransformable* t2){
        return t1->mLocalXfm.v.x < t2->mLocalXfm.v.x;
    }

    bool VerticalCmp(const RndTransformable* t1, const RndTransformable* t2){
        return t1->mLocalXfm.v.z > t2->mLocalXfm.v.z;
    }
}

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

BEGIN_PROPSYNCS(RndTransformable)
    SYNC_PROP_METHOD(trans_parent, mParent, SetTransParent(_val.Obj<RndTransformable>(0), true))
    SYNC_PROP_METHOD(trans_constraint, mConstraint, SetTransConstraint((Constraint)_val.Int(0), mTarget, mPreserveScale))
    SYNC_PROP_METHOD(trans_target, (Hmx::Object*)mTarget, SetTransConstraint((Constraint)mConstraint, _val.Obj<RndTransformable>(0), mPreserveScale))
    SYNC_PROP_METHOD(preserve_scale, mPreserveScale, SetTransConstraint((Constraint)mConstraint, mTarget, _val.Int(0)))
END_PROPSYNCS
