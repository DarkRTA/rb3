#ifndef UTL_MULTITEMPOTEMPOMAP_H
#define UTL_MULTITEMPOTEMPOMAP_H
#include "utl/TempoMap.h"
#include <vector>

class MultiTempoTempoMap : public TempoMap {
public:
    struct TempoInfoPoint {
        TempoInfoPoint(){}
        TempoInfoPoint(float ms, int tick, int tempo) : mMs(ms), mTick(tick), mTempo(tempo) {}
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
    virtual void Finalize();
    virtual void ClearLoopPoints();
    virtual void SetLoopPoints(int, int);
    virtual int GetLoopTick(int, int&) const;
    virtual int GetLoopTick(int) const;
    virtual float GetTimeInLoop(float);

    bool AddTempoInfoPoint(int, int);
    TempoInfoPoint* PointForTick(float) const;
    static bool CompareTick(float, const TempoInfoPoint&);
    static bool CompareTime(float, const TempoInfoPoint&);

    std::vector<TempoInfoPoint> mTempoPoints; // 0x4
    float mStartLoopTick; // 0xc
    float mEndLoopTick; // 0x10
    float mStartLoopTime; // 0x14
    float mEndLoopTime; // 0x18
};

#endif
