#include "synth/FxSendDelay.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

unsigned short FxSendDelay::gRev = 0;
unsigned short FxSendDelay::gAltRev = 0;

FxSendDelay::FxSendDelay() : mDelayTime(0.2f), mGain(-6.0f), mPingPongPct(0.0f), mTempoSync(0), mSyncType(), mTempo(120.0f) {
    mSyncType = eighth;
}

FxSendDelay::~FxSendDelay(){

}

SAVE_OBJ(FxSendDelay, 0x1E);

void FxSendDelay::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0);
    FxSend::Load(bs);
    bs >> mDelayTime >> mGain;
    if(gRev >= 2){
        bs >> mTempoSync >> mSyncType;
        bs >> mTempo;
    }
    if(gRev >= 3){
        bs >> mPingPongPct;
    }
    OnParametersChanged();
}

BEGIN_COPYS(FxSendDelay)
    COPY_SUPERCLASS(FxSend)
    CREATE_COPY(FxSendDelay)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mDelayTime)
        COPY_MEMBER(mGain)
        COPY_MEMBER(mTempoSync)
        COPY_MEMBER(mSyncType)
        COPY_MEMBER(mTempo)
        COPY_MEMBER(mPingPongPct)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(FxSendDelay)
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x50)
END_HANDLERS

BEGIN_PROPSYNCS(FxSendDelay)
    SYNC_PROP_MODIFY(delay_time, mDelayTime, OnParametersChanged())
    SYNC_PROP_MODIFY(feedback, mGain, OnParametersChanged())
    SYNC_PROP_MODIFY(tempo_sync, mTempoSync, OnParametersChanged())
    SYNC_PROP_MODIFY(sync_type, mSyncType, OnParametersChanged())
    SYNC_PROP_MODIFY(tempo, mTempo, OnParametersChanged())
    SYNC_PROP_MODIFY(ping_pong_pct, mPingPongPct, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS
