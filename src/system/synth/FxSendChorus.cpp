#include "synth/FxSendChorus.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

unsigned short FxSendChorus::gRev = 0;
unsigned short FxSendChorus::gAltRev = 0;

FxSendChorus::FxSendChorus() : mDelayMs(50.0f), mRate(1.0f), mDepth(10.0f), mFeedbackPct(30), mOffsetPct(20), mTempoSync(0), mSyncType(), mTempo(120.0f) {
    mSyncType = quarter;
    mDryGain = -3.0f;
    mWetGain = -3.0f;
}

SAVE_OBJ(FxSendChorus, 0x1F);

void FxSendChorus::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0);
    FxSend::Load(bs);
    if(gRev == 1){
        mDryGain = -3.0f;
        mWetGain = -3.0f;
        UpdateMix();
    }
    bs >> mDelayMs >> mRate >> mDepth >> mFeedbackPct >> mOffsetPct;
    if(gRev >= 3){
        bs >> mTempoSync >> mSyncType;
        bs >> mTempo;
    }
    OnParametersChanged();
}

BEGIN_COPYS(FxSendChorus)
    COPY_SUPERCLASS(FxSend)
    GET_COPY(FxSendChorus)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mDelayMs)
        COPY_MEMBER(mRate)
        COPY_MEMBER(mDepth)
        COPY_MEMBER(mFeedbackPct)
        COPY_MEMBER(mOffsetPct)
        COPY_MEMBER(mTempoSync)
        COPY_MEMBER(mSyncType)
        COPY_MEMBER(mTempo)
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(FxSendChorus)
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x5C)
END_HANDLERS

BEGIN_PROPSYNCS(FxSendChorus)
    SYNC_PROP_MODIFY(delay_ms, mDelayMs, OnParametersChanged())
    SYNC_PROP_MODIFY(rate, mRate, OnParametersChanged())
    SYNC_PROP_MODIFY(depth, mDepth, OnParametersChanged())
    SYNC_PROP_MODIFY(feedback_pct, mFeedbackPct, OnParametersChanged())
    SYNC_PROP_MODIFY(offset_pct, mOffsetPct, OnParametersChanged())
    SYNC_PROP_MODIFY(tempo_sync, mTempoSync, OnParametersChanged())
    SYNC_PROP_MODIFY(sync_type, mSyncType, OnParametersChanged())
    SYNC_PROP_MODIFY(tempo, mTempo, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS
