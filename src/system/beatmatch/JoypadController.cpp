#include "beatmatch/JoypadController.h"
#include "utl/Symbols.h"

float somefloatidk = 0.0f;

JoypadController::JoypadController(User* user, const DataArray* cfg, BeatMatchControllerSink* bsink, bool b1, bool lefty) : BeatMatchController(user, cfg, lefty),
    mDisabled(b1), unk3d(0), mAlternateMapping(0), mFretMask(0), mSecondaryPedalFunction(kHiHatPedal), mCymbalConfiguration(0), mSink(bsink) {
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

int JoypadController::MapSlot(int i) const {
    int ret = i;
    if(mLefty){
        if(mGemMapping == kDrumGemMapping){
            if(ret == 0) return 0;
            else if(ret == 4 && IsCymbal(4) && mCymbalShiftButton != kPad_NumButtons){
                return 4;
            }
            else return 5 - ret;
        }
        else return 4 - ret;
    }
    return ret;
}

int JoypadController::ButtonToSlot(JoypadButton btn) const {
    if(mSecondaryPedalFunction == kSecondKickPedal && btn == mSecondaryPedalButton) return 0;
    else {
        int bmSlot = BeatMatchController::ButtonToSlot(btn);
        if(bmSlot == -1) return bmSlot;
        else return MapSlot(bmSlot);
    }
}

int JoypadController::SlotToButton(int i) const {
    return BeatMatchController::SlotToButton(MapSlot(i));
}

void JoypadController::Disable(bool b){
    mDisabled = b;
    if(b){
        for(int i = 0; i < 5; i++){
            if(mFretMask & (1 << i)){
                mSink->FretButtonUp(i);
            }
        }
        mFretMask = 0;
    }
    else ReconcileFretState();
}

float JoypadController::GetWhammyBar() const {
    if(!mUser->IsLocal()) return 0.0f;
    if(mLocalUser){
        JoypadData* thePadData = mLocalUser ? JoypadGetPadData(mLocalUser->GetPadNum()) : 0;
        float stick = thePadData->mSticks[0][1];
        return (stick < somefloatidk) ? stick : somefloatidk;
    }
    else {
        return 0.0f;
    }
}

void JoypadController::SetSecondPedalHiHat(bool b){
    mSecondaryPedalFunction = (SecondaryPedalFunction)(b == 0);
}

void JoypadController::SetCymbalConfiguration(int i){
    mCymbalConfiguration = i;
}

BEGIN_HANDLERS(JoypadController)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_CHECK(0x273)
END_HANDLERS

static void weakfuncslol(JoypadController* jc){
    jc->IsDisabled();
    jc->GetFretButtons();
    jc->UseAlternateMapping(0);
    jc->IsAlternateMapping();
}
