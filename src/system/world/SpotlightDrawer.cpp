#include "world/SpotlightDrawer.h"

std::vector<SpotlightDrawer::SpotlightEntry> SpotlightDrawer::sLights;
std::vector<SpotlightDrawer::SpotMeshEntry> SpotlightDrawer::sCans;
std::vector<class Spotlight*> SpotlightDrawer::sShadowSpots;

SpotlightDrawer::SpotlightDrawer() : mParams(this) {
    mOrder = -100000.f;
}

SpotlightDrawer::~SpotlightDrawer(){
    
}

SpotDrawParams::SpotDrawParams(SpotlightDrawer* owner) : mIntensity(1.0f), mColor(), mBaseIntensity(0.1f), mSmokeIntensity(0.5f), mHalfDistance(250.0f), mLightingInfluence(1.0f),
    mTexture(owner, 0), mProxy(owner, 0), mOwner(owner) {
    MILO_ASSERT(owner, 0x37C);
}

SpotDrawParams& SpotDrawParams::operator=(const SpotDrawParams& params){
    mIntensity = params.mIntensity;
    mBaseIntensity = params.mBaseIntensity;
    mSmokeIntensity = params.mSmokeIntensity;
    mHalfDistance = params.mHalfDistance;
    mLightingInfluence = params.mLightingInfluence;
    mColor = params.mColor;
    mTexture = params.mTexture;
    mProxy = params.mProxy;
    return *this;
}

void SpotDrawParams::Load(BinStream& bs, int rev){
    if(rev > 5) MILO_WARN("Can't load new Params");
    else {
        bs >> mIntensity;
        if(rev > 3){
            bs >> mSmokeIntensity >> mHalfDistance >> mLightingInfluence;
        }
        else {
            float i, j, k, l;
            bs >> i >> j >> k >> l;
            if(k < 0.5f){
                mSmokeIntensity = 0.5f;
                mBaseIntensity = 0.1f;
            }
            else {
                mBaseIntensity = 0.15f;
                mSmokeIntensity = 1.0f;
            }
        }
        bs >> mColor;
        if(rev < 4){
            int a, b, c, d, e;
            bs >> a >> b >> c >> d >> e;
        }
        bs >> mTexture;
        bs >> mProxy;
        if(rev < 3){
            bool b;
            bs >> b;
        }
        if(rev > 4) bs >> mLightingInfluence;
    }
}