#include "bandobj/OverdriveMeter.h"
#include "utl/Symbols.h"

INIT_REVS(OverdriveMeter)

OverdriveMeter::OverdriveMeter() : mState((State)0), mResetTrig(this, 0), mSpotlightPhraseSuccessTrig(this, 0), mBeDeployingTrig(this, 0), mBeFillingTrig(this, 0),
    mBeReadyTrig(this, 0), mPulseMiloTrig(this, 0), mNoOverdriveTrig(this, 0), mExtendAnimGroup(this, 0), mPulseAnimGroup(this, 0), mTestEnergy(0) {

}

OverdriveMeter::~OverdriveMeter(){
    
}

void OverdriveMeter::SyncObjects(){
    RndDir::SyncObjects();
    mResetTrig = Find<EventTrigger>("reset.trig", false);
    mSpotlightPhraseSuccessTrig = Find<EventTrigger>("spotlight_phrase_success.trig", false);
    mBeDeployingTrig = Find<EventTrigger>("be_deploying.trig", false);
    mBeFillingTrig = Find<EventTrigger>("be_filling.trig", false);
    mBeReadyTrig = Find<EventTrigger>("be_ready.trig", false);
    mPulseMiloTrig = Find<EventTrigger>("pulse_milo.trig", false);
    mNoOverdriveTrig = Find<EventTrigger>("no_overdrive.trig", false);
    mExtendAnimGroup = Find<RndGroup>("extend_anim.grp", false);
    mPulseAnimGroup = Find<RndGroup>("pulse_anim.grp", false);
}

SAVE_OBJ(OverdriveMeter, 0x34)

void OverdriveMeter::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    RndDir::PreLoad(bs);
}

void OverdriveMeter::PostLoad(BinStream& bs){ RndDir::PostLoad(bs); }

BEGIN_COPYS(OverdriveMeter)
    COPY_SUPERCLASS(RndDir)
END_COPYS

void OverdriveMeter::Reset(){
    if(mResetTrig) mResetTrig->Trigger();
    SetEnergy(0.0f, (State)1, guitar, 0.0f, true);
}

void OverdriveMeter::SetEnergy(float f1, OverdriveMeter::State state, Symbol s, float f2, bool b){
    if(mExtendAnimGroup && (f1 != mExtendAnimGroup->GetFrame() || b)){
        mExtendAnimGroup->SetFrame(f1, 1.0f);
    }
    if((state != mState) || b){
        mState = state;
        switch(mState){
            case (State)1:
                StopDeploy();
                break;
            case (State)2:
                EnergyReady(s, !b, f2);
                break;
            case (State)3:
                Deploy();
                break;
            default:
                break;
        }
    }
}

void OverdriveMeter::Deploy(){
    if(mBeDeployingTrig) mBeDeployingTrig->Trigger();
}

void OverdriveMeter::StopDeploy(){
    if(mBeFillingTrig) mBeFillingTrig->Trigger();
    if(mPulseAnimGroup) mPulseAnimGroup->Animate(0.0f, false, 0.0f, RndAnimatable::k30_fps_ui, 0.0f, 0.0f, 0.0f, 1.0f, range);
}

void OverdriveMeter::SetNoOverdrive(){
    if(mNoOverdriveTrig) mNoOverdriveTrig->Trigger();
}

void OverdriveMeter::MiloReset(){
    if(mPulseMiloTrig) mPulseMiloTrig->Trigger();
    Reset();
    SetShowing(true);
}

void OverdriveMeter::EnergyReady(Symbol s, bool b, float f){
    if(mBeReadyTrig) mBeReadyTrig->Trigger();
    if(mPulseAnimGroup) mPulseAnimGroup->Animate(0.0f, false, f, RndAnimatable::k1_fpb, 0.0f, 1.0f, 0.0f, 1.0f, loop);
    if(b){
        const char* seqname = MakeString("rp_available_%s.cue", s);
        Sequence* seq = Find<Sequence>(seqname, true);
        if(seq) seq->Play(0,0,0);
        else MILO_WARN("%s not found in %s", seqname, mPathName);
    }
}

BEGIN_HANDLERS(OverdriveMeter)
    HANDLE_ACTION(initialize, MiloReset())
    HANDLE_ACTION(energy_ready, EnergyReady("guitar", true, 0.0f))
    HANDLE_ACTION(stop_deploy, StopDeploy())
    HANDLE_ACTION(set_no_overdrive, SetNoOverdrive())
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0xB5)
END_HANDLERS

BEGIN_PROPSYNCS(OverdriveMeter)
    SYNC_PROP_MODIFY(test_energy, mTestEnergy, SetEnergy(mTestEnergy, mState, "guitar", 0.0f, true))
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS