#pragma once
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/GameMic.h"
#include "game/UISyncNetMsgs.h"
#include "meta_band/BandMachine.h"
#include "meta_band/CharData.h"
#include "meta_band/Matchmaker.h"
#include "meta_band/OvershellSlotState.h"
#include "meta_band/SessionMgr.h"
#include "net/Server.h"
#include "obj/ObjMacros.h"
#include "os/JoypadMsgs.h"
#include "os/PlatformMgr.h"
#include "ui/UIComponent.h"
#include "ui/UIPanel.h"
#include "net/Synchronize.h"
#include "obj/Msg.h"
#include "math/Rand.h"
#include "meta_band/OvershellSlot.h"

class SessionMgr;
class BandUserMgr;

enum OvershellActiveStatus {
    kOvershellInactive = 0,
    kOvershellInShell = 1,
    kOvershellInGameShell = 2,
    kOvershellInSong = 3
};

class OvershellPanel : public UIPanel, public Synchronizable, public MsgSource {
public:
    OvershellPanel(SessionMgr * = nullptr, BandUserMgr * = nullptr);
    OBJ_CLASSNAME(OvershellPanel);
    OBJ_SET_TYPE(OvershellPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~OvershellPanel();
    virtual void Enter();
    virtual void Exit();
    virtual bool Exiting() const;
    virtual void Poll();
    virtual void FinishLoad();
    virtual void SyncSave(BinStream &, unsigned int) const;
    virtual void SyncLoad(BinStream &, unsigned int);
    virtual bool HasSyncPermission() const;
    virtual void OnSynchronized(unsigned int);

    bool CanGuitarPlayKeys() const;
    void UpdateAll();
    void EndOverrideFlow(OvershellOverrideFlow, bool);
    bool IsFinding() const;
    bool InSong() const;
    OvershellSlot *GetSlot(int);
    void BeginOverrideFlow(OvershellOverrideFlow);
    bool IsAnySlotEditingChar(CharData *) const;
    bool AreAllLocalSlotsAllowingInputToShell();
    void ClearSlots();
    OvershellSlot *FindSlotForUser(BandUser *);
    void SetActiveStatus(OvershellActiveStatus);
    bool InOverrideFlow(OvershellOverrideFlow);
    void SetSongOptionsRequired(bool);
    void SetInGame(bool);
    void SetAutohide(bool);
    void AddQueuedJoinUsers();
    void SetUseExtendedMicArrows(bool);
    void SetAllowsButtonPulse(bool);
    void AttemptToAddUser(LocalBandUser *);
    void QueueUserToJoin(LocalBandUser *);
    void RemoveUsersWithoutOnlinePrivilege();
    void RemoveUsersRequiringSongOptions();
    void ResolveReadyToPlayStates();
    void ResolvePartWaitStates();
    void AddSlot(OvershellSlot *, int);
    bool IsFull() const;
    OvershellSlot *GetSlot(BandUser *);
    OvershellSlot *FindSlotForRemoteUser(RemoteBandUser *);
    BandUser *GetPartRestrictedUser() const;
    TrackType GetPartRestriction() const;
    Difficulty GetMinimumDifficulty() const;
    bool AllSlotsReadyToPlay() const;
    bool ShouldPause() const;
    void SetBlockAllInput(bool);
    void RefreshJoinableUsers();
    void ResolveSlotStates();
    void CheckForControllerDisconnects();
    void AddJoinUserEntryToSlot(LocalBandUser *, OvershellSlot *);
    bool IsAnySlotAllowingInputToShell();
    BandUser *GetFirstUserAllowingInputToShell();
    bool IsAnyLocalSlotAllowingInputToShell();
    bool IsAnySlotJoinable() const;
    bool IsNonVocalistInVocalsSlot() const;
    bool IsAutoVocalsAllowed() const;
    void EnableAutoVocals();
    bool DoesAnySlotHaveChar(CharData *) const;
    void ResolveSignInWaitStates();
    void ResolveAutoSignInStates();
    bool ShouldSeeRealGuitarPrompt(LocalBandUser *, OvershellSlotStateID &);
    void ExportAll(const Message &);
    void SetPartRestrictedUser(BandUser *);
    void SetPartRestriction(TrackType);
    void SetMinimumDifficulty(Difficulty);
    void ClearTrackTypesFromUsers();
    void Update(OvershellSlot *);
    void LeaveOptions();

    bool InGame() const {
        return mActiveStatus == kOvershellInGameShell
            || mActiveStatus == kOvershellInSong;
    }
    bool SongOptionsRequired() const { return mSongOptionsRequired; }
    bool GetUseExtendedMicArrows() const { return mUseExtendedMicArrows; }

    DataNode SlotHandle(OvershellSlot *, const Message &);
    DataNode ExportButtonMsg(const Message &, BandUser *, bool);
    DataNode ExportToUser(const Message &, User *, UIComponent *);
    DataNode SlotHandle(PanelDir *, const Message &);
    DataNode OnUpdate(DataArray *);
    DataNode OnExportAll(DataArray *);

    DataNode OnMsg(const SessionReadyMsg &);
    DataNode OnMsg(const SessionDisconnectedMsg &);
    DataNode OnMsg(const JoypadConnectionMsg &);
    DataNode OnMsg(const GameMicsChangedMsg &);
    DataNode OnMsg(const MatchmakerChangedMsg &);
    DataNode OnMsg(const ServerStatusChangedMsg &);
    DataNode OnMsg(const ConnectionStatusChangedMsg &);
    DataNode OnMsg(const NetStartUtilityFinishedMsg &);
    DataNode OnMsg(const ButtonDownMsg &);
    DataNode OnMsg(const ButtonUpMsg &);
    DataNode OnMsg(const UIComponentScrollMsg &);
    DataNode OnMsg(const UIComponentSelectMsg &);
    DataNode OnMsg(const UIComponentSelectDoneMsg &);
    DataNode OnMsg(const UIComponentFocusChangeMsg &);
    DataNode OnMsg(const UITransitionCompleteMsg &);
    DataNode OnMsg(const NetComponentSelectMsg &);
    DataNode OnMsg(const NetComponentScrollMsg &);
    DataNode OnMsg(const RemoteUserLeftMsg &);
    DataNode OnMsg(const RemoteMachineUpdatedMsg &);
    DataNode OnMsg(const RemoteUserUpdatedMsg &);
    DataNode OnMsg(const NewRemoteUserMsg &);
    DataNode OnMsg(const SigninChangedMsg &);
    DataNode OnMsg(const PartyMembersChangedMsg &);
    DataNode OnMsg(const InviteReceivedMsg &);
    DataNode OnMsg(const InviteExpiredMsg &);
    DataNode OnMsg(const UserNameNewlyProfaneMsg &);
    DataNode OnMsg(const SessionBusyMsg &);

    NEW_OBJ(OvershellPanel);
    static void Init();
    static void Register() { REGISTER_OBJ_FACTORY(OvershellPanel); }

    std::vector<OvershellSlot *> mSlots; // 0x70
    std::vector<int> mSlotPriorities; // 0x78
    OvershellOverrideFlow mPanelOverrideFlow; // 0x80
    OvershellActiveStatus mActiveStatus; // 0x84
    bool mSongOptionsRequired; // 0x88
    bool mUseExtendedMicArrows; // 0x89
    bool mAllowsButtonPulse; // 0x8a
    std::vector<LocalBandUser *> mQueuedJoinUsers; // 0x8c
    SessionMgr *mSessionMgr; // 0x94
    BandUserMgr *mBandUserMgr; // 0x98
    BandUser *mPartRestrictedUser; // 0x9c
    TrackType mPartRestriction; // 0xa0
    Difficulty mMinimumDifficulty; // 0xa4
    Rand mPartResolver; // 0xa8
    int mPartResolverSeed; // 0x4b8
    bool mAllowRealGuitarFlow; // 0x4bc
    std::vector<u64> unk4c0;
    bool unk4c8;
    int unk4cc;
};

DECLARE_MESSAGE(NewOvershellLocalUserMsg, "new_overshell_local_user_msg")
NewOvershellLocalUserMsg(LocalBandUser *);
LocalBandUser *GetBandUser() const;
END_MESSAGE

DECLARE_MESSAGE(OvershellAllowingInputChangedMsg, "overshell_allowing_input_changed_msg");
OvershellAllowingInputChangedMsg(BandUser *);
END_MESSAGE

DECLARE_MESSAGE(OvershellActiveStatusChangedMsg, "overshell_active_status_changed_msg");
OvershellActiveStatusChangedMsg() : Message(Type()) {}
END_MESSAGE

DECLARE_MESSAGE(OvershellOverrideEndedMsg, "override_ended")
OvershellOverrideEndedMsg(OvershellOverrideFlow, bool);
OvershellOverrideFlow GetOverrideFlowType() const;
bool Cancelled() const;
END_MESSAGE