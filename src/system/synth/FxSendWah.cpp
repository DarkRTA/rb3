#include "synth/FxSendWah.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"
#include "os/Debug.h"

unsigned short FxSendWah::gRev = 0;
unsigned short FxSendWah::gAltRev = 0;

FxSendWah::FxSendWah() : mResonance(7.0f), mUpperFreq(5000.0f), mLowerFreq(1000.0f), mLfoFreq(1.35f),
    mMagic(0.3f), mDistAmount(0.5f), mAutoWah(0), mFrequency(0.5f), mTempoSync(0), mSyncType("quarter"), mTempo(120.0f), mBeatFrac(0.0f) {

}

SAVE_OBJ(FxSendWah, 0x20);

void FxSendWah::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0);
    FxSend::Load(bs);
    bs >> mResonance >> mLowerFreq >> mUpperFreq >> mLfoFreq >> mMagic;
    if(gRev >= 2){
        bs >> mTempoSync >> mTempo >> mSyncType;
    }
    if(gRev >= 3){
        bs >> mDistAmount >> mAutoWah >> mFrequency;
    }
    OnParametersChanged();
}

BEGIN_COPYS(FxSendWah)
    COPY_SUPERCLASS(FxSend)
    GET_COPY(FxSendWah)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mResonance)
        COPY_MEMBER(mLowerFreq)
        COPY_MEMBER(mUpperFreq)
        COPY_MEMBER(mLfoFreq)
        COPY_MEMBER(mMagic)
        COPY_MEMBER(mTempoSync)
        COPY_MEMBER(mTempo)
        COPY_MEMBER(mSyncType)
        COPY_MEMBER(mDistAmount)
        COPY_MEMBER(mAutoWah)
        COPY_MEMBER(mFrequency)
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(FxSendWah)
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x69)
END_HANDLERS

BEGIN_PROPSYNCS(FxSendWah)
    SYNC_PROP_ACTION(resonance, mResonance, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(upper_freq, mUpperFreq, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(lower_freq, mLowerFreq, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(lfo_freq, mLfoFreq, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(magic, mMagic, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(tempo_sync, mTempoSync, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(sync_type, mSyncType, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(tempo, mTempo, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(beat_frac, mBeatFrac, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(dist_amount, mDistAmount, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(auto_wah, mAutoWah, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(frequency, mFrequency, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(dump, mDump, kPropSize|kPropGet, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS
