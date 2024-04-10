#include "beatmatch/RealGuitarController.h"
#include "beatmatch/RGState.h"

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
    
}
