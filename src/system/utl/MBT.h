#ifndef UTL_MBT_H
#define UTL_MBT_H
#include "utl/MeasureMap.h"

void ParseMBT(const char*, int&, int&, int&);
const char* TickFormat(int, const MeasureMap&);
const char* FormatTimeMSH(float);

struct MBT {
    MBT() : measure(0), beat(0), tick(0) {}
    MBT(int m, int b, int t) : measure(m), beat(b), tick(t) {}
    // total size: 0xC
    int measure; // offset 0x0, size 0x4
    int beat; // offset 0x4, size 0x4
    int tick; // offset 0x8, size 0x4
};

#endif
