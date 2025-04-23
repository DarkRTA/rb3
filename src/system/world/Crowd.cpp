#include "world/Crowd.h"
#include "CameraShot.h"
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
#include "stl/_pair.h"
#include "utl/Loader.h"
#include "utl/Symbols.h"
#include "world/ColorPalette.h"

RndCam *gImpostorCamera;
RndMat *gImpostorMat;
int gNumCrowd;
WorldCrowd *gParent;

INIT_REVS(WorldCrowd)

namespace {
    void GetMeshShaderFlags(RndMat *mat, std::list<unsigned int> &flags) {
        std::vector<ObjRef *>::const_reverse_iterator it = mat->Refs().rbegin();
        std::vector<ObjRef *>::const_reverse_iterator itEnd = mat->Refs().rend();
        for (; it != itEnd; ++it) {
            RndMesh *mesh = dynamic_cast<RndMesh *>((*it)->RefOwner());
            if (mesh) {
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

WorldCrowd::WorldCrowd()
    : mPlacementMesh(this), mCharacters(this), mNum(0), mRotate(kCrowdRotateNone),
      mForce3DCrowd(0), mShow3DOnly(0), mCharFullness(1.0f), mFlatFullness(1.0f), mLod(0),
      mEnviron(this), mEnviron3D(this), mFocus(this), mModifyStamp(0) {
    if (gNumCrowd++ == 0) {
#ifdef MILO_DEBUG
        GetGfxMode();
#endif
        gImpostorMat = Hmx::Object::New<RndMat>();
        gImpostorMat->SetUseEnv(true);
        gImpostorMat->SetPreLit(false);
        gImpostorMat->SetBlend(RndMat::kBlendSrc);
        gImpostorMat->SetZMode(RndMat::kZModeNormal);
        gImpostorMat->SetAlphaCut(true);
        gImpostorMat->SetAlphaThreshold(0x80);
        gImpostorMat->SetTexWrap(kTexWrapClamp);
        gImpostorMat->SetPerPixelLit(false);
        gImpostorMat->SetPointLights(true);
        gImpostorCamera = Hmx::Object::New<RndCam>();
        SetMatAndCameraLod();
    }
}

void WorldCrowd::SetMatAndCameraLod() {
    RndTex *tex = TheWiiRnd.GetSharedTex((WiiRnd::SharedTexType)5, true);
    gImpostorCamera->SetTargetTex(tex);
    gImpostorMat->SetDiffuseTex(tex);
}

WorldCrowd::~WorldCrowd() {
    FOREACH (it, mCharacters) {
        if (it->mMMesh) {
            delete it->mMMesh->GetMesh();
            RELEASE(it->mMMesh);
        }
    }
    gNumCrowd--;
    if (gNumCrowd == 0) {
        RELEASE(gImpostorCamera);
        RELEASE(gImpostorMat);
    }
}

void WorldCrowd::CreateMeshes() {
    mCharFullness = 1.0f;
    mFlatFullness = 1.0f;
    mLod = 0;
    FOREACH (it, mCharacters) {
        if (it->mMMesh) {
            delete it->mMMesh->GetMesh();
            RELEASE(it->mMMesh);
        }
        it->mBackup.clear();
        if (it->mDef.mChar) {
            RndMesh *built = BuildBillboard(it->mDef.mChar, it->mDef.mHeight);
            it->mMMesh = Hmx::Object::New<RndMultiMesh>();
            it->mMMesh->SetMesh(built);
        }
    }
}

DataNode WorldCrowd::OnRebuild(DataArray *da) { return 0; }

BEGIN_COPYS(WorldCrowd)
    COPY_SUPERCLASS(RndDrawable)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(WorldCrowd)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mPlacementMesh)
        COPY_MEMBER(mNum)
        COPY_MEMBER(mCenter)
        COPY_MEMBER(mCharFullness)
        COPY_MEMBER(mFlatFullness)
        COPY_MEMBER(mLod)
        COPY_MEMBER(mEnviron)
        COPY_MEMBER(mEnviron3D)
        COPY_MEMBER(mForce3DCrowd)
        COPY_MEMBER(mShow3DOnly)
        COPY_MEMBER(mFocus)
        mCharacters.clear();
        mCharacters.resize(c->mCharacters.size());
        ObjList<CharData>::const_iterator j = c->mCharacters.begin();
        ObjList<CharData>::iterator i = mCharacters.begin();
        for (; i != mCharacters.end(); ++i, ++j) {
            i->mDef = j->mDef;
            i->mBackup = j->mBackup;
            i->m3DChars = j->m3DChars;
            i->m3DCharsCreated = j->m3DCharsCreated;
        }
        CreateMeshes();
        j = c->mCharacters.begin();
        for (ObjList<CharData>::iterator i = mCharacters.begin(); i != mCharacters.end();
             ++i, ++j) {
            if (i->mMMesh) {
                MILO_ASSERT(j->mMMesh, 0x1EB);
                i->mMMesh->mInstances = j->mMMesh->mInstances;
            }
        }
    END_COPYING_MEMBERS
END_COPYS

void WorldCrowd::CollideList(const Segment &seg, std::list<Collision> &colls) {
    if (LOADMGR_EDITMODE && CollideSphere(seg)) {
        FOREACH (it, mCharacters) {
            RndMultiMesh *curMM = it->mMMesh;
            if (curMM) {
                curMM->CollideList(seg, colls);
            }
        }
    }
}

// matches in retail
void WorldCrowd::Reset3DCrowd() {
    SetFullness(1.0f, mCharFullness);
    FOREACH (it, mCharacters) {
        RndMultiMesh *multiMesh = it->mMMesh;
        if (multiMesh) {
            int i6 = 0;
            std::list<RndMultiMesh::Instance>::iterator instIt =
                multiMesh->mInstances.begin();
            for (int i = 0; i != it->m3DCharsCreated.size(); i++) {
                int cap = it->m3DCharsCreated[i].unk30;
                for (; i6 != cap; i6++)
                    ++instIt;
                CharData::Char3D &curChar3D = it->m3DCharsCreated[i];
                RndMultiMesh::Instance inst(curChar3D.unk0);
                instIt = multiMesh->mInstances.insert(instIt, inst);
            }
        }
        it->m3DCharsCreated.clear();
        it->m3DChars.clear();
    }
}

void WorldCrowd::Sort3DCharList() {
    FOREACH (it, mCharacters) {
        std::sort(it->m3DChars.begin(), it->m3DChars.end(), Sort3DChars());
        it->m3DCharsCreated = it->m3DChars;
    }
}

// matches in retail
void WorldCrowd::Set3DCharAll() {
    START_AUTO_TIMER("crowd_set3d");
    float fvar1 = mFlatFullness;
    Reset3DCrowd();
    FOREACH (it, mCharacters) {
        RndMultiMesh *multiMesh = it->mMMesh;
        if (multiMesh) {
            std::list<RndMultiMesh::Instance>::iterator instIt =
                multiMesh->mInstances.begin();
            int idx = 0;
            for (; instIt != multiMesh->mInstances.end(); ++instIt, ++idx) {
                CharData::Char3D char3D(instIt->mXfm, idx);
                it->m3DChars.push_back(char3D);
            }
            multiMesh->mInstances.clear();
            multiMesh->InvalidateProxies();
        }
    }
    Sort3DCharList();
    SetFullness(fvar1, mCharFullness);
    AssignRandomColors();
}

void WorldCrowd::Set3DCharList(
    const std::vector<std::pair<int, int> > &pairVec, Hmx::Object *obj
) {
    START_AUTO_TIMER("crowd_set3d");
    if (!IsForced3DCrowd()) {
        float oldFullness = mFlatFullness;
        Reset3DCrowd();
        std::vector<std::pair<RndMultiMesh *, std::list<RndMultiMesh::Instance>::iterator> >
            grosserPairs;
        grosserPairs.reserve(pairVec.size());
        for (int i = 0; i != pairVec.size(); i++) {
            int cap1 = pairVec[i].first;
#ifdef MILO_DEBUG
            if (cap1 >= mCharacters.size()) {
                MILO_WARN(
                    "%s setting bad mesh %d, only has %d",
                    PathName(obj),
                    cap1,
                    mCharacters.size()
                );
            } else {
#endif
                ObjList<CharData>::iterator charIt = mCharacters.begin();
                for (int n = 0; n < cap1; ++n, ++charIt)
                    ;
                RndMultiMesh *curMMesh = charIt->mMMesh;
                if (curMMesh) {
                    int cap2 = pairVec[i].second;
#ifdef MILO_DEBUG
                    if (cap2 >= curMMesh->mInstances.size()) {
                        MILO_WARN(
                            "%s setting bad 3d char %d on mmesh %s, only has %d chars",
                            PathName(this),
                            cap2,
                            curMMesh->Name(),
                            curMMesh->mInstances.size()
                        );
                    } else {
#endif
                        std::list<RndMultiMesh::Instance>::iterator instIt =
                            curMMesh->mInstances.begin();
                        for (int n = 0; n < cap2; ++instIt, ++n)
                            ;
                        charIt->m3DChars.push_back(CharData::Char3D(instIt->mXfm, cap2));
                        grosserPairs.push_back(std::make_pair(charIt->mMMesh, instIt));
#ifdef MILO_DEBUG
                    }
#endif
                }
#ifdef MILO_DEBUG
            }
#endif
        }
        for (int i = 0; i != grosserPairs.size(); i++) {
            grosserPairs[i].first->mInstances.erase(grosserPairs[i].second);
            grosserPairs[i].first->InvalidateProxies();
        }
        Sort3DCharList();
        SetFullness(oldFullness, mCharFullness);
        AssignRandomColors();
    }
}

void SetMatColorFlags(
    ObjPtrList<RndMat> &matList,
    RndMat::ColorModFlags flags,
    std::vector<Hmx::Color> *modulate
) {
    FOREACH (it, matList) {
        (*it)->SetColorModFlags(flags);
        if (modulate) {
            MILO_ASSERT(RndMat::kColorModNum == modulate->size(), 0x2CB);
            for (int i = 0; i < modulate->size(); i++) {
                (*it)->SetColorMod(modulate->at(i), i);
            }
        }
    }
}

bool WorldCrowd::Crowd3DExists() {
    FOREACH (it, mCharacters) {
        if ((*it).mDef.mChar && (*it).mMMesh && !(*it).m3DChars.empty()) {
            return true;
        }
    }
    return false;
}

void WorldCrowd::Draw3DChars() {}

void WorldCrowd::DrawShowing() {
    START_AUTO_TIMER("crowd_draw");
    MILO_ASSERT(!gImpostorMat->NextPass(), 0x34A);
    MILO_NOTIFY_ONCE(
        "%s: Rendering 2D crowd character texture without an environment, set the environ property on the WorldCrowd object."
    );
}

RndMesh *WorldCrowd::BuildBillboard(Character *c, float f) {
    c->mSphere.GetRadius();
    RndMesh *mesh = Hmx::Object::New<RndMesh>();
    RndMesh::VertVector &verts = mesh->Verts();
    std::vector<RndMesh::Face> &faces = mesh->Faces();
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

void WorldCrowd::SetLod(int lod) { mLod = Clamp(0, 2, lod); }

void WorldCrowd::SetFullness(float, float) { START_AUTO_TIMER("crowd_set"); }

SAVE_OBJ(WorldCrowd, 0x4BF)

DECOMP_FORCEACTIVE(WorldCrowd, "ObjPtr_p.h", "f.Owner()", "")

// matches in retail
BEGIN_LOADS(WorldCrowd)
    LOAD_REVS(bs)
    ASSERT_REVS(0xE, 0)
    LOAD_SUPERCLASS(RndDrawable)
    bs >> mPlacementMesh;
    if (gRev < 3) {
        int i;
        bs >> i;
    }
    bs >> mNum;
    if (gRev < 8) {
        bool b;
        bs >> b;
    }
    bs >> mCharacters;
    if (gRev > 6)
        bs >> mEnviron;
    if (gRev > 9)
        bs >> mEnviron3D;
    else
        mEnviron3D = mEnviron;
    if (gRev > 1) {
        CreateMeshes();
        FOREACH (it, mCharacters) {
            if (gRev < 0xE) {
                std::list<Transform> xfmList;
                std::list<RndMultiMesh::Instance> instancesList;
                std::list<OldMMInst> oldmmiList;
                if (it->mMMesh) {
                    if (gRev < 9) {
                        bs >> xfmList;
                        it->mMMesh->mInstances.clear();
                        FOREACH (transIt, xfmList) {
                            std::list<RndMultiMesh::Instance> &instances =
                                it->mMMesh->mInstances;
                            instances.push_back(RndMultiMesh::Instance(*transIt));
                        }
                    } else if (gRev < 0xB) {
                        bs >> oldmmiList;
                        FOREACH (mmiIt, oldmmiList) {
                            OldMMInst &old = *mmiIt;
                            std::list<RndMultiMesh::Instance> &instances =
                                it->mMMesh->mInstances;
                            instances.push_back(RndMultiMesh::Instance(old.mOldXfm));
                        }
                    } else {
                        std::list<RndMultiMesh::Instance> &instances =
                            it->mMMesh->mInstances;
                        unsigned int count;
                        bs >> count;
                        if (count > 10000000) {
                            MILO_FAIL(
                                "Crowd tried to allocate %d mesh instances.  That's a little excessive, no?",
                                count
                            );
                        }
                        instances.resize(count);
                        FOREACH_POST (instIt, instances) {
                            instIt->LoadRev(bs, 3);
                        }
                    }
                } else if (gRev > 3) {
                    if (gRev < 9)
                        bs >> xfmList;
                    else if (gRev < 0xB)
                        bs >> oldmmiList;
                    else
                        bs >> instancesList;
                }
            } else {
                std::list<Transform> xfms;
                bs >> xfms;
                it->mMMesh->mInstances.clear();
                std::list<Transform>::iterator xfmItEnd = xfms.end();
                std::list<Transform>::iterator xfmIt = xfms.begin();
                for (; xfmIt != xfmItEnd; ++xfmIt) {
                    std::list<RndMultiMesh::Instance> &instances = it->mMMesh->mInstances;
                    instances.push_back(RndMultiMesh::Instance(*xfmIt));
                }
            }
            AssignRandomColors();
        }
    } else
        OnRebuild(0);
    if (gRev > 4)
        bs >> mModifyStamp;
    if (gRev > 0xC) {
        bool force = false;
        bs >> force;
        Force3DCrowd(force);
    }
    if (gRev > 5)
        bs >> mShow3DOnly;
    if (gRev > 0xB)
        bs >> mFocus;
    if (gRev != 0)
        LOAD_SUPERCLASS(RndHighlightable);
END_LOADS

void WorldCrowd::AssignRandomColors() {
    FOREACH (it, mCharacters) {
        if (it->mDef.mChar && it->mMMesh && !it->m3DChars.empty()) {
            bool b1 = false;
            std::vector<ColorPalette *> colorPaletteList;
            it->mDef.mUseRandomColor = false;
            for (int i = 0; i < 3; i++) {
                ColorPalette *randPal = it->mDef.mChar->Find<ColorPalette>(
                    MakeString("random%d.pal", i + 1), false
                );
                if (randPal) {
                    colorPaletteList.push_back(randPal);
                    b1 = true;
                }
            }
            if (b1) {
                for (int i = 0; i != it->m3DChars.size(); i++) {
                    CharData::Char3D &curChar3D = it->m3DChars[i];
                    curChar3D.mRandomColors.clear();
                    MILO_ASSERT(!colorPaletteList.empty(), 0x5B8);
                    it->mDef.mUseRandomColor = true;
                    while (curChar3D.mRandomColors.size() < 3) {
                        ColorPalette *randPal =
                            colorPaletteList[RandomInt(0, colorPaletteList.size())];
                        Hmx::Color randColor =
                            randPal->GetColor(RandomInt(0, randPal->NumColors()));
                        curChar3D.mRandomColors.push_back(randColor);
                    }
                }
            }
        }
    }
}

void WorldCrowd::ListDrawChildren(std::list<RndDrawable *> &draws) {
    FOREACH (it, mCharacters) {
        Character *curChar = it->mDef.mChar;
        if (curChar)
            draws.push_back(curChar);
    }
}

void WorldCrowd::UpdateSphere() {
    Sphere s;
    MakeWorldSphere(s, true);
    SetSphere(s);
}

float WorldCrowd::GetDistanceToPlane(const Plane &p, Vector3 &vout) {
    if (mCharacters.empty())
        return 0;
    else {
        float dist = 0;
        bool b1 = true;
        FOREACH (it, mCharacters) {
            RndMultiMesh *multimesh = it->mMMesh;
            if (multimesh) {
                Vector3 v4c;
                float f5 = multimesh->GetDistanceToPlane(p, v4c);
                if (b1 || (std::fabs(f5) < std::fabs(dist))) {
                    b1 = false;
                    vout = v4c;
                    dist = f5;
                }
            }
        }
        return dist;
    }
}

bool WorldCrowd::MakeWorldSphere(Sphere &s, bool b) {
    if (b) {
        s.Zero();
        FOREACH (it, mCharacters) {
            RndMultiMesh *multimesh = it->mMMesh;
            if (multimesh) {
                Sphere local;
                multimesh->MakeWorldSphere(local, true);
                s.GrowToContain(local);
            }
        }
        return true;
    } else if (mSphere.GetRadius()) {
        s = mSphere;
        return true;
    } else
        return false;
}

void WorldCrowd::ListPollChildren(std::list<RndPollable *> &polls) const {
    FOREACH (it, mCharacters) {
        Character *curChar = it->mDef.mChar;
        if (curChar)
            polls.push_back(curChar);
    }
}

void WorldCrowd::Poll() {
    if (Showing()) {
        FOREACH (it, mCharacters) {
            Character *curChar = it->mDef.mChar;
            if (curChar && curChar->GetPollState() != 3) {
                curChar->Poll();
            }
        }
    }
}

void WorldCrowd::Enter() {
    RndPollable::Enter();
    FOREACH (it, mCharacters) {
        Character *curChar = it->mDef.mChar;
        if (curChar) {
            if (curChar->GetPollState() != 2)
                curChar->Enter();
            for (int i = 0; i < 3; i++) {
                ColorPalette *randPal =
                    curChar->Find<ColorPalette>(MakeString("random%d.pal", i + 1), false);
                if (!randPal || randPal->NumColors() == 0)
                    break;
                if (i == 0) {
                    for (ObjDirItr<RndMat> objIt(curChar, true); objIt; ++objIt) {
                        it->mDef.mMats.push_back(objIt);
                    }
                }
            }
        }
    }
}

void WorldCrowd::Exit() {
    RndPollable::Exit();
    FOREACH (it, mCharacters) {
        Character *curChar = it->mDef.mChar;
        if (curChar)
            curChar->Exit();
    }
}

void WorldCrowd::Mats(std::list<RndMat *> &, bool) {
    std::list<unsigned int> uints;
    GetMeshShaderFlags(0, uints);
}

WorldCrowd::CharData::CharData(Hmx::Object *o) : mDef(o), mMMesh(0) {}

void WorldCrowd::CharData::Load(BinStream &bs) { bs >> mDef; }

WorldCrowd::CharDef::CharDef(Hmx::Object *o)
    : mChar(o), mHeight(75.0f), mDensity(1.0f), mRadius(10.0f), mUseRandomColor(0),
      mMats(o) {}

void WorldCrowd::CharDef::Load(BinStream &bs) {
    bs >> mChar;
    bs >> mHeight;
    bs >> mDensity;
    if (WorldCrowd::gRev > 1)
        bs >> mRadius;
    if (WorldCrowd::gRev > 8)
        bs >> mUseRandomColor;
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

void WorldCrowd::Force3DCrowd(bool force) {
    mForce3DCrowd = force;
    if (mForce3DCrowd)
        Set3DCharAll();
    else {
        SetFullness(1, 1);
        Set3DCharList(std::vector<std::pair<int, int> >(), this);
    }
}

DataNode WorldCrowd::OnIterateFrac(DataArray *da) { START_AUTO_TIMER("crowd_iter"); }

void WorldCrowd::CleanUpCrowdFloor() {
    Hmx::Object *miloObj = ObjectDir::Main()->FindObject("milo", false);
    if (!miloObj) {
        WiiMesh *mesh = dynamic_cast<WiiMesh *>(mPlacementMesh.Ptr());
        if (mesh)
            mesh->RemoveVertData();
        else
            MILO_WARN("WorldCrowd[%s] does not have a placement mesh.", PathName(this));
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
