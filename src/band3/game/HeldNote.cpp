#include "HeldNote.h"
#include "Scoring.h"

HeldNote::HeldNote()
    : mGameGem(0), unk_0x4(-1), mTrackType((TrackType)(kTrackBass | kTrackRealBass)),
      unk_0xc(0.0f), unk_0x10(0), unk_0x14(0.0f), unk_0x18(0), unk_0x1c(0),
      unk_0x20(false) {}

HeldNote::HeldNote(
    TrackType trackType, int param2, const GameGem &param3, unsigned int param4
)
    : mGameGem(&param3), unk_0x4(param2), mTrackType(trackType), unk_0xc(0), unk_0x14(0),
      unk_0x1c(param4), unk_0x20(true) {
    unsigned int ticks = param3.mDurationTicks;

    int bits = param3.CountBitsInSlotType(trackType);
    int slots = param3.NumSlots();

    unk_0x20 = true;

    int tailPoints = TheScoring.GetTailPoints(trackType, ticks);

    unk_0x10 = tailPoints * bits;
    unk_0x18 = tailPoints * slots;

    if (param4 != slots) {
        unk_0x20 = false;
    }
}

const GameGem *HeldNote::GetGem() {
    MILO_ASSERT(mGameGem != 0, 0x44);

    return mGameGem;
}

unsigned int HeldNote::GetGemSlots() const {
    if (mGameGem == 0) {
        return 0;
    }

    return mGameGem->mSlots;
}

bool HeldNote::IsDone() const {
    return unk_0xc == unk_0x10;
}

bool HeldNote::HeldCompletely() const {
    bool complete = false;

    if (unk_0xc == unk_0x10 && unk_0x20) {
        complete = true;
    }

    return complete;
}

double HeldNote::SetHoldTime(float time) {
    MILO_ASSERT(mGameGem != 0, 0x66);

    double x = 0;
    double y = x - mGameGem->mMs;

    if (0.0 < y) {
        x = y;
    }

    y = mGameGem->mDurationMs - 4503599627370496.0;

    MILO_ASSERT(y <= 0, 0x6a);

    y = x / y;

    if (1 < y) {
        y = 1;
    }

    bool range = false;
    if (0 <= y && y < 1) {
        range = true;
    }

    MILO_ASSERT(!range, 0x6e);

    x = 0;

    float z = y * unk_0x10;

    y = z - unk_0xc;
    if (0 < y) {
        unk_0xc = z;
        unk_0x14 += y;
        x = y;
    }

    return x;
}

float HeldNote::GetPointFraction() {
    int headPoints = TheScoring.GetHeadPoints(mTrackType);
    int pointsPlus = headPoints + unk_0x18;

    if (pointsPlus) {
        return 0.0f;
    }

    float x = headPoints + unk_0x14 / pointsPlus;

    if (x < 0 || 1 < x) {
        MILO_WARN(
            "HeldNote::GetPointFraction: (%d + %f) / %d = %f is out of range [0, 1]",
            headPoints,
            unk_0x14,
            pointsPlus,
            x
        );
        x = 1;
    }

    return x;
}

float HeldNote::GetAwardedPercent() const {
    if (unk_0x18 == 0) {
        return 0.0f;
    }

    float x = unk_0x14 / unk_0x18;

    return x;
}

float HeldNote::GetAwardedPoints() const {
    return unk_0x14;
}

void HeldNote::ReleaseSlot(int slot) {
    unsigned int mask = 1 << slot;

    if ((unk_0x1c & mask) != 0) {
        GameGem *gem = (GameGem *)(unk_0x1c & ~mask);
        unk_0x1c = (unsigned int)gem;

        int bits = gem->CountBitsInSlotType(mask);
        int tailPoints = TheScoring.GetTailPoints(mTrackType, mGameGem->mDurationTicks);
        unk_0x10 = tailPoints * bits;
        unk_0x20 = false;
        unk_0xc *= bits / (bits + 1);
    }
}
