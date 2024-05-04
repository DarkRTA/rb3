#include "synth/StandardStream.h"
#include "synth/Synth.h"

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
    if(b){
        while(mChanParams.size() < 0x20){
            mChanParams.push_back(*(new ChannelParams()));
        }
    }
    else {
        MILO_ASSERT(mChanParams.empty(), 0x6B);
        mChanParams.resize(0x20);
        while(mChanParams.size() < 0x20){
            mChanParams.push_back(*(new ChannelParams()));
        }
    }
    mJumpFromSamples = 0;
    mJumpToSamples = 0;
    mJumpFromMs = 0.0f;
    mJumpToMs = 0.0f;
    mCurrentSamp = 0;
    mThrottle = SystemConfig("synth", "oggvorbis")->FindArray("throttle", true)->Float(1);
    if(mPollingEnabled) StartPolling();
    mRdr = TheSynth->NewStreamDecoder(mFile, this, sym);
}