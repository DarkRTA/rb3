#pragma once
#include "game/TambourineManager.h"

class Singer;

class TambourineDetector {
public:
    TambourineDetector(TambourineManager &, Singer *);
    ~TambourineDetector();
    void CheckForSwing(float, float);

    TambourineManager &mManager; // 0x0
    Singer *mSinger; // 0x4
    bool unk8; // 0x8
    float unkc; // 0xc
    float unk10; // 0x10
    float mEnergyDropThreshold; // 0x14
    float mEnergyRiseThreshold; // 0x18
    int mLagMsOffset; // 0x1c
};