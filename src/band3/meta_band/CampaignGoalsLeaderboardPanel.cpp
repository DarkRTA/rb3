#include "meta_band/CampaignGoalsLeaderboardPanel.h"
#include "BandProfile.h"
#include "game/BandUser.h"
#include "game/Game.h"
#include "game/GameMode.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/Campaign.h"
#include "meta_band/CampaignLeaderboards.h"
#include "meta_band/Leaderboard.h"
#include "meta_band/ProfileMgr.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "tour/Tour.h"
#include "ui/UIList.h"
#include "ui/UIPanel.h"
#include "utl/Symbol.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

CampaignGoalsLeaderboardPanel::CampaignGoalsLeaderboardPanel() : mCampaignGoalsLeaderboardProvider(0), mGoal(gNullStr) {

}

void CampaignGoalsLeaderboardPanel::ResultSuccess(bool b1, bool b2, bool b3){
    static Message success("lb_success", 0, 0, 0);
    success[0] = b1;
    success[1] = b2;
    success[2] = b3;
    HandleType(success);
}

void CampaignGoalsLeaderboardPanel::ResultFailure(){
    HandleType(lb_failure_msg);
}

void CampaignGoalsLeaderboardPanel::EnumerationStarted(){
    HandleType(lb_in_progress_msg);
}

void CampaignGoalsLeaderboardPanel::Poll(){
    UIPanel::Poll();
    if(mCampaignGoalsLeaderboardProvider){
        mCampaignGoalsLeaderboardProvider->Poll();
    }
}

void CampaignGoalsLeaderboardPanel::Enter(){
    UIPanel::Enter();
    MILO_ASSERT(mCampaignGoalsLeaderboardProvider, 0x4C);
    mCampaignGoalsLeaderboardProvider->SetMode(Leaderboard::kPercentile, false);
    mCampaignGoalsLeaderboardProvider->StartEnumerate();
    UpdateProvider();
}

void CampaignGoalsLeaderboardPanel::Load(){
    UIPanel::Load();
    LocalBandUser* pUser = nullptr;
    if(TheGameMode->InMode("campaign")){
        pUser = TheCampaign->GetUser();
    }
    else if(TheGameMode->InMode("tour")){
        pUser = TheTour->GetUser();
    }
    MILO_ASSERT(pUser, 99);
    BandProfile* pProfile = TheProfileMgr.GetProfileForUser(pUser);
    MILO_ASSERT(pProfile, 0x67);
    MILO_ASSERT(!mCampaignGoalsLeaderboardProvider, 0x69);
    mCampaignGoalsLeaderboardProvider = new PlayerCampaignGoalLeaderboard(pProfile, this, mGoal);
}

void CampaignGoalsLeaderboardPanel::Unload(){
    UIPanel::Unload();
    RELEASE(mCampaignGoalsLeaderboardProvider);
}

void CampaignGoalsLeaderboardPanel::SetGoal(Symbol goal){ mGoal = goal; }

Symbol CampaignGoalsLeaderboardPanel::GetGoalDescription() const {
    if(TheAccomplishmentMgr->HasAccomplishment(mGoal)){
        Accomplishment* pGoal = TheAccomplishmentMgr->GetAccomplishment(mGoal);
        MILO_ASSERT(pGoal, 0x86);
        return pGoal->GetDescription();
    }
    else return gNullStr;
}

Symbol CampaignGoalsLeaderboardPanel::GetGoalUnits() const {
    if(TheAccomplishmentMgr->HasAccomplishment(mGoal)){
        Accomplishment* pGoal = TheAccomplishmentMgr->GetAccomplishment(mGoal);
        MILO_ASSERT(pGoal, 0x94);
        return pGoal->GetUnitsToken(0);
    }
    else return fans;
}

const char* CampaignGoalsLeaderboardPanel::GetGoalIcon() const {
    Accomplishment* pGoal = TheAccomplishmentMgr->GetAccomplishment(mGoal);
    MILO_ASSERT(pGoal, 0xA2);
    return pGoal->GetIconArt();
}

void CampaignGoalsLeaderboardPanel::UpdateProvider(){
    static Message cUpdateLeaderboardProviderMsg("update_leaderboard_provider", 0);
    cUpdateLeaderboardProviderMsg[0] = mCampaignGoalsLeaderboardProvider;
    Handle(cUpdateLeaderboardProviderMsg, true);
}

void CampaignGoalsLeaderboardPanel::CycleMode(){
    mCampaignGoalsLeaderboardProvider->CycleMode();
}

BEGIN_HANDLERS(CampaignGoalsLeaderboardPanel)
    HANDLE_ACTION(set_goal, SetGoal(_msg->Sym(2)))
    HANDLE_EXPR(get_goal, mGoal)
    HANDLE_EXPR(get_goal_units, GetGoalUnits())
    HANDLE_EXPR(get_goal_desc, GetGoalDescription())
    HANDLE_EXPR(get_goal_icon, GetGoalIcon())
    HANDLE_EXPR(symbol, TheAccomplishmentMgr->HasAccomplishment(mGoal))
    HANDLE_ACTION(cycle_mode, CycleMode())
    HANDLE_EXPR(get_mode_symbol, GetModeSymbol())
    HANDLE_ACTION(scroll_lb_up, mCampaignGoalsLeaderboardProvider && mCampaignGoalsLeaderboardProvider->EnumerateLowerRankRange())
    HANDLE_ACTION(scroll_lb_down, mCampaignGoalsLeaderboardProvider && mCampaignGoalsLeaderboardProvider->EnumerateHigherRankRange())
    HANDLE_ACTION(set_leaderboard_mode, {MILO_ASSERT(mCampaignGoalsLeaderboardProvider, 0xD9); mCampaignGoalsLeaderboardProvider->SetMode((Leaderboard::Mode)_msg->Int(2), true); })
    HANDLE_ACTION_IF(select_lb_row, mCampaignGoalsLeaderboardProvider, mCampaignGoalsLeaderboardProvider->OnSelectRow(_msg->Int(2), _msg->Obj<BandUser>(3)) )
    HANDLE_ACTION_IF(set_to_starting_lb_ix, mCampaignGoalsLeaderboardProvider, _msg->Obj<UIList>(2)->SetSelected(mCampaignGoalsLeaderboardProvider->GetStartingRow(), -1))
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xE0)
END_HANDLERS