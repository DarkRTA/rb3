#ifndef OS_OSFUNCS_H
#define OS_OSFUNCS_H
#include <revolution/os.h>

extern OSThread* gMainThreadID;

inline bool MainThread() {
    bool ret = true;
    if ((gMainThreadID != 0) && (gMainThreadID != OSGetCurrentThread()))
        ret = false;
    return ret;
}

inline OSThread* CurrentThreadId() { return OSGetCurrentThread(); }


#endif
