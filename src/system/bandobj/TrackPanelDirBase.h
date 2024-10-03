#pragma once
#include "ui/PanelDir.h"

class BandTrack;
class TrackPanelInterface;
class GemTrackResourceManager;
class EndingBonus;
class BandCrowdMeter;

enum TrackInstrument {
    kInstGuitar = 0,
    kInstDrum = 1,
    kInstBass = 2,
    kInstVocals = 3,
    kInstKeys = 4,
    kInstRealGuitar = 5,
    kInstRealBass = 6,
    kInstRealKeys = 7,
    kNumTrackInstruments = 8,
    kInstPending = -2,
    kInstNone = -1
};

class TrackPanelDirBase : public PanelDir {
public:
    TrackPanelDirBase();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~TrackPanelDirBase(){}
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
    virtual void ResetAll(){}
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
    virtual void StartFinale(){}
    virtual void SetMultiplier(int, bool);
    virtual void SetCrowdRating(float);
    virtual void CodaSuccess();
    virtual void UnisonStart(int){}
    virtual void UnisonEnd();
    virtual void UnisonSucceed();
    virtual EndingBonus* GetEndingBonus();
    virtual BandCrowdMeter* GetCrowdMeter(); // ptr
    virtual void SetupApplauseMeter(int, const char*, const char*, RndDir*, RndDir*, bool, Symbol){}
    virtual void DisablePlayer(int, bool);
    virtual void EnablePlayer(int);
    virtual void FadeBotbBandNames(bool){}
    virtual void CleanUpChordMeshes();
    virtual void SetApplauseMeterScale(int, int){}
    virtual void StartPulseAnims(float);
    virtual float GetPulseAnimStartDelay(bool) const;
    virtual GemTrackResourceManager* GetGemTrackResourceManager() const { return 0; }

    void SetShowing(bool);
    bool ModifierActive(Symbol);

    DataNode DataForEachConfigObj(DataArray*);

    DECLARE_REVS;

    float mViewTimeEasy; // 0x1d8
    float mViewTimeExpert; // 0x1dc
    float mNetTrackAlpha; // 0x1e0
    float mPulseOffset; // 0x1e4
    ObjPtr<Hmx::Object, ObjectDir> mConfiguration; // 0x1e8
    ObjPtrList<RndTransformable, ObjectDir> mConfigurableObjects; // 0x1f4
    std::vector<int> unk204; // 0x204
    ObjVector<int> unk20c; // 0x20c - BandSlot?
    ObjVector<int> unk21c; // 0x21c - BandTrack*
    bool unk224; // 0x224
    int unk228; // 0x228
    ObjPtr<RndDir, ObjectDir> unk22c; // 0x22c
    int unk238; // 0x238
    int unk23c; // 0x23c
    bool unk240; // 0x240
    bool mDoubleSpeedActive; // 0x241
    bool mIndependentTrackSpeeds; // 0x242
};