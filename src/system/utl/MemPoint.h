#pragma once

#include "types.h"
class MemPointDelta {
    public:
    MemPointDelta();
    MemPointDelta& operator+=(const MemPointDelta&);
    u32 unk_0x0[0x11];
};

class MemPoint {
public:
    enum eInitType {
        kInitType0,
        kInitType1
    };

    MemPoint(eInitType = kInitType1);
    int operator-(const MemPoint&) const;

    int unk_0x0;
};