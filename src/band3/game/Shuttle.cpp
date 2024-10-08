#include "Shuttle.h"
#include "os/Joypad.h"
#include <cmath>

Shuttle::Shuttle() : unk_0x0(0), unk_0x4(0), mActive(0), mPadNum(0) {}
Shuttle::~Shuttle() {}

void Shuttle::SetActive(bool b) { mActive = b; }

void Shuttle::Poll() {
    if (mActive) {
        JoypadData* data = JoypadGetPadData(mPadNum);
        if (data) {
            float f2 = pow(data->GetLX(), 5);
            float f1 = 1000.0f;
            f1 *= f2;
            float f0 = unk_0x0 + f1; // this func is a mess
            if (f0 > unk_0x4) {
                if (f0 < 0) f2 = f0;
            } else f2 = unk_0x4;

            unk_0x0 = f2;
        }
    }
}
