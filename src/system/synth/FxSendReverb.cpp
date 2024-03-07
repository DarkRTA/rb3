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
    unsigned int rev;
    bs >> rev;
    gRev = getHmxRev(rev);
    gAltRev = getAltRev(rev);
    if(gRev > 2){
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), gRev, (unsigned short)2);
    }
    if(gAltRev != 0){
        MILO_FAIL("%s can't load new %s alt version %d > %d", PathName(this), ClassName(), gAltRev, (unsigned short)0);
    }
    FxSend::Load(bs);
    bs >> mEnvironmentPreset;
    if(gRev >= 2){
        bs >> mPreDelayMs >> mHighCut >> mLowCut >> mRoomSize >> mDamping >> mDiffusion >> mEarlyLate;
    }
    OnParametersChanged();
}

void FxSendReverb::Copy(const Hmx::Object* o, Hmx::Object::CopyType ty){
    FxSend::Copy(o, ty);
    const FxSendReverb* c = dynamic_cast<const FxSendReverb*>(o);
    if(c){
        mEnvironmentPreset = c->mEnvironmentPreset;
        mPreDelayMs = c->mPreDelayMs;
        mHighCut = c->mHighCut;
        mLowCut = c->mLowCut;
        mRoomSize = c->mRoomSize;
        mDamping = c->mDamping;
        mDiffusion = c->mDiffusion;
        mEarlyLate = c->mEarlyLate;
    }
}

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
