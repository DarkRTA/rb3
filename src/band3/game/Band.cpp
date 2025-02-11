#include "game/Band.h"
#include "BandPerformer.h"
#include "bandobj/BandDirector.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/CommonPhraseCapturer.h"
#include "game/GameConfig.h"
#include "meta_band/MetaPerformer.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/System.h"

Band::Band(bool bbb, int i2, BandUser *user, BeatMaster *bm)
    : mBandPerformer(0), unk30(0), unk34(0), unk38(0), unk3c(0), unk40(0), unk44(0),
      unk48(0), unk4c(1), unk50(1), unk54(0), unk58(0), unk5c(1), unk60(0) {
    DataArray *cfg = SystemConfig("scoring", "bonuses");
    unk64 = cfg->FindInt("max_bonus");
    DataArray *multArr = cfg->FindArray("multiplier", true)->Array(1);
    for (int i = 0; i < multArr->Size(); i++) {
        unk68.push_back(multArr->Int(i));
    }
    DataArray *crowdArr = cfg->FindArray("crowd_boost", true)->Array(1);
    for (int i = 0; i < crowdArr->Size(); i++) {
        unk70.push_back(crowdArr->Int(i));
    }
    SetName(MakeString("band_%i", i2), ObjectDir::sMainDir);
    mBandPerformer = new BandPerformer(this, nullptr);
    mCommonPhraseCapturer = new CommonPhraseCapturer();
    MetaPerformer *perf = MetaPerformer::Current();
    std::vector<BandUser *> users;
    TheBandUserMgr->GetParticipatingBandUsers(users);
    FOREACH (it, users) {
        BandUser *pUser = *it;
        MILO_ASSERT(pUser, 0x57);
        bool b1 = false;
        if (perf && !perf->PartPlaysInSong(pUser->GetTrackSym())) {
            b1 = true;
        }
        if (!b1 && (!bbb || pUser == user)) {
            AddPlayer(bm, pUser);
        }
    }
    if (TheGameConfig->GetConfigList()->GetAutoVocals()) {
        Player *p = AddPlayer(bm, TheBandUserMgr->GetNullUser());
        p->SetQuarantined(true);
    }
}

Band::~Band() {
    if (unk60 == 1)
        TheBandDirector->SetCharacterHideHackEnabled(false);
    unk60 = 0;
}