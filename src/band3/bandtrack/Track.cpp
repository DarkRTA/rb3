#include "bandtrack/Track.h"
#include "bandobj/BandTrack.h"
#include "bandtrack/TrackPanel.h"
#include "decomp.h"
#include "game/Band.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/Game.h"
#include "game/GameMode.h"
#include "game/Player.h"
#include "meta_band/AppLabel.h"
#include "meta_band/MetaPerformer.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

Track::Track(BandUser *user)
    : mTrackConfig(user), unk48(-1.0f), unk4c(3), unk50(0), unk54(-1), unk58(-1),
      unk60(0), unk64(-3.4028235E+38f) {}

void Track::Poll(float f) {
    Player *player = mTrackConfig.GetBandUser()->GetPlayer();
    if (player) {
        float dispval = player->mCrowd->GetDisplayValue();
        bool warning = player->AllowWarningState();
        if (unk48 != dispval || warning != unk50) {
            CrowdMeterState cty;
            if (!player->mCrowd->IsBelowLoseLevel() || IsNoFailActive()
                || GetPlayerDifficulty() == kDifficultyEasy) {
                if (player->mCrowd->GetExcitement() <= 1 && warning) {
                    cty = kCrowdMeterWarning;
                } else
                    cty = kCrowdMeterNormal;
            } else {
                cty = kCrowdMeterFailed;
            }
            if (unk4c == cty) {
                cty = kCrowdMeterInvalidState;
            } else {
                unk4c = cty;
            }
            GetBandTrack()->SetCrowdRating(dispval, cty);
            unk48 = dispval;
            unk50 = warning;
        }

        int curstreak = player->mStats.GetCurrentStreak();
        if (curstreak != unk54) {
            if (!GetBandTrack()) {
                MILO_FAIL(
                    "no track dir for track %s (%s)!",
                    mTrackConfig.GetBandUser()->UserName(),
                    mTrackConfig.GetBandUser()->mUserGuid.ToString()
                );
            }
            unk54 = curstreak;
        }

        if (unk60 && f > unk64) {
            unk60 = false;
            unk64 = -3.4028235E+38f;
        }
    }
}

const User *Track::GetUser() const { return mTrackConfig.GetBandUser(); }

const BandUser *Track::GetBandUser() const { return mTrackConfig.GetBandUser(); }

Difficulty Track::GetPlayerDifficulty() const {
    const BandUser *user = mTrackConfig.GetBandUser();
    if (user->mPlayer) {
        return user->mPlayer->GetUser()->GetDifficulty();
    } else
        return kDifficultyEasy;
}

Symbol Track::GetPlayerDifficultySym() const {
    const BandUser *user = mTrackConfig.GetBandUser();
    if (user->mPlayer) {
        return user->mPlayer->GetUser()->GetDifficultySym();
    } else
        return gNullStr;
}

Hmx::Object *Track::GetObj(Symbol s) {
    RndDir *dir = GetDir();
    if (!dir)
        return nullptr;
    else
        dir->FindObject(s.Str(), false);
}

Symbol Track::GetType() const { return mTrackConfig.Type(); }

Player *Track::GetPlayer() const { return mTrackConfig.GetBandUser()->GetPlayer(); }

bool Track::ShouldDisablePopupHelp() const {
    Player *player = mTrackConfig.GetBandUser()->GetPlayer();
    return player
        && (player->GetUser()->GetDifficulty() >= kDifficultyHard || player->IsNet());
}

bool Track::InGame() const { return TheGame; }

bool Track::HasPlayer() const { return mTrackConfig.GetBandUser()->GetPlayer(); }

const char *Track::GetTrackIcon() const {
    const BandUser *user = mTrackConfig.GetBandUser();
    if (user)
        return user->GetTrackIcon();
    else
        return "";
}

const char *Track::GetPlayerName() const {
    const BandUser *user = mTrackConfig.GetBandUser();
    if (user->GetPlayer())
        return user->GetPlayer()->GetUser()->IntroName();
    else
        return "";
}

const char *Track::UserName() const {
    const BandUser *user = mTrackConfig.GetBandUser();
    if (user->GetPlayer())
        return user->GetPlayer()->GetUser()->UserName();
    else
        return "";
}

bool Track::PlayerDisconnected() const {
    const BandUser *user = mTrackConfig.GetBandUser();
    if (user->GetPlayer())
        return user->GetPlayer()->mEnabledState == kPlayerDisconnected;
    else
        return false;
}

bool Track::PlayerDisconnectedAtStart() const {
    const BandUser *user = mTrackConfig.GetBandUser();
    if (user->GetPlayer())
        return user->GetPlayer()->mDisconnectedAtStart;
    else
        return false;
}

bool Track::HasLocalPlayer() const {
    const BandUser *user = mTrackConfig.GetBandUser();
    if (user->GetPlayer())
        return user->GetPlayer()->IsLocal();
    else
        return false;
}

bool Track::PlayerDisabled() const {
    const BandUser *user = mTrackConfig.GetBandUser();
    if (user->GetPlayer())
        return user->GetPlayer()->mEnabledState != kPlayerEnabled;
    else
        return false;
}

void Track::DTSPopup(bool) const {}

bool Track::HasNetPlayer() const {
    Player *player = mTrackConfig.GetBandUser()->GetPlayer();
    if (player)
        return player->IsNet() || player->mEnabledState == kPlayerDisconnected;
    else
        return false;
}

bool Track::IsLocal() const {
    const BandUser *user = mTrackConfig.GetBandUser();
    if (user && user->IsLocal())
        return true;
    else
        return false;
}

int Track::GetBandMultiplier() const {
    int i1, i2, i3;
    return mTrackConfig.GetBandUser()->GetPlayer()->GetBand()->GetMultiplier(
        true, i1, i2, i3
    );
}

void Track::PushGameplayOptions(VocalParam, int) {
    unk5c = mTrackConfig.GetBandUser()->GetPlayer()->GetUser()->GetGameplayOptions();
}

int Track::GetNoBackFromBrink() const {
    MetaPerformer::Current();
    return 0;
}

void Track::RefreshPlayerHUD() {
    static bool sDump;
    BandTrack *track = GetBandTrack();
    Player *player = mTrackConfig.GetBandUser()->GetPlayer();
    if (track && player) {
        if (sDump) {
            float od = player->mBandEnergy;
            MILO_LOG(
                "Refreshing HUD for player %d: streak %d, mult %d, od %.2f, ready %d\n",
                player->GetSlot(),
                player->mStats.GetCurrentStreak(),
                player->GetIndividualMultiplier(),
                od,
                player->CanDeployOverdrive()
            );
        }
        track->RefreshStreakMeter(
            player->mStats.GetCurrentStreak(),
            player->GetIndividualMultiplier(),
            player->GetNotesPerStreak()
        );
        float od = player->mBandEnergy;
        track->RefreshOverdrive(od, player->CanDeployOverdrive());
    }
}

bool Track::FailedAtStart() {
    if (mTrackConfig.GetBandUser()->GetPlayer()) {
        return mTrackConfig.GetBandUser()->GetPlayer()->unk2a9;
    } else
        return false;
}

bool Track::IsDeployingOverdrive() const {
    if (mTrackConfig.GetBandUser()->GetPlayer()) {
        return mTrackConfig.GetBandUser()->GetPlayer()->IsDeployingBandEnergy();
    } else
        return false;
}

bool Track::IsNoFailActive() const { return MetaPerformer::Current()->IsNoFailActive(); }

void Track::SetUserNameLabel(ObjectDir *dir, const char *labelName) {
    MILO_ASSERT(dir && labelName, 0x177);
    AppLabel *label = dir->Find<AppLabel>(labelName, false);
    if (label) {
        if (mTrackConfig.GetBandUser()) {
            label->SetIntroName((BandUser *)mTrackConfig.GetBandUser());
        } else {
            label->SetTextToken("<username>");
        }
    }
}

bool Track::InGameMode(Symbol s) const { return TheGameMode->InMode(s); }

bool Track::IsScoring() const {
    if (mTrackConfig.GetBandUser()->GetPlayer()) {
        return !mTrackConfig.GetBandUser()->GetPlayer()->GetQuarantined();
    } else
        return false;
}

void Track::StartPulseAnims(float f) {
    if (GetBandTrack()) {
        GetBandTrack()->StartPulseAnims(f);
    } else
        MILO_LOG("no BandTrack found\n");
}

int Track::GetTrackNum() const { return mTrackConfig.TrackNum(); }

BEGIN_HANDLERS(Track)
    HANDLE_EXPR(get_dir, GetDir())
    HANDLE_EXPR(get_obj, GetObj(_msg->Sym(2)))
    HANDLE_EXPR(get_player_config, (BandUser *)mTrackConfig.GetBandUser())
    HANDLE_EXPR(panel, GetTrackPanel())
    HANDLE_EXPR(player, mTrackConfig.GetBandUser()->GetPlayer())
    HANDLE_ACTION(refresh_hud, RefreshPlayerHUD())
    HANDLE_ACTION(set_playing_intro, SetPlayingIntro(_msg->Float(2)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_MEMBER_PTR(GetDir())
    HANDLE_CHECK(0x1AF)
END_HANDLERS