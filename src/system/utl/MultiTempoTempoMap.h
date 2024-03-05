#ifndef UTL_MULTITEMPOTEMPOMAP_H
#define UTL_MULTITEMPOTEMPOMAP_H
#include "utl/TempoMap.h"
#include <vector>

class MultiTempoTempoMap : public TempoMap {
public:
    struct TempoInfoPoint {
        // total size: 0xC
        float mMs; // offset 0x0, size 0x4
        int mTick; // offset 0x4, size 0x4
        int mTempo; // offset 0x8, size 0x4
    };

    MultiTempoTempoMap();
    virtual ~MultiTempoTempoMap();
    virtual float TickToTime(float f) const;
    virtual float TimeToTick(float f) const;
    virtual float GetTempo(int) const;
    virtual int GetTempoInMicroseconds(int i) const;
    virtual float GetTempoBPM(int) const;
    virtual int GetNumTempoChangePoints() const;
    virtual int GetTempoChangePoint(int) const;
    virtual void ClearLoopPoints();
    virtual void SetLoopPoints(int, int);
    virtual int GetLoopTick(int, int&) const;
    virtual int GetLoopTick(int) const;
    virtual float GetTimeInLoop(float);

    std::vector<TempoInfoPoint> mTempoPoints;
    float mStartLoopTick;
    float mEndLoopTick;
};

#endif
