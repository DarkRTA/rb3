#pragma once
#include "Tracker.h"
#include "TrackerDisplay.h"
#include "beatmatch/TrackType.h"
#include "game/TrackerUtils.h"

class PerfectSectionTracker : public Tracker {
public:
    class PlayerStreakData {
    public:
        int unk0;
        int unk4;
        int unk8;
        int unkc;
        float unk10;
        int unk14;
        bool unk18;
        bool unk19;
        int unk1c;
    };

    class SectionData {
    public:
        SectionData() : unk0(0), unk4(0), unk8(0), unkc(0) {}

        int unk0;
        int unk4;
        int unk8;
        float unkc;
    };

    enum SectionFlags {
    };

    PerfectSectionTracker(TrackerSource *, TrackerBandDisplay &, TrackerBroadcastDisplay &);
    virtual ~PerfectSectionTracker();
    virtual void TranslateRelativeTargets();
    virtual void UpdateGoalValueLabel(UILabel &) const;
    virtual void UpdateCurrentValueLabel(UILabel &) const;
    virtual String GetPlayerContributionString(Symbol) const;
    virtual void ConfigureTrackerSpecificData(const DataArray *);
    virtual void HandlePlayerSaved_(const TrackerPlayerID &);
    virtual void FirstFrame_(float);
    virtual void Poll_(float);
    virtual DataArrayPtr GetBroadcastDescription() const;
    virtual DataArrayPtr GetTargetDescription(int idx) const {
        return TrackerDisplay::MakeIntegerTargetDescription(mTargets[idx]);
    }
    virtual TrackerChallengeType GetChallengeType() const {
        return (TrackerChallengeType)1;
    }
    virtual float GetCurrentValue() const { return unkb4; }
    virtual void SavePlayerStats() const;

    void RemoteSectionComplete(Player *, int, int, int);
    void LocalSectionComplete(const TrackerPlayerID &, int, SectionFlags, float);
    void CheckForCompletedSections();
    void HandleEnterExtent(float, int, bool);
    void HandleInExtent(float, int);
    void HandleExitExtent(float, int, bool);

    const char *unk58; // 0x58
    std::map<TrackType, PlayerStreakData> unk5c; // 0x5c
    std::map<TrackType, bool> unk74; // 0x74
    std::map<TrackType, int> unk8c; // 0x8c
    std::vector<SectionData> mSectionData; // 0xa4
    int unkac;
    float unkb0;
    float unkb4;
    int unkb8;
    float unkbc;
    bool unkc0;
    int unkc4;
    int unkc8;
    String unkcc;
    String unkd8;
    bool unke4;
    bool unke5;
    TrackerMultiplierMap unke8;
    TrackerSectionManager unk104;
};