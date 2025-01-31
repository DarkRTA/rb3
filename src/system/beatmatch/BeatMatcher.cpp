#include "beatmatch/BeatMatcher.h"
#include "beatmatch/BeatMaster.h"
#include "beatmatch/DrumPlayer.h"
#include "beatmatch/MercurySwitchFilter.h"
#include "beatmatch/Playback.h"
#include "obj/Data.h"

BeatMatcher::BeatMatcher(const UserGuid& u, int i1, int i2, Symbol s, SongData* data, SongInfo& info, DataArray* arr, BeatMaster* bm) :
    unk8(1), mUserGuid(u), unk1c(i1), unk20(i2), mControllerType(s), mSongData(data), mCfg(arr), unk34(0), mAudio(bm->GetMasterAudio()), unk3c(0), mMercurySwitchFilter(0), mWatcher(0),
    mDrumPlayer(new DrumPlayer(info)), unk5c(-1), unk60(1), unk78(0), unk7c(0), unk80(0), unk84(0), unk8c(0), unk90(0), unk94(0), unk95(0),
    unk98(0), unk9c(0), unka0(0x7fffffff), unka4(-1), unka8(-1), unkad(0), unkae(0), unkaf(0), unkb0(1), unkb8(1), unkb9(1) {
    mSongData->AddBeatMatcher(this);
    DataArray* filterArr = arr->FindArray("mercury_switch_filter", false);
    if(filterArr){
        mMercurySwitchFilter = NewMercurySwitchFilter(filterArr->Array(1));
    }
    TheBeatMatchPlayback.AddSink(this);
}

BeatMatcher::~BeatMatcher(){
    
}