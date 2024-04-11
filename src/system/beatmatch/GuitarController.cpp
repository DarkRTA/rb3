#include "beatmatch/GuitarController.h"

GuitarController::GuitarController(User* user, const DataArray* cfg, BeatMatchControllerSink* bsink, bool disabled, bool lefty) : 
    BeatMatchController(user, cfg, lefty), mDisabled(disabled), unk3d(0), mFretMask(0), mShiftButtonMask(0), mSink(bsink), mControllerStyle(kPS2), mStrumBarButtons(), unk58(0) {
    JoypadSubscribe(this);
    Symbol cntType;
    if(cfg->FindData("controller_style", cntType, false)){
        if(cntType == "ps2") mControllerStyle = kPS2;
        else if(cntType == "hx_ps3") mControllerStyle = kPS3;
        else if(cntType == "ro_ps3") mControllerStyle = kRoPS3;
        else if(cntType == "ro_xbox") mControllerStyle = kRoXbox;
        else if(cntType == "hx_xbox") mControllerStyle = kHxXbox;
        else if(cntType == "hx_wii") mControllerStyle = kHxWii;
        else MILO_FAIL("Bad controller style %s\n", cntType);
    }
    if(mControllerStyle == kHxXbox) unk58 = 3;
    if(mControllerStyle == kPS3) unk58 = 3;
    if(mControllerStyle == kHxWii) unk58 = 3;
    if(!disabled) ReconcileFretState();
    DataArray* strum_buttons = cfg->FindArray("strum_buttons", false);
    if(strum_buttons){
        // unkvec.reserve(5);
        for(int i = 1; i < strum_buttons->Size(); i++){
            mStrumBarButtons.push_back(strum_buttons->Int(i));
        }
    }
    else {
        // reserve 5 here too
    }
    DataArray* shift_button_cfg = cfg->FindArray("shift_button", false);
    if(shift_button_cfg){
        mShiftButtonMask = 1 << shift_button_cfg->Int(1);
    }
}

GuitarController::~GuitarController(){
    JoypadUnsubscribe(this);
}
