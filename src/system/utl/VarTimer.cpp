#include "utl/VarTimer.h"

VarTimer::VarTimer() : mRawTimer(), mAccumMs(0.0f), mSpeed(1.0f) {
    
}

void VarTimer::Start(){
    if(!mRawTimer.Running())
        mRawTimer.Start();
}
