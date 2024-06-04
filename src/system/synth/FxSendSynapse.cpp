#include "synth/FxSendSynapse.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"
#include "os/Debug.h"

unsigned short FxSendSynapse::gRev = 0;
unsigned short FxSendSynapse::gAltRev = 0;

FxSendSynapse::FxSendSynapse() : mAmount(0.0f), mProximityEffect(0.5f), mProximityFocus(0.5f), mNote1Hz(200.0f), mNote2Hz(0.0f), mNote3Hz(0.0f), mUnisonTrio(0), mAttackSmoothing(30.0f), mReleaseSmoothing(60.0f) {

}

void FxSendSynapse::SetAttackSmoothing(float as){
    mAttackSmoothing = as;
    OnParametersChanged();
}

void FxSendSynapse::SetReleaseSmoothing(float rs){
    mReleaseSmoothing = rs;
    OnParametersChanged();
}

void FxSendSynapse::SetAmount(float amt){
    mAmount = amt;
    OnParametersChanged();
}

void FxSendSynapse::SetProximityEffect(float pe){
    mProximityEffect = pe;
    OnParametersChanged();
}

void FxSendSynapse::SetProximityFocus(float pf){
    mProximityFocus = pf;
    OnParametersChanged();
}

BEGIN_HANDLERS(FxSendSynapse)
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x52)
END_HANDLERS

BEGIN_PROPSYNCS(FxSendSynapse)
    SYNC_PROP_MODIFY(amount, mAmount, OnParametersChanged())
    SYNC_PROP_MODIFY(proximity_effect, mProximityEffect, OnParametersChanged())
    SYNC_PROP_MODIFY(proximity_focus, mProximityFocus, OnParametersChanged())
    SYNC_PROP_MODIFY(note1_hz, mNote1Hz, OnParametersChanged())
    SYNC_PROP_MODIFY(note2_hz, mNote2Hz, OnParametersChanged())
    SYNC_PROP_MODIFY(note3_hz, mNote3Hz, OnParametersChanged())
    SYNC_PROP_MODIFY(unison_trio, mUnisonTrio, OnParametersChanged())
    SYNC_PROP_MODIFY(attack_smoothing, mAttackSmoothing, OnParametersChanged())
    SYNC_PROP_MODIFY(release_smoothing, mReleaseSmoothing, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS

SAVE_OBJ(FxSendSynapse, 0x68);

void FxSendSynapse::Load(BinStream& bs){
    int rev;
    bs >> rev;
    if(rev > 5) MILO_WARN("Can't load new FxSendSynapse");
    else {
        FxSend::Load(bs);
        bs >> mAmount >> mProximityEffect >> mNote1Hz;
        if(rev > 1) bs >> mAttackSmoothing;
        if(rev > 2) bs >> mProximityFocus;
        if(rev > 3) bs >> mReleaseSmoothing;
        if(rev > 4) bs >> mNote2Hz >> mNote3Hz >> mUnisonTrio;
        OnParametersChanged();
    }
}

BEGIN_COPYS(FxSendSynapse)
    COPY_SUPERCLASS(FxSend)
    CREATE_COPY(FxSendSynapse, c)
    if(c){
        COPY_MEM(c, mAmount)
        COPY_MEM(c, mProximityEffect)
        COPY_MEM(c, mProximityFocus)
        COPY_MEM(c, mNote1Hz)
        COPY_MEM(c, mNote2Hz)
        COPY_MEM(c, mNote3Hz)
        COPY_MEM(c, mUnisonTrio)
        COPY_MEM(c, mAttackSmoothing)
        COPY_MEM(c, mReleaseSmoothing)   
    }
END_COPYS
