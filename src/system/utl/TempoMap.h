#ifndef UTL_TEMPOMAP_H
#define UTL_TEMPOMAP_H

class TempoMap {
public:
    // TempoMap();
    virtual ~TempoMap(){}
    virtual float TickToTime(float) const = 0;
    virtual float TimeToTick(float) const = 0;
    virtual float GetTempo(int) const = 0;
    virtual int GetTempoInMicroseconds(int i) const = 0;
    virtual float GetTempoBPM(int) const = 0;
    virtual int GetNumTempoChangePoints() const = 0;
    virtual int GetTempoChangePoint(int) const = 0;
    virtual void Finalize(){}
    virtual void ClearLoopPoints() = 0;
    virtual void SetLoopPoints(int, int) = 0;
    virtual int GetLoopTick(int, int&) const = 0;
    virtual int GetLoopTick(int) const = 0;
    virtual float GetTimeInLoop(float) = 0;
};

void SetTheTempoMap(TempoMap*);
void ResetTheTempoMap();

extern TempoMap* TheTempoMap;

#endif
