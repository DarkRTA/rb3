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