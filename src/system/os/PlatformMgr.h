#ifndef OS_PLATFORMMGR_H
#define OS_PLATFORMMGR_H
#include "obj/MsgSource.h"
#include "os/ContentMgr.h"

enum DiskError {
    kNoDiskError,
    kDiskError,
    kWrongDisk,
    kFailedChecksum
};

class PlatformMgr : public MsgSource, ContentMgr::Callback {
public:
    int filler;

    void SetDiskError(DiskError);
};

#endif
