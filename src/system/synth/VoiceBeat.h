#pragma once
#include <vector>

class VoiceBeat {
public:
    VoiceBeat();
    ~VoiceBeat() {}
    void SetEnable(bool);
    void Analyze(float *, int, bool, bool, float);
    void Reset();
    void ClearTrigger();
    void ClearEventList();

    bool unk0;
    bool unk1;
    float unk4;
    bool mEnabled; // 0x8
    int unkc;
    double mXVVoice[5]; // 0x10
    double mYVVoice[5]; // 0x38
    double mXVEnvAntiAlias[3]; // 0x60
    double mYVEnvAntiAlias[3]; // 0x78
    double mXVSyllables[3]; // 0x90
    double mYVSyllables[3]; // 0xa8
    double mXVSpamSyllables[5]; // 0xc0
    double mYVSpamSyllables[5]; // 0xe8
    double mSpamAvg; // 0x110
    double mSylEnvSigma; // 0x118
    double mSylDeltaPrev; // 0x120
    double mVoiceEnergy; // 0x128
    double mFullBandEnergy; // 0x130
    double mFloorSigma; // 0x138
    std::vector<float> mPeaks; // 0x140
    std::vector<float> mTimes; // 0x148
    double mCount; // 0x150
    double mRate; // 0x158
    bool mTriggered; // 0x160
};

class EventTracker {
public:
    EventTracker();
    ~EventTracker() {}
    int findEarliest(float, int);
    int findLatest(float, int);
    bool Hit(float, float, float);
    bool Miss(float, float);
    void Reset();
    void invalidate();

    std::vector<float> mTimes; // 0x0
    std::vector<float> mPeaks; // 0x8
    std::vector<bool> mHits; // 0x10
    std::vector<bool> mMisses; // 0x18
    std::vector<int> mSwings; // 0x20
    int mSelFrom; // 0x28
    int mSelTo; // 0x2c
    float mAvgHitTime; // 0x2c
};

class TalkyMatcher {
public:
    TalkyMatcher();
    ~TalkyMatcher() {}
    void updateScoring(float);
    void LoadEvents(const std::vector<float> &, const std::vector<float> &);
    void Reset();
    void SetEnableTalkyMatcher(bool);
    void Analyze(const short *, int, float);

    VoiceBeat mVoiceBeat; // 0x0
    EventTracker mRefEvents; // 0x168
    float mBuffer[4096]; // 0x19c
};