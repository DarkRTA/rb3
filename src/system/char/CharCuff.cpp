#include "char/CharCuff.h"
#include "math/Vec.h"
#include "utl/Symbols.h"

INIT_REVS(CharCuff)

CharCuff::CharCuff() : mOpenEnd(0), mIgnore(this, kObjListNoNull), mBone(this, 0), mEccentricity(1.0f), mCategory() {
    mShape[0].offset = -2.9f;
    mShape[0].radius = 1.9f;

    mShape[1].offset = 0.0f;
    mShape[1].radius = 2.6f;

    mShape[2].offset = 2.0f;
    mShape[2].radius = 3.5f;

    mOuterRadius = mShape[1].radius + 0.5f;
}

CharCuff::~CharCuff(){
    
}

float CharCuff::Eccentricity(const Vector2& v) const {
    float f1 = v.y * v.y;
    float f2 = v.x * v.x;
    return std::sqrt((f1 + f2) / (f1 * (1.0f / (mEccentricity * mEccentricity)) + f2));
}

// fn_804C3D90 - highlight
void CharCuff::Highlight(){
    
}

unsigned int BoneMask(std::list<RndTransformable*>& tlist, RndMesh* mesh){
    for(int i = 0; i < mesh->mBones.size(); i++){

    }
}

void AddBoneChildren(std::list<RndTransformable*>& tlist, RndTransformable* trans){
    if(trans){
        if(strncmp(trans->Name(), "bone_", 5) == 0){
            tlist.push_back(trans);
            for(std::vector<RndTransformable*>::iterator it = trans->TransChildren().begin(); it != trans->TransChildren().end(); ++it){
                AddBoneChildren(tlist, *it);
            }
        }
    }
}

void CharCuff::DeformMesh(RndMesh*, int, SyncMeshCB*){
    Vector4_16_01 v;
    v.GetW(); v.GetX(); v.GetY(); v.GetZ();
}

SAVE_OBJ(CharCuff, 0x1A2)

BEGIN_LOADS(CharCuff)
    LOAD_REVS(bs)
    ASSERT_REVS(8, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndTransformable)
    for(int i = 0; i < 3; i++){
        bs >> mShape[i].radius >> mShape[i].offset;
    }
    if(gRev > 1) bs >> mOuterRadius;
    else mOuterRadius = mShape[1].radius + 0.5f;
    if(gRev > 2) bs >> mOpenEnd;
    else mOpenEnd = false;
    if(gRev > 3) bs >> mBone;
    else mBone = TransParent();
    if(gRev > 4) bs >> mEccentricity;
    else mEccentricity = 1.0f;
    if(gRev > 5) bs >> mCategory;
    else mCategory = Symbol("");
    if(gRev > 7) bs >> mIgnore;
    if(gRev < 7) MILO_WARN("%s old CharCuff, must convert, see James", PathName(this));
END_LOADS

BEGIN_COPYS(CharCuff)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    CREATE_COPY(CharCuff)
    BEGIN_COPYING_MEMBERS
        memcpy(mShape, c->mShape, 0x18);
        COPY_MEMBER(mOuterRadius)
        COPY_MEMBER(mOpenEnd)
        COPY_MEMBER(mBone)
        COPY_MEMBER(mEccentricity)
        COPY_MEMBER(mCategory)
        COPY_MEMBER(mIgnore)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharCuff)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x1FE)
END_HANDLERS

BEGIN_PROPSYNCS(CharCuff)
    SYNC_PROP(offset0, mShape[0].offset)
    SYNC_PROP(radius0, mShape[0].radius)
    SYNC_PROP(offset1, mShape[1].offset)
    SYNC_PROP(radius1, mShape[1].radius)
    SYNC_PROP(offset2, mShape[2].offset)
    SYNC_PROP(radius2, mShape[2].radius)
    SYNC_PROP(outer_radius, mOuterRadius)
    SYNC_PROP(open_end, mOpenEnd)
    SYNC_PROP(bone, mBone)
    SYNC_PROP(eccentricity, mEccentricity)
    SYNC_PROP(category, mCategory)
    SYNC_PROP(ignore, mIgnore)
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS