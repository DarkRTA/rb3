#include "HeldNote.h"
#include "Scoring.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "os/Debug.h"

HeldNote::HeldNote()
    : mGem(0), unk_0x4(-1), mTrackType(kTrackNone), unk_0xc(0.0f), unk_0x10(0),
      unk_0x14(0.0f), unk_0x18(0), unk_0x1c(0), unk_0x20(false) {}

HeldNote::HeldNote(TrackType trackType, int gemID, const GameGem &gem, unsigned int param4)
    : mGem(&gem), unk_0x4(gemID), mTrackType(trackType), unk_0xc(0), unk_0x14(0),
      unk_0x1c(param4), unk_0x20(true) {
    unsigned int ticks = gem.GetDurationTicks();
    int bits = gem.CountBitsInSlotType(param4);
    int slots = gem.NumSlots();
    unk_0x20 = bits == slots;
    int tailPoints = TheScoring->GetTailPoints(trackType, ticks);
    unk_0x10 = tailPoints * bits;
    unk_0x18 = tailPoints * slots;
    if (param4 != gem.mSlots) {
        unk_0x20 = false;
    }
}

const GameGem *HeldNote::GetGem() {
    MILO_ASSERT(mGem, 0x44);
    return mGem;
}

unsigned int HeldNote::GetGemSlots() const { return !mGem ? 0 : mGem->GetSlots(); }

FORCE_LOCAL_INLINE
bool HeldNote::IsDone() const { return unk_0xc == unk_0x10 ? true : false; }
END_FORCE_LOCAL_INLINE

bool HeldNote::HeldCompletely() const { return IsDone() && unk_0x20; }

float HeldNote::SetHoldTime(float time) {
    MILO_ASSERT(mGem, 0x66);
    float f3 = Max<float>(0, time - mGem->GetMs());
    float total = mGem->DurationMs();
    MILO_ASSERT(total > 0, 0x6A);
    float fraction = Min<float>(f3 / total, 1);
    MILO_ASSERT(fraction >= 0 && fraction <= 1, 0x6E);

    float frac = fraction * (float)unk_0x10;
    float f2 = frac - unk_0xc;
    if (f2 > 0) {
        unk_0xc = frac;
        unk_0x14 += f2;
        return f2;
    } else
        return 0;
}

float HeldNote::GetPointFraction() {
    int headPoints = TheScoring->GetHeadPoints(mTrackType);
    int pointsPlus = headPoints + unk_0x18;
    if (pointsPlus <= 0)
        return 0;
    else {
        float f1 = (float)(headPoints + unk_0x14) / (float)(pointsPlus);
        if (f1 < 0.0f || f1 > 1.0f) {
            MILO_WARN(
                "HeldNote::GetPointFraction: (%d + %f) / %d = %f is out of range [0, 1]",
                headPoints,
                unk_0x14,
                pointsPlus,
                f1
            );
            f1 = 1.0f;
        }
        return f1;
    }
}

float HeldNote::GetAwardedPercent() const {
    return unk_0x18 == 0 ? 0 : unk_0x14 / unk_0x18;
}

float HeldNote::GetAwardedPoints() const { return unk_0x14; }

void HeldNote::ReleaseSlot(int slot) {
    unsigned int mask = 1 << slot;
    if (unk_0x1c & mask) {
        unk_0x1c &= ~mask;
        unsigned int bits = GameGem::CountBitsInSlotType(mask);
        int tailPts = TheScoring->GetTailPoints(mTrackType, mGem->GetDurationTicks());
        unk_0x10 = tailPts * bits;
        unk_0x20 = false;
        unk_0xc *= ((float)bits / (float)(bits + 1));
    }
}
