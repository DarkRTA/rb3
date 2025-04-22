#include "world/SpotlightDrawer.h"
#include "char/Character.h"
#include "decomp.h"
#include "math/Color.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/BoxMap.h"
#include "rndobj/Draw.h"
#include "rndobj/Env.h"
#include "rndobj/Flare.h"
#include "rndobj/Mesh.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Rnd.h"
#include "utl/Std.h"
#include "utl/Symbols.h"
#include "world/Spotlight.h"

RndEnviron *SpotlightDrawer::sEnviron;
RndMat *SpotlightDrawer::sEditorMat;
SpotlightDrawer *SpotlightDrawer::sCurrent;
SpotlightDrawer *SpotlightDrawer::sDefault;
std::vector<SpotlightDrawer::SpotlightEntry> SpotlightDrawer::sLights;
std::vector<SpotlightDrawer::SpotMeshEntry> SpotlightDrawer::sCans;
std::vector<class Spotlight *> SpotlightDrawer::sShadowSpots;
int SpotlightDrawer::sNeedBoxMap = -1;
bool SpotlightDrawer::sNeedDraw;
bool SpotlightDrawer::sHaveAdditionals;
bool SpotlightDrawer::sHaveLenses;
bool SpotlightDrawer::sHaveFlares;
bool SpotlightDrawer::sNoBeams;

DECOMP_FORCEACTIVE(SpotlightDrawer, "%s drawn after SpotlightEnder")

SpotlightDrawer::SpotlightDrawer() : mParams(this) { SetOrder(-100000.f); }

SpotlightDrawer::~SpotlightDrawer() {
    if (sCurrent == this) {
        DeSelect();
        ClearAndShrink(sLights);
        ClearAndShrink(sShadowSpots);
        ClearAndShrink(sCans);
    }
}

void SpotlightDrawer::RemoveFromLists(Spotlight *spot) {
    for (std::vector<SpotlightDrawer::SpotlightEntry>::iterator it = sLights.begin();
         it != sLights.end();) {
        if (it->unk4 == spot) {
            it = sLights.erase(it);
        } else
            ++it;
    }
    for (std::vector<SpotlightDrawer::SpotMeshEntry>::iterator it = sCans.begin();
         it != sCans.end();) {
        if (it->unk8 == spot) {
            it = sCans.erase(it);
        } else
            ++it;
    }
    for (std::vector<class Spotlight *>::iterator it = sShadowSpots.begin();
         it != sShadowSpots.end();) {
        if (*it == spot) {
            it = sShadowSpots.erase(it);
        } else
            ++it;
    }
}

void SpotlightDrawer::ListDrawChildren(std::list<RndDrawable *> &draws) {
    draws.push_back(mParams.mProxy);
}

void SpotlightDrawer::SetAmbientColor(const Hmx::Color &c) {
    sEnviron->SetAmbientColor(c);
    sEnviron->Select(nullptr);
}

void SpotlightDrawer::DrawLight(Spotlight *) {
    RndMesh *mesh;
    MILO_ASSERT(mesh, 0x0);
}

void SpotlightDrawer::UpdateBoxMap() {
    if ((uint)sNeedBoxMap != TheRnd->GetFrameID()) {
        RndEnviron::sGlobalLighting.Clear();
        float lightingInf = mParams.mLightingInfluence;
        if (lightingInf > 0) {
            ApplyLightingApprox(RndEnviron::sGlobalLighting, lightingInf);
        }
        sNeedBoxMap = TheRnd->GetFrameID();
    }
}

void SpotlightDrawer::EndWorld() {
    if (TheRnd->ProcCmds() & kProcessChar) {
        UpdateBoxMap();
        if (sNeedDraw) {
            DrawWorld();
            ClearPostDraw();
        }
        if (TheRnd->DisablePP()) {
            ClearLights();
        }
        MILO_ASSERT(!sNeedDraw, 0x172);
    }
}

void SpotlightDrawer::OnGPHangRecover() {}

void SpotlightDrawer::Select() {
    if (sCurrent != this) {
        if (sCurrent) {
            TheRnd->UnregisterPostProcessor(sCurrent);
        }
        sCurrent = this;
        TheRnd->RegisterPostProcessor(this);
    }
    sNeedBoxMap = -1;
}

void SpotlightDrawer::DeSelect() {
    if (sCurrent != this)
        return;
    if (sDefault == this)
        return;
    sDefault->Select();
}

void SpotlightDrawer::Init() {
    sEnviron = Hmx::Object::New<RndEnviron>();
    sEnviron->SetUseApproxes(false);
    Register();
    sDefault = Hmx::Object::New<SpotlightDrawer>();
    sDefault->mParams.mLightingInfluence = 0;
    sDefault->Select();
}

void SpotlightDrawer::SortLights() {
    if (sLights.size() > 2) {
        std::sort(sLights.begin(), sLights.end(), ByColor());
    }
    if (sCans.size() > 2) {
        std::sort(sCans.begin(), sCans.end(), ByEnvMesh());
    }
}

template <class T>
void DrawAccessories(const SpotlightDrawer::SpotlightEntry *&, const SpotlightDrawer::SpotlightEntry *&);

struct LensExtract {};

void SpotlightDrawer::DrawWorld() {
    if ((!sLights.empty() || !sCans.empty()) && Showing()) {
        SortLights();
        DrawMeshVec(sCans);
        sCans.resize(0);
        RndEnviron *cur = RndEnviron::sCurrent;
        if (!sLights.empty()) {
            Vector3 *pos = cur->CurrentPos();
            MILO_ASSERT(sEnviron->GetUseApprox() == false, 0x1EE);
            sEnviron->Select(nullptr);
            DrawShadow();
            std::vector<SpotlightDrawer::SpotlightEntry>::iterator it = sLights.begin();
            std::vector<SpotlightDrawer::SpotlightEntry>::iterator itEnd = sLights.end();
            while (it != itEnd) {
                const SpotlightEntry *const e1 = it;
                const Hmx::Color &c = e1->unk4->IntensifiedColor();
                const SpotlightEntry *const e2 = it;
                // for (; e2 != itEnd && e2 == e1; ++e2)
                //     ;
                // SetAmbientColor(c);
                // if (sHaveAdditionals) {
                //     DrawAdditional(it, e2);
                // }
                // if (sHaveLenses) {
                //     DrawAccessories<LensExtract>(e1, e2);
                // }
                // if (!sNoBeams && TheRnd->DrawMode() != 4) {
                //     DrawBeams(it, e2);
                // }
                // if (sHaveFlares) {
                //     DrawFlares(it, e2);
                // }
                // it = (SpotlightEntry *)e2;
            }
            cur->Select(pos);
        }
    }
}

void SpotlightDrawer::ApplyLightingApprox(BoxMapLighting &boxMap, float f2) const {
    MILO_ASSERT(boxMap.NumQueuedLights() == 0, 0x21D);
    std::vector<SpotlightEntry>::iterator it = sLights.begin();
    std::vector<SpotlightEntry>::iterator itEnd = sLights.end();
    for (; it != itEnd; ++it) {
        Spotlight *curSpotlight = it->unk4;
        Transform &xfm = curSpotlight->WorldXfm();
        Hmx::Color c50(curSpotlight->Color());
        Multiply(c50, f2, c50);
        Multiply(c50, curSpotlight->Intensity(), c50);
        BoxMapLighting::LightParams_Spot *params;
        if (!boxMap.ParamsAt(params))
            break;
        params->unk38 = xfm.v;
        params->unk0 = xfm.m.y;
        params->mColor = c50;
        params->unk48 = curSpotlight->mBeam.mTopRadius;
        params->unk4c = curSpotlight->mBeam.mBottomRadius * 2.0f;
        params->unk44 = curSpotlight->mBeam.mLength * 2.0f;
        boxMap.CacheData(*params);
    }
}

void SpotlightDrawer::DrawMeshVec(std::vector<SpotMeshEntry> &entries) {
    if (entries.size() != 0) {
        std::vector<SpotMeshEntry>::iterator it = entries.begin();
        RndMesh *mesh = it->unk0;
        RndMultiMesh *multiMesh = mesh->CreateMultiMesh();
        multiMesh->mInstances.push_back(RndMultiMesh::Instance(it->unk10));
        RndMesh *mesh4 = it->unk4;
        mesh4->Highlight();
        std::vector<SpotMeshEntry>::iterator itEnd = entries.end();
        for (; it != itEnd; ++it) {
            RndMesh *mesh2 = it->unk0;
            int i6 = mesh4 - it->unk4;
            int i1 = i6 - 1 + (i6 == 0);
            if (i6 != i1 || mesh != mesh2) {
                multiMesh->DrawShowing();
                if (i6 != i1 && mesh4) {
                    mesh4 = it->unk4;
                    mesh4->Highlight();
                }
                if (mesh != mesh2) {
                    multiMesh = it->unk0->CreateMultiMesh();
                }
            }
            multiMesh->mInstances.push_back(RndMultiMesh::Instance(it->unk10));
        }
        multiMesh->DrawShowing();
    }
}

#pragma push
#pragma auto_inline on
void SpotlightDrawer::DrawShowing() {
    if (sCurrent && sCurrent != sDefault && sCurrent != this) {
        MILO_NOTIFY_ONCE(
            "Drawing 2 spotlightdrawers in one frame, %s and %s",
            PathName(sCurrent),
            PathName(this)
        );
    } else
        Select();
}
#pragma pop

void SpotlightDrawer::DrawShadow() {
    std::vector<Spotlight *>::iterator it = sShadowSpots.begin();
    std::vector<Spotlight *>::iterator itEnd = sShadowSpots.end();
    for (; it != itEnd; ++it) {
        Spotlight *shadowSpot = *it;
        MILO_ASSERT(shadowSpot->GetTarget() && shadowSpot->GetCastShadow(), 0x29A);
        Character *theChar = dynamic_cast<Character *>(shadowSpot->GetTarget());
        if (theChar) {
            Vector3 v48(theChar->WorldXfm().v);
            v48.z += 1.5f;
            Plane p58(v48, Vector3(0, 0, 1));
            theChar->DrawShadow(shadowSpot->WorldXfm(), p58);
        }
    }
}

void SpotlightDrawer::DrawAdditional(
    SpotlightDrawer::SpotlightEntry *spotIter,
    SpotlightDrawer::SpotlightEntry *const &spotEnd
) {
    MILO_ASSERT(spotIter != spotEnd, 0x2AF);
    for (; spotIter != spotEnd; ++spotIter) {
        Spotlight *sl = spotIter->unk4;
        FOREACH (it, sl->mAdditionalObjects) {
            RndDrawable *add = *it;
            MILO_ASSERT(add != sl, 0x2BA);
            if (add != sl)
                add->Draw();
        }
    }
}

void SpotlightDrawer::DrawLenses(
    SpotlightDrawer::SpotlightEntry *spotIter,
    SpotlightDrawer::SpotlightEntry *const &spotEnd
) {
    MILO_ASSERT(spotIter != spotEnd, 0x2C8);
    for (; spotIter != spotEnd; ++spotIter) {
        Spotlight *sl = spotIter->unk4;
        if (Spotlight::sDiskMesh) {
            MILO_ASSERT(sl->LensMesh(), 0x2D0);
            Spotlight::sDiskMesh->SetMat(sl->LensMesh());
            Spotlight::sDiskMesh->Draw();
        }
    }
}

void SpotlightDrawer::DrawBeams(
    SpotlightDrawer::SpotlightEntry *spotIter,
    SpotlightDrawer::SpotlightEntry *const &spotEnd
) {
    MILO_ASSERT(spotIter != spotEnd, 0x2DE);
    for (; spotIter != spotEnd; ++spotIter) {
        Spotlight *sl = spotIter->unk4;
        Spotlight::BeamDef &def = sl->mBeam;
        if (def.mBeam) {
            float f3 = 1;
            RndMat *mat = def.mBeam->Mat();
            if (mat) {
                f3 = mat->Alpha();
                mat->SetAlpha(f3 * 0.60f);
            }
            MILO_ASSERT(def.mBeam->Showing(), 0x307);
            def.mBeam->DrawShowing();
            if (mat) {
                mat->SetAlpha(f3);
            }
        }
    }
}

void SpotlightDrawer::DrawFlares(
    SpotlightDrawer::SpotlightEntry *spotIter,
    SpotlightDrawer::SpotlightEntry *const &spotEnd
) {
    MILO_ASSERT(spotIter != spotEnd, 0x31E);
    for (; spotIter != spotEnd; ++spotIter) {
        Spotlight *sl = spotIter->unk4;
        if (sl->GetFlare() && sl->GetFlare()->GetMat()) {
            sl->GetFlare()->Draw();
        }
    }
}

void SpotlightDrawer::ClearPostDraw() {
    ClearLights();
    sNeedDraw = false;
}

void SpotlightDrawer::ClearLights() {
    sLights.resize(0);
    sShadowSpots.resize(0);
    sCans.resize(0);
    sHaveAdditionals = false;
    sHaveLenses = false;
    sHaveFlares = false;
}

SAVE_OBJ(SpotlightDrawer, 0x344)

BEGIN_COPYS(SpotlightDrawer)
    COPY_SUPERCLASS(RndDrawable)
    CREATE_COPY(SpotlightDrawer)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mParams)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_LOADS(SpotlightDrawer)
    int rev;
    bs >> rev;
    if (rev > 5)
        MILO_FAIL("DxSpotlightDrawer: not forward compatable!");
    else {
        if (rev > 0)
            LOAD_SUPERCLASS(RndDrawable)
        else
            LOAD_SUPERCLASS(Hmx::Object)
        SetOrder(-100000.f);
        mParams.Load(bs, rev);
    }
END_LOADS

SpotDrawParams::SpotDrawParams(SpotlightDrawer *owner)
    : mIntensity(1.0f), mColor(1.0f, 1.0f, 1.0f), mBaseIntensity(0.1f),
      mSmokeIntensity(0.5f), mHalfDistance(250.0f), mLightingInfluence(1.0f),
      mTexture(owner, 0), mProxy(owner, 0), mOwner(owner) {
    MILO_ASSERT(owner, 0x37C);
}

SpotDrawParams &SpotDrawParams::operator=(const SpotDrawParams &params) {
    mIntensity = params.mIntensity;
    mBaseIntensity = params.mBaseIntensity;
    mSmokeIntensity = params.mSmokeIntensity;
    mHalfDistance = params.mHalfDistance;
    mLightingInfluence = params.mLightingInfluence;
    mColor = params.mColor;
    mTexture = params.mTexture;
    mProxy = params.mProxy;
    return *this;
}

void SpotDrawParams::Load(BinStream &bs, int rev) {
    if (rev > 5)
        MILO_WARN("Can't load new Params");
    else {
        bs >> mIntensity;
        if (rev > 3) {
            bs >> mSmokeIntensity >> mHalfDistance >> mLightingInfluence;
        } else {
            float i, j, k, l;
            bs >> i >> j >> k >> l;
            if (k < 0.5f) {
                mSmokeIntensity = 0.5f;
                mBaseIntensity = 0.1f;
            } else {
                mBaseIntensity = 0.15f;
                mSmokeIntensity = 1.0f;
            }
        }
        bs >> mColor;
        if (rev < 4) {
            int a, b, c, d, e;
            bs >> a >> b >> c >> d >> e;
        }
        bs >> mTexture;
        bs >> mProxy;
        if (rev < 3) {
            bool b;
            bs >> b;
        }
        if (rev > 4)
            bs >> mLightingInfluence;
    }
}

BEGIN_HANDLERS(SpotlightDrawer)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_ACTION(select, Select())
    HANDLE_ACTION(deselect, DeSelect())
    HANDLE_CHECK(0x3E4)
END_HANDLERS

BEGIN_PROPSYNCS(SpotlightDrawer)
    SYNC_PROP(total, mParams.mIntensity)
    SYNC_PROP(base_intensity, mParams.mBaseIntensity)
    SYNC_PROP(smoke_intensity, mParams.mSmokeIntensity)
    SYNC_PROP(color, mParams.mColor)
    SYNC_PROP(proxy, mParams.mProxy)
    SYNC_PROP(light_influence, mParams.mLightingInfluence)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS