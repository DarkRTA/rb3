#include "game/VocalScoreHistory.h"
#include "os/Debug.h"
#include "utl/Std.h"

#define kHistorySampleCount 20

VocalScoreHistory::VocalScoreHistory(int i1, int i2)
    : unk0(0), unkc(0), unk10(i1), unk14(i2), unk18(0), mOctaveOffset(0), unk20(0) {
    mScores.resize(20);
    MILO_ASSERT(mScores.size() == kHistorySampleCount, 0x1D);
}

VocalScoreHistory::~VocalScoreHistory() {}

void VocalScoreHistory::AddScore(float f1, float f2) {
    if (f1 < unk0 + 50.0f)
        return;
    else {
        mScores[unkc++] = f2;
        if (unkc >= mScores.size())
            unkc = 0;
        unk0 = f1;
        unk20 = true;
    }
}

void VocalScoreHistory::BiasLastScore(float f1) {
    if (unk20) {
        unk20 = false;
        int i2 = unkc - 1;
        if (i2 < 0) {
            i2 = mScores.size() - 1;
        }
        mScores[i2];
        mScores[i2] *= f1;
    }
}

float VocalScoreHistory::CalculateSum(float f1) const {
    float sum = 0;
    for (int i = 0; i < mScores.size(); i++) {
        sum += mScores[i];
    }
    return sum;
}

void VocalScoreHistory::SetOctaveOffset(int i) { mOctaveOffset = i; }
int VocalScoreHistory::GetOctaveOffset() const { return mOctaveOffset; }

void VocalScoreHistory::Reset() {
    unk0 = 0;
    unkc = 0;
    unk18 = 0;
    mOctaveOffset = 0;
    unk20 = 0;
    FOREACH (it, mScores) {
        *it = 0;
    }
}