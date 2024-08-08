#include "utl/VarTimer.h"

VarTimer::VarTimer() : mRawTimer(), mAccumMs(0.0f), mSpeed(1.0f) {
    
}

void VarTimer::Start(){
    if(!mRawTimer.Running())
        mRawTimer.Start();
}

void VarTimer::Stop() {
    if(mRawTimer.Running()) mRawTimer.Stop();
    mAccumMs += mRawTimer.Ms() * mSpeed;
    mRawTimer.Reset();
}

void VarTimer::Reset(float f) {
    bool b = mRawTimer.Running();
    mRawTimer.Reset();
    mAccumMs = f;
    if (b) mRawTimer.Start();
}

void VarTimer::SetSpeed(float f) {
    bool b = mRawTimer.Running();
    if (b) Stop();
    mSpeed = f;
    if (b) Start();
}

float VarTimer::Ms() {
    return mRawTimer.SplitMs();
}
