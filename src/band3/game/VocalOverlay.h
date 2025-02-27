#pragma once
#include "utl/Str.h"

class VocalPart;
class Singer;

class VocalOverlay {
public:
    VocalOverlay();
    ~VocalOverlay();
    void Reset(int);
    void AppendSingerPitch(int, float);
    void AddPossiblePart(int, VocalPart *);
    void EqualizeSingerStrings();
    void AppendAssignedPart(const Singer *, const std::vector<VocalPart *> &);
    void AppendEnergy(int, float, float);
    void AppendTalkyData(int, bool, bool, float);
    void AppendDeploymentTime(int, float);
    void AppendDeploymentMarker(int);
    void AppendPartData(const std::vector<VocalPart *> &);
    void AppendPhraseMeter(float);
    void FinalizeDisplayString();

    String mDisplayedString; // 0x0
    std::vector<String> mSingerStrings; // 0xc
    String mFooterString; // 0x14
    float unk20; // 0x20
    float unk24; // 0x24
};