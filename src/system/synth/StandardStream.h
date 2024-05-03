#ifndef SYNTH_STANDARDSTREAM_H
#define SYNTH_STANDARDSTREAM_H
#include "synth/Stream.h"
#include "synth/Pollable.h"

class StandardStream : public Stream, public SynthPollable {
public:
    StandardStream(File*, float, float, Symbol, bool, bool);
    virtual ~StandardStream();
    virtual bool Fail();
    virtual bool IsReady() const;
    virtual bool IsFinished() const;
    virtual int GetNumChannels() const;
    virtual int GetNumChanParams() const;
    virtual void Play();
    virtual void Stop();
    virtual bool IsPlaying() const;
    virtual bool IsPaused() const;
    virtual void Resync(float);
    virtual void Fill();
    virtual bool FillDone() const;
    virtual void EnableReads(bool);
    virtual float GetTime();
    virtual float GetJumpBackTotalTime();
    virtual float GetInSongTime();
    virtual int GetLoopInstances();
    virtual float GetFilePos() const;
    virtual float GetFileLength() const;
    virtual void SetVolume(int, float);
    virtual float GetVolume(int) const;
    virtual void SetPan(int, float);
    virtual float GetPan(int) const;
    virtual void SetFX(int, bool);
    virtual bool GetFX(int) const;
    virtual void SetFXCore(int, FXCore);
    virtual FXCore GetFXCore(int) const;
    virtual void SetFXSend(int, FxSend*);
    virtual void SetADSR(int, const ADSR&);
    virtual void SetSpeed(float);
    virtual float GetSpeed() const;
    virtual void LoadMarkerList(const char*);
    virtual void ClearMarkerList();
    virtual void AddMarker(Marker);
    virtual int MarkerListSize() const;
    virtual int MarkerAt(int, Marker&) const;
    virtual void SetLoop(String&, String&);
    virtual int CurrentLoopPoints(Marker&, Marker&);
    virtual void AbandonLoop();
    virtual void SetJump(float, float, const char*);
    virtual void ClearJump();
    virtual void EnableSlipStreaming(int);
    virtual void SetSlipOffset(int, float);
    virtual void SlipStop(int);
    virtual float GetSlipOffset(int);
    virtual void SetSlipSpeed(int, float);
    virtual int ChannelFaders(int); // fix return type
    virtual void AddVirtualChannels(int);
    virtual void RemapChannel(int, int);

    virtual const char* GetSoundDisplayName();
    virtual void UpdateTime();
    virtual void UpdateTimeByFiltering();
    virtual float GetRawTime();
    virtual void SetJumpSamples(int, int, const char*);
    virtual int GetSampleRate(); // fix return type
    virtual void SynthPoll();

    void PollStream();
};

#endif
