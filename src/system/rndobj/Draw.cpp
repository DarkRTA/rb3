#include "rndobj/Draw.h"

RndDrawable::RndDrawable() : mOrder(0.0f), mSphere() {
    mShowing = (unsigned char)mShowing | 0x80;
}
