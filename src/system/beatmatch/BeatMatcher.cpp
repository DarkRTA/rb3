#include "beatmatch/BeatMatcher.h"
#include "beatmatch/BeatMaster.h"
#include "beatmatch/DrumPlayer.h"
#include "beatmatch/MercurySwitchFilter.h"
#include "beatmatch/Output.h"
#include "beatmatch/Playback.h"
#include "obj/Data.h"

BeatMatcher::BeatMatcher(const UserGuid& u, int i1, int i2, Symbol s, SongData* data, SongInfo& info, DataArray* arr, BeatMaster* bm) :
    mWaitingForAudio(1), mUserGuid(u), unk1c(i1), unk20(i2), mControllerType(s), mSongData(data), mCfg(arr), mSink(0), mAudio(bm->GetMasterAudio()), unk3c(0), mMercurySwitchFilter(0), mWatcher(0),
    mDrumPlayer(new DrumPlayer(info)), mCurTrack(-1), unk60(1), mNow(0), unk7c(0), unk80(0), unk84(0), unk8c(0), unk90(0), unk94(0), unk95(0),
    unk98(0), unk9c(0), unka0(0x7fffffff), unka4(-1), unka8(-1), unkad(0), unkae(0), unkaf(0), unkb0(1), unkb8(1), unkb9(1) {
    mSongData->AddBeatMatcher(this);
    DataArray* filterArr = arr->FindArray("mercury_switch_filter", false);
    if(filterArr){
        mMercurySwitchFilter = NewMercurySwitchFilter(filterArr->Array(1));
    }
    TheBeatMatchPlayback.AddSink(this);
}

void BeatMatcher::PostDynamicAdd(int i, float f){
    mSongData->PostDynamicAdd(this, i);
    SetTrack(i);
    mAudio->ResetTrack(mCurTrack, true);
    ResetGemStates(f);
}

void BeatMatcher::Leave(){
    mAudio->ResetTrack(mCurTrack, false);
}

BeatMatcher::~BeatMatcher(){
    mSongData->RemoveBeatMatcher(this);
    delete mWatcher;
    delete mMercurySwitchFilter;
    delete mDrumPlayer;
}

void BeatMatcher::PostLoad(){}

bool BeatMatcher::IsReady(){
    if(mWaitingForAudio){
        if(mAudio->Fail() || mAudio->IsReady()) mWaitingForAudio = false;
    }
    return !mWaitingForAudio;
}

void BeatMatcher::Start(){
    if(TheBeatMatchOutput.IsActive()){
        TheBeatMatchOutput.Print(MakeString("(%2d%10.1f TRACK\t%d)\n", TheBeatMatchPlayback.GetPlaybackNum(this), mNow, mCurTrack));
    }
}

void BeatMatcher::AddTrack(int, Symbol, SongInfoAudioType, TrackType t, bool){
    mTrackTypes.push_back(t);
    unk50.push_back(0);
}

void BeatMatcher::RegisterSink(BeatMatchSink& sink){
    mSink = &sink;
}