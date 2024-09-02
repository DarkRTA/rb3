#include "world/Crowd.h"
#include "rndobj/Cam.h"
#include "rndwii/Rnd.h"
#include "utl/Symbols.h"

RndCam* gImpostorCamera;
RndMat* gImpostorMat;
int gNumCrowd;
WorldCrowd* gParent;

INIT_REVS(WorldCrowd)

WorldCrowd::WorldCrowd() : mPlacementMesh(this), mCharacters(this), mNum(0), unk44(0), mForce3DCrowd(0), mShow3DOnly(0),
    unk58(1.0f), unk5c(1.0f), mLod(0), mEnviron(this), mEnviron3D(this), mFocus(this), unk88(0) {
    if(gNumCrowd++ == 0){
        GetGfxMode();
        gImpostorMat = Hmx::Object::New<RndMat>();
        gImpostorMat->SetUseEnv(true);
        gImpostorMat->SetPreLit(false);
        gImpostorMat->SetBlend(kSrc);
        gImpostorMat->SetZMode(kNormal);
        gImpostorMat->SetAlphaCut(true);
        gImpostorMat->SetAlphaThreshold(0x80);
        gImpostorMat->SetTexWrap(kClamp);
        gImpostorMat->SetPerPixelLit(false);
        gImpostorMat->SetPointLights(true);
        gImpostorCamera = Hmx::Object::New<RndCam>();
        SetMatAndCameraLod();
    }
}

void WorldCrowd::SetMatAndCameraLod(){
    RndTex* tex = TheWiiRnd.GetSharedTex((WiiRnd::SharedTexType)5, true);
    gImpostorCamera->SetTargetTex(tex);
    gImpostorMat->SetDiffuseTex(tex);
}

WorldCrowd::~WorldCrowd(){
    for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
        if(it->mMMesh){
            delete it->mMMesh->GetMesh();
            RELEASE(it->mMMesh);
        }
    }
    gNumCrowd--;
    if(gNumCrowd == 0){
        RELEASE(gImpostorCamera);
        RELEASE(gImpostorMat);
    }
}

void WorldCrowd::CreateMeshes(){
    unk58 = 1.0f;
    unk5c = 1.0f;
    mLod = 0;
    for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
        if(it->mMMesh){
            delete it->mMMesh->mMesh;
            RELEASE(it->mMMesh);
        }
        it->mBackup.clear();
        if(it->mDef.mChar){
            RndMesh* built = BuildBillboard(it->mDef.mChar, it->mDef.mHeight);
            it->mMMesh = Hmx::Object::New<RndMultiMesh>();
            it->mMMesh->SetMesh(built);
        }
    }
}

DataNode WorldCrowd::OnRebuild(DataArray* da){
    return DataNode(0);
}

BEGIN_COPYS(WorldCrowd)
    COPY_SUPERCLASS(RndDrawable)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(WorldCrowd)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mPlacementMesh)
        COPY_MEMBER(mNum)
        COPY_MEMBER(unk48)
        COPY_MEMBER(unk58)
        COPY_MEMBER(unk5c)
        COPY_MEMBER(mLod)
        COPY_MEMBER(mEnviron)
        COPY_MEMBER(mEnviron3D)
        COPY_MEMBER(mForce3DCrowd)
        COPY_MEMBER(mShow3DOnly)
        COPY_MEMBER(mFocus)
        mCharacters.clear();
        mCharacters.resize(c->mCharacters.size());
    END_COPYING_MEMBERS
END_COPYS

void WorldCrowd::SetLod(int lod){
    mLod = Clamp(0, 2, lod);
}

SAVE_OBJ(WorldCrowd, 0x4BF)

BEGIN_LOADS(WorldCrowd)
    LOAD_REVS(bs)
    ASSERT_REVS(0xE, 0)
    LOAD_SUPERCLASS(RndDrawable)
    bs >> mPlacementMesh;
    if(gRev < 3){
        int i; bs >> i;
    }
    bs >> mNum;
    if(gRev < 8){
        bool b; bs >> b;
    }
    bs >> mCharacters;
    if(gRev > 6) bs >> mEnviron;
    if(gRev > 9) bs >> mEnviron3D;
    else mEnviron3D = mEnviron;
END_LOADS

WorldCrowd::CharData::CharData(Hmx::Object* o) : mDef(o), mMMesh(0) {

}

void WorldCrowd::CharData::Load(BinStream& bs){ mDef.Load(bs); }

WorldCrowd::CharDef::CharDef(Hmx::Object* o) : mChar(o, 0), mHeight(75.0f), mDensity(1.0f), mRadius(10.0f), unk18(0), unk1c(o, kObjListNoNull) {}

void WorldCrowd::CharDef::Load(BinStream& bs){
    bs >> mChar;
    bs >> mHeight;
    bs >> mDensity;
    if(WorldCrowd::gRev > 1) bs >> mRadius;
    if(WorldCrowd::gRev > 8) bs >> unk18;
}

BEGIN_HANDLERS(WorldCrowd)
    HANDLE(rebuild, OnRebuild)
    HANDLE_ACTION(assign_random_colors, AssignRandomColors())
    HANDLE(iterate_frac, OnIterateFrac)
    HANDLE_ACTION(set_fullness, SetFullness(_msg->Float(2), _msg->Float(3)))
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x6FF)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(WorldCrowd::CharData)
    SYNC_PROP(character, o.mDef.mChar)
    SYNC_PROP(height, o.mDef.mHeight)
    SYNC_PROP(density, o.mDef.mDensity)
    SYNC_PROP(radius, o.mDef.mRadius)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(WorldCrowd)
    gParent = this;
    SYNC_PROP(num, mNum)
    SYNC_PROP(placement_mesh, mPlacementMesh)
    SYNC_PROP(characters, mCharacters)
    SYNC_PROP(show_3d_only, mShow3DOnly)
    SYNC_PROP_STATIC(environ, mEnviron)
    SYNC_PROP(environ_3d, mEnviron3D)
    SYNC_PROP_SET(lod, mLod, SetLod(_val.Int(0)))
    SYNC_PROP_SET(force_3D_crowd, mForce3DCrowd, Force3DCrowd(_val.Int(0)))
    SYNC_PROP(focus, mFocus)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS