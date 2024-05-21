#include "Trans.h"
#include "obj/Object.h"
#include "os/System.h"
#include "utl/PoolAlloc.h"
#include "math/Rot.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include <new>

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
    mCache->mFlags = 0;
}

RndTransformable::~RndTransformable() {
    if(mParent){

    }
    delete mCache;
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
