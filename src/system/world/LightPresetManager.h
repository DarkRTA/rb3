#pragma once
#include "obj/Data.h"
#include "world/LightPreset.h"
#include <map>

class WorldDir;

class LightPresetManager {
public:
    LightPresetManager(WorldDir *);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~LightPresetManager();

    void Enter();
    void Reset();
    void Poll();
    void SyncObjects();
    void SendLightingMessage(Symbol);
    void UpdateOverlay();
    void StartPreset(LightPreset *, bool);
    void SetPresetsEquivalent(bool);
    void GetPresets(LightPreset *&, LightPreset *&);
    void ReportError();
    void SchedulePstKey(LightPreset::KeyframeCmd);
    void Interp(Symbol, Symbol, float);
    void ForcePreset(LightPreset *, float);
    void ForcePresets(LightPreset *, LightPreset *, float);
    void StompPresets(LightPreset *, LightPreset *);
    void SelectPreset(LightPreset *, bool);
    void SetLighting(Symbol, bool);
    LightPreset *PickRandomPreset(Symbol);

    NEW_POOL_OVERLOAD(LightPresetManager)
    DELETE_POOL_OVERLOAD(LightPresetManager)

    DataNode OnToggleLightingEvents(DataArray *);
    DataNode OnForcePreset(DataArray *);
    DataNode OnForceTwoPresets(DataArray *);

    std::map<Symbol, std::vector<LightPreset *> > mPresets; // 0x4
    Symbol mLastCategory; // 0x1c
    WorldDir *mParent; // 0x20
    LightPreset *mPresetOverride; // 0x24
    LightPreset *mPresetNew; // 0x28
    LightPreset *mPresetPrev; // 0x2c
    float unk30; // 0x30
    float unk34; // 0x34
    float unk38; // 0x38
    bool unk3c; // 0x3c
    float mBlend; // 0x40
    float unk44; // 0x44
    int unk48; // 0x48
    bool mIgnoreLightingEvents; // 0x4c
};
