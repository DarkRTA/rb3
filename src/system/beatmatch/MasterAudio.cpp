#include "beatmatch/MasterAudio.h"

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