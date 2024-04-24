#ifndef BEATMATCH_FILLINFO_H
#define BEATMATCH_FILLINFO_H
#include "utl/TickedInfo.h"
#include <vector>

class FillInfo {
public:
    FillInfo();
    virtual ~FillInfo();

    TickedInfoCollection<int> mLanes;
    std::vector<int> mFills;
};

struct FillExtent {
    int start;
    int end;
    bool bre;
};

#endif