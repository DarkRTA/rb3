#pragma once

/** The map of tempos for the current song. */
class TempoMap {
public:
    TempoMap() {}
    virtual ~TempoMap() {}
    virtual float TickToTime(float tick) const = 0;
    virtual float TimeToTick(float time) const = 0;
    virtual float GetTempo(int tick) const = 0;
    virtual int GetTempoInMicroseconds(int tick) const = 0;
    virtual float GetTempoBPM(int tick) const = 0;
    virtual int GetNumTempoChangePoints() const = 0;
    virtual int GetTempoChangePoint(int index) const = 0;
    virtual void Finalize() {}
    virtual void ClearLoopPoints() = 0;
    virtual void SetLoopPoints(int start, int end) = 0;
    virtual int GetLoopTick(int tick, int &) const = 0;
    virtual int GetLoopTick(int tick) const = 0;
    virtual float GetTimeInLoop(float time) = 0;

    float TickToTime(int tick) const { return TickToTime((float)tick); }
};

void SetTheTempoMap(TempoMap *);
void ResetTheTempoMap();

extern TempoMap *TheTempoMap;
