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
    std::vector<BeatInfo> mInfos;
};

#endif
