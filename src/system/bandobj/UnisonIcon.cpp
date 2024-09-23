#include "bandobj/UnisonIcon.h"
#include "utl/Symbols.h"

INIT_REVS(UnisonIcon)

UnisonIcon::UnisonIcon() : mProgress(0), mStartTrig(0), mEndTrig(0), mSucceedTrig(0), mFailTrig(0), mResetTrig(0), mMeterWipeAnim(0), mIconLabel(0) {

}

void UnisonIcon::SyncObjects(){
    RndDir::SyncObjects();
    if(!mStartTrig) mStartTrig = Find<EventTrigger>("start.trig", false);
    if(!mEndTrig) mEndTrig = Find<EventTrigger>("end.trig", false);
    if(!mSucceedTrig) mSucceedTrig = Find<EventTrigger>("succeed.trig", false);
    if(!mFailTrig) mFailTrig = Find<EventTrigger>("fail.trig", false);
    if(!mResetTrig) mResetTrig = Find<EventTrigger>("reset.trig", false);
    if(!mMeterWipeAnim) mMeterWipeAnim = Find<RndAnimatable>("meter_wipe.anim", false);
    if(!mIconLabel) mIconLabel = Find<BandLabel>("icon.lbl", false);
}

SAVE_OBJ(UnisonIcon, 0x2E)

void UnisonIcon::PreLoad(BinStream& bs){
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    RndDir::PreLoad(bs);
}

void UnisonIcon::PostLoad(BinStream& bs){ RndDir::PostLoad(bs); }

BEGIN_COPYS(UnisonIcon)
    COPY_SUPERCLASS(RndDir)
END_COPYS

void UnisonIcon::Reset(){
    mResetTrig->Trigger();
    SetProgress(0.0f);
}

void UnisonIcon::UnisonStart(){ mStartTrig->Trigger(); }
void UnisonIcon::UnisonEnd(){ mEndTrig->Trigger(); }
void UnisonIcon::Succeed(){ mSucceedTrig->Trigger(); }
void UnisonIcon::Fail(){ mFailTrig->Trigger(); }

void UnisonIcon::SetProgress(float f){
    float progress = f;
    if(f < 0.0f || f > 1.0f){
        MILO_WARN("improper unison progress val %.2f, clamping to [0,1]", f);
        ClampEq(progress, 0.0f, 1.0f);
    }
    mProgress = progress;
    if(mMeterWipeAnim) mMeterWipeAnim->SetFrame(progress, 1.0f);
}

void UnisonIcon::SetIcon(const char* cc){ mIconLabel->SetIcon(*cc); }

BEGIN_PROPSYNCS(UnisonIcon)
    SYNC_PROP_MODIFY(progress, mProgress, SetProgress(mProgress))
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS

BEGIN_HANDLERS(UnisonIcon)
    HANDLE_ACTION(reset, Reset())
    HANDLE_ACTION(set_icon, SetIcon(_msg->Str(2)))
    HANDLE_ACTION(start, UnisonStart())
    HANDLE_ACTION(end, UnisonEnd())
    HANDLE_ACTION(succeed, Succeed())
    HANDLE_ACTION(fail, Fail())
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x81)
END_HANDLERS