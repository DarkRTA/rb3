#ifndef OS_PLATFORMMGR_H
#define OS_PLATFORMMGR_H
#include "obj/MsgSource.h"
#include "os/ContentMgr.h"
#include "os/JoypadMsgs.h"
#include "os/HomeMenu_Wii.h"
#include "os/DiscErrorMgr_Wii.h"

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
    i, d, k
};

class PlatformMgr : public MsgSource, ContentMgr::Callback {
public:
    PlatformMgr();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~PlatformMgr();
    virtual void ContentStarted();
    virtual void ContentDone();
    virtual void ContentCancelled();

    void SetDiskError(DiskError);
    void GetOnlineID(int, OnlineID*) const;
    const char* GetName(int) const;
    bool IsSignedIn(int) const;
    bool IsUserSignedIn(const LocalUser*) const;
    bool HasUserSigninChanged(const LocalUser*) const;
    bool IsUserSignedIntoLive(const LocalUser*) const;
    bool UserHasOnlinePrivilege(const LocalUser*) const;
    bool IsUserAGuest(const LocalUser*) const;
    bool IsAnyUserSignedIntoLive() const;
    bool HasOnlinePrivilege(int) const;
    bool IsSignedIntoLive(int) const;
    PlatformRegion GetRegion() const;
    void SetRegion(PlatformRegion);
    DataNode OnSignInUsers(const DataArray*);
    void SetScreenSaver(bool);
    void RunNetStartUtility();
    void SetNotifyUILocation(NotifyLocation);
    int GetLastDWCError();
    class String GetNetErrorString(bool);
    DataArrayPtr GetNetErrorStringAsDataArray(bool);
    void ClearNetError();
    void ClearDWCError();

    bool IsUserAWiiGuest(const LocalUser*) const;
    int InitNintendoConnection();
    void CloseNintendoConnection(bool, bool);
    void EnableProfanity(bool);
    int GetLastNHTTPError();
    void SetConnected(bool);
    void SetPartyMicOptionsShowing(bool);
    int GetLastDNSError();
    void SetHomeMenuEnabled(bool);
    void PrintParentalPin();
    void StartProfanity(const char*, Hmx::Object*);
    bool IsEthernetCableConnected();

    bool OnMsg(const ButtonDownMsg&);
    bool OnMsg(const ButtonUpMsg&);

    bool IsConnected() const { return mConnected; }
    int SigninMask() const { return mSigninMask; }
    int SigninChangedMask() const { return mSigninChangeMask; }
    bool HasNetError() { return mHasNetError; }
    bool IsOnlineRestricted() { return mIsOnlineRestricted; }
    void RelaxOnlineRestriction(){ mIsOnlineRestricted = false; }
    void SetIsRestarting(bool b){ mIsRestarting = b; }
    bool HomeMenuActive(){ return mHomeMenuWii->mHomeMenuActive; }
    void EnableSFX(bool b){ mEnableSFX = b; }
    bool AreSFXEnabled(){ return mEnableSFX; }
    void IgnoreWiiSpeakFriends(){ unkce5a = true; }

    LocalUser* GetOwnerUserOfGuestUser(LocalUser*);
    int GetOwnerOfGuest(int) const;
    void Draw();
    void Poll();
    void InitGQR();

    int mSigninMask;
    int mSigninChangeMask;
    bool mGuideShowing;
    bool mConnected;
    bool unk2a;
    bool unk2b;
    PlatformRegion mRegion;
    int unk30;
    int unk34;
    Timer mTimer;
    bool unk68;
    bool unk69;
    bool unk6a;
    bool unk6b;
    bool unk6c;
    bool unk6d;
    int unk70;
    bool mEthernetCableConnected;
    
    char filler[0x432b];

    bool unk43a0;
    bool unk43a1;
    bool unk43a2;
    bool unk43a3;

    char filler43a4[0x431c];

    int mHasNetError;
    Symbol unk86c4;

    char filler86c8[0x4018];

    class String unkc6e0;
    class String unkc6ec;

    char fillerunkc6f0[0x318];

    bool mCheckingProfanity;
    bool unkca11;
    bool unkca12;
    int unkca14;
    int unkca18;

    char fillerunkca1c[0x42c];

    HomeMenu* mHomeMenuWii;
    bool unkce4c;
    DiscErrorMgrWii* mDiscErrorMgr;
    bool mStorageChanged;
    bool unkce55;
    bool unkce56;
    bool mIsRestarting;
    bool unkce58;
    bool mEnableSFX;
    bool unkce5a;
    int unkce5c;
    int unkce60;
    int unkce64;
    bool mIsOnlineRestricted;
    bool unkce69;
    bool unkce6a;
};

Symbol PlatformRegionToSymbol(PlatformRegion);
PlatformRegion SymbolToPlatformRegion(Symbol);

extern PlatformMgr ThePlatformMgr;

#endif
