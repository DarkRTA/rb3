#ifndef UTL_SIMPLETEMPOMAP_H
#define UTL_SIMPLETEMPOMAP_H
#include "utl/TempoMap.h"

class SimpleTempoMap : public TempoMap {
public:
    SimpleTempoMap(float f){ mTempo = f / 480.0f; }
    virtual ~SimpleTempoMap(){}
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

    float mTempo;
};

#endif
