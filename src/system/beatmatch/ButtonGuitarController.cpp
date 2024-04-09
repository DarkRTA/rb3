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
    if(mDisabled) return 0;
    if(!mUser->IsLocal()) return 0;
    
    LocalUser* lUser = mUser->GetLocalUser();
    int msgInt = ((DataArray*)msg)->Int(3);
    int padnum = lUser->GetPadNum();
    if(msgInt != padnum) return 0;
    int slot = GetCurrentSlot();
    mSink->Swing(slot, true, true, false, true, IsShifted() ? kGemHitFlagSolo : kGemHitFlagNone);
    return 0;
}

int ButtonGuitarController::OnMsg(const ButtonDownMsg& msg){
    if(mDisabled) return 0;
    if(!mUser->IsLocal()) return 0;
    LocalUser* lUser = mUser->GetLocalUser();
    int msgInt = ((DataArray*)msg)->Int(5);
    int padnum = lUser->GetPadNum();
    if(msgInt != padnum) return 0;
    if(((DataArray*)msg)->Int(3) == 8)
        mSink->ForceMercurySwitch(true);
    return 0;
}

int ButtonGuitarController::OnMsg(const ButtonUpMsg& msg){
    if(mDisabled) return 0;
    if(!mUser->IsLocal()) return 0;
    LocalUser* lUser = mUser->GetLocalUser();
    int msgInt = ((DataArray*)msg)->Int(5);
    int padnum = lUser->GetPadNum();
    if(msgInt != padnum) return 0;
    if(((DataArray*)msg)->Int(3) == 8)
        mSink->ForceMercurySwitch(false);
    return 0;
}

int ButtonGuitarController::OnMsg(const RGFretButtonDownMsg& msg){
    if(mDisabled) return 0;
    if(!mUser->IsLocal()) return 0;
    LocalUser* lUser = mUser->GetLocalUser();
    int msgInt = ((DataArray*)msg)->Int(3);
    int padnum = lUser->GetPadNum();
    if(msgInt != padnum) return 0;
    MILO_ASSERT(mSink, 0x8A);
    DataArray* arr = ((DataArray*)msg);
    int i1 = arr->Int(2);
    int i3 = arr->Int(4);
    mShifted = i3 != 0;
    mSlotMask |= (1 << i1);
    mSink->FretButtonDown(i1, -1);
    if(mShifted && mSink->Swing(i1, false, true, true, false, kGemHitFlagSolo) != 0) return 0;
    mSink->NonStrumSwing(i1, true, mShifted);
    return 0;
}

int ButtonGuitarController::OnMsg(const RGFretButtonUpMsg& msg){
    if(mDisabled) return 0;
    if(!mUser->IsLocal()) return 0;
    LocalUser* lUser = mUser->GetLocalUser();
    int msgInt = ((DataArray*)msg)->Int(3);
    int padnum = lUser->GetPadNum();
    if(msgInt != padnum) return 0;
    MILO_ASSERT(mSink, 0xA4);
    DataArray* arr = ((DataArray*)msg);
    int i1 = arr->Int(2);
    int i3 = arr->Int(4);
    mShifted = i3 != 0;
    mSlotMask &= ~(1 << i1);
    mSink->FretButtonUp(i1);
    if(mSlotMask != 0)
        mSink->NonStrumSwing(GetCurrentSlot(), false, mShifted);
    return 0;
}

int ButtonGuitarController::OnMsg(const RGAccelerometerMsg& msg){
    if(mDisabled) return 0;
    if(!mUser->IsLocal()) return 0;
    LocalUser* lUser = mUser->GetLocalUser();
    int msgInt = ((DataArray*)msg)->Int(5);
    int padnum = lUser->GetPadNum();
    if(msgInt != padnum) return 0;
    MILO_ASSERT(mSink, 0xBB);
    DataArray* arr = ((DataArray*)msg);
    int i3 = arr->Int(3);
    mSink->MercurySwitch(127.0f);
    // mShifted = i3 != 0;
    // mSlotMask &= ~(1 << i1);
    // mSink->FretButtonUp(i1);
    // if(mSlotMask != 0)
    //     mSink->NonStrumSwing(GetCurrentSlot(), false, mShifted);
    return 0;
}

int ButtonGuitarController::GetCurrentSlot() const {
    int ret = -1;
    if(mSlotMask & 1) ret = 0;
    if(mSlotMask & 2) ret = 1;
    if(mSlotMask & 4) ret = 2;
    if(mSlotMask & 8) ret = 3;
    if(mSlotMask & 0x10) ret = 4;
    return ret;
}

BEGIN_HANDLERS(ButtonGuitarController)
    if(sym == StringStrummedMsg::Type()){
        StringStrummedMsg theMsg(_msg);
        DataNode result(0);
        theMsg.~StringStrummedMsg();
        if(result.Type() != kDataUnhandled) return DataNode(result);
    }
    if(sym == StringStoppedMsg::Type()){
        StringStoppedMsg theMsg(_msg);
        DataNode result = DataNode(0);
        theMsg.~StringStoppedMsg();
        if(result.Type() != kDataUnhandled) return DataNode(result);
    }
    if(sym == RGSwingMsg::Type()){
        DataNode result = DataNode(OnMsg(RGSwingMsg(_msg)));
        if(result.Type() != kDataUnhandled) return DataNode(result);
    }
    if(sym == ButtonDownMsg::Type()){
        DataNode result = DataNode(OnMsg(ButtonDownMsg(_msg)));
        if(result.Type() != kDataUnhandled) return DataNode(result);
    }
    if(sym == ButtonUpMsg::Type()){
        DataNode result = DataNode(OnMsg(ButtonUpMsg(_msg)));
        if(result.Type() != kDataUnhandled) return DataNode(result);
    }
    if(sym == RGFretButtonDownMsg::Type()){
        DataNode result = DataNode(OnMsg(RGFretButtonDownMsg(_msg)));
        if(result.Type() != kDataUnhandled) return DataNode(result);
    }
    if(sym == RGFretButtonUpMsg::Type()){
        DataNode result = DataNode(OnMsg(RGFretButtonUpMsg(_msg)));
        if(result.Type() != kDataUnhandled) return DataNode(result);
    }
    if(sym == RGAccelerometerMsg::Type()){
        DataNode result = DataNode(OnMsg(RGAccelerometerMsg(_msg)));
        if(result.Type() != kDataUnhandled) return DataNode(result);
    }
    HANDLE_CHECK(0xDA)
END_HANDLERS
