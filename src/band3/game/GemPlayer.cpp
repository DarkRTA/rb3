#include "GemPlayer.h"
#include "obj/DataFunc.h"
#include "obj/ObjMacros.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

class DeltaTracker;
DeltaTracker *sTracker = nullptr;

static DataNode OnEnableDeltas(DataArray *array) {
    delete sTracker;
    sTracker = nullptr;
    if (array->Int(1) != 0) {
        // sTracker = new DeltaTracker;
    }
    return 0;
}

static DataNode OnPrintDeltas(DataArray *array) {
    { MILO_LOG("No samples to be had\n"); }
    return 0;
}

void DeltaTrackerInit() {
    static bool once = true;
    if (once) {
        DataRegisterFunc("enable_deltas", OnEnableDeltas);
        DataRegisterFunc("print_deltas", OnPrintDeltas);
    }
    once = false;
}

GemPlayer::GemPlayer(
    BandUser *user, BeatMaster *bm, Band *band, int i, BandPerformer *perf
)
    : Player(user, band, i, bm) {

      };

GemPlayer::~GemPlayer() {}

void GemPlayer::SetFillLogic(FillLogic fl) {
    if (mBeatMatcher)
        mBeatMatcher->SetFillLogic(fl);
}

bool GemPlayer::IsAutoplay() const { return mBeatMatcher->IsAutoplay(); }

void GemPlayer::SetAutoplay(bool b) { mBeatMatcher->SetAutoplay(b); }

void GemPlayer::PrintMsg(const char *str) {
    const char *prnt = MakeString("", 3, str);
    *unk_0x340 << prnt;
    MILO_LOG(prnt);
}

void GemPlayer::PrintAddHead(int mils, int idx, int pts, int ms_avg, int recent) {
    if (unk2c4) {
        char id[5] = { 0 };
        if (idx > 1) {
            sprintf(id, " X %d", idx);
        }
        PrintMsg(MakeString(
            "%s (%dms) %d pts -- %dms avg  -- %d recent", id, mils, pts, ms_avg, recent
        ));
    }
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(GemPlayer)
    HANDLE_ACTION(
        disable_fills_deploy_band_energy, mBehavior->SetFillsDeployBandEnergy(false)
    )
    HANDLE_ACTION(
        enable_fills_deploy_band_energy, mBehavior->SetFillsDeployBandEnergy(true)
    )

    HANDLE_ACTION(
        win, unk_0x2cc ? unk_0x2cc->WinGame(_msg->Int(2)) : WinGame(_msg->Int(2))
    )
    HANDLE_ACTION(lose, unk_0x2cc ? unk_0x2cc->LoseGame() : LoseGame())

    HANDLE_SUPERCLASS(Player)
    HANDLE_CHECK(4668)
END_HANDLERS
#pragma pop
