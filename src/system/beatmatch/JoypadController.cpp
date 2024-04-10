#include "beatmatch/JoypadController.h"
#include "utl/Symbols.h"
#include "os/Debug.h"

float somefloatidk = 0.0f; // JoypadController's RX - possibly a resting position for the whammy?

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
        JoypadData* thePadData = GetJoypadData();
        float stick = thePadData->mSticks[0][1];
        float* ptr;
        if(stick < somefloatidk) ptr = &stick;
        else ptr = &somefloatidk;
        return *ptr;
    }
    else {
        return 0.0f;
    }
}

int JoypadController::GetVelocityBucket(int i) const {
    if (mLocalUser == 0)
        return 0;

    if (mVelocityAxes) {
        DataArray* findMapSlot = mVelocityAxes->FindArray(MapSlot(i), false);
        if (!findMapSlot) {
            return 0;
        } else {
            return GetJoypadData()->GetVelocityBucket(findMapSlot->Sym(1));
        }
    } else if (mVelocityPressures) {
        DataArray* findMapSlot = mVelocityPressures->FindArray(MapSlot(i), false);
        if (!findMapSlot)
            return 0;
        else {
            return GetJoypadData()->GetPressureBucket((JoypadButton)findMapSlot->Int(1));
        }
    }

    return 0;
}


bool JoypadController::IsCymbal(int i) const {
    if(!mLocalUser) return false;
    else {
        JoypadData* thePadData = GetJoypadData();
        bool ret = false;
        switch(i){
            case 2:
                ret = false;
                if(thePadData->IsButtonInMask(mCymbalShiftButton)){
                    bool b2 = true;
                    if(!thePadData->IsButtonInMask(0xC) && thePadData->IsButtonInMask(mPadShiftButton)){
                        b2 = false;
                    }
                    if(b2) ret = true;
                }
                break;
            case 3:
                ret = false;
                if(thePadData->IsButtonInMask(mCymbalShiftButton)){
                    bool bvar3 = true;
                    if(!thePadData->IsButtonInMask(0xE) && thePadData->IsButtonInMask(mPadShiftButton)){
                        bvar3 = false;
                    }
                    if(bvar3) ret = true;
                }
                break;
            case 4:
                ret = false;
                if(thePadData->IsButtonInMask(mCymbalShiftButton)){
                    bool bvar4_2 = false;
                    bool bvar4_1 = false;
                    if(thePadData->IsButtonInMask(0xC) || thePadData->IsButtonInMask(0xE)){
                        bvar4_1 = true;
                    }
                    if(bvar4_1 && thePadData->IsButtonInMask(mPadShiftButton)){
                        bvar4_2 = true;
                    }
                    if(!bvar4_2) ret = true;
                }
                break;
            default: break;
        }
        return ret;
    }
}

int JoypadController::GetVirtualSlot(int i) const {
    if(!mLocalUser) return i;
    int ret = i;
    JoypadData* thePadData = GetJoypadData();
    if(mPadShiftButton == kPad_NumButtons){
        if((thePadData->mType == kJoypadXboxRoDrums || thePadData->mType == kJoypadPs3RoDrums)){
            if(mLefty){
                switch(i){
                    case 2:
                        ret = 5;
                        break;
                    case 4:
                        bool cym = IsCymbal(4);
                        ret = 8;
                        if(cym) ret = 4;
                        break;
                    default: break;
                }
            }
            return ret;
        }
    }
    else if(1U < i){
        switch(i){
            case 2:
                if(mLefty){
                    if(HasBlueCymbal(thePadData)){
                        if(IsCymbal(3)){
                            if(thePadData->mHasSecondaryPedal && mSecondaryPedalFunction == kHiHatPedal){
                                ret = thePadData->IsButtonInMask(mSecondaryPedalButton) + 6;
                            }
                            else ret = 5;
                        }
                        else ret = 2;
                    }
                    else {
                        ret = mAlternateMapping ? 5 : 2;
                    }
                }
                else {
                    if(HasYellowCymbal(thePadData)){
                        if(IsCymbal(2)){
                            if(thePadData->mHasSecondaryPedal && mSecondaryPedalFunction == kHiHatPedal){
                                ret = thePadData->IsButtonInMask(mSecondaryPedalButton) + 6;
                            }
                            else ret = 5;
                        }
                        else ret = 2;
                    }
                    else {
                        ret = mAlternateMapping ? 5 : 2;
                    }
                }
                break;
            case 3:
                if(mLefty){
                    if(IsCymbal(2)) ret = 7;
                    else ret = 3;
                }
                else {
                    if(IsCymbal(3)) ret = 7;
                    else ret = 3;
                }
                break;
            case 4:
                if(mLefty){
                    if(HasGreenCymbal(thePadData)){
                        if(IsCymbal(4)) ret = 4;
                        else ret = 8;
                    }
                    else {
                        ret = 8;
                        if(mAlternateMapping) ret = 4;
                    }
                }
                else {
                    if(HasGreenCymbal(thePadData)){
                        if(IsCymbal(4)) ret = 4;
                        else ret = 8;
                    }
                    else {
                        ret = 8;
                        if(mAlternateMapping) ret = 4;
                    }
                }
                break;
            default: 
                MILO_FAIL("JoypadController::GetVirtualSlot of bad slot %d", i);
                break;
        }
    }
    return ret;
}

int JoypadController::OnMsg(const ButtonDownMsg& msg){
    if(mDisabled) return 0;
    if(!mLocalUser) return 0;
    if(msg.GetUser() != mLocalUser) return 0;
    JoypadData* thePadData = GetJoypadData();
    MILO_ASSERT(mSink, 0x1A2);
    JoypadButton btn = msg.GetButton();
    if(btn == mForceMercuryBut){
        mSink->ForceMercurySwitch(true);
        RegisterHit((HitType)0x15);
    }
    else if((btn == mCymbalShiftButton || btn == mPadShiftButton) && NoSlotButtonsThisFrame()){
        if(mLefty){
            if(GetJoypadData()->IsButtonInMask(SlotToButton(4))){
                if(btn == mCymbalShiftButton){
                    mSink->Swing(4, false, true, false, false, (GemHitFlags)4);
                    RegisterHit((HitType)0x11);
                }
                else {
                    mSink->Swing(1, false, true, false, false, (GemHitFlags)0);
                    RegisterHit((HitType)0);
                }
            }
        }
    }
    else {
        int slot = ButtonToSlot(btn);
        if(slot != -1){
            int i9 = 0;
            int i5 = BeatMatchController::ButtonToSlot(btn);
            if(IsCymbal(i5)) i9 |= 4;
            switch(i5){
                case 0:
                    RegisterHit((HitType)0xE);
                    break;
                case 1:
                    RegisterHit((HitType)1);
                    break;
                case 2:
                    RegisterHit((i9 & 4) ? (HitType)0xF : (HitType)2);
                    break;
                case 3:
                    RegisterHit((i9 & 4) ? (HitType)0x10 : (HitType)3);
                    break;
                case 4:
                    RegisterHit((i9 & 4) ? (HitType)0x11 : (HitType)0);
                    break;
                default: break;
            }
            mSink->Swing(slot, false, true, false, false, (GemHitFlags)i9);
            mSink->FretButtonDown(slot, -1);
            mFretMask |= 1 << slot;
            if(mLefty && BeatMatchController::ButtonToSlot(btn) == 4 && 
                thePadData->IsButtonInMask(mCymbalShiftButton) &&
                thePadData->IsButtonInMask(mPadShiftButton) &&
                !thePadData->IsButtonInMask(0xC) &&
                !thePadData->IsButtonInMask(0xE) &&
                !thePadData->IsButtonInMask(BeatMatchController::SlotToButton(1)) &&
                !thePadData->IsButtonInMask(BeatMatchController::SlotToButton(2)) &&
                !thePadData->IsButtonInMask(BeatMatchController::SlotToButton(3))){
                mSink->Swing(1, false, true, false, false, (GemHitFlags)0);
                RegisterHit((HitType)0);
            }
        }
    }
    return 0;
}

int JoypadController::OnMsg(const ButtonUpMsg& msg){
    if(mDisabled) return 0;
    MILO_ASSERT(mSink, 0x213);
    if(!mLocalUser) return 0;
    if(msg.GetUser() != mLocalUser) return 0;
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

void JoypadController::ReconcileFretState(){
    if(mLocalUser && UserHasController(mLocalUser)){
        int mask = 0;
        for(int i = 0; i < 5; i++){
            bool curMask = mFretMask & 1 << i;
            bool btnInMask = GetJoypadData()->IsButtonInMask(SlotToButton(i));
            if(btnInMask) mask |= 1 << i;
            if(curMask != btnInMask){
                if(btnInMask) mSink->FretButtonDown(i, -1);
                else mSink->FretButtonUp(i);
            }
        }
        mFretMask = mask;
    }
}

bool JoypadController::NoSlotButtonsThisFrame() const {
    for(int i = 1; i <= 4; i++){
        if(GetJoypadData()->IsButtonNewlyPressed(
            BeatMatchController::SlotToButton(i)
        )) return false;
    }
    return true;
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
