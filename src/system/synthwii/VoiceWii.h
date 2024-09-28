#ifndef SYNTHWII_VOICE_WII_H
#define SYNTHWII_VOICE_WII_H

#include "EnvelopeWii.h"
#include "synth/SampleInst.h"
#include "synth/SampleData.h"

class Voice {
public:
    struct _AXPBMIX {
        unsigned short vL;
        unsigned short vDeltaL;
        unsigned short vR;
        unsigned short vDeltaR;
        unsigned short vAuxAL;
        unsigned short vDeltaAuxAL;
        unsigned short vAuxAR;
        unsigned short vDeltaAuxAR;
        unsigned short vAuxBL;
        unsigned short vDeltaAuxBL;
        unsigned short vAuxBR;
        unsigned short vDeltaAuxBR;
        unsigned short vAuxCL;
        unsigned short vDeltaAuxCL;
        unsigned short vAuxCR;
        unsigned short vDeltaAuxCR;
        unsigned short vS;
        unsigned short vDeltaS;
        unsigned short vAuxAS;
        unsigned short vDeltaAuxAS;
        unsigned short vAuxBS;
        unsigned short vDeltaAuxBS;
        unsigned short vAuxCS;
        unsigned short vDeltaAuxCS;
    };

    struct _AXPBITD {
        unsigned short flag;
        unsigned short bufferHi;
        unsigned short bufferLo;
        unsigned short shiftL;
        unsigned short shiftR;
        unsigned short targetShiftL;
        unsigned short targetShiftR;
    };

    struct _AXPBDPOP {
        short aL;
        short aAuxAL;
        short aAuxBL;
        short aAuxCL;
        short aR;
        short aAuxAR;
        short aAuxBR;
        short aAuxCR;
        short aS;
        short aAuxAS;
        short aAuxBS;
        short aAuxCS;
    };

    struct _AXPBVE {
        unsigned short currentVolume;
        short currentDelta;
    };

    struct _AXPBADDR {
        unsigned short loopFlag;
        unsigned short format;
        unsigned short loopAddressHi;
        unsigned short loopAddressLo;
        unsigned short endAddressHi;
        unsigned short endAddressLo;
        unsigned short currentAddressHi;
        unsigned short currentAddressLo;
    };

    struct _AXPBADPCM {
        unsigned short a[2][8];
        unsigned short gain;
        unsigned short pred_scale;
        unsigned short yn1;
        unsigned short yn2;
    };

    struct _AXPBSRC {
        unsigned short ratioHi;
        unsigned short ratioLo;
        unsigned short currentAddressFrac;
        unsigned short last_samples[4];
    };

    struct _AXPBADPCMLOOP {
        unsigned short loop_pred_scale;
        unsigned short loop_yn1;
        unsigned short loop_yn2;
    };

    struct _AXPBLPF {
        unsigned short on;
        unsigned short yn1;
        unsigned short a0;
        unsigned short b0;
    };

    struct _AXPBBIQUAD {
        unsigned short on;
        unsigned short xn1;
        unsigned short xn2;
        unsigned short yn1;
        unsigned short yn2;
        unsigned short b0;
        unsigned short b1;
        unsigned short b2;
        unsigned short a1;
        unsigned short a2;
    };

    struct _AXPBRMTMIX {
        unsigned short vMain0;
        unsigned short vDeltaMain0;
        unsigned short vAux0;
        unsigned short vDeltaAux0;
        unsigned short vMain1;
        unsigned short vDeltaMain1;
        unsigned short vAux1;
        unsigned short vDeltaAux1;
        unsigned short vMain2;
        unsigned short vDeltaMain2;
        unsigned short vAux2;
        unsigned short vDeltaAux2;
        unsigned short vMain3;
        unsigned short vDeltaMain3;
        unsigned short vAux3;
        unsigned short vDeltaAux3;
    };

    struct _AXPBRMTDPOP {
        short aMain0;
        short aMain1;
        short aMain2;
        short aMain3;
        short aAux0;
        short aAux1;
        short aAux2;
        short aAux3;
    };

    struct _AXPBRMTSRC {
        unsigned short currentAddressFrac;
        unsigned short last_samples[4];
    };

    struct __AXPBRMTIIR {
        _AXPBLPF lpf;
        _AXPBBIQUAD biquad;
    };

    struct _AXPB {
        unsigned short nextHi; // 0x0
        unsigned short nextLo; // 0x2
        unsigned short currHi; // 0x4
        unsigned short currLo; // 0x6
        unsigned short srcSelect; // 0x8
        unsigned short coefSelect; // 0xA
        unsigned long mixerCtrl; // 0xC
        unsigned short state; // 0x10
        unsigned short type; // 0x12
        _AXPBMIX mix; // 0x14
        _AXPBITD itd;
        _AXPBDPOP dpop;
        _AXPBVE ve;
        _AXPBADDR addr;
        _AXPBADPCM adpcm;
        _AXPBSRC src;
        _AXPBADPCMLOOP adpcmLoop;
        _AXPBLPF lpf;
        _AXPBBIQUAD biquad;
        unsigned short remote;
        unsigned short rmtMixerCtrl;
        _AXPBRMTMIX rmtMix;
        _AXPBRMTDPOP rmtDpop;
        _AXPBRMTSRC rmtSrc;
        __AXPBRMTIIR rmtIIR;
        unsigned short pad[12];
    };

    struct _AXVPB {
        void *next; // 0x0
        void *prev; // 0x4
        void *next1; // 0x8
        unsigned long priority; // 0xC
        void (*callback)(void *p); // 0x10
        unsigned long userContext; // 0x14
        unsigned long index; // 0x18
        unsigned long sync; // 0x1C
        unsigned long depop; // 0x20
        void *itdBuffer; // 0x24
        _AXPB pb; // 0x28
    };

    Voice(const void*, int, bool, bool);
    ~Voice();
    void *GetAddr();
    bool IsPaused();
    bool IsPlaying();
    int SampToByte(int, bool);
    void SetFX(bool);
    void SetFormat(SampleData::Format);
    void SetLoopSamp(int);
    void SetStartSamp(int);
    void SetVolume(float);
    void SetVolume(float, bool);

    int mState; // 0x0 this is an enum, figure out the values todo
    struct _AXVPB *mVoice; // 0x4
    unsigned char *mVoiceBuffer; // 0x8
    int mVoiceBufferSize; // 0xC
    int mNextBufferSyncPtr; // 0x10
    int mNextBufferSyncSize; // 0x14
    unsigned char *mLastBufferSyncEndPtr; // 0x18
    char *mBufferStart; // 0x1C
    int mBufferBytes; // 0x20
    int mStartByte; // 0x24
    int mLoopByte; // 0x28
    int mSampleRate; // 0x2C
    float mSpeed; // 0x30
    bool mMixDirty; // 0x34

    float mVolume; // 0x38
    float mPan; // 0x3c
    float mLastVolume; // 0x40
    FXCore mFXCore; // 0x44
    bool mFXActive; // 0x48
    bool mUseInPlace; // 0x49

    class PitchShiftEffect *mPitchEffect; // 0x4C
    float mPitch; // 0x50
    unsigned char *mLastPitchEffectWritePtr; // 0x54
    SampleData::Format mFormat; // 0x58

    EnvelopeWii mEnvelope; // 0x5C
    bool mFirstPoll;
};

#endif // SYNTHWII_VOICE_WII_H
