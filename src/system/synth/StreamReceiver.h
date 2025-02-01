#pragma once
#include "synth/ADSR.h"
#include "synth/SampleInst.h"

class StreamReceiver;
typedef StreamReceiver *StreamReceiverFactoryFunc(int, int, bool, int);

class StreamReceiver {
public:
    enum State {
        kInit = 0,
        kReady = 1,
        kPlaying = 2,
        kStopped = 3,
    };

    StreamReceiver(int, bool);
    virtual ~StreamReceiver();
    virtual void SetVolume(float) = 0;
    virtual void SetPan(float) = 0;
    virtual void SetSpeed(float) = 0;
    virtual void SetADSR(const ADSR &) {}
    virtual void SetFXCore(FXCore) {}
    virtual FXCore GetFXCore() { return kFXCoreNone; }
    virtual void SetFX(bool) {}
    virtual bool GetFX() { return false; }
    virtual void SetPitchShift(bool) {}
    virtual void Tag() {}
    virtual void Poll();
    virtual void SetSlipOffset(float) = 0;
    virtual void SlipStop() = 0;
    virtual void SetSlipSpeed(float) = 0;
    virtual float GetSlipOffset() = 0;
    virtual void SetFXSend(FxSend *) {}
    virtual void PauseImpl(bool) = 0;
    virtual void PlayImpl() = 0;
    virtual int GetPlayCursor() = 0;
    virtual void StartSendImpl(unsigned char *, int, int) = 0;
    virtual void StartSendImpl(unsigned char *, unsigned char *, int, int, int) = 0;
    virtual bool SendDoneImpl() = 0;

    int BytesWriteable();
    void Play();
    void Stop();
    void EndData();
    bool Ready();
    void WriteData(const void *, int);
    void ClearAtEndData();
    int GetBytesPlayed();

    static StreamReceiver *New(int, int, bool, int);
    static StreamReceiverFactoryFunc *sFactory;

    bool mSlipEnabled; // 0x4
    unsigned char mBuffer[0x18000]; // 0x5
    int mNumBuffers; // 0x18008
    int mRingSize; // 0x1800c
    int mRingWritePos; // 0x18010
    int mRingReadPos; // 0x18014
    int mRingFreeSpace; // 0x18018
    int mRingWrittenSpace; // 0x1801c
    State mState; // 0x18020
    int mSendTarget; // 0x18024
    bool mWantToSend; // 0x18028
    bool mSending; // 0x18029
    int mBuffersSent; // 0x1802c
    bool mStarving; // 0x18030
    bool mEndData; // 0x18031
    int mDoneBufferCounter; // 0x18034
    int mLastPlayCursor; // 0x18038
};
