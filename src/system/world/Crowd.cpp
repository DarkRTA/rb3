#include "world/Crowd.h"
#include "char/Character.h"
#include "decomp.h"
#include "math/Color.h"
#include "math/Mtx.h"
#include "math/Rand.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/Timer.h"
#include "rndobj/Cam.h"
#include "rndobj/Draw.h"
#include "rndobj/Mesh.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Poll.h"
#include "rndobj/Trans.h"
#include "rndwii/Mesh.h"
#include "rndwii/Rnd.h"
#include "utl/Loader.h"
#include "utl/Symbols.h"
#include "world/ColorPalette.h"

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

void WorldCrowd::Set3DCharList(const std::vector<std::pair<int, int> >& pairVec, Hmx::Object* obj){
    START_AUTO_TIMER("crowd_set3d");
    if(!IsForced3DCrowd()){
        Reset3DCrowd();
        std::vector<std::pair<RndMultiMesh*, std::list<RndMultiMesh::Instance>::iterator> > grosserPairs;
        grosserPairs.reserve(pairVec.size());
        for(int i = 0; i != pairVec.size(); i++){

        }
    }
}

DECOMP_FORCEACTIVE(Crowd, "%s setting bad mesh %d, only has %d", "%s setting bad 3d char %d on mmesh %s, only has %d chars")

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

bool WorldCrowd::Crowd3DExists(){
    for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
        if((*it).mDef.mChar && (*it).mMMesh && !(*it).m3DChars.empty()){
            return true;
        }
    }
    return false;
}

void WorldCrowd::Draw3DChars(){
    
}

void WorldCrowd::DrawShowing(){
    START_AUTO_TIMER("crowd_draw");
    MILO_ASSERT(!gImpostorMat->NextPass(), 0x34A);
    MILO_NOTIFY_ONCE("%s: Rendering 2D crowd character texture without an environment, set the environ property on the WorldCrowd object.");
}

RndMesh* WorldCrowd::BuildBillboard(Character* c, float f){
    c->mSphere.GetRadius();
    RndMesh* mesh = Hmx::Object::New<RndMesh>();
    RndMesh::VertVector& verts = mesh->Verts();
    std::vector<RndMesh::Face>& faces = mesh->Faces();
    float f1 = f * 0.5f;
    float f2 = f1 * 0.5f;
    verts.resize(4, true);
    float f2neg = -f2;
    verts[0].pos.Set(f2neg, 0, f1);
    float f1neg = -f1;
    verts[1].pos.Set(f2neg, 0, f1neg);
    verts[2].pos.Set(f2, 0, f1);
    verts[3].pos.Set(f2, 0, f1neg);

    verts[0].uv.Set(0, 0);
    verts[1].uv.Set(0, 1);
    verts[2].uv.Set(1, 0);
    verts[3].uv.Set(1, 1);

    faces.resize(2);
    faces[0].Set(0, 1, 2);
    faces[1].Set(1, 3, 2);
    mesh->Sync(0x3F);
    mesh->SetMat(gImpostorMat);
    mesh->SetTransConstraint(RndTransformable::kFastBillboardXYZ, gImpostorCamera, false);
    return mesh;
}

void WorldCrowd::SetLod(int lod){
    mLod = Clamp(0, 2, lod);
}

void WorldCrowd::SetFullness(float, float){
    START_AUTO_TIMER("crowd_set");
}

SAVE_OBJ(WorldCrowd, 0x4BF)

DECOMP_FORCEACTIVE(WorldCrowd, "ObjPtr_p.h", "f.Owner()", "")

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
    if(gRev > 1){
        CreateMeshes();
        for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
            if(gRev < 0xE){
                std::list<Transform> xfmList;
                std::list<RndMultiMesh::Instance> instancesList;
                std::list<OldMMInst> oldmmiList;
                if(it->mMMesh){
                    if(gRev < 9){
                        bs >> xfmList;
                        it->mMMesh->mInstances.clear();
                        for(std::list<Transform>::iterator transIt = xfmList.begin(); transIt != xfmList.end(); ++transIt){
                            it->mMMesh->mInstances.push_back(RndMultiMesh::Instance(*transIt));
                        }
                    }
                    else if(gRev < 0xB){
                        bs >> oldmmiList;
                        for(std::list<OldMMInst>::iterator mmiIt = oldmmiList.begin(); mmiIt != oldmmiList.end(); ++mmiIt){
                            it->mMMesh->mInstances.push_back(RndMultiMesh::Instance(mmiIt->mOldXfm));
                        }
                    }
                    else {
                        std::list<RndMultiMesh::Instance>& instances = it->mMMesh->mInstances;
                        unsigned int count;
                        bs >> count;
                        if(count > 10000000){
                            MILO_FAIL("Crowd tried to allocate %d mesh instances.  That's a little excessive, no?", count);
                        }
                        instances.resize(count);
                        for(std::list<RndMultiMesh::Instance>::iterator instIt = instances.begin(); instIt != instances.end(); ++instIt){
                            instIt->LoadRev(bs, 3);
                        }
                    }
                }
                else if(gRev > 3){
                    if(gRev < 9) bs >> xfmList;
                    else if(gRev < 0xB) bs >> oldmmiList;
                    else bs >> instancesList;
                }
            }
            else {
                std::list<Transform> xfms;
                bs >> xfms;
                it->mMMesh->mInstances.clear();
                for(std::list<Transform>::const_iterator xfmIt = xfms.begin(); xfmIt != xfms.end(); ++xfmIt){
                    it->mMMesh->mInstances.push_back(RndMultiMesh::Instance(*xfmIt));
                }
            }
            AssignRandomColors();
        }
    }
    else OnRebuild(0);
    if(gRev > 4) bs >> unk88;
    if(gRev > 0xC){
        bool force = false;
        bs >> force;
        Force3DCrowd(force);
    }
    if(gRev > 5) bs >> mShow3DOnly;
    if(gRev > 0xB) bs >> mFocus;
    if(gRev != 0) LOAD_SUPERCLASS(RndHighlightable);
END_LOADS

void WorldCrowd::AssignRandomColors(){
    for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
        if((*it).mDef.mChar && (*it).mMMesh && !(*it).m3DChars.empty()){
            bool b1 = false;
            std::vector<ColorPalette*> colorPaletteList;
            (*it).mDef.unk18 = false;
            for(int i = 0; i < 3; i++){
                ColorPalette* randPal = (*it).mDef.mChar->Find<ColorPalette>(MakeString("random%d.pal", i + 1), false);
                if(randPal){
                    colorPaletteList.push_back(randPal);
                    b1 = true;
                }
            }
            if(b1){
                for(int i = 0; i != (*it).m3DChars.size(); i++){
                    CharData::Char3D& curChar3D = (*it).m3DChars[i];
                    curChar3D.unk34.clear();
                    MILO_ASSERT(!colorPaletteList.empty(), 0x5B8);
                    (*it).mDef.unk18 = true;
                    while(curChar3D.unk34.size() < 3){
                        ColorPalette* randPal = colorPaletteList[RandomInt(0, colorPaletteList.size())];
                        Hmx::Color randColor = randPal->GetColor(RandomInt(0, randPal->NumColors()));
                        curChar3D.unk34.push_back(randColor);
                    }
                }
            }
        }
    }
}

void WorldCrowd::ListDrawChildren(std::list<RndDrawable*>& draws){
    for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
        Character* curChar = (*it).mDef.mChar;
        if(curChar) draws.push_back(curChar);   
    }
}

void WorldCrowd::UpdateSphere(){
    Sphere s;
    MakeWorldSphere(s, true);
    SetSphere(s);
}

float WorldCrowd::GetDistanceToPlane(const Plane& p, Vector3& vout){
    if(mCharacters.empty()) return 0;
    else {
        float dist = 0;
        bool b1 = true;
        for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
            RndMultiMesh* multimesh = it->mMMesh;
            if(multimesh){
                Vector3 v4c;
                float f5 = multimesh->GetDistanceToPlane(p, v4c);
                if(b1 || (std::fabs(f5) < std::fabs(dist))){
                    b1 = false;
                    vout = v4c;
                    dist = f5;
                }
            }
        }
        return dist;
    }
}

bool WorldCrowd::MakeWorldSphere(Sphere& s, bool b){
    if(b){
        s.Zero();
        for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
            RndMultiMesh* multimesh = it->mMMesh;
            if(multimesh){
                Sphere local;
                multimesh->MakeWorldSphere(local, true);
                s.GrowToContain(local);
            }
        }
        return true;
    }
    else if(mSphere.GetRadius()){
        s = mSphere;
        return true;
    }
    else return false;
}

void WorldCrowd::ListPollChildren(std::list<RndPollable*>& polls) const {
    for(ObjList<CharData>::const_iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
        Character* curChar = (*it).mDef.mChar;
        if(curChar) polls.push_back(curChar);
    }
}

void WorldCrowd::Poll(){
    if(Showing()){
        for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
            Character* curChar = (*it).mDef.mChar;
            if(curChar && curChar->GetPollState() != 3){
                curChar->Poll();
            }
        }
    }
}

void WorldCrowd::Enter(){
    RndPollable::Enter();
    for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
        Character* curChar = (*it).mDef.mChar;
        if(curChar){
            if(curChar->GetPollState() != 2) curChar->Enter();
            for(int i = 0; i < 3; i++){
                ColorPalette* randPal = curChar->Find<ColorPalette>(MakeString("random%d.pal", i + 1), false);
                if(!randPal || randPal->NumColors() == 0) break;
                if(i == 0){
                    for(ObjDirItr<RndMat> objIt(curChar, true); objIt; ++objIt){
                        (*it).mDef.unk1c.push_back(objIt);
                    }
                }
            }
        }
    }
}

void WorldCrowd::Exit(){
    RndPollable::Exit();
    for(ObjList<CharData>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
        Character* curChar = (*it).mDef.mChar;
        if(curChar) curChar->Exit();
    }
}

void WorldCrowd::Mats(std::list<RndMat*>&, bool){
    std::list<unsigned int> uints;
    GetMeshShaderFlags(0, uints);
}

WorldCrowd::CharData::CharData(Hmx::Object* o) : mDef(o), mMMesh(0) {

}

void WorldCrowd::CharData::Load(BinStream& bs){ bs >> mDef; }

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

void WorldCrowd::Force3DCrowd(bool force){
    mForce3DCrowd = force;
    if(mForce3DCrowd) Set3DCharAll();
    else {
        SetFullness(1, 1);
        Set3DCharList(std::vector<std::pair<int, int> >(), this);
    }
}

DataNode WorldCrowd::OnIterateFrac(DataArray* da){
    START_AUTO_TIMER("crowd_iter");
}

void WorldCrowd::CleanUpCrowdFloor(){
    Hmx::Object* miloObj = ObjectDir::Main()->FindObject("milo", false);
    if(!miloObj){
        WiiMesh* mesh = dynamic_cast<WiiMesh*>(mPlacementMesh.Ptr());
        if(mesh) mesh->RemoveVertData();
        else MILO_WARN("WorldCrowd[%s] does not have a placement mesh.", PathName(this));
    }
}

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
