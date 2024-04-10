#include "beatmatch/JoypadMidiController.h"

JoypadMidiController::JoypadMidiController(User* user, const DataArray* cfg, BeatMatchControllerSink* bsink, bool disabled) : 
    JoypadController(user, cfg, bsink, disabled, false), mWhammy(0.0f) {
    JoypadSubscribe(this);
}

JoypadMidiController::~JoypadMidiController(){
    JoypadUnsubscribe(this);
}

float JoypadMidiController::GetWhammyBar() const {
    return -mWhammy;
}

float JoypadMidiController::GetCapStrip() const {
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

int JoypadMidiController::OnMsg(const KeyboardKeyPressedMsg& msg){
    if(IsDisabled()) return 0;
    if(!IsOurPadNum(msg.GetNode4())) return 0;
    JoypadButton btn = MidiNoteToButton(msg.GetNode2());
    if(btn == kPad_Circle){
        mSink->OutOfRangeSwing();
    }
    else {
        JoypadController::OnMsg(ButtonDownMsg(mLocalUser, btn, kAction_None, mLocalUser->GetPadNum()));
    }
    return 0;
}

int JoypadMidiController::OnMsg(const KeyboardKeyReleasedMsg& msg){
    if(IsDisabled()) return 0;
    if(!IsOurPadNum(msg.GetNode3())) return 0;
    JoypadButton btn = MidiNoteToButton(msg.GetNode2());
    JoypadController::OnMsg(ButtonUpMsg(mLocalUser, btn, kAction_None, mLocalUser->GetPadNum()));
    return 0;
}

int JoypadMidiController::OnMsg(const KeyboardSustainMsg& msg){
    if(IsDisabled()) return 0;
    if(!IsOurPadNum(msg.GetNode3())) return 0;
    mSink->ForceMercurySwitch(true);
    mSink->ForceMercurySwitch(false);
    return 0;
}

int JoypadMidiController::OnMsg(const KeyboardModMsg& msg){
    if(IsDisabled()) return 0;
    if(!IsOurPadNum(msg.GetNode3())) return 0;
    mWhammy = msg.GetNode2() / 127.0f;
    return 0;
}

JoypadButton JoypadMidiController::MidiNoteToButton(int note) const {
    static DataNode* keyboard_wide_frets = DataVariable("keyboard_wide_frets");
    int theInt = keyboard_wide_frets->Int(0);
    if(theInt != 0){
        theInt = note / 0xC + (note >> 0x1F);
        int u5 = theInt - (theInt >> 0x1F);
        int pad = mLocalUser->GetPadNum();
        if(pad < 2 && (theInt = u5 >> 0x1F, (u5 & 1 ^ -theInt) + theInt != pad)) return kPad_Circle;
    }
    theInt = note / 0xC + (note >> 0x1F);
    theInt = note + (theInt - (theInt >> 0x1F)) * -0xC;
    switch(theInt){
        case 0:
            return kPad_L2;
        case 2:
            return kPad_R2;
        case 4:
            return kPad_L1;
        case 5:
            return kPad_R1;
        case 7:
            return kPad_Tri;
        default: return kPad_Circle;
    }
}

int JoypadMidiController::OnMsg(const ButtonDownMsg& msg){
    if(IsDisabled()) return 0;
    if(!IsOurPadNum(msg.GetPadNum())) return 0;
    JoypadButton btn = msg.GetButton();
    if(btn == mForceMercuryBut){
        mSink->ForceMercurySwitch(true);
        mSink->ForceMercurySwitch(false);
    }
    return 0;    
}

BEGIN_HANDLERS(JoypadMidiController)
    HANDLE_MESSAGE(KeyboardKeyPressedMsg)
    HANDLE_MESSAGE(KeyboardKeyReleasedMsg)
    HANDLE_MESSAGE(KeyboardModMsg)
    HANDLE_MESSAGE(KeyboardSustainMsg)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_CHECK(0xDB)
END_HANDLERS
