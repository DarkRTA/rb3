#ifndef OS_PLATFORMMGR_H
#define OS_PLATFORMMGR_H

enum DiskError {
    i, d, k, l, m, a, o
};

class PlatformMgr {
public:
    int filler;

    void SetDiskError(DiskError);
};

#endif
