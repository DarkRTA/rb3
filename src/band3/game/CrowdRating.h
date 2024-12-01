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
    float GetLoseLevel() const { return mLoseLevel; }
    void SetLoseLevel(float level) { mLoseLevel = level; }
    float GetMinValue(){ return mRunningMin; }
    float GetValue() const { return mValue; }
    float GetRawValue() const { return mRawValue; }
    bool IsActive() const { return mActive; }

    bool mActive; // 0x4
    float mRawValue; // 0x8
    float mValue; // 0xc
    float mRunningMin; // 0x10
    float mSongFraction; // 0x14
    float mLoseLevel; // 0x18
    char unk1c[16];
    float unk2c;
};