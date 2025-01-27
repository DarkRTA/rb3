#pragma once
#include "utl/TickedInfo.h"
#include <vector>

struct FillExtent {
    FillExtent(int s, int e, bool b) : start(s), end(e), bre(b) {}
    bool CheckBounds(int tick) const {
        return tick >= start && tick <= end;
    }
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
    bool FillAt(int, FillExtent&, bool) const;

    TickedInfoCollection<int> mLanes; // 0x4
    std::vector<FillExtent> mFills; // 0xc
};
