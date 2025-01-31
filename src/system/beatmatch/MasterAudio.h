#pragma once
#include "beatmatch/InternalSongParserSink.h"
#include "obj/Data.h"
#include "beatmatch/SongData.h"
#include "beatmatch/BeatMasterSink.h"
#include "beatmatch/BeatMatchSink.h"
#include "beatmatch/HxAudio.h"
#include "beatmatch/PitchMucker.h"
#include "beatmatch/Submix.h"
#include "obj/Object.h"
#include "os/User.h"
#include "synth/Faders.h"
#include "synth/Stream.h"
#include "synth/SlipTrack.h"
#include "beatmatch/SlotChannelMapping.h"

class BeatMaster;
class SongInfo;

class ChannelData {
public:
    ChannelData(Stream *, int, float, float, FXCore);
    ~ChannelData();
    void SetSlippable(bool);
    void ForceOn();
    void Reset(bool);
    void SetSlipTrackSpeed(float);
    void Poll();
    void SetFX(FXCore, bool);
    void SetStereo(bool);
    void SetFaderVal(float);
    void SetPan(float);
    float GetPan() const { return mPan; }
    float GetVol() const { return mVolume; }

    Stream *mStream; // 0x0
    int mChannel; // 0x4
    SlipTrack *mSlipTrack; // 0x8
    Fader *mBaseFader; // 0xc
    bool mIsTrackChannel; // 0x10
    float mPan; // 0x14
    float mOriginalPan; // 0x18
    FXCore mCore; // 0x1c
    float mOverallSpeed; // 0x20
    float mSpeed; // 0x24
    bool mDirty; // 0x28
    float mVolume; // 0x2c
};

class TrackData {
public:
    TrackData();
    TrackData(SubmixCollection *, const std::vector<int> &, bool, bool);
    ~TrackData();
    int GetSucceeding(int) const;
    void Hit(int, int, float);
    void Init(SubmixCollection *, bool);
    bool IsSlotActive(int, float) const;
    void Miss(int, float);
    void SetButtonMashingMode(bool, float);
    void SetMapping(const std::vector<int> &);
    void SetLastMashTime(float);
    void SetSucceeding(bool, int, float);
    void SetMapping(const char *);
    void SetNonmutable(bool);
    void SetUserGuid(const UserGuid &);
    void FillChannelList(std::list<int> &) const;
    void FillChannelList(std::list<int> &, int) const;
    void Reset();
    void FillChannelListWithInactiveSlots(std::list<int>&, float, bool) const;
    bool Vocals() const { return mVocals; }
    bool InButtonMashingMode() const { return mButtonMashingMode; }
    float LastMashTime() const { return mLastMashTime; }
    int LastPlayedGem() const { return mLastPlayedGem; }
    bool InFill() const { return mInFill; }
    bool AutoOn() const { return mAutoOn; }
    void SetAutoOn(bool on){ mAutoOn = on; }
    bool NonMutable() const { return mNonmutable; }
    bool NonNullUser() const { return !mUserGuid.IsNull(); }
    void SetInFill(bool fill){ mInFill = fill; }

    bool mSucceeding; // 0x0
    std::vector<bool> mSucceedingVec; // 0x4
    std::vector<float> mLastGemTimes; // 0xc
    bool mMultiSlot; // 0x14
    int mLastPlayedGem; // 0x18
    SlotChannelMapping *mChannelMapping; // 0x1c
    SubmixCollection *mSubmixes; // 0x20
    UserGuid mUserGuid; // 0x24
    bool mIndieSlots; // 0x34
    bool mNonmutable; // 0x35
    bool mButtonMashingMode; // 0x36
    float mLastMashTime; // 0x38
    bool mInFill; // 0x3c
    bool mAutoOn; // 0x3d
    bool mVocals; // 0x3e
    std::vector<int> mOriginalChannels; // 0x40
    float unk48; // 0x48
};

class TrackDataCollection {
public:
    TrackDataCollection() {}
    TrackData*& operator[](AudioTrackNum num){
        return mTrackData[num.mVal];
    }
    const TrackData*& operator[](AudioTrackNum num) const {
        return (const TrackData*&)(mTrackData[num.mVal]);
    }
    std::vector<TrackData *> mTrackData; // 0x0
};

class MasterAudio : public BeatMasterSink,
                    public BeatMatchSink,
                    public Hmx::Object,
                    public HxAudio {
public:
    class ExtraTrackInfo {
    public:
        ExtraTrackInfo() : unk0(0), unk4(0), unk8(0), unk9(0), unka(0) {}
        bool unk0;
        float unk4;
        bool unk8;
        bool unk9;
        bool unka;
    };

    enum DontPlayReason {

    };

    MasterAudio(DataArray *, int, BeatMaster *, SongData *);
    virtual ~MasterAudio();
    virtual void Beat(int, int) {}
    virtual void UpdateSongPos(const SongPos &) {}
    virtual void HandleSubmix(int, const char *);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool IsReady();
    virtual bool Paused() const;
    virtual void SetPaused(bool);
    virtual void Poll();
    virtual float GetTime() const;
    virtual Stream* GetSongStream();
    virtual void SetMasterVolume(float);

    virtual void Hit(int, float, int, unsigned int, GemHitFlags);
    virtual void ReleaseGem(int, float, int, float);
    virtual void Miss(int, int, float, int, int, GemHitFlags);
    virtual void SpuriousMiss(int, int, float, int) {}
    virtual void Pass(int, float, int, bool);
    virtual void Ignore(int, float, int, const UserGuid &);
    virtual void ImplicitGem(int, float, int, const UserGuid &);
    virtual void SeeGem(int, float, int);
    virtual void FillSwing(int, int, int, int, bool);
    virtual void SetTrack(const UserGuid &, int);
    virtual void Swing(int, int, float, bool, bool) {}
    virtual void FretButtonDown(int, float) {}
    virtual void FretButtonUp(int, float) {}
    virtual void MercurySwitch(bool, float) {}
    virtual void WhammyBar(float) {}
    virtual void FilteredWhammyBar(float) {}
    virtual void SwingAtHopo(int, float, int) {}
    virtual void Hopo(int, float, int) {}
    virtual void SetCurrentPhrase(int, const PhraseInfo &) { return; }
    virtual void NoCurrentPhrase(int) {}
    virtual void FillReset() {}
    virtual void FillComplete(int, int) {}

    void Load(SongInfo *, PlayerTrackConfigList *);
    void SetupChannels(SongInfo *);
    void SetupTracks(SongInfo *, PlayerTrackConfigList *);
    bool IsLoaded();
    void FadeOutDrums(int);
    void ResetTrack(int, bool);
    void ResetTrack(AudioTrackNum, bool);
    void SetAutoOn(AudioTrackNum, int);
    void SetAutoOn(int, int);
    void SetupTrackChannel(int, bool, float, bool, bool);
    void SetupBackgroundChannel(int, bool, float, bool, bool);
    void SetBackgroundVolume(float);
    void SetForegroundVolume(float);
    void SetFX(int, FXCore, bool);
    void SetFX(AudioTrackNum, FXCore, bool);
    void SetMuckWithPitch(bool);
    void SetMuteMaster(bool);
    void SetPracticeMode(bool);
    void SetStereo(bool);
    void SetTrackFader(AudioTrackNum, int, Symbol, float, float);
    void SetTrackMuteFader(AudioTrackNum, int, float, float);
    void SetVocalFailFader(float);
    void SetVocalState(bool);
    void ToggleMuteMaster();
    void ConfigureVocalFaders(int, bool);
    bool Fail();
    bool IsFinished() const;
    void Play();
    void Jump(float);
    void UnmuteAllTracks();
    void UnmuteTrack(AudioTrackNum, int);
    void UpdateMasterFader();
    void ResetSlipTrack(AudioTrackNum, bool);
    void SetTimeOffset(float);
    void GetExtraTrackInfo(PlayerTrackConfigList*, SongInfoAudioType, ExtraTrackInfo&);
    void SetupBackgroundChannel_(int, ExtraTrackInfo&);
    void SetupTrackChannel_(int, ExtraTrackInfo&);
    void SetNonmutable(AudioTrackNum);
    void FillChannelList(std::list<int> &, int);
    void SetSpeed(int, const UserGuid&, float);
    void SetSpeed(AudioTrackNum, const UserGuid&, float);
    void SetVocalDuckFader(float);
    void SetVocalCueFader(float);
    void SetCrowdFader(float);
    void SetBaseCrowdFader(float);
    void ResetSlipTrack(int, bool);
    void SetRemoteTrack(int);
    int GemSlot(int, int);
    void MuteTrack(AudioTrackNum, int, DontPlayReason, float);
    void DontPlay(AudioTrackNum, int, DontPlayReason);
    void SetNonmutable(int);
    void MuteTrack(int);
    void RestoreDrums(int);
    void SetButtonMashingMode(int, bool);
    void PrintFaders();

    AudioTrackNum TrackNumAt(int idx){ return mSongData->GetAudioTrackNum(idx); }
    int NumPlayTracks() const { return mTrackData.mTrackData.size(); }
    bool IsStreamPlaying() const { return mSongStream && mSongStream->IsPlaying(); }
    int GetSucceeding(AudioTrackNum num, int slot) const {
        return mTrackData[num]->GetSucceeding(slot);
    }

    int mNumPlayers; // 0x28
    Stream *mSongStream; // 0x2c
    SongData *mSongData; // 0x30
    bool mStreamEnabled; // 0x34
    Fader *mMasterFader; // 0x38
    Fader *mForegroundFader; // 0x3c
    Fader *mMultiplayerFader; // 0x40
    Fader *mBackgroundFader; // 0x44
    Fader *mBackgroundAttenFader; // 0x48
    Fader *mCommonFader; // 0x4c
    Fader *mRemoteFader; // 0x50
    Fader *mPracticeFader; // 0x54
    Fader *mVocalDuckFader; // 0x58
    Fader *mVocalCueFader; // 0x5c
    Fader *mVocalFailFader; // 0x60
    Fader *mCrowdFader; // 0x64
    Fader *mBaseCrowdFader; // 0x68
    SubmixCollection *mSubmixes; // 0x6c
    std::vector<ChannelData *> mChannelData; // 0x70
    TrackDataCollection mTrackData; // 0x78
    bool mPlayingInCommon; // 0x80
    float mMultiplayerStereoScale; // 0x84
    float mMultiplayerVolume; // 0x88
    float mMultiplayerCommonVolume; // 0x8c
    float mPlayerAtten; // 0x90
    float mBackgroundVolume; // 0x94
    float mMuteVolume; // 0x98
    float mVocalMuteVolume; // 0x9c
    float mPassVolume; // 0xa0
    float mUnplayedVolume; // 0xa4
    float mCueVolume; // 0xa8
    float mPracticeVolume; // 0xac
    float mRemoteVolume; // 0xb0
    float mMasterVolume; // 0xb4

    bool mMuteMaster; // 0xb8
    bool mMuckWithPitch; // 0xb9

    PitchMucker *mPitchMucker; // 0xbc - PitchMucker*
    bool mWhammyEnabled; // 0xc0
    float mTimeOffset; // 0xc4
};
