#pragma once
#include "Tracker.h"
#include "TrackerDisplay.h"
#include "game/Band.h"
#include "game/Player.h"
#include "tour/TourGameRules.h"

class TrackerSource;

class TrackerManager {
public:
    TrackerManager(Band*);
    ~TrackerManager();

    void ForceStars(int);
    void Restart();
    TrackerSource* CreateSource(const TrackerDesc&) const;
    void HandleAddPlayer(Player*);
    void HandleRemovePlayer(Player*);
    void HandleGameOver(float);
    void StartIntro();
    void Poll(float);
    void ConfigureGoals();
    void ConfigureQuestGoal();
    void ConfigureAccomplishmentGoal();
    TrackerType GetTrackerTypeFromGameType(TourGameType) const;
    void SetTracker(const TrackerDesc&);
    int GetQuestEarnedStars() const;
    void UpdateQuestGoalLabel(UILabel*) const;
    void UpdateQuestResultLabel(UILabel*) const;
    String GetPlayerContributionString(Symbol) const;
    void OnStatsSynced();
    void OnPlayerAddEnergy(Player*, float);
    void OnPlayerSaved(Player*);
    void OnPlayerQuarantined(Player*);
    void OnRemoteTrackerFocus(Player*, int, int, int);
    void OnRemoteTrackerPlayerProgress(Player*, float);
    void OnRemoteTrackerSectionComplete(Player*, int, int, int);
    void OnRemoteTrackerPlayerDisplay(Player*, int, int, int);
    void OnRemoteTrackerDeploy(Player*);
    void OnRemoteTrackerEndDeployStreak(Player*, int);
    void OnRemoteTrackerEndStreak(Player*, int, int);
    Tracker* MakeTracker(TrackerType, TrackerSource*);

    int unk0; // 0x0
    float unk4; // 0x4
    TrackerBandDisplay mBandDisplay; // 0x8
    TrackerBroadcastDisplay mBroadcastDisplay; // 0xc
    TrackerBandDisplayType mBandDisplayType; // 0x10
    TrackerBandDisplayStyle mBandDisplayStyle; // 0x14
    Band* mBand; // 0x18
    Tracker* mTracker; // 0x1c
    TrackerDesc mDesc; // 0x20
    bool unk48; // 0x48
    bool unk49; // 0x49
    float unk4c; // 0x4c
};