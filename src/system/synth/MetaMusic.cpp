#include "synth/MetaMusic.h"

void MetaMusicLoader::DoneLoading() {}

MetaMusic::MetaMusic(const char *cc)
    : mStream(0), mLoop(0), mFadeTime(1.0f), mVolume(0), mPlayFromBuffer(1), mRndHeap(0),
      mBufferH(0), mBuf(0), mFile(0), mBufSize(0), mBytesRead(0),
      mExtraFaders(this, kObjListNoNull), mLoader(0), unk78(0), unk88(cc), unk8c(1) {
    mFader = Hmx::Object::New<Fader>();
    mFaderMute = Hmx::Object::New<Fader>();
}

MetaMusic::~MetaMusic() {
    delete mStream;
    mStream = 0;
    UnloadStreamFx();
    delete mFile;
    mFile = 0;
    delete mLoader;
    mLoader = 0;
    if (mRndHeap) {
        if (mBufferH) {
            mBufferH->Unlock();
            MemFreeH(mBufferH);
            mBufferH = 0;
        }
        mBuf = 0;
    } else if (mBuf) {
        _MemFree(mBuf);
        mBuf = 0;
    }
    delete mFader;
    delete mFaderMute;
}

int MetaMusic::ChooseStartMs() const {
    int startMs = 0;

    if (mStartTimes.size() != 0) {
        // pick a random element
        int randomInt = RandomInt(0, mStartTimes.size());
        startMs = mStartTimes[randomInt];
    }

    return startMs;
}

bool MetaMusic::IsFading() const {
    return mFader->IsFading();
}

bool MetaMusic::Loaded() {
    bool isLoaded = 0;
    if (mPlayFromBuffer == 0 || (mBuf != 0 && mFile == 0)) {
        isLoaded = 1;
    }
    return isLoaded;
}

void MetaMusic::Mute() {
    mFaderMute->DoFade(-96.0f, 1000.0);
}

void MetaMusic::UnMute() {
    mFaderMute->DoFade(0.0f, 1000.0);
}
