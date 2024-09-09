#include "bandobj/OutfitConfig.h"

OutfitConfig::OutfitConfig() : mMats(this), unk38(0), unk3c(0), mComputeAO(1), mPatches(this), mPermaProject(0), mPiercings(this),
    mTexBlender(this, 0), mWrinkleBlender(this, 0), mOverlays(this), mBandLogo(this, 0) {
    for(int i = 0; i < 3; i++) mColors[i] = i;
}