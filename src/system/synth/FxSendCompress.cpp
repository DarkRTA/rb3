#include "synth/FxSendCompress.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

unsigned short FxSendCompress::gRev = 0;
unsigned short FxSendCompress::gAltRev = 0;

FxSendCompress::FxSendCompress() : mThresholdDB(-12.0f), mRatio(3.0f), mOutputLevel(0.0f), mAttack(0.005f), mRelease(0.12f), mExpRatio(1.0f), mExpAttack(0.12f), mExpRelease(0.005f) {

}

FxSendCompress::~FxSendCompress(){

}

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
    CREATE_COPY(FxSendCompress)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mThresholdDB)
        COPY_MEMBER(mRatio)
        COPY_MEMBER(mOutputLevel)
        COPY_MEMBER(mAttack)
        COPY_MEMBER(mRelease)
        COPY_MEMBER(mExpRatio)
        COPY_MEMBER(mExpAttack)
        COPY_MEMBER(mExpRelease)
        COPY_MEMBER(mGateThresholdDB)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(FxSendCompress)
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x66)
END_HANDLERS

BEGIN_PROPSYNCS(FxSendCompress)
    SYNC_PROP_MODIFY(threshold, mThresholdDB, OnParametersChanged())
    SYNC_PROP_MODIFY(comp_ratio, mRatio, OnParametersChanged())
    SYNC_PROP_MODIFY(output_level, mOutputLevel, OnParametersChanged())
    SYNC_PROP_MODIFY(attack, mAttack, OnParametersChanged())
    SYNC_PROP_MODIFY(release, mRelease, OnParametersChanged())
    SYNC_PROP_MODIFY(exp_ratio, mExpRatio, OnParametersChanged())
    SYNC_PROP_MODIFY(exp_attack, mExpAttack, OnParametersChanged())
    SYNC_PROP_MODIFY(exp_release, mExpRelease, OnParametersChanged())
    SYNC_PROP_MODIFY(gate_threshold, mGateThresholdDB, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS
