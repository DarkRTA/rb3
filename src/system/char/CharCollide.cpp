#include "char/CharCollide.h"
#include "utl/Symbols.h"

INIT_REVS(CharCollide)

CharCollide::CharCollide() : mShape(kSphere), mFlags(0), mMesh(this, 0), mMeshYBias(0) {
    for(int i = 0; i < 2; i++){
        mLength[i] = 0;
        mRadius[i] = 0;
    }
    CopyOriginalToCur();
    for(int i = 0; i < 8; i++){
        unk_structs[i].unk0 = 0;
        unk_structs[i].vec.Zero();
    }
    unk148.Reset();
}

CharCollide::~CharCollide(){
    
}

SAVE_OBJ(CharCollide, 0x58)

BEGIN_LOADS(CharCollide)
    LOAD_REVS(bs)
    ASSERT_REVS(7, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndTransformable)
    bs >> (int&)mShape;
    bs >> mRadius[0];
    if(gRev > 4) bs >> mLength[0];
    if(gRev > 2) bs >> mLength[1];
    if(gRev > 1) bs >> mFlags;
    else mFlags = 0;
    if(gRev > 3) bs >> unk_arr[0];
    else unk_arr[0] = mRadius[0];

    if(gRev > 5){
        bs >> mRadius[1];
        bs >> unk_arr[1];
        bs >> unk_arr2[0];
        bs >> unk_arr2[1];
        bs >> unk148;
        bs >> mMesh;
        for(int i = 0; i < 8; i++){
            bs >> unk_structs[i].unk0;
            bs >> unk_structs[i].vec;
        }
        bs >> mDigest;
        bs >> mMeshYBias;
        if(gRev < 7) CopyOriginalToCur();
    }
    else {
        mRadius[1] = mRadius[0];
        CopyOriginalToCur();
    }
END_LOADS

BEGIN_COPYS(CharCollide)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    CREATE_COPY(CharCollide)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mShape)
        COPY_MEMBER(mFlags)
        memcpy(mRadius, c->mRadius, 8);
        memcpy(mLength, c->mLength, 8);
        memcpy(unk_arr, c->unk_arr, 8);
        memcpy(unk_arr2, c->unk_arr2, 8);
        COPY_MEMBER(unk148)
        COPY_MEMBER(mMeshYBias)
        COPY_MEMBER(mMesh)
    END_COPYING_MEMBERS
END_COPYS

void CharCollide::CopyOriginalToCur(){
    memcpy(unk_arr, mRadius, 8);
    memcpy(unk_arr2, mLength, 8);
}

void CharCollide::SyncShape(){
    if(unk_arr2[1] < unk_arr2[0]){
        unk_arr2[0] = unk_arr2[1];
    }
    CopyOriginalToCur();
}

BEGIN_HANDLERS(CharCollide)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x221)
END_HANDLERS

BEGIN_PROPSYNCS(CharCollide)
    SYNC_PROP_MODIFY(shape, (int&)mShape, SyncShape())
    SYNC_PROP(flags, mFlags)
    SYNC_PROP_MODIFY(radius0, mRadius[0], SyncShape())
    SYNC_PROP_MODIFY(radius1, mRadius[1], SyncShape())
    SYNC_PROP_MODIFY(length0, mLength[0], SyncShape())
    SYNC_PROP_MODIFY(length1, mLength[1], SyncShape())
    SYNC_PROP_MODIFY_ALT(mesh, mMesh, SyncShape())
    SYNC_PROP_MODIFY(mesh_y_bias, mMeshYBias, SyncShape())
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS