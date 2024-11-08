#pragma once
#include "Tracker.h"
#include "TrackerDisplay.h"
#include "game/TrackerSource.h"
#include "game/TrackerUtils.h"

class OverdriveTracker : public Tracker {
public:
    class DeployData {
    public:
        bool unk0;
        bool unk1;
    };

    OverdriveTracker(TrackerSource*, TrackerBandDisplay&, TrackerBroadcastDisplay&);
    virtual ~OverdriveTracker();
    virtual void TranslateRelativeTargets();
    virtual void UpdateGoalValueLabel(UILabel&) const;
    virtual void UpdateCurrentValueLabel(UILabel&) const;
    virtual String GetPlayerContributionString(Symbol) const;
    virtual void ConfigureTrackerSpecificData(const DataArray*);
    virtual void FirstFrame_(float);
    virtual void Poll_(float);
    virtual void TargetSuccess(int) const;
    virtual DataArrayPtr GetBroadcastDescription() const;
    virtual DataArrayPtr GetTargetDescription(int idx) const {
        return TrackerDisplay::MakeTimeTargetDescription(mTargets[idx]);
    }
    virtual TrackerChallengeType GetChallengeType() const { return (TrackerChallengeType)2; }
    virtual float GetCurrentValue() const { return unka0; }
    virtual void SavePlayerStats() const;

    void UpdateTimeRemainingDisplay();
    void LocalEndDeployStreak(float);
    void RemoteEndDeployStreak(Player*, int);

    std::map<TrackerPlayerID, DeployData> unk58; // 0x58
    TrackerMultiplierMap unk70; // 0x70
    float unk8c;
    float unk90;
    float unk94;
    float unk98;
    float unk9c;
    float unka0;
    float unka4;
    int unka8;
    float unkac;
    bool unkb0; // 0xb0
};