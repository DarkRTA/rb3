#pragma once
#include "bandobj/BandScoreboard.h"
#include "bandobj/TrackInstruments.h"
#include "bandobj/TrackPanelDirBase.h"
#include "bandobj/TrackPanelInterface.h"
#include "bandtrack/Track.h"
#include "game/BandUser.h"
#include "obj/Data.h"

class DepChecker;

class TrackPanel : public TrackPanelInterface {
public:
    class TrackSlot {
    public:
        TrackSlot() : mTrack(0), mInstrument(kInstNone) {}

        Track* mTrack; // 0x0
        TrackInstrument mInstrument; // 0x4
    };

    enum TourGoalConfig {
        kConfigScoreStars = 0,
        kConfigScoreStarsGoal = 1,
        kConfigScoreGoal = 2,
        kConfigStarsGoal = 3,
        kConfigGoal = 4,
        kConfigInvalid = 5
    };

    TrackPanel();
    OBJ_CLASSNAME(TrackPanel);
    OBJ_SET_TYPE(TrackPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~TrackPanel();
    virtual void Draw();
    virtual void Enter();    
    virtual void Exit();    
    virtual void Poll();    
    virtual void Unload();    
    virtual void FinishLoad();
    virtual void GetTrackOrder(std::vector<TrackInstrument>*, bool) const;
    virtual int GetTrackCount() const;
    virtual int GetNumPlayers() const;
    virtual bool InGame() const;
    virtual bool IsGameOver() const;
    virtual int GetNoCrowdMeter() const; // fix ret type
    virtual int GetGameExcitement() const; // fix ret type
    virtual void PushCrowdReaction(bool);
    virtual bool ShowApplauseMeter() const { return false; }
    virtual float CrowdRatingDefaultVal(Symbol) const;
    virtual bool ShouldUpdateScrollSpeed() const;
    virtual bool SlotReservedForVocals(int) const;
    virtual bool GameResumedNoScore() const;
    virtual bool AutoVocals() const { return mAutoVocals; }

    void CleanUpReloadChecks();
    Track* GetTrack();
    Track* GetTrack(Player*, bool);
    Track* GetTrack(BandUser*, bool);
    const BandUser* GetUserFromTrackNum(int);
    void Reload();
    void CleanUpTracks();
    void UpdateReservedVocalSlot();
    void CreateTracks();
    void Reset();
    void AssignAndInitTracks();
    void SetMainGoalConfiguration(TourGoalConfig);
    void MainGoalReset();
    void TrackerDisplayReset();
    void SetSuppressTambourineDisplay(bool);
    void AssignTrack(int);
    void HandleAddUser(BandUser*);
    void HandleAddPlayer(Player*);
    void DoHandleAddPlayer(BandUser*);
    void PostHandleAddPlayer(Player*);
    void DoPostHandleAddPlayer(BandUser*);
    void HandleRemoveUser(BandUser*);
    void PostHandleRemoveUser(BandUser*);
    void PlaySequence(const char*, float, float, float);
    void StopSequence(const char*, bool);
    void ShowMainGoalInfo(bool);
    void SendTrackerDisplayMessage(const Message&) const;
    void SendTrackerBroadcastDisplayMessage(const Message&) const;
    void TrackerDisplayReset() const;
    void StartPulseAnims();
    void SetSmasherGlowing(int, bool);

    DataArray* mConfig; // 0x38
    std::vector<Track*> mTracks; // 0x3c
    std::vector<TrackSlot> mTrackSlots; // 0x44
    int mReservedVocalSlot; // 0x4c
    ObjPtr<BandScoreboard, ObjectDir> mScoreboard; // 0x50
    bool unk5c; // 0x5c
    bool unk5d; // 0x5d
    bool unk5e; // 0x5e
    bool unk5f; // 0x5f
    bool unk60; // 0x60
    bool unk61; // 0x61
    bool unk62; // 0x62
    bool mAutoVocals; // 0x63
    std::map<Symbol, DepChecker*> unk64; // 0x64
    float unk7c;
    TrackPanelDirBase* mTrackPanelDir; // 0x80
    int unk84;
    TourGoalConfig mTourGoalConfig; // 0x88
    float unk8c;
};

TrackPanel* GetTrackPanel();
TrackPanelDirBase* GetTrackPanelDir();

extern TrackPanel* TheTrackPanel;