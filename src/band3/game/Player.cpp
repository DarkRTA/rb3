#include "game/Player.h"
#include "Player.h"
#include "bandobj/BandDirector.h"
#include "bandobj/OverdriveMeter.h"
#include "bandtrack/Track.h"
#include "Band.h"
#include "PlayerBehavior.h"
#include "bandobj/BandTrack.h"
#include "bandtrack/TrackPanel.h"
#include "beatmatch/BeatMaster.h"
#include "utl/SongPos.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/Game.h"
#include "game/GameConfig.h"
#include "game/NetGameMsgs.h"
#include "game/Performer.h"
#include "game/Scoring.h"
#include "game/SongDB.h"
#include "meta_band/MetaPerformer.h"
#include "net/NetSession.h"
#include "obj/Data.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/HxGuid.h"
#include "utl/MakeString.h"
#include "utl/Messages4.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include "utl/TimeConversion.h"

inline PlayerParams::PlayerParams() {
    DataArray *crowdcfg = SystemConfig("scoring", "crowd");
    mCrowdSaveLevel = crowdcfg->FindFloat("save_level");
    mMsToReturnFromBrink = crowdcfg->FindFloat("time_to_return_from_brink") * 1000.0f;
    mCrowdLossPerMs = crowdcfg->FindFloat("crowd_loss_per_sec") / 1000.0f;

    DataArray *unisoncfg = SystemConfig("scoring", "unison_phrase");
    unk24 = unisoncfg->FindFloat("point_bonus");

    DataArray *energycfg = SystemConfig("scoring", "band_energy");
    unkc = 1.0f / energycfg->FindFloat("deploy_beats");
    unk10 = energycfg->FindFloat("deploy_bonus");
    unk14 = energycfg->FindFloat("spotlight_phrase");
    unk18 = energycfg->FindFloat("deploy_threshold");
    unk1c = energycfg->FindFloat("save_energy");
}

inline void PlayerParams::SetVocals() {
    DataArray *crowdcfg = SystemConfig("scoring", "crowd");
    mMsToReturnFromBrink = crowdcfg->FindFloat("vocals_to_return_from_brink") * 1000.0f;
}

Player::Player(BandUser *user, Band *band, int tracknum, BeatMaster *bmaster)
    : Performer(user, band), mParams(new PlayerParams()), mBehavior(new PlayerBehavior()),
      mUser(user), mRemote(0), mTrackNum(tracknum), mTrackType(kTrackNone),
      mEnabledState(kPlayerEnabled), mTimesFailed(0), unk268(0), mBandEnergy(0),
      mDeployingBandEnergy(0), unk274(1), unk278(0), mPhraseBonus(1),
      mBeatMaster(bmaster), unk284(5000.0f), unk288(0), unk28c(0), unk290(0), unk294(0),
      unk298(0), mDisconnectedAtStart(0), unk2a9(0), unk2ac(0), mPermanentOverdrive(0),
      mHasFinishedCoda(0), mHasBlownCoda(0), unk2b4(0), unk2b8(0), unk2bc(0), unk2c0(-1),
      unk2c4(1) {
    if (user) {
        mRemote = !user->IsLocal();
        mPlayerName = user->UserName();
        mTrackType = user->GetTrackType();
        if (mTrackType == kTrackVocals) {
            mParams->SetVocals();
        }
    }
    unk29c = 0;
    unk2a0 = 0;
    unk2a4 = 0;
    DataArray *cfg = SystemConfig("track_graphics");
    unk284 = cfg->FindFloat("popup_help_intro_duration_ms");
}

void Player::DynamicAddBeatmatch() { DisableOverdrivePhrases(); }

void Player::PostDynamicAdd() {
    float secs = TheTaskMgr.Seconds(TaskMgr::kRealTime);
    mQuarantined = true;
    mPollMs = secs * 1000.0f;
    SetTrack(mTrackNum);
    PostLoad(true);
    HookupTrack();
    SetEnabledState((EnabledState)3, mUser, false);
    GetBandTrack()->DropIn();
}

#pragma push
#pragma dont_inline on
DECOMP_FORCEFUNC(Player, Player, GetUser())
#pragma pop

void Player::Leave() {
    mCommonPhraseCapturer->Enabled(this, mTrackNum, MsToTick(PollMs()), false);
    BandTrack *track = GetBandTrack();
    if (track)
        track->DropOut();
}

Player::~Player() {
    delete mBehavior;
    delete mParams;
}

bool Player::RebuildPhrases() {
    if (mQuarantined) {
        if (mUser != TheBandUserMgr->GetNullUser()) {
            TheSongDB->RebuildPhrases(mTrackNum);
            return true;
        }
    }
    return false;
}

void Player::Restart(bool b) {
    if (mEnabledState == kPlayerDisconnected) {
        mDisconnectedAtStart = true;
        SetEnabledState(kPlayerDisconnected, mUser, false);
        SetAutoplay(true);
        SetAutoOn(true);
    } else
        mEnabledState = kPlayerEnabled;
    SetQuarantined(mUser == TheBandUserMgr->GetNullUser());
    unk2c4 = true;
    mTimesFailed = 0;
    unk268 = false;
    mBandEnergy = 0;
    mDeployingBandEnergy = false;
    unk28c = 0;
    unk294 = 0;
    unk2b4 = 0;
    unk298 = 0;
    unk274 = 1;
    unk278 = 0;
    unk29c = 0;
    unk2a0 = 0;
    unk2a4 = 0;
    unk2b8 = 0;
    unk2bc = 0;
    unk2c0 = -1;
    unk260.clear();
    Performer::Restart(b);
    if (IsLocal()) {
        mStats.SetFinalized(true);
    }
    if (mDisconnectedAtStart) {
        mCrowd->SetDisplayValue(0);
    }
    unk2ac = 0;
    mHasFinishedCoda = 0;
    mHasBlownCoda = 0;
    if (mUser) {
        Track *track = mUser->GetTrack();
        if (track) {
            track->RefreshPlayerHUD();
        }
    }
    SetCrowdMeterActive(!TheGame->ResumedNoScore());
}

void Player::Poll(float f, const SongPos &pos) {
    PollMultiplier();
    if (f < TheSongDB->GetSongDurationMs()) {
        PollEnabledState(f);
    }
    if (IsNet()) {
        PollTalking(unk2ac);
    }
    UpdateEnergy(pos);
    Performer::Poll(f, pos);
    unk2ac++;
    if (unk1e2 && mDeployingBandEnergy) {
        StopDeployingBandEnergy(false);
    }
    if (IsLocal() && f >= unk2a4 + 2000.0f && !unk1e2) {
        Handle(send_update_energy_msg, true);
        unk2a4 = f;
    }
    if (unk288 && IsLocal() && f >= unk284) {
        PopupHelp(intro, false);
        unk288 = false;
    }
    if (unk2c4) {
        BandTrack *track = GetBandTrack();
        if (track)
            track->SetQuarantined(mQuarantined);
        unk2c4 = false;
    }
}

void Player::PollMultiplier() {}

void Player::PollEnabledState(float f) {
    switch (mEnabledState) {
    case kPlayerEnabled:
        break;
    case kPlayerDisabled:
        if (mTimesFailed < 3) {
            BandTrack *track = GetBandTrack();
            if (track)
                track->PlayerDisabled();
        }
    case kPlayerDisconnected:
        if (!mDisconnectedAtStart) {
            MetaPerformer::Current();
            if (GetCrowdMeterActive()) {
                mCrowd->SetDisplayValue(
                    mParams->mCrowdLossPerMs * (TheGame->NumActivePlayers() - 1)
                    * (f - unk25c)
                );
            }
        }
        break;
    case kPlayerBeingSaved:
    case kPlayerDroppingIn:
        if (f >= mEnableMs) {
            SetEnabledState(kPlayerEnabled, mUser, false);
        }
        break;
    default:
        break;
    }
}

void Player::PollTalking(int i) {
    if (i == i % 5 && unk290) {
        BandTrack *track = GetBandTrack();
        if (track)
            track->SetNetTalking(false);
        unk290 = false;
    }
}

void Player::AddPoints(float f, bool b1, bool b2) {
    if (IsLocal()) {
        Performer::AddPoints(f, b1, b2);
        BroadcastScore();
    }
}

void Player::StartIntro() {
    if (IsLocal()) {
        LocalBandUser *user = mUser->GetLocalBandUser();
        if (!user->HasShownIntroHelp(mTrackType)) {
            PopupHelp(intro, true);
            user->SetShownIntroHelp(mTrackType, true);
            unk288 = true;
        }
    }
}

float Player::GetSongMs() const { return mBeatMaster->mAudio->GetTime(); }

void Player::BroadcastScore() {
    if (unk1fd) {
        float poll = PollMs();
        float sub = poll - unk29c;
        int isub = (int)mScore - unk2a0;
        if ((isub > 0x13U) || (isub != 0) && (sub >= 250.0f)) {
            HandleType(send_update_score_msg);
            unk29c = poll;
            unk2a0 = mScore;
        }
    }
}

void Player::EnterCoda() {
    if (!unk268) {
        if (mEnabledState == kPlayerDisabled || mEnabledState == kPlayerBeingSaved
            || mEnabledState == kPlayerDroppingIn) {
            mEnableMs = PollMs();
            mUser->GetTrack()->SetGemsEnabledByPlayer();
            SetEnabledState(kPlayerEnabled, mUser, false);
        }
        unk268 = true;
        mStats.mHasCoda = true;
    }
}

void Player::AddBonusPoints(int i) { TheGame->AddBonusPoints(mUser, i, unk28c++); }

void Player::Rollback(float, float) {
    BandTrack *track = GetBandTrack();
    if (track) {
        track->ResetSmashers(false);
    }
}

int Player::GetAccumulatedScore() const { return mScore; }
float Player::GetTotalStars() const { return GetNumStarsFloat(); }

void Player::SetEnabledState(EnabledState estate, BandUser *user, bool b) {
    if (IsLocal()) {
        int tick = MsToTick(GetSongMs());
        LocalSetEnabledState(estate, tick, user, b);
        static Message msg("send_enabled_state", 0, 0, 0);
        msg[0] = estate << 0x10 | b;
        msg[1] = tick;
        msg[2] = user->GetSlot();
        HandleType(msg);
    } else if (estate == 2) {
        unk298 = 1;
    }
}

EnabledState Player::GetEnabledStateAt(float) const {}

DECOMP_FORCEACTIVE(
    Player, __FILE__, "causer", "send_already_saved", "", "player_saved", "%s_regen.cue"
)

void Player::LocalSetEnabledState(EnabledState estate, int i, BandUser *causer, bool b) {
    unk298 = 0;
    if (estate == kPlayerBeingSaved && mEnabledState != kPlayerDisabled) {
        MILO_ASSERT(causer, 0x260);
        if (causer->GetPlayer()->IsLocal()) {
            static Message msg("send_already_saved", 0);
            msg[0] = causer;
            HandleType(msg);
        }
    }
    if (mEnabledState == kPlayerDisabled && estate == kPlayerEnabled) {
        mCrowd->SetDisplayValue(mParams->mCrowdSaveLevel);
    }
    if (unk2a9 && estate != kPlayerDisabled) {
        unk2a9 = false;
    }
    SetCrowdMeterActive(!b);
    float durms = TheSongDB->GetSongDurationMs();
    float f11 = GetSongMs();
    float newpct = f11 / durms;
    if (b) {
        SetNoScorePercent(newpct);
    }
    mEnabledState = estate;
    switch (estate) {
    case kPlayerEnabled:
        Handle(enable_player_msg, true);
        break;
    case kPlayerDisabled:
    case kPlayerDisconnected:
        SetEnergy(0);
        break;
    case kPlayerDroppingIn:
        DelayReturn(true);
        mUser->GetTrack()->SetGemsEnabledByPlayer();
        break;
    case kPlayerBeingSaved:
        BandTrack *track = GetBandTrack();
        track->PlayerSaved();
        float savedurms = TheSongDB->GetSongDurationMs();
        float savesongms = GetSongMs();
        float savenewpct = f11 / durms;
        mStats.AddToTimesSaved(0, savenewpct);
        mCrowd->SetDisplayValue(mParams->mCrowdSaveLevel);
        DelayReturn(true);
        track->SavePlayer();
        static Message player_saved("player_saved", "", 0);
        player_saved[0] = causer->GetTrackSym();
        player_saved[1] = b;
        TheBandDirector->HandleType(player_saved);
        break;
    default:
        break;
    }
}

bool Player::Saveable() const {
    bool ret = false;
    if (mEnabledState == kPlayerDisabled && mTimesFailed < 3 && !unk298)
        ret = true;
    if (ret)
        MetaPerformer::Current();
    return ret;
}

void Player::Save(BandUser *user, bool b) { SetEnabledState(kPlayerBeingSaved, user, b); }

#pragma push
#pragma pool_data off
void Player::DisablePlayer(int i) {
    if (!unk2a9) {
        const char *cue = MakeString("%s_died.cue", TrackTypeToSym(mTrackType).Str());
        float f = 0;
        if (TheBandUserMgr->IsMultiplayerGame()) {
            if (mUser->GetSlot() == -1)
                f = -1.0f;
            else
                f = 1.0f;
        }
        GetTrackPanel()->PlaySequence(cue, 0, f, 0);
    }
    if (GetBandTrack()) {
        GetBandTrack()->DisablePlayer(i);
    }
    if (mEnabledState == kPlayerDisabled) {
        static Message player_failed("player_failed", 0);
        player_failed[0] = TrackTypeToSym(mTrackType);
        TheBandDirector->HandleType(player_failed);
    }

    static Message disable_player("disable_player", 0);
    disable_player[0] = mTimesFailed;
    Export(disable_player, true);
}
#pragma pop

const UserGuid &Player::GetUserGuid() const {
    MILO_ASSERT(GetUser(), 0x330);
    return mUser->mUserGuid;
}

int Player::GetSlot() const {
    MILO_ASSERT(GetUser(), 0x336);
    return mUser->GetSlot();
}

bool Player::IsNet() const { return mRemote; }

int Player::GetMultiplier(bool b, int &i1, int &i2, int &i3) const {
    if (GetMultiplierActive()) {
        int i1ret;
        if (b) {
            i1ret = GetIndividualMultiplier();
        } else
            i1ret = 1;
        i1 = i1ret;
        i2 = mBand->EnergyMultiplier();
        i3 = mDeployingBandEnergy + 1;
        i2 /= i3;
        return i1 * i2 * i3;
    } else {
        i1 = 1;
        i2 = 1;
        i3 = 1;
        return 1;
    }
}

void Player::SetMultiplierActive(bool b) {
    Performer::SetMultiplierActive(b);
    if (!b) {
        SetEnergy(0);
        BandTrack *track = GetBandTrack();
        if (track)
            track->SetStreak(0, 1, 1, false);
    }
}

bool Player::CanDeployOverdrive() const {
    return mBandEnergy >= mParams->unk18 && !mDeployingBandEnergy && unk2b0;
}

bool Player::IsDeployingBandEnergy() const { return mDeployingBandEnergy; }

void Player::StopDeployingBandEnergy(bool b) {
    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    GetMultiplier(true, i1, i2, i3);
    mStats.StopDeployingOverdrive(GetSongMs(), i1 * i3);
    mDeployingBandEnergy = false;
    if (mBand) {
        mBand->UpdateBonusLevel(PollMs());
    }
    if (!b) {
        GetTrackPanel()->PlaySequence(
            MakeString("rp_depleted_%s.cue", TrackTypeToSym(mTrackType).Str()), 0, 0, 0
        );
    }

    if (GetBandTrack()) {
        GetBandTrack()->StopDeploy();
    }
    SetEnergyAutomatically(mBandEnergy);
    if (CanDeployOverdrive()) {
        mUser->GetTrack()->SetCanDeploy(true);
        if (mTrackType == kTrackDrum) {
            EnableDrumFills(true);
        }
    }
}

void Player::DisablePhraseBonus() { mPhraseBonus = false; }
void Player::EnablePhraseBonus() { mPhraseBonus = true; }

void Player::DisableOverdrivePhrases() {
    mCommonPhraseCapturer->Enabled(this, mTrackNum, MsToTick(PollMs()), false);
    TheSongDB->ClearTrackPhrases(mTrackNum);
}

void Player::CompleteCommonPhrase(bool b1, bool b2) {
    float energy;
    if (mPhraseBonus)
        energy = mParams->unk14;
    else
        energy = 0;
    AddEnergy(energy);
    if (b1) {
        if (b2) {
            mStats.mUnisonPhraseCompleted++;
        }
    } else
        mStats.mOverdrivePhrasesCompleted++;
}

int Player::GetIndividualMultiplier() const {
    if (GetMultiplierActive()) {
        int streak = mStats.GetCurrentStreak();
        int mult = TheScoring->GetStreakMult(streak, mBehavior->mStreakType);

        return mult;
    } else
        return 1;
}

int Player::GetMaxIndividualMultipler() const { return mBehavior->mMaxMultiplier; }

int Player::GetNumStars() const {
    return TheScoring->GetSoloNumStars(mScore, mTrackType);
}

float Player::GetNumStarsFloat() const {
    return TheScoring->GetSoloNumStarsFloat(mScore, mTrackType);
}

int Player::GetScoreForStars(int i) const {
    return TheScoring->GetSoloScoreForStars(i, mTrackType);
}

void Player::SavePersistentData(PersistentPlayerData &data) const {
    data.unk0 = mBandEnergy;
    data.unk4 = GetCrowdRating();
    data.unk8 = mStats.m0x150;
    data.unkc = mStats.mLongestPersistentStreak;
}

void Player::LoadPersistentData(const PersistentPlayerData &data) {
    if (!mDisconnectedAtStart) {
        SetEnergyAutomatically(data.unk0);
        mCrowd->SetValue(data.unk4);
        mStats.SetPersistentStreak(data.unk8);
        BandUser *user = mUser;
        mStats.mLongestPersistentStreak = data.unkc;
        MILO_ASSERT(user, 0x402);
        Track *track = user->GetTrack();
        if (track)
            track->RefreshPlayerHUD();
    }
}

DECOMP_FORCEACTIVE(Player, "Non-local player trying to deploy locally\n", "send_deploy")

int Player::LocalDeployBandEnergy() {
    int energy = mBand->DeployBandEnergy(mUser);
    mStats.mDeployCount++;
    mStats.AddToPlayersSaved(energy, mBand->MainPerformer()->Crowd()->GetValue());
    PerformDeployBandEnergy(energy, true);
    return energy;
}

void Player::PerformDeployBandEnergy(int i, bool b) {
    if (!b)
        mBand->DeployBandEnergy(mUser);
    if (i == 0) {
        mDeployingBandEnergy = true;
        if (mBand) {
            mBand->UpdateBonusLevel(PollMs());
        }
        Deploy();
    } else
        SubtractEnergy(mParams->unk1c);
}

DECOMP_FORCEACTIVE(Player, "rp_deployed_%s.cue")

void Player::RemoteAlreadySaved(int i) {
    unk294--;
    if (unk294 == 0) {
        AddEnergy(mParams->unk1c);
    }
    unk2b4--;
}

void Player::PopupHelp(Symbol s, bool b) {
    BandUser *user = mUser;
    if (user && user->GetDifficulty() == kDifficultyEasy) {
        BandTrack *track = GetBandTrack();
        if (track) {
            track->SetControllerType(user->GetControllerSym());
            track->PopupHelp(s, b);
        }
    }
}

void Player::AddEnergy(float f) {
    TheGame->OnPlayerAddEnergy(this, f);
    float set = Min(1.0f, mBandEnergy + f);
    SetEnergy(set);
}

Symbol Player::GetStreakType() const { return mBehavior->mStreakType; }

void Player::SetEnergy(float f) {
    MetaPerformer::Current();
    if (IsLocal() && unk2b0) {
        float old = mBandEnergy;
        SetEnergyAutomatically(f);
        float newf = mBandEnergy;
        float poll = PollMs();
        if (old < newf || poll - unk2a4 >= 100.0f || mBandEnergy == 0) {
            Handle(send_update_energy_msg, true);
            unk2a4 = poll;
        }
    }
}

void Player::SetEnergyFromNet(float f, bool b) {
    SetEnergyAutomatically(f);
    if (mDeployingBandEnergy && !b) {
        StopDeployingBandEnergy(false);
    }
}

bool Player::ShouldDrainEnergy() const { return true; }

void Player::CheckCrowdFailure() {
    if (mCrowd->IsBelowLoseLevel() && mEnabledState == kPlayerEnabled) {
        if (!mCrowd->CantFailYet() && mUser->GetDifficulty() != kDifficultyEasy
            && !mUser->IsNullUser()) {
            if (!MetaPerformer::Current()->IsNoFailActive() && !mQuarantined
                && !mBand->MainPerformer()->mGameOver) {
                SetEnabledState(kPlayerDisabled, mUser, false);
            }
        }
        mCrowd->SetDisplayValue(0);
    }
}

BandTrack *Player::GetBandTrack() const {
    if (mUser->GetTrack()) {
        return mUser->GetTrack()->GetBandTrack();
    } else
        return nullptr;
}

void Player::UnisonMiss(int i) const {
    if (mUser->GetTrack()) {
        mUser->GetTrack()->OnMissPhrase(i);
    }
}

void Player::UnisonHit() {
    BandTrack *track = GetBandTrack();
    if (track) {
        track->SpotlightPhraseSuccess();
    }
    GetTrackPanel()->PlaySequence(
        MakeString("rp_captured_%s.cue", TrackTypeToSym(mTrackType).Str()), 0, 0, 0
    );
}

void Player::SetFinishedCoda() {
    MILO_ASSERT(!mHasBlownCoda, 0x5A8);
    mHasFinishedCoda = true;
}

void Player::ChangeDifficulty(Difficulty diff) {
    mScore = 0;
    mStats = Stats();
    SetEnergy(0);
    mCrowd->ChangeDifficulty(mUser, diff);
    mCrowd->SetLoseLevel(mBand->MainPerformer()->Crowd()->GetLoseLevel());
    SetQuarantined(true);
    TheGameConfig->ChangeDifficulty(GetUser(), diff);
    mBand->UpdateBonusLevel(TheTaskMgr.Seconds(TaskMgr::kRealTime) * 1000.0f);
}

void Player::SetQuarantined(bool b) {
    mQuarantined = b;
    if (b && mTrackNum != -1) {
        DisableOverdrivePhrases();
        TheGame->OnPlayerQuarantined(this);
    }
    BandTrack *track = GetBandTrack();
    if (track) {
        track->SetQuarantined(b);
        unk2c4 = false;
    }
}

void Player::DeterminePerformanceAwards() {
    DataArray *cfg = SystemConfig(performance_awards);
    DataNode &playerNode = DataVariable("player");
    DataNode n30(playerNode);
    DataNode thisNode(this);
    playerNode = thisNode;
    for (int i = 1; i < cfg->Size(); i++) {
        DataArray *arr = cfg->Array(i);
        if (arr->Int(1)) {
            mStats.mAccessPerformanceAwards.push_back(arr->Sym(0));
        }
    }
    playerNode = n30;
}

DataNode Player::OnSendNetGameplayMsg(DataArray *arr) {
    int opcode = arr->Int(2);
    int packet = arr->Int(3) != 0;

    int arg3 = 0;
    int arg2 = 0;
    int arg1 = 0;

    if (arr->Size() > 4)
        arg1 = arr->Int(4);
    if (arr->Size() > 5)
        arg2 = arr->Int(5);
    if (arr->Size() > 6)
        arg3 = arr->Int(6);

    PlayerGameplayMsg msg(mUser, opcode, arg1, arg2, arg3);
    TheNetSession->SendMsgToAll(msg, (PacketType)packet);
    return 1;
}

DataNode Player::OnSendNetGameplayMsgToPlayer(DataArray *arr) {
    User *destUser = arr->Obj<User>(2);
    int opcode = arr->Int(3);
    int packet = arr->Int(4) != 0;

    int arg3 = 0;
    int arg2 = 0;
    int arg1 = 0;

    if (arr->Size() > 5)
        arg1 = arr->Int(5);
    if (arr->Size() > 6)
        arg2 = arr->Int(6);
    if (arr->Size() > 7)
        arg3 = arr->Int(7);

    PlayerGameplayMsg msg(mUser, opcode, arg1, arg2, arg3);
    TheNetSession->SendMsg(destUser, msg, (PacketType)packet);
    return 1;
}

DataNode Player::OnGetOverdriveMeter(DataArray *arr) {
    BandTrack *track = GetBandTrack();
    return track ? (OverdriveMeter *)track->mStarPowerMeter : NULL_OBJ;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(Player)
    HANDLE_EXPR(track, GetUser()->GetTrack())
    HANDLE_EXPR(get_user, GetUser())
    HANDLE_EXPR(player_name, mPlayerName)
    HANDLE_EXPR(instrument, GetUser()->GetTrackSym())
    HANDLE_EXPR(difficulty, GetUser()->GetDifficulty())
    HANDLE_EXPR(is_net, IsNet())
    HANDLE_EXPR(disconnected_at_start, mDisconnectedAtStart)
    HANDLE_ACTION(enter_coda, EnterCoda())
    HANDLE_EXPR(band_energy, mBandEnergy)
    HANDLE_ACTION(set_band_energy, SetEnergy(_msg->Float(2)))
    HANDLE_ACTION(fill_band_energy, SetEnergy(1.0f))
    HANDLE_ACTION(empty_band_energy, SetEnergy(0))
    HANDLE_EXPR(can_deploy, CanDeployOverdrive())
    HANDLE_EXPR(is_deploying, IsDeployingBandEnergy())
    HANDLE_ACTION(deploy_if_possible, DeployBandEnergyIfPossible(false))
    HANDLE_ACTION_IF(force_deploy, !mDeployingBandEnergy, LocalDeployBandEnergy())
    HANDLE_EXPR(in_freestyle_section, InFreestyleSection())
    HANDLE(star_power_meter, OnGetOverdriveMeter)
    HANDLE_ACTION(fail, SetEnabledState(kPlayerDisabled, GetUser(), false))
    HANDLE_EXPR(enabled_state, mEnabledState)
    HANDLE_EXPR(enable_time, mEnableMs)
    HANDLE_ACTION(enable_swings, EnableSwings(_msg->Int(2)))
    HANDLE_ACTION(update_lefty_flip, UpdateLeftyFlip())
    HANDLE_ACTION(update_vocal_style, UpdateVocalStyle())
    HANDLE_ACTION(reset_controller, ResetController(_msg->Int(2)))
    HANDLE_ACTION(enable_phrase_bonus, EnablePhraseBonus())
    HANDLE_ACTION(disable_phrase_bonus, DisablePhraseBonus())
    HANDLE_ACTION(popup_help, PopupHelp(_msg->Sym(2), _msg->Int(3)))
    HANDLE(send_net_gameplay_msg, OnSendNetGameplayMsg)
    HANDLE(send_net_gameplay_msg_to_player, OnSendNetGameplayMsgToPlayer)
    HANDLE_ACTION(remote_deploy, PerformDeployBandEnergy(_msg->Int(2), false))
    HANDLE_ACTION(
        remote_hit_last_unison_gem,
        mCommonPhraseCapturer->LocalHitLastGem(this, _msg->Int(2), _msg->Int(3))
    )
    HANDLE_ACTION(remote_update_energy, SetEnergyFromNet(_msg->Float(2), _msg->Int(3)))
    HANDLE_ACTION(
        remote_fail_unison_phrase,
        mCommonPhraseCapturer->LocalFail(this, _msg->Int(2), _msg->Int(3))
    )
    HANDLE_ACTION(
        remote_enabled_state,
        LocalSetEnabledState(
            (EnabledState)(_msg->Int(2) >> 0x10),
            _msg->Int(3),
            TheBandUserMgr->GetUserFromSlot(_msg->Int(4)),
            (u16)(_msg->Int(2))
        )
    )
    HANDLE_ACTION(remote_already_saved, RemoteAlreadySaved(_msg->Int(2)))
    HANDLE_ACTION(
        remote_tracker_focus,
        TheGame->OnRemoteTrackerFocus(this, _msg->Int(2), _msg->Int(3), _msg->Int(4))
    )
    HANDLE_ACTION(
        remote_tracker_player_progress,
        TheGame->OnRemoteTrackerPlayerProgress(this, _msg->Float(2))
    )
    HANDLE_ACTION(
        remote_tracker_section_complete,
        TheGame->OnRemoteTrackerSectionComplete(
            this, _msg->Int(2), _msg->Int(3), _msg->Int(4)
        )
    )
    HANDLE_ACTION(
        remote_tracker_player_display,
        TheGame->OnRemoteTrackerPlayerDisplay(
            this, _msg->Int(2), _msg->Int(3), _msg->Int(4)
        )
    )
    HANDLE_ACTION(remote_tracker_deploy, TheGame->OnRemoteTrackerDeploy(this))
    HANDLE_ACTION(
        remote_tracker_end_deploy_streak,
        TheGame->OnRemoteTrackerEndDeployStreak(this, _msg->Int(2))
    )
    HANDLE_ACTION(
        remote_tracker_end_streak,
        TheGame->OnRemoteTrackerEndStreak(this, _msg->Int(2), _msg->Int(3))
    )
    HANDLE_EXPR(get_times_failed, mTimesFailed)
    HANDLE_EXPR(get_deploy_failed, mStats.GetFailedDeploy())
    HANDLE_EXPR(get_saved_count, mStats.GetPlayersSaved())
    HANDLE_ACTION(set_permanent_overdrive, mPermanentOverdrive = _msg->Int(2))
    HANDLE_ACTION(set_energy_automatically, SetEnergyAutomatically(_msg->Float(2)))
    HANDLE_ACTION(clear_score_histories, ClearScoreHistories())
    HANDLE_ACTION(change_difficulty, ChangeDifficulty((Difficulty)_msg->Int(2)))
    HANDLE_SUPERCLASS(Performer)
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0x6DE)
END_HANDLERS
#pragma pop