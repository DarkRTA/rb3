#include "beatmatch/RealGuitarController.h"
#include "beatmatch/RGState.h"
#include "os/UsbMidiGuitar.h"
#include "beatmatch/RGUtl.h"

RealGuitarController::RealGuitarController(User* user, const DataArray* cfg, BeatMatchControllerSink* bsink, bool disabled, bool lefty) : 
    BeatMatchController(user, cfg, false), mDisabled(disabled), mSink(bsink) {
    mLefty = lefty;
    JoypadSubscribe(this);
    mStrings[5] = mStrings[4] = mStrings[3] = mStrings[2] = mStrings[1] = mStrings[0] = 0;
}

RealGuitarController::~RealGuitarController(){
    JoypadUnsubscribe(this);
}

void RealGuitarController::Poll(){}
void RealGuitarController::Disable(bool b){ mDisabled = b; }
bool RealGuitarController::IsDisabled() const { return mDisabled; }
float RealGuitarController::GetWhammyBar() const { return 0.0f; }
int RealGuitarController::GetFretButtons() const { return 0; }
bool RealGuitarController::IsShifted() const { return false; }
void RealGuitarController::SetAutoSoloButtons(bool){}

int RealGuitarController::GetRGFret(int string) const {
    MILO_ASSERT(string >= 0 && string < kNumRGStrings, 0x55);
    return mStrings[string];
}

int RealGuitarController::OnMsg(const StringStrummedMsg& msg){
    if(!IsOurPadNum(msg.GetPadNum())) return 0;
    int fretnum = msg.GetFretNum();
    if(fretnum > 0x16){
        MILO_WARN("Warning: Fret # is %d:", fretnum);
        return 0;
    }
    int i4 = 5 - msg.GetStringNum();
    if(mLefty){
        i4 = msg.GetStringNum();
    }
    int u5 = PackRGData(i4, fretnum);
    mStrings[i4] = fretnum;
    if(mDisabled) return 0;
    if(msg.GetVelocity() < UsbMidiGuitar::E3CheatGetMinVelocity()){
        RegisterRGFret(i4, fretnum);
        mSink->FretButtonDown(u5, -1);
        mSink->NonStrumSwing(u5, true, false);
    }
    else {
        mSink->RGFretButtonDown(u5);
        RegisterRGStrum(i4);
    }
    return 0;
}

int RealGuitarController::OnMsg(const RGSwingMsg& msg){
    if(mDisabled || !IsOurPadNum(msg.GetPadNum())) return 0;
    int mask = 0;
    if(mLefty){
        for(int i = 0; i < 6; i++){
            if(msg.GetNode2() & 1 << i){
                mask |= 1 << 5 - i;
            }
        }
    }
    else mask = msg.GetNode2();
    for(int i = 0; i < 6; i++){
        if(mask & 1 << i){
            int tuning = RGGetTuning(i) & 0xFF;
            mSink->PlayNote(mStrings[i] + tuning - 12);
        }
    }
    mSink->Swing(mask, true, true, false, false, (GemHitFlags)0);
    return 0;
}

int RealGuitarController::OnMsg(const ButtonDownMsg& msg){
    if(mDisabled || !IsOurPadNum(msg.GetPadNum())) return 0;
    if(msg.GetUser() != mUser) return 0;
    MILO_ASSERT(mSink, 0xB0);
    if(msg.GetButton() == kPad_Select){
        mSink->ForceMercurySwitch(true);
    }
    return 0;
}

int RealGuitarController::OnMsg(const ButtonUpMsg& msg){
    if(mDisabled || !IsOurPadNum(msg.GetPadNum())) return 0;
    if(msg.GetUser() != mUser) return 0;
    MILO_ASSERT(mSink, 0xC3);
    if(msg.GetButton() == kPad_Select){
        mSink->ForceMercurySwitch(false);
    }
    return 0;
}

int RealGuitarController::OnMsg(const RGAccelerometerMsg& msg){
    if(mDisabled || !IsOurPadNum(msg.GetPadNum())) return 0;
    mSink->MercurySwitch(msg.GetNode3() / 127.0f);
    return 0;
}

BEGIN_HANDLERS(RealGuitarController)
    HANDLE_MESSAGE(StringStrummedMsg)
    HANDLE_MESSAGE(StringStoppedMsg)
    HANDLE_MESSAGE(RGSwingMsg)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_MESSAGE(RGAccelerometerMsg)
    HANDLE_CHECK(0xDF)
END_HANDLERS
