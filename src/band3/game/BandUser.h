#ifndef GAME_BANDUSER_H
#define GAME_BANDUSER_H
#include "game/Defines.h"
#include "meta_band/GameplayOptions.h"
#include "meta_band/OvershellSlotState.h"
#include "meta_band/CharData.h"
#include "os/User.h"
#include "types.h"
#include "system/bandobj/BandCharacter.h"

class BandCharDesc;
class LocalBandUser;
class RemoteBandUser;
class NullLocalBandUser;
class Player;

class BandUser : public virtual User {
public:
    BandUser();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual ~BandUser();
    virtual bool IsNullUser();
    virtual bool IsParticipating();
    virtual int GetCurrentInstrumentCareerScore() const = 0;
    virtual int GetCurrentHardcoreIconLevel() const = 0;
    virtual int GetCymbalConfiguration() const = 0;
    virtual LocalBandUser* GetLocalBandUser() = 0;
    virtual LocalBandUser* GetLocalBandUser() const = 0;
    virtual RemoteBandUser* GetRemoteBandUser() = 0;
    virtual RemoteBandUser* GetRemoteBandUser() const = 0;
    virtual int GetFriendsConsoleCodes() const = 0;
    virtual void Reset();
    virtual void SyncSave();

    const char* ProfileName() const;
    bool IsFullyInGame() const;
    ControllerType GetControllerType() const;
    Difficulty GetDifficulty() const;
    Symbol GetDifficultySym() const;
    TrackType GetTrackType() const;
    Symbol GetTrackSym() const;
    BandCharacter* GetCharLocal();
    bool HasChar();
    void SetDifficulty(Difficulty);
    void UpdateData(unsigned int);
    void SetDifficulty(Symbol);
    void SetTrackType(TrackType);
    void SetTrackType(Symbol);
    const char* GetOvershellFocus();
    ScoreType GetPreferredScoreType() const;
    void SetPreferredScoreType(ScoreType);
    Symbol GetControllerSym() const;
    void SetControllerType(ControllerType);
    void SetControllerType(Symbol);
    void SetHasButtonGuitar(bool);
    void SetHas22FretGuitar(bool);
    CharData* GetChar();
    const char* IntroName() const;
    int GetSlot() const;
    const char* GetTrackIcon() const;
    void SetOvershellSlotState(OvershellSlotStateID);
    GameplayOptions* GetGameplayOptions();
    float GetLastHitFraction() const { return mLastHitFraction; }
    void SetLastHitFraction(float f){ mLastHitFraction = f; }
    
    static LocalBandUser* NewLocalBandUser();
    static RemoteBandUser* NewRemoteBandUser();
    static NullLocalBandUser* NewNullLocalBandUser();

    DataNode OnSetDifficulty(DataArray*);
    DataNode OnSetTrackType(DataArray*);
    DataNode OnSetHas22FretGuitar(DataArray*);
    DataNode OnSetPreferredScoreType(DataArray*);
    DataNode OnSetControllerType(DataArray*);
    DataNode OnSetPrefabChar(DataArray*);

    Difficulty mDifficulty; // 0x8
    u8 unk_0xC; // 0xC
    TrackType mTrackType; // 0x10
    ControllerType mControllerType; // 0x14
    bool mHasButtonGuitar; // 0x18
    bool mHas22FretGuitar; // 0x19
    ScoreType mPreferredScoreType; // 0x1C
    OvershellSlotStateID mOvershellState; // 0x20
    String mOvershellFocus; // 0x24
    CharData* mChar; // 0x30 - CharData*
    GameplayOptions mGameplayOptions; // 0x34
    bool mAutoplay; // 0x70
    Symbol mPreviousAward; // 0x74
    float mLastHitFraction; // 0x78
    void *mTrack; // 0x7c
    Player* mPlayer; // 0x80
    bool mParticipating; // 0x84
    bool mIsWiiRemoteController; // 0x85
    bool mJustDisconnected; // 0x86
};

class LocalBandUser : public virtual BandUser, public virtual LocalUser {
public:
    LocalBandUser();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~LocalBandUser(){}
    virtual LocalBandUser* GetLocalBandUser();
    virtual LocalBandUser* GetLocalBandUser() const;
    virtual RemoteBandUser* GetRemoteBandUser();
    virtual RemoteBandUser* GetRemoteBandUser() const;
    virtual int GetFriendsConsoleCodes() const;
    virtual void Reset();
    virtual ControllerType ConnectedControllerType() const;
    virtual int GetCurrentInstrumentCareerScore() const;
    virtual int GetCurrentHardcoreIconLevel() const;
    virtual int GetCymbalConfiguration() const;

    bool HasSeenRealGuitarPrompt() const;
    void SetHasSeenRealGuitarPrompt();
    void SetOvershellFocus(const char*);
    ControllerType DebugGetControllerTypeOverride() const;
    void DebugSetControllerTypeOverride(ControllerType);

    bool unkc; // 0xc
    bool mHasSeenRealGuitarPrompt; // 0xd
    std::set<TrackType> mShownIntrosSet; // 0x10
    ControllerType mControllerTypeOverride; // 0x28
};

class RemoteBandUser : public virtual BandUser, public virtual RemoteUser {
public:
    RemoteBandUser();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~RemoteBandUser();
    virtual LocalBandUser* GetLocalBandUser();
    virtual LocalBandUser* GetLocalBandUser() const;
    virtual RemoteBandUser* GetRemoteBandUser();
    virtual RemoteBandUser* GetRemoteBandUser() const;
    virtual int GetFriendsConsoleCodes() const;
    virtual int GetCurrentInstrumentCareerScore() const;
    virtual int GetCurrentHardcoreIconLevel() const;
    virtual int GetCymbalConfiguration() const;
    virtual void Reset();
    virtual void SyncLoad(BinStream&, unsigned int);

    int unkc; // TourCharRemote*
    std::vector<int> unk10; // 0x10
    bool unk18;
    bool unk19;
    bool unk1a;
    int unk1c;
    int unk20;
    int unk24;
};

class NullLocalBandUser : public LocalBandUser {
public:
    NullLocalBandUser(){}
    virtual ~NullLocalBandUser(){}
    virtual bool IsNullUser() const { return true; }
    virtual bool IsJoypadConnected() const { return false; }
    virtual bool CanSaveData() const { return false; }
    virtual const char* UserName() const { return ""; }
};

#endif // GAME_BANDUSER_H
