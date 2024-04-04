#ifndef OS_HDCACHE_H
#define OS_HDCACHE_H

#include "os/CritSec.h"
#include "utl/Str.h"
#include <vector>
#include <revolution/os.h>

class HDCache {
    public:
    int a;
    std::vector<int> b, c;
    int d[8];
    OSThread* mLockID;
    CriticalSection cs;
    String e, f;
    bool g;

    HDCache();
    ~HDCache();
    void Init();
    bool LockCache();
    void UnlockCache();
    void Poll();
    int HdrSize();
    void WriteHdr();
    bool ReadAsync(int, int, void*);
    bool ReadFail();
    bool ReadDone();

};

#endif // OS_HDCACHE_H
