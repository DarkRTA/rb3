#pragma once
#include "bandtrack/TrackConfig.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "rndobj/Mesh.h"
#include <vector>

class GemRepTemplate {
    enum TailType {
        type0,
        type1,
        kNumTailTypes
    };

    GemRepTemplate(const TrackConfig&);
    ~GemRepTemplate();
    void Init(ObjectDir*);
    RndMesh* GetTail();
    void ReturnTail(RndMesh*);
    RndMesh* CreateTail();
    int GetRequiredVertCount(int) const;
    int GetRequiredFaceCount(int) const;
    RndMat* GetMatByTag(const char*, int);
    void SetupTailVerts();
    int GetNumTailSections(TailType) const;
    float GetTailSectionLength(TailType) const;
    RndMat* GetSlotMat(int, int) const;
    void SetSlotMat(int, int, RndMat*);

    DataArray* mConfig; // 0x0
    float kTailPulseRate; // 0x4 // why is it k. why
    float kTailPulseSmoothing; // 0x8
    float kTailOffsetX; // 0xC
    float kTailMinAlpha; // 0x10
    float kTailMaxAlpha; // 0x14
    float kTailAlphaSmoothing; // 0x18
    float kTailFadeDistance; // 0x1C
    float kTailMaxLength; // 0x20
    Vector2 kTailFrequencyRange; // 0x24
    Vector2 kTailAmplitudeRange; // 0x2C  
    const TrackConfig& mTrackCfg; // 0x34
    RndMat** mSlots; // 0x38
    float unk_0x3C;
    float unk_0x40;
    ObjectDir* objectDir; // 0x44
    uint mNumTailSections;
    u32 pad1;
    float mTailSectionLen;
    u32 pad2;

    RndMesh::VertVector mTailVerts; // 0x58
    RndMesh::VertVector unk_0x64;

    int pad[3];

    std::vector<RndMesh*> mTails; // 0x7C
};
