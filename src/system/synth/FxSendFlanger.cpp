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
    unsigned int rev;
    unsigned short huh;
    bs >> rev;
    huh = rev & 0xFFFF;
    gRev = huh;
    gAltRev = rev >> 0x10;
    if(huh > 6){
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), gRev, (unsigned short)6);
    }
    if(gAltRev != 0){
        MILO_FAIL("%s can't load new %s alt version %d > %d", PathName(this), ClassName(), gAltRev, (unsigned short)0);
    }
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

void FxSendFlanger::Copy(const Hmx::Object* o, Hmx::Object::CopyType ty){
    FxSend::Copy(o, ty);
    const FxSendFlanger* c = dynamic_cast<const FxSendFlanger*>(o);
    if(c){
        mDelayMs = c->mDelayMs;
        mRate = c->mRate;
        mDepthPct = c->mDepthPct;
        mFeedbackPct = c->mFeedbackPct;
        mOffsetPct = c->mOffsetPct;
        mTempoSync = c->mTempoSync;
        mSyncType = c->mSyncType;
        mTempo = c->mTempo;
    }
}

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

static void UnusedClassThatOnlyExistsToMoveSetTypeUp(FxSendFlanger* flang){
    flang->SetType(Symbol());
}
