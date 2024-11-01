#pragma once
#include "meta_band/CampaignLeaderboards.h"
#include "ui/UIPanel.h"

class CampaignGoalsLeaderboardPanel : public Leaderboard::Callback, public UIPanel {
public:
    CampaignGoalsLeaderboardPanel();
    virtual ~CampaignGoalsLeaderboardPanel(){}
    virtual void EnumerationStarted();
    virtual void ResultSuccess(bool, bool, bool);
    virtual void ResultFailure();
    OBJ_CLASSNAME(CampaignGoalsLeaderboardPanel);
    OBJ_SET_TYPE(CampaignGoalsLeaderboardPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Enter();
    virtual void Load();
    virtual void Unload();

    void UpdateProvider();
    void SetGoal(Symbol);
    Symbol GetGoalDescription() const;
    Symbol GetGoalUnits() const;
    const char* GetGoalIcon() const;
    void CycleMode();
    Symbol GetModeSymbol() const { return mCampaignGoalsLeaderboardProvider->GetModeSymbol(); }

    PlayerCampaignGoalLeaderboard* mCampaignGoalsLeaderboardProvider; // 0x3c
    Symbol mGoal; // 0x40
};