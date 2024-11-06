#ifndef GAME_TRACKER_H
#define GAME_TRACKER_H

#include "game/Defines.h"
#include "game/TrackerDisplay.h"
#include "game/TrackerSource.h"
#include "meta_band/GameplayOptions.h"
#include "game/BandUser.h"
#include "obj/Data.h"
#include "types.h"

struct TrackerDesc {
    int mType; // 0x0 - enum TrackerType
    LocalBandUser* mUser;  // 0x04 - LocalBandUser*
    Symbol symbol3;  // 0x08
    int unkc;        // 0x0c
    int unk10;
    float unk14;
    std::vector<float> unk18;
};

class Tracker {
public:
    Tracker(TrackerSource*, TrackerBandDisplay&, TrackerBroadcastDisplay&);
    virtual ~Tracker();
    virtual void TranslateRelativeTargets();
    virtual void UpdateGoalValueLabel(UILabel&) const;
    virtual void UpdateCurrentValueLabel(UILabel&) const;
    virtual String GetPlayerContributionString(Symbol) const;
    virtual void RemoteEndStreak_(Player*, float, int);
    virtual void ConfigureTrackerSpecificData(const DataArray*);
    virtual void HandleAddPlayer_(Player*);
    virtual void HandleRemovePlayer_(Player*);
    virtual void HandlePlayerSaved_(const TrackerPlayerID&);
    virtual void HandleGameOver_(float);
    virtual void Restart_();
    virtual void FirstFrame_(float){}
    virtual void Poll_(float){}
    virtual void TargetSuccess(int) const;
    virtual DataArrayPtr GetBroadcastDescription() const;
    virtual DataArrayPtr GetTargetDescription(int) const = 0;
    virtual int GetChallengeType() const;
    virtual float GetCurrentValue() const = 0;
    virtual void SavePlayerStats() const = 0;

    void UpdateSource(TrackerSource*);
    void Restart();
    void HandleAddPlayer(Player*);
    void HandleRemovePlayer(Player*);
    int GetPlayerDisplayIndex(Player*) const;
    void HandlePlayerSaved(Player*);
    void HandleGameOver(float);
    float CalcProgressPercentage() const;
    void StartIntro();
    void Poll(float);
    void ReachedTargetLevel(int);
    void SetupDisplays();
    void Configure(const TrackerDesc&);

    bool mFirstPoll; // 0x4
    TrackerBandDisplay& mBandDisplay; // 0x8
    TrackerBroadcastDisplay& mBroadcastDisplay; // 0xc
    std::vector<TrackerPlayerDisplay> mPlayerDisplays; // 0x10
    int unk18;
    int unk1c;
    Symbol unk20;
    int unk24;
    bool unk28;
    bool unk29;
    bool unk2a;
    float unk2c;
    std::vector<float> unk30;
    bool unk38;
    int unk3c;
    TrackerSource* mSource; // 0x40
    float unk44;
    Symbol unk48;
    Symbol unk4c;
    std::vector<float> unk50;
};

#endif // GAME_TRACKER_H