#include "Mat.h"
#include "math/Color.h"
#include "math/Mtx.h"
#include "math/Rot.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/Timer.h"
#include "revolution/gx/GXAttr.h"
#include "revolution/gx/GXBump.h"
#include "revolution/gx/GXGeometry.h"
#include "revolution/gx/GXLight.h"
#include "revolution/gx/GXPixel.h"
#include "revolution/gx/GXTev.h"
#include "revolution/gx/GXTransform.h"
#include "revolution/gx/GXTypes.h"
#include "rndobj/Cam.h"
#include "rndobj/Env.h"
#include "rndobj/Utl.h"
#include "rndobj/Mat.h"
#include "rndwii/Rnd.h"
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

bool WiiMat::Select(bool b) {
    START_AUTO_TIMER("mat_select");
    if (this == sCurrent && !mDirty)
        return 0;
    Reset();
    RndEnviron *env = RndEnviron::sCurrent;
#ifdef VERSION_SZBE69_B8
    if (TheLoadMgr.EditMode()) {
        GXSetCullMode(GX_CULL_NONE);
    } else {
        GXSetCullMode((GXCullMode)mCull);
    }
#else
    GXSetCullMode((GXCullMode)mCull);
#endif
    Hmx::Color c1 = env != nullptr ? env->AmbientColor() : Hmx::Color(0, 0, 0);
    Hmx::Color c2 = mColor;
    if (mBlend == 7) {
        PreMultiplyAlpha(c2);
    }
    // int p1 = c1.PackAlpha();
    // int p2 = c2.PackAlpha();
    // GXSetChanMatColor(GX_COLOR0A0, *(GXColor *)&p1);
    // GXSetChanMatColor(GX_COLOR1A1, *(GXColor *)&p2);
    GXSetNumChans(1);
    GXSetChanCtrl(
        GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPOT
    );
    GXSetChanCtrl(
        GX_COLOR1A1, 0, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPOT
    );

    int lightIds;
    MILO_ASSERT(((unsigned int)lightIds) < ((unsigned int)GX_MAX_LIGHT), 417);
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
#ifdef VERSION_SZBE69_B8
#pragma push
#pragma dont_inline on
#endif
void WiiMat::SetTexGen(GXTexCoordID tcid, GXTexMtx mtx) {
    Transform t1, t2;
    t1.Zero();
    Vector3 v;
    Mtx m;
    if (!unk_0xAD_5) {
        switch (mTexGen) {
        case kTexGenXfm:
        case kTexGenXfmOrigin:
            if (unk_0xAD_7) {
                Transform t;
                t.Reset();
                MakeWiiMtxTex(t, mTexGen == kTexGenXfm, m);
                GXLoadTexMtxImm(m, mtx, GX_MTX_2x4);
                break;
            } else {
                MakeWiiMtxTex(mTexXfm, mTexGen == kTexGenXfm, m);
                GXLoadTexMtxImm(m, mtx, GX_MTX_2x4);
                break;
            }
            break;
        case kTexGenProjected:
            FastInvert(mTexXfm, t1);
            if (sCurrentModelXfm != nullptr) {
                Multiply(*sCurrentModelXfm, t1, t1);
            }
            t2.v.Zero();
            t2.m.Set(1, 0, 0, 0, 0, 1, 0, -1, 0);
            Multiply(t1, t2, t1);
            MakeWiiMtx(t1, m);
            GXLoadTexMtxImm(m, mtx, GX_MTX_2x4);
            break;
        case kTexGenEnviron:
            Transpose(mTexXfm.m, t1.m);
            Multiply(RndCam::Current()->WorldXfm().m, t1.m, t1.m);
            Hmx::Matrix3 m2(1, 0, 0, 0, 0, 1, 0, 1, 0);
            Multiply(m2, t1.m, t1.m);
            m2.x.x = 0.5;
            m2.z.y = -0.5;
            Multiply(t1.m, m2, t1.m);
            t1.v.Set(0.5, 0.5, 0);
            MakeWiiMtx(t1, m);
            GXLoadTexMtxImm(m, mtx, GX_MTX_3x4);
            break;
        case kTexGenSphere:
            Transpose(mTexXfm.m, t1.m);
            Multiply(RndCam::Current()->WorldXfm().m, t1.m, t1.m);
            // Vector3 v;
            MakeEuler(t1.m, v);
            v.x = InterpAng(0, v.x, 0.5);
            v.z = InterpAng(0, v.z, 0.5);
            MakeRotMatrix(v, t1.m, true);
            t2.v.Zero();
            Transpose(RndCam::Current()->WorldXfm().m, t2.m);
            Multiply(t2.m, t1.m, t1.m);
            t2.m.Set(0.5, 0, 0, 0, 0, 1, 0, -0.5, 0);
            Multiply(t1.m, t2.m, t1.m);
            t1.v.Set(0.5, 0.5, 0);
            MakeWiiMtx(t1, m);
            GXLoadTexMtxImm(m, mtx, GX_MTX_2x4);
            break;
        default:
            break;
        }
        unk_0xAD_5 = true;
    }
    switch (mTexGen) {
    case kTexGenXfm:
    case kTexGenXfmOrigin:
        GXSetTexCoordGen(tcid, GX_TG_MTX2x4, GX_TG_TEX0, mtx);
        break;
    case kTexGenProjected:
        GXSetTexCoordGen(tcid, GX_TG_MTX2x4, GX_TG_POS, mtx);
        break;
    case kTexGenEnviron:
        GXSetTexCoordGen(tcid, GX_TG_MTX2x4, GX_TG_BINRM, mtx);
        break;
    case kTexGenSphere:
        GXSetTexCoordGen(tcid, GX_TG_MTX2x4, GX_TG_NRM, mtx);
        break;
    case kTexGenNone:
        GXSetTexCoordGen(tcid, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX_IDENT);
        break;
    default:;
    }
}
#ifdef VERSION_SZBE69_B8
#pragma pop
#endif

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
