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

class PlatformMgr : public MsgSource, ContentMgr::Callback {
public:
    int filler1, filler2;
    bool bool1, bool2;

    void SetDiskError(DiskError);
    void GetOnlineID(int, OnlineID*) const;
    const char* GetName(int) const;
    bool UserHasOnlinePrivilege(const LocalUser*) const;
    bool IsUserAGuest(const LocalUser*) const;
    bool IsUserSignedIn(const LocalUser*) const;
    bool IsUserSignedIntoLive(const LocalUser*) const;

    void Poll();
};

extern PlatformMgr ThePlatformMgr;

#endif
