#pragma once
#include "beatmatch/HitSink.h"
#include <vector>

class HitTracker : public HitSink {
public:
    HitTracker();
    virtual ~HitTracker(){}
    virtual void Hit(HitType);
    virtual void Key(int);
    virtual void RGFret(int, int);
    virtual void RGStrum(int);

    void Reset();
    void PrintStats() const;

    std::vector<int> mHits; // 0x4
    int mKeys[128]; // 0xc
    int mRGStrums[6]; // 0x20c
    int mRGFrets[6][20]; // 0x228
};