#ifndef METABAND_PROFILEMGR_H
#define METABAND_PROFILEMGR_H
#include "obj/MsgSource.h"
#include "os/Joypad.h"
#include "meta/Profile.h"
#include "meta_band/BandProfile.h"
#include "net_band/DataResults.h"

enum LagContext {
    kGame = 0,
    kVCal = 1,
    kACal = 2,
    kPractice90 = 3,
    kPractice80 = 4,
    kPractice70 = 5,
    // where 6
    kNumLagContexts = 7
};

class ProfileMgr : public MsgSource {
public:
    ProfileMgr();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~ProfileMgr(){}
    virtual void SetMicVol(int, int);
    virtual int GetMicVol(int) const;

    int GetSliderStepCount() const;
    Profile* GetProfileForUser(const LocalUser*);
    void SetCymbalConfiguration(unsigned int);
    void UpdatePrimaryProfile();
    bool GetAllUnlocked();
    int GetMaxCharacters() const;
    bool UnlockAllSongs();
    void RelockSongs();
    void SetGlobalOptionsSaveState(ProfileSaveState);
    bool GlobalOptionsNeedsSave();
    int GetGlobalOptionsSize();
    void SaveGlobalOptions(FixedSizeSaveableStream&);
    void LoadGlobalOptions(FixedSizeSaveableStream&);
    void PushAllOptions();
    void InitSliders();
    float SliderIxToDb(int) const;
    void GetMicGainInfo(const Symbol&, float&, float&, float&, float&) const;
    bool GetBassBoost() const;
    void SetBackgroundVolume(int);
    void SetForegroundVolume(int);
    void SetFxVolume(int);
    int GetFxVolume() const;
    void SetCrowdVolume(int);
    void SetVocalCueVolume(int);
    void SetVoiceChatVolume(int);
    void SetBassBoost(bool);
    void SetDolby(bool);
    void SetOverscan(bool);
    void SetSynapseEnabled(bool);
    void SetWiiSpeakToggle(bool);
    void SetWiiSpeakFriendsVolume(int);
    void SetWiiSpeakMicrophoneSensitivity(int);
    void SetWiiSpeakHeadphoneMode(bool);
    void SetWiiSpeakEchoSuppression(bool);
    bool GetHasSeenFirstTimeCalibration() const;
    void SetHasSeenFirstTimeCalibration(bool);
    bool GetHasConnectedProGuitar() const;
    void SetHasConnectedProGuitar(bool);
    void SetWiiFriendsPromptShown();
    bool GetUsingWiiFriends();
    bool GetSecondPedalHiHat() const;
    void SetSecondPedalHiHat(bool);
    void SetSyncPresetIx(int);
    float GetSongToTaskMgrMsRaw() const;
    void SetSongToTaskMgrMsRaw(float);
    float GetJoypadExtraLagInits(JoypadType, LagContext) const;
    float GetJoypadExtraLag(JoypadType, LagContext) const;
    void SetJoypadExtraLag(JoypadType, LagContext, float);
    float GetPadExtraLag(int, LagContext) const;
    void SetPlatformAudioLatency(float);
    void SetPlatformVideoLatency(float);
    float GetInGameExtraVideoLatency() const;
    void SetInGameExtraVideoLatency(float);
    float GetInGameSyncOffsetAdjustment() const;
    void SetInGameSyncOffsetAdjustment(float);
    float GetSyncOffset(int) const;
    float GetSyncOffsetRaw() const;
    void SetSyncOffsetRaw(float);
    float GetExcessVideoLag() const;
    void SetExcessVideoLag(float);
    void SetExcessAudioLag(float);
    float GetPlatformAudioLatency() const;
    float GetPlatformVideoLatency() const;
    float GetExcessAudioLagNeutral(int, bool) const;
    float GetExcessVideoLagNeutral(int, bool) const;
    float GetExcessAudioLag() const;
    float GetBackgroundVolumeDb() const;
    int GetBackgroundVolume() const;
    float GetForegroundVolumeDb() const;
    int GetForegroundVolume() const;
    float GetFxVolumeDb() const;
    float GetCrowdVolumeDb();
    int GetCrowdVolume() const;
    float GetVocalCueVolumeDb();
    int GetVocalCueVolume() const;
    float GetVoiceChatVolumeDb();
    int GetVoiceChatVolume() const;
    unsigned int GetCymbalConfiguration() const;
    bool HasLoaded();
    BandProfile* FindTourProgressOwner(const TourProgress*);

    DECLARE_REVS;

    float mPlatformAudioLatency; // 0x1c
    float mPlatformVideoLatency; // 0x20
    float mInGameExtraVideoLatency; // 0x24
    float mInGameSyncOffsetAdjustment; // 0x28
    float mJoypadExtraLagOffsets[0x2F][7]; // 0x2c
    int unk550;
    ProfileSaveState mGlobalOptionsSaveState; // 0x554
    bool mGlobalOptionsDirty; // 0x558
    int mBackgroundVolume; // 0x55c
    int mForegroundVolume; // 0x560
    int mFxVolume; // 0x564
    int mCrowdVolume; // 0x568
    int mVocalCueVolume; // 0x56c
    int mVoiceChatVolume; // 0x570
    bool mHasSeenFirstTimeCalibration; // 0x574
    bool mHasConnectedProGuitar; // 0x575
    float mSyncOffset; // 0x578
    float mSongToTaskMgrMs; // 0x57c
    bool mBassBoost; // 0x580
    bool mDolby; // 0x581
    bool unk582;
    int mSyncPresetIx; // 0x584
    bool mOverscan; // 0x588
    bool mSynapseEnabled; // 0x589
    bool unk58a;
    bool mSecondPedalHiHat; // 0x58b
    DataResultList unk58c;
    bool mWiiSpeakToggle; // 0x5a4
    int mWiiSpeakFriendsVolume; // 0x5a8
    int mWiiSpeakMicrophoneSensitivity; // 0x5ac
    bool mWiiSpeakHeadphoneMode; // 0x5b0
    bool mWiiSpeakEchoSuppression; // 0x5b1
    bool unk5b2;
    bool mWiiFriendsPromptShown; // 0x5b3
    bool mUsingWiiFriends; // 0x5b4
    int unk5b8;
    std::vector<int> unk5bc;
    DataArray* mSliderConfig; // 0x5c4
    DataArray* mVoiceChatSliderConfig; // 0x5c8
    unsigned int mCymbalConfiguration; // 0x5cc
    std::vector<BandProfile*> mProfiles; // 0x5d0
    int unk5d8;
    bool mAllUnlocked; // 0x5dc
    std::vector<float> unk5e0;
};

extern ProfileMgr TheProfileMgr;

#endif // METABAND_PROFILEMGR_H