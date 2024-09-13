#include "bandobj/MeterDisplay.h"
#include "utl/Symbols.h"

MeterDisplay::MeterDisplay() : unk10c(0), mAnimPeriod(0), unk114(0), unk118(-1), unk11c(0), mShowText(0), mPercentageText(0), mHideDenominator(0),
    mWrapperText(gNullStr), mCurrentValue(0), mMaxValue(0) {

}

MeterDisplay::~MeterDisplay(){
    
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