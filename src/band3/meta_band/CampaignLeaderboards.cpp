#include "meta_band/CampaignLeaderboards.h"
#include "meta_band/Leaderboard.h"
#include "meta_band/PlayerLeaderboards.h"
#include "net_band/RockCentral.h"

PlayerCampaignGoalLeaderboard::PlayerCampaignGoalLeaderboard(Profile* p, Leaderboard::Callback* cb, Symbol goal) : PlayerLeaderboard(p, cb), mGoal(goal) {

}

void PlayerCampaignGoalLeaderboard::EnumerateFromID(){
    mDataResultList.Clear();
    std::vector<int> ids;
    GetPlayerIds(ids);
    TheRockCentral.GetAccLeaderboardByPlayer(ids, mGoal, ModeToLeaderboardMode(mMode), sPageSize, mDataResultList, this);
}

void PlayerCampaignGoalLeaderboard::EnumerateRankRange(int i1, int i2){
    mDataResultList.Clear();
    std::vector<int> ids;
    GetPlayerIds(ids);
    TheRockCentral.GetAccLeaderboardByRankRange(ids, mGoal, i1, i1 + i2, mDataResultList, this);
}

void PlayerCampaignGoalLeaderboard::GetStats(){
    mDataResultList.Clear();
    std::vector<int> ids;
    GetPlayerIds(ids);
    TheRockCentral.GetAccMaxRank(ids, mGoal, mDataResultList, this);
}

PlayerCampaignCareerLeaderboard::PlayerCampaignCareerLeaderboard(Profile* p, Leaderboard::Callback* cb, ScoreType s, bool dlc) : PlayerLeaderboard(p, cb), mScoreType(s), mUseDLC(dlc) {

}

void PlayerCampaignCareerLeaderboard::EnumerateFromID(){
    mDataResultList.Clear();
    LeaderboardType ltype = mUseDLC ? kCareer : kCappedCareer;
    std::vector<int> ids;
    GetPlayerIds(ids);
    TheRockCentral.GetLeaderboardByPlayer(ids, 0, mScoreType, ltype, ModeToLeaderboardMode(mMode), sPageSize, mDataResultList, this);
}

void PlayerCampaignCareerLeaderboard::EnumerateRankRange(int i1, int i2){
    mDataResultList.Clear();
    LeaderboardType ltype = mUseDLC ? kCareer : kCappedCareer;
    std::vector<int> ids;
    GetPlayerIds(ids);
    TheRockCentral.GetLeaderboardByRankRange(ids, 0, mScoreType, i1, i1 + i2, ltype, mDataResultList, this);
}

void PlayerCampaignCareerLeaderboard::GetStats(){
    mDataResultList.Clear();
    LeaderboardType ltype = mUseDLC ? kCareer : kCappedCareer;
    std::vector<int> ids;
    GetPlayerIds(ids);
    TheRockCentral.GetMaxRank(ids, 0, mScoreType, ltype, mDataResultList, this);
}

void PlayerCampaignCareerLeaderboard::SetScoreType(ScoreType ty){
    if(ty != mScoreType){
        mScoreType = ty;
        CancelEnumerate();
        StartEnumerate();
    }
}