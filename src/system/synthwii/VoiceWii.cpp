#include "VoiceWii.h"

static int active_voice_count;
static int gVoices;

Voice::Voice(const void *buffer, int bufBytes, bool bUseInPlace, bool bUseMEM2) {
    mEnvelope = EnvelopeWii();

    MILO_ASSERT(bufBytes > 0, 0x43);
    MILO_ASSERT(buffer, 0x44);

    mFormat = SampleData::kBigEndPCM;
    mState = 1;
    mBufferStart = (char*)buffer;
    mBufferBytes = bufBytes;

    mStartByte = -1;
    mLoopByte = -1;
    mSampleRate = 48000;
    mSpeed = 1.0f;

    // need to impl this
    // float decibels = RatioToDb();
    // mVolume = decibels * 10.0f;


    // TODO IMPL THE REST



}

bool Voice::IsPaused() {
    return mState == 3;
}

bool Voice::IsPlaying() {
    if (mVoice == 0) {
        return false;
    }
    if (mState == 3) {
        return true;
    }

    return mVoice->pb.state != 0;
}

int Voice::SampToByte(int samp, bool b) {
    if (b != 0) {
        samp++;
    }
    if ((mFormat) == 1) {
        return samp << 1;
    }
    if ((mFormat) == 6) {
        return samp / 2;
    }

    return 0;
}

void Voice::SetFX(bool enabled) {
    mFXActive = enabled;
    mMixDirty = true;
}

void Voice::SetFormat(SampleData::Format format) {
    mFormat = format;
}

void Voice::SetLoopSamp(int samp) {
    int byte = SampToByte(samp, false);
    mLoopByte = byte;
}

void Voice::SetStartSamp(int samp) {
    int byte = SampToByte(samp, false);
    mStartByte = byte;
}

void Voice::SetVolume(float volume) {
    SetVolume(volume, true);
}