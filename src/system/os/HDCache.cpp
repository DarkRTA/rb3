#include "HDCache.h"
#include "os/Debug.h"
#include "os/OSFuncs.h"

HDCache TheHDCache;

HDCache::HDCache() : a(0), d(), g(false) {}

HDCache::~HDCache() { }

void HDCache::UnlockCache() {
    if (cs.mEntryCount) cs.Enter();
    MILO_ASSERT(mLockID == CurrentThreadID(), 249);
    if (cs.mEntryCount) cs.Exit();
}
