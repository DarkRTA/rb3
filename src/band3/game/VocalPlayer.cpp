#include "game/VocalPlayer.h"

VocalPlayer::VocalPlayer(
    BandUser *user, BeatMaster *bmaster, Band *band, int tracknum, Performer *perf, int
)
    : Player(user, band, tracknum, bmaster), unk2cc(perf), unk2d0(0), unk2d4(0),
      unk2d8(0), unk2dc(1.25f), unk2e8(0), unk2ec(0), unk2f0(0), unk300(0), unk304(0),
      unk308(0), unk328(-1), unk32c(0), unk330(0), unk334(0), unk338(0.6f), unk33c(0),
      unk340(0), unk344(0), unk348(0), unk34c(-1.0f), unk368(0), unk36c(0), unk370(0),
      unk374(0), unk378(0), unk37c(0), unk380(0), unk384(0), unk388(1),
      mTambourineManager(*this), unk414(0), unk418(0), unk41c(0), unk420(0), unk424(0) {}
