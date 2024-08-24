#include "char/CharCollide.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

INIT_REVS(CharCollide)

CharCollide::CharCollide() : mShape(kSphere), mFlags(0), mMesh(this, 0), mMeshYBias(0) {
    for(int i = 0; i < 2; i++){
        mOrigLength[i] = 0;
        mOrigRadius[i] = 0;
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

void CharCollide::Highlight(){
    Hmx::Color black(1.0f, 1.0f, 1.0f);
    Hmx::Color red(1.0f, 0.0f, 0.0f);
    switch(mShape){
        case kPlane:
            Plane p(WorldXfm().v, WorldXfm().m.x);
            UtilDrawPlane(p, WorldXfm().v, red, 1, 12.0f);
            break;
        case kSphere:
        case kInsideSphere:
            UtilDrawSphere(WorldXfm().v, mOrigRadius[0], red);
            UtilDrawSphere(WorldXfm().v, mCurRadius[0], black);
            break;
        case kCigar:
        case kInsideCigar:
            UtilDrawCigar(WorldXfm(), mOrigRadius, mOrigLength, red, 8);
            UtilDrawCigar(WorldXfm(), mCurRadius, mCurLength, black, 8);
            break;
        default: break;
    }
    if(mMesh){
        int numspheres = NumSpheres();
        for(int i = 0; i < numspheres * 2; i++){

        }
    }
    
//   iVar1 = MergedGet0x8(this + 0x98);
//   if (iVar1 != 0) {
//     iVar1 = NumSpheres(this);
//     iVar7 = 0;
//     for (iVar6 = 0; iVar6 < iVar1 << 2; iVar6 = iVar6 + 1) {
//       pCVar4 = (Color *)Hmx::Color::Color(aCStack_68,0.0,0.0,1.0);
//       uVar2 = MergedGet0x8(this + 0x98); mMesh
//       pVVar5 = (Vector3 *)fn_800DEE80(uVar2,*(undefined4 *)(this + iVar7 + 0xb8));
//       UtilDrawSphere(pVVar5,0.1,pCVar4);
//       iVar7 = iVar7 + 0x10;
//     }
//   }
}

SAVE_OBJ(CharCollide, 0x58)

BEGIN_LOADS(CharCollide)
    LOAD_REVS(bs)
    ASSERT_REVS(7, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndTransformable)
    bs >> (int&)mShape;
    bs >> mOrigRadius[0];
    if(gRev > 4) bs >> mOrigLength[0];
    if(gRev > 2) bs >> mOrigLength[1];
    if(gRev > 1) bs >> mFlags;
    else mFlags = 0;
    if(gRev > 3) bs >> mCurRadius[0];
    else mCurRadius[0] = mOrigRadius[0];

    if(gRev > 5){
        bs >> mOrigRadius[1];
        bs >> mCurRadius[1];
        bs >> mCurLength[0];
        bs >> mCurLength[1];
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
        mOrigRadius[1] = mOrigRadius[0];
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
        memcpy(mOrigRadius, c->mOrigRadius, 8);
        memcpy(mOrigLength, c->mOrigLength, 8);
        memcpy(mCurRadius, c->mCurRadius, 8);
        memcpy(mCurLength, c->mCurLength, 8);
        COPY_MEMBER(unk148)
        COPY_MEMBER(mMeshYBias)
        COPY_MEMBER(mMesh)
    END_COPYING_MEMBERS
END_COPYS

void CharCollide::CopyOriginalToCur(){
    memcpy(mCurRadius, mOrigRadius, 8);
    memcpy(mCurLength, mOrigLength, 8);
}

void CharCollide::SyncShape(){
    if(mCurLength[1] < mCurLength[0]){
        mCurLength[0] = mCurLength[1];
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
    SYNC_PROP_MODIFY(radius0, mOrigRadius[0], SyncShape())
    SYNC_PROP_MODIFY(radius1, mOrigRadius[1], SyncShape())
    SYNC_PROP_MODIFY(length0, mOrigLength[0], SyncShape())
    SYNC_PROP_MODIFY(length1, mOrigLength[1], SyncShape())
    SYNC_PROP_MODIFY_ALT(mesh, mMesh, SyncShape())
    SYNC_PROP_MODIFY(mesh_y_bias, mMeshYBias, SyncShape())
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS