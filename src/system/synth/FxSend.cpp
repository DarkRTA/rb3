#include "synth/FxSend.h"

FxSend::FxSend() : mNextSend(this, 0), mDryGain(-96.0f), mWetGain(0.0f), 
    mInputGain(0.0f), mReverbMixDb(-96.0f), mEnableUpdates(0), unk41(1), mChannels(kSendAll) {
}

FxSend::~FxSend(){
    
}

void FxSend::Save(BinStream&){
    MILO_ASSERT(0, 0xA2);
}
