#include "game/TambourineManager.h"
#include "game/VocalPlayer.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/System.h"

TambourineManager::TambourineManager(VocalPlayer &p)
    : mPlayerRef(p), mIsLocal(p.IsLocal()), unk30(0), unk34(Hmx::Object::New<Fader>()),
      unk38(0), unk44(0), unk48(1), unk4c(0), unk5c(0), unk60(0), unk68(0), unk74(0),
      unk78(0), unk7c(0) {
    DataArray *cfg = SystemConfig("scoring", "vocals");
    int diff = mPlayerRef.GetUser()->GetDifficulty();
    mTambourineWindowTicks = cfg->FindInt("tambourine_window_ticks");
    mTambourineCrowdSuccess =
        cfg->FindArray("tambourine_crowd_success", true)->Float(diff + 1);
    mTambourineCrowdFailure =
        cfg->FindArray("tambourine_crowd_failure", true)->Float(diff + 1);
    mTambourinePoints = cfg->FindFloat("tambourine_points");
}

TambourineManager::~TambourineManager() {
    RELEASE(unk34);
    unk24 = nullptr;
}