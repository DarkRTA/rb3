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
    GET_COPY(FxSendEQ)
    BEGIN_COPY_CHECKED
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
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(FxSendEQ)
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x61)
END_HANDLERS

BEGIN_PROPSYNCS(FxSendEQ)
    SYNC_PROP_ACTION(high_frequency, mHighFreqCutoff, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(high_gain, mHighFreqGain, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(mid_frequency, mMidFreqCutoff, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(mid_bandwidth, mMidFreqBandwidth, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(mid_gain, mMidFreqGain, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(low_frequency, mLowFreqCutoff, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(low_gain, mLowFreqGain, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(low_pass_cutoff, mLowPassCutoff, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(low_pass_reso, mLowPassReso, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(high_pass_cutoff, mHighPassCutoff, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(high_pass_reso, mHighPassReso, kPropSize|kPropGet, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS
