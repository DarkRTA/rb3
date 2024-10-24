#include "beatmatch/KeyboardController.h"

KeyboardController::KeyboardController(User* user, const DataArray* cfg, BeatMatchControllerSink* bsink, bool disabled) : 
    BeatMatchController(user, cfg, false), mDisabled(disabled), mFretButtons(), mWhammy(0.0f), mSink(bsink) {
    JoypadSubscribe(this);
}

KeyboardController::~KeyboardController(){
    JoypadUnsubscribe(this);
}

void KeyboardController::Poll(){}

void KeyboardController::Disable(bool b){ mDisabled = b; }

float KeyboardController::GetWhammyBar() const {
    return -GetCapStrip();
}

float KeyboardController::GetCapStrip() const {
    float f;
    if(!mUser->IsLocal()){
        f = 0.0f;
    }
    else {
        mUser->GetLocalUser();
        f = mWhammy;
    }
    return f;
}

int KeyboardController::OnMsg(const KeyboardKeyPressedMsg& msg){
    if(mDisabled) return 0;
    if(!IsOurPadNum(msg.GetPadNum())) return 0;
    MILO_ASSERT(mSink, 0x52);
    RegisterKey(msg.GetNode2());
    int slot = MidiNoteToSlot(msg.GetNode2());
    mSink->NoteOn(msg.GetNode2());
    if(slot != -1){
        mSink->FretButtonDown(slot, msg.GetNode3());
        mSink->Swing(slot, false, true, false, false, (GemHitFlags)0);
        mFretButtons |= 1 << slot;
    }
    return 0;
}

int KeyboardController::OnMsg(const KeyboardKeyReleasedMsg& msg){
    if(mDisabled) return 0;
    if(!IsOurPadNum(msg.GetNode3())) return 0;
    int slot = MidiNoteToSlot(msg.GetNode2());
    mSink->NoteOff(msg.GetNode2());
    if(slot != -1){
        mSink->FretButtonUp(slot);
        mFretButtons &= ~(1 << slot);
    }
    return 0;
}

int KeyboardController::OnMsg(const KeyboardSustainMsg& msg){
    if(IsDisabled()) return 0;
    if(!IsOurPadNum(msg.GetNode3())) return 0;
    mSink->ForceMercurySwitch(true);
    mSink->ForceMercurySwitch(false);
    return 0;
}

int KeyboardController::OnMsg(const KeyboardModMsg& msg){
    if(IsDisabled()) return 0;
    if(!IsOurPadNum(msg.GetNode3())) return 0;
    mWhammy = msg.GetNode2() / 127.0f;
    return 0;
}

int KeyboardController::OnMsg(const ButtonDownMsg& msg){
    if(IsDisabled()) return 0;
    if(!IsOurPadNum(msg.GetPadNum())) return 0;
    JoypadButton btn = msg.GetButton();
    if(btn == mForceMercuryBut){
        mSink->ForceMercurySwitch(true);
        mSink->ForceMercurySwitch(false);
    }
    return 0;
}

int KeyboardController::MidiNoteToSlot(int note) const {
    if(note - 0x30 > 0x18U) return -1;
    else return note - 0x30;
}

BEGIN_HANDLERS(KeyboardController)
    HANDLE_MESSAGE(KeyboardKeyPressedMsg)
    HANDLE_MESSAGE(KeyboardKeyReleasedMsg)
    HANDLE_MESSAGE(KeyboardSustainMsg)
    HANDLE_MESSAGE(KeyboardModMsg)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_CHECK(0xC6)
END_HANDLERS
