#include "Mat.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/Timer.h"
#include "revolution/gx/GXBump.h"
#include "revolution/gx/GXGeometry.h"
#include "revolution/gx/GXPixel.h"
#include "revolution/gx/GXTev.h"
#include "revolution/gx/GXTransform.h"
#include "revolution/gx/GXTypes.h"
#include "rndobj/Env.h"
#include "rndobj/Mat.h"
#include "utl/Loader.h"

bool WiiMat::sOverrideAlphaWrite = 0;
bool WiiMat::sCurrentZCompLoc = 1;
bool bDoMatLightHackBS = 1;

WiiMat *WiiMat::sCurrent = nullptr;
Transform *WiiMat::sCurrentModelXfm = nullptr;
RndTex *WiiMat::sGradientTex = nullptr;

int StageId(int i) {
    MILO_ASSERT(0 <= i && i < 16, 45);
    GXSetTevDirect((GXTevStageID)i);
    return i;
}

int TexCoordId(int i) {
    MILO_ASSERT(0 <= i && i < 8, 58);
    return i;
}

int TexMapId(int i) {
    MILO_ASSERT(0 <= i && i < 8, 64);
    return i;
}

int TexMtx(int i) {
    static const int op[8] = { 0x24, 0x27, 0x2a, 0x2d, 0x30, 0x33, 0x36, 0x39 };
    MILO_ASSERT(0 <= i && i < 8, 70);
    return op[i];
}

int PTTexMtx(int i) {
    MILO_ASSERT(0 <= i && i < 20, 89);
    return i * 3 + 64;
}

void WiiMat::SetCurrentModelTransform(const Transform *t) {
    sCurrentModelXfm = const_cast<Transform *>(t);
}

void WiiMat::PreInit() {
    Register();
    delete sGradientTex;
    sGradientTex = nullptr;
    sGradientTex = Hmx::Object::New<RndTex>();
    sGradientTex->SetBitmap(
        FilePath(MakeString("%s/world/gradient64x64_keep.bmp", FileSystemRoot()))
    );
}

void WiiMat::Init() {}

void WiiMat::SelectParticles() {
    if (this == sCurrent) {
    }
}

void WiiMat::Select(bool b) {
    START_AUTO_TIMER("mat_select");
    Reset();
    RndEnviron *env = RndEnviron::sCurrent;
    if (TheLoadMgr.EditMode()) {
        GXSetCullMode(GX_CULL_NONE);
    } else {
        GXSetCullMode((GXCullMode)mCull);
    }
    if (env != nullptr) {
        env->AmbientColor();
    }
}

void WiiMat::SetAlphaCutout(bool b, int i) {
    if (b) {
        GXSetAlphaCompare(GX_GREATER, i, GX_AOP_OR, GX_NEVER, 0);
    } else {
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    }
    if (b != sCurrentZCompLoc) {
        if (b != 0) {
            GXSetZCompLoc(false);
        } else {
            GXSetZCompLoc(true);
        }
        sCurrentZCompLoc = b;
    }
}

void WiiMat::SetZBufferMode(ZMode z) {
    switch (z) {
    case kZModeDisable:
        GXSetZMode(0, GX_NEVER, 0);
        return;
    case kZModeNormal:
        GXSetZMode(1, GX_LESS, 1);
        return;
    case kZModeTransparent:
        GXSetZMode(1, GX_LEQUAL, 0);
        return;
    case kZModeForce:
        GXSetZMode(1, GX_ALWAYS, 1);
        return;
    case kZModeDecal:
        GXSetZMode(1, GX_LEQUAL, 1);
        return;
    default:
        return;
    }
}

void WiiMat::SetFrameBlend(Blend b) {
    switch (b) {
    case RndMat::kBlendDest:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_ONE, GX_LO_NOOP);
        break;
    case RndMat::kBlendSrc:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
        break;
    case RndMat::kBlendAdd:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_NOOP);
        break;
    case RndMat::kBlendSrcAlpha:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        break;
    case RndMat::kBlendSrcAlphaAdd:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
        break;
    case RndMat::kBlendSubtract:
        GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_ONE, GX_BL_ONE, GX_LO_NOOP);
        break;
    case RndMat::kBlendMultiply:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCCLR, GX_BL_ZERO, GX_LO_NOOP);
        break;
    case RndMat::kPreMultAlpha:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        break;
    default:
        MILO_WARN("Invalid frame blend mode: %d\n", b);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    }
}

void WiiMat::SetModelviewTexGen() {
    if (!unk_0xAD_6) {
        unk_0xAD_6 = true;
        Mtx44 m;
        GXLoadTexMtxImm(m, 33, GX_MTX_3x4);
    }
}

void WiiMat::Reset() {
    unk_0xAD_5 = 0;
    unk_0xAD_6 = 0;
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
    GXSetTevDirect(GX_TEVSTAGE2);
    GXSetNumIndStages(0);
}

WiiMat::~WiiMat() {
    if (sCurrent == this)
        sCurrent = nullptr;
}
