#ifndef SYNTH_STANDARDSTREAM_H
#define SYNTH_STANDARDSTREAM_H
#include "synth/Stream.h"
#include "synth/Pollable.h"
#include "synth/StreamReader.h"
#include <vector>
#include "utl/VarTimer.h"
#include "synth/Faders.h"

enum State {
    kInit = 0,
    kBuffering = 1,
    kReady = 2,
    kPlaying = 3,
    kSuspended = 4,
    kStopped = 5,
    kFinished = 6,
};

class StandardStream : public Stream, public SynthPollable {
public:

    class ChannelParams {
    public:
        ChannelParams();
        float mPan;
        float mSlipSpeed;
        bool mSlipEnabled;
        ADSR mADSR;
        FaderGroup mFaders;
        ObjPtr<FxSend, ObjectDir> mFxSend;
        FXCore mFXCore;
        bool mPitchShift;
    };

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
    virtual FaderGroup* ChannelFaders(int); // fix return type
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
    void ClearLoopMarkers();
    void Init(float, float, Symbol, bool);

    State mState;
    File* mFile;
    StreamReader* mRdr;
    std::vector<int> mChannels;
    int mSampleRate;
    float mBufSecs;
    float mFileStartMs;
    float mStartMs;
    float mLastStreamTime;
    int unk3c;
    VarTimer mTimer;
    std::vector<ChannelParams> mChanParams;
    int mJumpFromSamples;
    int mJumpToSamples;
    float mJumpFromMs;
    float mJumpToMs;
    bool mJumpSamplesInvalid;
    String mJumpFile;
    int mCurrentSamp;
    float mSpeed;
    Timer mFrameTimer;
    float mThrottle;
    Symbol mExt;
    bool mFloatSamples;
    int mVirtualChans;
    int mInfoChannels;
    float unkec;
    bool mGetInfoOnly;
    std::vector<int> unkf4;
    std::vector<int> unkfc;
    std::vector<int> unk104;
    std::vector<int> unk10c;
    Marker mStartMarker;
    Marker mEndMarker;
    float mAccumulatedLoopbacks;
    bool mPollingEnabled;
};

#endif
