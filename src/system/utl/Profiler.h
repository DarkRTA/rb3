#ifndef UTL_PROFILER_H
#define UTL_PROFILER_H
#include "os/Timer.h"
#include "milo_types.h"

class Profiler { // total size: 0x4C
    Profiler(const char*, int);
    void Start();
    void Stop();

    const char * mName; // offset 0x0, size 0x4
    Timer mTimer; // offset 0x8, size 0x30
    float mMin; // offset 0x38, size 0x4
    float mMax; // offset 0x3C, size 0x4
    float mSum; // offset 0x40, size 0x4
    uint mCount; // offset 0x44, size 0x4
    uint mCountMax; // offset 0x48, size 0x4
};

#endif
