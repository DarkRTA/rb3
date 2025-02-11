#include "game/BandPerformer.h"
#include "os/System.h"

BandPerformer::BandPerformer(Band *band, BandUser *user)
    : Performer(user, band), unk20c(SystemConfig("scoring", "crowd", "weights")) {
    mCrowd->SetLoseLevel(
        SystemConfig("scoring", "crowd")->FindFloat("multiplayer_lose_level")
    );
    ComputeScoreData();
}

BandPerformer::~BandPerformer() {}