#include "ui/LabelNumberTicker.h"
#include "ui/UILabel.h"
#include "ui/UI.h"
#include "utl/Locale.h"
#include "math/MathFuncs.h"
#include "utl/Symbols.h"

INIT_REVS(LabelNumberTicker)

void LabelNumberTicker::Init(){
    Register();
    TheUI->InitResources("LabelNumberTicker");
}

LabelNumberTicker::LabelNumberTicker() : mLabel(this, 0), mDesiredValue(0), mAnimTime(0.0f), mAnimDelay(0.0f), mWrapperText(gNullStr), 
    mAcceleration(0.0f), unk12c(0), unk130(0), mTickTrigger(this, 0), mTickEvery(0) {

}

LabelNumberTicker::~LabelNumberTicker(){

}

BEGIN_COPYS(LabelNumberTicker)
    CREATE_COPY_AS(LabelNumberTicker, p)
    MILO_ASSERT(p, 0x33);
    COPY_MEMBER_FROM(p, mLabel)
    COPY_MEMBER_FROM(p, mDesiredValue)
    COPY_MEMBER_FROM(p, mAnimTime)
    COPY_MEMBER_FROM(p, mAnimDelay)
    COPY_MEMBER_FROM(p, mWrapperText)
    COPY_MEMBER_FROM(p, mAcceleration)
    COPY_MEMBER_FROM(p, mTickTrigger)
    COPY_MEMBER_FROM(p, mTickEvery)
    UIComponent::Copy(p, ty);
END_COPYS

SAVE_OBJ(LabelNumberTicker, 0x46)

void LabelNumberTicker::Enter(){
    UIComponent::Enter();
    UpdateDisplay();
}

BEGIN_LOADS(LabelNumberTicker)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void LabelNumberTicker::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    bs >> mLabel >> mDesiredValue >> mAnimTime >> mAnimDelay >> mWrapperText;
    if(gRev >= 1) bs >> mAcceleration;
    if(gRev >= 2){
        bs >> mTickTrigger >> mTickEvery;
    }
    UIComponent::PreLoad(bs);
}

void LabelNumberTicker::PostLoad(BinStream& bs){
    UIComponent::PostLoad(bs);
    Update();
}

void LabelNumberTicker::UpdateDisplay(){
    if(mLabel){
        bool textIsNull = mWrapperText == gNullStr;
        if(!textIsNull){
            mLabel->SetTokenFmt(mWrapperText, LocalizeSeparatedInt(unk130));
        }
    }
}

// fn_80549740
void LabelNumberTicker::Poll(){
    UIComponent::Poll();
    if(mTimer.Running()){
        float split = mTimer.SplitMs();
        float animdelay = mAnimDelay * 1000.0f;
        float animtime = mAnimTime * 1000.0f;
        float animsum = animdelay + animtime;
        if(split >= animdelay){
            float quotient = (split - animdelay) / animtime;
            float powf = pow_f(animtime, mAcceleration);
            int somenum = unk12c + (animtime*animdelay)*(mDesiredValue-unk12c);
            if(mTickTrigger){
                if(mTickEvery != 0){
                    if((somenum / mTickEvery) > (unk130 / mTickEvery)){
                        mTickTrigger->Trigger();
                    }
                }
            }
            unk130 = somenum;
            if(unk130 == mDesiredValue || (split >= animsum)){
                unk130 = mDesiredValue;
                mTimer.fn_800A8898();
            }
        }
        UpdateDisplay();
    }
}

void LabelNumberTicker::SetLabel(UILabel* l){
    mLabel = l;
    UpdateDisplay();
}

void LabelNumberTicker::SetDesiredValue(int i){
    unk12c = unk130;
    mDesiredValue = i;
    if(mAnimTime + mAnimDelay <= 0.0f) unk130 = i;
    else {
        mTimer.Reset();
        mTimer.Start();
    }
    if(mTickTrigger && i > 0){
        mTickTrigger->Trigger();
    }
    UpdateDisplay();
}

void LabelNumberTicker::SnapToValue(int i){
    unk130 = i;
    mDesiredValue = i;
    UpdateDisplay();
}

void LabelNumberTicker::CountUp(){
    int val = mDesiredValue;
    SnapToValue(0);
    SetDesiredValue(val);
}

BEGIN_HANDLERS(LabelNumberTicker)
    HANDLE_ACTION(snap_to_value, SnapToValue(_msg->Int(2)))
    HANDLE_ACTION(count_up, CountUp())
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0xD5)
END_HANDLERS

BEGIN_PROPSYNCS(LabelNumberTicker)
    SYNC_PROP_SET(label, (Hmx::Object*)mLabel, SetLabel(_val.Obj<UILabel>(0)))
    SYNC_PROP_SET(desired_value, mDesiredValue, SetDesiredValue(_val.Int(0)))
    SYNC_PROP_MODIFY(wrapper_text, mWrapperText, UpdateDisplay())
    SYNC_PROP_MODIFY(anim_time, mAnimTime, UpdateDisplay())
    SYNC_PROP_MODIFY(anim_delay, mAnimDelay, UpdateDisplay())
    SYNC_PROP(acceleration, mAcceleration)
    SYNC_PROP(tick_trigger, mTickTrigger)
    SYNC_PROP(tick_every, mTickEvery)
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS