#include "synth/FxSendCompress.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

unsigned short FxSendCompress::gRev = 0;
unsigned short FxSendCompress::gAltRev = 0;

FxSendCompress::FxSendCompress() : mThresholdDB(-12.0f), mRatio(3.0f), mOutputLevel(0.0f), mAttack(0.005f), mRelease(0.12f), mExpRatio(1.0f), mExpAttack(0.12f), mExpRelease(0.005f) {

}

FxSendCompress::~FxSendCompress(){

}

// float mThresholdDB;
//     float mRatio;
//     float mOutputLevel;
//     float mAttack;
//     float mRelease;
//     float mExpRatio;
//     float mExpAttack;
//     float mExpRelease;
//     float mGateThresholdDB;

SAVE_OBJ(FxSendCompress, 0x1F);

void FxSendCompress::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(4, 0);
    FxSend::Load(bs);
    bs >> mThresholdDB >> mRatio >> mOutputLevel;
    if(gRev < 2) mOutputLevel = 0.0f;
    bs >> mAttack >> mRelease;
    int dummy;
    if(gRev < 2) bs >> dummy;
    if(gRev >= 3){
        bs >> mExpRatio >> mExpAttack >> mExpRelease;
    }
    if(gRev >= 4) bs >> mGateThresholdDB;
    OnParametersChanged();
}

BEGIN_COPYS(FxSendCompress)
    COPY_SUPERCLASS(FxSend)
    GET_COPY(FxSendCompress)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mThresholdDB)
        COPY_MEMBER(mRatio)
        COPY_MEMBER(mOutputLevel)
        COPY_MEMBER(mAttack)
        COPY_MEMBER(mRelease)
        COPY_MEMBER(mExpRatio)
        COPY_MEMBER(mExpAttack)
        COPY_MEMBER(mExpRelease)
        COPY_MEMBER(mGateThresholdDB)
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(FxSendCompress)
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x66)
END_HANDLERS

BEGIN_PROPSYNCS(FxSendCompress)
    SYNC_PROP_ACTION(threshold, mThresholdDB, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(comp_ratio, mRatio, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(output_level, mOutputLevel, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(attack, mAttack, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(release, mRelease, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(exp_ratio, mExpRatio, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(exp_attack, mExpAttack, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(exp_release, mExpRelease, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(gate_threshold, mGateThresholdDB, kPropSize|kPropGet, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS
