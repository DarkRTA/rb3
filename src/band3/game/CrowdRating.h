#pragma once
#include "game/BandUser.h"
#include "game/Defines.h"
#include "bandobj/CrowdAudio.h" // for the ExcitementLevel enum

class CrowdRating {
public:
    CrowdRating(BandUser *, Difficulty);
    virtual ~CrowdRating() {}
    virtual ExcitementLevel GetExcitement() const; // ExcitementLevel?

    void Reset();
    void Configure(BandUser *, Difficulty);
    float GetThreshold(ExcitementLevel) const;
    void SetActive(bool);
    void SetValue(float);
    bool IsInWarning() const;
    void SetDisplayValue(float);
    float GetDisplayValue() const;
    bool IsBelowLoseLevel() const;
    bool CantFailYet() const;
    void ChangeDifficulty(BandUser *, Difficulty);
    void Poll(float);
    void Update(float, float);
    void CalculateValue();
    void UpdatePhrase(float, float);

    float GetLoseLevel() const { return mLoseLevel; }
    void SetLoseLevel(float level) { mLoseLevel = level; }
    float GetMinValue() { return mRunningMin; }
    float GetValue() const { return mValue; }
    float GetRawValue() const { return mRawValue; }
    bool IsActive() const { return mActive; }

    bool mActive; // 0x4
    float mRawValue; // 0x8
    float mValue; // 0xc
    float mRunningMin; // 0x10
    float mSongFraction; // 0x14
    float mLoseLevel; // 0x18
    float kMin; // 0x1c
    float kMax; // 0x20
    float kNoteWeight; // 0x24
    float kPhraseWeight; // 0x28
    float kInitialDisplayLevel; // 0x2c
    float kGreatLevel; // 0x30
    float kOkayLevel; // 0x34
    float kBadLevel; // 0x38
    float kWarningLevel; // 0x3c
    float kFreeRide; // 0x40
};