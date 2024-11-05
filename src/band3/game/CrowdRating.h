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
    float GetMinValue(){ return unk10; }
    bool IsActive() const { return mActive; }
    float GetValue() const { return unkc; }
    void SetActive(bool);
    void SetValue(float);
    bool IsInWarning() const;
    float GetRawValue() const { return unk8; }
    void SetDisplayValue(float);
    float GetDisplayValue() const;
    bool IsBelowLoseLevel() const;
    bool CantFailYet() const;
    void ChangeDifficulty(BandUser*, Difficulty);
    float GetLoseLevel() const { return unk18; }
    void SetLoseLevel(float level){ unk18 = level; }

    bool mActive; // 0x4
    float unk8;
    float unkc;
    float unk10;
    float unk14;
    float unk18;
};