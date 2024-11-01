#pragma once
#include "game/Defines.h"
#include "meta_band/PlayerLeaderboards.h"

class PlayerCampaignGoalLeaderboard : public PlayerLeaderboard {
public:
    PlayerCampaignGoalLeaderboard(Profile*, Callback*, Symbol);
    virtual ~PlayerCampaignGoalLeaderboard(){}
    virtual void EnumerateFromID();
    virtual void EnumerateRankRange(int, int);
    virtual void GetStats();

    Symbol mGoal; // 0x84
};

class PlayerCampaignCareerLeaderboard : public PlayerLeaderboard {
public:
    PlayerCampaignCareerLeaderboard(Profile*, Callback*, ScoreType, bool);
    virtual ~PlayerCampaignCareerLeaderboard(){}
    virtual void EnumerateFromID();
    virtual void EnumerateRankRange(int, int);
    virtual void GetStats();

    void SetScoreType(ScoreType);

    ScoreType mScoreType; // 0x84
    bool mUseDLC; // 0x88
};