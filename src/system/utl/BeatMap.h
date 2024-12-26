#pragma once
#include <vector>

struct BeatInfo {
    BeatInfo(int t, int l) : mTick(t), mLevel(l) {}
    int mTick;
    int mLevel;
};

class BeatMap {
public:
    BeatMap();
    ~BeatMap(){}
    bool AddBeat(int, int);
    float Beat(int) const;
    float Beat(float) const;
    float BeatToTick(float) const;
    float Interpolate(int t1, int t2) const {
        const BeatInfo& r30 = mInfos[t2];
        const BeatInfo& r31 = mInfos[t2 + 1];

        int k1 = mInfos[t2].mTick;
        
        return t2 + static_cast<float>(t1 - k1) /
            static_cast<float>(r31.mTick - r30.mTick);
    }

    float Interpolate(float, int) const;

    std::vector<BeatInfo> mInfos;
};

extern BeatMap* TheBeatMap;
void SetTheBeatMap(BeatMap*);
void ResetTheBeatMap();
