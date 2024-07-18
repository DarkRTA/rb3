#ifndef UTL_MEASUREMAP_H
#define UTL_MEASUREMAP_H
#include <vector>

class MeasureMap {
public:
    class TimeSigChange {
    public:
        int mMeasure; // offset 0x0, size 0x4
        int mNum; // offset 0x4, size 0x4
        int mDenom; // offset 0x8, size 0x4
        int mTick; // offset 0xC, size 0x4
    };

    MeasureMap();
    void TickToMeasureBeatTick(int, int&, int&, int&) const;
    void TickToMeasureBeatTick(int, int&, int&, int&, int&) const;
    bool AddTimeSignature(int, int, int, bool);

    std::vector<TimeSigChange> mTimeSigChanges; // offset 0x0, size 0xC
};

#endif
