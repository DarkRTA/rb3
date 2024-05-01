#ifndef SYNTH_STREAM_H
#define SYNTH_STREAM_H
#include "synth/SampleInst.h"
#include "synth/ADSR.h"

class FaderGroup;

struct Marker {
    class String name;
    int position;
    float posMS;
};

class Stream {
public:
    Stream();
    virtual ~Stream();
    virtual bool Fail(){ return false; }
    virtual bool IsReady() const = 0;
    virtual bool IsFinished() const = 0;
    virtual int GetNumChannels() const = 0;
    virtual int GetNumChanParams() const = 0;
    virtual void Play() = 0;
    virtual void Stop() = 0;
    virtual bool IsPlaying() const = 0;
    virtual bool IsPaused() const { return false; }
    virtual void Resync(float) = 0;
    virtual void Fill() = 0;
    virtual bool FillDone() const = 0;
    virtual void EnableReads(bool) = 0;
    virtual float GetTime() = 0;
    virtual float GetJumpBackTotalTime() = 0;
    virtual float GetInSongTime() = 0;
    virtual int GetLoopInstances() = 0;
    virtual float GetFilePos() const = 0;
    virtual float GetFileLength() const = 0;
    virtual void SetVolume(int, float) = 0;
    virtual float GetVolume(int) const = 0;
    virtual void SetPan(int, float) = 0;
    virtual float GetPan(int) const = 0;
    virtual void SetFX(int, bool) = 0;
    virtual bool GetFX(int) const = 0;
    virtual void SetFXCore(int, FXCore) = 0;
    virtual FXCore GetFXCore(int) const = 0;
    virtual void SetFXSend(int, FxSend*){}
    virtual void SetADSR(int, const ADSR&){}
    virtual void SetSpeed(float) = 0;
    virtual float GetSpeed() const = 0;
    virtual void LoadMarkerList(const char*) = 0;
    virtual void ClearMarkerList(){}
    virtual void AddMarker(Marker){}
    virtual int MarkerListSize() const { return 0; }
    virtual int MarkerAt(int, Marker&) const { return 0; }
    virtual void SetLoop(String&, String&) = 0;
    virtual int CurrentLoopPoints(Marker&, Marker&){ return 0; }
    virtual void AbandonLoop() = 0;
    virtual void SetJump(float, float, const char*) = 0;
    virtual void ClearJump() = 0;
    virtual void EnableSlipStreaming(int) = 0;
    virtual void SetSlipOffset(int, float) = 0;
    virtual void SlipStop(int) = 0;
    virtual float GetSlipOffset(int) = 0;
    virtual void SetSlipSpeed(int, float) = 0;
    virtual void SetStereoPair(int, int){}
    virtual int ChannelFaders(int) = 0; // fix return type
    virtual void AddVirtualChannels(int){}
    virtual void RemapChannel(int, int){}

    void SetVolume(float);

    FaderGroup* mFaders;
};

#endif
