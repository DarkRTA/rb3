#pragma once
#include "obj/Object.h"
#include "obj/Msg.h"

class OvershellSlot;

// #define kState_NoInstrument
// (0)
// #define kState_Join
// (1)
// #define kState_SignIn
// (2)
// #define kState_ConnectMic
// (3)
// #define kState_Finding
// (4)
// #define kState_JoinedDefault
// (5)
// #define kState_ChooseChar
// (6)
// #define kState_Options
// (7)
// #define kState_OnlineOptions
// (8)
// #define kState_GameOptions
// (9)
// #define kState_ChoosePart
// (10)
// #define kState_ChoosePartWait
// (11)
// #define kState_ChooseDiff
// (12)
// #define kState_SongOptionsCancel
// (13)
// #define kState_ReadyToPlay
// (14)
// #define kState_ReadyToPlayWait
// (15)
// #define kState_AutoSignInSony
// (16)
// #define kState_SignInSonyPrivilegeDenial
// (17)
// #define kState_AutoSignInRockCentral
// (18)
// #define kState_SignInToRegister
// (19)
// #define kState_SignInWait
// (20)
// #define kState_RegisteringOnline
// (21)
// #define kState_SignInFailRetry
// (22)
// #define kState_EnterCalibration
// (23)
// #define kState_EnterCharCreator
// (24)
// #define kState_DisconnectConfirm
// (25)
// #define kState_RemoveUserDisconnectConfirm
// (26)
// #define kState_KickUsers
// (27)
// #define kState_MuteUsers
// (28)
// #define kState_GamercardUsers
// (29)
// #define kState_InviteFriends
// (30)
// #define kState_ChooseProfile
// (31)
// #define kState_ChooseProfileConfirm
// (32)
// #define kState_OptionsEndGame
// (33)
// #define kState_Modifiers
// (34)
// #define kState_AutoVocalsDenial
// (35)
// #define kState_RegisterOnlineDenial
// (36)
// #define kState_OptionsDrumInSongSettings
// (37)
// #define kState_OptionsDrumMessage
// (38)
// #define kState_OptionsDrum
// (39)
// #define kState_ChooseDiffConfirm
// (40)
// #define kState_KickConfirmation
// (41)
// #define kState_OptionsAVSettings
// (42)
// #define kState_OptionsAudio
// (43)
// #define kState_OptionsVocal
// (44)
// #define kState_OptionsExtras
// (45)
// #define kState_ModifierUnlock
// (46)
// #define kState_LinkingCode
// (47)
// #define kState_CharCreatorDenial
// (48)
// #define kState_CalibrationDenial
// (49)
// #define kState_ReconnectController
// (50)
// #define kState_CharCreatorDenialNoProfile
// (51)
// #define kState_CharCreatorDenialMaxChars
// (52)
// #define kState_ChooseCharEdit
// (53)
// #define kState_ChooseCharDelete
// (54)
// #define kState_FirstTimeRG
// (55)
// #define kState_SecondTimeRG
// (56)
// #define kState_NoJoinInGame
// (57)
// #define kState_LinkingCodeError
// (58)
// #define kState_EnterCredits
// (59)
// #define kState_CreditsDenial
// (60)
// #define kState_RemoveUserDenial
// (61)
// #define kState_SaveloadManagerNotIdle
// (62)
// #define kState_ModifiersDrumWarning
// (63)
// #define kState_ChooseContribute
// (64)
// #define kState_RemoveCriticalUserConfirm
// (65)
// #define kState_ChooseCharDeleteDenial
// (66)
// #define kState_ToggleNoFailDenial
// (67)
// #define kState_ChoosePartDenial
// (68)
// #define kState_SaveloadManagerNotMeta
// (69)
// #define kState_SignInToRegisterNoResolve
// (70)
// #define kState_SaveloadManagerAutosaveConfirm
// (71)
// #define kState_InviteFriendsDenial
// (72)
// #define kState_ChooseCharDenial
// (73)
// #define kState_ModifierDelayedEffect
// (74)
// #define kState_QuitEarlyConfirm
// (75)
// #define kState_SkipSongConfirm
// (76)
// #define kState_RemoveUserInSongConfirm
// (77)
// #define kState_ChoosePartWarn
// (78)
// #define kState_RestartConfirm
// (79)
// #define kState_NotBattlePartWarn
// (80)
// #define kState_AuditionNoHardDriveConfirm
// (81)
// #define kState_AuditionNoMembershipConfirm
// (82)
// #define kState_AuditionNoRockCentral
// (83)
// #define kState_AuditionEnterConfirm
// (84)
// #define kState_AuditionDenialRemotePlayers
// (85)
// #define kState_EnterWiiSpeakOptions
// (128)
// #define kState_WaitWii
// (129)
// #define kState_WiiProfileOptions
// (130)
// #define kState_WiiProfileList
// (131)
// #define kState_WiiProfileConfirm
// (132)
// #define kState_WiiProfileRemoveUserConfirm
// (133)
// #define kState_WiiProfileListEmpty
// (134)
// #define kState_WiiProfileFail
// (135)
// #define kState_WiiProfileFailBusy
// (136)
// #define kState_WiiProfileFailCreate
// (137)
// #define kState_WiiProfileSwapFail
// (138)
// #define kState_AutoSignInNintendo
// (139)
// #define kState_ChooseInvitation
// (140)
// #define kState_AcceptInvitation
// (141)
// #define kState_NoInvitations
// (142)
// #define kState_WiiProfilePreconfirm
// (143)
// #define kState_WiiProfileSwitchConfirm
// (144)
// #define kState_WiiProfilePostAction
// (145)
// #define kState_OptionsWiiSpeak
// (146)
// #define kState_EnterWiiProfile
// (201)
// #define kState_WiiProfileGuestConfirm
// (202)
// #define kState_RemoveUserInCampaignConfirm
// (203)
// #define kState_RegisterWiiProfile
// (204)
// #define kState_WiiProfileDenial
// (205)
// #define kState_RegisterWiiProfileDenial
// (206)

enum OvershellSlotStateID {
    kState_NoInstrument = 0,
    kState_Join = 1,
    kState_SignIn = 2,
    kState_ConnectMic = 3,
    kState_Finding = 4,
    kState_JoinedDefault = 5,
    kState_ChooseChar = 6,
    kState_Options = 7,
    kState_OnlineOptions = 8,
    kState_GameOptions = 9,
    kState_ChoosePart = 0xa,
    kState_ChoosePartWait = 0xb,
    kState_ChooseDiff = 0xc,
    kState_SongOptionsCancel = 0xd,
    kState_ReadyToPlay = 0xe,
    kState_ReadyToPlayWait = 0xf,
    kState_AutoSignInSony = 0x10,
    kState_SignInSonyPrivilegeDenial = 0x11,
    kState_AutoSignInRockCentral = 0x12,
    kState_SignInToRegister = 0x13,
    kState_SignInWait = 0x14,
    kState_RegisteringOnline = 0x15,
    kState_SignInFailRetry = 0x16,
    kState_EnterCalibration = 0x17,
    kState_EnterCharCreator = 0x18,
    kState_DisconnectConfirm = 0x19,
    kState_RemoveUserConfirm = 0x1a,
    kState_KickUsers = 0x1b,
    kState_MuteUsers = 0x1c,
    kState_GamercardUsers = 0x1d,
    kState_InviteFriends = 0x1e,
    kState_ChooseProfile = 0x1f,
    kState_ChooseProfileConfirm = 0x20,
    kState_OptionsEndGame = 0x21,
    kState_Modifiers = 0x22,
    kState_AutoVocalsDenial = 0x23,
    kState_RegisterOnlineDenial = 0x24,
    kState_OptionsDrumInSongSettings = 0x25,
    kState_OptionsDrumMessage = 0x26,
    kState_OptionsDrum = 0x27,
    kState_ChooseDiffConfirm = 0x28,
    kState_KickConfirmation = 0x29,
    kState_OptionsAVSettings = 0x2a,
    kState_OptionsAudio = 0x2b,
    kState_OptionsVocal = 0x2c,
    kState_OptionsExtras = 0x2d,
    kState_ModifierUnlock = 0x2e,
    kState_OptionsSystem = 0x2f,
    kState_LinkingCode = 0x2f,
    kState_CharCreatorDenial = 0x31,
    kState_CalibrationDenial = 0x32,
    kState_ReconnectController = 0x33,
    kState_CharCreatorDenialNoProfile = 0x34,
    kState_ChooseCharEdit = 0x35,
    kState_ChooseCharDelete = 0x36,
    kState_FirstTimeRG = 0x37,
    kState_EnterWiiSpeakOptions = 0x80,
    kState_WaitWii = 0x81,
    kState_WiiProfileOptions = 0x82,
    kState_WiiProfileList = 0x83,
    kState_WiiProfileConfirm = 0x84,
    kState_WiiProfileRemoveUserConfirm = 0x85,
    kState_WiiProfileListEmpty = 0x86,
    kState_WiiProfileFail = 0x87,
    kState_AutoSignInNintendo = 0x88,
    kState_ChooseInvitation = 0x89,
    kState_AcceptInvitation = 0x8a,
    kState_NoInvitations = 0x8b,
    kState_WiiPreventOverrideStart = 0xc8,
    kState_EnterWiiProfile = 0xc9,
    kState_WiiProfileGuestConfirm = 0xca,
    kState_WiiProfileEditLogo = 0xcb
};

class OvershellSlotState : public Hmx::Object {
public:
    OvershellSlotState(DataArray*, OvershellSlot*);
    virtual ~OvershellSlotState(){}

    OvershellSlotStateID GetStateID() const;
    Symbol GetView();
    void UpdateView();
    bool UsesRemoteStatusView();
    Symbol GetRemoteStatus();
    bool AllowsInputToShell();
    bool PreventsOverride();
    bool RequiresOnlineSession();
    bool AllowsHiding();
    bool RequiresRemoteUsers();
    bool RetractedPosition();
    bool ShowsExtendedMicArrows();
    bool InSongSettingsFlow();
    bool IsPartUnresolved();
    bool InRegisterOnlineFlow();
    bool InChooseCharFlow();
    bool InCharEditFlow();
    bool IsRemoveUserPrompt();
    bool IsReadyToPlay();

    DataNode HandleMsg(const Message&);

    OvershellSlotStateID mStateID; // 0x1c
    OvershellSlot* mSlot; // 0x20
};

class OvershellSlotStateMgr {
public:
    OvershellSlotStateMgr();
    ~OvershellSlotStateMgr();
    void Init(DataArray*, OvershellSlot*);
    OvershellSlotState* GetSlotState(OvershellSlotStateID);

    std::vector<OvershellSlotState*> mStates; // 0x0
};