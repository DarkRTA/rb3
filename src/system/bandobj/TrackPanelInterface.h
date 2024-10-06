#pragma once
#include "ui/UIPanel.h"
#include "bandobj/TrackPanelDirBase.h"

class TrackPanelInterface : public UIPanel {
public:
    TrackPanelInterface(){}
    virtual ~TrackPanelInterface(){}
    virtual void GetTrackOrder(std::vector<TrackInstrument>*, bool) const = 0;
    virtual int GetTrackCount() const = 0;
    virtual int GetNumPlayers() const = 0;
    virtual bool InGame() const = 0;
    virtual bool IsGameOver() const = 0;
    virtual int GetNoCrowdMeter() const = 0; // fix ret type
    virtual int GetGameExcitement() const = 0; // fix ret type
    virtual void PushCrowdReaction(bool) = 0;
    virtual bool ShowApplauseMeter() const = 0;
    virtual float CrowdRatingDefaultVal(Symbol) const = 0;
    virtual bool ShouldUpdateScrollSpeed() const = 0;
    virtual bool SlotReservedForVocals(int) const = 0;
    virtual bool GameResumedNoScore() const = 0;
    virtual bool AutoVocals() const = 0;
};