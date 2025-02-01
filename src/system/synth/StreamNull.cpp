#include "synth/StreamNull.h"

StreamNull::StreamNull(float f) : mFaders(nullptr) {
    mTimer.Reset(f);
    mChannelFaders.resize(20);
    for (std::vector<FaderGroup *>::iterator it = mChannelFaders.begin();
         it != mChannelFaders.end();
         ++it) {
        *it = new FaderGroup(nullptr);
    }
}

StreamNull::~StreamNull() { DeleteAll(mChannelFaders); }

void StreamNull::Play() { mTimer.Start(); }

void StreamNull::Stop() { mTimer.Stop(); }

bool StreamNull::IsPlaying() const { return mTimer.mRawTimer.Running(); }

bool StreamNull::IsFinished() const { return !mTimer.mRawTimer.Running(); }

void StreamNull::Resync(float f) {
    mTimer.Stop();
    mTimer.Reset(f);
}

float StreamNull::GetTime() { return mTimer.Ms(); }

float StreamNull::GetJumpBackTotalTime() { return 0; }
float StreamNull::GetInSongTime() { return 0; }
int StreamNull::GetLoopInstances() { return 0; }
void StreamNull::SetSpeed(float speed) { mTimer.SetSpeed(speed); }
float StreamNull::GetSpeed() const { return mTimer.GetSpeed(); }

FaderGroup *StreamNull::ChannelFaders(int idx) { return mChannelFaders[idx]; }