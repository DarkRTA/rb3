#pragma once
#include "bandtrack/TrackPanel.h"
#include "game/Defines.h"
#include "game/TrackerDisplay.h"
#include "game/TrackerSource.h"
#include "meta_band/GameplayOptions.h"
#include "game/BandUser.h"
#include "obj/Data.h"
#include "types.h"
#include "utl/Symbol.h"

enum TrackerType {
    kTrackerType_Undef = 0,
    kTrackerType_Accuracy = 1,
    kTrackerType_AccuracyFocus = 2,
    kTrackerType_CareerDeployCount = 3,
    kTrackerType_CareerFills = 4,
    kTrackerType_HopoCount = 5,
    kTrackerType_HopoPercent = 6,
    kTrackerType_Overdrive = 7,
    kTrackerType_OverdriveDeployCount = 8,
    kTrackerType_OverdriveTime = 9,
    kTrackerType_PerfectOverdrive = 10,
    kTrackerType_PerfectSection = 11,
    kTrackerType_Score = 12,
    kTrackerType_SoloButtonedSoloPercentage = 13,
    kTrackerType_Streak = 14,
    kTrackerType_StreakCount = 15,
    kTrackerType_StreakFocus = 16,
    kTrackerType_DeployCount = 17,
    kTrackerType_UnisonCount = 18,
    kTrackerType_UpstrumCount = 19,
    kTrackerType_UpstrumPercent = 20
};

class TrackerDesc {
public:
    TrackerDesc()
        : mType(kTrackerType_Undef), mUser(0), mName(gNullStr),
          unkc(TrackPanel::kConfigScoreStarsGoal), unk10(0), unk11(0), unk12(0), unk14(0),
          unk20(0), unk24(0) {}

    TrackerType mType; // 0x0
    LocalBandUser *mUser; // 0x4
    Symbol mName; // 0x08
    TrackPanel::TourGoalConfig unkc; // 0x0c
    bool unk10; // 0x10
    bool unk11; // 0x11
    bool unk12; // 0x12
    float unk14; // 0x14
    std::vector<float> unk18; // 0x18
    bool unk20; // 0x20
    const DataArray *unk24; // 0x24
};

class Tracker {
public:
    Tracker(TrackerSource *, TrackerBandDisplay &, TrackerBroadcastDisplay &);
    virtual ~Tracker();
    virtual void TranslateRelativeTargets() {}
    virtual void UpdateGoalValueLabel(UILabel &) const;
    virtual void UpdateCurrentValueLabel(UILabel &) const;
    virtual String GetPlayerContributionString(Symbol) const;
    virtual void RemoteEndStreak_(Player *, float, int) {}
    virtual void ConfigureTrackerSpecificData(const DataArray *) {}
    virtual void HandleAddPlayer_(Player *) {}
    virtual void HandleRemovePlayer_(Player *) {}
    virtual void HandlePlayerSaved_(const TrackerPlayerID &) {}
    virtual void HandleGameOver_(float) {}
    virtual void Restart_() {}
    virtual void FirstFrame_(float) {}
    virtual void Poll_(float) {}
    virtual void TargetSuccess(int) const {}
    virtual DataArrayPtr GetBroadcastDescription() const { return DataArrayPtr(); }
    virtual DataArrayPtr GetTargetDescription(int) const = 0;
    virtual TrackerChallengeType GetChallengeType() const {
        return (TrackerChallengeType)0;
    }
    virtual float GetCurrentValue() const = 0;
    virtual void SavePlayerStats() const = 0;

    void UpdateSource(TrackerSource *);
    void Restart();
    void HandleAddPlayer(Player *);
    void HandleRemovePlayer(Player *);
    int GetPlayerDisplayIndex(Player *) const;
    void HandlePlayerSaved(Player *);
    void HandleGameOver(float);
    float CalcProgressPercentage() const;
    void StartIntro();
    void Poll(float);
    void ReachedTargetLevel(int);
    void SetupDisplays();
    void Configure(const TrackerDesc &);
    void ReconcileStats();
    int GetTargetSuccessLevel() const;
    bool HasPlayerForInstrument(Symbol) const;
    bool ReachedAnyTarget() const;
    const TrackerPlayerDisplay &GetPlayerDisplay(const TrackerPlayerID &) const;
    void SetPlayerProgress(const TrackerPlayerID &, float);
    void LocalSetPlayerProgress(const TrackerPlayerID &, float);
    void RemoteSetPlayerProgress(Player *, float);
    void RemoteTrackerPlayerDisplay(Player *, int, int, int);
    void RemoteEndStreak(Player *, int, int);
    void SendEndStreak(Player *, float, int);

    bool mFirstPoll; // 0x4
    TrackerBandDisplay &mBandDisplay; // 0x8
    TrackerBroadcastDisplay &mBroadcastDisplay; // 0xc
    std::vector<TrackerPlayerDisplay> mPlayerDisplays; // 0x10
    TrackerDesc mDesc; // 0x18
    TrackerSource *mSource; // 0x40
    float unk44;
    Symbol unk48;
    Symbol unk4c;
    std::vector<float> mTargets; // 0x50
};
