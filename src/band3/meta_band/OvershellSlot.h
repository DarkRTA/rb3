#pragma once
#include "obj/Object.h"
#include "net_band/DataResults.h"
#include "game/BandUserMgr.h"
#include "game/BandUser.h"
#include "bandobj/OvershellDir.h"
#include "meta_band/SessionMgr.h"
#include "bandobj/BandLabel.h"

class OvershellPanel;
class OvershellSlotState;
class OvershellSlotStateMgr;
class PassiveMessageQueue;
class CharProvider;
class SessionUsersProvider;
class OvershellProfileProvider;
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

    OvershellSlotStateMgr* mStateMgr; // 0x1c
    OvershellSlotState* mState; // 0x20
    int unk24;
    int unk28;
    BandLabel* unk2c;
    OvershellPanel* mOvershell; // 0x30
    BandUserMgr* mBandUserMgr; // 0x34
    SessionMgr* mSessionMgr; // 0x38
    int mSlotNum; // 0x3c
    std::vector<ControllerType> unk40;
    std::vector<ControllerType> unk48;
    OvershellDir* mOvershellDir; // 0x50
    bool unk54;
    bool unk55;
    Symbol unk58;
    bool unk5c;
    bool mInGame; // 0x5d
    bool unk5e;
    std::vector<PotentialUserEntry> mPotentialUsers; // 0x60
    DataResultList mLinkingCodeResultList; // 0x68
    bool unk80;
    bool unk81;
    int unk84;
    unsigned int unk88;
    PassiveMessageQueue* mMessageQueue; // 0x8c
    OvershellOverrideFlow unk90;
    CharProvider* mCharProvider; // 0x94
    SessionUsersProvider* unk98;
    SessionUsersProvider* unk9c;
    OvershellProfileProvider* mSwappableProfilesProvider; // 0xa0
    OvershellPartSelectProvider* mPartSelectProvider; // 0xa4
    CymbalSelectionProvider* mCymbalProvider; // 0xa8
};