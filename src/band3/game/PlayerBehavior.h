#pragma once
#include "utl/Symbol.h"

class PlayerBehavior {
public:
    PlayerBehavior();

    void SetCanDeployOverdrive(bool);
    void SetTiltDeploysBandEnergy(bool);
    void SetFillsDeployBandEnergy(bool);
    void SetRequireAllCodaLanes(bool);
    void SetStreakType(Symbol);
    void SetMaxMultiplier(int);
    void SetCanFreestyleBeforeGems(bool);
    void SetHasSolos(bool);

    bool GetFillsDeployBandEnergy() const { return mFillsDeployBand; }
    int GetMaxMultiplier() const { return mMaxMultiplier; }
    bool GetRequireAllCodaLanes() const { return mRequireAllCodas; }
    bool GetHasSolos() const { return mHasSolos; }

    bool mCanDeployOverdrive; // 0x0
    bool mTiltDeployBand; // 0x1
    bool mFillsDeployBand; // 0x2
    bool mRequireAllCodas; // 0x3
    bool mCanFreestyleGems; // 0x4
    bool mHasSolos; // 0x5
    Symbol mStreakType; // 0x8
    int mMaxMultiplier; // 0xc
};