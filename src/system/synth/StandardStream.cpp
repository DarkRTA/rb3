#include "synth/StandardStream.h"
#include "synth/Synth.h"
#include "utl/Symbols.h"

StandardStream::ChannelParams::ChannelParams() : mPan(0.0f), mSlipSpeed(1.0f), mSlipEnabled(0), mADSR(), mFaders(0), mFxSend(0, 0), mFXCore(kFXCoreNone), mPitchShift(0) {
    mFaders.AddLocal(_parent)->SetVal(0.0f);
    mFaders.AddLocal(_default)->SetVal(0.0f);
}

StandardStream::StandardStream(File* f, float f1, float f2, Symbol sym, bool b1, bool b2) : mPollingEnabled(b2) {
    MILO_ASSERT(f, 0x46);
    mExt = sym;
    mFile = f;
    mInfoChannels = -1;
    unkec = -1.0f;
    Init(f1, f2, sym, false);
}

void StandardStream::Init(float f1, float f2, Symbol sym, bool b){
    ClearLoopMarkers();
    mAccumulatedLoopbacks = 0.0f;
    mGetInfoOnly = false;
    mState = kInit;
    mSampleRate = 0;
    mBufSecs = f2;
    if(mBufSecs == 0.0f){
        SystemConfig("synth")->FindData("stream_buf_size", mBufSecs, true);
    }
    mFileStartMs = f1;
    mStartMs = f1;
    mLastStreamTime = f1;
    mTimer.Reset(f1);
    mFloatSamples = false;
    if(!b){
        MILO_ASSERT(mChanParams.empty(), 0x6B);
        mChanParams.resize(0x20);
        for(int i = 0; i < 0x20; i++){
            mChanParams[i] = new ChannelParams();
        }
        mVirtualChans = 0;
        mSpeed = 1.0f;
    }
    else {
        while(mChanParams.size() < 0x20){
            mChanParams.push_back((new ChannelParams()));
        }
    }
    mJumpFromSamples = 0;
    mJumpToSamples = 0;
    mJumpFromMs = 0.0f;
    mJumpToMs = 0.0f;
    mCurrentSamp = 0;
    mThrottle = SystemConfig("synth", "oggvorbis")->FindFloat("throttle");
    if(mPollingEnabled) StartPolling();
    mRdr = TheSynth->NewStreamDecoder(mFile, this, sym);
}

void StandardStream::Destroy(){
    delete mRdr;
    mRdr = 0;
}

StandardStream::~StandardStream(){
    Destroy();
}