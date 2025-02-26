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
#include "utl/TextFileStream.h"

MicClientID sNullMicClientID;

VocalPlayer::VocalPlayer(
    BandUser *user, BeatMaster *bmaster, Band *band, int tracknum, Performer *perf, int i7
)
    : Player(user, band, tracknum, bmaster), mBandPerformer(perf), unk2d0(0), mTrack(0),
      unk2d8(0), unk2dc(1.25f), unk2e8(0), unk2ec(0), unk2f0(0), unk300(0), unk304(0),
      unk308(0), unk328(-1), mPhraseValue(0), unk330(0), unk334(0), unk338(0.6f),
      unk33c(0), mCodaEndMs(0), unk344(0), mTuningOffset(0), unk34c(-1.0f), unk368(0),
      unk36c(0), unk370(0), unk374(0), unk378(0), unk37c(0), mOverlay(0), unk384(0),
      unk388(1), mTambourineManager(*this), unk414(0), unk418(0), unk41c(0),
      mFrameSpewData(0), mFrameSpewStream(0) {
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
    unk308 = cfg->FindFloat("track_wrapping_margin");
    unk320 = cfg->FindArray("freestyle_deployment_time", true)->Array(1);
    unk324 = cfg->FindArray("freestyle_min_duration", true)->Array(1);
    unk2f4 = cfg->FindFloat("max_detune");
    unk2f8 = cfg->FindFloat("packet_period");
    unk330 = cfg->FindArray("part_score_multiplier", true);
    unk334 = cfg->FindArray("rating_thresholds", true);
    unk338 = cfg->FindFloat("nonpitch_stickiness");
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
        unk2f0 = 0;
        unk328 = -1;
        mBeatMaster->GetAudio()->SetVocalFailFader(0);
        mBeatMaster->GetAudio()->SetVocalDuckFader(0);
        if (mTrack) {
            unk33c = !TheNetSession->IsLocal() && PressingToTalk();
            SendCanChat(unk33c);
        }
        Player::Restart(b1);
        unk374 = 0;
        if (!b1) {
            mStats.SetVocalSingerAndPartCounts(mSingers.size(), mVocalParts.size());
            unk37c = 0;
            unk378 = 0;
        }
        mTambourineManager.Restart();
        unk414 = 0;
        unk418 = 0;
        unk41c = 0;
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
        unk2f0 = 0;
        unk328 = -1;
        unk374 = 0;
        unk378 = 0;
        unk37c = 0;
        mTambourineManager.Jump(f1);
        mTambourineManager.SetTambourine(mVocalParts.front()->InTambourinePhrase());
        if (mTrack)
            mTrack->RebuildHUD();
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