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
    unk_0x0[0x10] += mpd.unk_0x0[0x10];
    return *this;
}


MemPoint::MemPoint(eInitType t) {
    if (t == kInitType1) {
        for (int i = 0; i < MemNumHeaps(); i++) {
            int a,b,c;
            MemFreeBlockStats(i, a, b, (int&)*this, c);
        }
    } else {
        memset(this, 0, 0x44);
    }
}

int MemPoint::operator-(const MemPoint&) const {
    MemPointDelta mpd;
}
