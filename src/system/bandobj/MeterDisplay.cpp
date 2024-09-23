#include "bandobj/MeterDisplay.h"
#include "ui/UI.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"

INIT_REVS(MeterDisplay);

void MeterDisplay::Init(){
    Register();
    TheUI->InitResources("MeterDisplay");
}

MeterDisplay::MeterDisplay() : mMeterAnim(0), mAnimPeriod(0), unk114(0), unk118(-1), mMeterLabel(0), mShowText(0), mPercentageText(0), mHideDenominator(0),
    mWrapperText(gNullStr), mCurrentValue(0), mMaxValue(0) {

}

MeterDisplay::~MeterDisplay(){
    delete mMeterLabel;
}

BEGIN_COPYS(MeterDisplay)
    CREATE_COPY_AS(MeterDisplay, p);
    MILO_ASSERT(p, 0x36);
    COPY_MEMBER_FROM(p, mShowText)
    COPY_MEMBER_FROM(p, mPercentageText)
    COPY_MEMBER_FROM(p, mHideDenominator)
    COPY_MEMBER_FROM(p, mWrapperText)
    COPY_MEMBER_FROM(p, mCurrentValue)
    COPY_MEMBER_FROM(p, mMaxValue)
    COPY_MEMBER_FROM(p, mAnimPeriod)
    COPY_SUPERCLASS_FROM(UIComponent, p);
END_COPYS

SAVE_OBJ(MeterDisplay, 0x4C)

void MeterDisplay::Enter(){
    UIComponent::Enter();
    UpdateDisplay();
}

BEGIN_LOADS(MeterDisplay)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void MeterDisplay::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(4, 0);
    bs >> mShowText;
    if(gRev >= 1){
        bs >> mCurrentValue;
        bs >> mMaxValue;
    }
    if(gRev >= 2) bs >> mPercentageText;
    if(gRev >= 3) bs >> mAnimPeriod;
    if(gRev >= 4){
        bs >> mHideDenominator;
        bs >> mWrapperText;
    }
    UIComponent::PreLoad(bs);
}

void MeterDisplay::PostLoad(BinStream& bs){
    UIComponent::PostLoad(bs);
    Update();
}

void MeterDisplay::UpdateDisplay(){
    if(mMeterLabel){
        String str44;
        if(mPercentageText){
            float f = 0;
            if(mMaxValue > 0){
                f = (float)mCurrentValue / (float)mMaxValue;
            }
            str44 = MakeString<int>(Localize(meter_progress_percent, 0), f * 100.0f);
        }
        else if(mHideDenominator){
            String localizedint(LocalizeSeparatedInt(mCurrentValue));
            str44 = MakeString(Localize(meter_progress_no_denominator, 0), localizedint);
        }
        else {
            String current(LocalizeSeparatedInt(mCurrentValue));
            String max(LocalizeSeparatedInt(mMaxValue));
            str44 = MakeString(Localize(meter_progress, 0), current, max);
        }
        if(mWrapperText != gNullStr){
            mMeterLabel->SetTokenFmt(mWrapperText, str44);
        }
        else {
            mMeterLabel->SetTokenFmt(meter_progress_generic_wrapper, str44);
        }
        mMeterLabel->SetShowing(true);
    }
}

void MeterDisplay::DrawShowing(){
    RndDir* dir = mResource->Dir();
    MILO_ASSERT(dir, 0xB6);
    float f = 0;
    if(mMaxValue > 0){
        f = (float)mCurrentValue / (float)mMaxValue;
        float f1 = TheTaskMgr.UISeconds() - unk114;
        if(mAnimPeriod > 0){
            int itouse = unk118;
            if(itouse >= 0 && f1 > 0){
                if(f1 < mAnimPeriod){
                    f = (f1 / mAnimPeriod) * (float)(itouse - mCurrentValue) + (float)mCurrentValue / (float)mMaxValue;
                }
                else {
                    mCurrentValue = itouse;
                    unk118 = -1;
                    f = (float)mCurrentValue / (float)mMaxValue;
                }
            }
        }
    }
    ClampEq(f, 0.0f, 1.0f);
    mMeterAnim->SetFrame((mMeterAnim->EndFrame() - mMeterAnim->StartFrame()) * (f + mMeterAnim->StartFrame()), 1.0f);
    dir->SetWorldXfm(WorldXfm());
    dir->Draw();
    if(mShowText && mMeterLabel) mMeterLabel->Draw();
    SetWorldXfm(WorldXfm());
}

void MeterDisplay::Poll(){
    MILO_ASSERT(mResource, 0xE6);
    if(mResource->Dir()) mResource->Dir()->Poll();
    UIComponent::Poll();
}

void MeterDisplay::SetValues(int i, int j){
    if(i < 0){
        MILO_WARN("MeterDisplay cannot have a current value that is negative.\n");
        i = 0;
    }
    mCurrentValue = i;
    mMaxValue = j;
    UpdateDisplay();
}

void MeterDisplay::SetShowText(bool b){
    mShowText = b;
    UpdateDisplay();
}

void MeterDisplay::SetPercentageText(bool b){
    mPercentageText = b;
    UpdateDisplay();
}

void MeterDisplay::AnimateToValue(int i, int j){
    unk118 = Min(i, mMaxValue);
    unk114 = (float)j / 1000.0f + TheTaskMgr.UISeconds();
}

void MeterDisplay::Update(){
    UIComponent::Update();
    const DataArray* typeDef = TypeDef();
    MILO_ASSERT(typeDef, 0x129);
    RndDir* dir = mResource->Dir();
    MILO_ASSERT(dir, 300);
    const char* label = 0;
    if(typeDef->FindData(meter_label, label, false)){
        BandLabel* thelabel = dir->Find<BandLabel>(label, true);
        if(!mMeterLabel) mMeterLabel = Hmx::Object::New<BandLabel>();
        mMeterLabel->ResourceCopy(thelabel);
        mMeterLabel->SetTransParent(thelabel->TransParent(), false);
        thelabel->SetShowing(false);
    }
    else RELEASE(mMeterLabel);
    mMeterAnim = dir->Find<RndAnimatable>(typeDef->FindStr(meter_anim), true);
}

BEGIN_HANDLERS(MeterDisplay)
    HANDLE_ACTION(animate_to_value, AnimateToValue(_msg->Int(2), _msg->Int(3)))
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0x14C)
END_HANDLERS

BEGIN_PROPSYNCS(MeterDisplay)
    SYNC_PROP_MODIFY(show_text, mShowText, UpdateDisplay())
    SYNC_PROP_MODIFY(percentage_text, mPercentageText, UpdateDisplay())
    SYNC_PROP_MODIFY(hide_denominator, mHideDenominator, UpdateDisplay())
    SYNC_PROP_MODIFY(wrapper_text, mWrapperText, UpdateDisplay())
    SYNC_PROP_MODIFY(current_value, mCurrentValue, UpdateDisplay())
    SYNC_PROP_MODIFY(max_value, mMaxValue, UpdateDisplay())
    SYNC_PROP(anim_period, mAnimPeriod)
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS