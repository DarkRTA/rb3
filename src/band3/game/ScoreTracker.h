#pragma once
#include "Tracker.h"

class ScoreTracker : public Tracker {
public:
    ScoreTracker(TrackerSource*, TrackerBandDisplay&, TrackerBroadcastDisplay&);
    virtual ~ScoreTracker();
    virtual void UpdateCurrentValueLabel(UILabel&) const {}
    virtual void UpdateGoalValueLabel(UILabel&) const {}
    virtual void FirstFrame_(float);
    virtual void Poll_(float);
    virtual DataArrayPtr GetTargetDescription(int) const;
    virtual float GetCurrentValue() const { return unk58; }
    virtual void SavePlayerStats() const;

    int unk58; // 0x58
};