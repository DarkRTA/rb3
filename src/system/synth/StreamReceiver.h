#ifndef SYNTH_STREAMRECEIVER_H
#define SYNTH_STREAMRECEIVER_H
#include "synth/ADSR.h"
#include "synth/SampleInst.h"

enum State {
    kInit = 0,
    kReady = 1,
    kPlaying = 2,
    kStopped = 3,
};

class StreamReceiver {
public:
    StreamReceiver(int, bool);
    virtual ~StreamReceiver();
    virtual void SetVolume(float) = 0;
    virtual void SetPan(float) = 0;
    virtual void SetSpeed(float) = 0;
    virtual void SetADSR(const ADSR&){}
    virtual void SetFXCore(FXCore){}
    virtual FXCore GetFXCore(){ return kFXCoreNone; }
    virtual void SetFX(bool){}
    virtual bool GetFX(){ return false; }
    virtual void SetPitchShift(bool){}
    virtual void Tag(){}
    virtual void Poll();
    virtual void SetSlipOffset(float) = 0;
    virtual void SlipStop() = 0;
    virtual void SetSlipSpeed(float) = 0;
    virtual float GetSlipOffset() = 0;
    virtual void SetFXSend(FxSend*){}
    virtual void PauseImpl(bool) = 0;
    virtual void PlayImpl() = 0;
    virtual int GetPlayCursor() = 0;
    virtual void StartSendImpl(unsigned char*, int, int) = 0;
    virtual void StartSendImpl(unsigned char*, unsigned char*, int, int, int) = 0;
    virtual bool SendDoneImpl() = 0;

    int BytesWriteable();

    bool mSlipEnabled;
    unsigned char mBuffer[0x8000];
    int mNumBuffers;
    int mRingSize;
    int mRingWritePos;
    int mRingReadPos;
    int mRingFreeSpace;
    int mRingWrittenSpace;
    State mState;
    int mSendTarget;
    bool mWantToSend;
    bool mSending;
    int mBuffersSent;
    bool mStarving;
    bool mEndData;
    int mDoneBufferCounter;
    int mLastPlayCursor;
};

#endif
