#pragma once
#include "synth/Stream.h"
#include "utl/VarTimer.h"
#include "synth/Faders.h"

class StreamNull : public Stream {
public:
    StreamNull(float);
    virtual ~StreamNull();
    virtual bool IsReady() const { return true; }
    virtual bool IsFinished() const;
    virtual int GetNumChannels() const { return 0; }
    virtual int GetNumChanParams() const { return 0; }
    virtual void Play();
    virtual void Stop();
    virtual bool IsPlaying() const;
    virtual void Resync(float);
    virtual void Fill() {}
    virtual bool FillDone() const { return true; }
    virtual void EnableReads(bool) {}
    virtual float GetTime();
    virtual float GetJumpBackTotalTime();
    virtual float GetInSongTime();
    virtual int GetLoopInstances();
    virtual float GetFilePos() const { return 0; }
    virtual float GetFileLength() const { return 0; }
    virtual void SetVolume(int, float) {}
    virtual float GetVolume(int) const { return 0; }
    virtual void SetPan(int, float) {}
    virtual float GetPan(int) const { return 0; }
    virtual void SetFX(int, bool) {}
    virtual bool GetFX(int) const { return false; }
    virtual void SetFXCore(int, FXCore) {}
    virtual FXCore GetFXCore(int) const { return kFXCoreNone; }
    virtual void SetSpeed(float);
    virtual float GetSpeed() const;
    virtual void LoadMarkerList(const char *) {}
    virtual void SetLoop(class String &, class String &) {}
    virtual void AbandonLoop() {}
    virtual void SetJump(float, float, const char *) {}
    virtual void SetJumpSamples(int, int, const char *) {}
    virtual void ClearJump() {}
    virtual void EnableSlipStreaming(int) {}
    virtual void SetSlipOffset(int, float) {}
    virtual void SlipStop(int) {}
    virtual float GetSlipOffset(int) { return 0; }
    virtual void SetSlipSpeed(int, float) {}
    virtual FaderGroup *ChannelFaders(int);

    VarTimer mTimer; // 0x8
    FaderGroup mFaders; // 0x40
    std::vector<FaderGroup *> mChannelFaders; // 0x54
};
