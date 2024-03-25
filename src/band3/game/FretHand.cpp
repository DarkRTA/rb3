#include "FretHand.h"

#include "os/Debug.h"

FretHand::FretHand() {
    Reset();
}

FretHand::~FretHand() {}

void FretHand::SetFinger(uint finger, int a, int b, int c) {
    MILO_ASSERT(finger < kNumFingers, 24);
    test[0 + finger * 12] = a;
    test[1] = b;
    test[2] = c;
}

void FretHand::GetFinger(uint finger, int& a, int& b, int& c) const {
    MILO_ASSERT(finger < kNumFingers, 33);
    finger * 12;
    a = test[0] + finger;
    b = test[1];
    c = test[2];
}

void FretHand::Reset() {
    for (int i = 0; i < kNumFingers; i++) SetFinger(i, -1, -1, -1);
}

int FretHand::GetFret(int x) const {
    if (test[1] == x) {
        return test[0];
    } else if (test[1] > x && test[2] == x) {
        return test[3];
    }
}
