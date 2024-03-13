#include "rndobj/TexBlendController.h"
#include "rndobj/Mesh.h"
#include "rndobj/Tex.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"

RndTexBlendController::RndTexBlendController() : mMesh(this, 0), mObject1(this, 0), mObject2(this, 0), mReferenceDistance(0.0f), mMinDistance(0.0f), mMaxDistance(0.0f), mTex(this, 0) {
    
}

RndTexBlendController::~RndTexBlendController(){
    
}

BEGIN_COPYS(RndTexBlendController)
    COPY_SUPERCLASS(Hmx::Object)
    GET_COPY(RndTexBlendController)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mMesh)
        COPY_MEMBER(mObject1)
        COPY_MEMBER(mObject2)
        COPY_MEMBER(mReferenceDistance)
        COPY_MEMBER(mMinDistance)
        COPY_MEMBER(mMaxDistance)
        COPY_MEMBER(mTex)
    END_COPY_CHECKED
END_COPYS

SAVE_OBJ(RndTexBlendController, 0xF5)

BEGIN_HANDLERS(RndTexBlendController)
    HANDLE_ACTION(set_min_distance, UpdateMinDistance())
    HANDLE_ACTION(set_max_distance, UpdateMaxDistance())
    HANDLE_ACTION(set_base_distance, UpdateReferenceDistance())
    HANDLE_ACTION(set_all_distances, UpdateAllDistances())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x129)
END_HANDLERS
