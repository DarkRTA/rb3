#pragma once
#include "beatmatch/TrackType.h"
#include "game/Defines.h"
#include "meta_band/GameplayOptions.h"
#include "meta_band/OvershellSlotState.h"
#include "meta_band/CharData.h"
#include "os/User.h"
#include "tour/TourCharLocal.h"
#include "tour/TourCharRemote.h"
#include "types.h"
#include "system/bandobj/BandCharacter.h"

class BandCharDesc;
class LocalBandUser;
class RemoteBandUser;
class NullLocalBandUser;
class Player;
class Track;

class BandUser : public virtual User {
public:
    BandUser();
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual ~BandUser();
    virtual bool IsNullUser() const { return false; }
    virtual bool IsParticipating() const { return mParticipating; }
    virtual int GetCurrentInstrumentCareerScore() const = 0;
    virtual int GetCurrentHardcoreIconLevel() const = 0;
    virtual int GetCymbalConfiguration() const = 0;
    virtual LocalBandUser *GetLocalBandUser() = 0;
    virtual LocalBandUser *GetLocalBandUser() const = 0;
    virtual RemoteBandUser *GetRemoteBandUser() = 0;
    virtual RemoteBandUser *GetRemoteBandUser() const = 0;
    virtual int GetFriendsConsoleCodes() const = 0;
    virtual void Reset();
    virtual void SyncSave(BinStream &, unsigned int) const;

    const char *ProfileName() const;
    bool IsFullyInGame() const;
    ControllerType GetControllerType() const;
    Difficulty GetDifficulty() const;
    Symbol GetDifficultySym() const;
    TrackType GetTrackType() const;
    Symbol GetTrackSym() const;
    bool HasChar();
    void SetDifficulty(Difficulty);
    void UpdateData(unsigned int);
    void SetDifficulty(Symbol);
    void SetTrackType(TrackType);
    void SetTrackType(Symbol);
    const char *GetOvershellFocus();
    ScoreType GetPreferredScoreType() const;
    void SetPreferredScoreType(ScoreType);
    Symbol GetControllerSym() const;
    void SetControllerType(ControllerType);
    void SetControllerType(Symbol);
    void SetHasButtonGuitar(bool);
    void SetHas22FretGuitar(bool);
    CharData *GetChar();
    void SetChar(CharData *);
    const char *IntroName() const;
    int GetSlot() const;
    const char *GetTrackIcon() const;
    void SetOvershellSlotState(OvershellSlotStateID);
    GameplayOptions *GetGameplayOptions();
    void SetLoadedPrefabChar(int);
    void DeletePlayer();
    TourCharLocal *GetCharLocal();

    float GetLastHitFraction() const { return mLastHitFraction; }
    void SetLastHitFraction(float f) { mLastHitFraction = f; }
    Player *GetPlayer() const { return mPlayer; }
    Track *GetTrack() const { return mTrack; }
    void SetPlayer(Player *p) { mPlayer = p; }
    void SetTrack(Track *trk) { mTrack = trk; }

    static LocalBandUser *NewLocalBandUser();
    static RemoteBandUser *NewRemoteBandUser();
    static NullLocalBandUser *NewNullLocalBandUser();

    DataNode OnSetDifficulty(DataArray *);
    DataNode OnSetTrackType(DataArray *);
    DataNode OnSetHas22FretGuitar(DataArray *);
    DataNode OnSetPreferredScoreType(DataArray *);
    DataNode OnSetControllerType(DataArray *);
    DataNode OnSetPrefabChar(DataArray *);

    Difficulty mDifficulty; // 0x8
    u8 unk_0xC; // 0xC
    TrackType mTrackType; // 0x10
    ControllerType mControllerType; // 0x14
    bool mHasButtonGuitar; // 0x18
    bool mHas22FretGuitar; // 0x19
    ScoreType mPreferredScoreType; // 0x1C
    OvershellSlotStateID mOvershellState; // 0x20
    String mOvershellFocus; // 0x24
    CharData *mChar; // 0x30 - CharData*
    GameplayOptions mGameplayOptions; // 0x34
    bool mAutoplay; // 0x70
    Symbol mPreviousAward; // 0x74
    float mLastHitFraction; // 0x78
    Track *mTrack; // 0x7c
    Player *mPlayer; // 0x80
    bool mParticipating; // 0x84
    bool mIsWiiRemoteController; // 0x85
    bool mJustDisconnected; // 0x86
};

class LocalBandUser : public virtual BandUser, public virtual LocalUser {
public:
    LocalBandUser();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~LocalBandUser() {}
    virtual LocalBandUser *GetLocalBandUser();
    virtual LocalBandUser *GetLocalBandUser() const;
    virtual RemoteBandUser *GetRemoteBandUser();
    virtual RemoteBandUser *GetRemoteBandUser() const;
    virtual int GetFriendsConsoleCodes() const;
    virtual void Reset();
    virtual ControllerType ConnectedControllerType() const;
    virtual int GetCurrentInstrumentCareerScore() const;
    virtual int GetCurrentHardcoreIconLevel() const;
    virtual int GetCymbalConfiguration() const;

    bool HasSeenRealGuitarPrompt() const;
    void SetHasSeenRealGuitarPrompt();
    void SetOvershellFocus(const char *);
    ControllerType DebugGetControllerTypeOverride() const;
    void DebugSetControllerTypeOverride(ControllerType);
    bool HasShownIntroHelp(TrackType) const;
    void SetShownIntroHelp(TrackType, bool);
    bool CanGetAchievements() const { return CanSaveData(); }

    bool unkc; // 0xc
    bool mHasSeenRealGuitarPrompt; // 0xd
    std::set<TrackType> mShownIntrosSet; // 0x10
    ControllerType mControllerTypeOverride; // 0x28
};

class RemoteBandUser : public virtual BandUser, public virtual RemoteUser {
public:
    RemoteBandUser();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~RemoteBandUser();
    virtual LocalBandUser *GetLocalBandUser();
    virtual LocalBandUser *GetLocalBandUser() const;
    virtual RemoteBandUser *GetRemoteBandUser();
    virtual RemoteBandUser *GetRemoteBandUser() const;
    virtual int GetFriendsConsoleCodes() const;
    virtual int GetCurrentInstrumentCareerScore() const;
    virtual int GetCurrentHardcoreIconLevel() const;
    virtual int GetCymbalConfiguration() const;
    virtual void Reset();
    virtual void SyncLoad(BinStream &, unsigned int);

    TourCharRemote *mRemoteChar; // TourCharRemote*
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
    NullLocalBandUser() {}
    virtual ~NullLocalBandUser() {}
    virtual bool IsNullUser() const { return true; }
    virtual bool IsJoypadConnected() const { return false; }
    virtual bool CanSaveData() const { return false; }
    virtual const char *UserName() const { return ""; }
};

#include "obj/Msg.h"

DECLARE_MESSAGE(NewRemoteUserMsg, "new_remote_user")
NewRemoteUserMsg(RemoteUser *u) : Message(Type(), u) {}
RemoteUser *GetUser() const { return mData->Obj<RemoteUser>(2); }
END_MESSAGE
;

DECLARE_MESSAGE(RemovingRemoteUserMsg, "removing_remote_user")
RemovingRemoteUserMsg(RemoteUser *u) : Message(Type(), u) {}
RemoteUser *GetUser() const { return mData->Obj<RemoteUser>(2); }
END_MESSAGE
;

DECLARE_MESSAGE(RemoteUserUpdatedMsg, "remote_user_updated")
RemoteUserUpdatedMsg(RemoteUser *u) : Message(Type(), u) {}
END_MESSAGE
;

DECLARE_MESSAGE(LocalUserLeftMsg, "local_user_left")
LocalUserLeftMsg(LocalUser *u) : Message(Type(), u) {}
LocalUser *GetUser() const { return mData->Obj<LocalUser>(2); }
END_MESSAGE
;

DECLARE_MESSAGE(RemoteUserLeftMsg, "remote_user_left")
RemoteUserLeftMsg(RemoteUser *u) : Message(Type(), u) {}
RemoteUser *GetUser() const { return mData->Obj<RemoteUser>(2); }
END_MESSAGE
;

DECLARE_MESSAGE(RemoteLeaderLeftMsg, "remote_leader_left_msg")
RemoteLeaderLeftMsg() : Message(Type()) {}
END_MESSAGE
;

DECLARE_MESSAGE(UserLoginMsg, "user_login")
UserLoginMsg() : Message(Type()) {}
END_MESSAGE
;

DECLARE_MESSAGE(AddUserResultMsg, "add_user_result")
AddUserResultMsg(int i) : Message(Type(), i) {}
AddUserResultMsg(int i, User *u) : Message(Type(), i, u) {}
int GetResult() const { return mData->Int(2); }
END_MESSAGE
;
