#pragma once
#include "utl/TickedInfo.h"
#include <vector>

/** Info for a single fill. */
struct FillExtent {
    FillExtent(int s, int e, bool b) : start(s), end(e), bre(b) {}
    bool CheckBounds(int tick) const {
        return tick >= start && tick <= end;
    }
    /** The starting tick. */
    int start; // 0x0
    /** The ending tick. */
    int end; // 0x4
    /** Is this fill for a BRE? */
    bool bre; // 0x8
};

/** A general collection of fill information. */
class FillInfo {
public:
    FillInfo(){}
    virtual ~FillInfo(){}

    /** Completely empty the lane and fill collections. */
    void Clear();
    /** Add a fill to our fill collection.
     * @param [in] start The start tick of this fill.
     * @param [in] duration How long in ticks this fill should last.
     * @param [in] bre Is this fill for a BRE?
     * @returns True if the fill was successfully added, false if not.
     */
    bool AddFill(int start, int duration, bool bre);
    bool FillAt(int, bool) const;
    bool AddLanes(int, int);
    bool NextFillExtents(int, FillExtent&) const;
    bool FillExtentAtOrBefore(int, FillExtent&) const;
    int LanesAt(int) const;
    bool FillAt(int, FillExtent&, bool) const;

    TickedInfoCollection<int> mLanes; // 0x4
    std::vector<FillExtent> mFills; // 0xc
};
