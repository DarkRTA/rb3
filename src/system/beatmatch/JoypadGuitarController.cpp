#include "beatmatch/JoypadGuitarController.h"

float JoypadGuitarControllerRX = 0.0f;

JoypadGuitarController::JoypadGuitarController(User* user, const DataArray* cfg, BeatMatchControllerSink* bsink, bool disabled, bool lefty) : 
    BeatMatchController(user, cfg, lefty), mDisabled(disabled), mDpadForNavigation(true), mFretMask(0), mSink(bsink) {
    JoypadSubscribe(this);
    if(!disabled) ReconcileFretState();
    cfg->FindData("dpad_for_navigation", mDpadForNavigation, false);
}

JoypadGuitarController::~JoypadGuitarController(){
    JoypadUnsubscribe(this);
}

void JoypadGuitarController::Disable(bool b){
    mDisabled = b;
    if(!b) ReconcileFretState();
}

float JoypadGuitarController::GetWhammyBar() const {
    if(!mUser->IsLocal()) return 0.0f;
    else {
        LocalUser* lUser = mUser->GetLocalUser();
        if(!UserHasController(lUser)) return 0.0f;
        else {
            JoypadData* thePadData = JoypadGetPadData(lUser->GetPadNum());
            float stick = thePadData->mSticks[0][1];
            float* ptr;
            if(stick < JoypadGuitarControllerRX) ptr = &stick;
            else ptr = &JoypadGuitarControllerRX;
            return *ptr;

        }
    }
}

int JoypadGuitarController::OnMsg(const ButtonDownMsg& msg){
    if(mDisabled) return 0;
    if(msg.GetUser() != mUser) return 0;
    MILO_ASSERT(mSink, 0x4B);
    JoypadButton btn = msg.GetButton();
    if(btn == kPad_Select){
        mSink->ForceMercurySwitch(true);
    }
    else {
        int slot = ButtonToSlot(btn);
        if(slot != -1){
            mSink->FretButtonDown(slot, -1);
            mSink->Swing(slot, false, true, false, false, (GemHitFlags)0);
            mFretMask |= 1 << slot;
        }
    }
    return 0;
}

int JoypadGuitarController::OnMsg(const ButtonUpMsg& msg){
    if(mDisabled) return 0;
    if(msg.GetUser() != mUser) return 0;
    MILO_ASSERT(mSink, 0x68);
    JoypadButton btn = msg.GetButton();
    if(btn == mForceMercuryBut){
        mSink->ForceMercurySwitch(false);
    }
    int slot = ButtonToSlot(btn);
    if(slot != -1){
        mSink->FretButtonUp(slot);
        mFretMask &= ~(1 << slot);
    }
    return 0;
}

void JoypadGuitarController::ReconcileFretState(){
    if(mUser->IsLocal()){
        LocalUser* lUser = mUser->GetLocalUser();
        if(UserHasController(lUser)){
            JoypadData* thePadData = JoypadGetPadData(lUser->GetPadNum());
            int mask = 0;
            for(int i = 0; i < 5; i++){
                int fretmask = mFretMask;
                bool inFretMask = (fretmask & 1 << i);
                bool isCurBtnInMask = thePadData->IsButtonInMask(SlotToButton(i));
                if(isCurBtnInMask){
                    mask |= 1 << i;
                }
                if(inFretMask != isCurBtnInMask){
                    if(isCurBtnInMask){
                        mSink->FretButtonDown(i, -1);
                    }
                    else {
                        mSink->FretButtonUp(i);
                    }
                }
            }
            mFretMask = mask;
            mSink->ForceMercurySwitch(thePadData->IsButtonInMask(mForceMercuryBut));
        }
    }
}

BEGIN_HANDLERS(JoypadGuitarController)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_CHECK(0x9C)
END_HANDLERS
