#include "beatmatch/MasterAudio.h"
#include "beatmatch/GameGem.h"
#include "beatmatch/InternalSongParserSink.h"
#include "beatmatch/SlotChannelMapping.h"
#include "beatmatch/TrackType.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "synth/Faders.h"
#include "synth/Synth.h"
#include "utl/SongInfoAudioType.h"
#include "utl/SongInfoCopy.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"
#include "utl/TextStream.h"
#include "utl/TimeConversion.h"
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
    if (DataVariable("no_background_atten").Int())
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
    mMuteVolume = vol;
    mPassVolume = mMuteVolume;
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
            FaderGroup* curGrp = mSongStream->ChannelFaders(i);
            if(std::find(cores.begin(), cores.end(), i) != cores.end()){
                curGrp->Add(mBaseCrowdFader);
                curGrp->Add(mCrowdFader);
                curGrp->Add(mPracticeFader);
            }
            else {
                curGrp->Add(mBackgroundFader);
                curGrp->Add(mBackgroundAttenFader);
                curGrp->Add(mPracticeFader);
            }
        }
        float voltouse = vols[i];
        if (voltouse < -40.0) {
            i9++;
            if (3 < i9)
                voltouse = -40.0;
        }
        mChannelData.push_back(
            new ChannelData(mSongStream, i, voltouse, (float)pans[i], (FXCore)cores[i])
        );
    }
}


typedef void (MasterAudio::*ChannelSetupFunc)(int, MasterAudio::ExtraTrackInfo&);

void MasterAudio::SetupTracks(SongInfo* info, PlayerTrackConfigList* pList){
    const std::vector<TrackChannels>& chans = info->GetTracks();
    for(int i = 0; i < chans.size(); i++){
        SongInfoAudioType curAudioType = chans[i].mAudioType;
        const std::vector<int>& curChannels = chans[i].mChannels;
        if(!curChannels.empty()){
            ExtraTrackInfo extraInfo;
            GetExtraTrackInfo(pList, curAudioType, extraInfo);
            mTrackData.mTrackData.push_back(new TrackData(mSubmixes, curChannels, mSongData->TrackHasIndependentSlots(i), extraInfo.unka));

            ChannelSetupFunc func = extraInfo.unk0 ? &MasterAudio::SetupTrackChannel_ : &MasterAudio::SetupBackgroundChannel_;
            for(int j = 0; j < curChannels.size(); j++){
                // (func)(curChannels[j], info);
            }
            if(extraInfo.unka){
                SetNonmutable(AudioTrackNum(i));
            }
        }
    }
    if(pList->UseVocalHarmony()){
        int numVoxParts = info->GetNumVocalParts();
        for(int i = 1; i < numVoxParts; i++){
            mTrackData.mTrackData.push_back(new TrackData());
        }
    }
}

void MasterAudio::FillChannelList(std::list<int>& chans, int i){
    mTrackData.mTrackData[mSongData->GetAudioTrackNum(i).mVal]->FillChannelList(chans);
}

void MasterAudio::GetExtraTrackInfo(PlayerTrackConfigList* player_track_config_list, SongInfoAudioType audioTy, ExtraTrackInfo& trackInfo){
    MILO_ASSERT(player_track_config_list, 0x24F);
    const UserGuid& player = player_track_config_list->InstrumentPlayer(audioTy, 0);
    if(audioTy == kAudioTypeVocals){
        trackInfo.unka = true;
    }
    if(!player.IsNull()){
        if(audioTy == kAudioTypeVocals){
            if(player_track_config_list->IsUserRemote(player)){
                trackInfo.unk8 = true;
                trackInfo.unk0 = true;
            }
            else {
                trackInfo.unk4 = mCueVolume;
                trackInfo.unk0 = true;
                trackInfo.unk9 = true;
            }
        }
        else trackInfo.unk0 = true;
    }
    else trackInfo.unk0 = false;
}

void MasterAudio::SetupTrackChannel_(int i, ExtraTrackInfo& info){
    SetupTrackChannel(i, info.unka, info.unk4, info.unk9, info.unk8);
}

void MasterAudio::SetupTrackChannel(int chan, bool b2, float f3, bool b4, bool b5){
    ChannelData* cur = mChannelData[chan];
    if(!b2) cur->SetSlippable(true);
    cur->SetPan(cur->GetPan());
    cur->SetFaderVal(f3 + cur->GetVol());
    FaderGroup* grp = mSongStream->ChannelFaders(chan);
    if(b4) grp->Add(mVocalCueFader);
    if(b2) ConfigureVocalFaders(chan, b5);
    else {
        grp->Add(mForegroundFader);
        grp->Add(mMultiplayerFader);
        grp->Add(mCommonFader);
    }
    grp->AddLocal("mute");
    grp->AddLocal("remote");
    grp->AddLocal("drum_fill");
}

void MasterAudio::SetupBackgroundChannel_(int i, ExtraTrackInfo& info){
    SetupBackgroundChannel(i, info.unka, info.unk4, info.unk9, info.unk8);
}

void MasterAudio::SetupBackgroundChannel(int chan, bool b2, float f3, bool b4, bool b5){
    FaderGroup* grp = mSongStream->ChannelFaders(chan);
    grp->Add(mBackgroundFader);
    grp->Add(mBackgroundAttenFader);
    grp->Add(mPracticeFader);
    grp->Add(mRemoteFader);
    ChannelData* cur = mChannelData[chan];
    float val = f3 + cur->GetVol();
    val += (b4 ? 0 : mBackgroundVolume);
    cur->SetFaderVal(val);
    if(b4) grp->Add(mVocalCueFader);
    if(b2){
        cur->SetSlippable(false);
        ConfigureVocalFaders(chan, b5);
    }
    else cur->SetSlippable(true);
    grp->AddLocal("mute");
    grp->AddLocal("remote");
    grp->AddLocal("drum_fill");
}

void MasterAudio::ResetTrack(int i, bool b) {
    ResetTrack(TrackNumAt(i), b);
}

void MasterAudio::ResetTrack(AudioTrackNum num, bool b) {
    std::list<int> iList;
    mTrackData[num]->FillChannelList(iList);
    mTrackData[num]->Reset();
    SetAutoOn(num, 0);
    for (std::list<int>::iterator it = iList.begin(); it != iList.end(); ++it) {
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
        bool b1 = mTrackData[num]->Vocals();
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

bool MasterAudio::Fail() {
    if (mSongStream)
        return mSongStream->Fail();
    else
        return true;
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

void MasterAudio::Play() {
    MILO_ASSERT(mSongStream, 0x334);
    mSongStream->Play();
    for (int i = 0; i < mChannelData.size(); i++) {
        mChannelData[i]->ForceOn();
    }
}

void MasterAudio::Poll(){
    if(mMuckWithPitch && IsStreamPlaying() && mPitchMucker){
        mPitchMucker->UpdatePitch(mSongStream);
    }
    if(IsReady()){
        for(std::vector<ChannelData *>::iterator it = mChannelData.begin(); it != mChannelData.end(); ++it){
            (*it)->Poll();
        }
        float time = GetTime();
        for(AudioTrackNum num(0); num.Val() < NumPlayTracks(); ++num){
            if(mTrackData[num]->InButtonMashingMode() && (time > mTrackData[num]->LastMashTime() + 500.0f)){
                SetTrackMuteFader(num, -1, -96.0f, 500.0f);
            }
        }
    }
}

void MasterAudio::Jump(float f) {
    mSongStream->Stop();
    mStreamEnabled = false;
    mSongStream->Resync(f);
    UnmuteAllTracks();
    for(AudioTrackNum num(0); num.Val() < NumPlayTracks(); ++num){
        mTrackData[num]->Reset();
        ResetSlipTrack(num, true);
    }
}

void MasterAudio::ToggleMuteMaster() {
    bool b = mMuteMaster;
    SetMuteMaster(!b);
    return;
}

void MasterAudio::SetMuteMaster(bool muted) {
    mMuteMaster = muted;
    UpdateMasterFader();
}

void MasterAudio::SetMasterVolume(float volume) {
    mMasterVolume = volume;
    UpdateMasterFader();
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

void MasterAudio::SetForegroundVolume(float volume) {
    mForegroundFader->SetVal(volume);
}

void MasterAudio::SetBackgroundVolume(float volume) {
    mBackgroundFader->SetVal(volume);
}

void MasterAudio::SetStereo(bool b) {
    for (int i = 0; i < mChannelData.size(); i++) {
        mChannelData[i]->SetStereo(b);
    }
}

void MasterAudio::SetSpeed(int idx, const UserGuid& u, float f){
    SetSpeed(TrackNumAt(idx), u, f);
}

void MasterAudio::SetSpeed(AudioTrackNum num, const UserGuid& u, float f){
    if(mStreamEnabled && mWhammyEnabled){
        if(mTrackData[num]->mUserGuid == u){
            std::list<int> chans;
            mTrackData[num]->FillChannelList(chans);
            for(std::list<int>::iterator it = chans.begin(); it != chans.end(); ++it){
                mChannelData[*it]->SetSlipTrackSpeed(f);
            }
        }
    }
}

void MasterAudio::SetVocalDuckFader(float val){
    mVocalDuckFader->DoFade(val * mVocalMuteVolume, 250.0f);
}

void MasterAudio::SetVocalCueFader(float val){
    mVocalCueFader->DoFade(val, 0);
}

void MasterAudio::SetVocalFailFader(float fader) {
    mVocalFailFader->DoFade(fader, 0);
}

void MasterAudio::SetCrowdFader(float fader){
    mCrowdFader->DoFade(fader, 4000.0f);
}

void MasterAudio::SetBaseCrowdFader(float fader){
    mBaseCrowdFader->DoFade(fader, 0);
}

void MasterAudio::ResetSlipTrack(int i, bool b){
    ResetSlipTrack(TrackNumAt(i), b);
}

void MasterAudio::ResetSlipTrack(AudioTrackNum num, bool b){
    if(IsStreamPlaying()){
        std::list<int> chans;
        mTrackData[num]->FillChannelList(chans);
        for(std::list<int>::iterator it = chans.begin(); it != chans.end(); ++it){
            mChannelData[*it]->Reset(b);
        }
    }
}

void MasterAudio::SetFX(int channel, FXCore core, bool enabled) {
    if (!mTrackData.mTrackData.empty()) {
        SetFX(TrackNumAt(channel), core, enabled);
    }
    return;
}

void MasterAudio::SetFX(AudioTrackNum trackNum, FXCore core, bool enabled) {
    if (core == -1) {
        MILO_ASSERT(core != kFXCoreNone, 0x406);
    }

    std::list<int> iList;
    mTrackData[trackNum]->FillChannelList(iList, -1);
    for (std::list<int>::iterator it = iList.begin(); it != iList.end(); ++it) {
        mChannelData[*it]->SetFX(core, enabled);
    }
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

void MasterAudio::SetTimeOffset(float offset) {
    mTimeOffset = offset;
}

void MasterAudio::SetPaused(bool paused){
    if(mSongStream){
        if(paused) mSongStream->Stop();
        else if(!mSongStream->IsPlaying()){
            mSongStream->Play();
        }
        if(!paused){
            for(int i = 0; i < mChannelData.size(); i++){
                mChannelData[i]->ForceOn();
            }
        }
    }
}

bool MasterAudio::Paused() const {
    return !mSongStream->IsPlaying();
}

void MasterAudio::SetPracticeMode(bool enabled) {
    mPracticeFader->SetVal(enabled ? mPracticeVolume : 0.0f);
}

void MasterAudio::SetMuckWithPitch(bool enabled) {
    mMuckWithPitch = enabled;
}

void MasterAudio::SetRemoteTrack(int track){
    mRemoteFader->SetVal(mRemoteVolume);
    SetTrackFader(TrackNumAt(track), -1, "remote", mRemoteVolume, 0);
}

void MasterAudio::SetTrackFader(AudioTrackNum track, int i, Symbol s, float f1, float f2){
    MILO_ASSERT(0 <= track.Val() && track.Val() < NumPlayTracks(), 0x457);
    std::list<int> chans;
    mTrackData[track]->FillChannelList(chans, i);
    chans.size();
    if(i != -1 && s == mute){
        mTrackData[track]->FillChannelListWithInactiveSlots(chans, GetTime(), f1 == 0);
    }
    for(std::list<int>::iterator it = chans.begin(); it != chans.end(); ++it){
        int cur = *it;
        Fader* fader = mSongStream->ChannelFaders(cur)->FindLocal(s, true);
        if(f2 > 0) fader->DoFade(f1, f2);
        else fader->SetVal(f1);
    }
}

void MasterAudio::SetTrackMuteFader(AudioTrackNum num, int i, float f1, float f2){
    TrackData* data = mTrackData[num];
    SetTrackFader(num, i, "mute", f1, f2);
    data->unk48 = f1;
}

void MasterAudio::Hit(int i1, float f2, int i3, unsigned int ui, GemHitFlags flags){
    int slot = GemSlot(i1, i3);
    AudioTrackNum track = TrackNumAt(i1);
    mTrackData[track]->Hit(i3, slot, f2);
    UnmuteTrack(track, slot);
}

void MasterAudio::ReleaseGem(int i1, float f2, int i3, float f4){
    AudioTrackNum num = TrackNumAt(i1);
    GameGem& gem = mSongData->GetGemList(i1)->GetGem(i3);
    bool b2 = false;
    if(i3 == mTrackData[num]->LastPlayedGem() && !gem.IgnoreDuration()){
        if(f4 > 0) b2 = true;
    }
    if(b2){
        int slot = gem.GetSlot();
        MuteTrack(num, slot, (DontPlayReason)1, 50.0f);
        mTrackData[num]->Miss(slot, f2);
        DontPlay(num, slot, (DontPlayReason)0);
    }
}

void MasterAudio::Miss(int i1, int i2, float f1, int i3, int i4, GemHitFlags flags){
    if(i3 == 0){
        int tick = MsToTickInt(f1);
        if(tick <= mSongData->GetGemList(i1)->GetGem(i3).GetTick() - 240) return;
    }
    AudioTrackNum num = TrackNumAt(i1);
    int slot = GemSlot(i1, i3);
    mTrackData[num]->Miss(slot, f1);
    DontPlay(num, slot, (DontPlayReason)0);
}

void MasterAudio::Pass(int i1, float f2, int i3, bool b4){
    AudioTrackNum num = TrackNumAt(i1);
    if(b4 && !mTrackData[num]->AutoOn() && !mTrackData[num]->InButtonMashingMode() && !mTrackData[num]->InFill()){
        int slot = GemSlot(i1, i3);
        mTrackData[num]->Miss(slot, f2);
        DontPlay(num, slot, (DontPlayReason)1);
    }
}

void MasterAudio::Ignore(int i1, float f2, int i3, const UserGuid& u){
    AudioTrackNum num = TrackNumAt(i1);
    if(mTrackData[num]->mUserGuid == u){
        Pass(i1, f2, i3, true);
    }
}

void MasterAudio::ImplicitGem(int, float, int, const UserGuid&){}

void MasterAudio::SeeGem(int i1, float f2, int i3){
    AudioTrackNum num = TrackNumAt(i1);
    if(!mTrackData[num]->InButtonMashingMode()){
        int slot = GemSlot(i1, i3);
        if(GetSucceeding(num, slot)){
            UnmuteTrack(num, slot);
        }
        else {
            MuteTrack(num, slot, (DontPlayReason)1, 50.0f);
        }
    }
}

void MasterAudio::FillSwing(int idx, int, int, int, bool){
    AudioTrackNum num = TrackNumAt(idx);
    if(mTrackData[num]->InButtonMashingMode()){
        mTrackData[num]->SetLastMashTime(GetTime());
        SetTrackMuteFader(num, -1, 0, 10.0f);
    }
}

void MasterAudio::SetTrack(const UserGuid& u, int i){
    AudioTrackNum num = TrackNumAt(i);
    mTrackData[num]->SetUserGuid(u);
}

void MasterAudio::SetAutoOn(int i1, int i2){
    SetAutoOn(TrackNumAt(i1), i2);
}

void MasterAudio::SetAutoOn(AudioTrackNum num, int on){
    mTrackData[num]->SetAutoOn(on);
    if(on) UnmuteTrack(num, -1);
}

void MasterAudio::DontPlay(AudioTrackNum num, int i, DontPlayReason reason){
    MuteTrack(num, i, reason, 50.0f);
}

void MasterAudio::SetNonmutable(int iii){
    SetNonmutable(TrackNumAt(iii));
}

void MasterAudio::SetNonmutable(AudioTrackNum num){
    mTrackData[num]->SetNonmutable(true);
    UnmuteTrack(num, -1);
}

void MasterAudio::MuteTrack(int i){
    MuteTrack(TrackNumAt(i), -1, (DontPlayReason)1, 50.0f);
}

void MasterAudio::MuteTrack(AudioTrackNum num, int i, DontPlayReason r, float f){
    if(!mTrackData[num]->NonMutable() && !mTrackData[num]->AutoOn()){
        float f1 = mUnplayedVolume;
        if(mTrackData[num]->NonNullUser()){
            if(r == 0) f1 = mMuteVolume;
            else f1 = mPassVolume;
        }
        SetTrackMuteFader(num, i, f1, f);
    }
}

void MasterAudio::UnmuteTrack(AudioTrackNum trackNum, int i) {
    SetTrackMuteFader(trackNum, i, 0.0f, 0.0f);
}

void MasterAudio::UnmuteAllTracks() {
    for(AudioTrackNum num(0); num.Val() < NumPlayTracks(); ++num){
        UnmuteTrack(num, -1);
    }
}

void MasterAudio::FadeOutDrums(int trackNum) {
    AudioTrackNum num = TrackNumAt(trackNum);
    mTrackData[num]->SetInFill(true);
    SetTrackFader(num, -1, "drum_fill", -96.0f, 1000.0f);
}

void MasterAudio::RestoreDrums(int trackNum){
    AudioTrackNum num = TrackNumAt(trackNum);
    mTrackData[num]->SetInFill(false);
    SetTrackFader(num, -1, "drum_fill", 0, 250.0f);
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

void MasterAudio::HandleSubmix(int i, const char* cc){
    AudioTrackNum num = TrackNumAt(i);
    mTrackData[num]->SetMapping(cc);
}

void MasterAudio::SetButtonMashingMode(int i, bool b){
    AudioTrackNum num = TrackNumAt(i);
    mTrackData[num]->SetButtonMashingMode(b, GetTime());
}

int MasterAudio::GemSlot(int i1, int i2){
    if(i2 == -1) return -1;
    else {
        return mSongData->GetGemList(i1)->GetGem(i2).GetSlot();
    }
}

void MasterAudio::PrintFaders(){
    MILO_LOG("MasterFader %.2f\n", mMasterFader->GetVal());
    MILO_LOG("ForegroundFader %.2f\n", mForegroundFader->GetVal());
    MILO_LOG("MultiplayerFader %.2f\n", mMultiplayerFader->GetVal());
    MILO_LOG("BackgroundFader %.2f\n", mBackgroundFader->GetVal());
    MILO_LOG("BackgroundAttenFader %.2f\n", mBackgroundAttenFader->GetVal());
    MILO_LOG("CommonFader %.2f\n", mCommonFader->GetVal());
    MILO_LOG("RemoteFader %.2f\n", mRemoteFader->GetVal());
    MILO_LOG("PracticeFader %.2f\n", mPracticeFader->GetVal());
    MILO_LOG("VocalDuckFader %.2f\n", mVocalDuckFader->GetVal());
    MILO_LOG("VocalFailFader %.2f\n", mVocalFailFader->GetVal());
    MILO_LOG("VocalCueFader %.2f\n", mVocalCueFader->GetVal());
    MILO_LOG("CrowdFader %.2f\n", mCrowdFader->GetVal());
    MILO_LOG("BaseCrowdFader %.2f\n", mBaseCrowdFader->GetVal());
    for(int i = 0; i < mChannelData.size(); i++){
        MILO_LOG("CHANNEL %d\n", i);
        FaderGroup* grp = mSongStream->ChannelFaders(i);
        grp->Print(TheDebug);
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

void TrackData::Init(SubmixCollection *submixes, bool b) {
    mSubmixes = submixes;
    mMultiSlot = false;
    mSucceeding = false;
    mSucceedingVec.reserve(kMaxSlots);
    mSucceedingVec.assign(kMaxSlots, false);
    mLastGemTimes.reserve(kMaxSlots);
    mLastGemTimes.assign(kMaxSlots, -10000.0f);
    SetSucceeding(true, -1, -10000.0f);
    mLastPlayedGem = -1;
    mChannelMapping = 0;
    mIndieSlots = b;
    mOriginalChannels.clear();
    mNonmutable = false;
    mButtonMashingMode = false;
    mInFill = false;
    mAutoOn = false;
    mVocals = false;
    unk48 = 99.0f;
    mUserGuid.Clear();
}

void TrackData::SetMapping(const std::vector<int>& chans){
    mOriginalChannels.clear();
    mOriginalChannels.insert(mOriginalChannels.begin(), chans.begin(), chans.end());
    if(mSubmixes){
        RELEASE(mChannelMapping);
        if(chans.size() == 1){
            mChannelMapping = new SingleSlotChannelMapping(chans[0]);
            mMultiSlot = false;
        }
        else {
            mChannelMapping = NewSlotChannelMapping(mSubmixes, chans, !mIndieSlots);
            mMultiSlot = chans.size() > 2;
        }
    }
}

void TrackData::SetMapping(const char* cc){
    if(mSubmixes){
        char* p = (char*)cc;
        for(; *p != '\0' && *p != ' '; p++);
        int len = p - (char*)cc;
        MILO_ASSERT(len < 64, 0x67B);
        char buf[64];
        strncpy(buf, cc, len);
        buf[len] = '\0';
        Submix* mix = mSubmixes->Find(buf);
        if(mix){
            RELEASE(mChannelMapping);
            mChannelMapping = new MultiChannelMapping(mix, buf, mOriginalChannels);
        }
        else MILO_WARN("MIDI authoring error: submix %s is not defined\n", buf);
        mMultiSlot = true;
    }
}

TrackData::~TrackData(){
    RELEASE(mChannelMapping);
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

void TrackData::FillChannelList(std::list<int> &list) const {
    if (mChannelMapping == 0) {
        return;
    }
    mChannelMapping->FillChannelList(list);
}

void TrackData::FillChannelList(std::list<int> &list, int i) const {
    if(mChannelMapping) mChannelMapping->FillChannelList(list, i);
}

void TrackData::Hit(int gemID, int i, float f) {
    SetSucceeding(true, i, f);
    mLastPlayedGem = gemID;
}

void TrackData::Miss(int i, float f) {
    SetSucceeding(false, i, f);
}

void TrackData::SetUserGuid(const UserGuid &guid) {
    mUserGuid = guid;
}

void TrackData::SetNonmutable(bool nonmutable) {
    mNonmutable = nonmutable;
}

void TrackData::SetButtonMashingMode(bool enabled, float lastMashTime) {
    mButtonMashingMode = enabled;
    mLastMashTime = lastMashTime;
}

void TrackData::SetLastMashTime(float lastMashTime) {
    mLastMashTime = lastMashTime;
}

void TrackData::Reset() {
    SetSucceeding(true, -1, -10000.0f);
    mInFill = 0;
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

bool TrackData::IsSlotActive(int i, float f) const {
    if (mMultiSlot) {
        return (f - mLastGemTimes[i] < 5000.0f);
    }
    return true;
}

void TrackData::FillChannelListWithInactiveSlots(std::list<int>& chans, float f, bool b) const {
    if(mMultiSlot && mChannelMapping){
        int i6 = 0;
        int i5 = 0;
        bool b4 = true;
        for(int i = 0; i < mChannelMapping->GetNumSlots(); i++){
            if(IsSlotActive(i, f)){
                if(!GetSucceeding(i)) b4 = false;
                i6 |= mChannelMapping->ChannelBitfield(i);
            }
            else {
                i5 |= mChannelMapping->ChannelBitfield(i);
            }
        }
        i5 &= ~i6;
        if(b4 == b){
            for(int i = 0; i5 != 0; i++){
                i6 = 1 << i;
                if(i6 & i5){
                    i5 -= i6;
                    chans.push_back(i);
                }
            }
        }
    }
}

BEGIN_HANDLERS(MasterAudio)
    HANDLE_ACTION(set_vocal_cue_fader, SetVocalCueFader(_msg->Float(2)))
    HANDLE_ACTION(set_crowd_fader, SetCrowdFader(_msg->Float(2)))
    HANDLE_ACTION(toggle_mute_master, ToggleMuteMaster())
    HANDLE_ACTION(set_mute_master, SetMuteMaster(_msg->Int(2)))
    HANDLE_ACTION(set_base_crowd_fader, SetBaseCrowdFader(_msg->Float(2)))
    HANDLE_ACTION(print_faders, PrintFaders())
    HANDLE_CHECK(0x735)
END_HANDLERS