#include "game/VocalPlayer.h"
#include "VocalOverlay.h"
#include "bandobj/BandTrack.h"
#include "bandobj/VocalTrackDir.h"
#include "bandtrack/VocalTrack.h"
#include "beatmatch/BeatMaster.h"
#include "beatmatch/MasterAudio.h"
#include "beatmatch/VocalNote.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/Game.h"
#include "game/GameConfig.h"
#include "game/GameMic.h"
#include "game/GameMicManager.h"
#include "game/GamePanel.h"
#include "game/Performer.h"
#include "game/PracticePanel.h"
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
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include "os/System.h"
#include "rndobj/Overlay.h"
#include "synth/MicManagerInterface.h"
#include "ui/UI.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include "utl/TextFileStream.h"
#include "world/Dir.h"
#include "utl/Messages.h"
#include <utility>

MicClientID sNullMicClientID;

VocalPlayer::VocalPlayer(
    BandUser *user, BeatMaster *bmaster, Band *band, int tracknum, Performer *perf, int i7
)
    : Player(user, band, tracknum, bmaster), mBandPerformer(perf), mSpoofed(0), mTrack(0),
      mAutoPlay(0), mVocalPartBias(1.25f), unk2e8(0), unk2ec(0), mNextPacketSendTime(0),
      unk300(0), unk304(0), mTrackWrappingMargin(0), mLastDeploymentSinger(-1),
      mPhraseValue(0), mPartScoreMultipliers(0), mRatingThresholds(0),
      mNonpitchStickiness(0.6f), mCouldChat(0), mCodaEndMs(0), unk344(0),
      mTuningOffset(0), unk34c(-1.0f), mInitialMicCount(0), unk36c(0), unk370(0),
      mPhraseActivePartCount(0), mPhrasePercentageTotal(0), mPhrasePercentageCount(0),
      mOverlay(0), mVocalOverlay(0), mScoringEnabled(1), mTambourineManager(*this),
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
        if (IsNet() || mSpoofed)
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

void VocalPlayer::Poll(float, const SongPos &) {
    MILO_WARN("j != i");
    MILO_WARN("pTrack");
    MILO_WARN("mFrameSpewData");
}

bool VocalPlayer::
    FindBestPart(float, float, std::vector<VocalPart *> &, Singer *i_pSinger, VocalPart *&, float &, float &) {
    MILO_ASSERT(i_pSinger, 0x5DA);
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
        MILO_ASSERT(( 0.0f) <= ( fPercentage) && ( fPercentage) <= ( 1.0f), 0x63E);
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
        MILO_ASSERT(( 0.0f) <= ( fNormalized) && ( fNormalized) <= ( 1.0f), 0x6D9);
        int iByteValue = fNormalized * 255.0f;
        MILO_ASSERT(( 0) <= ( iByteValue) && ( iByteValue) <= ( 255), 0x6DC);
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
        if (!cur->InEmptyPhrase() && cur->InPlayablePhrase()
            && !cur->mThisPhrase->mTambourinePhrase && cur->ScoringEnabled()
            && cur->ScoringEnabled()) {
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

void VocalPlayer::LocalScorePhrase(
    int i1, const std::vector<int> &i_rNewPhraseActiveParts, bool b3
) {
    if (mTrack) {
        int iActivePartCount =
            std::count(i_rNewPhraseActiveParts.begin(), i_rNewPhraseActiveParts.end(), 0);
        MILO_ASSERT(( 0) <= ( iActivePartCount) && ( iActivePartCount) <= ( i_rNewPhraseActiveParts.size()), 0x855);
        VocalTrackDir *dir = mTrack->GetVocalTrackDir();
        dir->ShowPhraseFeedback(i1, -1, -1, IsDeployingBandEnergy());
        dir->UpdateVocalMeters(
            i_rNewPhraseActiveParts[0],
            i_rNewPhraseActiveParts[1],
            i_rNewPhraseActiveParts[2],
            false
        );
        if (b3 && ScoringEnabled()) {
            dir->SpotlightPhraseSuccess();
        }
    }
}

void VocalPlayer::RemoteScorePhrase(int i1, int i2, bool b3) {
    std::vector<int> bools;
    UnpackBools(i2, bools);
    LocalScorePhrase(i1, bools, b3);
}

void VocalPlayer::HookupTrack() {
    mTrack = dynamic_cast<VocalTrack *>(GetUser()->GetTrack());
    MILO_ASSERT(mTrack, 0x88A);
}

DECOMP_FORCEACTIVE(
    VocalPlayer, "fast song scoring should only be done on PC.", "vocal_score_song_done"
)

void VocalPlayer::UnHookTrack() { mTrack = nullptr; }
bool VocalPlayer::PastFinalNote() const { return AtLastPhrase(); }

void VocalPlayer::SetMusicSpeed(float speed) {
    mBeatMaster->GetAudio()->GetSongStream()->SetSpeed(speed);
}

void VocalPlayer::SetAutoplay(bool play) {
    GetUser()->SetAutoplay(play);
    mAutoPlay = play;
    FOREACH (it, mSingers) {
        Singer *cur = *it;
        cur->SetAutoplayToPart(play ? cur->GetSingerIndex() : -1);
    }
}

void VocalPlayer::RotateSingerAutoplayPart(int x) {
    if (x < mSingers.size()) {
        Singer *cur = mSingers[x];
        int part = cur->GetAutoplayToPart();
        if (part == -1)
            part = 0;
        else {
            part++;
            if (part >= NumVocalParts()) {
                part = -1;
            }
        }
        cur->SetAutoplayToPart(part);
    }
}

int VocalPlayer::GetSingerAutoplayPart(int x) {
    if (x < mSingers.size()) {
        return mSingers[x]->GetAutoplayToPart();
    } else
        return -1;
}

void VocalPlayer::SetAutoplayOffset(float f1) {
    FOREACH (it, mSingers) {
        (*it)->SetAutoplayOffset(f1);
    }
}

float VocalPlayer::GetAutoplayOffset() const {
    return mSingers.front()->GetAutoplayOffset();
}

void VocalPlayer::SetVocalPartBias(float bias) { mVocalPartBias = bias; }
float VocalPlayer::GetVocalPartBias() const { return mVocalPartBias; }

DataNode VocalPlayer::OnMidiParser(DataArray *arr) {
    Symbol sym = arr->Sym(2);
    if (sym == "tambourine_gem" && mTrack) {
        mTrack->GetVocalTrackDir()->TambourineNote();
    }
    return 0;
}

int VocalPlayer::OnMsg(const GameMicsChangedMsg &) {
    UpdateMicDisplay();
    return 1;
}

void VocalPlayer::UpdateMicDisplay() {
    if (mTrack) {
        VocalTrackDir *pTrackDir = mTrack->GetVocalTrackDir();
        MILO_ASSERT(pTrackDir, 0x977);
        MILO_ASSERT(TheGameMicManager, 0x979);
        int numMics = TheGameMicManager->GetMicCount();
        bool noMic0 = !TheGameMicManager->HasMic(MicClientID(0, -1));
        bool noMic1 = !TheGameMicManager->HasMic(MicClientID(1, -1));
        bool noMic2 = !TheGameMicManager->HasMic(MicClientID(2, -1));
        bool hadMic0 = HadMic(MicClientID(0, -1));
        bool hadMic1 = HadMic(MicClientID(1, -1));
        bool hadMic2 = HadMic(MicClientID(2, -1));

        bool hadAnyMic = hadMic0 || hadMic1 || hadMic2;
        bool noLongerHasMic0 = noMic0 && hadMic0;
        bool noLongerHasMic1 = noMic1 && hadMic1;
        bool noLongerHasMic2 = noMic2 && hadMic2;
        bool b15 = numMics == 0 || noLongerHasMic0 || noLongerHasMic1 || noLongerHasMic2;
        if (!(b15 & GetUser()->IsLocal())) {
            pTrackDir->ShowMicDisplay(false);
        } else {
            if (mVocalParts.size() == 1) {
                pTrackDir->SetMicDisplayLabel(vocals_connect_a_mic);
            } else {
                pTrackDir->SetMicDisplayLabel(vocals_mics_disconnected);
            }
            if (hadAnyMic) {
                pTrackDir->SetMissingMicsForDisplay(
                    noLongerHasMic0, noLongerHasMic1, noLongerHasMic2
                );
            } else
                pTrackDir->SetMissingMicsForDisplay(true, false, false);
            pTrackDir->ShowMicDisplay(true);
        }
    }
}

void VocalPlayer::RememberCurrentMics() {
    mInitialMicClientIDs.clear();
    mInitialMicCount = 0;
    MILO_ASSERT(TheGameMicManager, 0x9BE);
    for (int i = 0; i < 4; i++) {
        MicClientID id(i, -1);
        if (TheGameMicManager->HasMic(id)) {
            mInitialMicClientIDs.push_back(id);
            mInitialMicCount++;
        }
    }
}

bool VocalPlayer::HadMic(const MicClientID &id) const {
    FOREACH (it, mInitialMicClientIDs) {
        if (it->unk0 == id.unk0)
            return true;
    }
    return false;
}

int VocalPlayer::OnMsg(const ButtonDownMsg &msg) {
    if ((User *)GetUser() != msg.GetUser())
        return 0;
    else {
        bool b1 = false;
        if (TheUI->FocusPanel()) {
            b1 = strcmp(TheUI->FocusPanel()->Name(), "world_panel") == 0;
        }
        if (TheUI->FocusPanel() != TheGamePanel && !b1) {
            if (!dynamic_cast<PracticePanel *>(TheUI->FocusPanel()))
                return 0;
        }
    }
    return 0;
}

DECOMP_FORCEACTIVE(
    VocalPlayer,
    "HandleActivateVolume: Couldn't get a VocalParam for supposed volume button %d!\n",
    "HandleDeactivateVolume: Couldn't get a VocalParam for supposed volume button %d!\n",
    "HandleChangeVolume got an unused button! Ignoring it.\n",
    "( 0) <= ( o_rMicNumber) && ( o_rMicNumber) < ( 3)"
)

int VocalPlayer::OnMsg(const ButtonUpMsg &) { return 0; }

bool VocalPlayer::AllowPitchCorrection() const {
    MILO_ASSERT(TheGameMicManager, 0xA46);
    return TheGameMicManager->GetMicCount() == 1 && mVocalParts.size() == 1;
}

bool VocalPlayer::AllowWarningState() const {
    MILO_ASSERT(TheGameMicManager, 0xA56);
    return !GetUser()->IsNullUser() || TheGameMicManager->GetMicCount() > 0;
}

void VocalPlayer::OnGameOver() {
    if (!MetaPerformer::Current()->SongEndsWithEndgameSequence()) {
        TheGameMicManager->SetPlayback(false);
    }
    mTambourineManager.GameOver();
    FOREACH (it, mVocalParts) {
        (*it)->OnGameOver();
    }
}

void VocalPlayer::EnableController() {
    TheGameMicManager->SetPlayback(true);
    FOREACH (it, mSingers) {
        (*it)->EnableController();
    }
    if (mUser->IsLocal()) {
        JoypadKeepAlive(mUser->GetLocalUser()->GetPadNum(), true);
    }
}

void VocalPlayer::DisableController() { OnDisableController(); }

void VocalPlayer::OnDisableController() {
    TheGameMicManager->SetPlayback(false);
    FOREACH (it, mSingers) {
        (*it)->DisableController();
    }
    if (mUser->IsLocal()) {
        JoypadKeepAlive(mUser->GetLocalUser()->GetPadNum(), false);
    }
}

bool VocalPlayer::ShouldDrainEnergy() const { return true; }

bool VocalPlayer::InFreestyleSection() const {
    FOREACH (it, mVocalParts) {
        if ((*it)->InFreestyleSection())
            return true;
    }
    return false;
}

void VocalPlayer::ChangeDifficulty(Difficulty diff) {
    Player::ChangeDifficulty(diff);
    TheSongDB->ChangeDifficulty(mTrackNum, diff);
    mStats.SetVocalSingerAndPartCounts(mSingers.size(), mVocalParts.size());
    SetDifficultyVariables(diff);
}

void VocalPlayer::BuildPhrases(bool b1) {
    std::vector<std::pair<const VocalPhrase *, VocalPart *> > vec;
    FOREACH (it, mVocalParts) {
        vec.push_back(std::make_pair((*it)->GetFirstPhraseMarker(), *it));
    }
    unk36c = 0;
    unk370 = 0;

    bool b3;
    do {
        b3 = true;
        bool bvar1 = false;
        bool bvar2 = false;
        FOREACH (it, vec) {
            const VocalPhrase *curPhrase = it->first;
            VocalPart *curPart = it->second;
            if (!curPart->IsPhraseMarkerAtEnd(curPhrase)) {
                b3 = false;
                if (!curPart->IsEmptyPhrase(curPhrase))
                    bvar1 = true;
                if (curPhrase->mTambourinePhrase)
                    bvar2 = true;
                it->first = curPart->GetNextPhraseMarker(curPhrase);
            }
        }
        if (bvar1)
            unk36c++;
        if (bvar2)
            unk370++;
    } while (!b3);
    mTambourineManager.PostLoad();
    if (!b1 && NeedsToOverrideBasePoints()) {
        TheSongDB->OverrideBasePoints(
            mTrackNum,
            mTrackType,
            GetUserGuid(),
            GetBaseMaxPoints(),
            GetBaseMaxStreakPoints(),
            GetBaseBonusPoints()
        );
    }
}

bool VocalPlayer::RebuildPhrases() {
    BuildPhrases(false);
    return Player::RebuildPhrases();
}

void VocalPlayer::Rollback(float f1, float f2) {
    FOREACH (it, mVocalParts) {
        (*it)->Rollback(f1, f2);
    }
    FOREACH (it, mSingers) {
        (*it)->Rollback(f1, f2);
    }
    mTambourineManager.Rollback(f1, f2);
    Player::Rollback(f1, f2);
}

bool VocalPlayer::DoneWithSong() const {
    return mQuarantined || GetUser()->IsNullUser() || PastFinalNote();
}

FORCE_LOCAL_INLINE
bool VocalPlayer::ScoringEnabled() const { return mScoringEnabled && !InRollback(); }
END_FORCE_LOCAL_INLINE

void VocalPlayer::HitCoda() {
    if (IsLocal()) {
        LocalHitCoda();
        static Message msg("send_hit_last_coda_gem", 0);
        HandleType(msg);
    }
}

DECOMP_FORCEACTIVE(
    VocalPlayer,
    "**** NEW SONG MIN PITCH: %2.0f (was %2.0f)\n",
    "**** NEW SONG MAX PITCH: %2.0f (was %2.0f)\n"
)

float VocalPlayer::FramePhraseMeterFrac(int idx) const {
    if (idx >= mVocalParts.size())
        return 0;
    else
        return mVocalParts[idx]->FramePhraseMeterFrac();
}

float VocalPlayer::FrameOverallPhraseMeterFrac() const {
    float ret = 0;
    for (int i = 0; i < mVocalParts.size(); i++) {
        float frac = FramePhraseMeterFrac(i);
        if (frac > ret) {
            ret = frac;
        }
    }
    return ret;
}

int VocalPlayer::CalculatePhraseRating(float f1) {
    for (int i = mRatingThresholds->Size() - 1; i >= 1; i--) {
        if (f1 > mRatingThresholds->Float(i)) {
            return i;
        }
    }
    return 0;
}

int VocalPlayer::PhraseScore() const { return mVocalParts.front()->mPhraseScore; }
bool VocalPlayer::IgnorePhrase() const { return false; }

bool VocalPlayer::PressingToTalk() {
    if (!IsLocal())
        return false;
    BandUser *u = GetUser();
    if (!u->IsLocal())
        return false;
    else {
        LocalBandUser *lu = u->GetLocalBandUser();
        if (!UserHasController(lu))
            return false;
        else {
            return JoypadGetPadData(lu->GetPadNum())->IsButtonInMask(0);
        }
    }
}

void VocalPlayer::LocalHitCoda() {
    mBand->LocalFinishedCoda(this);
    mTrack->HideCoda();
    Deploy();
}

void VocalPlayer::LocalBlowCoda() { mBand->LocalBlowCoda(this); }

float VocalPlayer::GetHitPercentage(int p) {
    MILO_ASSERT(p < NumVocalParts(), 0xD18);
    return mVocalParts[p]->GetOverallPartHitPercentage();
}

float VocalPlayer::GetPracticeHitPercentage(int p, int i2, int i3) {
    MILO_ASSERT(p < NumVocalParts(), 0xD20);
    std::vector<VocalPhrase> phrases;
    mVocalParts.front()->mVocalNoteList->GetPracticePhrases(phrases, i2, i3);
    if (p == -1) {
        float f7 = 0;
        for (int i = 0; i < (int)mVocalParts.size(); i++) {
            VocalPart *cur = mVocalParts[i];
            if (cur->ScoringEnabled()) {
                float pct = cur->GetPartHitPercentage(phrases, i2, i3);
                if (pct > f7)
                    f7 = pct;
            }
        }
        return f7;
    } else
        return mVocalParts[p]->GetPartHitPercentage(phrases, i2, i3);
}

float VocalPlayer::GetBestPercentage(int p) {
    MILO_ASSERT(p < NumVocalParts(), 0xD79);
    if (!ScoringEnabled())
        return 0;
    else if (p == -1) {
        float f6 = 0;
        for (int i = 0; i < NumVocalParts(); i++) {
            VocalPart *cur = mVocalParts[i];
            if (cur->ScoringEnabled()) {
                if (cur->GetOverallPartHitPercentage() > f6) {
                    f6 = cur->GetOverallPartHitPercentage();
                }
            }
        }
        return f6;
    } else
        return GetHitPercentage(p);
}

void VocalPlayer::UpdateSectionStats() {
    float f1;
    int diff = mPhrasePercentageCount - mSectionStartPhrasePercentageCount;
    if (diff >= 1) {
        f1 = (mPhrasePercentageTotal - mSectionStartPhrasePercentageTotal) / (float)diff;
    } else {
        f1 = -1;
    }
    Player::UpdateSectionStats(f1, mScore - mSectionStartScore);
}

void VocalPlayer::HandleNewSection(const PracticeSection &s, int i1, int i2) {
    if (ScoringEnabled()) {
        mSectionStartPhrasePercentageCount = mPhrasePercentageCount;
        mSectionStartPhrasePercentageTotal = mPhrasePercentageTotal;
        mSectionStartScore = mScore;
        Player::HandleNewSection(s, i1, i2);
    }
}

void VocalPlayer::UpdateVocalStyle() {
    if (!mTrack || mGameOver)
        return;
    else {
        mTrack->SetVocalStyle(mUser->GetGameplayOptions()->GetVocalStyle());
    }
}

bool VocalPlayer::Freestyling() const {
    bool insection = InFreestyleSection();
    return unk268 || IsDeployingBandEnergy() && insection;
}

bool VocalPlayer::CanDeployCoda() const {
    return mBand->NumNonQuarantinedPlayers() > 1 && !mQuarantined;
}

bool VocalPlayer::AutoplaysCoda() const { return mAutoPlay && !IsNet(); }
bool VocalPlayer::NeedsToOverrideBasePoints() const { return !mUser->IsNullUser(); }

void VocalPlayer::ToggleOverlay() {
    MILO_ASSERT(mOverlay, 0xDF0);
    mOverlay->SetShowing(!mOverlay->Showing());
    RELEASE(mVocalOverlay);
    if (mOverlay->Showing())
        mVocalOverlay = new VocalOverlay();
}

float VocalPlayer::UpdateOverlay(RndOverlay *o, float f2) {
    o->Clear();
    if (mVocalOverlay) {
        o->Print(mVocalOverlay->mDisplayedString.c_str());
    }
    return f2;
}

bool VocalPlayer::SongSectionOnly(float &f1, float &f2) const {
    if (!TheGame->mProperties.mHasSongSections) {
        return false;
    } else {
        int i20, i24;
        TheGameConfig->GetPracticeSections(i20, i24);
        float f28;
        TheGameConfig->GetSectionBounds(i20, f1, f28);
        TheGameConfig->GetSectionBounds(i24, f28, f2);
        TheGame->AdjustForVocalPhrases(f1, f2);
        return true;
    }
}

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

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(VocalPlayer)
    HANDLE_EXPR(in_star_mode, 0)
    HANDLE_EXPR(score, GetScore())
    HANDLE_EXPR(percent_hit, 0)
    HANDLE_ACTION(toggle_overlay, ToggleOverlay())
    HANDLE_ACTION(toggle_frame_spew, ToggleFrameSpew())
    HANDLE_EXPR(num_stars, GetNumStars())
    HANDLE_EXPR(star_rating, GetStarRating())
    HANDLE_ACTION(set_spoofed, mSpoofed = _msg->Int(2))
    HANDLE_EXPR(auto_play, IsAutoplay())
    HANDLE_ACTION(set_auto_play, SetAutoplay(_msg->Int(2)))
    HANDLE_ACTION(rotate_singer_autoplay_part, RotateSingerAutoplayPart(_msg->Int(2)))
    HANDLE_EXPR(get_singer_autoplay_part, GetSingerAutoplayPart(_msg->Int(2)))
    HANDLE_ACTION(
        rotate_singer_autoplay_variation_magnitude,
        RotateSingerAutoplayVariationMagnitude(_msg->Int(2))
    )
    HANDLE_EXPR(
        get_singer_autoplay_variation_magnitude,
        GetSingerAutoplayVariationMagnitude(_msg->Int(2))
    )
    HANDLE_ACTION(set_autoplay_offset, SetAutoplayOffset(_msg->Float(2)))
    HANDLE_EXPR(get_autoplay_offset, GetAutoplayOffset())
    HANDLE_ACTION(set_vocal_part_bias, SetVocalPartBias(_msg->Float(2)))
    HANDLE_EXPR(get_vocal_part_bias, GetVocalPartBias())
    HANDLE_EXPR(get_hit_percentage, GetHitPercentage(_msg->Int(2)))
    HANDLE_EXPR(get_best_percentage, GetBestPercentage(_msg->Int(2)))
    HANDLE_EXPR(
        get_practice_hit_percentage,
        GetPracticeHitPercentage(_msg->Int(2), _msg->Int(3), _msg->Int(4))
    )
    HANDLE_EXPR(get_num_phrases, GetNumPhrases(_msg->Int(2), _msg->Int(3), _msg->Int(4)))
    HANDLE_ACTION(
        remote_vocal_state, RemoteVocalState(_msg->Int(2), _msg->Int(3), _msg->Int(4))
    )
    HANDLE_ACTION(remote_phrase_over, unk2fc = 0)
    HANDLE_ACTION(remote_hit, SetAutoplay(true))
    HANDLE_ACTION(remote_penalize, SetAutoplay(false))
    HANDLE_ACTION(
        remote_score_phrase, RemoteScorePhrase(_msg->Int(2), _msg->Int(3), _msg->Int(4))
    )
    HANDLE_ACTION(remote_hit_last_coda_gem, LocalHitCoda())
    HANDLE_ACTION(remote_blow_coda, LocalBlowCoda())
    HANDLE_ACTION(remote_vocal_energy, LocalEndgameEnergy(_msg->Int(2)))
    HANDLE_ACTION(on_new_track, HookupTrack())
    HANDLE_ACTION(on_game_over, OnGameOver())
    HANDLE_ACTION(disable_controller, OnDisableController())
    HANDLE_ACTION(enable_part_scoring, EnablePartScoring(_msg->Int(2), _msg->Int(3)))
    HANDLE_ACTION(reset_scoring, ResetScoring())
    HANDLE_EXPR(fill_star_power, 0)
    HANDLE_EXPR(empty_star_power, 0)
    HANDLE_EXPR(set_star_power, 0)
    HANDLE_EXPR(set_star_power_deploy_rate, 0)
    HANDLE_EXPR(set_star_power_phrase_boost, 0)
    HANDLE_EXPR(on_downbeat, 0)
    HANDLE_EXPR(set_auto_solo, 0)
    HANDLE_EXPR(toggle_solo_quantize, 0)
    HANDLE_EXPR(on_start_starpower, 0)
    HANDLE_EXPR(on_stop_starpower, 0)
    HANDLE_EXPR(refresh_track_buttons, 0)
    HANDLE(midi_parser, OnMidiParser)
    HANDLE_MESSAGE(GameMicsChangedMsg)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_MEMBER_PTR((&mTambourineManager))
    HANDLE_SUPERCLASS(Player)
    HANDLE_CHECK(0xF30)
END_HANDLERS
#pragma pop