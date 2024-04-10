#include "beatmatch/RealGuitarController.h"
#include "beatmatch/RGState.h"
#include "os/UsbMidiGuitar.h"

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
