#pragma once
#include "types.h"

class MemPointDelta {
public:
    MemPointDelta();
    MemPointDelta &operator+=(const MemPointDelta &);

    int unk_0x0[16];
    int unk40;
};

class MemPoint {
public:
    enum eInitType {
        kInitType0,
        kInitType1
    };

    MemPoint(eInitType = kInitType1);
    MemPointDelta operator-(const MemPoint &) const;

    int unk0[16];
    int unk40;
};