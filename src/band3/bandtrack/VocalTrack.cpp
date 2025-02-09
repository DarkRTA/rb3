#include "bandtrack/VocalTrack.h"
#include "bandobj/NoteTube.h"
#include "decomp.h"
#include "obj/DataFunc.h"

bool gDebugSpew;

DECOMP_FORCEACTIVE(VocalTrack, "popping unbaked plate")

void VocalTrack::DumpAllPlates() {
    for (int i = 0; i < 3; i++) {
        DumpPlates(mFrontTubePlates[i], MakeString("part %d front", i));
        DumpPlates(mBackTubePlates[i], MakeString("part %d back", i));
        DumpPlates(mPhonemeTubePlates[i], MakeString("part %d phoneme", i));
    }
    DumpPlates(mLeadDeployPlates, "lead deploy");
    DumpPlates(mHarmonyDeployPlates, "harmony deploy");
}

DataNode ToggleDebugSpew(DataArray *) {
    gDebugSpew = !gDebugSpew;
    return gDebugSpew;
}

#pragma push
#pragma dont_inline on
VocalTrack::VocalTrack(BandUser *u)
    : Track(u), unk68(0), unk6c(1), unk70(2), unk78(24.0f), unk7c(0), mDir(this),
      mPlayer(this), unke8(0), unkec(0), unkf0(0), unkf4(0), unkf8(0), unkfc(0),
      unk100(0), unk104(1), unk108(0), unk128(0), unk19c(0), unk1c8(this),
      mTambourineGemPool(0), unk204(-1), unk208(60), unk20c(0), unk210(0), unk23c(0.1f),
      unk240(0.1f), unk294(0), unk298(0), unk2a4(-1.0f), unk2a8(0), unk2ac(0), unk2b0(0),
      unk2c0(2.0f), unk2c4(0.5f), unk2c8(0.1f), unk2cc(100.0f), unk2d0(20.0f),
      unk2d4(250.0f), unk2d8(100.0f), unk2dc(500.0f), unk2e0(100.0f), unk2e4(0),
      mNoteTube(new NoteTube()), unk2ec(1) {
    DataRegisterFunc("vocal_jitter_debug", ToggleDebugSpew);
    for (int i = 0; i < 3; i++) {
        mFrontTubePlates.push_back(std::deque<TubePlate *>());
        mBackTubePlates.push_back(std::deque<TubePlate *>());
        mPhonemeTubePlates.push_back(std::deque<TubePlate *>());
        unk2b4[i] = 0;
    }
    InitPlatePool();
}
#pragma pop