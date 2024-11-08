#pragma once
#include "Tracker.h"

class AccuracyTracker : public Tracker {
public:
    AccuracyTracker(TrackerSource*, TrackerBandDisplay&, TrackerBroadcastDisplay&);
    virtual ~AccuracyTracker();
    virtual void UpdateGoalValueLabel(UILabel&) const;
    virtual void UpdateCurrentValueLabel(UILabel&) const;
    virtual String GetPlayerContributionString(Symbol) const;
    virtual void FirstFrame_(float);
    virtual void Poll_(float);
    virtual DataArrayPtr GetTargetDescription(int) const;
    virtual float GetCurrentValue() const { return mCurrentAccuracy; }
    virtual void SavePlayerStats() const;

    float mCurrentAccuracy; // 0x58
};