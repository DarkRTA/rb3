#pragma once
#include "obj/Object.h"
#include "bandobj/CrowdMeterIcon.h"
#include "bandobj/TrackPanelDirBase.h"

class BandTrack : public virtual Hmx::Object {
public:
    BandTrack(Hmx::Object*);
    OBJ_CLASSNAME(BandTrack);
    OBJ_SET_TYPE(BandTrack);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Reset();
    virtual void TrackReset();
    virtual void ResetSmashers(bool);
    virtual void Retract(bool);
    virtual void Extend(bool);
    virtual void SpotlightPhraseSuccess();
    virtual void SetStreak(int, int, int, bool);
    virtual void Deploy();
    virtual void StopDeploy();
    virtual void EnterCoda();
    virtual void PlayIntro();
    virtual void DisablePlayer(int);
    virtual void SavePlayer();
    virtual void SuperStreak(bool, bool);
    virtual void PeakState(bool, bool);
    virtual void SetTambourine(bool);
    virtual void SetPlayerLocal(float);
    virtual void SetHasTrackerFocus(bool);
    virtual int ThisDir(); // fix ptr
    virtual int ThisDir() const; // fix ptr
    virtual int AsGemTrackDir();
    virtual int AsVocalTrackDir();
    virtual int AsRndDir();
    virtual void RefreshStreakMeter(int, int, int);
    virtual void RefreshOverdrive(float, bool);
    virtual void RefreshCrowdRating(float, CrowdMeterState);
    virtual void StartPulseAnims(float);
    virtual void SetupInstrument();
    virtual void SetPerformanceMode(bool);
    virtual void SetUsed(bool);
    virtual void SetInstrument(TrackInstrument);
    virtual void ResetEffectSelector();
    virtual void SetupSmasherPlate();
    virtual void ReleaseSmasherPlate();
    virtual void TutorialReset();
    virtual ~BandTrack();

    bool unk8;
    bool unk9;
    Symbol unkc;
    int unk10;
    int unk14;
    bool unk18;
    bool unk19;
    bool unk1a;
    bool unk1b;
    bool unk1c;
    bool unk1d;
    bool unk1e;
    bool unk1f;
};