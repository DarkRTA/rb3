#include "meta_band/CampaignCareerLeaderboardPanel.h"
#include "Campaign.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "meta_band/CampaignLeaderboards.h"
#include "meta_band/ProfileMgr.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "ui/UIList.h"
#include "ui/UIPanel.h"
#include "utl/Messages.h"
#include "utl/Messages2.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

CampaignCareerLeaderboardPanel::CampaignCareerLeaderboardPanel() : mCampaignCareerLeaderboardProvider(0), mScoreType(kScoreBand), mUseDLC(0) {

}

void CampaignCareerLeaderboardPanel::EnumerationStarted(){
    HandleType(lb_in_progress_msg);
}

void CampaignCareerLeaderboardPanel::ResultSuccess(bool b1, bool b2, bool b3){
    static Message success("lb_success", 0, 0, 0);
    success[0] = b1;
    success[1] = b2;
    success[2] = b3;
    HandleType(success);
}

void CampaignCareerLeaderboardPanel::ResultFailure(){
    HandleType(lb_failure_msg);
}

void CampaignCareerLeaderboardPanel::Poll(){
    UIPanel::Poll();
    if(mCampaignCareerLeaderboardProvider){
        mCampaignCareerLeaderboardProvider->Poll();
    }
}

void CampaignCareerLeaderboardPanel::Enter(){
    UIPanel::Enter();
    MILO_ASSERT(mCampaignCareerLeaderboardProvider, 0x4A);
    mCampaignCareerLeaderboardProvider->SetMode(Leaderboard::kPercentile, false);
    mCampaignCareerLeaderboardProvider->StartEnumerate();
    UpdateProvider();
}

void CampaignCareerLeaderboardPanel::Load(){
    UIPanel::Load();
    LocalBandUser* pUser  = TheCampaign->GetUser();
    MILO_ASSERT(pUser, 0x59);
    BandProfile* pProfile = TheProfileMgr.GetProfileForUser(pUser);
    MILO_ASSERT(pProfile, 0x5D);
    MILO_ASSERT(!mCampaignCareerLeaderboardProvider, 0x5F);
    mCampaignCareerLeaderboardProvider = new PlayerCampaignCareerLeaderboard(pProfile, this, mScoreType, mUseDLC);
}

void CampaignCareerLeaderboardPanel::Unload(){
    UIPanel::Unload();
    RELEASE(mCampaignCareerLeaderboardProvider);
}

void CampaignCareerLeaderboardPanel::SetScoreType(ScoreType ty){
    MILO_ASSERT(mCampaignCareerLeaderboardProvider, 0x6E);
    if(ty != mScoreType){
        mScoreType = ty;
        mCampaignCareerLeaderboardProvider->SetScoreType(mScoreType);
    }
}

Symbol CampaignCareerLeaderboardPanel::GetScoreType() const {
    if(mScoreType == kNumScoreTypes) return "record_label";
    else return ScoreTypeToSym(mScoreType);
}

void CampaignCareerLeaderboardPanel::SetUseDLC(bool dlc){ mUseDLC = dlc; }

void CampaignCareerLeaderboardPanel::UpdateProvider(){
    static Message cUpdateLeaderboardProviderMsg("update_leaderboard_provider", 0);
    cUpdateLeaderboardProviderMsg[0] = mCampaignCareerLeaderboardProvider;
    Handle(cUpdateLeaderboardProviderMsg, true);
}

void CampaignCareerLeaderboardPanel::CycleMode(){
    mCampaignCareerLeaderboardProvider->CycleMode();
}

BEGIN_HANDLERS(CampaignCareerLeaderboardPanel)
    HANDLE_ACTION(set_scoretype, SetScoreType((ScoreType)_msg->Int(2)))
    HANDLE_EXPR(get_scoretype, GetScoreType())
    HANDLE_ACTION(set_use_dlc, SetUseDLC(_msg->Int(2)))
    HANDLE_ACTION(cycle_mode, CycleMode())
    HANDLE_EXPR(get_mode_symbol, mCampaignCareerLeaderboardProvider->GetModeSymbol())
    HANDLE_ACTION(scroll_lb_up, mCampaignCareerLeaderboardProvider && mCampaignCareerLeaderboardProvider->EnumerateLowerRankRange())
    HANDLE_ACTION(scroll_lb_down, mCampaignCareerLeaderboardProvider && mCampaignCareerLeaderboardProvider->EnumerateHigherRankRange())
    HANDLE_ACTION(set_leaderboard_mode, {MILO_ASSERT(mCampaignCareerLeaderboardProvider, 0xAD); mCampaignCareerLeaderboardProvider->SetMode((Leaderboard::Mode)_msg->Int(2), true); })
    HANDLE_ACTION_IF(select_lb_row, mCampaignCareerLeaderboardProvider, mCampaignCareerLeaderboardProvider->OnSelectRow(_msg->Int(2), _msg->Obj<BandUser>(3)) )
    HANDLE_ACTION_IF(set_to_starting_lb_ix, mCampaignCareerLeaderboardProvider, _msg->Obj<UIList>(2)->SetSelected(mCampaignCareerLeaderboardProvider->GetStartingRow(), -1))
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xB4)
END_HANDLERS