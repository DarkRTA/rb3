#include "Env.h"
#include "math/Color.h"
#include "obj/DataFunc.h"
#include "obj/ObjPtr_p.h"
#include "os/Debug.h"
#include "revolution/gx/GXTypes.h"
#include "rndobj/Lit.h"
#include "rndobj/Mat.h"

ObjPtrList<BandCharacter> WiiEnviron::mShadowedCharacters(NULL, kObjListNoNull);
RndMat *WiiEnviron::mShadowMat;
RndCam *WiiEnviron::mShadowCam;
#ifndef MILO_DEBUG
Transform some_xform;
#endif
bool WiiEnviron::mShadowLightSet;
bool WiiEnviron::mbRenderingShadows;
bool WiiEnviron::mbEnableShadows;
bool WiiEnviron::mbShowShadowTextureOnScreen;

static GXLightID LightId(int n) {
    MILO_ASSERT_RANGE(n, 0, 8, 34);
    return (GXLightID)(1 << n);
}

static DataNode DebugToggleShadows(DataArray *array) {
    WiiEnviron::mbEnableShadows = 0;
    return 0;
}

static DataNode DebugToggleShowShadowTextureOnScreen(DataArray *array) {
    WiiEnviron::mbShowShadowTextureOnScreen = !WiiEnviron::mbShowShadowTextureOnScreen;
    return 0;
}

WiiEnviron::WiiEnviron() {
    if (mShadowMat == nullptr) {
        mShadowMat = New<RndMat>();
        mShadowMat->SetBlend(RndMat::kBlendSrc);
        mShadowMat->SetZMode(RndMat::kZModeDisable);
        mShadowMat->SetTexWrap(kTexWrapClamp);
        mShadowMat->SetDiffuseTex(NULL);
        mShadowMat->SetAlpha(1);
        mShadowMat->SetColor(Hmx::Color(0, 0, 0, 1));
        mShadowMat->SetUseEnv(false);
    }
    if (mShadowCam == nullptr) {
        mShadowCam = New<RndCam>();
    }
#ifdef MILO_DEBUG
    DataRegisterFunc("toggle_shadows", DebugToggleShadows);
    DataRegisterFunc("toggle_show_shadow_texture", DebugToggleShowShadowTextureOnScreen);
#endif
}

WiiEnviron::~WiiEnviron() {}

bool WiiEnviron::SetLight(int i, WiiLight *lit) {
    GXLightID id = LightId(i);
    lit->Update(id);
    unk_0x19E |= id;
    if (unk_0x19C && lit->GetType() != RndLight::kDirectional) {
        unk_0x19C = false;
    }
    return 1;
}

void WiiEnviron::RenderCharactersToShadowBuffers() {
    mShadowedCharacters.clear();
    mShadowLightSet = false;
}
