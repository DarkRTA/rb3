#include "ui/LabelNumberTicker.h"
#include "ui/UILabel.h"
#include "ui/UI.h"

void LabelNumberTicker::Init(){
    Register();
    TheUI->InitResources("LabelNumberTicker");
}

LabelNumberTicker::LabelNumberTicker() : mLabel(this, 0), mDesiredValue(0), mAnimTime(0.0f), mAnimDelay(0.0f), mWrapperText(gNullStr), 
    mAcceleration(0.0f), unk12c(0), unk130(0), mTickTrigger(this, 0), mTickEvery(0) {

}

LabelNumberTicker::~LabelNumberTicker(){

}