#pragma once
#include "Tracker.h"
#include "game/TrackerSource.h"
#include "game/TrackerUtils.h"
#include "utl/Symbols.h"

class FocusTracker : public Tracker {
public:
    enum FocusFlags {
    };

    FocusTracker(TrackerSource *, TrackerBandDisplay &, TrackerBroadcastDisplay &);
    virtual ~FocusTracker();
    virtual void UpdateGoalValueLabel(UILabel &) const;
    virtual void UpdateCurrentValueLabel(UILabel &) const;
    virtual String GetPlayerContributionString(Symbol) const;
    virtual void ConfigureTrackerSpecificData(const DataArray *);
    virtual void HandleRemovePlayer_(Player *);
    virtual void HandlePlayerSaved_(const TrackerPlayerID &);
    virtual void HandleGameOver_(float);
    virtual void Restart_();
    virtual void FirstFrame_(float);
    virtual void Poll_(float);
    virtual void TargetSuccess(int) const;
    virtual DataArrayPtr GetTargetDescription(int) const;
    virtual float GetCurrentValue() const { return unk84; }
    virtual void SavePlayerStats() const;
    virtual void PlayerAddEnergy(Player *, float) {}
    virtual TrackerPlayerID
    GetNextFocusPlayer(const TrackerPlayerID &, float, bool &) const;
    virtual bool PlayerWantsFocus(const TrackerPlayerID &, float) const { return true; }
    virtual void CheckCondition(float, bool, bool &, bool &) = 0;
    virtual void FocusLeaving(FocusFlags) {}
    virtual void HandleFocusSwitch(float) {}
    virtual void BroadcastFocusSuccess() const {}
    virtual void BroadcastSuccess(int) const {}
    virtual Symbol GetContributionToken(int) const;

    void RemoteSetFocusPlayer(Player *, int, int, FocusFlags);
    void SetFocusPlayer(const TrackerPlayerID &, float, FocusFlags);
    TrackerPlayerID GetFirstFocusPlayer(bool &) const;
    bool PlayerCanHaveFocus(const TrackerPlayerID &) const;
    void ActivateFocus(float);
    void LocalSetFocusPlayer(const TrackerPlayerID &, float, int, float, FocusFlags);
    void SetTrackFocus(const TrackerPlayerID &, bool, FocusFlags);

    float mFocusDelayMs; // 0x58
    bool mInFocusDelay; // 0x5c
    FocusFlags mFocusFlags; // 0x60
    TrackerPlayerID mFocusPlayer; // 0x64
    bool unk74; // 0x74
    float unk78; // 0x78
    float unk7c; // 0x7c
    float unk80; // 0x80
    float unk84; // 0x84
    int unk88; // 0x88
    int unk8c; // 0x8c
    std::map<TrackerPlayerID, int> mFocusCountMap; // 0x90
    TrackerMultiplierMap unka8; // 0xa8
    int unkc4; // 0xc4
    bool unkc8; // 0xc8
};

class StreakFocusTracker : public FocusTracker {
public:
    StreakFocusTracker(TrackerSource *, TrackerBandDisplay &, TrackerBroadcastDisplay &);
    virtual ~StreakFocusTracker() {}
    virtual void TranslateRelativeTargets();
    virtual void ConfigureTrackerSpecificData(const DataArray *);
    virtual DataArrayPtr GetBroadcastDescription() const;
    virtual TrackerChallengeType GetChallengeType() const {
        return (TrackerChallengeType)3;
    }
    virtual TrackerPlayerID
    GetNextFocusPlayer(const TrackerPlayerID &, float, bool &) const;
    virtual bool PlayerWantsFocus(const TrackerPlayerID &, float) const;
    virtual void CheckCondition(float, bool, bool &, bool &);
    virtual void HandleFocusSwitch(float);
    virtual void BroadcastFocusSuccess() const;
    virtual void BroadcastSuccess(int) const;
    virtual Symbol GetContributionToken(int fmt) const {
        if (fmt == 1)
            return tour_goal_band_streak_player_contribution_format_1;
        else
            return tour_goal_band_streak_player_contribution_format;
    }

    float unkcc;
    int unkd0;
    float unkd4;
    int unkd8;
    int unkdc;
    int unke0;
    bool unke4;
    std::map<TrackerPlayerID, int> unke8;
};

class AccuracyFocusTracker : public FocusTracker {
public:
    AccuracyFocusTracker(TrackerSource *, TrackerBandDisplay &, TrackerBroadcastDisplay &);
    virtual ~AccuracyFocusTracker() {}
    virtual void TranslateRelativeTargets();
    virtual void ConfigureTrackerSpecificData(const DataArray *);
    virtual DataArrayPtr GetBroadcastDescription() const;
    virtual TrackerChallengeType GetChallengeType() const {
        return (TrackerChallengeType)1;
    }
    virtual bool PlayerWantsFocus(const TrackerPlayerID &, float) const;
    virtual void CheckCondition(float, bool, bool &, bool &);
    virtual void FocusLeaving(FocusFlags);
    virtual void HandleFocusSwitch(float);
    virtual void BroadcastFocusSuccess() const;

    int unkcc;
    float mRequiredAccuracy; // 0xd0
    int unkd4;
    int unkd8;
    int unkdc;
    int unke0;
    float unke4;
    bool unke8;
    TrackerSectionManager mSectionManager; // 0xec
};