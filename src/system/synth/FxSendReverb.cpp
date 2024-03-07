#include "synth/FxSendReverb.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

unsigned short FxSendReverb::gRev = 0;
unsigned short FxSendReverb::gAltRev = 0;

FxSendReverb::FxSendReverb() : mEnvironmentPreset(), mPreDelayMs(50.0f), mHighCut(5000.0f), mLowCut(100.0f), mRoomSize(0.5f), mDamping(0.5f), mDiffusion(0.5f), mEarlyLate(0.5f) {
    mEnvironmentPreset = generic;
    mDryGain = 0.0f;
    mWetGain = -6.0f;
}

FxSendReverb::~FxSendReverb(){

}

SAVE_OBJ(FxSendReverb, 0x23);

void FxSendReverb::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    FxSend::Load(bs);
    bs >> mEnvironmentPreset;
    if(gRev >= 2){
        bs >> mPreDelayMs >> mHighCut >> mLowCut >> mRoomSize >> mDamping >> mDiffusion >> mEarlyLate;
    }
    OnParametersChanged();
}

BEGIN_COPYS(FxSendReverb)
    COPY_SUPERCLASS(FxSend)
    GET_COPY(FxSendReverb)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mEnvironmentPreset)
        COPY_MEMBER(mPreDelayMs)
        COPY_MEMBER(mHighCut)
        COPY_MEMBER(mLowCut)
        COPY_MEMBER(mRoomSize)
        COPY_MEMBER(mDamping)
        COPY_MEMBER(mDiffusion)
        COPY_MEMBER(mEarlyLate)
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(FxSendReverb)
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x5B)
END_HANDLERS


BEGIN_PROPSYNCS(FxSendReverb)
    SYNC_PROP_ACTION(environment, mEnvironmentPreset, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(pre_delay_ms, mPreDelayMs, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(high_cut, mHighCut, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(low_cut, mLowCut, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(room_size, mRoomSize, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(damping, mDamping, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(diffusion, mDiffusion, kPropSize|kPropGet, OnParametersChanged())
    SYNC_PROP_ACTION(early_late, mEarlyLate, kPropSize|kPropGet, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS
