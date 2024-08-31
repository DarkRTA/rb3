#include "world/SpotlightDrawer.h"
#include "rndobj/Rnd.h"
#include "utl/Symbols.h"

SpotlightDrawer* SpotlightDrawer::sCurrent;
SpotlightDrawer* SpotlightDrawer::sDefault;
std::vector<SpotlightDrawer::SpotlightEntry> SpotlightDrawer::sLights;
std::vector<SpotlightDrawer::SpotMeshEntry> SpotlightDrawer::sCans;
std::vector<class Spotlight*> SpotlightDrawer::sShadowSpots;
int SpotlightDrawer::sNeedBoxMap = -1;
bool SpotlightDrawer::sNeedDraw;
bool SpotlightDrawer::sHaveAdditionals;
bool SpotlightDrawer::sHaveLenses;
bool SpotlightDrawer::sHaveFlares;
bool SpotlightDrawer::sNoBeams;

SpotlightDrawer::SpotlightDrawer() : mParams(this) {
    SetOrder(-100000.f);
}

SpotlightDrawer::~SpotlightDrawer(){
    
}

void SpotlightDrawer::OnGPHangRecover(){}

void SpotlightDrawer::Select(){
    if(sCurrent != this){
        if(sCurrent){
            TheRnd->UnregisterPostProcessor(sCurrent);
        }
        sCurrent = this;
        TheRnd->RegisterPostProcessor(this);
    }
    sNeedBoxMap = -1;
}

void SpotlightDrawer::DeSelect(){
    if(sCurrent != this) return;
    if(sDefault == this) return;
    sDefault->Select();
}

void SpotlightDrawer::DrawShowing(){
    if(sCurrent && sCurrent != sDefault && sCurrent != this){
        MILO_NOTIFY_ONCE("Drawing 2 spotlightdrawers in one frame, %s and %s", PathName(sCurrent), PathName(this));
    }
    else Select();
}

void SpotlightDrawer::ClearPostDraw(){
    ClearLights();
    sNeedDraw = false;
}

void SpotlightDrawer::ClearLights(){
    sLights.clear();
    sShadowSpots.clear();
    sCans.clear();
    sHaveAdditionals = false;
    sHaveLenses = false;
    sHaveFlares = false;
}

SAVE_OBJ(SpotlightDrawer, 0x344)

BEGIN_COPYS(SpotlightDrawer)
    COPY_SUPERCLASS(RndDrawable)
    CREATE_COPY(SpotlightDrawer)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mParams)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_LOADS(SpotlightDrawer)
    int rev;
    bs >> rev;
    if(rev > 5) MILO_FAIL("DxSpotlightDrawer: not forward compatable!");
    else {
        if(rev > 0) LOAD_SUPERCLASS(RndDrawable)
        else LOAD_SUPERCLASS(Hmx::Object)
        SetOrder(-100000.f);
        mParams.Load(bs, rev);
    }
END_LOADS

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

BEGIN_HANDLERS(SpotlightDrawer)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_ACTION(select, Select())
    HANDLE_ACTION(deselect, DeSelect())
    HANDLE_CHECK(0x3E4)
END_HANDLERS

BEGIN_PROPSYNCS(SpotlightDrawer)
    SYNC_PROP(total, mParams.mIntensity)
    SYNC_PROP(base_intensity, mParams.mBaseIntensity)
    SYNC_PROP(smoke_intensity, mParams.mSmokeIntensity)
    SYNC_PROP(color, mParams.mColor)
    SYNC_PROP(proxy, mParams.mProxy)
    SYNC_PROP(light_influence, mParams.mLightingInfluence)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS