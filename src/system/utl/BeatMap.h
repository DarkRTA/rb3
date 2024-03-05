#ifndef UTL_BEATMAP_H
#define UTL_BEATMAP_H
#include <vector>

struct BeatInfo {
    int mTick;
    int mLevel;
};

class BeatMap {
public:
    BeatMap();
    ~BeatMap(){}
    float Beat(int) const;
    float Beat(float) const;
    float BeatToTick(float) const;

    std::vector<BeatInfo> mInfos;
};

extern BeatMap* TheBeatMap;

#endif
