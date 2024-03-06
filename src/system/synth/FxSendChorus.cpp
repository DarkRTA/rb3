#include "synth/FxSendChorus.h"
#include "utl/Symbols.h"

unsigned short FxSendChorus::gRev = 0;
unsigned short FxSendChorus::gAltRev = 0;

FxSendChorus::FxSendChorus() : mDelayMs(50.0f), mRate(1.0f), mDepth(10.0f), mFeedbackPct(30), mOffsetPct(20), mTempoSync(0), mSyncType(), mTempo(120.0f) {
    mSyncType = quarter;
    mDryGain = -3.0f;
    mWetGain = -3.0f;
}

void FxSendChorus::Save(BinStream&){
    MILO_ASSERT(0, 0x1F);
}

void FxSendChorus::Load(BinStream& bs){
    unsigned int rev;
    unsigned short huh;
    bs >> rev;
    huh = rev & 0xFFFF;
    gRev = huh;
    gAltRev = rev >> 0x10;
    if(huh > 3){
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), gRev, (unsigned short)3);
    }
    if(gAltRev != 0){
        MILO_FAIL("%s can't load new %s alt version %d > %d", PathName(this), ClassName(), gAltRev, (unsigned short)0);
    }
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
