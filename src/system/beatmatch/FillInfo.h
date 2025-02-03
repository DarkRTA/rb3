#pragma once
#include "utl/TickedInfo.h"
#include <vector>

enum FillLogic {
    kFillsRegular = 0,
    kFillsDeployGemAndDim = 1,
    kFillsDeployGemAndInvisible = 2
};

/** Info for a single fill. */
struct FillExtent {
    FillExtent(int s, int e, bool b) : start(s), end(e), bre(b) {}
    bool CheckBounds(int tick) const { return tick >= start && tick <= end; }
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
    FillInfo() {}
    virtual ~FillInfo() {}

    /** Completely empty the lane and fill collections. */
    void Clear();
    /** Add a fill to our fill collection.
     * @param [in] start The start tick of this fill.
     * @param [in] duration How long in ticks this fill should last.
     * @param [in] bre Is this fill for a BRE?
     * @returns True if the fill was successfully added, false if not.
     */
    bool AddFill(int start, int duration, bool bre);
    /** Checks if a fill exists at the given tick.
     * @param [in] tick The tick to check.
     * @param [in] include_end TODO: unknown
     * @returns True if a fill exists at the given tick, false if not.
     */
    bool FillAt(int tick, bool include_end) const;
    /** Add a new TickedInfo entry for the supplied lanes.
     * @param [in] tick The tick the lanes occur at.
     * @param [in] lanes The lanes.
     * @returns True if the lanes were successfully added, false if not.
     */
    bool AddLanes(int tick, int lanes);
    /** Get the next coming FillExtent relative to the supplied tick.
     * @param [in] tick The tick to check.
     * @param [out] outExtent The next FillExtent coming after this tick.
     * @returns True if a FillExtent exists after the supplied tick, false if not.
     */
    bool NextFillExtents(int tick, FillExtent &outExtent) const;
    /** Get the FillExtent either at or before the supplied tick.
     * @param [in] tick The tick to check.
     * @param [out] outExtent The FillExtent at or before this tick.
     * @returns True if a FillExtent exists at or before the supplied tick, false if not.
     */
    bool FillExtentAtOrBefore(int tick, FillExtent &outExtent) const;
    /** Get the lanes associated with the supplied tick.
     * @param [in] tick The tick to check.
     * @returns The lanes associated with the tick.
     */
    int LanesAt(int tick) const;
    /** Checks if a fill exists at the given tick, and if so, write its tick range to
     * outExtent.
     * @param [in] tick The tick to check.
     * @param [out] outExtent The FillExtent containing this tick.
     * @param [in] include_end TODO: unknown
     * @returns True if a fill exists at the given tick, false if not.
     */
    bool FillAt(int tick, FillExtent &outExtent, bool include_end) const;

    TickedInfoCollection<int> mLanes; // 0x4
    std::vector<FillExtent> mFills; // 0xc
};
