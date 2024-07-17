#include "synth/MetaMusic.h"

MetaMusic::MetaMusic(const char* cc) : mStream(0), mLoop(0), mFadeTime(1.0f), mVolume(0), mPlayFromBuffer(1), mRndHeap(0), mBufferH(0),
    mBuf(0), mFile(0), mBufSize(0), mBytesRead(0), mExtraFaders(this, kObjListNoNull), mLoader(0), unk78(0), unk88(cc), unk8c(1) {
    mFader = Hmx::Object::New<Fader>();
    mFaderMute = Hmx::Object::New<Fader>();
}

MetaMusic::~MetaMusic(){
    delete mStream;
    mStream = 0;
    UnloadStreamFx();
    delete mFile;
    mFile = 0;
    delete mLoader;
    mLoader = 0;
    if(mRndHeap){
        if(mBufferH){
            mBufferH->Unlock();
            MemFreeH(mBufferH);
            mBufferH = 0;
        }
        mBuf = 0;
    }
    else if(mBuf){
        _MemFree(mBuf);
        mBuf = 0;
    }
    delete mFader;
    delete mFaderMute;
}