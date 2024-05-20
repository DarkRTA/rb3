#ifndef OS_PLATFORMMGR_H
#define OS_PLATFORMMGR_H
#include "obj/MsgSource.h"
#include "os/ContentMgr.h"

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

class PlatformMgr : public MsgSource, ContentMgr::Callback {
public:
    int mSigninMask;
    int mSigninChangeMask;
    bool unk28;
    bool mConnected;
    bool unk2a;
    bool unk2b;
    PlatformRegion mRegion;

    PlatformMgr();

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

    bool IsConnected() const { return mConnected; }
    int SigninMask() const { return mSigninMask; }
    int SigninChangedMask() const { return mSigninChangeMask; }

    LocalUser* GetOwnerUserOfGuestUser(LocalUser*);
    int GetOwnerOfGuest(int) const;
    
    void Draw();

    void Poll();
    void InitGQR();
};

Symbol PlatformRegionToSymbol(PlatformRegion);
PlatformRegion SymbolToPlatformRegion(Symbol);

extern PlatformMgr ThePlatformMgr;

#endif
