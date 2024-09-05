#pragma once
#include "ui/PanelDir.h"

class BandTrack;
class TrackPanelInterface;

enum TrackInstrument {

};

class TrackPanelDirBase : public PanelDir {
public:
    TrackPanelDirBase();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~TrackPanelDirBase();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream& bs);
    virtual void Enter();
    virtual void ConfigureTracks(bool) = 0;
    virtual void ConfigureTrack(int) = 0;
    virtual void AssignTracks() = 0;
    virtual void AssignTrack(int, TrackInstrument, bool) = 0;
    virtual void RemoveTrack(int) = 0;
    virtual void SetConfiguration(Hmx::Object*, bool);
    virtual void ReapplyConfiguration(bool);
    virtual void Reset() = 0;
    virtual void ResetAll();
    virtual void PlayIntro();
    virtual bool TracksExtended() const;
    virtual void GameOver();
    virtual void HideScore();
    virtual void Coda() = 0;
    virtual void CodaEnd() = 0;
    virtual void SetCodaScore(int);
    virtual void SoloEnd(BandTrack*, int, Symbol) = 0;
    virtual void SetTrackPanel(TrackPanelInterface*);
    virtual void ResetPlayers();
    virtual void StartFinale();
    virtual void SetMultiplier(int, bool);
    virtual void SetCrowdRating(float);
    virtual void CodaSuccess();
    virtual void UnisonStart(int);
    virtual void UnisonEnd();
    virtual void UnisonSucceed();
    virtual int GetEndingBonus(); // prolly a ptr
    virtual int GetCrowdMeter(); // ptr
    virtual void SetupApplauseMeter(int, const char*, const char*, RndDir*, RndDir*, bool, Symbol);
    virtual void DisablePlayer(int, bool);
    virtual void EnablePlayer(int);
    virtual void FadeBotbBandNames(bool);
    virtual void CleanUpChordMeshes();
    virtual void SetApplauseMeterScale(int, int);
    virtual void StartPulseAnims(float);
    virtual float GetPulseAnimStartDelay(bool) const;
    virtual int GetGemTrackResourceManager() const; // also a ptr
};