#include "game/VocalPlayer.h"
#include "bandobj/BandTrack.h"
#include "bandtrack/VocalTrack.h"
#include "beatmatch/BeatMaster.h"
#include "beatmatch/MasterAudio.h"
#include "decomp.h"
#include "game/Game.h"
#include "game/GameMic.h"
#include "game/GameMicManager.h"
#include "game/GamePanel.h"
#include "game/Performer.h"
#include "game/Scoring.h"
#include "game/SongDB.h"
#include "game/VocalPart.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "midi/MidiParser.h"
#include "net/NetSession.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/System.h"
#include "rndobj/Overlay.h"
#include "synth/MicManagerInterface.h"
#include "utl/Messages3.h"
#include "utl/Messages4.h"
#include "utl/TextFileStream.h"
#include "world/Dir.h"
#include "utl/Messages.h"

MicClientID sNullMicClientID;

VocalPlayer::VocalPlayer(
    BandUser *user, BeatMaster *bmaster, Band *band, int tracknum, Performer *perf, int i7
)
    : Player(user, band, tracknum, bmaster), mBandPerformer(perf), unk2d0(0), mTrack(0),
      unk2d8(0), mVocalPartBias(1.25f), unk2e8(0), unk2ec(0), mNextPacketSendTime(0),
      unk300(0), unk304(0), mTrackWrappingMargin(0), mLastDeploymentSinger(-1),
      mPhraseValue(0), mPartScoreMultipliers(0), mRatingThresholds(0),
      mNonpitchStickiness(0.6f), mCouldChat(0), mCodaEndMs(0), unk344(0),
      mTuningOffset(0), unk34c(-1.0f), unk368(0), unk36c(0), unk370(0),
      mPhraseActivePartCount(0), mPhrasePercentageTotal(0), mPhrasePercentageCount(0),
      mOverlay(0), unk384(0), mScoringEnabled(1), mTambourineManager(*this),
      mSectionStartPhrasePercentageTotal(0), mSectionStartPhrasePercentageCount(0),
      mSectionStartScore(0), mFrameSpewData(0), mFrameSpewStream(0) {
    BandSongMetadata *data = (BandSongMetadata *)TheSongMgr->Data(
        TheSongMgr->GetSongIDFromShortName(MetaPerformer::Current()->Song(), true)
    );
    mTuningOffset = data->TuningOffset() / 100.0f;
    for (int i = 0; i < i7; i++) {
        mSingers.push_back(new Singer(this, i));
    }
    SetTypeDef(SystemConfig("player", "handlers"));
    SetDifficultyVariables(mUser->GetDifficulty());
    DataArray *cfg = SystemConfig("scoring", "vocals");
    mTrackWrappingMargin = cfg->FindFloat("track_wrapping_margin");
    mFreestyleDeploymentTimes =
        cfg->FindArray("freestyle_deployment_time", true)->Array(1);
    mFreestyleMinDurations = cfg->FindArray("freestyle_min_duration", true)->Array(1);
    mMaxDetune = cfg->FindFloat("max_detune");
    mPacketPeriodMs = cfg->FindFloat("packet_period");
    mPartScoreMultipliers = cfg->FindArray("part_score_multiplier", true);
    mRatingThresholds = cfg->FindArray("rating_thresholds", true);
    mNonpitchStickiness = cfg->FindFloat("nonpitch_stickiness");
    JoypadSubscribe(this);
    TheGameMicManager->AddSink(this, GameMicsChangedMsg::Type());
    RememberCurrentMics();
    mOverlay = RndOverlay::Find("vocalplayer", true);
    mOverlay->SetCallback(this);
}

VocalPlayer::~VocalPlayer() {
    if (mOverlay)
        mOverlay->SetCallback(nullptr);
    TheGameMicManager->RemoveSink(this);
    FOREACH (it, mVocalParts) {
        RELEASE(*it);
    }
    FOREACH (it, mSingers) {
        RELEASE(*it);
    }
    if (mUser->IsLocal()) {
        JoypadKeepAlive(mUser->GetLocalUser()->GetPadNum(), false);
    }
    JoypadUnsubscribe(this);
}

void VocalPlayer::PostDynamicAdd() {
    Player::PostDynamicAdd();
    mBeatMaster->GetAudio()->ResetTrack(mTrackNum, true);
    mTambourineManager.PostDynamicAdd();
    mTambourineManager.SetBank(TheGamePanel->mVocalPercussionBank);
    TheGameMicManager->SetPlayback(true);
    if (mUser->IsLocal()) {
        JoypadKeepAlive(mUser->GetLocalUser()->GetPadNum(), true);
    }
}

void VocalPlayer::Leave() {
    if (mTrackNum != -1) {
        MasterAudio *audio = mBeatMaster->GetAudio();
        audio->ResetTrack(mTrackNum, false);
        audio->SetVocalState(true);
        audio->SetVocalDuckFader(0);
    }
    TheGameMicManager->SetPlayback(false);
    if (mUser->IsLocal()) {
        JoypadKeepAlive(mUser->GetLocalUser()->GetPadNum(), false);
    }
}

void VocalPlayer::SetDifficultyVariables(int diff) {
    DataArray *voxCfg = SystemConfig("scoring", "vocals");
    mPitchMaximumDistance = voxCfg->FindArray("pitch_margin", true)->Float(diff + 1);
    mSynapseProximitySolo =
        voxCfg->FindArray("synapse_proximity_solo", true)->Float(diff + 1);
    mSynapseFocusSolo = voxCfg->FindArray("synapse_focus_solo", true)->Float(diff + 1);
    mSynapseProximityHarmony =
        voxCfg->FindArray("synapse_proximity_harm", true)->Float(diff + 1);
    mSynapseFocusHarmony = voxCfg->FindArray("synapse_focus_harm", true)->Float(diff + 1);
    mPhraseValue = voxCfg->FindArray("phrase_value", true)->Int(diff + 1);
    FOREACH (it, mVocalParts) {
        (*it)->SetDifficultyVariables(diff);
    }
}

void VocalPlayer::ConfigureBehavior() {
    mBehavior->SetStreakType(mUser->GetTrackSym());
    mBehavior->SetMaxMultiplier(4);
}

void VocalPlayer::SetTrack(int trk) {
    if (mTrackNum != trk) {
        MILO_ASSERT(mTrackNum == -1, 0x128);
        mBeatMaster->GetAudio()->SetTrack(GetUserGuid(), trk);
        mTrackNum = trk;
        bool b1 = false;
        if (IsNet() || unk2d0)
            b1 = true;
        if (b1) {
            mBeatMaster->GetAudio()->SetNonmutable(trk);
        }
    }
}

void VocalPlayer::PostLoad(bool b1) {
    ObjectDir::sMainDir->Find<MidiParser>("play_tambourine", true)->AddSink(this);
    int num = TheSongDB->GetVocalNoteListCount();
    mStats.SetVocalSingerAndPartCounts(mSingers.size(), num);
    for (int i = 0; i < num; i++) {
        mVocalParts.push_back(new VocalPart(this, i));
        mStats.mVocalPartPercentages[i] = 0;
    }
    FOREACH (it, mVocalParts) {
        (*it)->PostLoad();
    }
    FOREACH (it, mSingers) {
        (*it)->PostLoad();
    }
    BuildPhrases(b1);
    DataNode spew = DataVariable("vocal_frame_spew");
    if (spew.Int())
        ToggleFrameSpew();
}

void VocalPlayer::Start() {
    mTambourineManager.Start();
    FOREACH (it, mVocalParts) {
        (*it)->Start();
    }
    FOREACH (it, mSingers) {
        (*it)->Start();
    }
    SetAutoplay(mUser->mAutoplay);
    BandTrack *track = GetBandTrack();
    if (track) {
        track->ShowOverdriveMeter(
            !mUser->IsNullUser() && TheGame->AllowOverdrivePhrases()
        );
    }
}

void VocalPlayer::StartIntro() {
    Player::StartIntro();
    TheGameMicManager->SetPlayback(true);
    FOREACH (it, mVocalParts) {
        (*it)->StartIntro();
    }
    FOREACH (it, mSingers) {
        (*it)->StartIntro();
    }
}

void VocalPlayer::Restart(bool b1) {
    if (!mVocalParts.empty()) {
        FOREACH (it, mVocalParts) {
            (*it)->Restart(b1);
        }
        FOREACH (it, mSingers) {
            (*it)->Restart(b1);
        }
        mNextPacketSendTime = 0;
        mLastDeploymentSinger = -1;
        mBeatMaster->GetAudio()->SetVocalFailFader(0);
        mBeatMaster->GetAudio()->SetVocalDuckFader(0);
        if (mTrack) {
            mCouldChat = !TheNetSession->IsLocal() && PressingToTalk();
            SendCanChat(mCouldChat);
        }
        Player::Restart(b1);
        mPhraseActivePartCount = 0;
        if (!b1) {
            mStats.SetVocalSingerAndPartCounts(mSingers.size(), mVocalParts.size());
            mPhrasePercentageCount = 0;
            mPhrasePercentageTotal = 0;
        }
        mTambourineManager.Restart();
        mSectionStartPhrasePercentageTotal = 0;
        mSectionStartPhrasePercentageCount = 0;
        mSectionStartScore = 0;
        if (mUser->IsLocal()) {
            JoypadKeepAlive(mUser->GetLocalUser()->GetPadNum(), true);
        }
        RememberCurrentMics();
    }
}

void VocalPlayer::SetPaused(bool b1) {
    mTambourineManager.SetPaused(b1);
    FOREACH (it, mVocalParts) {
        (*it)->SetPaused(b1);
    }
    FOREACH (it, mSingers) {
        (*it)->SetPaused(b1);
    }
    if (mUser->IsLocal()) {
        JoypadKeepAlive(mUser->GetLocalUser()->GetPadNum(), !b1);
    }
}

void VocalPlayer::Jump(float f1, bool b2) {
    if (!mVocalParts.empty()) {
        FOREACH (it, mVocalParts) {
            (*it)->Jump(f1, b2);
        }
        FOREACH (it, mSingers) {
            (*it)->Jump(f1, b2);
        }
        mNextPacketSendTime = 0;
        mLastDeploymentSinger = -1;
        mPhraseActivePartCount = 0;
        mPhrasePercentageTotal = 0;
        mPhrasePercentageCount = 0;
        mTambourineManager.Jump(f1);
        mTambourineManager.SetTambourine(mVocalParts.front()->InTambourinePhrase());
        if (mTrack)
            mTrack->RebuildHUD();
    }
}

float VocalPlayer::GetNotesHitFraction(bool *bptr) const {
    if (bptr) {
        *bptr = mPhrasePercentageCount > 0;
    }
    if (mPhrasePercentageCount == 0)
        return 0;
    else
        return mPhrasePercentageTotal / (float)mPhrasePercentageCount;
}

Symbol VocalPlayer::GetStarRating() const {
    return TheScoring->GetStarRating(GetNumStars());
}

int VocalPlayer::LocalDeployBandEnergy() {
    int ret = Player::LocalDeployBandEnergy();
    FOREACH (it, mVocalParts) {
        (*it)->LocalDeployBandEnergy();
    }
    return ret;
}

void VocalPlayer::RemoteUpdateCrowd(float f1) {
    Performer::RemoteUpdateCrowd(f1);
    mBeatMaster->GetAudio()->SetVocalDuckFader(RemoteVocalVolume());
}

float VocalPlayer::RemoteVocalVolume() const {
    float ret = mCrowd->GetDisplayValue();
    if (ret > 0.33f)
        return 0;
    else if (ret <= 0) {
        return 1.0f;
    } else
        return 1.0f - ret / 0.33f;
}

void VocalPlayer::LocalEndgameEnergy(int x) {
    if (TheWorld) {
        if (x == 0) {
            TheWorld->Handle(endgame_vocals_none_msg, false);
        } else if (x == 1) {
            TheWorld->Handle(endgame_vocals_low_msg, false);
        } else if (x == 2) {
            TheWorld->Handle(endgame_vocals_medium_msg, false);
        } else
            TheWorld->Handle(endgame_vocals_high_msg, false);
    }
}

void VocalPlayer::SendCanChat(bool b1) {
    if (mTrack) {
        mTrack->GetVocalTrackDir()->CanChat(b1);
    }
}

void VocalPlayer::SendVocalState(float f1) {
    MILO_ASSERT(IsLocal(), 0x62C);
    if (f1 < mNextPacketSendTime)
        return;
    std::vector<float> framePercs(mVocalParts.size());
    FOREACH (it, mVocalParts) {
        VocalPart *cur = *it;
        float fPercentage = cur->FramePhraseMeterFrac();
        MILO_ASSERT_RANGE_EQ(fPercentage, 0.0f, 1.0f, 0x63E);
        framePercs[cur->PartIndex()] = fPercentage;
    }
    int packed = PackFloats(framePercs, 0, 1);
    std::vector<float> moreFsToPack(mSingers.size());
    std::vector<int> boolsToPack(mSingers.size());
    FOREACH (it, mSingers) {
        Singer *cur = *it;
        float f9 = Clamp<float>(
            -1, 1, (cur->mFrameMicPitch - cur->mFrameTargetPitch) / mMaxDetune
        );
        float f10 = cur->GetFrameMicPitch();
        moreFsToPack[cur->GetSingerIndex()] = f9;
        boolsToPack[cur->GetSingerIndex()] = f10 == 0;
    }
    int packedFs2 = PackFloats(moreFsToPack, -1, 1);
    int packedBs = PackBools(boolsToPack);
    static Message vocal_state_msg("send_vocal_state", 0.0f, 0, 0.0f);
    vocal_state_msg[0] = packedFs2;
    vocal_state_msg[1] = packedBs;
    vocal_state_msg[2] = packed;
    HandleType(vocal_state_msg);
    mNextPacketSendTime = f1 + mPacketPeriodMs;
}

void VocalPlayer::RemoteVocalState(int i1, int i2, int i3) {
    std::vector<float> fvec1;
    UnpackFloats(i1, -1, 1, fvec1);
    std::vector<int> ivec;
    UnpackBools(i2, ivec);
    std::vector<float> fvec2;
    UnpackFloats(i3, 0, 1, fvec2);
    FOREACH (it, mSingers) {
        Singer *cur = *it;
        float detune = fvec1[cur->GetSingerIndex()] * mMaxDetune;
        cur->SetIsSinging(ivec[cur->GetSingerIndex()]);
        cur->Detune(detune);
    }
    FOREACH (it, mVocalParts) {
        (*it)->SetRemotePhraseMeterFrac(fvec2[(*it)->PartIndex()]);
    }
}

unsigned int VocalPlayer::PackFloats(
    const std::vector<float> &i_rFractionArray, float f1, float f2
) const {
    MILO_ASSERT(i_rFractionArray.size() <= 4, 0x6BE);
    float fDenominator = f2 - f1;
    MILO_ASSERT(fDenominator > 0.0f, 0x6C1);
    unsigned int packed = 0;
    for (int i = 0; i < i_rFractionArray.size(); i++) {
        float curF = i_rFractionArray[i];
        float f2ToUse;
        if (curF >= f1) {
            f2ToUse = f1;
        } else if (curF <= f2) {
            f2ToUse = curF;
        } else
            f2ToUse = f2;
        float fNormalized = (f2ToUse - f1) / fDenominator;
        MILO_ASSERT_RANGE_EQ(fNormalized, 0.0f, 1.0f, 0x6D9);
        int iByteValue = fNormalized * 255.0f;
        MILO_ASSERT_RANGE_EQ(iByteValue, 0, 255, 0x6DC);
        packed |= iByteValue << (i * 8);
    }
    return packed;
}

void VocalPlayer::UnpackFloats(
    int i1, float f1, float f2, std::vector<float> &o_rFractionArray
) const {
    MILO_ASSERT(o_rFractionArray.size() == 0, 0x6ED);
    o_rFractionArray.resize(4);
    float fDifference = f2 - f1;
    MILO_ASSERT(fDifference > 0.0f, 0x6F3);
    for (int i = 0; i < 4; i++) {
        o_rFractionArray[i] =
            fDifference * ((float)((i1 >> (i * 8)) & 0xFF) / 255.0f) + f1;
    }
}

unsigned int VocalPlayer::PackBools(const std::vector<int> &i_rBoolArray) const {
    MILO_ASSERT(i_rBoolArray.size() <= 4, 0x70D);
    unsigned int packed = 0;
    for (int i = 0; i < i_rBoolArray.size(); i++) {
        packed |= (bool)(i_rBoolArray[i] != 0) << (i * 8);
    }
    return packed;
}

void VocalPlayer::UnpackBools(int i1, std::vector<int> &o_rBoolArray) const {
    MILO_ASSERT(o_rBoolArray.size() == 0, 0x723);
    o_rBoolArray.resize(4);
    for (int i = 0; i < 4; i++) {
        o_rBoolArray[i] = (bool)((i1 >> (i * 8)) != 0);
    }
}

int VocalPlayer::GetSpotlightPhraseID() const {
    FOREACH (it, mVocalParts) {
        int phrase = (*it)->GetSpotlightPhrase();
        if (phrase != -1)
            return phrase;
    }
    return -1;
}

void VocalPlayer::HandlePhraseEnd(float f1) {
    std::vector<VocalPart *> voxParts = mVocalParts;
    std::sort(voxParts.begin(), voxParts.end(), VocalPart::FramePhraseMeterFracSorter);
    for (int i = 0; i < voxParts.size(); i++) {
        VocalPart *cur = voxParts[i];
        cur->SetPhraseScoreMultiplier(mPartScoreMultipliers->Float(i + 1));
        cur->SetPhraseRank(i);
    }
    int i4 = GetSpotlightPhraseID();
    float fc4 = -1.0f;
    int i16 = 0;
    int ic8 = -1;
    int i15 = 0;
    int i14 = mPhraseActivePartCount;
    mPhraseActivePartCount = 0;
    int id8;
    float fcc;
    float fd0;
    int idc;
    std::vector<float> vec58;
    std::vector<int> vec60(3);
    FOREACH (it, mVocalParts) {
        VocalPart *cur = *it;
        vec58.push_back(cur->MaxPhraseScore());
        float fd4 = FramePhraseMeterFrac(cur->PartIndex());
        if (!cur->InEmptyPhrase() && cur->InPlayablePhrase() && !cur->mThisPhrase->unk2d
            && cur->ScoringEnabled() && cur->ScoringEnabled()) {
            MaxEq(fc4, fd4);
        }

        cur->HandlePhraseEnd(id8, fcc, fd0, idc, f1);
        if (!cur->InEmptyPhrase() && cur->InPlayablePhrase() && cur->ScoringEnabled()) {
            vec60[cur->PartIndex()] = 1;
            mPhraseActivePartCount++;
        }
        if (ic8 < id8 && ScoringEnabled() && cur->ScoringEnabled()) {
            ic8 = id8;
        }
        if (id8 >= 4)
            i15++;
        mStats.SetVocalPartPercentage(
            cur->PartIndex(), cur->GetOverallPartHitPercentage()
        );
    }
    if (fc4 >= 0 && ScoringEnabled()) {
        mPhrasePercentageCount++;
        mPhrasePercentageTotal += fc4;
    }
    FOREACH (it, mSingers) {
        Singer *cur = *it;
        cur->HandlePhraseEnd(f1, vec58);
        FOREACH (it2, mVocalParts) {
            VocalPart *curPart = *it2;
            mStats.SetSingerPartPercentage(
                cur->GetSingerIndex(),
                curPart->PartIndex(),
                cur->GetPartPercentage(curPart->PartIndex())
            );
        }
        float fe0, fe4;
        cur->GetPitchDeviation(fe0, fe4);
        mStats.SetSingerPitchDeviationInfo(cur->GetSingerIndex(), fe0, fe4);
    }
    if (i14 >= 2) {
        mStats.mDoubleHarmonyPhraseCount++;
        if (i15 >= 2) {
            mStats.mDoubleHarmonyHit++;
        }
        if (i14 == 3) {
            mStats.mTripleHarmonyPhraseCount++;
            if (i15 == 3) {
                mStats.mTripleHarmonyHit++;
            }
        }
    }
    if (i15 > 1)
        ic8 = i15 + 3;
    if (ic8 != -1) {
        int idx = mVocalParts.front()->CurrentPhraseIndex();
        int min = std::min(ic8, 4);
        UpdateCrowdMeter(min, idx);
    }
    mTambourineManager.SetTambourine(mVocalParts.front()->InTambourinePhrase());
    bool b14 = i4 != -1 && ic8 >= 4;
    if (mTrack) {
        if (mScoringEnabled) {
            mTrack->OnPhraseComplete(fcc, fd0, i16);
        }
        if (IsLocal()) {
            LocalScorePhrase(ic8, vec60, b14);
            int packedBools = PackBools(vec60);
            static Message msg("send_score_phrase", 0, 0, 0);
            msg[0] = ic8;
            msg[1] = packedBools;
            msg[2] = i14;
            HandleType(msg);
        }
    }
    HandleType(send_vocal_phrase_over_msg);
    Handle(phrase_end_msg, false);
    if (ScoringEnabled() && ic8 != -1) {
        Message msg("phrase_rating", ic8);
        Handle(msg, false);
    }
    if (b14 && ScoringEnabled() && mTrack) {
        mCommonPhraseCapturer->HandleVocalPhrase(
            this, mTrack->mTrackConfig.TrackNum(), i4, b14
        );
    }
    if (ScoringEnabled())
        UpdateSectionStats();
}

FORCE_LOCAL_INLINE
bool VocalPlayer::ScoringEnabled() const { return mScoringEnabled && !InRollback(); }
END_FORCE_LOCAL_INLINE

bool VocalPlayer::ToggleFrameSpew() {
    if (mFrameSpewData) {
        MILO_ASSERT(mFrameSpewStream, 0xE28);
        RELEASE(mFrameSpewData);
        RELEASE(mFrameSpewStream);
        return false;
    } else {
        MILO_ASSERT(mFrameSpewStream == NULL, 0xE38);
        mFrameSpewData = new VocalFrameSpewData(mSingers.size(), mVocalParts.size());
        TextFileStream *s = new TextFileStream("vocals.frame_data.txt", false);
        mFrameSpewStream = s;
        mFrameSpewData->OutputHeader(*s);
        return true;
    }
}

void VocalPlayer::EnablePartScoring(int part, bool b2) {
    MILO_ASSERT(mVocalParts.size() > part, 0xE4D);
    mVocalParts[part]->EnableScoring(b2);
}

void VocalPlayer::SwapAmbiguousPoints(float f1, int i2, int i3) {
    mVocalParts[i2]->ForcePhrasePointDelta(-f1);
    mVocalParts[i3]->ForcePhrasePointDelta(f1);
}

void VocalPlayer::ClearScoreHistories() {
    FOREACH (it, mSingers) {
        (*it)->ClearScoreHistories();
    }
}

void VocalPlayer::AddAccuracyStat(int i) { mStats.AddAccuracy(i); }
void VocalPlayer::AddScoreStreakStat(float f) { mStats.AddScoreStreak(f); }
void VocalPlayer::AddBandContributionStat(float f) { mStats.AddBandContribution(f); }
void VocalPlayer::AddOverdriveStat(float f) { mStats.AddOverdrive(f); }
void VocalPlayer::AddTambourinePointsStat(float f) { mStats.AddTambourine(f); }
void VocalPlayer::AddHarmonyStat(int i) { mStats.AddHarmony(i); }
void VocalPlayer::AddTambourineSeen() { mStats.AddTambourineSeen(); }
void VocalPlayer::AddTambourineHit() { mStats.AddTambourineHit(); }
void VocalPlayer::EndTambourineSection(int i) { mStats.UpdateBestTambourineSection(i); }