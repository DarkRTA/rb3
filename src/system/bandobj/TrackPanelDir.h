#pragma once
#include "bandobj/TrackPanelDirBase.h"

class TrackPanelDir : public TrackPanelDirBase {
public:
    TrackPanelDir();
    OBJ_CLASSNAME(TrackPanelDir)
    OBJ_SET_TYPE(TrackPanelDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~TrackPanelDir();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void ConfigureTracks(bool);
    virtual void ConfigureTrack(int);
    virtual void AssignTracks();
    virtual void AssignTrack(int, TrackInstrument, bool);
    virtual void RemoveTrack(int);
    virtual void SetConfiguration(Hmx::Object*, bool);
    virtual void ReapplyConfiguration(bool);
    virtual void Reset();
    virtual void ResetAll();
    virtual void PlayIntro();
    virtual bool TracksExtended() const;
    virtual void GameOver();
    virtual void HideScore();
    virtual void Coda();
    virtual void CodaEnd();
    virtual void SetCodaScore(int);
    virtual void SoloEnd(BandTrack*, int, Symbol);
    virtual void SetTrackPanel(TrackPanelInterface*);
    virtual void ResetPlayers();
    virtual void StartFinale();
    virtual void SetMultiplier(int, bool);
    virtual void SetCrowdRating(float);
    virtual void CodaSuccess();
    virtual void UnisonStart(int);
    virtual void UnisonEnd();
    virtual void UnisonSucceed();
    virtual int GetEndingBonus(); // ptr to EndingBonus*
    virtual int GetCrowdMeter(); // ptr
    virtual void SetupApplauseMeter(int, const char*, const char*, RndDir*, RndDir*, bool, Symbol);
    virtual void DisablePlayer(int, bool);
    virtual void EnablePlayer(int);
    virtual void FadeBotbBandNames(bool);
    virtual void CleanUpChordMeshes();
    virtual void SetApplauseMeterScale(int, int);
    virtual void StartPulseAnims(float);
    virtual int GetGemTrackResourceManager() const; // also a ptr

    int unk244; // 0x244
    int unk248; // 0x248
    int unk24c; // 0x24c
    int unk250; // 0x250
    // ObjPtr<VocalTrackDir>
};