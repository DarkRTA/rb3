#include "bandtrack/Track.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/Game.h"
#include "game/Player.h"
#include "obj/Object.h"
#include "utl/Symbol.h"

Track::Track(BandUser* user) : mTrackConfig(user), unk48(-1.0f), unk4c(3), unk50(0), unk54(-1), unk58(-1), unk60(0), unk64(-3.4028235E+38f) {

}

void Track::Poll(float f){
    Player* player = mTrackConfig.GetBandUser()->GetPlayer();
    if(player){
        float dispval = player->mCrowd->GetDisplayValue();
        bool warning = player->AllowWarningState();
        if(unk48 != dispval || warning != unk50){
            CrowdMeterState cty;
            if(!player->mCrowd->IsBelowLoseLevel() || IsNoFailActive() || GetPlayerDifficulty() == kDifficultyEasy){
                if(player->mCrowd->GetExcitement() <= 1 && warning){
                    cty = kCrowdMeterWarning;
                }
                else cty = kCrowdMeterNormal;
            }
            else {
                cty = kCrowdMeterFailed;
            }
            if(unk4c == cty){
                cty = kCrowdMeterInvalidState;
            }
            else {
                unk4c = cty;
            }
            GetBandTrack()->SetCrowdRating(dispval, cty);
            unk48 = dispval;
            unk50 = warning;
        }

        int curstreak = player->mStats.GetCurrentStreak();
        if(curstreak != unk54){
            if(!GetBandTrack()){
                MILO_FAIL("no track dir for track %s (%s)!", mTrackConfig.GetBandUser()->UserName(), 
                    mTrackConfig.GetBandUser()->mUserGuid.ToString());
            }
            unk54 = curstreak;
        }

        if(unk60 && f > unk64){
            unk60 = false;
            unk64 = -3.4028235E+38f;
        }
    }
}

const User* Track::GetUser() const {
    return mTrackConfig.GetBandUser();
}

const BandUser* Track::GetBandUser() const {
    return mTrackConfig.GetBandUser();
}

Difficulty Track::GetPlayerDifficulty() const {
    const BandUser* user = mTrackConfig.GetBandUser();
    if(user->mPlayer){
        return user->mPlayer->unk230->GetDifficulty();
    }
    else return kDifficultyEasy;
}

Symbol Track::GetPlayerDifficultySym() const {
    const BandUser* user = mTrackConfig.GetBandUser();
    if(user->mPlayer){
        return user->mPlayer->unk230->GetDifficultySym();
    }
    else return gNullStr;
}

Hmx::Object* Track::GetObj(Symbol s){
    RndDir* dir = GetDir();
    if(!dir) return nullptr;
    else dir->FindObject(s.Str(), false);
}

Symbol Track::GetType() const { return mTrackConfig.Type(); }

Player* Track::GetPlayer() const {
    return mTrackConfig.GetBandUser()->GetPlayer();
}

bool Track::ShouldDisablePopupHelp() const {
    Player* player = mTrackConfig.GetBandUser()->GetPlayer();
    return player && (player->unk230->GetDifficulty() >= kDifficultyHard || player->IsNet());
}

bool Track::InGame() const {
    return TheGame;
}

bool Track::HasPlayer() const {
    return mTrackConfig.GetBandUser()->GetPlayer();
}

const char* Track::GetTrackIcon() const {
    const BandUser* user = mTrackConfig.GetBandUser();
    if(user) return user->GetTrackIcon();
    else return "";
}

const char* Track::GetPlayerName() const {
    const BandUser* user = mTrackConfig.GetBandUser();
    if(user->GetPlayer()) return user->GetPlayer()->unk230->IntroName();
    else return "";
}

const char* Track::UserName() const {
    const BandUser* user = mTrackConfig.GetBandUser();
    if(user->GetPlayer()) return user->GetPlayer()->unk230->UserName();
    else return "";
}

bool Track::PlayerDisconnected() const {

}