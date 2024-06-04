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
    CREATE_COPY(FxSendReverb, c)
    if(c){
        COPY_MEM(c, mEnvironmentPreset)
        COPY_MEM(c, mPreDelayMs)
        COPY_MEM(c, mHighCut)
        COPY_MEM(c, mLowCut)
        COPY_MEM(c, mRoomSize)
        COPY_MEM(c, mDamping)
        COPY_MEM(c, mDiffusion)
        COPY_MEM(c, mEarlyLate)
    }
END_COPYS

BEGIN_HANDLERS(FxSendReverb)
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x5B)
END_HANDLERS


BEGIN_PROPSYNCS(FxSendReverb)
    SYNC_PROP_MODIFY(environment, mEnvironmentPreset, OnParametersChanged())
    SYNC_PROP_MODIFY(pre_delay_ms, mPreDelayMs, OnParametersChanged())
    SYNC_PROP_MODIFY(high_cut, mHighCut, OnParametersChanged())
    SYNC_PROP_MODIFY(low_cut, mLowCut, OnParametersChanged())
    SYNC_PROP_MODIFY(room_size, mRoomSize, OnParametersChanged())
    SYNC_PROP_MODIFY(damping, mDamping, OnParametersChanged())
    SYNC_PROP_MODIFY(diffusion, mDiffusion, OnParametersChanged())
    SYNC_PROP_MODIFY(early_late, mEarlyLate, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS
