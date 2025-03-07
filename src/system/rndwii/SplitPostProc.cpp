#include "SplitPostProc.h"
#include "decomp.h"
#include "obj/Dir.h"
#include "os/Timer.h"
#include "revolution/gx/GXAttr.h"
#include "revolution/gx/GXLight.h"
#include "revolution/gx/GXMisc.h"
#include "revolution/gx/GXPixel.h"
#include "revolution/gx/GXTev.h"
#include "revolution/gx/GXTypes.h"
#include "rndobj/Cam.h"
#include "rndobj/PostProc.h"
#include "rndobj/Rnd.h"
#include "rndwii/Mat.h"
#include "rndwii/PostProc.h"
#include "rndwii/Rnd.h"
#include "ui/UI.h"
#include "utl/Messages4.h"

WiiSplitPostProc::WiiSplitPostProc() : unk_0x8(0), unk_0x9(0) {
    mTex = (WiiTex *)Hmx::Object::New<RndTex>();
    int h = TheWiiRnd.Height();
    mTex->DisableFiltering(true);
    mTex->SetBitmap(608, h, 16, RndTex::kRendered, false, nullptr);
    TheRnd->RegisterPostProcessor(this);
}

WiiSplitPostProc::~WiiSplitPostProc() {
    TheRnd->UnregisterPostProcessor(this);
    delete mTex;
    mTex = nullptr;
}

void WiiSplitPostProc::OnGPHangRecover() {
    WiiTex *wt = mTex;
    if (wt != nullptr) {
        int siz = wt->Height() * wt->Width();
        siz *= wt->Bpp() / 8;
        memset(wt->ImgData(), 0, siz);
        DCStoreRange(wt->ImgData(), siz);
    }
}

void WiiSplitPostProc::BeginWorld() {
    START_AUTO_TIMER("postproc");
    if (TheWiiRnd.ProcCmds() == kProcessAll) {
#ifdef VERSION_SZBE69_B8
        _at.mTimer->Split();
#endif
    } else {
        if (TheWiiRnd.ProcCmds() & 0x4) {
            if (unk_0x8)
                DrawWorldTex();
        } else {
            if (TheWiiRnd.ProcCmds() == kProcessPost) {
                DrawWorldColorTex();
            }
        }
    }
}

void WiiSplitPostProc::EndWorld() { START_AUTO_TIMER("postproc"); }

void WiiSplitPostProc::DoPost() {
    START_AUTO_TIMER("postproc");
    if (TheWiiRnd.ProcCmds() == kProcessAll) {
        mTex->unk(1);
        unk_0x9 = 1;
#ifdef VERSION_SZBE69_B8
        _at.mTimer->Stop();
#endif
        return;
    } else if (TheWiiRnd.ProcCmds() == kProcessWorld) {
        WiiTex *a = (WiiTex *)TheWiiRnd.GetSharedTex((WiiRnd::SharedTexType)0, 1);
        WiiTex *b = (WiiTex *)TheWiiRnd.GetSharedTex((WiiRnd::SharedTexType)1, 1);
        a->unk(0);
        b->unk(1);
        unk_0x8 = true;
    }

    if (TheWiiRnd.ProcCmds() == kProcessChar) {
        ((WiiTex *)TheWiiRnd.GetSharedTex((WiiRnd::SharedTexType)0, 1))->unk(1);
    }
    if (TheWiiRnd.ProcCmds() & kProcessPost) {
        mTex->unk(1);
        GXPixModeSync();
        unk_0x9 = true;
    }
}

void WiiSplitPostProc::DrawWorldTex() {
    RndCam::sCurrent->Select();
    WiiOrthoProj p;
    GXSetZMode(true, GX_ALWAYS, true);
    if (WiiMat::sCurrentZCompLoc == 0)
        GXSetZCompLoc(false);
    GXSetAlphaUpdate(true);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60);
    GXSetNumTevStages(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);

    ((WiiTex *)TheWiiRnd.GetSharedTex((WiiRnd::SharedTexType)0, false))
        ->Select(GX_TEXMAP0);
    ((WiiTex *)TheWiiRnd.GetSharedTex((WiiRnd::SharedTexType)1, false))
        ->Select(GX_TEXMAP1);
    GXSetZTexture(GZ_ZT_REPLACE, GX_TF_Z24X8, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    TheWiiRnd.DrawQuad(0, 0);
    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);
    if (WiiMat::sCurrentZCompLoc == 0)
        GXSetZCompLoc(true);
}

void WiiSplitPostProc::DrawFinalTex() {
    if (unk_0x9 != 0) {
        RndCam::sCurrent->Select();
        WiiOrthoProj p;
        GXSetZMode(0, GX_ALWAYS, 0);
        GXSetNumChans(0);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        WiiPostProc *pp;
        if (TheWiiRnd.ProcCmds() == kProcessAll && TheUI.unkb5 && TheUI.InTransition()) {
            UIPanel *p = ObjectDir::sMainDir->Find<UIPanel>("abstract_wipe_panel", true);
            pp = p->HandleType(wipe_pp_msg).Obj<WiiPostProc>();
        } else {
            pp = dynamic_cast<WiiPostProc *>(RndPostProc::Current());
        }
        if (pp != nullptr && !TheRnd->DisablePP()) {
            pp->PrepareFinalTEV();
        } else {
            GXSetNumTexGens(1);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60);
            GXSetNumTevStages(1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorOp(
                GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV
            );
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
            GXSetTevAlphaOp(
                GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV
            );
            GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_1);
        }
        mTex->Select(GX_TEXMAP0);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
        if (pp != nullptr && !TheRnd->DisablePP()) {
            pp->DrawKaleidoscope();
            if (TheWiiRnd.ProcCmds() == kProcessAll) {
                mTex->unk(0);
                GXPixModeSync();
            }
        } else {
            TheWiiRnd.DrawQuad(TheWiiRnd.Width(), TheWiiRnd.Height());
        }
        if (pp != nullptr) {
            pp->ClearFinalTEV();
        }
    }
}

void WiiSplitPostProc::DrawWorldColorTex() {
    RndCam::sCurrent->Select();
    WiiOrthoProj p;
    GXSetZMode(0, GX_ALWAYS, 0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_1);
    ((WiiTex *)TheWiiRnd.GetSharedTex((WiiRnd::SharedTexType)0, false))
        ->Select(GX_TEXMAP0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    TheWiiRnd.DrawQuad(0, 0);
}

DECOMP_FORCEACTIVE(
    SplitPostProc,
    "[WiiSplitPostProc::ClearAlpha] Please inform George if you see this notify!\n"
)
