#pragma once
#include "Tracker.h"
#include "TrackerDisplay.h"
#include "beatmatch/TrackType.h"
#include "game/TrackerSource.h"
#include "game/TrackerUtils.h"

class PerfectOverdriveTracker : public Tracker {
public:
    class PlayerContribData {
    public:
        int unk0;
        int unk4;
        int unk8;
    };

    class PlayerStreakData {
    public:
        // PlayerStreakData() : unk0(-1.0f), unk4(0), unk5(0), unk6(0), unk8(0), unkc(0), unk10(0), unk14(-1), unk18(-1.0f), unk1c(0) {}

        float unk0;
        bool unk4;
        bool unk5;
        bool unk6;
        int unk8;
        int unkc;
        int unk10;
        int unk14;
        float unk18;
        int unk1c;
    };

    PerfectOverdriveTracker(TrackerSource*, TrackerBandDisplay&, TrackerBroadcastDisplay&);
    virtual ~PerfectOverdriveTracker();
    virtual void TranslateRelativeTargets();
    virtual void UpdateGoalValueLabel(UILabel&) const;
    virtual void UpdateCurrentValueLabel(UILabel&) const;
    virtual String GetPlayerContributionString(Symbol) const;
    virtual void RemoteEndStreak_(Player*, float, int);
    virtual void ConfigureTrackerSpecificData(const DataArray*);
    virtual void HandlePlayerSaved_(const TrackerPlayerID&);
    virtual void FirstFrame_(float);
    virtual void Poll_(float);
    virtual DataArrayPtr GetTargetDescription(int idx) const {
        return TrackerDisplay::MakeIntegerTargetDescription(mTargets[idx]);
    }
    virtual TrackerChallengeType GetChallengeType() const { return (TrackerChallengeType)2; }
    virtual float GetCurrentValue() const { return unk88; }
    virtual void SavePlayerStats() const;

    void LocalEndStreak(const TrackerPlayerID&, float, int);

    std::map<TrackType, PlayerContribData> unk58;
    std::map<TrackType, PlayerStreakData> unk70;
    float unk88;
    TrackerMultiplierMap unk8c;
};