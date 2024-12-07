#include "world/Crowd.h"
#include "decomp.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/Timer.h"
#include "rndobj/Cam.h"
#include "rndobj/MultiMesh.h"
#include "rndwii/Rnd.h"
#include "utl/Loader.h"
#include "utl/Symbols.h"

RndCam* gImpostorCamera;
RndMat* gImpostorMat;
int gNumCrowd;
WorldCrowd* gParent;

INIT_REVS(WorldCrowd)

namespace {
    void GetMeshShaderFlags(RndMat* mat, std::list<unsigned int>& flags){
        std::vector<ObjRef*>::reverse_iterator it = mat->mRefs.rbegin();
        std::vector<ObjRef*>::reverse_iterator itEnd = mat->mRefs.rend();
        for(; it != itEnd; ++it){
            RndMesh* mesh = dynamic_cast<RndMesh*>((*it)->RefOwner());
            if(mesh){
                unsigned int flag = 0;
                flag |= mesh->IsSkinned();
                flag |= -(mesh->HasAOCalc()) & 2;
                flags.push_back(flag);
            }
        }
        flags.sort();
        flags.unique();
    }
}

DECOMP_FORCEACTIVE(Crowd, "WorldCrowd[%s] does not have a placement mesh.")

WorldCrowd::WorldCrowd() : mPlacementMesh(this), mCharacters(this), mNum(0), unk44(0), mForce3DCrowd(0), mShow3DOnly(0),
    unk58(1.0f), unk5c(1.0f), mLod(0), mEnviron(this), mEnviron3D(this), mFocus(this), unk88(0) {
    if(gNumCrowd++ == 0){
        GetGfxMode();
        gImpostorMat = Hmx::Object::New<RndMat>();
        gImpostorMat->SetUseEnv(true);
        gImpostorMat->SetPreLit(false);
        gImpostorMat->SetBlend(kBlendSrc);
        gImpostorMat->SetZMode(kZModeNormal);
        gImpostorMat->SetAlphaCut(true);
        gImpostorMat->SetAlphaThreshold(0x80);
        gImpostorMat->SetTexWrap(kTexWrapClamp);
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
            delete it->mMMesh->GetMesh();
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
    return 0;
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
        ObjList<CharData>::iterator it = mCharacters.begin();
        ObjList<CharData>::const_iterator j = c->mCharacters.begin();
        for(; it != mCharacters.end(); ++it, ++j){
            (*it).mDef = (*j).mDef;
            (*it).mBackup = (*j).mBackup;
            (*it).m3DChars = (*j).m3DChars;
            (*it).m3DCharsCreated = (*j).m3DCharsCreated;
        }
        CreateMeshes();
        it = mCharacters.begin();
        j = c->mCharacters.begin();
        for(; it != mCharacters.end(); ++it, ++j){
            if((*it).mMMesh){
                MILO_ASSERT(j->mMMesh, 0x1EB);
                (*it).mMMesh->mInstances = j->mMMesh->mInstances;
            }
        }
    END_COPYING_MEMBERS
END_COPYS

void WorldCrowd::CollideList(const Segment& seg, std::list<Collision>& colls){
    if(LOADMGR_EDITMODE && CollideSphere(seg)){
        for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
            RndMultiMesh* curMM = (*it).mMMesh;
            if(curMM){
                curMM->CollideList(seg, colls);
            }
        }
    }
}

void WorldCrowd::Reset3DCrowd(){
    SetFullness(1.0f, unk58);
    for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
        RndMultiMesh* multiMesh = it->mMMesh;
        if(multiMesh){
            int i6 = 0;
            std::list<RndMultiMesh::Instance>::iterator instIt = multiMesh->mInstances.begin();
            for(int i = 0; i != it->m3DCharsCreated.size(); i++){
                int cap = it->m3DCharsCreated[i].unk30;
                for(; i6 != cap; i6++) ++instIt;
                CharData::Char3D& curChar3D = it->m3DCharsCreated[i];
            }
        }
        it->m3DCharsCreated.clear();
        it->m3DChars.clear();
    }
}

void WorldCrowd::Sort3DCharList(){
    for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
        std::sort(it->m3DChars.begin(), it->m3DChars.end(), Sort3DChars());
        it->m3DCharsCreated = it->m3DChars;
    }
}

void WorldCrowd::Set3DCharAll(){
    START_AUTO_TIMER("crowd_set3d");
    float fvar1 = unk5c;
    Reset3DCrowd();
    for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
        RndMultiMesh* multiMesh = it->mMMesh;
        if(multiMesh){
            std::list<RndMultiMesh::Instance>::iterator instIt = multiMesh->mInstances.begin();
            int idx = 0;
            for(; instIt != multiMesh->mInstances.end(); ++instIt, ++idx){
                CharData::Char3D char3D(instIt->mXfm, idx);
                it->m3DChars.push_back(char3D);
            }
            multiMesh->mInstances.clear();
            multiMesh->InvalidateProxies();
        }
    }
    Sort3DCharList();
    SetFullness(fvar1, unk58);
    AssignRandomColors();
}

void SetMatColorFlags(ObjPtrList<RndMat>& matList, RndMat::ColorModFlags flags, std::vector<Hmx::Color>* modulate){
    for(ObjPtrList<RndMat>::iterator it = matList.begin(); it != matList.end(); ++it){
        (*it)->SetColorModFlags(flags);
        if(modulate){
            MILO_ASSERT(RndMat::kColorModNum == modulate->size(), 0x2CB);
            for(int i = 0; i < modulate->size(); i++){
                (*it)->SetColorMod(modulate->at(i), i);
            }
        }
    }
}

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

void WorldCrowd::Mats(std::list<RndMat*>&, bool){
    std::list<unsigned int> uints;
    GetMeshShaderFlags(0, uints);
}

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
    SYNC_PROP_SET(lod, mLod, SetLod(_val.Int()))
    SYNC_PROP_SET(force_3D_crowd, mForce3DCrowd, Force3DCrowd(_val.Int()))
    SYNC_PROP(focus, mFocus)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
