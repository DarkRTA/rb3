#include "game/Player.h"
#include "bandtrack/Track.h"
#include "Band.h"
#include "PlayerBehavior.h"
#include "bandobj/BandTrack.h"
#include "beatmatch/BeatMaster.h"
#include "beatmatch/SongPos.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Game.h"
#include "game/Performer.h"
#include "game/SongDB.h"
#include "meta_band/MetaPerformer.h"
#include "obj/Data.h"
#include "obj/Task.h"
#include "os/System.h"
#include "utl/Messages4.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"
#include "utl/Symbols3.h"
#include "utl/TimeConversion.h"

inline PlayerParams::PlayerParams(){
    DataArray* crowdcfg = SystemConfig("scoring", "crowd");
    mCrowdSaveLevel = crowdcfg->FindFloat("save_level");
    mMsToReturnFromBrink = crowdcfg->FindFloat("time_to_return_from_brink") * 1000.0f;
    mCrowdLossPerMs = crowdcfg->FindFloat("crowd_loss_per_sec") / 1000.0f;

    DataArray* unisoncfg = SystemConfig("scoring", "unison_phrase");
    unk24 = unisoncfg->FindFloat("point_bonus");

    DataArray* energycfg = SystemConfig("scoring", "band_energy");
    unkc = 1.0f / energycfg->FindFloat("deploy_beats");
    unk10 = energycfg->FindFloat("deploy_bonus");
    unk14 = energycfg->FindFloat("spotlight_phrase");
    unk18 = energycfg->FindFloat("deploy_threshold");
    unk1c = energycfg->FindFloat("save_energy");
}

inline void PlayerParams::SetVocals(){
    DataArray* crowdcfg = SystemConfig("scoring", "crowd");
    mMsToReturnFromBrink = crowdcfg->FindFloat("vocals_to_return_from_brink") * 1000.0f;
}

Player::Player(BandUser* user, Band* band, int i, BeatMaster* bmaster) : Performer(user, band), mParams(new PlayerParams()), mBehavior(new PlayerBehavior()), mUser(user), unk238(0),
    unk248(i), mTrackType(kTrackNone), unk250(0), unk254(0), unk268(0), unk26c(0), unk270(0), unk274(1), unk278(0), unk27c(1), unk280(bmaster), unk284(5000.0f), unk288(0), unk28c(0),
    unk290(0), unk294(0), unk298(0), unk2a8(0), unk2a9(0), unk2ac(0), unk2b1(0), unk2b2(0), unk2b3(0), unk2b4(0), unk2b8(0), unk2bc(0), unk2c0(-1), unk2c4(1) {
    if(user){
        unk238 = !user->IsLocal();
        unk23c = user->UserName();
        mTrackType = user->GetTrackType();
        if(mTrackType == kTrackVocals){
            mParams->SetVocals();
        }
    }
    unk29c = 0;
    unk2a0 = 0;
    unk2a4 = 0;
    DataArray* cfg = SystemConfig("track_graphics");
    unk284 = cfg->FindFloat("popup_help_intro_duration_ms");
}

void Player::DynamicAddBeatmatch(){
    DisableOverdrivePhrases();
    // mCommonPhraseCapturer->Enabled(this, unk248, MsToTick(PollMs()), false);
    // TheSongDB->ClearTrackPhrases(unk248);
}

void Player::PostDynamicAdd(){
    float secs = TheTaskMgr.Seconds(TaskMgr::b);
    mQuarantined = true;
    mPollMs = secs * 1000.0f;
    SetTrack(unk248);
    PostLoad(true);
    HookupTrack();
    SetEnabledState((EnabledState)3, mUser, false);
    GetBandTrack()->DropIn();
}

#pragma push
#pragma dont_inline on
DECOMP_FORCEFUNC(Player, Player, GetUser())
#pragma pop

void Player::Leave(){
    mCommonPhraseCapturer->Enabled(this, unk248, MsToTick(PollMs()), false);
    BandTrack* track = GetBandTrack();
    if(track) track->DropOut();
}

Player::~Player(){
    delete mBehavior;
    delete mParams;
}

bool Player::RebuildPhrases(){
    if(mQuarantined){
        if(mUser != TheBandUserMgr->GetNullUser()){
            TheSongDB->RebuildPhrases(unk248);
            return true;
        }
    }
    return false;
}

void Player::Restart(bool b){
    if(unk250 == 4){
        unk2a8 = true;
        SetEnabledState((EnabledState)4, mUser, false);
        SetAutoplay(true);
        SetAutoOn(true);
    }
    else unk250 = 0;
    SetQuarantined(mUser == TheBandUserMgr->GetNullUser());
    unk2c4 = true;
    unk254 = 0;
    unk268 = false;
    unk26c = 0;
    unk270 = false;
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
    if(IsLocal()){
        mStats.SetFinalized(true);
    }
    if(unk2a8){
        mCrowd->SetDisplayValue(0);
    }
    unk2ac = 0;
    unk2b2 = 0;
    unk2b3 = 0;
    if(mUser){
        Track* track = mUser->GetTrack();
        if(track){
            track->RefreshPlayerHUD();
        }
    }
    SetCrowdMeterActive(!TheGame->ResumedNoScore());
}

void Player::Poll(float f, const SongPos& pos){
    PollMultiplier();
    if(f < TheSongDB->GetSongDurationMs()){
        PollEnabledState(f);
    }
    if(IsNet()){
        PollTalking(unk2ac);
    }
    UpdateEnergy(pos);
    Performer::Poll(f, pos);
    unk2ac++;
    if(unk1e2 && unk270){
        StopDeployingBandEnergy(false);
    }
    if(IsLocal() && f >= unk2a4 + 2000.0f && !unk1e2){
        Handle(send_update_energy_msg, true);
        unk2a4 = f;
    }
    if(unk288 && IsLocal() && f >= unk284){
        PopupHelp(intro, false);
        unk288 = false;
    }
    if(unk2c4){
        BandTrack* track = GetBandTrack();
        if(track) track->SetQuarantined(mQuarantined);
        unk2c4 = false;
    }
}

void Player::PollMultiplier(){

}

void Player::PollEnabledState(float f){
    switch(unk250){
        case 0:
            break;
        case 1:
            if(unk254 < 3){
                BandTrack* track = GetBandTrack();
                if(track) track->PlayerDisabled();
            }
        case 4:
            if(!unk2a8){
                MetaPerformer::Current();
                if(GetCrowdMeterActive()){
                    mCrowd->SetDisplayValue(mParams->mCrowdLossPerMs * (TheGame->NumActivePlayers() - 1) * (f - unk25c));
                }
            }
            break;
        case 2:
        case 3:
            if(f >= unk258){
                SetEnabledState((EnabledState)0, mUser, false);
            }
            break;
        default:
            break;
    }
}

void Player::PollTalking(int i){
    if(i == i % 5 && unk290){
        BandTrack* track = GetBandTrack();
        if(track) track->SetNetTalking(false);
        unk290 = false;
    }
}

void Player::AddPoints(float f, bool b1, bool b2){
    if(IsLocal()){
        Performer::AddPoints(f, b1, b2);
        BroadcastScore();
    }
}

void Player::StartIntro(){
    if(IsLocal()){
        LocalBandUser* user = mUser->GetLocalBandUser();
        if(!user->HasShownIntroHelp(mTrackType)){
            PopupHelp(intro, true);
            user->SetShownIntroHelp(mTrackType, true);
            unk288 = true;
        }
    }
}

float Player::GetSongMs() const {
    return unk280->mAudio->GetTime();
}

void Player::BroadcastScore(){
    if(unk1fd){
        float poll = PollMs();
        float sub = poll - unk29c;
        int isub = (int)mScore - unk2a0;
        if((isub > 0x13U) || (isub != 0) && (sub >= 250.0f)){
            HandleType(send_update_score_msg);
            unk29c = poll;
            unk2a0 = mScore;
        }
    }
}

void Player::EnterCoda(){
    if(!unk268){
        if(unk250 - 1U <= 2){
            unk258 = PollMs();
            mUser->GetTrack()->SetGemsEnabledByPlayer();
            SetEnabledState((EnabledState)0, mUser, false);
        }
        unk268 = true;
        mStats.mHasCoda = true;
    }
//   if ((this[0x268] == (Player)0x0) && (*(char *)(TheGame + 0x36) != '\0')) {
//     if (*(int *)(this + 0x250) - 1U < 3) {
//       dVar1 = (double)Performer::PollMs((Performer *)this);
//       *(float *)(this + 0x258) = (float)dVar1;
//       (**(code **)(**(int **)(*(int *)(this + 0x230) + 0x7c) + 0xe4))();
//       (**(code **)(*(int *)(this + 4) + 0x1b4))(this,0,*(undefined4 *)(this + 0x230),0);
//     }
//     this[0x268] = (Player)0x1;
//     this[0xb8] = (Player)0x1;
//   }
}