#pragma once
#include "game/BandUser.h"
#include "game/Defines.h"
#include "bandobj/CrowdAudio.h" // for the ExcitementLevel enum

class CrowdRating {
public:
    CrowdRating(BandUser*, Difficulty);
    virtual ~CrowdRating(){}
    virtual ExcitementLevel GetExcitement() const; // ExcitementLevel?

    void Reset();
    void Configure(BandUser*, Difficulty);
    float GetThreshold(ExcitementLevel) const;
    void SetActive(bool);
    void SetValue(float);
    bool IsInWarning() const;
    void SetDisplayValue(float);
    float GetDisplayValue() const;
    bool IsBelowLoseLevel() const;
    bool CantFailYet() const;
    void ChangeDifficulty(BandUser *, Difficulty);
    float GetLoseLevel() const { return unk18; }
    void SetLoseLevel(float level) { unk18 = level; }
    float GetMinValue(){ return unk10; }
    float GetValue() const { return unkc; }
    float GetRawValue() const { return unk8; }
    bool IsActive() const { return mActive; }

    bool mActive; // 0x4
    float unk8;
    float unkc;
    float unk10;
    float unk14;
    float unk18;
    char unk1c[16];
    float unk2c;
};