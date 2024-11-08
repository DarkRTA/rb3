#pragma once
#include "Tracker.h"

class StatMemberTracker : public Tracker {
public:
    StatMemberTracker(TrackerSource*, TrackerBandDisplay&, TrackerBroadcastDisplay&);
    virtual ~StatMemberTracker();
    virtual void UpdateGoalValueLabel(UILabel&) const;
    virtual void UpdateCurrentValueLabel(UILabel&) const;
    virtual String GetPlayerContributionString(Symbol) const;
    virtual void FirstFrame_(float);
    virtual void Poll_(float);
    virtual DataArrayPtr GetTargetDescription(int) const;
    virtual float GetCurrentValue() const;
    virtual void SavePlayerStats() const;
    virtual bool IsBandWideCummulative() const = 0;
    virtual bool IsPercentageStat() const { return false; }
    virtual float GetStatValue(const Stats&) const = 0;
    virtual Symbol GetGoalValueSymbol() const = 0;
    virtual Symbol GetCurrentValueSymbol() const = 0;
    virtual Symbol GetContributionSymbol() const = 0;
    virtual Symbol GetSingularContributionSymbol() const;

    float CalcCurrentStat() const;

    float unk58; // 0x58
};