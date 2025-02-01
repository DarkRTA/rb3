#pragma once
#include <vector>

class Stream;

class SlipTrack {
public:
    SlipTrack(Stream *, int);
    void Init(Stream *);
    void ForceOn();
    void VolumeOn(float);
    void Poll();
    void VolumeOff();
    void SetOffset(float);
    void SetSpeed(float);
    float GetCurrentOffset();

    Stream *mStream;
    std::vector<int> mChannels;
    float mOffMs;
    float mMaxSlip;
    bool mOn;
};
