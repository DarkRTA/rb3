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
    int msgInt = msg.GetPadNum();
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
    int msgInt = msg.GetPadNum();
    int padnum = lUser->GetPadNum();
    if(msgInt != padnum) return 0;
    if(msg.GetButton() == kPad_Select)
        mSink->ForceMercurySwitch(true);
    return 0;
}

int ButtonGuitarController::OnMsg(const ButtonUpMsg& msg){
    if(mDisabled) return 0;
    if(!mUser->IsLocal()) return 0;
    LocalUser* lUser = mUser->GetLocalUser();
    int msgInt = msg.GetPadNum();
    int padnum = lUser->GetPadNum();
    if(msgInt != padnum) return 0;
    if(msg.GetButton() == kPad_Select)
        mSink->ForceMercurySwitch(false);
    return 0;
}

int ButtonGuitarController::OnMsg(const RGFretButtonDownMsg& msg){
    if(mDisabled) return 0;
    if(!mUser->IsLocal()) return 0;
    LocalUser* lUser = mUser->GetLocalUser();
    int msgInt = msg.GetPadNum();
    int padnum = lUser->GetPadNum();
    if(msgInt != padnum) return 0;
    MILO_ASSERT(mSink, 0x8A);
    int i1 = msg.GetNode2();
    mShifted = msg.GetShifted() != 0;
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
    int msgInt = msg.GetPadNum();
    int padnum = lUser->GetPadNum();
    if(msgInt != padnum) return 0;
    MILO_ASSERT(mSink, 0xA4);
    int i1 = msg.GetNode2();
    mShifted = msg.GetShifted() != 0;
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
    int msgInt = msg.GetPadNum();
    int padnum = lUser->GetPadNum();
    if(msgInt != padnum) return 0;
    MILO_ASSERT(mSink, 0xBB);
    mSink->MercurySwitch(msg.GetNode3() / 127.0f);
    return 0;
}

int ButtonGuitarController::GetCurrentSlot() const {
    int ret = -1;
    int i;

    for (i = 0; i < 5; i++) {
        if ((mSlotMask & (1 << i))) {
            ret = i;
        }
    }
    
    return ret;
}

BEGIN_HANDLERS(ButtonGuitarController)
    if(sym == StringStrummedMsg::Type()){
        DataNode result = DataNode(OnMsg(StringStrummedMsg(_msg)));
        if(result.Type() != kDataUnhandled) return DataNode(result);
    }
    if(sym == StringStoppedMsg::Type()){
        DataNode result = DataNode(OnMsg(StringStoppedMsg(_msg)));
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
