#include "beatmatch/GuitarController.h"

GuitarController::GuitarController(User* user, const DataArray* cfg, BeatMatchControllerSink* bsink, bool disabled, bool lefty) : 
    BeatMatchController(user, cfg, lefty), mDisabled(disabled), mAutoSoloButtons(0), mFretMask(0), mShiftButtonMask(0), mSink(bsink), mControllerStyle(kPS2), mStrumBarButtons(), unk58(0) {
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
        mStrumBarButtons.reserve(strum_buttons->Size() - 1);
        for(int i = 1; i < strum_buttons->Size(); i++){
            mStrumBarButtons.push_back(strum_buttons->Int(i));
        }
    }
    else {
        mStrumBarButtons.reserve(2);
        if(lefty){
            mStrumBarButtons.push_back(0xE);
            mStrumBarButtons.push_back(0xC);
        }
        else {
            mStrumBarButtons.push_back(0xC);
            mStrumBarButtons.push_back(0xE);
        }
    }

    DataArray* shift_button_cfg = cfg->FindArray("shift_button", false);
    if(shift_button_cfg){
        mShiftButtonMask = 1 << shift_button_cfg->Int(1);
    }
}

GuitarController::~GuitarController(){
    JoypadUnsubscribe(this);
}

void GuitarController::Disable(bool b){
    mDisabled = b;
    if(b){
        for(int i = 0; i < 5; i++){
            if(mFretMask & 1 << i){
                mSink->FretButtonUp(i);
            }
        }
        mFretMask = 0;
    }
    else ReconcileFretState();
}

float guitarwhammyprobs = 0.0f;

float GuitarController::GetWhammyBar() const {
    bool idk;
    float* ptr;
    float ret;
    if(!mUser->IsLocal()) return 0.0f;
    else {
        LocalUser* lUser = mUser->GetLocalUser();
        if(!UserHasController(lUser)) return 0.0f;
        JoypadData* thePadData = JoypadGetPadData(lUser->GetPadNum());
        Symbol cntType = JoypadControllerTypePadNum(lUser->GetPadNum());
        DataArray* found = SystemConfig("joypad")->FindArray("controllers", cntType);
        if(found->FindData("ly_whammy", idk, false)){
            *ptr = thePadData->GetLY();
        }
        else if(found->FindData("negative_rx_whammy_val", idk, false)){
            *ptr = -thePadData->GetRX();
        }
        else if(found->FindData("traditional_whammy_val", idk, false)){
            *ptr = -(thePadData->GetRX() + 1.0f) * 0.5f;
        }
        if(guitarwhammyprobs < *ptr){
            ptr = &guitarwhammyprobs;
        }
        ret = *ptr;
    }
    return ret;
}

float GuitarController::GetCapStrip() const { return 0.0f; }

void GuitarController::Poll(){
    bool idk;
    if(!mUser->IsLocal()) return;
    else {
        LocalUser* lUser = mUser->GetLocalUser();
        if(!UserHasController(lUser)) return;
        if(mDisabled) return;
        JoypadData* thePadData = JoypadGetPadData(lUser->GetPadNum());
        Symbol cntType = JoypadControllerTypePadNum(lUser->GetPadNum());
        DataArray* found = SystemConfig("joypad")->FindArray("controllers", cntType);
        if(found->FindData("xbox_mercury_switch", idk, false)){
            mSink->MercurySwitch(-thePadData->GetRY());
        }
        else if(found->FindData("ps3_mercury_switch", idk, false)) {
            mSink->MercurySwitch(thePadData->mSensors[0] * -4.65f);
        }
    }
}

bool GuitarController::IsShifted() const {
    if(!mUser->IsLocal()) return false;
    else if(mAutoSoloButtons) return true;
    else {
        JoypadData* thePadData = JoypadGetPadData(mUser->GetLocalUser()->GetPadNum());
        unsigned int btns = thePadData->mButtons;
        return btns & mShiftButtonMask;
    }
}

BEGIN_HANDLERS(GuitarController)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_CHECK(0x1BA)
END_HANDLERS