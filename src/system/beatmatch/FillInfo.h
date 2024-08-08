#ifndef BEATMATCH_FILLINFO_H
#define BEATMATCH_FILLINFO_H
#include "utl/TickedInfo.h"
#include <vector>

struct FillExtent {
    FillExtent(int s, int e, bool b) : start(s), end(e), bre(b) {}
    int start;
    int end;
    bool bre;
};

class FillInfo {
public:
    FillInfo(){}
    virtual ~FillInfo(){}

    void Clear();
    bool AddFill(int, int, bool);
    bool FillAt(int, bool) const;
    bool AddLanes(int, int);
    bool NextFillExtents(int, FillExtent&) const;
    bool FillExtentAtOrBefore(int, FillExtent&) const;
    int LanesAt(int) const;

    TickedInfoCollection<int> mLanes; // 0x4
    std::vector<FillExtent> mFills; // 0xc
};

#endif