#include "synth/FxSendEQ.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

unsigned short FxSendEQ::gRev = 0;
unsigned short FxSendEQ::gAltRev = 0;

FxSendEQ::FxSendEQ() : mHighFreqCutoff(12000.0f), mHighFreqGain(0.0f), 
    mMidFreqCutoff(8000.0f), mMidFreqBandwidth(1000.0f), mMidFreqGain(0.0f), mLowFreqCutoff(2000.0f), mLowFreqGain(0.0f), 
    mLowPassCutoff(20000.0f), mLowPassReso(0.0f), mHighPassCutoff(20.0f), mHighPassReso(0.0f) {

}

FxSendEQ::~FxSendEQ(){

}

SAVE_OBJ(FxSendEQ, 0x22);

void FxSendEQ::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    FxSend::Load(bs);
    bs >> mHighFreqCutoff >> mHighFreqGain >> mMidFreqCutoff >> mMidFreqBandwidth >> mMidFreqGain >> mLowFreqCutoff >> mLowFreqGain;
    if(gRev >= 2){
        bs >> mLowPassCutoff >> mLowPassReso >> mHighPassCutoff >> mHighPassReso;
    }
    OnParametersChanged();
}

BEGIN_COPYS(FxSendEQ)
    COPY_SUPERCLASS(FxSend)
    CREATE_COPY(FxSendEQ)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mHighFreqCutoff)
        COPY_MEMBER(mHighFreqGain)
        COPY_MEMBER(mMidFreqCutoff)
        COPY_MEMBER(mMidFreqBandwidth)
        COPY_MEMBER(mMidFreqGain)
        COPY_MEMBER(mLowFreqCutoff)
        COPY_MEMBER(mLowFreqGain)
        COPY_MEMBER(mLowPassCutoff)
        COPY_MEMBER(mLowPassReso)
        COPY_MEMBER(mHighPassCutoff)
        COPY_MEMBER(mHighPassReso)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(FxSendEQ)
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x61)
END_HANDLERS

BEGIN_PROPSYNCS(FxSendEQ)
    SYNC_PROP_MODIFY(high_frequency, mHighFreqCutoff, OnParametersChanged())
    SYNC_PROP_MODIFY(high_gain, mHighFreqGain, OnParametersChanged())
    SYNC_PROP_MODIFY(mid_frequency, mMidFreqCutoff, OnParametersChanged())
    SYNC_PROP_MODIFY(mid_bandwidth, mMidFreqBandwidth, OnParametersChanged())
    SYNC_PROP_MODIFY(mid_gain, mMidFreqGain, OnParametersChanged())
    SYNC_PROP_MODIFY(low_frequency, mLowFreqCutoff, OnParametersChanged())
    SYNC_PROP_MODIFY(low_gain, mLowFreqGain, OnParametersChanged())
    SYNC_PROP_MODIFY(low_pass_cutoff, mLowPassCutoff, OnParametersChanged())
    SYNC_PROP_MODIFY(low_pass_reso, mLowPassReso, OnParametersChanged())
    SYNC_PROP_MODIFY(high_pass_cutoff, mHighPassCutoff, OnParametersChanged())
    SYNC_PROP_MODIFY(high_pass_reso, mHighPassReso, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS
