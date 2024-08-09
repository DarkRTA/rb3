#include "beatmatch/MasterAudio.h"
#include "synth/Synth.h"
#include "utl/SongInfoCopy.h"
#include "beatmatch/PlayerTrackConfig.h"

namespace {
    int kMaxSlots = 8;
}

MasterAudio::MasterAudio(DataArray* da, int num_players, BeatMaster* master, SongData* data) : mNumPlayers(num_players), mSongStream(0), mSongData(data), mStreamEnabled(0),
    mMasterFader(Hmx::Object::New<Fader>()), mForegroundFader(Hmx::Object::New<Fader>()), mMultiplayerFader(Hmx::Object::New<Fader>()),
    mBackgroundFader(Hmx::Object::New<Fader>()), mBackgroundAttenFader(Hmx::Object::New<Fader>()), mCommonFader(Hmx::Object::New<Fader>()),
    mRemoteFader(Hmx::Object::New<Fader>()), mPracticeFader(Hmx::Object::New<Fader>()), mVocalDuckFader(Hmx::Object::New<Fader>()),
    mVocalCueFader(Hmx::Object::New<Fader>()), mVocalFailFader(Hmx::Object::New<Fader>()), mCrowdFader(Hmx::Object::New<Fader>()), mBaseCrowdFader(Hmx::Object::New<Fader>()),
    mPlayingInCommon(0), mMuteVolume(-96.0f), mVocalMuteVolume(-96.0f), mUnplayedVolume(-96.0f), mCueVolume(-12.0f), mPracticeVolume(0), mRemoteVolume(0), mMuteMaster(0), mMuckWithPitch(1),
    mPitchMucker(0), mWhammyEnabled(1), mTimeOffset(0) {
    mMasterFader->SetName("MasterFader", ObjectDir::Main());
    mForegroundFader->SetName("ForegroundFader", ObjectDir::Main());
    mMultiplayerFader->SetName("MultiplayerFader", ObjectDir::Main());
    mCommonFader->SetName("CommonFader", ObjectDir::Main());
    mBackgroundFader->SetName("BackgroundFader", ObjectDir::Main());
    mBackgroundAttenFader->SetName("BackgroundAttenFader", ObjectDir::Main());
    mRemoteFader->SetName("RemoteFader", ObjectDir::Main());
    mPracticeFader->SetName("PracticeFader", ObjectDir::Main());
    mVocalDuckFader->SetName("VocalDuckFader", ObjectDir::Main());
    mVocalCueFader->SetName("VocalCueFader", ObjectDir::Main());
    mVocalFailFader->SetName("VocalFailFader", ObjectDir::Main());
    mCrowdFader->SetName("CrowdFader", ObjectDir::Main());
    mBaseCrowdFader->SetName("BaseCrowdFader", ObjectDir::Main());
    SetName("audio", ObjectDir::Main());
    master->RegisterSink(*this);
    mMultiplayerStereoScale = da->FindFloat("multiplayer_scale");

    float mult_atten = da->FindFloat("multiplayer_attenuation");
    mPlayerAtten = num_players > 1 ? -mult_atten : 0;

    mMultiplayerCommonVolume = -da->FindFloat("multiplayer_common_attenuation");
    mBackgroundVolume = -da->FindFloat("background_attenuation");
    if(DataVariable("no_background_atten").Int(0)) mBackgroundVolume = 0;

    float practice;
    if(da->FindData("practice_attenuation", practice, false)) mPracticeVolume = -practice;
    float unplayed;
    if(da->FindData("unplayed_attenuation", unplayed, false)) mUnplayedVolume = -unplayed;
    float cue;
    if(da->FindData("cue_attenuation", cue, false)) mCueVolume = -cue;
    float remote;
    if(da->FindData("remote_attenuation", remote, false)) mRemoteVolume = -remote;

    da->FindData("mute_volume", mMuteVolume, false);
    mPassVolume = mMuteVolume;
    da->FindData("mute_volume_vocals", mVocalMuteVolume, false);
    da->FindData("pass_volume", mPassVolume, false);
    da->FindData("whammy_enabled", mWhammyEnabled, false);

    mSubmixes = new SubmixCollection(da->FindArray("submixes", false));
    mCrowdFader->SetVal(-96.0f);
    mBaseCrowdFader->SetVal(0);
    mPitchMucker = new PitchMucker();
}

MasterAudio::~MasterAudio(){
    for(std::vector<ChannelData*>::iterator it = mChannelData.begin(); it != mChannelData.end(); it++){
        RELEASE(*it);
    }
    for(std::vector<TrackData*>::iterator it = mTrackData.mTrackData.begin(); it != mTrackData.mTrackData.end(); it++){
        RELEASE(*it);
    }
    RELEASE(mBackgroundFader);
    RELEASE(mBackgroundAttenFader);
    RELEASE(mMasterFader);
    RELEASE(mForegroundFader);
    RELEASE(mMultiplayerFader);
    RELEASE(mCommonFader);
    RELEASE(mRemoteFader);
    RELEASE(mPracticeFader);
    RELEASE(mVocalDuckFader);
    RELEASE(mVocalCueFader);
    RELEASE(mVocalFailFader);
    RELEASE(mCrowdFader);
    RELEASE(mBaseCrowdFader);
    RELEASE(mSubmixes);
    RELEASE(mPitchMucker);
}

void MasterAudio::Load(SongInfo* info, PlayerTrackConfigList* player_track_config_list){
    MILO_ASSERT(mSongData, 0x186);
    MILO_ASSERT(player_track_config_list, 0x187);
    mSongStream = TheSynth->NewStream(info->GetBaseFileName(), 0, 0, false);
    int count = 1;
    mStreamEnabled = true;
    mSongStream->Faders()->Add(mMasterFader);
    float vol = info->GetMuteVolume();
    mPassVolume = mMuteVolume = vol;
    mVocalMuteVolume = info->GetVocalMuteVolume();

    info->GetTracks(); // why tho

    SetupChannels(info);
    SetupTracks(info, player_track_config_list);
    if(player_track_config_list->UseVocalHarmony()){
        count = info->GetNumVocalParts();
    }

    for(int i = 1; i < count; i++){
        mTrackData.mTrackData.push_back(new TrackData());
    }
}

bool MasterAudio::IsLoaded(){
    return mSongStream->IsReady();
}

void MasterAudio::SetupChannels(SongInfo* info){
    info->GetTracks();
    const std::vector<float>& pans = info->GetPans();
    const std::vector<float>& vols = info->GetVols();
    const std::vector<int>& cores = info->GetCores();
    const std::vector<int>& crowd_channels = info->GetCrowdChannels();
    MILO_ASSERT(pans.size() == vols.size(), 0x1BE);
    MILO_ASSERT(cores.size() == vols.size(), 0x1BF);
    
    int i9 = 0;
    for(int i = 0; i < vols.size(); i++){
        if(!info->IsPlayTrackChannel(i)){

        }
        float voltouse = vols[i];
        if(voltouse < -40.0f){
            i9++;
            if(3 < i9) voltouse = -40.0f;
        }
        mChannelData.push_back(new ChannelData(mSongStream, i, voltouse, (float)pans[i], (FXCore)cores[i]));
    }
}

void MasterAudio::ResetTrack(int i, bool b){
    ResetTrack(mSongData->GetAudioTrackNum(i), b);
}

void MasterAudio::ResetTrack(AudioTrackNum num, bool b){
    std::list<int> iList;
    mTrackData.mTrackData[num.mVal]->FillChannelList(iList);
    mTrackData.mTrackData[num.mVal]->Reset();
    SetAutoOn(num, 0);
    for(std::list<int>::iterator it = iList.begin(); it != iList.end(); it++){
        int idx = *it;
        FaderGroup* grp = mSongStream->ChannelFaders(idx);
        grp->Remove(mBackgroundAttenFader);
        grp->Remove(mBackgroundFader);
        grp->Remove(mCommonFader);
        grp->Remove(mForegroundFader);
        grp->Remove(mMultiplayerFader);
        grp->Remove(mPracticeFader);
        grp->Remove(mRemoteFader);
        grp->Remove(mVocalCueFader);

        bool b3 = false;
        bool b1 = mTrackData.mTrackData[num.mVal]->mVocals;
        if(b1 && b) b3 = true;
        float f2 = b3 ? mCueVolume : 0;
        if(b) SetupTrackChannel(idx, b1, f2, b3, false);
        else SetupBackgroundChannel(idx, b1, f2, b3, false);
    }
}

void MasterAudio::ConfigureVocalFaders(int i, bool b){
    FaderGroup* grp = mSongStream->ChannelFaders(i);
    if(b) grp->Add(mVocalDuckFader);
    else grp->Add(mVocalFailFader);
}

bool MasterAudio::Fail(){
    if(mSongStream) return mSongStream->Fail();
    else return true;
}

bool MasterAudio::IsReady(){
    bool b = false;
    if(mSongStream && mSongStream->IsReady()) b = true;
    mStreamEnabled = b;
    return b;
}

bool MasterAudio::IsFinished() const {
    bool b = false;
    if(mSongStream && mSongStream->IsFinished()) b = true;
    return b;
}

void MasterAudio::Play(){
    MILO_ASSERT(mSongStream, 0x334);
    mSongStream->Play();
    for(int i = 0; i < mChannelData.size(); i++){
        mChannelData[i]->ForceOn();
    }
}

void MasterAudio::Jump(float f){
    mSongStream->Stop();
    mStreamEnabled = false;
    mSongStream->Resync(f);
    UnmuteAllTracks();
    for(int i = 0; i < mTrackData.mTrackData.size(); i++){
        mTrackData.mTrackData[i]->Reset();
        AudioTrackNum num;
        num.mVal = i;
        ResetSlipTrack(num, true);
    }
}

ChannelData::ChannelData(Stream* stream, int chan, float vol, float pan, FXCore core) : mStream(stream), mChannel(chan), mSlipTrack(0), mIsTrackChannel(0),
    mPan(pan), mOriginalPan(pan), mCore(core), mOverallSpeed(1.0f), mSpeed(1.0f), mDirty(0), mVolume(vol) {
    mBaseFader = stream->ChannelFaders(chan)->AddLocal("base");
    mBaseFader->SetVal(vol);
    stream->SetPan(chan, mPan);
    stream->SetFXCore(chan, mCore);
}

ChannelData::~ChannelData(){
    RELEASE(mSlipTrack);
}

void ChannelData::SetSlippable(bool b){
    if(b){
        if(!mSlipTrack){
            mSlipTrack = new SlipTrack(mStream, mChannel);
        }
    }
    else if(mSlipTrack) RELEASE(mSlipTrack);
}

void ChannelData::ForceOn(){
    if(mSlipTrack) mSlipTrack->ForceOn();
}

void ChannelData::Reset(bool b){
    if(mOverallSpeed != 1.0f || mDirty || b){
        mSlipTrack->SetOffset(0);
        SetSlipTrackSpeed(1.0f);
        mDirty = false;
    }
}

void ChannelData::Poll(){
    if(mSlipTrack) mSlipTrack->Poll();
}

void ChannelData::SetSlipTrackSpeed(float f){
    if(mSlipTrack){
        if(mSlipTrack->mMaxSlip * 0.9f < __fabs(mSlipTrack->GetCurrentOffset())){
            f = 1.0f;
        }
        if(mSpeed != f || mOverallSpeed != 1.0f){
            mSlipTrack->SetSpeed(f * mOverallSpeed);
            mSpeed = f;
            mDirty = true;
        }
    }
}

void ChannelData::SetFX(FXCore core, bool b){
    if(mCore == core){
        mStream->SetFX(mChannel, b);
    }
}

void ChannelData::SetStereo(bool b){
    mStream->SetPan(mChannel, b ? mPan : 0);
}

void ChannelData::SetFaderVal(float val){
    mBaseFader->SetVal(val);
}

void ChannelData::SetPan(float pan){
    mPan = pan;
    mStream->SetPan(mChannel, mPan);
}

TrackData::TrackData(){
    Init(0, false);
}

TrackData::TrackData(SubmixCollection* submixes, const std::vector<int>& vec, bool b1, bool b2){
    Init(submixes, b1);
    SetMapping(vec);
    mVocals = b2;
}

void TrackData::Init(SubmixCollection* submixes, bool b){
    mSubmixes = submixes;
    mMultiSlot = false;
    mSucceeding = false;
    mSucceedingVec.reserve(kMaxSlots);
    mLastGemTimes.reserve(kMaxSlots);
    SetSucceeding(true, -1, -10000.0f);
    mLastPlayedGem = -1;
    mChannelMapping = 0;
    mIndieSlots = false;
    mOriginalChannels.clear();
    mNonmutable = false;
    mButtonMashingMode = false;
    mInFill = false;
    mAutoOn = false;
    mVocals = false;
    unk48 = 99.0f;
    mUserGuid.Clear();
}