#include "synth/FxSendFlanger.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

unsigned short FxSendFlanger::gRev = 0;
unsigned short FxSendFlanger::gAltRev = 0;

FxSendFlanger::FxSendFlanger() : mDelayMs(2.0f), mRate(0.5f), mDepthPct(50), mFeedbackPct(50), mOffsetPct(10), mTempoSync(0), mSyncType(), mTempo(120.0f) {
    mSyncType = quarter;
    mDryGain = -3.0f;
    mWetGain = -3.0f;
}

SAVE_OBJ(FxSendFlanger, 0x1F);

void FxSendFlanger::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(6, 0);
    FxSend::Load(bs);
    if(gRev <= 4){
        mDryGain = -3.0f;
        mWetGain = -3.0f;
        UpdateMix();
    }
    bs >> mDelayMs >> mRate;
    int dummy;

    if(gRev >= 4) bs >> mDepthPct;
    else bs >> dummy;
    if(gRev >= 2) bs >> mFeedbackPct;
    if(gRev >= 3) bs >> mOffsetPct;

    if(gRev >= 6){
        bs >> mTempoSync >> mSyncType;
        bs >> mTempo;
    }
    OnParametersChanged();
}

BEGIN_COPYS(FxSendFlanger)
    COPY_SUPERCLASS(FxSend)
    GET_COPY(FxSendFlanger)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mDelayMs)
        COPY_MEMBER(mRate)
        COPY_MEMBER(mDepthPct)
        COPY_MEMBER(mFeedbackPct)
        COPY_MEMBER(mOffsetPct)
        COPY_MEMBER(mTempoSync)
        COPY_MEMBER(mSyncType)
        COPY_MEMBER(mTempo)
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(FxSendFlanger)
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x67)
END_HANDLERS


BEGIN_PROPSYNCS(FxSendFlanger)
    SYNC_PROP_ACTION(delay_ms, mDelayMs, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(rate, mRate, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(depth_pct, mDepthPct, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(feedback_pct, mFeedbackPct, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(offset_pct, mOffsetPct, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(tempo_sync, mTempoSync, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(sync_type, mSyncType, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(tempo, mTempo, kPropSize|kPropGet, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS
