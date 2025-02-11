#include "bandtrack/VocalTrack.h"
#include "GraphicsUtl.h"
#include "VocalStyle.h"
#include "bandobj/NoteTube.h"
#include "bandobj/VocalTrackDir.h"
#include "bandtrack/Lyric.h"
#include "bandtrack/TrackPanel.h"
#include "bandtrack/VocalStyle.h"
#include "beatmatch/VocalNote.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/Game.h"
#include "game/GameConfig.h"
#include "game/Player.h"
#include "game/SongDB.h"
#include "math/Mtx.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/GameplayOptions.h"
#include "meta_band/MetaPerformer.h"
#include "obj/Data.h"
#include "obj/DataFile.h"
#include "obj/DataFunc.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rndobj/Anim.h"
#include "rndobj/Group.h"
#include "rndobj/Mesh.h"
#include "synth/MicManagerInterface.h"
#include "utl/Std.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"
#include "utl/TimeConversion.h"
#include <utility>

int maxPlatesQueued;
int maxVertsInPlate;
int maxFacesInPlate;
int maxNumLyricPlates;
bool dumpLyricShifts;
bool sDumpLyricPlates;
bool sDumpPlateStates;
bool gDebugSpew;

MicClientID sNullMicClientID(-1, -1);

inline TambourineGemPool::TambourineGemPool() {
    for (int i = 0; i < 25; i++) {
        mFreeGems.push_back(new TambourineGem());
    }
    mTambourineManager = 0;
}

inline TambourineGemPool::~TambourineGemPool() {
    FreeUsedGems();
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
        if (mVocalStyleOverride == kVocalStyleScrolling && cur->Deploy()) {
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
    : Track(u), unk68(0), mVocalStyleOverride(kVocalStyleScrolling), unk70(2),
      unk78(24.0f), unk7c(0), mDir(this), mPlayer(this), mPhraseStartMs(0),
      mPhraseEndMs(0), mNextPhraseEndMs(0), unkf4(0), unkf8(0), unkfc(0), unk100(0),
      unk104(1), unk108(0), unk128(0), unk19c(0), unk1c8(this), mTambourineGemPool(0),
      mCharOptMicID(-1), unk208(60), unk20c(0), unk210(0), unk23c(0.1f), unk240(0.1f),
      unk294(0), unk298(0), unk2a4(-1.0f), unk2a8(0), unk2ac(0), unk2b0(0),
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
        mAlternateNoteList[i] = 0;
    }
    InitPlatePool();
}

VocalTrack::~VocalTrack() {
    RELEASE(mTambourineGemPool);
    ClearLyrics();
    ClearMarkers();
    ClearAllTubePlates();
    DeleteAll(mMeshPool);
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
    if (mPlayer)
        mTambourineGemPool->SetTambourineManager(&mPlayer->mTambourineManager);
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

bool VocalTrack::ShowPitchCorrectionNotice() const {
    if (mPlayer)
        return mPlayer->ShowPitchCorrectionNotice();
    else
        return false;
}

void VocalTrack::ConfigNoteTube(bool pitched, int pts, int part, bool b4, float alpha) {
    mNoteTube->SetPitched(pitched);
    mNoteTube->SetNumPoints(pts);
    mNoteTube->SetPart(part);
    mNoteTube->unk_0x24 = b4;
    mNoteTube->SetAlpha(alpha);
    if (pitched) {
        switch (part) {
        case 1:
            mNoteTube->SetBackMat(mDir->mHarm1BackMat);
            mNoteTube->SetBackParent(mDir->mTubeBack1Grp);
            mNoteTube->SetFrontMat(mDir->mHarm1FrontMat);
            mNoteTube->SetFrontParent(mDir->mTubeFront1Grp);
            break;
        case 2:
            mNoteTube->SetBackMat(mDir->mHarm2BackMat);
            mNoteTube->SetBackParent(mDir->mTubeBack2Grp);
            mNoteTube->SetFrontMat(mDir->mHarm2FrontMat);
            mNoteTube->SetFrontParent(mDir->mTubeFront2Grp);
            break;
        default:
            mNoteTube->SetBackMat(mDir->mLeadBackMat);
            mNoteTube->SetBackParent(mDir->mTubeBack0Grp);
            mNoteTube->SetFrontMat(mDir->mLeadFrontMat);
            mNoteTube->SetFrontParent(mDir->mTubeFront0Grp);
            break;
        }
    } else if (!b4) {
        mNoteTube->SetFrontMat(nullptr);
        mNoteTube->SetFrontParent(nullptr);
        switch (part) {
        case 1:
            mNoteTube->SetBackMat(mDir->mHarm1PhonemeMat);
            mNoteTube->SetBackParent(mDir->mTubePhoneme1Grp);
            break;
        case 2:
            mNoteTube->SetBackMat(mDir->mHarm2PhonemeMat);
            mNoteTube->SetBackParent(mDir->mTubePhoneme2Grp);
            break;
        default:
            mNoteTube->SetBackMat(mDir->mLeadPhonemeMat);
            mNoteTube->SetBackParent(mDir->mTubePhoneme0Grp);
            break;
        }
    } else {
        MILO_ASSERT(part < 3, 0x30D);
        mNoteTube->SetFrontMat(nullptr);
        mNoteTube->SetFrontParent(nullptr);
        mNoteTube->SetBackParent(nullptr);
        if (part != 0)
            mNoteTube->SetBackMat(mDir->mHarmDeployMat);
        else
            mNoteTube->SetBackMat(mDir->mLeadDeployMat);
    }
}

LyricPlate *VocalTrack::GetNextLyricPlate(std::deque<LyricPlate *> &plates, bool b2) {
    FOREACH (it, plates) {
        if ((*it)->Empty())
            return *it;
    }
    RndText *text = b2 ? mDir->mLeadText : mDir->mHarmText;
    RndText *phonemeText = b2 ? mDir->mLeadPhonemeText : mDir->mHarmPhonemeText;
    RndText *newText = NewRndCopy(text);
    plates.push_back(new LyricPlate(newText, text, phonemeText));
    if (sDumpLyricPlates) {
        MILO_LOG("creating new %s lyric plate\n", b2 ? "lead" : "harmony");
        DumpLyricPlates(plates, b2);
    }
    int numplates = plates.size();
    if (maxNumLyricPlates < numplates) {
        maxNumLyricPlates = numplates;
        if (sDumpLyricPlates) {
            MILO_LOG("Max Lyric Plates: %d\n", maxNumLyricPlates);
        }
    }
    return plates.back();
}

Lyric *VocalTrack::GetLastLyric(std::deque<LyricPlate *> &plates) {
    Lyric *last = nullptr;
    FOREACH (it, plates) {
        if ((*it)->Empty())
            break;
        last = (*it)->LatestLyric();
    }
    return last;
}

Lyric *VocalTrack::GetLastBakedLyric(std::deque<LyricPlate *> &plates) {
    Lyric *last = nullptr;
    FOREACH (it, plates) {
        if (!(*it)->Baked())
            break;
        last = (*it)->LatestLyric();
    }
    return last;
}

RndMesh *VocalTrack::CreateMarker(Symbol s1, float f2, bool warn) {
    RndMesh *mesh = nullptr;
    if (mMeshPool.empty()) {
        mesh = Hmx::Object::New<RndMesh>();
        unk19c++;
        if (warn) {
            MILO_WARN(
                "VocalTrack::CreateMarker() added new %s mesh at run-time (total %d); please alert HUD/Track owner",
                s1.mStr,
                unk19c
            );
        }
    } else {
        mesh = mMeshPool.back();
        mMeshPool.pop_back();
    }
    RndMesh *found = mDir->Find<RndMesh>(s1.mStr, true);
    mesh->SetGeomOwner(found->GeomOwner());
    mesh->SetMat(found->Mat());
    mesh->SetShowing(true);
    mesh->SetTransParent(found->TransParent(), false);
    mesh->SetLocalXfm(found->mLocalXfm);
    mesh->SetTransParent(mDir->mScroller, true);
    Vector3 v18 = mesh->mLocalXfm.v;
    v18.x = unk78 * (f2 / unk74);
    mesh->SetLocalPos(v18);
    unk1c8->AddObject(mesh);
    unk1a0.push_back(std::make_pair(mesh, f2));
    return mesh;
}

void VocalTrack::ReturnFirstMarker() {
    RndMesh *mesh = unk1a0.front().first;
    MILO_ASSERT(mesh, 0x393);
    MILO_ASSERT(mesh->GeomOwner() != mesh, 0x394);
    mMeshPool.push_back(mesh);
    unk1c8->RemoveObject(mesh);
    unk1a0.pop_front();
}

void VocalTrack::SetDir(RndDir *dir) {
    mDir = dynamic_cast<VocalTrackDir *>(dir);
    Init();
}

bool VocalTrack::WantBeatLines(int i1) {
    if (mPlayer->IsNet())
        return false;
    else {
        VocalNoteList *notes = GetVocalNoteList(0);
        std::vector<VocalPhrase> &phrases = notes->mPhrases;
        FOREACH (it, phrases) {
            if (i1 >= it->unk8 && (i1 <= it->unk8 + it->unkc)) {
                return it->unk2d;
            }
        }
        return false;
    }
}

int VocalTrack::NumSingers() const {
    if (mPlayer)
        return mPlayer->NumSingers();
    else
        return 0;
}

bool VocalTrack::UseVocalHarmony() {
    if (mPlayer)
        return mPlayer->NumParts() > 1;
    else
        return 0;
}

void VocalTrack::SetVocalStyle(VocalStyle style) {
    if (HasNetPlayer())
        unk2e5 = true;
    else
        unk2e5 = false;
    if (mVocalStyleOverride != style) {
        mVocalStyleOverride = style;
        UpdateVocalStyle();
        TrackPanel *panel = GetTrackPanel();
        panel->unk5f = false;
    }
}

bool VocalTrack::IsScrolling() const {
    if (unk70 == 2)
        return mVocalStyleOverride == kVocalStyleScrolling;
    else
        return unk70 == 1;
}

void VocalTrack::UpdateVocalStyle() {
    std::vector<Player *> &players = TheGame->GetActivePlayers();
    if (mPlayer && mPlayer->IsLocal()) {
        for (int i = 0; i < players.size(); i++) {
            Player *cur = players[i];
            if (cur && cur->GetTrackType() == kTrackVocals) {
                if (cur->GetTrackNum() != mTrackConfig.TrackNum() && cur->IsNet()) {
                    VocalTrack *track =
                        dynamic_cast<VocalTrack *>(cur->GetUser()->GetTrack());
                    if (track)
                        track->SetVocalStyle(mVocalStyleOverride);
                }
            }
        }
    }
    if (mDir) {
        if (mPlayer) {
            EnabledState estate = mPlayer->GetEnabledState();
            if (estate == kPlayerDisabled || estate == kPlayerDisconnected)
                return;
        }
        mDir->UpdateConfiguration();
        unk78 = mDir->mTrackRightX - mDir->mTrackLeftX;
        BandSongMetadata *data = (BandSongMetadata *)TheSongMgr->Data(
            TheSongMgr->GetSongIDFromShortName(MetaPerformer::Current()->Song(), true)
        );
        unk74 = data->ScrollSpeed() * (unk78 / 16.8f);
        mDir->Find<RndAnimatable>("tambourine_preview.anim", true)->SetFrame(0, 1);
        RebuildHUD();
    }
}

void VocalTrack::RebuildHUD() {
    for (int i = 0; i < 3; i++) {
        mNextScrollNote[i] = 0;
    }
    for (int i = 0; i < 2; i++) {
        mNextDeployZone[i] = 0;
    }
    for (int i = 0; i < 2; i++) {
        mCurLyricPhrase[i] = 0;
    }

    unk108 = 0;
    unk104 = 1;
    unk100 = 0;
    unkf4 = 0;
    unkf8 = 0;
    unkfc = 0;
    unk23c = mStaticDeployMarginX;
    unk240 = mStaticDeployMarginX;
    mLeadLyricShifts.clear();
    mHarmonyLyricShifts.clear();
    mDir->mLeadLyricScroller->DirtyLocalXfm().v.x = unk23c;
    mDir->mHarmonyLyricScroller->DirtyLocalXfm().v.x = unk240;
    unk2ac = unk23c;
    unk2b0 = unk240;
    unk294 = 0;
    unk298 = 0;
    ClearLyrics();
    ClearMarkers();
    ResetAllTubePlates();
    mTambourineGemPool->FreeUsedGems();
}

float VocalTrack::GetBottomDisplayPitch() const {
    if (mDir)
        return mDir->mLastMin;
    else
        return 0;
}

float VocalTrack::GetTopDisplayPitch() const {
    if (mDir)
        return mDir->mLastMax;
    else
        return 0;
}

VocalNoteList *VocalTrack::GetVocalNoteList(int part) {
    if (mAlternateNoteList[part])
        return mAlternateNoteList[part];
    else
        return TheSongDB->GetVocalNoteList(part);
}

void VocalTrack::SetAlternateNoteList(int part, VocalNoteList *notes) {
    MILO_ASSERT_RANGE(part, 0, 3, 0x53E);
    mAlternateNoteList[part] = notes;
}

void VocalTrack::HideCoda() {
    unk2ec = false;
    mDir->mBREGrp->SetShowing(false);
    mDir->mLeadBREGrp->SetShowing(false);
    mDir->mHarmonyBREGrp->SetShowing(false);
}

void VocalTrack::DumpLyricPlates(std::deque<LyricPlate *> &plates, bool lead) {
    MILO_LOG("Dumping %s lyric plates\n", lead ? "lead" : "harmony");
    int idx = 0;
    FOREACH (it, plates) {
        LyricPlate *cur = *it;
        MILO_LOG(
            "[%d] %x (%.2f - %.2f) %s\n",
            idx,
            cur,
            !cur->mSyllables.empty() ? (cur->mSyllables.front()->mHighlightMs) / 1000.0f
                                     : -1.0f,
            cur->mInvalidateMs / 1000.0f,
            cur->mText->mText.c_str()
        );
        if (cur->Empty()) {
            MILO_LOG("\t<empty>\n");
        } else {
            for (int i = 0; i < cur->mSyllables.size(); i++) {
                Lyric *curLyric = cur->mSyllables[i];
                MILO_LOG("\t[%d] %x", i, curLyric);
                if (curLyric) {
                    MILO_LOG(
                        " %s x:%.2f (%.2f - %.2f)\n",
                        curLyric->mText.c_str(),
                        curLyric->unk48.x,
                        curLyric->mActiveMs / 1000.0f,
                        curLyric->mEndMs / 1000.0f
                    );
                } else
                    MILO_LOG("\n");
            }
        }
        idx++;
    }
    MILO_LOG("\n");
}

void VocalTrack::Poll(float f1) {
    bool gamebool = TheGame->InTrainer();
    if (f1 < unk2a4 && !gamebool) {
        RebuildHUD();
    }
    float f6 = unk78 * -(f1 / unk74);
    mDir->mScroller->SetLocalPos(Vector3(f6, 0, 0));
    unk2a8 = f6 + mDir->mNowBarX;
    Track::Poll(f1);
    mDir->UpdatePartIsolation();
    mDir->SortArrowFx();
    UpdateScrolling(f1);
    UpdateTambourineGems();
    if (f1 > 0) {
        PollLyricAnimations(mLyricsLead, f1, true);
        PollLyricAnimations(mLyricsHarmony, f1, false);
    }
    PollKaraoke(f1);
    if (unk68) {
        const char *txt = MakeString("current: %i\n", mPlayer->PhraseScore());
        mDir->Find<RndText>("debug_score_current.txt", true)->SetText(txt);
    }
    if (!gamebool)
        unk2a4 = f1;
    if (mPlayer && unk2ec) {
        if (!mPlayer->CanDeployCoda()) {
            HideCoda();
        }
    }
}

void VocalTrack::PollKaraoke(float f1) {
    if (mPlayer) {
        int i1 = mPlayer->NumSingers();
        if (!unk2e5) {
            StartUpdateArrows();
            for (int i = 0; i < i1; i++) {
                UpdatePitchArrow(f1, i);
            }
            UpdateUnusedArrows();
        }
        float f7 = 0;
        for (int i = i1; i < 3; i++) {
            float clamped = Clamp<float>(0, 1, mPlayer->FramePhraseMeterFrac(i));
            int rating = mPlayer->CalculatePhraseRating(clamped);
            mDir->mStreakMeter->SetPartPct(i, clamped, rating <= 4);
            if (clamped > f7)
                f7 = clamped;
        }
        mDir->SetStreakPct(f7);
    }
}

void UpdateSyllableText(String &str, bool b2, bool &bref) {
    bref = false;
    if (b2 && !str.empty() && str.rindex(-1) == '-') {
        if (str.length() > 1) {
            str = str.substr(0, str.length() - 1);
            return;
        }
        str = "";
        return;
    }
    if (!str.empty() && str.rindex(-1) == '=') {
        str.rindex(-1) = '-';
        if (!b2)
            str += ' ';
    } else {
        str += ' ';
        if (b2)
            str += ' ';
        bref = true;
    }
}

void PrintLyricOneLine(const Lyric &lyric) {
    MILO_LOG("\t%3.2f\t(%6.2fms)\t", lyric.unk48.x, lyric.mActiveMs);
    if (lyric.mDeployIdx > -1) {
        MILO_LOG("| ");
    }
    MILO_LOG("\"%s\"", lyric.mText.c_str());
    if (lyric.mChunkEnd) {
        MILO_LOG(" |");
    }
    MILO_LOG("\n");
}

bool VocalTrack::CheckDeploySections(
    Lyric *l1,
    float f2,
    int &i3,
    const std::vector<std::pair<float, float> > &pairs,
    bool b5,
    Lyric *l2,
    float &fref
) {
    bool ret = false;
    while (i3 < pairs.size() && pairs[i3].first < f2) {
        l1->SetAfterDeploy(i3);
        if (b5) {
            fref += mStaticDeployZoneXSize;
            if (l2)
                l2->SetChunkEnd(true);
        }
        ret = true;
        i3++;
    }
    return ret;
}

bool VocalTrack::IdenticalLyric(const VocalNote &n1, const VocalNote &n2) const {
    float f6 = Abs(n1.GetMs() - n2.GetMs());
    if (f6 == 0)
        return true;
    else if (f6 > mLyricOverlapWindowMs)
        return false;
    else if (n1.mText.length() != n2.mText.length())
        return false;
    else if (n1.mText == n2.mText)
        return true;
    else {
        String t1 = n1.mText;
        String t2 = n2.mText;
        t1.ToLower();
        t2.ToLower();
        return t1 == t2;
    }
}

void VocalTrack::BuildStaticDeployZone(
    int i1,
    const std::pair<float, float> &fpair,
    float f3,
    float &fref,
    std::deque<LyricShift> &shifts
) {
    ConfigNoteTube(false, 2, std::min(i1, 1), true, 1);
    HookupTubePlates(mNoteTube);
    float f10 = fref + mStaticDeployBufferX;
    fref = (f10 + mStaticDeployZoneXSize) - mStaticDeployMarginX;
    shifts.push_back(LyricShift(fpair.second, -fref));
    if (f3 != -1.0f) {
        float max = std::max<float>(mLyricShiftMs + fpair.second, f3);
        shifts.push_back(
            LyricShift(max, mStaticDeployMarginX + (-fref - mStaticDeployBufferX))
        );
    }
    bool i6 = TheSongDB->IsInCoda(MsToTickInt(fpair.first));
    bool i8 = i6 - 1 + !i6;
    float f1;
    RndGroup *u4;
    float f2;
    if (i1 == 0) {
        f1 = mDir->mTrackBottomZ + mDir->mPitchBottomZ;
        u4 = i6 == i8 ? mDir->mLeadLyricScrollGroup : mDir->mLeadBREGrp;
        f2 = mDir->mLeadLyricHeight;
    } else {
        f1 = mDir->mTrackTopZ + mDir->mPitchTopZ;
        u4 = i6 == i8 ? mDir->mHarmonyLyricScrollGroup : mDir->mHarmonyBREGrp;
        f2 = mDir->mHarmLyricHeight;
    }
    mNoteTube->SetPointPos(0, Vector3(0, 0, f1 / 2.0f));
    mNoteTube->SetPointPos(1, Vector3(fref - f10, 0, f1 / 2.0f));
    mNoteTube->unk_0x30 = f2 / 2.0f;
    mNoteTube->SetBackParent(u4);
    mNoteTube->SetXPos(f10);
    mNoteTube->CreateMeshes();
    mNoteTube->SetDeployTiming(fpair.first, fpair.second);
    mNoteTube->BakePlates();
    if (gDebugSpew)
        MILO_LOG("new final deploy section for part %d\n", i1);
}

void VocalTrack::ProcessStaticLyrics(
    bool b1,
    Lyric *l2,
    float &f3,
    float &f4,
    Lyric *&l5,
    Lyric *&l6,
    float &f7,
    bool b8,
    LyricPlate *lp9
) {
    if (b1) {
        if (b8) {
            f3 = f4;
            f7 = f4;
            l5 = nullptr;
            l6 = nullptr;
        }
        float d4 = mDir->unk42c;
        float f1 = d4 - mDir->mNowBarX;
        lp9->EstimateLyricWidth(l2);
        float f2 = f4;
        f4 += d4;
        f2 = f4 - f3;
        if (l5 && !l6)
            l6 = l2;
        if (l5 && f1 < f2) {
            l5->SetChunkEnd(true);
            l5 = nullptr;
            f2 = f7;
            f3 = f2;
            f2 = f4 - f2;
            l6->SetAfterMidPhraseLyricShift(true);
            l6 = nullptr;
        }
        if (!l5 && (f1 / 2.0f < f2) && l2->mWordEnd) {
            l5 = l2;
            f7 = f4;
        }
    }
}

void VocalTrack::Restart(VocalPlayer *player, float f1, float f2) {
    unk2a4 = -1.0f;
    mPlayer = player;
    mPhraseStartMs = 0;
    mPhraseEndMs = 0;
    mNextPhraseEndMs = 0;
    for (int i = 0; i < 3; i++)
        mNextScrollNote[i] = 0;
    for (int i = 0; i < 2; i++)
        mNextDeployZone[i] = 0;
    for (int i = 0; i < 2; i++)
        mCurLyricPhrase[i] = 0;
    unk108 = 0;
    unk104 = 1;
    unk100 = 0;
    unkf4 = 0;
    unkf8 = 0;
    unkfc = 0;
    mLeadLyricShifts.clear();
    mHarmonyLyricShifts.clear();
    unk23c = mStaticDeployMarginX;
    unk240 = unk23c;
    mDir->mLeadLyricScroller->DirtyLocalXfm().v.x = unk23c;
    mDir->mHarmonyLyricScroller->DirtyLocalXfm().v.x = unk240;
    unk2ac = unk23c;
    unk2b0 = unk240;
    mTambourineGemPool->FreeUsedGems();
    mTambourineGemPool->SetTambourineManager(&mPlayer->mTambourineManager);
    mDir->mBREGrp->SetShowing(true);
    mDir->mLeadBREGrp->SetShowing(true);
    mDir->mHarmonyBREGrp->SetShowing(true);
    unk2ec = true;
    UpdateVocalStyle();
}

void VocalTrack::HitTambourineGem(int) {}

void VocalTrack::MissTambourineGem(int, bool b) {
    if (b)
        mDir->Tambourine(miss);
}

void VocalTrack::OnPhraseComplete(float f1, float f2, int i3) {
    BuildPhrase(f1, f2);
    if (unk68) {
        const char *txt = MakeString("last: %i\n", i3);
        mDir->Find<RndText>("debug_score_current.txt", true)->SetText(txt);
    }
}

void VocalTrack::ClearLyrics() {
    if (sDumpLyricPlates) {
        MILO_WARN("clearing all lyric plates\n");
        DumpLyricPlates(mLyricsLead, true);
        DumpLyricPlates(mLyricsHarmony, false);
    }
    while (mLyricsLead.size() != 0) {
        RELEASE(mLyricsLead.front());
        mLyricsLead.pop_front();
    }
    while (mLyricsHarmony.size() != 0) {
        RELEASE(mLyricsHarmony.front());
        mLyricsHarmony.pop_front();
    }
}

void VocalTrack::BuildPhrase(float f1, float f2) {
    mPhraseStartMs = mPhraseEndMs;
    mPhraseEndMs = f1;
    mNextPhraseEndMs = f2;
}

void VocalTrack::PushGameplayOptions(VocalParam p, int id) {
    Track::PushGameplayOptions(p, id);
    mCharOptParam = p;
    mCharOptMicID = id;
}

DataNode VocalTrack::OnGetDisplayMode(const DataArray *a) {
    if (IsScrolling()) {
        return "scrolling";
    } else
        return "static";
}

DataNode VocalTrack::OnSetDisplayMode(const DataArray *a) {
    if (a->Sym(2) == "static") {
        mVocalStyleOverride = kVocalStyleStatic;
        return a->Node(2);
    } else if (a->Sym(2) == "scrolling") {
        mVocalStyleOverride = kVocalStyleScrolling;
        return a->Node(2);
    } else
        return "unrecognized";
}

void VocalTrack::SetCanDeploy(bool can) {
    if (mDir->mPitchScrollGroup) {
        mDir->mPitchScrollGroup->SetShowing(can);
    }
    if (mDir->mLeadLyricScrollGroup) {
        mDir->mLeadLyricScrollGroup->SetShowing(can);
    }
    if (mDir->mHarmonyLyricScrollGroup) {
        mDir->mHarmonyLyricScrollGroup->SetShowing(can);
    }
}

int VocalTrack::GetNumVocalParts() {
    if (mPlayer)
        return mPlayer->NumParts();
    else {
        MILO_NOTIFY_ONCE("invalid vocal player");
        return 0;
    }
}

BEGIN_HANDLERS(VocalTrack)
    HANDLE_ACTION(initialize, Init())
    HANDLE(set_display_mode, OnSetDisplayMode)
    HANDLE(display_mode, OnGetDisplayMode)
    HANDLE_ACTION(dump_plates, DumpAllPlates())
    HANDLE_EXPR(set_verbose_plates, sDumpPlateStates = _msg->Int(2))
    HANDLE_ACTION(reset_timing_data, ResetTimingData())
    HANDLE_SUPERCLASS(Track)
    HANDLE_CHECK(0xE6C)
END_HANDLERS

VocalTrack::LyricShift::LyricShift(float f1, float f2) : unk0(f2), unk4(f1), unk8(0) {
    if (dumpLyricShifts) {
        MILO_LOG(
            "New LyricShift begin %.2f sec, end %.2f x, fast: %d\n",
            f1 / 1000.0f,
            f2,
            false
        );
    }
}

VocalTrack::LyricShift::LyricShift(float f1, float f2, bool fast)
    : unk0(f2), unk4(f1), unk8(fast) {
    if (dumpLyricShifts) {
        MILO_LOG(
            "New LyricShift begin %.2f sec, end %.2f x, fast: %d\n", f1 / 1000.0f, f2, unk8
        );
    }
}