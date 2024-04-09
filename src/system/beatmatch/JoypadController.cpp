#include "beatmatch/JoypadController.h"
#include "utl/Symbols.h"

JoypadController::JoypadController(User* user, const DataArray* cfg, BeatMatchControllerSink* bsink, bool b1, bool lefty) : BeatMatchController(user, cfg, lefty),
    unk3c(b1), unk3d(0), unk3e(0), unk40(0), unk44(0), unk48(0), mSink(bsink) {
    mVelocityAxes = cfg->FindArray("velocity_axes", false);
    mVelocityPressures = cfg->FindArray("velocity_pressures", false);
    if(user->IsLocal()){
        mLocalUser = user->GetLocalUser();
        DataArray* sysConfig = SystemConfig(joypad, controllers, JoypadControllerTypePadNum(mLocalUser->GetPadNum()));
        mPadShiftButton = (JoypadButton)sysConfig->FindArray(pad_shift_button, true)->Int(1);
        mCymbalShiftButton = (JoypadButton)sysConfig->FindArray(cymbal_shift_button, true)->Int(1);
        mSecondaryPedalButton = (JoypadButton)sysConfig->FindArray(secondary_button, true)->Int(1);
        
    }
    else {
        mLocalUser = 0;
        mPadShiftButton = kPad_NumButtons;
        mCymbalShiftButton = kPad_NumButtons;
        mSecondaryPedalButton = kPad_NumButtons;
    }
    JoypadSubscribe(this);
    if(!b1) ReconcileFretState();
}

JoypadController::~JoypadController(){
    
}
