#pragma once
#include "game/Metronome.h"
#include "game/VocalGuidePitch.h"
#include "synth/Faders.h"
#include "ui/UIPanel.h"

class PracticePanel : public UIPanel {
public:
    PracticePanel();
    OBJ_CLASSNAME(PracticePanel);
    OBJ_SET_TYPE(PracticePanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~PracticePanel();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;
    virtual void FinishLoad();

    bool PlayAllTracks() const;
    void OnFadeSongIn(float);
    void OnFadeSongOut(float);
    bool IsDrums() const;
    void SetRestartAllowed(bool);
    void MarkGemsAsProcessed();
    bool HasPlayer() const;
    bool IsVocals() const;
    void GetSectionBounds(float &, float &) const;
    void SetPlayAllTracks(bool);
    void SetPitchShiftRatio(float);
    bool InVocalMode() const;
    void PracticeMetronome(Symbol);
    void StopMics();

    bool mInVocalMode; // 0x38
    Fader *mFader; // 0x3c
    float unk40; // 0x40
    bool mPlayAllTracks; // 0x44
    VocalGuidePitch *mGuidePitch; // 0x48
    int unk4c;
    int unk50;
    bool unk54;
    bool unk55;
    bool unk56;
    bool unk57;
    bool unk58;
    bool unk59;
    int unk5c;
    bool unk60;
    Metronome *mMetronome; // 0x64
};

extern PracticePanel *ThePracticePanel;