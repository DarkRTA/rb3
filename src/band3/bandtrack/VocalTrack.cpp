#include "bandtrack/VocalTrack.h"
#include "bandobj/NoteTube.h"
#include "bandtrack/VocalStyle.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/Game.h"
#include "game/GameConfig.h"
#include "math/Mtx.h"
#include "meta_band/GameplayOptions.h"
#include "obj/Data.h"
#include "obj/DataFile.h"
#include "obj/DataFunc.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Std.h"

int maxPlatesQueued;
int maxVertsInPlate;
int maxFacesInPlate;
int maxNumLyricPlates;
bool sDumpPlateStates;
bool gDebugSpew;

inline TambourineGemPool::TambourineGemPool() {
    for (int i = 0; i < 25; i++) {
        mFreeGems.push_back(new TambourineGem());
    }
    unk50 = 0;
}

inline TambourineGemPool::~TambourineGemPool() {
    mFreeGems.clear(); // there's a custom func here to transfer gems from mUsedGems to
                       // mFreeGems
    MILO_ASSERT(mUsedGems.empty(), 0x1B6);
    for (int i = 0; i < mFreeGems.size(); i++) {
        RELEASE(mFreeGems[i]);
    }
}

void VocalTrack::UpdateMarkerVisibility(float f1, float f2) {
    for (int i = 0; i < unk1a0.size(); i++) {
        std::pair<RndMesh *, float> &curMarker = unk1a0[i];
        curMarker.first->SetShowing(curMarker.second >= f1 && curMarker.second <= f2);
    }
}

void VocalTrack::InvalidateMarkers(float f1) {
    while (!unk1a0.empty()) {
        if (f1 < unk1a0.front().second)
            break;
        ReturnFirstMarker();
    }
}

void VocalTrack::ClearMarkers() {
    while (!unk1a0.empty()) {
        ReturnFirstMarker();
    }
}

void VocalTrack::UpdateTubePlates(
    std::deque<TubePlate *> &deque, float f2, float f3, bool b4
) {
    if (unk60 || deque.empty())
        return;
    while (!deque.empty() && !deque.front()->NoVerts()
           && (deque.front()->CurrentEndX(f3) < mDir->mTrackLeftX - unk78
               || deque.front()->InvalidateMs() < f2)) {
        if (!deque.front()->Baked()) {
            MILO_WARN("popping unbaked plate");
        }
        TubePlate *cur = deque.front();
        if (sDumpPlateStates) {
            MILO_LOG(
                "%s recycling plate at %.2f sec\n",
                cur->GetMatName().c_str(),
                f2 / 1000.0f
            );
            DumpPlates(deque, cur->GetMatName().c_str());
        }
        deque.pop_front();
        cur->Reset();
        deque.push_back(cur);
    }
    float fvar1 = TheGame->InTrainer() ? unk2a4 : f2; // fix game bool being checked
    FOREACH (it, deque) {
        TubePlate *cur = *it;
        if (cur->CurrentEndX(f3) < mDir->mTrackLeftX) {
            cur->SetShowing(false);
        } else {
            if (cur->CurrentStartX(f3) >= mDir->mTrackRightX) {
                cur->SetShowing(false);
                break;
            } else
                cur->SetShowing(true);
        }

        if (sDumpPlateStates && !cur->Baked()) {
            MILO_LOG(
                "%s baking plate at %.2f sec\n", cur->GetMatName().c_str(), f2 / 1000.0f
            );
            DumpPlates(deque, cur->GetMatName().c_str());
        }
        cur->Bake();
        if (unk6c == 0 && cur->Deploy()) {
            cur->PollDeploy(fvar1);
        }
    }
#ifdef MILO_DEBUG
    if (deque.size() != 0) {
        if (deque.size() > maxPlatesQueued) {
            maxPlatesQueued = std::max<int>(maxPlatesQueued, deque.size());
            if (maxPlatesQueued >= 24) {
                MILO_WARN(
                    "Too many tube plates - please file a bug to Josh Stoddard and include the Watson output."
                );
                DumpPlates(deque, deque.front()->GetMatName().c_str());
            }
            if (sDumpPlateStates) {
                MILO_LOG("max plates queued -> %d\n", maxPlatesQueued);
            }
        }
        int numverts = deque.front()->mMesh->mGeomOwner->mVerts.size();
        if (numverts > maxVertsInPlate) {
            maxVertsInPlate = std::max<int>(maxVertsInPlate, numverts);
            if (sDumpPlateStates) {
                MILO_LOG("max verts in a plate -> %d\n", maxVertsInPlate);
            }
        }
        int numfaces = deque.front()->mMesh->mGeomOwner->mFaces.size();
        if (numfaces > maxFacesInPlate) {
            maxFacesInPlate = std::max<int>(maxFacesInPlate, numfaces);
            if (sDumpPlateStates) {
                MILO_LOG("max faces in a plate -> %d\n", maxFacesInPlate);
            }
        }
    }
#endif
}

void VocalTrack::UpdateAllTubePlates(float f1) {
    if (!mPlayer->IsNet()) {
        for (int i = 0; i < 3; i++) {
            UpdateTubePlates(mFrontTubePlates[i], f1, unk2a8, false);
            UpdateTubePlates(mBackTubePlates[i], f1, unk2a8, false);
            UpdateTubePlates(mPhonemeTubePlates[i], f1, unk2a8, false);
        }
    }
    bool staticVox = !IsScrolling();
    UpdateTubePlates(mLeadDeployPlates, f1, staticVox ? unk2ac : unk2a8, staticVox);
    UpdateTubePlates(mHarmonyDeployPlates, f1, staticVox ? unk2b0 : unk2a8, staticVox);
}

void VocalTrack::ClearTubePlates(std::deque<TubePlate *> &plates) {
    while (!plates.empty()) {
        delete plates.front();
        plates.pop_front();
    }
}

void VocalTrack::ClearAllTubePlates() {
    for (int i = 0; i < 3; i++) {
        ClearTubePlates(mFrontTubePlates[i]);
        ClearTubePlates(mBackTubePlates[i]);
        ClearTubePlates(mPhonemeTubePlates[i]);
    }
    ClearTubePlates(mLeadDeployPlates);
    ClearTubePlates(mHarmonyDeployPlates);
}

void VocalTrack::ResetTubePlates(std::deque<TubePlate *> &plates) {
    FOREACH (it, plates) {
        (*it)->Reset();
    }
}

void VocalTrack::ResetAllTubePlates() {
    for (int i = 0; i < 3; i++) {
        ResetTubePlates(mFrontTubePlates[i]);
        ResetTubePlates(mBackTubePlates[i]);
        ResetTubePlates(mPhonemeTubePlates[i]);
    }
    ResetTubePlates(mLeadDeployPlates);
    ResetTubePlates(mHarmonyDeployPlates);
    if (sDumpPlateStates) {
        MILO_LOG("resetting all plates\n");
    }
}

void VocalTrack::DumpPlates(std::deque<TubePlate *> &plates, const char *str) {
    MILO_LOG("dumping plates in %s\n", str);
    int idx = 0;
    FOREACH (it, plates) {
        TubePlate *cur = *it;
        if (!cur->NoVerts()) {
            Transform &xfm = cur->mMesh->TransParent()->WorldXfm();
            MILO_LOG(
                "\t[%d] @ %x, xPos: %.2f, xStart: %.2f, XEnd: %.2f, verts: %d, faces: %d, baked: %d\n",
                idx++,
                cur,
                -xfm.v.x,
                cur->GetBeginX(),
                cur->GetBeginX() + cur->GetWidthX(),
                cur->mMesh->Verts().size(),
                cur->mMesh->Faces().size(),
                cur->Baked()
            );
        } else {
            MILO_LOG(
                "\t[%d] @ %x, <empty>, verts: %d, faces: %d, baked: %d\n",
                idx++,
                cur,
                cur->mMesh->Verts().size(),
                cur->mMesh->Faces().size(),
                cur->Baked()
            );
        }
    }
}

void VocalTrack::DumpAllPlates() {
    for (int i = 0; i < 3; i++) {
        DumpPlates(mFrontTubePlates[i], MakeString("part %d front", i));
        DumpPlates(mBackTubePlates[i], MakeString("part %d back", i));
        DumpPlates(mPhonemeTubePlates[i], MakeString("part %d phoneme", i));
    }
    DumpPlates(mLeadDeployPlates, "lead deploy");
    DumpPlates(mHarmonyDeployPlates, "harmony deploy");
}

TubePlate *VocalTrack::GetCurrentPlate(std::deque<TubePlate *> &plates, int i2) {
    FOREACH (it, plates) {
        if (!(*it)->Baked())
            return *it;
    }
    plates.push_back(new TubePlate(i2));
#ifdef MILO_DEBUG
    static Symbol leadDeployMat = "deploy_mask_lead.mat";
    static Symbol harmDeployMat = "deploy_mask_harmony.mat";

    String matName = plates.front()->GetMatName();
    if (!unk60 && matName != leadDeployMat && matName != harmDeployMat) {
        MILO_WARN(
            "%s new plate added.  Please alert HUD/Track owner and include the Watson output.",
            matName.c_str()
        );
        DumpPlates(plates, plates.front()->GetMatName().c_str());
    }
#endif
    return plates.back();
}

void VocalTrack::HookupTubePlates(NoteTube *tube) {
    if (tube->Pitched()) {
        tube->SetFrontPlate(GetCurrentPlate(mFrontTubePlates[tube->Part()], 0x80));
        tube->SetBackPlate(GetCurrentPlate(mBackTubePlates[tube->Part()], 0x80));
    } else if (tube->unk_0x24) {
        bool islead = tube->Part() == 0;
        tube->SetFrontPlate(nullptr);
        tube->SetBackPlate(
            GetCurrentPlate(islead ? mLeadDeployPlates : mHarmonyDeployPlates, 0x20)
        );
    } else {
        tube->SetFrontPlate(nullptr);
        tube->SetBackPlate(GetCurrentPlate(mPhonemeTubePlates[tube->Part()], 0x40));
    }
}

DataNode ToggleDebugSpew(DataArray *) {
    gDebugSpew = !gDebugSpew;
    return gDebugSpew;
}

VocalTrack::VocalTrack(BandUser *u)
    : Track(u), unk68(0), unk6c(1), unk70(2), unk78(24.0f), unk7c(0), mDir(this),
      mPlayer(this), unke8(0), unkec(0), unkf0(0), unkf4(0), unkf8(0), unkfc(0),
      unk100(0), unk104(1), unk108(0), unk128(0), unk19c(0), unk1c8(this),
      mTambourineGemPool(0), unk204(-1), unk208(60), unk20c(0), unk210(0), unk23c(0.1f),
      unk240(0.1f), unk294(0), unk298(0), unk2a4(-1.0f), unk2a8(0), unk2ac(0), unk2b0(0),
      mStaticDeployZoneXSize(2.0f), mStaticDeployBufferX(0.5f),
      mStaticDeployMarginX(0.1f), mLyricShiftMs(100.0f), mLyricShiftQuickMs(20.0f),
      mLyricShiftAnticipationMs(250.0f), mMinLyricHighlightMs(100.0f),
      mMinPhraseHighlightMs(500.0f), mLyricOverlapWindowMs(100.0f), unk2e4(0),
      mNoteTube(new NoteTube()), unk2ec(1) {
    DataRegisterFunc("vocal_jitter_debug", ToggleDebugSpew);
    for (int i = 0; i < 3; i++) {
        mFrontTubePlates.push_back(std::deque<TubePlate *>());
        mBackTubePlates.push_back(std::deque<TubePlate *>());
        mPhonemeTubePlates.push_back(std::deque<TubePlate *>());
        unk2b4[i] = 0;
    }
    InitPlatePool();
}

VocalTrack::~VocalTrack() {
    RELEASE(mTambourineGemPool);
    ClearLyrics();
    ClearMarkers();
    ClearAllTubePlates();
    DeleteAll(unk194);
    RELEASE(mNoteTube);
}

void VocalTrack::InitPlateList(std::deque<TubePlate *> &list, int i2, int i3) {
    MILO_ASSERT(list.empty(), 0x25C);
    for (int i = 0; i < i2; i++) {
        list.push_back(new TubePlate(i3));
    }
}

void VocalTrack::InitPlatePool() {
    for (int i = 0; i < 3; i++) {
        InitPlateList(mFrontTubePlates[i], 4, 0x80);
        InitPlateList(mBackTubePlates[i], 4, 0x80);
        InitPlateList(mPhonemeTubePlates[i], 4, 0x40);
    }
    InitPlateList(mLeadDeployPlates, 4, 0x20);
    InitPlateList(mHarmonyDeployPlates, 4, 0x20);
}

void VocalTrack::Init() {
    const BandUser *pUser = mTrackConfig.GetBandUser();
    MILO_ASSERT(pUser, 0x275);
    mTrackConfig.SetTrackNum(TheGameConfig->GetTrackNum(pUser->mUserGuid));
    unk74 = 3000.0f;
    RELEASE(mTambourineGemPool);
    mTambourineGemPool = new TambourineGemPool();

    BandUser *user = (BandUser *)mTrackConfig.GetBandUser();
    GameplayOptions *options = user->GetGameplayOptions();
    if (options) {
        DataArray *staticArr = SystemConfig()->FindArray("force_static_vocals", false);
        if (staticArr) {
            if (SystemConfig()->FindInt("force_static_vocals")) {
                SetVocalStyle((VocalStyle)0);
            }
            goto next;
        }
        SetVocalStyle(options->GetVocalStyle());
    }
next:
    ReadTimingData(SystemConfig()->FindArray("track_graphics", true));
    unk1c8 = mDir->Find<RndGroup>("markers.grp", true);
    unk19c = 0;
    for (int i = 0; i < 0x20; i++) {
        CreateMarker("beat_marker.mesh", 0, false);
    }
    ClearMarkers();
}

void VocalTrack::ResetTimingData() {
    ReadTimingData(DataReadFile("config/track_graphics.dta", true));
    RebuildHUD();
}

void VocalTrack::ReadTimingData(const DataArray *a) {
    mLyricOverlapWindowMs = a->FindFloat("lyric_overlap_ms");
    DataArray *staticCfg = a->FindArray("static_vocal_parameters", true);
    mStaticDeployZoneXSize = staticCfg->FindFloat("static_deploy_x_size");
    mStaticDeployBufferX = staticCfg->FindFloat("static_deploy_buffer_x");
    mStaticDeployMarginX = staticCfg->FindFloat("static_phrase_margin_x");
    mLyricShiftMs = staticCfg->FindArray("lyric_shift_ms", true)->Float(1);
    mLyricShiftQuickMs = staticCfg->FindArray("lyric_shift_ms", true)->Float(2);
    mLyricShiftAnticipationMs = staticCfg->FindFloat("lyric_shift_anticipation_ms");
    mMinLyricHighlightMs = staticCfg->FindFloat("min_lyric_highlight_ms");
    mMinPhraseHighlightMs = staticCfg->FindFloat("phrase_highlight_ms");
    static bool sDump;
    if (sDump) {
        MILO_LOG("lyric timing data:\n");
        MILO_LOG("\t overlap window ms %.0f\n", mLyricOverlapWindowMs);
        MILO_LOG("\t static deploy size %.2f\n", mStaticDeployZoneXSize);
        MILO_LOG("\t static deploy gap size %.2f\n", mStaticDeployBufferX);
        MILO_LOG("\t now bar offset %.2f\n", mStaticDeployMarginX);
        MILO_LOG("\t standard lyric shift ms %.0f\n", mLyricShiftMs);
        MILO_LOG("\t fast lyric shift ms %.0f\n", mLyricShiftQuickMs);
        MILO_LOG("\t lyric shift anticipation ms %.0f\n", mLyricShiftAnticipationMs);
        MILO_LOG("\t min lyric highlight ms %.0f\n", mMinLyricHighlightMs);
        MILO_LOG("\t phrase highlight anticipation ms %.0f\n", mMinPhraseHighlightMs);
    }
}