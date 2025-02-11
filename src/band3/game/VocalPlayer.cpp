#include "game/VocalPlayer.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "obj/Data.h"
#include "os/Joypad.h"
#include "os/System.h"
#include "rndobj/Overlay.h"

VocalPlayer::VocalPlayer(
    BandUser *user, BeatMaster *bmaster, Band *band, int tracknum, Performer *perf, int i7
)
    : Player(user, band, tracknum, bmaster), unk2cc(perf), unk2d0(0), unk2d4(0),
      unk2d8(0), unk2dc(1.25f), unk2e8(0), unk2ec(0), unk2f0(0), unk300(0), unk304(0),
      unk308(0), unk328(-1), unk32c(0), unk330(0), unk334(0), unk338(0.6f), unk33c(0),
      unk340(0), unk344(0), mTuningOffset(0), unk34c(-1.0f), unk368(0), unk36c(0),
      unk370(0), unk374(0), unk378(0), unk37c(0), mOverlay(0), unk384(0), unk388(1),
      mTambourineManager(*this), unk414(0), unk418(0), unk41c(0), unk420(0), unk424(0) {
    BandSongMetadata *data = (BandSongMetadata *)TheSongMgr->Data(
        TheSongMgr->GetSongIDFromShortName(MetaPerformer::Current()->Song(), true)
    );
    mTuningOffset = data->TuningOffset() / 100.0f;
    for (int i = 0; i < i7; i++) {
        mSingers.push_back(new Singer(this, i));
    }
    SetTypeDef(SystemConfig("player", "handlers"));
    SetDifficultyVariables(mUser->GetDifficulty());
    DataArray *cfg = SystemConfig("scoring", "vocals");
    unk308 = cfg->FindFloat("track_wrapping_margin");
    unk320 = cfg->FindArray("freestyle_deployment_time", true)->Array(1);
    unk324 = cfg->FindArray("freestyle_min_duration", true)->Array(1);
    unk2f4 = cfg->FindFloat("max_detune");
    unk2f8 = cfg->FindFloat("packet_period");
    unk330 = cfg->FindArray("part_score_multiplier", true);
    unk334 = cfg->FindArray("rating_thresholds", true);
    unk338 = cfg->FindFloat("nonpitch_stickiness");
    JoypadSubscribe(this);

    RememberCurrentMics();
    mOverlay = RndOverlay::Find("vocalplayer", true);
    mOverlay->SetCallback(this);
}

VocalPlayer::~VocalPlayer() {}