#include "rndobj/TexBlendController.h"
#include "rndobj/Mesh.h"
#include "rndobj/Tex.h"
#include "rndobj/Trans.h"
#include "math/MathFuncs.h"
#include "obj/PropSync_p.h"
#include "utl/Symbols.h"

unsigned short RndTexBlendController::gRev = 0;

RndTexBlendController::RndTexBlendController() : mMesh(this, 0), mObject1(this, 0), mObject2(this, 0), mReferenceDistance(0.0f), mMinDistance(0.0f), mMaxDistance(0.0f), mTex(this, 0) {
    
}

RndTexBlendController::~RndTexBlendController(){
    
}

// fn_806413C4
bool RndTexBlendController::GetCurrentDistance(float& dist) const {
    if(mObject1 && mObject2){
        dist = Distance(mObject1->WorldXfm().v, mObject2->WorldXfm().v);
        return true;
    }
    else {
        dist = 0;
        return false;
    }
}

void RndTexBlendController::UpdateReferenceDistance(){
    GetCurrentDistance(mReferenceDistance);
    mMinDistance = Minimum(mMinDistance, mReferenceDistance);
    mMaxDistance = Max(mMaxDistance, mReferenceDistance);
}

void RndTexBlendController::UpdateMinDistance(){
    GetCurrentDistance(mMinDistance);
    mMinDistance = Minimum(mMinDistance, mReferenceDistance);
}

void RndTexBlendController::UpdateMaxDistance(){
    GetCurrentDistance(mMaxDistance);
    mMaxDistance = Max(mMaxDistance, mReferenceDistance);
}

void RndTexBlendController::UpdateAllDistances(){
    UpdateReferenceDistance();
    mMinDistance = mReferenceDistance * 0.5f;
    mMaxDistance = mReferenceDistance * 1.5f;
}

BEGIN_COPYS(RndTexBlendController)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(RndTexBlendController)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mMesh)
        COPY_MEMBER(mObject1)
        COPY_MEMBER(mObject2)
        COPY_MEMBER(mReferenceDistance)
        COPY_MEMBER(mMinDistance)
        COPY_MEMBER(mMaxDistance)
        COPY_MEMBER(mTex)
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(RndTexBlendController, 0xF5)

void RndTexBlendController::Load(BinStream& bs){
    int rev;
    bs >> rev;
    if (rev > 2){
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), rev, (unsigned short)2);
    }
    Hmx::Object::Load(bs);
    bs >> mMesh;
    bs >> mObject1;
    bs >> mObject2;
    bs >> mReferenceDistance >> mMinDistance >> mMaxDistance;
    if(gRev > 1) bs >> mTex;
}

BEGIN_HANDLERS(RndTexBlendController)
    HANDLE_ACTION(set_min_distance, UpdateMinDistance())
    HANDLE_ACTION(set_max_distance, UpdateMaxDistance())
    HANDLE_ACTION(set_base_distance, UpdateReferenceDistance())
    HANDLE_ACTION(set_all_distances, UpdateAllDistances())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x129)
END_HANDLERS

BEGIN_PROPSYNCS(RndTexBlendController)
    SYNC_PROP_MODIFY_ALT(reference_object_1, mObject1, UpdateAllDistances())
    SYNC_PROP_MODIFY_ALT(reference_object_2, mObject2, UpdateAllDistances())
    SYNC_PROP(mesh, mMesh)
    SYNC_PROP(base_distance, mReferenceDistance)
    SYNC_PROP(min_distance, mMinDistance)
    SYNC_PROP(max_distance, mMaxDistance)
    SYNC_PROP(override_map, mTex)
END_PROPSYNCS
