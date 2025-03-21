#pragma once
#include "bandtrack/TrackConfig.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "rndobj/Mesh.h"
#include <vector>

class GemRepTemplate {
public:
    enum TailType {
        type0,
        type1,
        kNumTailTypes
    };

    GemRepTemplate(const TrackConfig &);
    ~GemRepTemplate();
    void Init(ObjectDir *);
    RndMesh *GetTail();
    void ReturnTail(RndMesh *);
    RndMesh *CreateTail();
    int GetRequiredVertCount(int) const;
    int GetRequiredFaceCount(int) const;
    RndMat *GetMatByTag(const char *, int);
    void SetupTailVerts();
    int GetNumTailSections(TailType) const;
    float GetTailSectionLength(TailType) const;
    RndMat *GetSlotMat(int, int) const;
    void SetSlotMat(int, int, RndMat *);

    RndMat *GetTailMiss() const { return mTailMiss; }
    RndMat *GetTailBonus() const { return mTailBonus; }
    RndMat *GetTailChord() const { return mTailChord; }
    float GetTailScaleX() const { return mTailScaleX; }

    DataArray *mConfig; // 0x0
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
    const TrackConfig &mTrackCfg; // 0x34
    RndMat **mSlotMats; // 0x38
    float mTailClipY; // 0x3c
    float mTailScaleX; // 0x40
    ObjectDir *mObjectDir; // 0x44
    int mNumTailSections[2]; // 0x48
    float mTailSectionLength[2]; // 0x50
    RndMesh::VertVector mTailVerts; // 0x58
    RndMesh::VertVector mCapVerts; // 0x64
    RndMat *mTailMiss; // 0x70
    RndMat *mTailBonus; // 0x74
    RndMat *mTailChord; // 0x78
    std::vector<RndMesh *> mTails; // 0x7C
};
