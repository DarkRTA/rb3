#include "world/SpotlightDrawer.h"

SpotlightDrawer::SpotlightDrawer(){

}

SpotDrawParams::SpotDrawParams(SpotlightDrawer* owner) : mIntensity(1.0f), mColor(), mBaseIntensity(0.1f), mSmokeIntensity(0.5f), mHalfDistance(250.0f), mLightingInfluence(1.0f),
    mTexture(owner, 0), mProxy(owner, 0), mOwner(owner) {
    MILO_ASSERT(owner, 0x37C);
}