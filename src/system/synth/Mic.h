#ifndef SYNTH_MIC_H
#define SYNTH_MIC_H
#include "utl/Symbol.h"
#include "utl/Symbols.h"

// forward decs
class FxSend;
class DataArray;

class Mic {
public:
    Mic() : mInUse(0), unk8(1.0f) {}
    virtual ~Mic(){}
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual bool IsRunning() const = 0;
    virtual int GetType() const = 0;
    virtual void SetDMA(bool) = 0;
    virtual bool GetDMA() const = 0;
    virtual void SetGain(float) = 0;
    virtual float GetGain() const = 0;
    virtual void SetEarpieceVolume(float) = 0;
    virtual float GetEarpieceVolume() const = 0;
    virtual void SetMute(bool){}
    virtual int GetClipping() const = 0;
    virtual void SetOutputGain(float) = 0;
    virtual float GetOutputGain() const = 0;
    virtual void SetSensitivity(float) = 0;
    virtual float GetSensitivity() const = 0;
    virtual void SetVolume(float){}
    virtual void SetFxSend(FxSend*){}
    virtual bool IsMultiMicDevice() const { return false; }
    virtual bool IsConnected() const { return IsRunning(); }
    virtual void SetChangeNotify(bool){}
    virtual void StartPlayback(){}
    virtual void StopPlayback(){}
    virtual bool IsPlaying(){ return false; }
    virtual void SetCompressor(bool) = 0;
    virtual bool GetCompressor() const = 0;
    virtual void SetCompressorParam(float) = 0;
    virtual float GetCompressorParam() const = 0;
    virtual void GetRecentBuf(int&) = 0;
    virtual void GetContinuousBuf(int&) = 0;
    virtual int GetDroppedSamples(){ return 0; }
    virtual int GetSampleRate() const = 0;
    virtual float PercentTalking(){ return 0.0f; }
    virtual void MarkAsInUse(bool b){ mInUse = b; }
    virtual bool IsInUse(){ return mInUse; }
    virtual Symbol GetName() const { return generic_usb; }

    void Set(const DataArray*);

    bool mInUse;
    float unk8;
};

#endif
