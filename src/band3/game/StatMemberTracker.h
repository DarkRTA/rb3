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
    virtual float GetCurrentValue() const { return mLastValue; }
    virtual void SavePlayerStats() const;
    virtual bool IsBandWideCummulative() const = 0;
    virtual bool IsPercentageStat() const { return false; }
    virtual float GetStatValue(const Stats&) const = 0;
    virtual Symbol GetGoalValueSymbol() const = 0;
    virtual Symbol GetCurrentValueSymbol() const = 0;
    virtual Symbol GetContributionSymbol() const = 0;
    virtual Symbol GetSingularContributionSymbol() const;

    float CalcCurrentStat() const;

    float mLastValue; // 0x58
};

#include "utl/Symbols.h"

class UnisonStatMemberTracker : public StatMemberTracker {
public:
    UnisonStatMemberTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : StatMemberTracker(src, banddisp, bcdisp) {}
    virtual ~UnisonStatMemberTracker(){}
    virtual void TranslateRelativeTargets();
    virtual void FirstFrame_(float);    
    virtual bool IsBandWideCummulative() const { return false; }
    virtual float GetStatValue(const Stats& stats) const { return stats.mUnisonPhraseCompleted; }
    virtual Symbol GetGoalValueSymbol() const { return ""; }
    virtual Symbol GetCurrentValueSymbol() const { return ""; }
    virtual Symbol GetContributionSymbol() const { return unison_stat_tracker_contribution; }
};

class HopoStatMemberTracker : public StatMemberTracker {
public:
    HopoStatMemberTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : StatMemberTracker(src, banddisp, bcdisp) {}
    virtual ~HopoStatMemberTracker(){}
    virtual bool IsBandWideCummulative() const { return true; }
    virtual float GetStatValue(const Stats& stats) const { return stats.mHopoGemsHopoed; }
    virtual Symbol GetGoalValueSymbol() const { return ""; }
    virtual Symbol GetCurrentValueSymbol() const { return ""; }
    virtual Symbol GetContributionSymbol() const { return hopo_stat_tracker_contribution; }
};

class DeployStatMemberTracker : public StatMemberTracker {
public:
    DeployStatMemberTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : StatMemberTracker(src, banddisp, bcdisp) {}
    virtual ~DeployStatMemberTracker(){}
    virtual bool IsBandWideCummulative() const { return true; }
    virtual float GetStatValue(const Stats& stats) const { return stats.mDeployCount; }
    virtual Symbol GetGoalValueSymbol() const { return ""; }
    virtual Symbol GetCurrentValueSymbol() const { return ""; }
    virtual Symbol GetContributionSymbol() const { return deploy_stat_tracker_contribution; }
    virtual Symbol GetSingularContributionSymbol() const { return deploy_stat_tracker_contribution_1; }
};

class FillsHitStatMemberTracker : public StatMemberTracker {
public:
    FillsHitStatMemberTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : StatMemberTracker(src, banddisp, bcdisp) {}
    virtual ~FillsHitStatMemberTracker(){}
    virtual bool IsBandWideCummulative() const { return false; }
    virtual float GetStatValue(const Stats& stats) const { return stats.mFillHitCount; }
    virtual Symbol GetGoalValueSymbol() const { return ""; }
    virtual Symbol GetCurrentValueSymbol() const { return ""; }
    virtual Symbol GetContributionSymbol() const { return ""; }
};