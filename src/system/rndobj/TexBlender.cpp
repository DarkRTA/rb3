#include "rndobj/TexBlender.h"

RndTexBlender::RndTexBlender() : p1(this, 0), p2(this, 0), p3(this, 0), p4(this, 0), p5(this, kObjListNoNull), p6(this, 0), unk6c(1.0f), unk70(0) {
    mShowing |= 2;
}
