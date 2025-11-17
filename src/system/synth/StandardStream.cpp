#include "math/Decibels.h"
#include "synth/StandardStream.h"
#include "synth/Synth.h"
#include <functional>
#include "utl/Symbols.h"

StandardStream::ChannelParams::ChannelParams()
    : mPan(0.0f), mSlipSpeed(1.0f), mSlipEnabled(0), mADSR(), mFaders(0), mFxSend(0, 0),
      mFXCore(kFXCoreNone), mPitchShift(0) {
    mFaders.AddLocal(_parent)->SetVal(0.0f);
    mFaders.AddLocal(_default)->SetVal(0.0f);
}

StandardStream::StandardStream(File *f, float f1, float f2, Symbol sym, bool b1, bool b2)
    : mPollingEnabled(b2) {
    MILO_ASSERT(f, 0x46);
    mExt = sym;
    mFile = f;
    mInfoChannels = -1;
    unkec = -1.0f;
    Init(f1, f2, sym, false);
}

void StandardStream::Init(float f1, float f2, Symbol sym, bool b) {
    ClearLoopMarkers();
    mAccumulatedLoopbacks = 0.0f;
    mGetInfoOnly = false;
    mState = kInit;
    mSampleRate = 0;
    mBufSecs = f2;
    if (mBufSecs == 0.0f) {
        SystemConfig("synth")->FindData("stream_buf_size", mBufSecs, true);
    }
    mFileStartMs = f1;
    mStartMs = f1;
    mLastStreamTime = f1;
    mTimer.Reset(f1);
    mFloatSamples = false;
    if (!b) {
        MILO_ASSERT(mChanParams.empty(), 0x6B);
        mChanParams.resize(0x20);
        for (int i = 0; i < 0x20; i++) {
            mChanParams[i] = new ChannelParams();
        }
        mVirtualChans = 0;
        mSpeed = 1.0f;
    } else {
        while (mChanParams.size() < 0x20) {
            mChanParams.push_back((new ChannelParams()));
        }
    }
    mJumpFromSamples = 0;
    mJumpToSamples = 0;
    mJumpFromMs = 0.0f;
    mJumpToMs = 0.0f;
    mCurrentSamp = 0;
    mThrottle = SystemConfig("synth", "oggvorbis")->FindFloat("throttle");
    if (mPollingEnabled)
        StartPolling();
    mRdr = TheSynth->NewStreamDecoder(mFile, this, sym);
}

void StandardStream::Destroy() {
    RELEASE(mRdr);
    DeleteAll(mChannels);
}

StandardStream::~StandardStream() { Destroy(); }

const char *StandardStream::GetSoundDisplayName() {
    if (!IsPlaying())
        return gNullStr;
    else if (mFile) {
        return MakeString("StandardStream: %s", FileGetName(mFile->Filename().c_str()));
    } else {
        return MakeString("StandardStream: --no file--");
    }
}

void StandardStream::SynthPoll() { PollStream(); }

void StandardStream::PollStream() {
    if (mRdr) {
        mFrameTimer.Restart();
        mRdr->Poll(
            Max(mFrameTimer.GetLastMs() * mThrottle, mState == kBuffering ? 8.0f : 1.0f)
        );
        std::for_each(
            mChannels.begin(), mChannels.end(), std::mem_fun(&StreamReceiver::Poll)
        );
        MILO_WARN("bad state logic.");
    }
}

void StandardStream::InitInfo(int i1, int sampleRate, bool floatSamples, int i4) {
    int numChannels = i1 + mVirtualChans;
    unk144 = i4;
    mInfoChannels = numChannels;
    unkec = (float)i4 / (float)numChannels;
    if (!mGetInfoOnly) {
        if (mSampleRate == 0) {
            mFloatSamples = floatSamples;
            mSampleRate = sampleRate;
            int i4 = (mBufSecs * (float)sampleRate * 2.0f);
            int i38 = (i4 + (0x18000 - i4 % 0x18000));
            i38 /= 0xC000;
            MILO_WARN("bufBytes % (2*kStreamBufSize) == 0");
            // bufBytes % (2*kStreamBufSize) == 0, where kStreamBufSize = 0xC000

            //   iVar1 = (int)(this->mBufSecs * (float)sampleRate * 2.0);
            //   local_40 = (longlong)iVar1;
            //   iVar1 = iVar1 / 0x18000 + (iVar1 >> 0x1f);
            //   iVar1 = (iVar1 - (iVar1 >> 0x1f)) * 0x18000 + 0x18000;
            //   iVar2 = iVar1 / 0x18000 + (iVar1 >> 0x1f);
            //   if (iVar1 != (iVar2 - (iVar2 >> 0x1f)) * 0x18000) {
            //     pcVar3 = ::MakeString(kAssertStr,::@stringBase0,0x142,
            //                           s_bufBytes_%_(2*kStreamBufSize)_==_80c3131e);
            //     Debug::Fail((Debug *)TheDebug,pcVar3);
            //   }
            //   iVar1 = iVar1 / 0xc000 + (iVar1 >> 0x1f);
            //   TVar16 = (TextStream)(iVar1 - (iVar1 >> 0x1f));
            //   Symbol::Symbol(&local_50,s_max_slip_80c31341);
            //   SVar4.mStr = (char *)Symbol::Symbol(&SStack_4c,s_iop_80c3134a);
            //   SVar5.mStr = (char *)Symbol::Symbol(aSStack_48,s_synth_80c312a1);
            //   pDVar6 = (DataArray *)SystemConfig(SVar5,SVar4);

            int i3c =
                (((mSampleRate * SystemConfig("synth", "iop")->FindInt("max_slip")) / 1000
                  << 1)
                 / 0xC000)
                    * 2
                + 4;
            MaxEq(i3c, i38);
            for (int i = 0; i < numChannels; i++) {
                mChannels.push_back(
                    StreamReceiver::New(i38, sampleRate, mChanParams[i]->mSlipEnabled, i)
                );
            }
            for (int i = 0; i < mVirtualChans; i++) {
                unkf4.push_back(_MemAlloc((mFloatSamples ? 4 : 2) << 0xB, 0));
            }
            mState = kBuffering;
        } else {
            MILO_ASSERT(numChannels == mChannels.size(), 0x161);
            MILO_ASSERT(mSampleRate == sampleRate, 0x162);
            MILO_ASSERT(mFloatSamples == floatSamples, 0x163);
        }
        if (mJumpSamplesInvalid) {
            setJumpSamplesFromMs(mJumpFromMs, mJumpToMs);
        }
        MILO_ASSERT(mChanParams.size() >= numChannels, 0x16C);
        int i = 0;
        for (; i < numChannels; i++) {
            mChannels[i]->SetPan(mChanParams[i]->mPan);
            UpdateSpeed(i);
            mChannels[i]->SetADSR(mChanParams[i]->mADSR);
            mChannels[i]->SetFXCore(mChanParams[i]->mFXCore);
            mChannels[i]->SetPitchShift(mChanParams[i]->mPitchShift);
        }
        for (; i < mChanParams.size(); i++) {
            delete mChanParams[i];
        }
        mChanParams.resize(numChannels);
        numChannels = MsToSamp(mFileStartMs);
        mCurrentSamp = numChannels;
        if (numChannels != 0) {
            mRdr->Seek(numChannels);
        }
        Faders()->SetDirty();
        UpdateFXSends();
    }
}

bool StandardStream::StuffChannels() {
    bool ret = true;
    for (int i = 0; i < mChannels.size(); i++) {
        if (!mChannels[i]->Ready())
            ret = false;
    }
    if (mRdr && mRdr->Done() && mJumpFromSamples == 0) {
        std::for_each(
            mChannels.begin(), mChannels.end(), std::mem_fun(&StreamReceiver::EndData)
        );
    }
    return ret;
}

#define DIM(lol) 0x1EU

int StandardStream::ConsumeData(void **v, int i1, int i2) {
    if (mGetInfoOnly)
        return 0;
    int numChannels = mChannels.size();
    int realChannels = numChannels - mVirtualChans;
    MILO_ASSERT(numChannels != 0, 0x1A9);
    if (i2 >= 0 && i2 != mCurrentSamp) {
        MILO_LOG("sample mismatch: expected %i, got %i\n", mCurrentSamp, i2);
        mCurrentSamp = i2;
    }
    MILO_ASSERT(numChannels < DIM(pcm), 0x1B3);
    MILO_ASSERT(mCurrentSamp <= mJumpFromSamples, 0x1CF);
}

bool StandardStream::Fail() { return mRdr && mRdr->Fail(); }

bool StandardStream::IsReady() const {
    if (mState - 2 <= 3U) {
        if ((1 << mState) & 0xB)
            return true;
    }
    return false;
}

bool StandardStream::IsFinished() const { return mState == kFinished; }
bool StandardStream::IsPlaying() const { return mState == kPlaying; }
bool StandardStream::IsPaused() const { return mState == kStopped; }
int StandardStream::GetNumChannels() const { return mChannels.size(); }
int StandardStream::GetNumChanParams() const { return mChanParams.size(); }

void StandardStream::Play() {
    MILO_ASSERT(IsReady() || mState == kSuspended, 0x227);
    UpdateVolumes();
    std::for_each(mChannels.begin(), mChannels.end(), std::mem_fun(&StreamReceiver::Play));
    mState = kPlaying;
    mTimer.Start();
}

DECOMP_FORCEACTIVE(
    StandardStream, "mState == kStopped || mState == kPlaying || mState == kSuspended"
)

void StandardStream::Stop() {
    if (mState == kPlaying) {
        std::for_each(
            mChannels.begin(), mChannels.end(), std::mem_fun(&StreamReceiver::Stop)
        );
        mState = kStopped;
        mTimer.Stop();
    }
}

void StandardStream::Resync(float f) {
    int bytes;
    while (!mFile->ReadDone(bytes))
        ;
    Destroy();
    mFile->Seek(0, 0);
    float f88 = mJumpFromMs;
    float f8c = mJumpToMs;
    String str94 = mJumpFile;
    Init(f, mBufSecs, mExt, true);
    if (f88 != 0) {
        SetJump(f88, f8c, str94.c_str());
    }
}

void StandardStream::LoadMarkerList(const char *cc) {
    ClearMarkerList();
    FileStream stream(cc, FileStream::kRead, 1);
    int i94 = 0;
    stream >> i94;
    int i98 = 0;
    stream >> i98;
    for (int i = 0; i < i98; i++) {
        Marker marker;
        stream >> marker.name;
        stream >> marker.position;
        marker.posMS = ((float)marker.position * 1000.0f) / (float)i94;
        AddMarker(marker);
    }
}

void StandardStream::ClearMarkerList() { mMarkerList.clear(); }

void StandardStream::AddMarker(Marker marker) { mMarkerList.push_back(marker); }

int StandardStream::MarkerListSize() const { return mMarkerList.size(); }

bool StandardStream::MarkerAt(int idx, Marker &marker) const {
    if (idx >= MarkerListSize() || idx < 0)
        return false;
    else {
        marker = mMarkerList[idx];
        return true;
    }
}

void StandardStream::SetLoop(String &str1, String &str2) {
    for (int i = 0; i < mMarkerList.size(); i++) {
        if (mMarkerList[i].name == str1) {
            mStartMarker = mMarkerList[i];
        }
        if (mMarkerList[i].name == str2) {
            mEndMarker = mMarkerList[i];
        }
    }
    SetJump(mEndMarker.posMS, mStartMarker.posMS, 0);
}

bool StandardStream::CurrentLoopPoints(Marker &start, Marker &end) {
    if (mJumpFromSamples == 0)
        return false;
    else {
        start = mStartMarker;
        end = mEndMarker;
        return true;
    }
}

void StandardStream::AbandonLoop() { ClearJump(); }

void StandardStream::ClearLoopMarkers() {
    mEndMarker.position = 0;
    mEndMarker.name = "";
    mStartMarker.position = 0;
    mStartMarker.name = "";
    mAccumulatedLoopbacks = 0;
}

void StandardStream::SetJump(float fromMs, float toMs, const char *file) {
    MILO_ASSERT(toMs >= 0, 0x2C4);
    MILO_ASSERT(fromMs >= 0 || fromMs == kStreamEndMs, 0x2C5);
    mJumpFromMs = fromMs;
    mJumpToMs = toMs;
    mJumpFile = file;
    if (!mJumpFile.empty()) {
        mJumpFile += ".";
        mJumpFile += mExt.mStr;
    }
    if (GetSampleRate() == 0)
        mJumpSamplesInvalid = true;
    else
        setJumpSamplesFromMs(fromMs, toMs);
}

void StandardStream::setJumpSamplesFromMs(float f1, float f2) {
    mJumpFromSamples = kStreamEndSamples;
    mJumpToSamples = 0;
    if (f1 != kStreamEndMs) {
        mJumpFromSamples = MsToSamp(f1);
    }
    if (f2 != 0) {
        mJumpToSamples = MsToSamp(f2);
    }
    if (unk144 != -1) {
        if (mJumpFromSamples >= unk144) {
            String str = mFile ? mFile->Filename().c_str() : "SynthStream";
            MILO_WARN(
                "%s: JumpFromSamples (%g sec) exceeds the length of the stream (%g sec)!",
                str,
                f1 / 1000.0f,
                f2 / 1000.0f
            );
        }
        if (mJumpToSamples >= unk144) {
            String str = mFile ? mFile->Filename().c_str() : "SynthStream:";
            MILO_WARN(
                "%s: JumpToSamples (%g sec) exceeds the length of the stream (%g sec)!",
                str,
                f2 / 1000.0f,
                SampToMs(unk144) / 1000.0f
            );
        }
    }
}

void StandardStream::SetJumpSamples(int fromSamples, int toSamples, const char *file) {
    MILO_ASSERT(toSamples >= 0, 0x2F4);
    MILO_ASSERT(fromSamples >= 0 || fromSamples == kStreamEndSamples, 0x2F5);
    MILO_ASSERT(file || fromSamples > toSamples || fromSamples == kStreamEndSamples, 0x2F6);
    MILO_ASSERT(mJumpFromSamples == 0, 0x2F8);
    mJumpFromSamples = fromSamples;
    mJumpToSamples = toSamples;
    mJumpFile = file;
    if (!mJumpFile.empty()) {
        mJumpFile += ".";
        mJumpFile += mExt.mStr;
    }
    mJumpSamplesInvalid = false;
}

void StandardStream::ClearJump() {
    mJumpFromSamples = 0;
    mJumpFromMs = 0;
    mJumpToSamples = 0;
    mJumpToMs = 0;
}

void StandardStream::DoJump() {
    MILO_ASSERT(mJumpFromSamples != 0, 0x314);
    if (!mJumpFile.empty()) {
        delete mFile;
        delete mRdr;
        mFile = NewFile(mJumpFile.c_str(), 2);
        if (!mFile)
            MILO_FAIL("\nCould not open %s", mJumpFile.c_str());
        mRdr = TheSynth->NewStreamDecoder(mFile, this, mExt);
        mFileStartMs = SampToMs(mJumpToSamples);
        mCurrentSamp = 0;
        ClearJump();
    } else {
        if (mJumpFromSamples != mJumpToSamples) {
            if (mRdr)
                mRdr->Seek(mJumpToSamples);
            mCurrentSamp = mJumpToSamples;
        }
    }
    mAccumulatedLoopbacks -= mEndMarker.posMS - mStartMarker.posMS;
}

void StandardStream::EnableReads(bool b) {
    if (mRdr)
        mRdr->EnableReads(b);
}

void StandardStream::UpdateTime() { MILO_WARN("timer error is large: %f\n"); }

float StandardStream::GetJumpBackTotalTime() { return mAccumulatedLoopbacks; }

float StandardStream::GetInSongTime() { return GetTime() + GetJumpBackTotalTime(); }

int StandardStream::GetLoopInstances() { return 0; }

void StandardStream::SetVolume(int chan, float vol) {
    MILO_ASSERT_RANGE(chan, 0, mChanParams.size(), 0x3D0);
    mChanParams[chan]->mFaders.FindLocal(_default, true)->SetVal(vol);
}

void StandardStream::SetPan(int chan, float pan) {
    MILO_ASSERT_RANGE(chan, 0, mChanParams.size(), 0x3D8);
    mChanParams[chan]->mPan = pan;
    if (!mChannels.empty()) {
        mChannels[chan]->SetPan(pan);
    }
}

void StandardStream::SetSpeed(float speed) {
    mSpeed = speed;
    for (int i = 0; i < mChannels.size(); i++) {
        UpdateSpeed(i);
    }
    mTimer.SetSpeed(speed);
}

void StandardStream::SetADSR(int chan, const ADSR &adsr) {
    MILO_ASSERT_RANGE(chan, 0, mChanParams.size(), 0x3EC);
    mChanParams[chan]->mADSR = adsr;
    if (!mChannels.empty()) {
        mChannels[chan]->SetADSR(adsr);
    }
}

float StandardStream::GetVolume(int chan) const {
    MILO_ASSERT_RANGE(chan, 0, mChanParams.size(), 0x3F6);
    return mChanParams[chan]->mFaders.GetVal();
}

float StandardStream::GetPan(int chan) const {
    MILO_ASSERT_RANGE(chan, 0, mChanParams.size(), 0x3FE);
    return mChanParams[chan]->mPan;
}

float StandardStream::GetSpeed() const { return mSpeed; }

int StandardStream::MsToSamp(float ms) {
    MILO_ASSERT(mSampleRate, 0x40B);
    return mSampleRate * (ms / 1000.0f);
}

float StandardStream::SampToMs(int samps) {
    MILO_ASSERT(mSampleRate, 0x412);
    float rate = mSampleRate;
    return (float)samps / (rate * 1000.0f);
}

void StandardStream::UpdateVolumes() {
    if (Faders()->Dirty()) {
        float val = Faders()->GetVal();
        for (std::vector<ChannelParams *>::iterator it = mChanParams.begin();
             it != mChanParams.end();
             ++it) {
            (*it)->mFaders.FindLocal(_parent, true)->SetVal(val);
        }
        Faders()->ClearDirty();
    }
    for (int i = 0; i < mChannels.size(); i++) {
        if (mChanParams[i]->mFaders.Dirty()) {
            float ratio = DbToRatio(mChanParams[i]->mFaders.GetVal());
            ClampEq(ratio, 0.0f, 1.0f);
            mChannels[i]->SetVolume(ratio);
            mChanParams[i]->mFaders.ClearDirty();
        }
    }
}

void StandardStream::UpdateFXSends() {
    for (int i = 0; i < mChannels.size(); i++) {
        mChannels[i]->SetFXSend(mChanParams[i]->mFxSend);
    }
}

FaderGroup *StandardStream::ChannelFaders(int channel) {
    MILO_ASSERT_RANGE(channel, 0, mChanParams.size(), 0x43F);
    return &mChanParams[channel]->mFaders;
}

void StandardStream::AddVirtualChannels(int i) {
    MILO_ASSERT(mChannels.empty(), 0x447);
    mVirtualChans += i;
}

void StandardStream::RemapChannel(int i1, int i2) {
    mChanMaps.push_back(std::make_pair(i1, i2));
}

void StandardStream::UpdateSpeed(int chn) {
    MILO_ASSERT_RANGE(chn, 0, mChanParams.size(), 0x454);
    mChannels[chn]->SetSpeed(mSpeed);
    if (mChanParams[chn]->mSlipEnabled) {
        mChannels[chn]->SetSlipSpeed((float)mSpeed * mChanParams[chn]->mSlipSpeed);
    }
}

void StandardStream::EnableSlipStreaming(int channel) {
    if (mChannels.empty()) {
        MILO_ASSERT_RANGE(channel, 0, mChanParams.size(), 0x46C);
        mChanParams[channel]->mSlipEnabled = true;
    }
}

void StandardStream::SetSlipOffset(int channel, float offset) {
    MILO_ASSERT_RANGE(channel, 0, mChanParams.size(), 0x473);
    mChannels[channel]->SetSlipOffset(offset);
}

void StandardStream::SlipStop(int channel) {
    MILO_ASSERT_RANGE(channel, 0, mChanParams.size(), 0x47A);
    mChannels[channel]->SlipStop();
}

void StandardStream::SetSlipSpeed(int channel, float speed) {
    MILO_ASSERT_RANGE(channel, 0, mChanParams.size(), 0x481);
    MILO_ASSERT(mChanParams[channel]->mSlipEnabled, 0x482);
    mChanParams[channel]->mSlipSpeed = speed;
    if (!mChannels.empty()) {
        UpdateSpeed(channel);
    }
}

float StandardStream::GetSlipOffset(int channel) {
    MILO_ASSERT_RANGE(channel, 0, mChanParams.size(), 0x48B);
    return mChannels[channel]->GetSlipOffset();
}

void StandardStream::SetFXSend(int channel, FxSend *send) {
    MILO_ASSERT_RANGE(channel, 0, mChanParams.size(), 0x495);
    mChanParams[channel]->mFxSend = send;
    if (!mChannels.empty()) {
        mChannels[channel]->SetFXSend(send);
    }
}

void StandardStream::SetFX(int channel, bool fx) {
    MILO_ASSERT_RANGE(channel, 0, mChanParams.size(), 0x4A1);
    // TODO: replace printf with MILO_LOG/MILO_WARN/some MILO macro
    printf("mChanParams.size() == %d\n", mChanParams.size());
    int numChannels = mChannels.size();
    printf("mChannels.size() == %d\n", numChannels);
    if (numChannels > channel) {
        mChannels[channel]->SetFX(fx);
    }
}

bool StandardStream::GetFX(int channel) const {
    MILO_ASSERT_RANGE(channel, 0, mChanParams.size(), 0x4B6);
    return mChannels[channel]->GetFX();
}

void StandardStream::SetFXCore(int channel, FXCore core) {
    MILO_ASSERT_RANGE(channel, 0, mChanParams.size(), 0x4BD);
    mChanParams[channel]->mFXCore = core;
}

FXCore StandardStream::GetFXCore(int channel) const {
    MILO_ASSERT_RANGE(channel, 0, mChanParams.size(), 0x4C4);
    return mChanParams[channel]->mFXCore;
}

void StandardStream::SetPitchShift(int channel, bool shift) {
    if (channel < mChanParams.size() && channel < mChannels.size()) {
        mChanParams[channel]->mPitchShift = shift;
        mChannels[channel]->SetPitchShift(shift);
    }
}