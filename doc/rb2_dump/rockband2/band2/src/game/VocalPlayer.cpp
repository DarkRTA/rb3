/*
    Compile unit: C:\rockband2\band2\src\game\VocalPlayer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800995CC -> 0x800A1D00
*/
class Symbol t; // size: 0x4, address: 0x80A4A15C
class Symbol t; // size: 0x4, address: 0x80A4A164
class VibratoDetector {
    // total size: 0x4C
    int mBuffer[5]; // offset 0x0, size 0x14
    float mPitches[5]; // offset 0x14, size 0x14
    int mBufIdx; // offset 0x28, size 0x4
    unsigned char mHi; // offset 0x2C, size 0x1
    float mY0; // offset 0x30, size 0x4
    float mY1; // offset 0x34, size 0x4
    float mY2; // offset 0x38, size 0x4
    int mSample; // offset 0x3C, size 0x4
    int mLastDetect; // offset 0x40, size 0x4
    int mMaxPeriod; // offset 0x44, size 0x4
    int mMinPeriod; // offset 0x48, size 0x4
};
// Range: 0x800995CC -> 0x8009992C
void * VocalPlayer::~VocalPlayer(class VocalPlayer * const this /* r30 */) {
    // Local variables
    class Mic * mic; // r28

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> struct [anonymous] __vt__11VocalPlayer;
}

// Range: 0x8009992C -> 0x80099978
void VocalPlayer::ConfigureBehavior(class VocalPlayer * const this /* r31 */) {}

// Range: 0x80099978 -> 0x80099A04
void VocalPlayer::SetTrack(class VocalPlayer * const this /* r29 */, int track_num /* r30 */) {}

// Range: 0x80099A04 -> 0x80099A10
float VocalPlayer::GetSongMs() {}

// Range: 0x80099A10 -> 0x80099A6C
void VocalPlayer::Start(class VocalPlayer * const this /* r31 */) {}

// Range: 0x80099A6C -> 0x80099AEC
void VocalPlayer::StartIntro(class VocalPlayer * const this /* r30 */) {
    // Local variables
    class Mic * mic; // r31
}

// Range: 0x80099AEC -> 0x80099D4C
void VocalPlayer::Restart(class VocalPlayer * const this /* r31 */) {
    // Local variables
    const class vector & phrases; // r0
    unsigned char foundPitchedNote; // r6
    const class vector & notes; // r0
    int i; // r7
    const class VocalPhrase * it; // r5
}

// Range: 0x80099D4C -> 0x80099DF8
void VocalPlayer::SetPaused(class VocalPlayer * const this /* r29 */) {
    // References
    // -> class GameMode * TheGameMode;
}

// Range: 0x80099DF8 -> 0x80099EF4
void VocalPlayer::Jump(class VocalPlayer * const this /* r31 */, float ms /* f31 */) {}

// Range: 0x80099EF4 -> 0x80099EF8
void VocalPlayer::PollAudio() {}

// Range: 0x80099EF8 -> 0x80099F98
float VocalPlayer::GetNotesHitFraction() {}

// Range: 0x80099F98 -> 0x80099FB0
int VocalPlayer::GetBaseMaxPoints() {}

// Range: 0x80099FB0 -> 0x80099FD0
int VocalPlayer::GetBaseMaxStreakPoints() {}

// Range: 0x80099FD0 -> 0x80099FD8
int VocalPlayer::GetBaseBonusPoints() {}

// Range: 0x80099FD8 -> 0x8009A010
class Symbol VocalPlayer::GetStarRating() {
    // References
    // -> class Scoring * TheScoring;
}

// Range: 0x8009A010 -> 0x8009A110
void VocalPlayer::LocalSetEnabledState(class VocalPlayer * const this /* r30 */, enum EnabledState state /* r31 */) {
    // Local variables
    const class VocalPhrase * i; // r4
    float vol; // f0
}

// Range: 0x8009A110 -> 0x8009A150
int VocalPlayer::LocalDeployBandEnergy(class VocalPlayer * const this /* r31 */) {
    // Local variables
    int retVal; // r3
}

static class Message msg; // size: 0x8, address: 0x809778C0
// Range: 0x8009A150 -> 0x8009A39C
void VocalPlayer::UpdateCrowdMeter(class VocalPlayer * const this /* r30 */, int rating /* r31 */) {
    // Local variables
    float weight; // f2
    float val; // f31

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8009A39C -> 0x8009A3F8
void VocalPlayer::RemoteUpdateCrowd(class VocalPlayer * const this /* r30 */) {
    // References
    // -> class GameMode * TheGameMode;
}

// Range: 0x8009A3F8 -> 0x8009A458
float VocalPlayer::RemoteVocalVolume() {
    // Local variables
    float display_value; // f0
}

// Range: 0x8009A458 -> 0x8009A4B8
unsigned char VocalPlayer::IsRemote(const class VocalPlayer * const this /* r30 */) {}

// Range: 0x8009A4B8 -> 0x8009A4F8
char * VocalPlayer::SongRoot() {
    // References
    // -> class SongMgr & TheSongMgr;
}

// Range: 0x8009A4F8 -> 0x8009A60C
void VocalPlayer::LoadWeights(class VocalPlayer * const this /* r29 */) {
    // Local variables
    const char * path; // r31
    const char * stem; // r0
    const char * weightsFilename; // r31
    class File * weightsFile; // r30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8009A60C -> 0x8009A87C
void VocalPlayer::CalcNoteWeights(class VocalPlayer * const this /* r29 */) {
    // Local variables
    unsigned char separateParts; // r0
    unsigned int i; // r30
    float w; // f0
    const class VocalPhrase * i; // r28

    // References
    // -> class GameMode * TheGameMode;
}

// Range: 0x8009A87C -> 0x8009A9DC
float VocalPlayer::IntegrateWeights(const class VocalPlayer * const this /* r28 */, float t1 /* f29 */, float t2 /* f30 */) {
    // Local variables
    float x; // f0
    int beg; // r31
    int end; // r29
    int frame; // r30
    float total; // f31
}

// Range: 0x8009A9DC -> 0x8009AA34
float VocalPlayer::GetWeight() {}

// Range: 0x8009AA34 -> 0x8009AA80
float VocalPlayer::NoteK() {
    // Local variables
    float f; // f1
}

// Range: 0x8009AA80 -> 0x8009AAA0
class VocalPhrase * VocalPlayer::GetNextPhraseMarker() {
    // Local variables
    const class VocalPhrase * out; // r4
}

// Range: 0x8009AAA0 -> 0x8009AAD4
float VocalPlayer::CalcPhraseScoreMax() {
    // Local variables
    float w; // f1
    unsigned int i; // r6
}

// Range: 0x8009AAD4 -> 0x8009AD34
void VocalPlayer::CorrectOctave(class VocalPlayer * const this /* r28 */, float ms /* f30 */, int endNote /* r29 */, float & micPitch /* r30 */) {
    // Local variables
    float bestDist; // f31
    int note; // r31
    float dist; // f29
    float absDist; // f28
    float modDist; // r1+0x18
}

// Range: 0x8009AD34 -> 0x8009AE90
void VocalPlayer::GetNoteRange(const class VocalPlayer * const this /* r27 */, float ms /* f31 */, int & beginNote /* r28 */, int & endNote /* r29 */) {
    // Local variables
    int cur; // [invalid]
    const class vector & notes; // r0
    int num; // r26
    int note; // r30
    float noteBegin; // f0
    float noteEnd; // f3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8009AE90 -> 0x8009B070
float VocalPlayer::GetSloppyPitch() {
    // Local variables
    float p1; // f6
    float p2; // f1
    float d1; // f0
    float d2; // f0
}

// Range: 0x8009B070 -> 0x8009B138
float VocalPlayer::ScoreNote(const class VocalPlayer * const this /* r29 */, float ms /* f30 */, int note /* r30 */, float micPitch /* f31 */, float & desiredPitchOut /* r31 */) {
    // Local variables
    float dist; // f0
    float hit; // f31
}

// Range: 0x8009B138 -> 0x8009B1B8
float VocalPlayer::GetNoteSliceWeight(const class VocalPlayer * const this /* r30 */, int note /* r31 */) {
    // Local variables
    float w; // f0
}

static class Message msg; // size: 0x8, address: 0x809778D8
// Range: 0x8009B1B8 -> 0x8009B5F8
void VocalPlayer::Poll(class VocalPlayer * const this /* r29 */, float ms /* f29 */, const class SongPos & pos /* r30 */) {
    // Local variables
    const class VocalNote * next; // r0
    float micPitch; // f31
    float micEnergy; // f30
    int tick; // r0
    float tempo; // f1
    class Mic * mic; // r31
    int vocal_level; // r31

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class TempoMap * TheTempoMap;
}

// Range: 0x8009B5F8 -> 0x8009B660
float VocalPlayer::GetCompensatedTime(class VocalPlayer * const this /* r31 */, float ms /* f31 */) {
    // Local variables
    float adjustedTime; // f1

    // References
    // -> class ProfileMgr TheProfileMgr;
}

static class Message msg; // size: 0x8, address: 0x809778F0
// Range: 0x8009B660 -> 0x8009B9A0
void VocalPlayer::LocalEndgameEnergy(int level /* r30 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class WorldDir * TheWorld;
}

// Range: 0x8009B9A0 -> 0x8009B9AC
void VocalPlayer::SendCanChat() {}

enum State {
    kInvalidState = 0,
    kStart = 1,
    kPlaying = 2,
    kPaused = 3,
    kReleased = 4,
    kDone = 5,
};
struct _AXPBMIX {
    // total size: 0x30
    unsigned short vL; // offset 0x0, size 0x2
    unsigned short vDeltaL; // offset 0x2, size 0x2
    unsigned short vR; // offset 0x4, size 0x2
    unsigned short vDeltaR; // offset 0x6, size 0x2
    unsigned short vAuxAL; // offset 0x8, size 0x2
    unsigned short vDeltaAuxAL; // offset 0xA, size 0x2
    unsigned short vAuxAR; // offset 0xC, size 0x2
    unsigned short vDeltaAuxAR; // offset 0xE, size 0x2
    unsigned short vAuxBL; // offset 0x10, size 0x2
    unsigned short vDeltaAuxBL; // offset 0x12, size 0x2
    unsigned short vAuxBR; // offset 0x14, size 0x2
    unsigned short vDeltaAuxBR; // offset 0x16, size 0x2
    unsigned short vAuxCL; // offset 0x18, size 0x2
    unsigned short vDeltaAuxCL; // offset 0x1A, size 0x2
    unsigned short vAuxCR; // offset 0x1C, size 0x2
    unsigned short vDeltaAuxCR; // offset 0x1E, size 0x2
    unsigned short vS; // offset 0x20, size 0x2
    unsigned short vDeltaS; // offset 0x22, size 0x2
    unsigned short vAuxAS; // offset 0x24, size 0x2
    unsigned short vDeltaAuxAS; // offset 0x26, size 0x2
    unsigned short vAuxBS; // offset 0x28, size 0x2
    unsigned short vDeltaAuxBS; // offset 0x2A, size 0x2
    unsigned short vAuxCS; // offset 0x2C, size 0x2
    unsigned short vDeltaAuxCS; // offset 0x2E, size 0x2
};
struct _AXPBITD {
    // total size: 0xE
    unsigned short flag; // offset 0x0, size 0x2
    unsigned short bufferHi; // offset 0x2, size 0x2
    unsigned short bufferLo; // offset 0x4, size 0x2
    unsigned short shiftL; // offset 0x6, size 0x2
    unsigned short shiftR; // offset 0x8, size 0x2
    unsigned short targetShiftL; // offset 0xA, size 0x2
    unsigned short targetShiftR; // offset 0xC, size 0x2
};
struct _AXPBDPOP {
    // total size: 0x18
    signed short aL; // offset 0x0, size 0x2
    signed short aAuxAL; // offset 0x2, size 0x2
    signed short aAuxBL; // offset 0x4, size 0x2
    signed short aAuxCL; // offset 0x6, size 0x2
    signed short aR; // offset 0x8, size 0x2
    signed short aAuxAR; // offset 0xA, size 0x2
    signed short aAuxBR; // offset 0xC, size 0x2
    signed short aAuxCR; // offset 0xE, size 0x2
    signed short aS; // offset 0x10, size 0x2
    signed short aAuxAS; // offset 0x12, size 0x2
    signed short aAuxBS; // offset 0x14, size 0x2
    signed short aAuxCS; // offset 0x16, size 0x2
};
struct _AXPBVE {
    // total size: 0x4
    unsigned short currentVolume; // offset 0x0, size 0x2
    signed short currentDelta; // offset 0x2, size 0x2
};
struct _AXPBADDR {
    // total size: 0x10
    unsigned short loopFlag; // offset 0x0, size 0x2
    unsigned short format; // offset 0x2, size 0x2
    unsigned short loopAddressHi; // offset 0x4, size 0x2
    unsigned short loopAddressLo; // offset 0x6, size 0x2
    unsigned short endAddressHi; // offset 0x8, size 0x2
    unsigned short endAddressLo; // offset 0xA, size 0x2
    unsigned short currentAddressHi; // offset 0xC, size 0x2
    unsigned short currentAddressLo; // offset 0xE, size 0x2
};
struct _AXPBADPCM {
    // total size: 0x28
    unsigned short a[8][2]; // offset 0x0, size 0x20
    unsigned short gain; // offset 0x20, size 0x2
    unsigned short pred_scale; // offset 0x22, size 0x2
    unsigned short yn1; // offset 0x24, size 0x2
    unsigned short yn2; // offset 0x26, size 0x2
};
struct _AXPBSRC {
    // total size: 0xE
    unsigned short ratioHi; // offset 0x0, size 0x2
    unsigned short ratioLo; // offset 0x2, size 0x2
    unsigned short currentAddressFrac; // offset 0x4, size 0x2
    unsigned short last_samples[4]; // offset 0x6, size 0x8
};
struct _AXPBADPCMLOOP {
    // total size: 0x6
    unsigned short loop_pred_scale; // offset 0x0, size 0x2
    unsigned short loop_yn1; // offset 0x2, size 0x2
    unsigned short loop_yn2; // offset 0x4, size 0x2
};
struct _AXPBLPF {
    // total size: 0x8
    unsigned short on; // offset 0x0, size 0x2
    unsigned short yn1; // offset 0x2, size 0x2
    unsigned short a0; // offset 0x4, size 0x2
    unsigned short b0; // offset 0x6, size 0x2
};
struct _AXPBBIQUAD {
    // total size: 0x14
    unsigned short on; // offset 0x0, size 0x2
    unsigned short xn1; // offset 0x2, size 0x2
    unsigned short xn2; // offset 0x4, size 0x2
    unsigned short yn1; // offset 0x6, size 0x2
    unsigned short yn2; // offset 0x8, size 0x2
    unsigned short b0; // offset 0xA, size 0x2
    unsigned short b1; // offset 0xC, size 0x2
    unsigned short b2; // offset 0xE, size 0x2
    unsigned short a1; // offset 0x10, size 0x2
    unsigned short a2; // offset 0x12, size 0x2
};
struct _AXPBRMTMIX {
    // total size: 0x20
    unsigned short vMain0; // offset 0x0, size 0x2
    unsigned short vDeltaMain0; // offset 0x2, size 0x2
    unsigned short vAux0; // offset 0x4, size 0x2
    unsigned short vDeltaAux0; // offset 0x6, size 0x2
    unsigned short vMain1; // offset 0x8, size 0x2
    unsigned short vDeltaMain1; // offset 0xA, size 0x2
    unsigned short vAux1; // offset 0xC, size 0x2
    unsigned short vDeltaAux1; // offset 0xE, size 0x2
    unsigned short vMain2; // offset 0x10, size 0x2
    unsigned short vDeltaMain2; // offset 0x12, size 0x2
    unsigned short vAux2; // offset 0x14, size 0x2
    unsigned short vDeltaAux2; // offset 0x16, size 0x2
    unsigned short vMain3; // offset 0x18, size 0x2
    unsigned short vDeltaMain3; // offset 0x1A, size 0x2
    unsigned short vAux3; // offset 0x1C, size 0x2
    unsigned short vDeltaAux3; // offset 0x1E, size 0x2
};
struct _AXPBRMTDPOP {
    // total size: 0x10
    signed short aMain0; // offset 0x0, size 0x2
    signed short aMain1; // offset 0x2, size 0x2
    signed short aMain2; // offset 0x4, size 0x2
    signed short aMain3; // offset 0x6, size 0x2
    signed short aAux0; // offset 0x8, size 0x2
    signed short aAux1; // offset 0xA, size 0x2
    signed short aAux2; // offset 0xC, size 0x2
    signed short aAux3; // offset 0xE, size 0x2
};
struct _AXPBRMTSRC {
    // total size: 0xA
    unsigned short currentAddressFrac; // offset 0x0, size 0x2
    unsigned short last_samples[4]; // offset 0x2, size 0x8
};
union __AXPBRMTIIR {
    struct _AXPBLPF lpf; // offset 0x0, size 0x8
    struct _AXPBBIQUAD biquad; // offset 0x0, size 0x14
};
struct _AXPB {
    // total size: 0x140
    unsigned short nextHi; // offset 0x0, size 0x2
    unsigned short nextLo; // offset 0x2, size 0x2
    unsigned short currHi; // offset 0x4, size 0x2
    unsigned short currLo; // offset 0x6, size 0x2
    unsigned short srcSelect; // offset 0x8, size 0x2
    unsigned short coefSelect; // offset 0xA, size 0x2
    unsigned long mixerCtrl; // offset 0xC, size 0x4
    unsigned short state; // offset 0x10, size 0x2
    unsigned short type; // offset 0x12, size 0x2
    struct _AXPBMIX mix; // offset 0x14, size 0x30
    struct _AXPBITD itd; // offset 0x44, size 0xE
    struct _AXPBDPOP dpop; // offset 0x52, size 0x18
    struct _AXPBVE ve; // offset 0x6A, size 0x4
    struct _AXPBADDR addr; // offset 0x6E, size 0x10
    struct _AXPBADPCM adpcm; // offset 0x7E, size 0x28
    struct _AXPBSRC src; // offset 0xA6, size 0xE
    struct _AXPBADPCMLOOP adpcmLoop; // offset 0xB4, size 0x6
    struct _AXPBLPF lpf; // offset 0xBA, size 0x8
    struct _AXPBBIQUAD biquad; // offset 0xC2, size 0x14
    unsigned short remote; // offset 0xD6, size 0x2
    unsigned short rmtMixerCtrl; // offset 0xD8, size 0x2
    struct _AXPBRMTMIX rmtMix; // offset 0xDA, size 0x20
    struct _AXPBRMTDPOP rmtDpop; // offset 0xFA, size 0x10
    struct _AXPBRMTSRC rmtSrc; // offset 0x10A, size 0xA
    union __AXPBRMTIIR rmtIIR; // offset 0x114, size 0x14
    unsigned short pad[12]; // offset 0x128, size 0x18
};
struct _AXVPB {
    // total size: 0x168
    void * next; // offset 0x0, size 0x4
    void * prev; // offset 0x4, size 0x4
    void * next1; // offset 0x8, size 0x4
    unsigned long priority; // offset 0xC, size 0x4
    void (* callback)(void *); // offset 0x10, size 0x4
    unsigned long userContext; // offset 0x14, size 0x4
    unsigned long index; // offset 0x18, size 0x4
    unsigned long sync; // offset 0x1C, size 0x4
    unsigned long depop; // offset 0x20, size 0x4
    void * itdBuffer; // offset 0x24, size 0x4
    struct _AXPB pb; // offset 0x28, size 0x140
};
class EnvelopeWii {
    // total size: 0x48
    class Timer mTimer; // offset 0x0, size 0x38
    float mAttackDuration; // offset 0x38, size 0x4
    float mReleaseDuration; // offset 0x3C, size 0x4
    unsigned char mInRelease; // offset 0x40, size 0x1
    unsigned char mIsPaused; // offset 0x41, size 0x1
    float mReleaseStart; // offset 0x44, size 0x4
};
class Voice {
    // total size: 0xB0
    enum State mState; // offset 0x0, size 0x4
    struct _AXVPB * mVoice; // offset 0x4, size 0x4
    unsigned char * mVoiceBuffer; // offset 0x8, size 0x4
    int mVoiceBufferSize; // offset 0xC, size 0x4
    int mNextBufferSyncPtr; // offset 0x10, size 0x4
    int mNextBufferSyncSize; // offset 0x14, size 0x4
    unsigned char * mLastBufferSyncEndPtr; // offset 0x18, size 0x4
    char * mBufferStart; // offset 0x1C, size 0x4
    int mBufferBytes; // offset 0x20, size 0x4
    int mStartByte; // offset 0x24, size 0x4
    int mLoopByte; // offset 0x28, size 0x4
    int mSampleRate; // offset 0x2C, size 0x4
    float mSpeed; // offset 0x30, size 0x4
    unsigned char mMixDirty; // offset 0x34, size 0x1
    float mVolume; // offset 0x38, size 0x4
    float mPan; // offset 0x3C, size 0x4
    float mLastVolume; // offset 0x40, size 0x4
    enum FXCore mFXCore; // offset 0x44, size 0x4
    unsigned char mFXActive; // offset 0x48, size 0x1
    unsigned char mUseInPlace; // offset 0x49, size 0x1
    class PitchShiftEffect * mPitchEffect; // offset 0x4C, size 0x4
    float mPitch; // offset 0x50, size 0x4
    unsigned char * mLastPitchEffectWritePtr; // offset 0x54, size 0x4
    enum Format mFormat; // offset 0x58, size 0x4
    class EnvelopeWii mEnvelope; // offset 0x60, size 0x48
    unsigned char mFirstPoll; // offset 0xA8, size 0x1
};
class MicWii : public Mic {
    // total size: 0x20A0
    int mIndex; // offset 0x4, size 0x4
    class VocalNote * (* mNoteCallback)(float); // offset 0x8, size 0x4
    unsigned char mOn; // offset 0xC, size 0x1
    unsigned char mConnected; // offset 0xD, size 0x1
    unsigned char mDMA; // offset 0xE, size 0x1
    unsigned char mFXActive; // offset 0xF, size 0x1
    unsigned char mPitchShift; // offset 0x10, size 0x1
    unsigned char mComp; // offset 0x11, size 0x1
    unsigned char mRunning; // offset 0x12, size 0x1
    unsigned char mVoiced; // offset 0x13, size 0x1
    unsigned char mLastVoiced; // offset 0x14, size 0x1
    unsigned char mMute; // offset 0x15, size 0x1
    unsigned char mAttemptedStart; // offset 0x16, size 0x1
    unsigned char * mPlaybackBuffer; // offset 0x18, size 0x4
    unsigned char * mPlaybackWritePtr; // offset 0x1C, size 0x4
    signed short mOutBuf[4096]; // offset 0x20, size 0x2000
    int mPadNum; // offset 0x2020, size 0x4
    int mOutBufSamples; // offset 0x2024, size 0x4
    long mMicHandle; // offset 0x2028, size 0x4
    float mGain; // offset 0x202C, size 0x4
    float mEarVol; // offset 0x2030, size 0x4
    float mCompOut; // offset 0x2034, size 0x4
    float mVolume; // offset 0x2038, size 0x4
    float mPan; // offset 0x203C, size 0x4
    float mSpeed; // offset 0x2040, size 0x4
    float mEnergy; // offset 0x2044, size 0x4
    float mPitch; // offset 0x2048, size 0x4
    float mVoiceSpeed; // offset 0x204C, size 0x4
    float mAvgLag; // offset 0x2050, size 0x4
    float mLastLag; // offset 0x2054, size 0x4
    float mLastEnergy; // offset 0x2058, size 0x4
    float mLastPitch; // offset 0x205C, size 0x4
    class ADSR mADSR; // offset 0x2060, size 0x28
    class Voice * mVoice; // offset 0x2088, size 0x4
    enum FXCore mFXCore; // offset 0x208C, size 0x4
};
// Range: 0x8009B9AC -> 0x8009C3B0
float VocalPlayer::Poll_(class VocalPlayer * const this /* r28 */, float ms /* f28 */, float micPitch /* r1+0x8 */, float micEnergy /* f29 */, struct SpeechAnalysis * pMicAnalysis /* r29 */) {
    // Local variables
    float micPhonemeAccuracy; // f31
    const class VocalNote * note; // r0
    unsigned char canChat; // r29
    int padNum; // r0
    class MicWii * mic; // r29
    int beginNote; // r1+0x18
    int endNote; // r1+0x14
    float bestHit; // f30
    int noteMatched; // r1+0x10
    int idx; // r0
    int vibPeriod; // r30
    int i; // r29
    float frameVibBonus; // f27
    float delta; // f3
    int acceleration; // r0
    float lastPhraseMs; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class TaskMgr TheTaskMgr;
    // -> class GameMode * TheGameMode;
    // -> class SynthWii * TheWiiSynth;
    // -> class WiiFX TheWiiFX;
    // -> class SongDB * TheSongDB;
}

// Range: 0x8009C3B0 -> 0x8009C470
void VocalPlayer::AddPhrasePoints(class VocalPlayer * const this /* r31 */) {
    // Local variables
    float prevScore; // f2
    float delta; // f31
}

// Range: 0x8009C470 -> 0x8009C560
void VocalPlayer::UpdateSmoothScore(class VocalPlayer * const this /* r31 */) {
    // Local variables
    float score; // f2
}

static class Message pitch_msg; // size: 0x8, address: 0x80977908
// Range: 0x8009C560 -> 0x8009C990
void VocalPlayer::SendVocalState(class VocalPlayer * const this /* r31 */, float ms /* f27 */, float micPitch /* f28 */, float pitchDetune /* f29 */) {
    // Local variables
    float frac; // f0

    // References
    // -> static class Message pitch_msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8009C990 -> 0x8009CAD0
float VocalPlayer::GetBestHit(class VocalPlayer * const this /* r27 */, float ms /* f28 */, int endNote /* r28 */, float micPitch /* f29 */, float micPhonemeAccuracy /* f30 */, int & noteMatched /* r29 */, float & targetPitch /* r30 */) {
    // Local variables
    float bestHit; // f31
    int note; // r31
    float outPitch; // r1+0x8
    float hit; // f1
}

// Range: 0x8009CAD0 -> 0x8009CD20
void VocalPlayer::AddScore(class VocalPlayer * const this /* r31 */, float ms /* f29 */, int noteMatched /* r30 */, float bestHit /* f30 */) {
    // Local variables
    float noteWeight; // f0
    float mult; // f3
    float pts; // f31
    float bestPossible; // f27
    float diff; // f1
    float scoreDelta; // f1
}

// Range: 0x8009CD20 -> 0x8009CD58
int VocalPlayer::CalculatePhraseRating() {
    // Local variables
    int i; // r5
}

static class Message net_msg; // size: 0x8, address: 0x80977920
static class Message msg; // size: 0x8, address: 0x80977938
static class Message msg; // size: 0x8, address: 0x80977950
// Range: 0x8009CD58 -> 0x8009D80C
void VocalPlayer::HandlePhraseEnd(class VocalPlayer * const this /* r26 */) {
    // Local variables
    const class VocalPhrase * nextPhrase; // r1+0x28
    float nextPhraseMs; // f31
    float nextnextPhraseMs; // f30
    const class VocalPhrase * nextnextPhrase; // r0
    int rating; // r28
    int points; // r25
    int bonus; // r24
    int mult; // r0
    unsigned char spotlightSuccess; // r27
    int lastPhraseScore; // r31
    class Message ratingMsg; // r1+0x98

    // References
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message net_msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class SongDB * TheSongDB;
    // -> class GameMode * TheGameMode;
}

// Range: 0x8009D80C -> 0x8009D8C4
void VocalPlayer::LocalScorePhrase(class VocalPlayer * const this /* r29 */, int rating /* r30 */, unsigned char spotlightSuccess /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8009D8C4 -> 0x8009D9E4
void VocalPlayer::UpdateMinMaxPitch() {
    // Local variables
    const class VocalPhrase * cur; // r8
    const class VocalPhrase * end; // r0
    unsigned char foundPitchedNote; // r9
    const class vector & notes; // r0
    int i; // r10
}

// Range: 0x8009D9E4 -> 0x8009DAD0
void VocalPlayer::HookupTrack(class VocalPlayer * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__5Track;
    // -> struct [anonymous] __RTTI__10VocalTrack;
}

// Range: 0x8009DAD0 -> 0x8009DADC
void VocalPlayer::UnHookTrack() {}

// Range: 0x8009DADC -> 0x8009DAF8
void VocalPlayer::SetMusicSpeed() {}

// Range: 0x8009DAF8 -> 0x8009DB08
void VocalPlayer::SetAutoplay() {}

// Range: 0x8009DB08 -> 0x8009DB10
void VocalPlayer::SetTutorialArrow() {}

static class Message scream; // size: 0x8, address: 0x80977968
// Range: 0x8009DB10 -> 0x8009DD40
void VocalPlayer::DetectScream(class VocalPlayer * const this /* r31 */, float ms /* f30 */, float energy /* f31 */) {
    // References
    // -> static class Message scream;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8009DD40 -> 0x8009DD4C
void VocalPlayer::CancelScream() {}

// Range: 0x8009DD4C -> 0x8009DD6C
void VocalPlayer::RemoteVocalState() {}

// Range: 0x8009DD6C -> 0x8009DE34
class DataNode VocalPlayer::OnMidiParser(class VocalPlayer * const this /* r30 */, class DataArray * d /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> class GameMode * TheGameMode;
}

// Range: 0x8009DE34 -> 0x8009E0C4
class DataNode VocalPlayer::OnPlayTambourine(class VocalPlayer * const this /* r29 */, class DataArray * d /* r27 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Sequence;
    // -> class Synth * TheSynth;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x8009E0C4 -> 0x8009E124
int VocalPlayer::TambourinePercentage() {}

// Range: 0x8009E124 -> 0x8009E1B4
void VocalPlayer::OnRemoteTambourineSucceeding(class VocalPlayer * const this /* r31 */, class DataArray * msg /* r30 */) {
    // Local variables
    class BandTrack * track; // r31
}

static class Message msg; // size: 0x8, address: 0x80977980
static class Message tutMsg; // size: 0x8, address: 0x80977998
// Range: 0x8009E1B4 -> 0x8009E5FC
void VocalPlayer::TambourineSucceed(class VocalPlayer * const this /* r28 */, int index /* r27 */) {
    // Local variables
    int perc; // r29
    class BandTrack * track; // r0

    // References
    // -> static class Message tutMsg;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message msg; // size: 0x8, address: 0x809779B0
static class Message tutMsg; // size: 0x8, address: 0x809779C8
// Range: 0x8009E5FC -> 0x8009E9D4
void VocalPlayer::TambourineFail(class VocalPlayer * const this /* r28 */, int index /* r29 */, unsigned char swing /* r27 */) {
    // References
    // -> static class Message tutMsg;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8009E9D4 -> 0x8009EA94
void VocalPlayer::CheckRemoteTambourine(class VocalPlayer * const this /* r29 */) {}

// Range: 0x8009EA94 -> 0x8009ED90
void VocalPlayer::CheckWiiTambourine(class VocalPlayer * const this /* r28 */, float ms /* f31 */, int acceleration /* r1+0x8 */, float energy /* r1+0xC */, unsigned char usb /* r29 */) {
    // Local variables
    unsigned char wiiSwinging; // r30
    unsigned char swinging; // r29
    int delta_tick; // r3
}

// Range: 0x8009ED90 -> 0x8009EE88
void VocalPlayer::TambourineSwing(class VocalPlayer * const this /* r29 */, int tick /* r30 */) {
    // Local variables
    int delta_tick; // r31
}

static class Symbol tambourine; // size: 0x4, address: 0x80A4A178
static class Message send_solo_end; // size: 0x8, address: 0x809779E0
// Range: 0x8009EE88 -> 0x8009F46C
void VocalPlayer::SetTambourine(class VocalPlayer * const this /* r27 */, unsigned char tamb /* r28 */) {
    // Local variables
    int dur; // r26
    const class VocalPhrase * next; // r1+0x14
    int start; // r30
    int end; // r29
    int idx; // r26
    int tick; // r25
    int pct; // r29
    class BandTrack * track; // r25

    // References
    // -> static class Message send_solo_end;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol tambourine;
}

static class Symbol tambourine; // size: 0x4, address: 0x80A4A180
// Range: 0x8009F46C -> 0x8009F6F8
void VocalPlayer::ComputeTambourinePoints(const class VocalPlayer * const this /* r23 */, int & points /* r24 */, int & bonus_points /* r25 */) {
    // Local variables
    unsigned char separate_parts; // r0
    class Symbol resultToken; // r1+0x14
    int bonus_points_per_gem; // r1+0x10
    int num_tamb_gems; // r30
    const class VocalPhrase * phrase; // r29
    int start_tick; // r28
    int end_tick; // r27
    int start_gem; // r26
    int end_gem; // r28

    // References
    // -> class Scoring * TheScoring;
    // -> const char * gNullStr;
    // -> static class Symbol tambourine;
    // -> class GameMode * TheGameMode;
}

static class Symbol tambourine; // size: 0x4, address: 0x80A4A188
// Range: 0x8009F6F8 -> 0x8009F7E0
void VocalPlayer::LocalTambourineSoloEnd(class VocalPlayer * const this /* r28 */, int pct /* r31 */, int num_gems /* r29 */) {
    // Local variables
    class Symbol resultToken; // r1+0x14
    int points_per_gem; // r1+0x10
    int points; // r29

    // References
    // -> class Scoring * TheScoring;
    // -> const char * gNullStr;
    // -> static class Symbol tambourine;
}

// Range: 0x8009F7E0 -> 0x8009F9E4
unsigned char VocalPlayer::OnMsg(class VocalPlayer * const this /* r29 */, const class ButtonDownMsg & msg /* r30 */) {
    // Local variables
    enum JoypadButton but; // r0

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class ProfileMgr TheProfileMgr;
}

static class Symbol vocalist_volume; // size: 0x4, address: 0x80A4A190
// Range: 0x8009F9E4 -> 0x8009FACC
unsigned char VocalPlayer::OnMsg(class VocalPlayer * const this /* r29 */, const class ButtonUpMsg & msg /* r30 */) {
    // Local variables
    enum JoypadButton but; // r0

    // References
    // -> static class Symbol vocalist_volume;
}

// Range: 0x8009FACC -> 0x8009FB3C
void VocalPlayer::OnGameOver(class VocalPlayer * const this /* r31 */) {
    // Local variables
    class Mic * mic; // r0
}

// Range: 0x8009FB3C -> 0x8009FBBC
void VocalPlayer::EnableController(class VocalPlayer * const this /* r30 */) {
    // Local variables
    class Mic * mic; // r31
}

// Range: 0x8009FBBC -> 0x8009FBC0
void VocalPlayer::DisableController() {}

// Range: 0x8009FBC0 -> 0x8009FC14
void VocalPlayer::OnDisableController(class VocalPlayer * const this /* r31 */) {
    // Local variables
    class Mic * mic; // r0
}

// Range: 0x8009FC14 -> 0x8009FC60
unsigned char VocalPlayer::InEmptyPhrase() {}

// Range: 0x8009FC60 -> 0x8009FD20
unsigned char VocalPlayer::ShouldDrainEnergy(const class VocalPlayer * const this /* r29 */) {
    // Local variables
    int slot; // r30

    // References
    // -> class SongDB * TheSongDB;
    // -> class GameMode * TheGameMode;
}

static class Message msg; // size: 0x8, address: 0x809779F8
// Range: 0x8009FD20 -> 0x8009FEE8
void VocalPlayer::HitCoda(class VocalPlayer * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8009FEE8 -> 0x8009FF4C
float VocalPlayer::FramePhraseMeterFrac(const class VocalPlayer * const this /* r31 */) {}

// Range: 0x8009FF4C -> 0x8009FFD8
unsigned char VocalPlayer::PressingToTalk(class VocalPlayer * const this /* r31 */) {
    // Local variables
    class JoypadData * jd; // r0
}

// Range: 0x8009FFD8 -> 0x800A0020
unsigned char VocalPlayer::CanChat(class VocalPlayer * const this /* r31 */) {
    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x800A0020 -> 0x800A0060
void VocalPlayer::LocalHitCoda(class VocalPlayer * const this /* r31 */) {}

// Range: 0x800A0060 -> 0x800A0098
void VocalPlayer::LocalBlowCoda(class VocalPlayer * const this /* r31 */) {}

// Range: 0x800A0098 -> 0x800A00BC
class vector & VocalPlayer::TambourineGems() {}

// Range: 0x800A00BC -> 0x800A0114
void VocalPlayer::UpdateVocalStyle(class VocalPlayer * const this /* r31 */) {
    // Local variables
    class GameplayOptions * options; // r0
}

// Range: 0x800A0114 -> 0x800A0174
unsigned char VocalPlayer::Freestyling(const class VocalPlayer * const this /* r30 */) {}

// Range: 0x800A0174 -> 0x800A0608
void VocalPlayer::SetMicSpecialFx(class VocalPlayer * const this /* r28 */, unsigned char on /* r29 */, unsigned char reverb /* r30 */) {
    // Local variables
    class FxParamAutoLock lock; // r1+0x8
    class ObjDirItr itr; // r1+0x1C

    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6FxSend;
}

static class Symbol tempo_sync; // size: 0x4, address: 0x80A4A198
static class Symbol tempo; // size: 0x4, address: 0x80A4A1A0
// Range: 0x800A0608 -> 0x800A09FC
void VocalPlayer::SetMicFxTempo(float tempoVal /* f31 */) {
    // Local variables
    class ObjDirItr itr; // r1+0x28
    const class DataNode * prop; // r0

    // References
    // -> static class Symbol tempo;
    // -> static class Symbol tempo_sync;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6FxSend;
}

// Range: 0x800A09FC -> 0x800A0A10
void VocalPlayer::SetScreamThresholds() {}

// Range: 0x800A0A10 -> 0x800A0A64
unsigned char VocalPlayer::AutoplaysCoda() {}

// Range: 0x800A0A64 -> 0x800A0AAC
void VocalPlayer::SetTargetGhostScore() {}

// Range: 0x800A0AAC -> 0x800A0AF8
class Mic * VocalPlayer::GetMic() {
    // Local variables
    int pad_num; // r4

    // References
    // -> class Synth * TheSynth;
}

static class Symbol _s; // size: 0x4, address: 0x80A4A1A8
static class Symbol _s; // size: 0x4, address: 0x80A4A1B0
static class Symbol _s; // size: 0x4, address: 0x80A4A1B8
static class Symbol _s; // size: 0x4, address: 0x80A4A1C0
static class Symbol _s; // size: 0x4, address: 0x80A4A1C8
static class Symbol _s; // size: 0x4, address: 0x80A4A1D0
static class Symbol _s; // size: 0x4, address: 0x80A4A1D8
static class Symbol _s; // size: 0x4, address: 0x80A4A1E0
static class Symbol _s; // size: 0x4, address: 0x80A4A1E8
static class Symbol _s; // size: 0x4, address: 0x80A4A1F0
static class Symbol _s; // size: 0x4, address: 0x80A4A1F8
static class Symbol _s; // size: 0x4, address: 0x80A4A200
static class Symbol _s; // size: 0x4, address: 0x80A4A208
static class Symbol _s; // size: 0x4, address: 0x80A4A210
static class Symbol _s; // size: 0x4, address: 0x80A4A218
static class Symbol _s; // size: 0x4, address: 0x80A4A220
static class Symbol _s; // size: 0x4, address: 0x80A4A228
static class Symbol _s; // size: 0x4, address: 0x80A4A230
static class Symbol _s; // size: 0x4, address: 0x80A4A238
static class Symbol _s; // size: 0x4, address: 0x80A4A240
static class Symbol _s; // size: 0x4, address: 0x80A4A248
static class Symbol _s; // size: 0x4, address: 0x80A4A250
static class Symbol _s; // size: 0x4, address: 0x80A4A258
static class Symbol _s; // size: 0x4, address: 0x80A4A260
static class Symbol _s; // size: 0x4, address: 0x80A4A268
static class Symbol _s; // size: 0x4, address: 0x80A4A270
static class Symbol _s; // size: 0x4, address: 0x80A4A278
static class Symbol _s; // size: 0x4, address: 0x80A4A280
static class Symbol _s; // size: 0x4, address: 0x80A4A288
static class Symbol _s; // size: 0x4, address: 0x80A4A290
static class Symbol _s; // size: 0x4, address: 0x80A4A298
static class Symbol _s; // size: 0x4, address: 0x80A4A2A0
static class Symbol _s; // size: 0x4, address: 0x80A4A2A8
static class Symbol _s; // size: 0x4, address: 0x80A4A2B0
static class Symbol _s; // size: 0x4, address: 0x80A4A2B8
static class Symbol _s; // size: 0x4, address: 0x80A4A2C0
static class Symbol _s; // size: 0x4, address: 0x80A4A2C8
static class Symbol _s; // size: 0x4, address: 0x80A4A2D0
static class Symbol _s; // size: 0x4, address: 0x80A4A2D8
// Range: 0x800A0AF8 -> 0x800A1D00
class DataNode VocalPlayer::Handle(class VocalPlayer * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x1E4
} __vt__11VocalPlayer; // size: 0x1E4, address: 0x8087B354
struct {
    // total size: 0x8
} __RTTI__11VocalPlayer; // size: 0x8, address: 0x8087B570
struct {
    // total size: 0xC
} __vt__11ButtonUpMsg; // size: 0xC, address: 0x8087B620
struct {
    // total size: 0x8
} __RTTI__11ButtonUpMsg; // size: 0x8, address: 0x8087B648
struct {
    // total size: 0xC
} __vt__13ButtonDownMsg; // size: 0xC, address: 0x8087B650
struct {
    // total size: 0x8
} __RTTI__13ButtonDownMsg; // size: 0x8, address: 0x8087B678
struct {
    // total size: 0x8
} __RTTI__10MidiParser; // size: 0x8, address: 0x8087B6A8
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class MicWii * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class MicWii * * _M_start; // offset 0x0, size 0x4
    class MicWii * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class SynthWii : public Synth {
    // total size: 0x214
    void * axBuffer; // offset 0x70, size 0x4
    void * mixBuffer; // offset 0x74, size 0x4
    int mVoiceStatus[96]; // offset 0x78, size 0x180
    class vector mMics; // offset 0x1F8, size 0xC
    unsigned char mMicFX; // offset 0x204, size 0x1
    unsigned char mHomePausedVoices; // offset 0x205, size 0x1
    float mMicRecVol; // offset 0x208, size 0x4
    int mMicDataIndex; // offset 0x20C, size 0x4
    int mNumConnectedMics; // offset 0x210, size 0x4
};

