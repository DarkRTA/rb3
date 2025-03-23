#include "game/Singer.h"
#include "VocalScoreHistory.h"
#include "dsp/VibratoDetector.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/GameMic.h"
#include "game/GameMicManager.h"
#include "game/SongDB.h"
#include "game/VocalPlayer.h"
#include "net/Net.h"
#include "net/NetSession.h"
#include "obj/Data.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/System.h"
#include "synth/MicManagerInterface.h"
#include "synth/VoiceBeat.h"

MicClientID sNullClientID(-1, -1);

Singer::Singer(VocalPlayer *vp, int n)
    : mPlayer(vp), unkc(0), mSingerIndex(n), unk14(0), unk18(0), unk1c(0), mIsSinging(0),
      mDetune(0), unk2c(0), unk30(0), unk38(100.0f), unk3c(0), unk40(0), unk44(0),
      unk48(-1.0f), mScreamEnergyThreshold(0.8f), unk50(500.0f), mFrameMicPitch(0),
      unk60(0), unk64(0), unk6c(0), mFrameAssignedPart(-1), unk74(0), mOctaveOffset(0),
      unk7c(0), unk80(0), unk84(0), unk88(0), unka0(0), unka4(0), unka8(0), mVibrato(0),
      unk244(0), mVibratoFrameBonus(0), unk24c(-1.0f), mAutoplayPart(-1),
      mAutoplayVariationMagnitude(0), mAutoplayOffset(0),
      mTambourineDetector(vp->mTambourineManager, this), unk29c(0), unk2a0(0), unk2a4(0) {
    CreateMicClientID();
    Difficulty diff = mPlayer->GetUser()->GetDifficulty();
    DataArray *cfg = SystemConfig("scoring", "vocals");
    cfg->FindArray("pitch_margin")->Float(diff + 1); // lol what happened to this
    mMaxDetune = cfg->FindFloat("max_detune");
    mScreamEnergyThreshold = cfg->FindFloat("scream_energy_threshold");
    unk38 = cfg->FindFloat("tambourine_deployment_suppress_ms");
    mVibrato = new VibratoDetector(0, 100);
    mTalkyMatcher = new TalkyMatcher();
    for (int i = 0; i < 5; i++)
        mPitchHistory[i] = 0;

    if (n == 0) {
        GameMic *mic = TheGameMicManager->GetMic(mMicClientID);
        if (mic) {
            DataNode node = DataVariable("playback_file");
            if (node.Type() == kDataString) {
                if (strlen(node.Str()) != 0) {
                    mic->SetInputFile(node.Str());
                }
            }
        }
    }
}

Singer::~Singer() {
    RELEASE(mTalkyMatcher);
    RELEASE(mVibrato);
    // RELEASE(unk18);
}

void Singer::PostLoad() {
    int numParts = mPlayer->NumVocalParts();
    for (int i = 0; i < numParts; i++) {
        mScoreHistories.push_back(VocalScoreHistory(i, mSingerIndex));
    }
    mScoreCaches.resize(numParts);
    mResultsData.resize(numParts);
    MILO_ASSERT(mTalkyMatcher, 0xB6);
    mTalkyMatcher->LoadEvents(
        TheSongDB->GetData()->mVocalFeatureVectorTimes,
        TheSongDB->GetData()->mVocalFeatureVectorPeaks
    );
}

void Singer::CreateMicClientID() {
    BandUser *u = mPlayer->GetUser();
    if ((!TheNet.GetNetSession()->HasUser(u) || !u->IsLocal()) && !u->IsNullUser()) {
        mMicClientID = sNullClientID;
    } else {
        mMicClientID = MicClientID(mSingerIndex, -1);
    }
}

GameMic *Singer::GetGameMic() const { return TheGameMicManager->GetMic(mMicClientID); }
MicClientID Singer::GetMicClientID() const { return mMicClientID; }

void Singer::SetMicProcessing(bool b1, bool b2) {
    GameMic *mic = TheGameMicManager->GetMic(mMicClientID);
    if (mic)
        mic->SetEnablePitchDetection(b1);
    if (mTalkyMatcher)
        mTalkyMatcher->SetEnableTalkyMatcher(b2);
}

void Singer::Start() {}
void Singer::StartIntro() {}

void Singer::Restart(bool b1) {
    CancelScream();
    mFrameAssignedPart = -1;
    ClearFreestyleDeployment();
    ClearScoreHistories();
    unk64 = 0;
    unk80 = 0;
    if (!b1) {
        FOREACH (it, mResultsData) {
            it->Reset();
        }
        unk29c = 0;
        unk2a0 = 0;
        unk2a4 = 0;
    }
    mAmbiguousData.clear();
}

void Singer::SetPaused(bool) {}

void Singer::Jump(float, bool) {
    CancelScream();
    mFrameAssignedPart = -1;
    ClearFreestyleDeployment();
    ClearScoreHistories();
    mAmbiguousData.clear();
}

void Singer::Rollback(float, float) {
    CancelScream();
    ClearFreestyleDeployment();
    mAmbiguousData.clear();
}

void Singer::ProcessTalkyData() {
    MILO_ASSERT(mTalkyMatcher, 0x2DC);
    GameMic *mic = GetGameMic();
    if (!mic)
        mTalkyMatcher->Reset();
    else {
        float secs = TheTaskMgr.Seconds(TaskMgr::kRealTime);
        const short *s = nullptr;
        int i28 = 0;
        mic->AccessContinuousSamples(s, i28);
        mTalkyMatcher->Analyze(s, i28, secs * 1000.0f);
    }
}

void Singer::DetectScream(float f1, float f2, float f3) {
    MILO_ASSERT(mPlayer->IsLocal(), 0x2F6);
    if (f3 >= mScreamEnergyThreshold) {
        if (unk48 < 0) {
            unk48 = f1;
        } else if (f1 - unk48 > unk50 && mPlayer->unk268 && !unk80) {
            unk80 = true;
            mPlayer->HitCoda();
        }
    } else
        CancelScream();
}

void Singer::CancelScream() { unk48 = -1.0f; }

void Singer::SetIsSinging(bool b1) { mIsSinging = b1; }
void Singer::Detune(float f1) { mDetune = f1; }

void Singer::SetFrameMicPitch(float f1) { mFrameMicPitch = f1; }
void Singer::EnableController() {}
void Singer::DisableController() {}

void Singer::SetOctaveOffset(int i1) {
    if (i1 != mOctaveOffset)
        mOctaveOffset = i1;
}

void Singer::AppendToScoreHistory(float f1, int i2, float f3, int i4) {
    VocalScoreHistory &history = mScoreHistories[i2];
    history.AddScore(f1, f3);
    history.SetOctaveOffset(i4);
}

float Singer::GetHistoricalScore(float f1, int i2) const {
    return mScoreHistories[i2].CalculateSum(f1);
}

VocalScoreHistory &Singer::AccessScoreHistory(int idx) { return mScoreHistories[idx]; }
VocalScoreCache &Singer::AccessScoreCache(int idx) { return mScoreCaches[idx]; }
const VocalScoreCache &Singer::AccessScoreCache(int idx) const {
    return mScoreCaches[idx];
}

void Singer::AllScoresAreIn(const std::vector<int> &) {
    MILO_ASSERT(mResultsData.size() == mScoreCaches.size(), 0x4B6);
}

void Singer::NoteTambourineSwing(float f1) {
    ClearFreestyleDeployment();
    unk3c = f1 + unk38;
}

void Singer::ClearFreestyleDeployment() {
    unk3c = 0;
    unk40 = 0;
    unk44 = 0;
}

void Singer::SetAutoplayToPart(int part) { mAutoplayPart = part; }
int Singer::GetAutoplayToPart() const { return mAutoplayPart; }
void Singer::SetAutoplayVariationMagnitude(float f1) { mAutoplayVariationMagnitude = f1; }
float Singer::GetAutoplayVariationMagnitude() const {
    return mAutoplayVariationMagnitude;
}
void Singer::SetAutoplayOffset(float f1) { mAutoplayOffset = f1; }
float Singer::GetAutoplayOffset() const { return mAutoplayOffset; }

void Singer::ClearScoreHistories() {
    FOREACH (it, mScoreHistories) {
        it->Reset();
    }
}