#ifndef OS_PLATFORMMGR_H
#define OS_PLATFORMMGR_H
#include "obj/MsgSource.h"
#include "os/ContentMgr.h"

class OnlineID; // forward dec

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
};



#endif
