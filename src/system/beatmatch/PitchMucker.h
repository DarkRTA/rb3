#ifndef BEATMATCH_PITCHMUCKER_H
#define BEATMATCH_PITCHMUCKER_H

class PitchMucker {
public:
    PitchMucker() : mToggle(0), mFrames(0), mPeriod(60) {}
    bool mToggle; // 0x0
    float mMaxPitch; // 0x4
    float mMinPitch; // 0x8
    unsigned int mFrames; // 0xc
    unsigned int mPeriod; // 0x10
};

#endif