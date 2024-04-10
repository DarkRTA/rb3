#include "beatmatch/KeyboardController.h"

KeyboardController::KeyboardController(User* user, const DataArray* cfg, BeatMatchControllerSink* bsink, bool disabled) : 
    BeatMatchController(user, cfg, false), mDisabled(disabled), mFretButtons(), unk44(0.0f), mSink(bsink) {
    JoypadSubscribe(this);
}

KeyboardController::~KeyboardController(){
    JoypadUnsubscribe(this);
}

void KeyboardController::Poll(){}

void KeyboardController::Disable(bool b){ mDisabled = b; }
