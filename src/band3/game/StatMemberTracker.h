#pragma once
#include "Player.h"
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

class HopoPercentStatMemberTracker : public StatMemberTracker {
public:
    HopoPercentStatMemberTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : StatMemberTracker(src, banddisp, bcdisp) {}
    virtual ~HopoPercentStatMemberTracker(){}
    virtual bool IsBandWideCummulative() const { return false; }
    virtual bool IsPercentageStat() const { return true; }
    virtual float GetStatValue(const Stats& stats) const { return stats.mHopoGemCount > 0 ? (int)(((float)stats.mHopoGemsHopoed / (float)stats.mHopoGemCount) * 100.0f) : -1.0f; }
    virtual Symbol GetGoalValueSymbol() const { return ""; }
    virtual Symbol GetCurrentValueSymbol() const { return ""; }
    virtual Symbol GetContributionSymbol() const { return hopo_percent_stat_tracker_contribution; }
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

class UpstrumStatMemberTracker : public StatMemberTracker {
public:
    UpstrumStatMemberTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : StatMemberTracker(src, banddisp, bcdisp) {}
    virtual ~UpstrumStatMemberTracker(){}
    virtual bool IsBandWideCummulative() const { return true; }
    virtual float GetStatValue(const Stats& stats) const { return stats.mUpstrumCount; }
    virtual Symbol GetGoalValueSymbol() const { return ""; }
    virtual Symbol GetCurrentValueSymbol() const { return ""; }
    virtual Symbol GetContributionSymbol() const { return upstrum_stat_tracker_contribution; }
};

class UpstrumPercentStatMemberTracker : public StatMemberTracker {
public:
    UpstrumPercentStatMemberTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : StatMemberTracker(src, banddisp, bcdisp) {}
    virtual ~UpstrumPercentStatMemberTracker(){}
    virtual bool IsBandWideCummulative() const { return false; }
    virtual bool IsPercentageStat() const { return true; }
    virtual float GetStatValue(const Stats& stats) const {
        if(stats.mHitCount + stats.m0x08 > 0){
            return stats.GetUpstrumPercent();
        }
        else return -1.0f;
    }
    virtual Symbol GetGoalValueSymbol() const { return ""; }
    virtual Symbol GetCurrentValueSymbol() const { return ""; }
    virtual Symbol GetContributionSymbol() const { return upstrum_percent_stat_tracker_contribution; }
};

class StreakCountStatMemberTracker : public StatMemberTracker {
public:
    StreakCountStatMemberTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : StatMemberTracker(src, banddisp, bcdisp) {}
    virtual ~StreakCountStatMemberTracker(){}
    virtual bool IsBandWideCummulative() const { return false; }
    virtual float GetStatValue(const Stats& stats) const {
        float streak = stats.GetLongestStreak();
        if(streak >= mTargets.front()){
            return Max<float>(streak, stats.GetCurrentStreak());
        }
        else return stats.GetCurrentStreak();
    }
    virtual Symbol GetGoalValueSymbol() const { return ""; }
    virtual Symbol GetCurrentValueSymbol() const { return ""; }
    virtual Symbol GetContributionSymbol() const { return streak_count_stat_tracker_contribution; }
};

class SoloButtonedSoloStatMemberTracker : public StatMemberTracker {
public:
    SoloButtonedSoloStatMemberTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : StatMemberTracker(src, banddisp, bcdisp) {}
    virtual ~SoloButtonedSoloStatMemberTracker(){}
    virtual bool IsBandWideCummulative() const { return false; }
    virtual bool IsPercentageStat() const { return true; }
    virtual float GetStatValue(const Stats& stats) const { return stats.mSoloButtonedSoloPercentage; }
    virtual Symbol GetGoalValueSymbol() const { return ""; }
    virtual Symbol GetCurrentValueSymbol() const { return ""; }
    virtual Symbol GetContributionSymbol() const { return solo_buttoned_solo_stat_tracker_contribution; }
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