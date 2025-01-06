#pragma once
#include "synth/Mic.h"
#include "math/Rand.h"
#include "os/Timer.h"

class MicNull : public Mic {
public:
    MicNull();
    virtual ~MicNull(){}
    virtual void Start(){}
    virtual void Stop(){}
    virtual bool IsRunning() const { return true; }
    virtual int GetType() const { return 2; }
    virtual void SetDMA(bool){}
    virtual bool GetDMA() const { return false; }
    virtual void SetGain(float){}
    virtual float GetGain() const { return 0.0f; }
    virtual void SetOutputGain(float){}
    virtual float GetSensitivity() const { return 0.0f; }
    virtual void SetSensitivity(float){}
    virtual float GetOutputGain() const { return 0.0f; }
    virtual void SetEarpiece(bool){}
    virtual bool GetEarpiece() const { return false; }
    virtual void SetEarpieceVolume(float){}
    virtual float GetEarpieceVolume() const { return 0.0f; }
    virtual void SetCompressor(bool){}
    virtual bool GetCompressor() const { return false; }
    virtual void SetCompressorParam(float){}
    virtual float GetCompressorParam() const { return 0.0f; }
    virtual char* GetRecentBuf(int&);
    virtual char* GetContinuousBuf(int&);
    virtual int GetSampleRate() const;
    virtual int GetClipping() const { return 0; }

    static Rand sRand;

    // buf at 0xc, 0xc00 bytes long
    // another buf at 0x5a60
    char buf_0xC[0xC00];
    char filler[20000]; // prolly a bunch of bufs
    Timer mTimer; // 0x5a30
    short mBuf[10000];
};
