#ifndef SYNTHWII_MIC_WII_H
#define SYNTHWII_MIC_WII_H

#include "synth/Mic.h"
#include "VoiceWii.h"

class MicWii : public Mic {
public:
    MicWii()
        : mOn(false), mConnected(false), mFXActive(false), mRunning(false), mMute(false),
          mAttemptedStart(false) {}
    virtual ~MicWii() {}
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
    virtual void SetMute(bool) {}
    virtual int GetClipping() const = 0;
    virtual void SetOutputGain(float) = 0;
    virtual float GetOutputGain() const = 0;
    virtual void SetSensitivity(float) = 0;
    virtual float GetSensitivity() const = 0;
    virtual void SetVolume(float) {}
    virtual void SetFxSend(FxSend *) {}
    virtual bool IsMultiMicDevice() const { return false; }
    virtual bool IsConnected() const { return IsRunning(); }
    virtual void SetChangeNotify(bool) {}
    virtual void StartPlayback() {}
    virtual void StopPlayback() {}
    virtual bool IsPlaying() { return false; }
    virtual void SetCompressor(bool) = 0;
    virtual bool GetCompressor() const = 0;
    virtual void SetCompressorParam(float) = 0;
    virtual float GetCompressorParam() const = 0;
    virtual char *GetRecentBuf(int &) = 0;
    virtual char *GetContinuousBuf(int &) = 0;
    virtual int GetDroppedSamples() { return 0; }
    virtual int GetSampleRate() const = 0;
    virtual float PercentTalking() { return 0.0f; }
    virtual void MarkAsInUse(bool b) { mInUse = b; }
    virtual bool IsInUse() { return mInUse; }
    virtual Symbol GetName() const { return generic_usb; }

    float GetVolume() const;
    short *GetBuf();
    int GetBufSamples() const;
    void SetFX(bool);
    void SetMicIndex(int);
    void SetPad(int);
    int GetPad();

    int mMicIndex; // 0x0
    bool mOn; // 0x4
    bool mConnected; // 0x5
    bool mFXActive; // 0x6
    bool mRunning; // 0x7
    bool mMute; // 0x8
    bool mAttemptedStart; // 0x9

    unsigned char *mPlaybackBuffer; // 0xC
    unsigned char *mPlaybackWritePtr; // 0x10

    short mOutBuf[4096]; // 0x14
    int mOutBufSamples; // 0x2020

    long mMicHandle; // 0x2024
    int mPadNum; // 0x2028
    float mGain; // 0x202c
    float mVolume; // 0x2030
    float mVoiceSpeed; // 0x2034
    float mAvgLag; // 0x2038
    float mLastLag; // 0x203C
    float mSensitivity; // 0x2040
    Voice *mVoice; // 0x2044
    bool mMicChanged; // 0x2048

    // there is more after this I believe, need to figure out the rest
};

#endif