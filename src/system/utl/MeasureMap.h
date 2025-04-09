#pragma once
#include <vector>

/** The map of measures for the current song. */
class MeasureMap {
public:
    /** An event denoting a time signature change. */
    class TimeSigChange {
    public:
        /** The measure this time sig change occurs at. */
        int mMeasure; // offset 0x0, size 0x4
        /** The new time sig's numerator. */
        int mNum; // offset 0x4, size 0x4
        /** The new time sig's denominator. */
        int mDenom; // offset 0x8, size 0x4
        /** The tick this time sig change occurs at. */
        int mTick; // offset 0xC, size 0x4
    };

    MeasureMap();
    ~MeasureMap() {}

    /** Convert the supplied tick into measure/beat/tick values.
     * @param [in] tick The tick value to convert.
     * @param [out] oMeasure The output measure value of the tick input.
     * @param [out] oBeat The output beat value of the tick input.
     * @param [out] oTick The output remaining tick value of the tick input.
     */
    void TickToMeasureBeatTick(int tick, int &oMeasure, int &oBeat, int &oTick) const;

    /** Convert the supplied tick into measure/beat/tick and BPM values.
     * @param [in] tick The tick value to convert.
     * @param [out] oMeasure The output measure value of the tick input.
     * @param [out] oBeat The output beat value of the tick input.
     * @param [out] oTick The output remaining tick value of the tick input.
     * @param [out] oBeatsPerMeasure The output BPM value of the tick input.
     */
    void TickToMeasureBeatTick(
        int tick, int &oMeasure, int &oBeat, int &oTick, int &oBeatsPerMeasure
    ) const;

    /** Attempt to add a new time signature to the measure map.
     * @param [in] measure The measure at which this new time sig occurs.
     * @param [in] num The numerator of this new time sig.
     * @param [in] denom The denominator of this new time sig.
     * @param [in] fail If true, and this is a bad new time sig, fail the game out.
     * @returns True if the new time sig was successfully added, false if not.
     */
    bool AddTimeSignature(int measure, int num, int denom, bool fail);

    /** Given the supplied measure/beat/tick values, get the total tick value.
     * @param [in] measure The supplied measure.
     * @param [in] beat The supplied beat.
     * @param [in] tick The supplied tick.
     * @returns The equivalent tick value of the supplied MBT.
     */
    int MeasureBeatTickToTick(int measure, int beat, int tick) const;

    static bool CompareTick(int, const TimeSigChange &);
    static bool CompareMeasure(int, const TimeSigChange &);

    /** The collection of measure markers. */
    std::vector<TimeSigChange> mTimeSigChanges; // offset 0x0, size 0xC
};
