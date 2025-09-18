#pragma once
#include "obj/Msg.h"
#include "os/ContentMgr.h"
#include "os/JoypadMsgs.h"
#include "os/HomeMenu_Wii.h"
#include "os/DiscErrorMgr_Wii.h"
#include "os/Friend.h"
#include "utl/MemStream.h"

class OnlineID; // forward dec
class LocalUser;

enum DiskError {
    kNoDiskError,
    kDiskError,
    kWrongDisk,
    kFailedChecksum
};

enum PlatformRegion {
    kRegionNone,
    kRegionNA,
    kRegionEurope,
    kRegionJapan,
    kNumRegions
};

enum NotifyLocation {
    kNotify0,
    kNotify1,
    kNotify2
};

enum QuitType {
    kQuitNone,
    kQuitShutdown,
    kQuitRestart,
    kQuitMenu,
    kQuitDataManager
};

typedef bool EnumerateFriendsCallbackFunc(int, std::vector<Friend *> &, Hmx::Object *);
typedef bool SendMsgCallbackFunc(Friend *, const char *, const char *, MemStream &);
typedef bool SignInUserCallbackFunc(User *, unsigned long);

class PlatformMgr : public MsgSource, public ContentMgr::Callback {
public:
    PlatformMgr();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~PlatformMgr();
    virtual void ContentStarted();
    virtual void ContentDone();
    virtual void ContentCancelled();

    void SetDiskError(DiskError);
    void GetOnlineID(int, OnlineID *) const;
    const char *GetName(int) const;
    bool IsSignedIn(int) const;
    bool IsUserSignedIn(const LocalUser *) const;
    bool HasUserSigninChanged(const LocalUser *) const;
    bool IsUserSignedIntoLive(const LocalUser *) const;
    bool UserHasOnlinePrivilege(const LocalUser *) const;
    bool IsUserAGuest(const LocalUser *) const;
    bool IsAnyUserSignedIntoLive() const;
    bool HasOnlinePrivilege(int) const;
    bool IsSignedIntoLive(int) const;
    PlatformRegion GetRegion() const;
    void SetRegion(PlatformRegion);
    DataNode OnSignInUsers(const DataArray *);
    void SetScreenSaver(bool);
    void RunNetStartUtility();
    void SetNotifyUILocation(NotifyLocation);
    int GetLastDWCError();
    String GetNetErrorString(bool);
    DataArrayPtr GetNetErrorStringAsDataArray(bool);
    void ClearNetError();
    void ClearDWCError();
    bool CanSeeUserCreatedContent(const OnlineID *) const;
    void SystemInitPowerCallbacks();
    void WiiPoll();
    void SystemCheckShutdown();

    bool IsUserAWiiGuest(const LocalUser *) const;
    int InitNintendoConnection();
    void CloseNintendoConnection(bool, bool);
    void InitSOLibrary(bool);
    void EnableProfanity(bool);
    int GetLastNHTTPError();
    void SetConnected(bool);
    void SetPartyMicOptionsShowing(bool);
    int GetLastDNSError();
    void SetHomeMenuEnabled(bool);
    void PrintParentalPin();
    bool StartProfanity(const char *, Hmx::Object *);
    bool IsEthernetCableConnected();
    void PreInit();
    void RegionInit();
    void Init();
    void UpdateSigninState();
    void SetUserSignedIn(int);
    void SetUserSignedOut(int);
    void RegisterEnumerateFriendsCallback(EnumerateFriendsCallbackFunc *);
    void RegisterSendMsgCallback(SendMsgCallbackFunc *);
    void RegisterSignInserCallback(SignInUserCallbackFunc *);
    void InitDWCLibrary();
    bool StartDNSLookup(const char *);
    bool CheckDNSLookup(String &);
    void KillDNSLookup();
    void UpdateDWCLibrary();
    void TerminateDWCLibrary();
    void HandleDWCError();
    void EnumerateFriends(int, std::vector<Friend *> &, Hmx::Object *);
    void SendMsg(Friend *, const char *, const char *, MemStream &);
    bool IsPadAGuest(int) const;
    bool IsGuestOnlineID(const OnlineID *) const;
    bool StartProfanity(const unsigned short **, int, char *, Hmx::Object *);
    bool CheckProfanity(bool &, bool &);
    void HandleNetError(int, Symbol);
    bool IsShuttingDown();
    void WiiShutdown(QuitType type);
    void HandleNANDCorruptError();

    bool OnMsg(const ButtonDownMsg &);
    bool OnMsg(const ButtonUpMsg &);

    bool IsConnected() const { return mConnected; }
    int SigninMask() const { return mSigninMask; }
    int SigninChangedMask() const { return mSigninChangeMask; }
    bool HasNetError() { return mHasNetError; }
    bool IsOnlineRestricted() { return mIsOnlineRestricted; }
    void RelaxOnlineRestriction() { mIsOnlineRestricted = false; }
    void SetIsRestarting(bool b) { mIsRestarting = b; }
    bool HomeMenuActive() { return mHomeMenuWii->mHomeMenuActive; }
    void EnableSFX(bool b) { mEnableSFX = b; }
    bool AreSFXEnabled() { return mEnableSFX; }
    void IgnoreWiiSpeakFriends() { unkce5a = true; }
    DiscErrorMgrWii *GetDiscErrorMgrWii() const { return mDiscErrorMgr; }
    bool IsGuideShowing() const { return mGuideShowing; }
    bool IsCheckingProfanity() const { return mCheckingProfanity; }

    LocalUser *GetOwnerUserOfGuestUser(LocalUser *);
    int GetOwnerOfGuest(int) const;
    void Draw();
    void Poll();
    void InitGQR();

    static void *DWCStartupThreadFunc(void *);

    int mSigninMask; // 0x20
    int mSigninChangeMask; // 0x24
    bool mGuideShowing; // 0x28
    bool mConnected; // 0x29
    bool unk2a; // 0x2a
    bool mScreenSaver; // 0x2b
    PlatformRegion mRegion; // 0x2c
    DiskError mDiskError; // 0x30
    int unk34; // 0x34
    Timer mTimer; // 0x38
    bool unk68; // 0x68
    bool unk69; // 0x69
    bool unk6a; // 0x6a
    bool unk6b; // 0x6b
    bool unk6c; // 0x6c
    bool unk6d; // 0x6d
    int unk70; // 0x70
    bool mEthernetCableConnected; // 0x74

    char filler[0x432b];

    bool unk43a0;
    bool unk43a1;
    bool unk43a2;
    bool unk43a3;
    int unk43a4;
    OSThread mThread; // 0x43a8
    char filler43a4[0x4000]; // 0x46c0

    int mHasNetError; // 0x86c0
    Symbol mNetError; // 0x86c4

    char filler86c8[0x4018];

    String mDNSResult; // 0xc6e0
    String unkc6ec;
    OSThread mDNSThread; // 0xc6f0
    bool mCheckingProfanity; // 0xca10
    bool unkca11;
    bool mProfanityAllowed; // 0xca12
    Hmx::Object *unkca14; // 0xca14
    const unsigned short *mProfaneWord; // 0xca18
    unsigned short mProfaneChars[501]; // 0xca1c
    char mProfaneResults[50]; // 0xce06
    int unkce38; // 0xce38
    int mProfaneWordCount; // 0xce3c
    int unkce40; // 0xce40
    bool mDisabling; // 0xce44
    HomeMenu *mHomeMenuWii; // 0xce48
    char mHomeMenuDisabled; // 0xce4c
    DiscErrorMgrWii *mDiscErrorMgr; // 0xce50
    bool mStorageChanged; // 0xce54
    bool mNetworkPlay; // 0xce55
    bool unkce56;
    bool mIsRestarting; // 0xce57
    bool mPartyMicAllowed; // 0xce58
    bool mEnableSFX;
    bool unkce5a;
    EnumerateFriendsCallbackFunc *mEnumerateFriendsCallback; // 0xce5c
    SendMsgCallbackFunc *mSendMsgCallback; // 0xce60
    SignInUserCallbackFunc *mSignInUserCallback; // 0xce64
    bool mIsOnlineRestricted; // 0xce68
    bool unkce69;
    bool mIgnorePowerOperations;
    bool unkce6b; // checked in Utl's MaxAllowedHmxMaturityLevel, need to come up with a
                  // better name
} __attribute__((aligned(32)));

Symbol PlatformRegionToSymbol(PlatformRegion);
PlatformRegion SymbolToPlatformRegion(Symbol);

extern PlatformMgr ThePlatformMgr;

DECLARE_MESSAGE(PlatformMgrOpCompleteMsg, "platform_mgr_op_complete")
PlatformMgrOpCompleteMsg(int i) : Message(Type(), i) {}
bool Success() const { return mData->Int(2); }
END_MESSAGE

DECLARE_MESSAGE(DiskErrorMsg, "disk_error")
// arg here is a bool
END_MESSAGE

DECLARE_MESSAGE(DWCProfanityResultMsg, "dwc_profanity_result_msg")
bool Success() const { return mData->Int(2); }
END_MESSAGE

DECLARE_MESSAGE(FriendsListChangedMsg, "friends_list_changed")
int GetPadNum() const { return mData->Int(2); }
END_MESSAGE

DECLARE_MESSAGE(PartyMembersChangedMsg, "party_members_changed")
END_MESSAGE

DECLARE_MESSAGE(EnumerateMessagesCompleteMsg, "enumerate_messages_complete")
END_MESSAGE

DECLARE_MESSAGE(WiiDiscErrorMsg, "wii_disc_error")
END_MESSAGE