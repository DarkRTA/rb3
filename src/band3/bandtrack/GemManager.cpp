#include "bandtrack/GemManager.h"
#include "bandobj/ArpeggioShape.h"
#include "bandtrack/NowBar.h"
#include "bandtrack/Track.h"
#include "beatmatch/RGUtl.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "obj/DataFunc.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Symbols4.h"

int sBeardThreshold = 480;

int GetBeardThreshold() { return sBeardThreshold; }

DataNode SetKeyGlow(DataArray *arr) {
    sBeardThreshold = arr->Int(1);
    return 0;
}

GemManager::GemManager(const TrackConfig &cfg, TrackDir *dir)
    : mTrackDir(dir), mTrackConfig(cfg), mTemplate(cfg),
      mConfig(SystemConfig("track_graphics")), mGemData(0), unk14(0), mBegin(0), mEnd(0),
      unkb8(0), mNowBar(0), unkc0(0), mInCoda(0), unkc4(0),
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
    mGems.clear();
}

void GemManager::InitRGTuning(BandUser *bandUser) {
    MILO_ASSERT(bandUser, 0xAE);
    bool isRG = bandUser->GetTrack()->GetType() == real_guitar;
    bool isRB = bandUser->GetTrack()->GetType() == real_bass;
    if (isRG || isRB) {
        BandSongMetadata *metadata = (BandSongMetadata *)TheSongMgr->Data(
            TheSongMgr->GetSongIDFromShortName(MetaPerformer::Current()->Song(), true)
        );
        std::vector<int> vec18;
        if (isRG) {
            vec18.reserve(6);
            for (int i = 0; i < 6; i++) {
                vec18.push_back(metadata->RealGuitarTuning(i));
            }
        } else {
            vec18.reserve(4);
            for (int i = 0; i < 4; i++) {
                vec18.push_back(metadata->RealBassTuning(i));
            }
        }
        RGSetTuning(vec18);
    }
}

void GemManager::ClearArpeggios() {
    ArpeggioShapePool *pool = mTrackDir->GetArpeggioShapePool();
    while (!mActiveArpeggios.empty()) {
        pool->ReleaseArpeggioShape(mActiveArpeggios.back()->unkc);
        mActiveArpeggios.pop_back();
    }
    while (!mExpiredArpeggios.empty()) {
        pool->ReleaseArpeggioShape(mExpiredArpeggios.back()->unkc);
        mExpiredArpeggios.pop_back();
    }
}