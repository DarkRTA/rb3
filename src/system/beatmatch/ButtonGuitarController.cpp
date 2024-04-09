#include "beatmatch/ButtonGuitarController.h"

ButtonGuitarController::ButtonGuitarController(User* user, const DataArray* cfg, BeatMatchControllerSink* bsink, bool b1, bool lefty) : BeatMatchController(user, cfg, false),
    mDisabled(b1), mShifted(0), mSlotMask(0), mSink(bsink) {
        mLefty = lefty;
        JoypadSubscribe(this);
}

ButtonGuitarController::~ButtonGuitarController(){
    
}

void ButtonGuitarController::Disable(bool b){
    mDisabled = b;
}

bool ButtonGuitarController::IsDisabled() const {
    return mDisabled;
}

float ButtonGuitarController::GetWhammyBar() const {
    return 0.0f;
}

int ButtonGuitarController::GetFretButtons() const {
    return 0;
}

bool ButtonGuitarController::IsShifted() const {
    return mShifted;
}

void ButtonGuitarController::SetAutoSoloButtons(bool){}

int ButtonGuitarController::OnMsg(const RGSwingMsg& msg){
    if(!mDisabled && mUser->IsLocal()){
        LocalUser* lUser = mUser->GetLocalUser();
        int msgInt = ((DataArray*)msg)->Int(3);
        int padnum = lUser->GetPadNum();
        if(padnum == msgInt){
            int slot = GetCurrentSlot();
            return mSink->Swing(slot, true, true, false, true, IsShifted() ? kGemHitFlagSolo : kGemHitFlagNone);
        }
    }
    return 0;
}

int ButtonGuitarController::OnMsg(const ButtonDownMsg& msg){
    if(!mDisabled && mUser->IsLocal()){
        LocalUser* lUser = mUser->GetLocalUser();
        int msgInt = ((DataArray*)msg)->Int(5);
        int padnum = lUser->GetPadNum();
        if(padnum == msgInt){
            if(((DataArray*)msg)->Int(3) == 8)
                mSink->ForceMercurySwitch(true);
        }
    }
    return 0;
}

int ButtonGuitarController::OnMsg(const ButtonUpMsg& msg){
    if(!mDisabled && mUser->IsLocal()){
        LocalUser* lUser = mUser->GetLocalUser();
        int msgInt = ((DataArray*)msg)->Int(5);
        int padnum = lUser->GetPadNum();
        if(padnum == msgInt){
            if(((DataArray*)msg)->Int(3) == 8)
                mSink->ForceMercurySwitch(false);
        }
    }
    return 0;
}
