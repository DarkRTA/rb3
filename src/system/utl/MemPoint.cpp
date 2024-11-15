#include "MemPoint.h"
#include "utl/MemMgr.h"
#include <string.h>

MemPointDelta::MemPointDelta() {
    memset(unk_0x0, 0, 0x44);
}

MemPointDelta& MemPointDelta::operator+=(const MemPointDelta& mpd) {
    for (int i = 0; i < MemNumHeaps(); i++) {
        unk_0x0[i] += mpd.unk_0x0[i];
    }
    unk40 += mpd.unk40;
    return *this;
}


MemPoint::MemPoint(eInitType t) {
#ifdef MILO_DEBUG
    if (t == kInitType1) {
        for (int i = 0; i < MemNumHeaps(); i++) {
            int a,b,c;
            MemFreeBlockStats(i, a, b, (int&)*this, c);
        }
    } else {
        memset(this, 0, 0x44);
    }
#else
    memset(unk0, 0, 0x44);
#endif
}

MemPointDelta MemPoint::operator-(const MemPoint& mp) const {
    MemPointDelta mpd;
    for(int i = 0; i < MemNumHeaps(); i++){
        mpd.unk_0x0[i] = mp.unk0[i] - unk0[i];
    }
    mpd.unk40 = unk40 - mp.unk40;
    return mpd;
}
