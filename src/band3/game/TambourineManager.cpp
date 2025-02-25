#include "game/TambourineManager.h"
#include "game/VocalPlayer.h"
#include "midi/MidiParser.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/System.h"
#include "utl/Symbols.h"

TambourineManager::TambourineManager(VocalPlayer &p)
    : mPlayerRef(p), mIsLocal(p.IsLocal()), mTambourineSequence(0),
      mTambourineFader(Hmx::Object::New<Fader>()), mTambourineParser(0),
      mTambourineIdx(0), unk48(1), unk4c(0), mTambourineActive(0), unk60(0), unk68(0),
      unk74(0), unk78(0), unk7c(0) {
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
    RELEASE(mTambourineFader);
    RELEASE(mTambourineSequence);
    mBank = nullptr;
}

void TambourineManager::PostLoad() {
    mTambourineParser = ObjectDir::sMainDir->Find<MidiParser>("tambourine", true);
    mTambourineParser->AddSink(this);
    ComputeTambourinePoints();
    mTambourineFader->DoFade(-96.0f, 0);
}

void TambourineManager::PostDynamicAdd() { Restart(); }

void TambourineManager::Start() { mTambourineActive = true; }

void TambourineManager::Restart() {
    unk4c = 0;
    mTambourineIdx = 0;
    unk60 = 0;
    unk68 = 0;
    mPlayerRef.PopupHelp(tambourine, false);
    unk48 = true;
    mGemStates.clear();
    mGemStates.resize(10);
    // mgem states resize
}

void TambourineManager::Jump(float) {
    unk4c = 0;
    mTambourineIdx = 0;
    unk60 = 0;
    unk68 = 0;
    mPlayerRef.PopupHelp(tambourine, false);
    unk48 = true;
}