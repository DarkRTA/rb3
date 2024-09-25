#include "CustomSplash_Wii.h"

DECOMP_FORCEACTIVE(
    CustomSplash,
    "16_9",
    "4_3",
    "StrapUsage/StrapUsage_eng_%s.tpl",
    "StrapUsage/StrapUsage_fre_%s.tpl",
    "StrapUsage/StrapUsage_ita_%s.tpl",
    "StrapUsage/StrapUsage_deu_%s.tpl",
    "StrapUsage/StrapUsage_esl_%s.tpl",
    "StrapUsage/StrapUsage_nld_%s.tpl",
    "StrapUsage/Loading.tpl",
    "StrapUsage/Loading_fre.tpl",
    "StrapUsage/Loading_ita.tpl",
    "StrapUsage/Loading_deu.tpl",
    "StrapUsage/Loading_esl.tpl"
)

void AllocateMEM2(int size) {
    _MemAlloc(size, 0x20);
}

CustomSplash::CustomSplash() : mTimer1(), mTimer2() {
    unk_64 = 0;
    unk_48c = 0;
    float val = 250.0f;
    unk_60 = -val;
    unk_48d = 0;
    unk_490 = 1;
}