#include "synth/FxSend.h"

FxSend::FxSend() : mNextSend(this, 0), mStage(0), mBypass(0), mDryGain(-96.0f), mWetGain(0.0f), 
    mInputGain(0.0f), mReverbMixDb(-96.0f), mEnableUpdates(0), unk41(1), mChannels(kSendAll) {
}

FxSend::~FxSend(){
    
}

void FxSend::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    MILO_ASSERT(from == mNextSend, 0x30);
    mNextSend = ObjOwnerPtr<FxSend, ObjectDir>(to, 0);
    RebuildChain();
}

void FxSend::Save(BinStream&){
    MILO_ASSERT(0, 0xA2);
}

BEGIN_COPYS(FxSend)
    COPY_SUPERCLASS(Hmx::Object)
    GET_COPY(FxSend)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mNextSend)
        COPY_MEMBER(mStage)
        COPY_MEMBER(mWetGain)
        COPY_MEMBER(mDryGain)
        COPY_MEMBER(mInputGain)
        COPY_MEMBER(mChannels)
        COPY_MEMBER(mBypass)
        COPY_MEMBER(mReverbMixDb)
        COPY_MEMBER(mEnableUpdates)
    END_COPY_CHECKED
END_COPYS
