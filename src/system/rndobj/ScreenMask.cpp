#include "rndobj/ScreenMask.h"

RndScreenMask::RndScreenMask() : mMat(this, 0) {
    mShowing &= 0xFB;
}
