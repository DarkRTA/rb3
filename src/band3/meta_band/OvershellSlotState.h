#pragma once
#include "obj/Object.h"
#include "obj/Msg.h"

class OvershellSlot;

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
    kState_ChoosePart = 10,
    kState_ChoosePartWait = 11,
    kState_ChooseDiff = 12,
    kState_SongOptionsCancel = 13,
    kState_ReadyToPlay = 14,
    kState_ReadyToPlayWait = 15,
    kState_AutoSignInSony = 16,
    kState_SignInSonyPrivilegeDenial = 17,
    kState_AutoSignInRockCentral = 18,
    kState_SignInToRegister = 19,
    kState_SignInWait = 20,
    kState_RegisteringOnline = 21,
    kState_SignInFailRetry = 22,
    kState_EnterCalibration = 23,
    kState_EnterCharCreator = 24,
    kState_DisconnectConfirm = 25,
    kState_RemoveUserDisconnectConfirm = 26,
    kState_KickUsers = 27,
    kState_MuteUsers = 28,
    kState_GamercardUsers = 29,
    kState_InviteFriends = 30,
    kState_ChooseProfile = 31,
    kState_ChooseProfileConfirm = 32,
    kState_OptionsEndGame = 33,
    kState_Modifiers = 34,
    kState_AutoVocalsDenial = 35,
    kState_RegisterOnlineDenial = 36,
    kState_OptionsDrumInSongSettings = 37,
    kState_OptionsDrumMessage = 38,
    kState_OptionsDrum = 39,
    kState_ChooseDiffConfirm = 40,
    kState_KickConfirmation = 41,
    kState_OptionsAVSettings = 42,
    kState_OptionsAudio = 43,
    kState_OptionsVocal = 44,
    kState_OptionsExtras = 45,
    kState_ModifierUnlock = 46,
    kState_LinkingCode = 47,
    kState_CharCreatorDenial = 48,
    kState_CalibrationDenial = 49,
    kState_ReconnectController = 50,
    kState_CharCreatorDenialNoProfile = 51,
    kState_CharCreatorDenialMaxChars = 52,
    kState_ChooseCharEdit = 53,
    kState_ChooseCharDelete = 54,
    kState_FirstTimeRG = 55,
    kState_SecondTimeRG = 56,
    kState_NoJoinInGame = 57,
    kState_LinkingCodeError = 58,
    kState_EnterCredits = 59,
    kState_CreditsDenial = 60,
    kState_RemoveUserDenial = 61,
    kState_SaveloadManagerNotIdle = 62,
    kState_ModifiersDrumWarning = 63,
    kState_ChooseContribute = 64,
    kState_RemoveCriticalUserConfirm = 65,
    kState_ChooseCharDeleteDenial = 66,
    kState_ToggleNoFailDenial = 67,
    kState_ChoosePartDenial = 68,
    kState_SaveloadManagerNotMeta = 69,
    kState_SignInToRegisterNoResolve = 70,
    kState_SaveloadManagerAutosaveConfirm = 71,
    kState_InviteFriendsDenial = 72,
    kState_ChooseCharDenial = 73,
    kState_ModifierDelayedEffect = 74,
    kState_QuitEarlyConfirm = 75,
    kState_SkipSongConfirm = 76,
    kState_RemoveUserInSongConfirm = 77,
    kState_ChoosePartWarn = 78,
    kState_RestartConfirm = 79,
    kState_NotBattlePartWarn = 80,
    kState_AuditionNoHardDriveConfirm = 81,
    kState_AuditionNoMembershipConfirm = 82,
    kState_AuditionNoRockCentral = 83,
    kState_AuditionEnterConfirm = 84,
    kState_AuditionDenialRemotePlayers = 85,
    kState_EnterWiiSpeakOptions = 128,
    kState_WaitWii = 129,
    kState_WiiProfileOptions = 130,
    kState_WiiProfileList = 131,
    kState_WiiProfileConfirm = 132,
    kState_WiiProfileRemoveUserConfirm = 133,
    kState_WiiProfileListEmpty = 134,
    kState_WiiProfileFail = 135,
    kState_WiiProfileFailBusy = 136,
    kState_WiiProfileFailCreate = 137,
    kState_WiiProfileSwapFail = 138,
    kState_AutoSignInNintendo = 139,
    kState_ChooseInvitation = 140,
    kState_AcceptInvitation = 141,
    kState_NoInvitations = 142,
    kState_WiiProfilePreconfirm = 143,
    kState_WiiProfileSwitchConfirm = 144,
    kState_WiiProfilePostAction = 145,
    kState_OptionsWiiSpeak = 146,
    kState_EnterWiiProfile = 201,
    kState_WiiProfileGuestConfirm = 202,
    kState_RemoveUserInCampaignConfirm = 203,
    kState_RegisterWiiProfile = 204,
    kState_WiiProfileDenial = 205,
    kState_RegisterWiiProfileDenial = 206
};

class OvershellSlotState : public Hmx::Object {
public:
    OvershellSlotState(DataArray *, OvershellSlot *);
    virtual ~OvershellSlotState() {}

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

    DataNode HandleMsg(const Message &);

    OvershellSlotStateID mStateID; // 0x1c
    OvershellSlot *mSlot; // 0x20
};

class OvershellSlotStateMgr {
public:
    OvershellSlotStateMgr();
    ~OvershellSlotStateMgr();
    void Init(DataArray *, OvershellSlot *);
    OvershellSlotState *GetSlotState(OvershellSlotStateID);

    std::vector<OvershellSlotState *> mStates; // 0x0
};