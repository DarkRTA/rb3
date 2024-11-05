#pragma once
#include "bandobj/BandScoreboard.h"
#include "bandobj/TrackPanelInterface.h"
#include "bandtrack/Track.h"
#include "obj/Data.h"

class DepChecker;

class TrackPanel : public TrackPanelInterface {
public:
    class TrackSlot {
    public:
        TrackSlot() : unk0(0), unk4(-1) {}
        int unk0;
        int unk4;
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

    DataArray* mConfig; // 0x38
    std::vector<Track*> mTracks; // 0x3c
    std::vector<TrackSlot> mTrackSlots; // 0x44
    int unk4c; // 0x4c
    ObjPtr<BandScoreboard, ObjectDir> unk50; // 0x50
    bool unk5c;
    bool unk5d;
    bool unk5e;
    bool unk5f;
    bool unk60;
    bool unk61;
    bool unk62;
    bool mAutoVocals; // 0x63
    std::map<Symbol, DepChecker*> unk64;
    float unk7c;
    int unk80;
    int unk84;
    int unk88;
    float unk8c;
};

TrackPanel* GetTrackPanel();

extern TrackPanel* TheTrackPanel;