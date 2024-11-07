#pragma once
#include "Tracker.h"
#include "game/TrackerSource.h"
#include "game/TrackerUtils.h"

class FocusTracker : public Tracker {
public:
    enum FocusFlags {

    };

    FocusTracker(TrackerSource*, TrackerBandDisplay&, TrackerBroadcastDisplay&);
    virtual ~FocusTracker();
    virtual void UpdateGoalValueLabel(UILabel&) const;
    virtual void UpdateCurrentValueLabel(UILabel&) const;
    virtual String GetPlayerContributionString(Symbol) const;
    virtual void ConfigureTrackerSpecificData(const DataArray*);
    virtual void HandleRemovePlayer_(Player*);
    virtual void HandlePlayerSaved_(const TrackerPlayerID&);
    virtual void HandleGameOver_(float);
    virtual void Restart_();
    virtual void FirstFrame_(float);
    virtual void Poll_(float);
    virtual void TargetSuccess(int) const;
    virtual DataArrayPtr GetTargetDescription(int) const;
    virtual float GetCurrentValue() const;
    virtual void SavePlayerStats() const;
    virtual void PlayerAddEnergy(Player*, float);
    virtual TrackerPlayerID GetNextFocusPlayer(const TrackerPlayerID&, float, bool&) const;
    virtual bool PlayerWantsFocus(const TrackerPlayerID&, float) const { return true; }
    virtual void CheckCondition(float, bool, bool&, bool&) = 0;
    virtual void FocusLeaving(FocusFlags){}
    virtual void HandleFocusSwitch(float){}
    virtual void BroadcastFocusSuccess() const {}
    virtual void BroadcastSuccess(int) const;
    virtual Symbol GetContributionToken(int) const;

    void RemoteSetFocusPlayer(Player*, int, int, FocusFlags);
    void SetFocusPlayer(const TrackerPlayerID&, float, FocusFlags);
    TrackerPlayerID GetFirstFocusPlayer(bool&) const;
    bool PlayerCanHaveFocus(const TrackerPlayerID&) const;
    void ActivateFocus(float);
    void LocalSetFocusPlayer(const TrackerPlayerID&, float, int, float, FocusFlags);
    void SetTrackFocus(const TrackerPlayerID&, bool, FocusFlags);

    float mFocusDelayMs; // 0x58
    bool unk5c;
    FocusFlags unk60; // 0x60
    TrackerPlayerID mFocusPlayer; // 0x64
    bool unk74;
    float unk78;
    float unk7c;
    float unk80;
    float unk84; // 0x84
    int unk88;
    int unk8c;
    std::map<TrackerPlayerID, int> mFocusCountMap; // 0x90
    TrackerMultiplierMap unka8; // 0xa8
    int unkc4;
    bool unkc8;
};