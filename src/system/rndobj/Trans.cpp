#include "rndobj/Trans.h"
#include "math/Rot.h"
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
    mCache->mFlags = (u32)mCache | (mCache->mFlags & 1);
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

void DirtyCache::SetDirty_Force(){
    SetLastBit(1);
    if(!mChildren.empty()){
        for(std::vector<DirtyCache*>::iterator it = mChildren.begin(); it != mChildren.end(); it++){
            (*it)->SetDirty();
        }
    }
}

void RndTransformable::Print() {
    TheDebug << "   localXfm: " << mLocalXfm << "\n";
    TheDebug << "   worldXfm: " << mWorldXfm << "\n";
}

SAVE_OBJ(RndTransformable, 586)

BEGIN_HANDLERS(RndTransformable)
    HANDLE(copy_local_to, OnCopyLocalTo)
    HANDLE(set_constraint, OnSetTransConstraint)
    HANDLE(set_local_rot, OnSetLocalRot)
    HANDLE(set_local_rot_index, OnSetLocalRotIndex)
    HANDLE(set_local_rot_mat, OnSetLocalRotMat)
    HANDLE(get_local_rot, OnGetLocalRot)
    HANDLE(get_local_rot_index, OnGetLocalRotIndex)
    HANDLE(get_local_pos, OnGetLocalPos)
END_HANDLERS

BEGIN_PROPSYNCS(RndTransformable)
    SYNC_PROP(trans_parent, mLocalXfm)
    SYNC_PROP(trans_constraint, mLocalXfm)
    SYNC_PROP(trans_target, mLocalXfm)
    SYNC_PROP(preserve_scale, mLocalXfm)
END_PROPSYNCS
