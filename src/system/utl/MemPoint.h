#pragma once
#include "types.h"

class MemPointDelta {
public:
    MemPointDelta();
    MemPointDelta& operator+=(const MemPointDelta&);

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

    MemPointDelta operator-(const MemPoint&) const;
    MemPoint& operator=(const MemPoint& mp){
        for(int i = 0; i < 16; i++){
            unk0[i] = mp.unk0[i];
        }
        unk40 = mp.unk40;
        return *this;
    }

    int unk0[16];
    int unk40;
};