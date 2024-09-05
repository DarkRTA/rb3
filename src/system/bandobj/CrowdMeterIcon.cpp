#include "bandobj/CrowdMeterIcon.h"
#include "rndobj/Part.h"
#include "utl/Symbols.h"

INIT_REVS(CrowdMeterIcon)

CrowdMeterIcon::CrowdMeterIcon() : mResetTrig(this, 0), mArrowHideTrig(this, 0), mArrowShowTrig(this, 0), mDeployTrig(this, 0), 
    mStopDeployTrig(this, 0), mStateFailedTrig(this, 0), mStateFailingTrig(this, 0), mStateNormalTrig(this, 0), mGlowTrig(this, 0),
    mGlowStopTrig(this, 0), mStateQuarantinedTrig(this, 0), mDropInTrig(this, 0), mDropOutTrig(this, 0), mIconLabel(this, 0),
    mIconStateAnim(this, 0), unk240(0), mState(kCrowdMeterNormal), mQuarantined(0) {

}

void CrowdMeterIcon::SyncObjects(){
    RndDir::SyncObjects();
    if(!mResetTrig) mResetTrig = Find<EventTrigger>("reset.trig", true);
    if(!mArrowHideTrig) mArrowHideTrig = Find<EventTrigger>("arrow_hide.trig", true);
    if(!mArrowShowTrig) mArrowShowTrig = Find<EventTrigger>("arrow_show.trig", true);
    if(!mDeployTrig) mDeployTrig = Find<EventTrigger>("deploy.trig", true);
    if(!mStopDeployTrig) mStopDeployTrig = Find<EventTrigger>("stop_deploy.trig", true);
    if(!mStateFailedTrig) mStateFailedTrig = Find<EventTrigger>("state_failed.trig", true);
    if(!mStateFailingTrig) mStateFailingTrig = Find<EventTrigger>("state_failing.trig", true);
    if(!mStateNormalTrig) mStateNormalTrig = Find<EventTrigger>("state_normal.trig", true);
    if(!mGlowTrig) mGlowTrig = Find<EventTrigger>("glow.trig", true);
    if(!mGlowStopTrig) mGlowStopTrig = Find<EventTrigger>("glow_stop.trig", true);
    if(!mStateQuarantinedTrig) mStateQuarantinedTrig = Find<EventTrigger>("state_quarantined.trig", true);
    if(!mDropInTrig) mDropInTrig = Find<EventTrigger>("drop_in.trig", true);
    if(!mDropOutTrig) mDropOutTrig = Find<EventTrigger>("drop_out.trig", true);
    if(!mIconLabel) mIconLabel = Find<BandLabel>("icon.lbl", true);
    if(!mIconStateAnim) mIconStateAnim = Find<RndAnimatable>("icon_state.anim", true);
}

void CrowdMeterIcon::SetState(CrowdMeterState state, bool b){
    if(state != mState || b){
        mState = state;
        if(!mQuarantined){
            switch(state){
                case kCrowdMeterNormal:
                    mStateNormalTrig->Trigger();
                    break;
                case kCrowdMeterWarning:
                    float delay = unk240->GetPulseAnimStartDelay(false);
                    mIconStateAnim->Animate(0.0f, false, delay, RndAnimatable::k1_fpb, 0.0f, 1.0f, 0.0f, 1.0f, loop);
                    break;
                case kCrowdMeterFailed:
                    mStateFailedTrig->Trigger();
                    break;
                default:
                    break;
            }
        }
    }
}

void CrowdMeterIcon::SetGlowing(bool glow){
    if(glow) mGlowTrig->Trigger();
    else mGlowStopTrig->Trigger();
}

void CrowdMeterIcon::SetIcon(const char* cc){
    mIconLabel->SetIcon(*cc);
}

bool CrowdMeterIcon::HasIcon() const {
    return strcmp(mIconLabel->GetDefaultText(), gNullStr) != 0;
}

void CrowdMeterIcon::ArrowShow(bool show){
    if(show) mArrowShowTrig->Trigger();
    else mArrowHideTrig->Trigger();
}

void CrowdMeterIcon::Deploy(){ mDeployTrig->Trigger(); }
void CrowdMeterIcon::StopDeploy(){ mStopDeployTrig->Trigger(); }

void CrowdMeterIcon::Reset(){
    mResetTrig->Trigger();
    Find<RndParticleSys>("star_power.part", true)->FreeAllParticles();
    mState = kCrowdMeterNormal;
    SetQuarantined(false);
}

void CrowdMeterIcon::SetQuarantined(bool q){
    if(q != mQuarantined){
        mQuarantined = q;
        if(q) mStateQuarantinedTrig->Trigger();
        else SetState(mState, true);
    }
}

void CrowdMeterIcon::DropIn(){ mDropInTrig->Trigger(); }
void CrowdMeterIcon::DropOut(){ mDropOutTrig->Trigger(); }

BEGIN_PROPSYNCS(CrowdMeterIcon)
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS

BEGIN_HANDLERS(CrowdMeterIcon)
    HANDLE_ACTION(reset, Reset())
    HANDLE_ACTION(arrow_hide, ArrowShow(false))
    HANDLE_ACTION(arrow_show, ArrowShow(true))
    HANDLE_ACTION(deploy, Deploy())
    HANDLE_ACTION(stop_deploy, StopDeploy())
    HANDLE_ACTION(set_state, SetState((CrowdMeterState)_msg->Int(2), false))
    HANDLE_ACTION(set_glowing, SetGlowing(_msg->Int(2)))
    HANDLE_ACTION(set_icon, SetIcon(_msg->Str(2)))
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0xD8)
END_HANDLERS

SAVE_OBJ(CrowdMeterIcon, 0xDF)

void CrowdMeterIcon::PreLoad(BinStream& bs){
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    RndDir::PreLoad(bs);
}

void CrowdMeterIcon::PostLoad(BinStream& bs){ RndDir::PostLoad(bs); }

BEGIN_COPYS(CrowdMeterIcon)
    COPY_SUPERCLASS(RndDir)
END_COPYS