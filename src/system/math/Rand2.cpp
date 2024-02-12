#include "math/Rand2.h"

// fn_802DDE34
Rand2::Rand2(int i) {
    mSeed = i;
    if (i == 0) {
        mSeed = 1;
        return;
    }
    if (i < 0)
        mSeed = -i;
}

// fn_802DDE5C
int Rand2::Int() {
    int test = ((mSeed % 127773) * 0x41A7) - ((mSeed / 127773) * 0xB14);
    if (test > 0)
        mSeed = test;
    else
        mSeed = test + 0x7FFFFFFF;
    return mSeed;
}
