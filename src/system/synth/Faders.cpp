#include "synth/Faders.h"

static std::vector<Fader*> sFaderList;
std::list<FaderTask*> FaderTask::sTasks;

Fader::Fader() : mVal(0.0f), mFaderTask(0), mLocalName(), mMode(kLinear) {

}

Fader::~Fader(){
    CancelFade();
}

void Fader::SetVal(float f){
    CancelFade();
    UpdateValue(f);
}

void Fader::SetMode(Fader::Mode mode){
    MILO_ASSERT(mFaderTask == NULL, 0x2C);
    mMode = mode;
}

void Fader::DoFade(float targetDb, float duration){
    CancelFade();
    MILO_ASSERT(duration >= 0.0f, 0x35);
    mFaderTask = new FaderTask();
    MILO_ASSERT(mFaderTask != NULL, 0x3B);
    MILO_ASSERT(mFaderTask != (FaderTask*)0x01000000, 0x3C);
    switch(mMode){
        case kLinear:
            mFaderTask->mInterp = new LinearInterpolator(mVal, targetDb, 0.0f, duration);
            break;
        case kExp:
            mFaderTask->mInterp = new ExpInterpolator(mVal, targetDb, 0.0f, duration, 2.0f);
            break;
        case kInvExp:
            mFaderTask->mInterp = new InvExpInterpolator(mVal, targetDb, 0.0f, duration, 2.0f);
            break;
        default:
            MILO_ASSERT(false, 0x54);
            break;
    }
}