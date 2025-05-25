#pragma once

class VibratoDetector {
public:
    VibratoDetector(int, int);
    ~VibratoDetector();
    int Analyze(float);
    int Detect();

    int mBuffer[5]; // 0x0
    float mPitches[5]; // 0x14
    int mBufIdx; // 0x28
    bool mHi; // 0x2c
    float mY0; // 0x30
    float mY1; // 0x34
    float mY2; // 0x38
    int mSample; // 0x3c
    int mLastDetect; // 0x40
    int mMaxPeriod; // 0x44
    int mMinPeriod; // 0x48
};
