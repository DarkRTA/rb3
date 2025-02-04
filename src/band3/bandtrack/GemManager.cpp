#include "bandtrack/GemManager.h"
#include "bandtrack/NowBar.h"
#include "obj/DataFunc.h"
#include "os/System.h"

int sBeardThreshold = 480;

int GetBeardThreshold() { return sBeardThreshold; }

DataNode SetKeyGlow(DataArray *arr) {
    sBeardThreshold = arr->Int(1);
    return 0;
}

GemManager::GemManager(const TrackConfig &cfg, TrackDir *dir)
    : mTrackDir(dir), mTrackConfig(cfg), mTemplate(cfg),
      mConfig(SystemConfig("track_graphics")), unk10(0), unk14(0), unk28(0), unk2c(0),
      unkb8(0), mNowBar(0), unkc0(0), unkc1(0), unkc4(0),
      unkc8(dir->SecondsToY(dir->TopSeconds())),
      unkcc(dir->SecondsToY(dir->BottomSeconds())), unkf8(0), unkfc(0), unk100(0),
      unk104(0), unk108(0), unk10c(0), unk118(0), unk12c(0), unk130(-1), unk134(960) {
    mNowBar = new NowBar(mTrackDir, mTrackConfig);
    mTemplate.Init(mTrackDir->Find<ObjectDir>("gem_tail", true));
    static bool firstPass = true;
    if (firstPass) {
        sBeardThreshold =
            SystemConfig("track_graphics")->FindInt("key_glow_threshold_ticks");
        firstPass = false;
    }
    unk134 = SystemConfig("track_graphics")->FindInt("rg_run_space_ticks");
    SetupGems(0);
    UpdateLeftyFlip(false);
    DataRegisterFunc("set_key_glow", SetKeyGlow);
    unk12c = mTrackDir->Find<RndDir>("chord_shape_outline", true)->mLocalXfm.v.y + 0.01f;
    unkd8.reserve(10);
}

GemManager::~GemManager() {
    RELEASE(mNowBar);
    ClearArpeggios();
    unk8.clear();
}