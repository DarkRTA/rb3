#include "FretHand.h"

#include "os/Debug.h"

FretHand::FretHand() {
    Reset();
}

FretHand::~FretHand() {}

void FretHand::SetFinger(uint finger, int fret, int lowstr, int highstr) {
    MILO_ASSERT(finger < kNumFingers, 24);
    FretFinger& thefinger = mFinger[finger];
    thefinger.mFret = fret;
    thefinger.mLowString = lowstr;
    thefinger.mHighString = highstr;
}

void FretHand::GetFinger(uint finger, int& fret, int& lowstr, int& highstr) const {
    MILO_ASSERT(finger < kNumFingers, 33);
    fret = mFinger[finger].mFret;
    lowstr = mFinger[finger].mLowString;
    highstr = mFinger[finger].mHighString;
}

void FretHand::Reset() {
    for (int i = 0; i < kNumFingers; i++) SetFinger(i, -1, -1, -1);
}

int FretHand::GetFret(int x) const {
    // if (test[1] == x) {
    //     return test[0];
    // } else if (test[1] > x && test[2] == x) {
    //     return test[3];
    // }
}
