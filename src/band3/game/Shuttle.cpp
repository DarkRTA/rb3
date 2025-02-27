#include "Shuttle.h"
#include "os/Joypad.h"
#include <cmath>

Shuttle::Shuttle() : mMs(0), mEndMs(0), mActive(0), mPadNum(0) {}
Shuttle::~Shuttle() {}

void Shuttle::SetActive(bool b) { mActive = b; }

void Shuttle::Poll() {
    if (mActive) {
        JoypadData *data = JoypadGetPadData(mPadNum);
        if (data) {
            mMs = Clamp<float>(0, mEndMs, mMs + powf(data->GetLX(), 5) * 1000.0f);
        }
    }
}
