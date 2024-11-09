#pragma once
#include "Tracker.h"
#include "game/TrackerDisplay.h"
#include "game/TrackerSource.h"

class DeployCountTracker : public Tracker {
public:
    class PlayerDeployData {
    public:
        bool unk0;
        bool unk1;
        bool unk2;
        bool unk3;
        int unk4;
    };

    DeployCountTracker(TrackerSource*, TrackerBandDisplay&, TrackerBroadcastDisplay&);
    virtual ~DeployCountTracker();
    virtual void TranslateRelativeTargets();
    virtual void UpdateGoalValueLabel(UILabel&) const;
    virtual void UpdateCurrentValueLabel(UILabel&) const;
    virtual String GetPlayerContributionString(Symbol) const;
    virtual void ConfigureTrackerSpecificData(const DataArray*);
    virtual void FirstFrame_(float);
    virtual void Poll_(float);
    virtual DataArrayPtr GetTargetDescription(int) const;
    virtual TrackerChallengeType GetChallengeType() const { return (TrackerChallengeType)2; }
    virtual float GetCurrentValue() const { return mDeployCount; }
    virtual void SavePlayerStats() const;

    void RemoteDeploy(Player*);
    void LocalDeploy(const TrackerPlayerID&);

    std::map<TrackerPlayerID, PlayerDeployData> mDeployDataMap; // 0x58
    int mDeployCount; // 0x70
    bool mRequireFullEnergy; // 0x74
    bool mRequireMaxMultiplier; // 0x75
};