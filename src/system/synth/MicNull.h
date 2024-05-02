#ifndef SYNTH_MICNULL_H
#define SYNTH_MICNULL_H
#include "synth/Mic.h"
#include "math/Rand.h"
#include "os/Timer.h"

class MicNull : public Mic {
public:
    MicNull();
    virtual ~MicNull(){}
    virtual void Start();
    virtual void Stop();
    virtual bool IsRunning() const;
    virtual int GetType() const;
    virtual void SetDMA(bool);
    virtual bool GetDMA() const;
    virtual void SetGain(float);
    virtual float GetGain() const;
    virtual void SetEarpieceVolume(float);
    virtual float GetEarpieceVolume() const;
    virtual int GetClipping() const;
    virtual void SetOutputGain(float);
    virtual float GetOutputGain() const;
    virtual void SetSensitivity(float);
    virtual float GetSensitivity() const;
    virtual void SetCompressor(bool);
    virtual bool GetCompressor() const;
    virtual void SetCompressorParam(float);
    virtual float GetCompressorParam() const;
    virtual void GetRecentBuf(int&);
    virtual void GetContinuousBuf(int&);
    virtual int GetSampleRate() const;
    virtual void SetEarpiece(bool);
    virtual bool GetEarpiece() const { return false; }

    static Rand sRand;

    char filler[0x5a20]; // prolly a bunch of bufs
    Timer mTimer;
    short mBuf[10000];
};

#endif
