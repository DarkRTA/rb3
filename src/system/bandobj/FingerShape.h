#pragma once
#include "rndobj/Dir.h"
#include "rndobj/Anim.h"
#include "rndobj/Text.h"
#include "beatmatch/RGState.h"

// size 0x34
class FingerShape {
public:
    FingerShape(RndDir*);
    ~FingerShape();
    void Update(const RGState&, bool, bool);
    void UpdateLeftyFlip(bool);
    void Reset(bool);
    void UpdateAnim(RndAnimatable*, float, bool);
    void UpdateFretNumber(const RGState&, bool);

    std::vector<RndAnimatable*> mFretHeightAnims; // 0x0
    std::vector<RndAnimatable*> mContourHeightAnims; // 0x8
    std::vector<RndAnimatable*> mContourAngleAnims; // 0x10
    RGState* mLastState; // 0x18
    RndAnimatable* mFretNumberShowAnim; // 0x1c
    RndAnimatable* mFretNumberPositionAnim; // 0x20
    RndText* mFretNumberText; // 0x24
    int mLastFretNumber; // 0x28
    float mAnimPeriod; // 0x2c
    bool mLefty; // 0x30
};