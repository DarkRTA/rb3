#pragma once
#include "game/Defines.h"
#include "meta_band/CampaignLeaderboards.h"
#include "ui/UIPanel.h"

class CampaignCareerLeaderboardPanel : public Leaderboard::Callback, public UIPanel {
public:
    CampaignCareerLeaderboardPanel();
    virtual ~CampaignCareerLeaderboardPanel(){}
    virtual void EnumerationStarted();
    virtual void ResultSuccess(bool, bool, bool);
    virtual void ResultFailure();
    OBJ_CLASSNAME(CampaignCareerLeaderboardPanel);
    OBJ_SET_TYPE(CampaignCareerLeaderboardPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Enter();
    virtual void Unload();
    virtual void Load();

    void UpdateProvider();
    void SetScoreType(ScoreType);
    Symbol GetScoreType() const;
    void SetUseDLC(bool);
    void CycleMode();
    
    PlayerCampaignCareerLeaderboard* mCampaignCareerLeaderboardProvider; // 0x3c
    ScoreType mScoreType; // 0x40
    bool mUseDLC; // 0x44
};

