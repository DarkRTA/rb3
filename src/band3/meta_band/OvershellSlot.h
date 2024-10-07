#pragma once
#include "obj/Object.h"
#include "net_band/DataResults.h"
#include "game/BandUserMgr.h"
#include "game/BandUser.h"
#include "bandobj/OvershellDir.h"
#include "meta_band/SessionMgr.h"
#include "bandobj/BandLabel.h"
#include "meta_band/OvershellProfileProvider.h"

class OvershellPanel;
class OvershellSlotState;
class OvershellSlotStateMgr;
class PassiveMessageQueue;
class CharProvider;
class SessionUsersProvider;
class OvershellPartSelectProvider;
class CymbalSelectionProvider;

enum JoinState {
    kMetaJoinNeedsOnline = 0,
    kMetaJoinOK = 1,
    kMetaJoinNeedsMic = 2
};

class PotentialUserEntry {
public:
    LocalBandUser* mUser; // 0x0
    JoinState mJoinState; // 0x4
};

enum OvershellOverrideFlow {
    kOverrideFlow_None = 0,
    kOverrideFlow_SongSettings = 1,
    kOverrideFlow_RegisterOnline = 2
};

class OvershellSlot : public Hmx::Object {
public:
    OvershellSlot(int, OvershellPanel*, OvershellDir*, BandUserMgr*, SessionMgr*);
    virtual ~OvershellSlot();
    virtual DataNode Handle(DataArray*, bool);
    virtual void SetTypeDef(DataArray*);
    virtual class ObjectDir* DataDir();

    void Enter();
    void Poll();
    int GetSlotNum();
    PanelDir* GetPanelDir();
    bool IsHidden() const;
    bool IsLeavingOptions() const;
    Symbol GetCurrentView() const;
    bool InOverrideFlow(OvershellOverrideFlow) const;
    void ClearPotentialUsers();
    void AddPotentialUser(PotentialUserEntry);
    int NumPotentialUsers() const;
    bool LookupUserInJoinList(const LocalBandUser*, JoinState*);
    bool IsValidControllerType(ControllerType);
    BandUser* GetUser() const;
    OvershellSlotState* GetState();
    void ShowState(OvershellSlotStateID);
    void LeaveOptions();
    bool InGame() const;
    void SelectPart(TrackType);
    void SelectPartImpl(TrackType, bool, bool);
    void SelectVocalPart(bool);
    void SelectDrumPart(bool);
    void ToggleCymbal(Symbol);
    bool IsCymbalSelected(Symbol);
    void FinishCymbalSelect(bool);
    void DismissCymbalMessage();
    void LeaveDifficultyConfirmation();
    void LeaveChoosePart();
    void CancelSongSettings();
    void LeaveChoosePartWait();
    void LeaveChooseDifficulty();
    void SetOverrideFlowReturnState(OvershellSlotStateID);
    void EndOverrideFlow(OvershellOverrideFlow, bool);
    void AttemptRemoveUser();
    void LeaveReadyToPlay();
    void LeaveSignInWait();
    void ShowEnterWiiSpeakOptions();
    void ShowEnterWiiProfile();
    void AttemptDisconnect();
    void ShowChordBook();
    void PracticeNewSection();
    void ToggleMetronome();
    void KickUser(int);
    void ConfirmKick();
    void LeaveKickConfirmation();
    void GenerateCurrentState();
    void RemoveUser();
    void ToggleMuteUser(int);
    void SelectDifficulty(Difficulty);
    void ShowSongOptions();
    void ActOnUserProfile(int);
    void HandleWiiProfileActResult(WiiProfileActResult);
    void ActOnUserProfileConfirm();
    void ShowWiiProfileConfirm();
    void ShowWiiProfilePreconfirm();
    void ShowWiiProfileSwitchConfirm();
    void ShowWiiProfileFail();
    void ShowWiiProfileFailBusy();
    void ShowWiiProfileFailCreate();
    void ShowWiiProfilePostAction();
    void AttemptSwapUserProfile(int);
    void SelectGuestProfile();
    void ShowWiiProfileSwapFail();
    void SetWiiProfileListMode(int, bool);
    OvershellProfileProvider::WiiProfileListMode GetWiiProfileListMode();
    int GetWiiProfileLastIndex();
    void ShowWiiProfileList(int);
    void ShowWiiProfileOptions();
    void ShowWaitWii();
    void LeaveWaitWii();
    void ShowWiiProfileSelector(bool);
    void CancelWiiProfileSelector();
    void FetchLinkingCode();
    void ToggleVocalStyle();
    void Update();
    void ToggleLeftyFlip();
    void ResetSlotCamera();
    void EnableAutohide(bool);
    void SetBlockAllInput(bool);
    void SetInGame(bool);
    void SetInTrackMode(bool);
    void SetView(Symbol);
    void RevertToOverrideFlowReturnState();
    bool IsQuitToken(Symbol) const;
    void BeginOverrideFlow(OvershellOverrideFlow, bool);
    void SetOverrideType(OvershellOverrideFlow, bool);
    void UpdateState();
    void UpdateView();
    void CheckViewOverride(Symbol, bool, Symbol&);
    void UpdateMuteUsersList();
    void UpdateKickUsersList();
    void UpdateProfilesList();
    void UpdatePartSelectList();

    OvershellSlotStateMgr* mStateMgr; // 0x1c
    OvershellSlotState* mState; // 0x20
    OvershellSlotStateID mOverrideFlowReturnState; // 0x24
    int unk28; // 0x28 - OvershellSlotStateID
    BandLabel* mUserNameLabel; // 0x2c
    OvershellPanel* mOvershell; // 0x30
    BandUserMgr* mBandUserMgr; // 0x34
    SessionMgr* mSessionMgr; // 0x38
    int mSlotNum; // 0x3c
    std::vector<ControllerType> unk40;
    std::vector<ControllerType> unk48;
    OvershellDir* mOvershellDir; // 0x50
    bool mAutohideEnabled; // 0x54
    bool mIsLeavingOptions; // 0x55
    Symbol mCurrentView; // 0x58
    bool mBlockAllInput; // 0x5c
    bool mInGame; // 0x5d
    bool mSongOptionsRequired; // 0x5e
    std::vector<PotentialUserEntry> mPotentialUsers; // 0x60
    DataResultList mLinkingCodeResultList; // 0x68
    bool unk80;
    bool unk81;
    int mCharForEdit; // 0x84 - TourCharLocal*
    unsigned int mCymbalConfiguration; // 0x88
    PassiveMessageQueue* mMessageQueue; // 0x8c
    OvershellOverrideFlow mSlotOverrideFlow; // 0x90
    CharProvider* mCharProvider; // 0x94
    SessionUsersProvider* mKickUsersProvider; // 0x98
    SessionUsersProvider* mMuteUsersProvider; // 0x9c
    OvershellProfileProvider* mSwappableProfilesProvider; // 0xa0
    OvershellPartSelectProvider* mPartSelectProvider; // 0xa4
    CymbalSelectionProvider* mCymbalProvider; // 0xa8
};