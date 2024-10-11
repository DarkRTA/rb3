#ifndef METABAND_PROFILEMGR_H
#define METABAND_PROFILEMGR_H
#include "obj/MsgSource.h"
#include "meta/Profile.h"
#include "net_band/DataResults.h"

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

    DECLARE_REVS;

    float unk1c;
    float unk20;
    float unk24;
    float unk28;
    char filler[0x528];
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
    float unk578;
    float unk57c;
    bool mBassBoost; // 0x580
    bool mDolby; // 0x581
    bool unk582;
    int unk584;
    bool mOverscan; // 0x588
    bool mSynapseEnabled; // 0x589
    bool unk58a;
    bool mSecondPedalHiHat; // 0x58b
    DataResultList unk58c;
    bool mWiiSpeakToggle; // 0x5a4
    int mWiiSpeakFriendsVolume; // 0x5a8
    int mWiiSpeakMicrophoneSensitivity; // 0x5ac
    bool unk5b0;
    bool mWiiSpeakEchoSuppression; // 0x5b1
    bool unk5b2;
    bool mWiiFriendsPromptShown; // 0x5b3
    bool mUsingWiiFriends; // 0x5b4
    int unk5b8;
    std::vector<int> unk5bc;
    DataArray* mSliderConfig; // 0x5c4
    DataArray* mVoiceChatSliderConfig; // 0x5c8
    int unk5cc;
    std::vector<int> unk5d0;
    int unk5d8;
    bool mAllUnlocked; // 0x5dc
    std::vector<float> unk5e0;
};

extern ProfileMgr TheProfileMgr;

#endif // METABAND_PROFILEMGR_H