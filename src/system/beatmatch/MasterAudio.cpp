#include "beatmatch/MasterAudio.h"
#include "synth/Synth.h"
#include "utl/SongInfoCopy.h"
#include "beatmatch/PlayerTrackConfig.h"
#include "beatmatch/BeatMaster.h"

namespace {
    int kMaxSlots = 8;
}

MasterAudio::MasterAudio(
    DataArray *da, int num_players, BeatMaster *master, SongData *data
)
    : mNumPlayers(num_players), mSongStream(0), mSongData(data), mStreamEnabled(0),
      mMasterFader(Hmx::Object::New<Fader>()),
      mForegroundFader(Hmx::Object::New<Fader>()),
      mMultiplayerFader(Hmx::Object::New<Fader>()),
      mBackgroundFader(Hmx::Object::New<Fader>()),
      mBackgroundAttenFader(Hmx::Object::New<Fader>()),
      mCommonFader(Hmx::Object::New<Fader>()), mRemoteFader(Hmx::Object::New<Fader>()),
      mPracticeFader(Hmx::Object::New<Fader>()),
      mVocalDuckFader(Hmx::Object::New<Fader>()),
      mVocalCueFader(Hmx::Object::New<Fader>()),
      mVocalFailFader(Hmx::Object::New<Fader>()), mCrowdFader(Hmx::Object::New<Fader>()),
      mBaseCrowdFader(Hmx::Object::New<Fader>()), mPlayingInCommon(0),
      mMuteVolume(-96.0f), mVocalMuteVolume(-96.0f), mUnplayedVolume(-96.0f),
      mCueVolume(-12.0f), mPracticeVolume(0), mRemoteVolume(0), mMuteMaster(0),
      mMuckWithPitch(1), mPitchMucker(0), mWhammyEnabled(1), mTimeOffset(0) {
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
    if (DataVariable("no_background_atten").Int(0))
        mBackgroundVolume = 0;

    float practice;
    if (da->FindData("practice_attenuation", practice, false))
        mPracticeVolume = -practice;
    float unplayed;
    if (da->FindData("unplayed_attenuation", unplayed, false))
        mUnplayedVolume = -unplayed;
    float cue;
    if (da->FindData("cue_attenuation", cue, false))
        mCueVolume = -cue;
    float remote;
    if (da->FindData("remote_attenuation", remote, false))
        mRemoteVolume = -remote;

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

MasterAudio::~MasterAudio() {
    for (std::vector<ChannelData *>::iterator it = mChannelData.begin();
         it != mChannelData.end();
         it++) {
        RELEASE(*it);
    }
    for (std::vector<TrackData *>::iterator it = mTrackData.mTrackData.begin();
         it != mTrackData.mTrackData.end();
         it++) {
        RELEASE(*it);
    }
    if (mSongStream) {
        for (int i = 0; i < 2; i++) {
            mSongStream->SetFX(i, false);
        }
    }
    RELEASE(mSongStream);

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

void MasterAudio::Load(SongInfo *info, PlayerTrackConfigList *player_track_config_list) {
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
    if (player_track_config_list->UseVocalHarmony()) {
        count = info->GetNumVocalParts();
    }

    for (int i = 1; i < count; i++) {
        mTrackData.mTrackData.push_back(new TrackData());
    }
}

bool MasterAudio::IsLoaded() {
    return mSongStream->IsReady();
}

void MasterAudio::SetupChannels(SongInfo *info) {
    info->GetTracks();
    const std::vector<float> &pans = info->GetPans();
    const std::vector<float> &vols = info->GetVols();
    const std::vector<int> &cores = info->GetCores();
    const std::vector<int> &crowd_channels = info->GetCrowdChannels();
    MILO_ASSERT(pans.size() == vols.size(), 0x1BE);
    MILO_ASSERT(cores.size() == vols.size(), 0x1BF);

    int i9 = 0;
    for (int i = 0; i < vols.size(); i++) {
        if (!info->IsPlayTrackChannel(i)) {
        }
        float voltouse = vols[i];
        if (voltouse < -40.0f) {
            i9++;
            if (3 < i9)
                voltouse = -40.0f;
        }
        mChannelData.push_back(
            new ChannelData(mSongStream, i, voltouse, (float)pans[i], (FXCore)cores[i])
        );
    }
}

void MasterAudio::ResetTrack(int i, bool b) {
    ResetTrack(mSongData->GetAudioTrackNum(i), b);
}

void MasterAudio::ResetTrack(AudioTrackNum num, bool b) {
    std::list<int> iList;
    mTrackData.mTrackData[num.mVal]->FillChannelList(iList);
    mTrackData.mTrackData[num.mVal]->Reset();
    SetAutoOn(num, 0);
    for (std::list<int>::iterator it = iList.begin(); it != iList.end(); it++) {
        int idx = *it;
        FaderGroup *grp = mSongStream->ChannelFaders(idx);
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
        if (b1 && b)
            b3 = true;
        float f2 = b3 ? mCueVolume : 0;
        if (b)
            SetupTrackChannel(idx, b1, f2, b3, false);
        else
            SetupBackgroundChannel(idx, b1, f2, b3, false);
    }
}

void MasterAudio::ConfigureVocalFaders(int i, bool b) {
    FaderGroup *grp = mSongStream->ChannelFaders(i);
    if (b)
        grp->Add(mVocalDuckFader);
    else
        grp->Add(mVocalFailFader);
}

void MasterAudio::FadeOutDrums(int trackNum) {
    // this is very close to being right not quite, can't figure out what is wrong
    /*    AudioTrackNum audioTrackNum = mSongData->GetAudioTrackNum(trackNum);
        mTrackData.mTrackData[audioTrackNum.mVal]->mInFill = 1;
        Symbol drum_fill = Symbol("drum_fill");
        SetTrackFader(audioTrackNum, -1, drum_fill, -96.0f, 1000.0f);
        */
}

bool MasterAudio::Fail() {
    if (mSongStream)
        return mSongStream->Fail();
    else
        return true;
}

float MasterAudio::GetTime() const {
    float time;
    if (mSongStream != 0) {
        time = mSongStream->GetTime();
    } else {
        time = 0.0f;
    }
    return time + mTimeOffset;
}

bool MasterAudio::IsReady() {
    bool b = false;
    if (mSongStream && mSongStream->IsReady())
        b = true;
    mStreamEnabled = b;
    return b;
}

bool MasterAudio::IsFinished() const {
    bool b = false;
    if (mSongStream && mSongStream->IsFinished())
        b = true;
    return b;
}

void MasterAudio::SetBackgroundVolume(float volume) {
    mBackgroundFader->SetVal(volume);
}

void MasterAudio::SetForegroundVolume(float volume) {
    mForegroundFader->SetVal(volume);
}

void MasterAudio::SetFX(int channel, FXCore core, bool enabled) {
    if (mTrackData.mTrackData.size() != 0) {
        AudioTrackNum trackNum = mSongData->GetAudioTrackNum(channel);
        SetFX(trackNum, core, enabled);
    }
    return;
}

void MasterAudio::SetFX(AudioTrackNum trackNum, FXCore core, bool enabled) {
    if (core == -1) {
        MILO_ASSERT(core != kFXCoreNone, 0x406);
    }

    std::list<int> iList;
    mTrackData.mTrackData[trackNum.mVal]->FillChannelList(iList, -1);
    for (std::list<int>::iterator it = iList.begin(); it != iList.end(); it++) {
        mChannelData[*it]->SetFX(core, enabled);
    }
}

void MasterAudio::SetMasterVolume(float volume) {
    mMasterVolume = volume;
    UpdateMasterFader();
}

void MasterAudio::SetMuckWithPitch(bool enabled) {
    mMuckWithPitch = enabled;
}

void MasterAudio::SetMuteMaster(bool muted) {
    mMuteMaster = muted;
    UpdateMasterFader();
}

void MasterAudio::SetPracticeMode(bool enabled) {
    mPracticeFader->SetVal(enabled ? mPracticeVolume : 0.0f);
}

void MasterAudio::SetStereo(bool b) {
    for (int i = 0; i < mChannelData.size(); i++) {
        mChannelData[i]->SetStereo(b);
    }
}

void MasterAudio::SetTimeOffset(float offset) {
    mTimeOffset = offset;
}

void MasterAudio::SetVocalFailFader(float fader) {
    mVocalFailFader->DoFade(fader, 0.0f);
}

void MasterAudio::SetVocalState(bool state) {
    float fader;
    if (state != 0) {
        fader = 0.0f;
    } else {
        fader = mVocalMuteVolume;
    }
    SetVocalFailFader(fader);
}

void MasterAudio::ToggleMuteMaster() {
    bool b = mMuteMaster;
    SetMuteMaster(!b);
    return;
}

void MasterAudio::UnmuteAllTracks() {
    for (int i = 0; i < mTrackData.mTrackData.size(); i++) {
        AudioTrackNum num;
        num.mVal = i;
        UnmuteTrack(num, -1);
    }
}

void MasterAudio::UnmuteTrack(AudioTrackNum trackNum, int i) {
    SetTrackMuteFader(trackNum, i, 0.0f, 0.0f);
}

void MasterAudio::UpdateMasterFader() {
    float masterVolume;
    if (mMuteMaster != 0) {
        masterVolume = -96.0f;
    } else {
        masterVolume = mMasterVolume;
    }
    mMasterFader->SetVal(masterVolume);
    return;
}

void MasterAudio::Play() {
    MILO_ASSERT(mSongStream, 0x334);
    mSongStream->Play();
    for (int i = 0; i < mChannelData.size(); i++) {
        mChannelData[i]->ForceOn();
    }
}

void MasterAudio::Jump(float f) {
    mSongStream->Stop();
    mStreamEnabled = false;
    mSongStream->Resync(f);
    UnmuteAllTracks();
    for (int i = 0; i < mTrackData.mTrackData.size(); i++) {
        mTrackData.mTrackData[i]->Reset();
        AudioTrackNum num;
        num.mVal = i;
        ResetSlipTrack(num, true);
    }
}

ChannelData::ChannelData(Stream *stream, int chan, float vol, float pan, FXCore core)
    : mStream(stream), mChannel(chan), mSlipTrack(0), mIsTrackChannel(0), mPan(pan),
      mOriginalPan(pan), mCore(core), mOverallSpeed(1.0f), mSpeed(1.0f), mDirty(0),
      mVolume(vol) {
    mBaseFader = stream->ChannelFaders(chan)->AddLocal("base");
    mBaseFader->SetVal(vol);
    stream->SetPan(chan, mPan);
    stream->SetFXCore(chan, mCore);
}

ChannelData::~ChannelData() {
    RELEASE(mSlipTrack);
}

void ChannelData::SetSlippable(bool b) {
    if (b) {
        if (!mSlipTrack) {
            mSlipTrack = new SlipTrack(mStream, mChannel);
        }
    } else if (mSlipTrack)
        RELEASE(mSlipTrack);
}

void ChannelData::ForceOn() {
    if (mSlipTrack)
        mSlipTrack->ForceOn();
}

void ChannelData::Reset(bool b) {
    if (mOverallSpeed != 1.0f || mDirty || b) {
        mSlipTrack->SetOffset(0);
        SetSlipTrackSpeed(1.0f);
        mDirty = false;
    }
}

void ChannelData::Poll() {
    if (mSlipTrack)
        mSlipTrack->Poll();
}

void ChannelData::SetSlipTrackSpeed(float trackSpeed) {
    if (mSlipTrack) {
        if (std::fabs(mSlipTrack->GetCurrentOffset()) > mSlipTrack->mMaxSlip * 0.9f) {
            trackSpeed = 1.0f;
        }
        if (mSpeed != trackSpeed || mOverallSpeed != 1.0f) {
            mSlipTrack->SetSpeed(trackSpeed * mOverallSpeed);
            mSpeed = trackSpeed;
            mDirty = true;
        }
    }
}

void ChannelData::SetFX(FXCore core, bool b) {
    if (mCore == core) {
        mStream->SetFX(mChannel, b);
    }
}

void ChannelData::SetStereo(bool enabled) {
    mStream->SetPan(mChannel, enabled ? mPan : 0);
}

void ChannelData::SetFaderVal(float val) {
    mBaseFader->SetVal(val);
}

void ChannelData::SetPan(float pan) {
    mPan = pan;
    mStream->SetPan(mChannel, mPan);
}

TrackData::TrackData() {
    Init(0, false);
}

TrackData::TrackData(
    SubmixCollection *submixes, const std::vector<int> &vec, bool b1, bool b2
) {
    Init(submixes, b1);
    SetMapping(vec);
    mVocals = b2;
}

void TrackData::FillChannelList(std::list<int> &list) const {
    if (mChannelMapping == 0) {
        return;
    }
    mChannelMapping->FillChannelList(list);
}

void TrackData::FillChannelList(std::list<int> &list, int i) const {
    if (mMultiSlot == 0) {
        return;
    }
    mChannelMapping->FillChannelList(list, i);
}

int TrackData::GetSucceeding(int slot) const {
    int ret;
    if (mMultiSlot) {
        if (slot == -1) {
            MILO_ASSERT(slot != -1, 0x698);
        }
        ret = mSucceedingVec[slot];
    } else {
        ret = mSucceeding;
    }
    return ret;
}

void TrackData::Hit(int gemID, int i, float f) {
    SetSucceeding(true, i, f);
    mLastPlayedGem = gemID;
}

bool TrackData::IsSlotActive(int i, float f) const {
    if (mMultiSlot) {
        return (f - mLastGemTimes[i] < 5000.0f);
    }
    return true;
}

void TrackData::Miss(int i, float f) {
    SetSucceeding(false, i, f);
}

void TrackData::Reset() {
    SetSucceeding(true, -1, -10000.0f);
    mInFill = 0;
}

void TrackData::SetButtonMashingMode(bool enabled, float lastMashTime) {
    mButtonMashingMode = enabled;
    mLastMashTime = lastMashTime;
}

void TrackData::SetLastMashTime(float lastMashTime) {
    mLastMashTime = lastMashTime;
}

void TrackData::SetNonmutable(bool nonmutable) {
    mNonmutable = nonmutable;
}

void TrackData::SetSucceeding(bool succeeding, int gemId, float lastGemTime) {
    if (mMultiSlot != 0) {
        if (gemId == -1) {
            int var = 0;
            for (int j = 0; j < mSucceedingVec.size(); j++) {
                mSucceedingVec[j] = succeeding;
                mLastGemTimes[var] = lastGemTime;
                var++;
            }
            return;
        }
        mSucceedingVec[gemId] = succeeding;
        mLastGemTimes[gemId] = lastGemTime;
    } else {
        mSucceeding = succeeding;
        return;
    }
}

void TrackData::SetUserGuid(const UserGuid &guid) {
    mUserGuid = guid;
}

void TrackData::Init(SubmixCollection *submixes, bool b) {
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
