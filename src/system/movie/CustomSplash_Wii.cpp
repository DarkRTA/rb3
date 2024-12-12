#include "CustomSplash_Wii.h"
#include "os/Joypad_Wii.h"
#include "os/PlatformMgr.h"
#include "revolution/DVD.h"
#include <revolution/GX.h>
#include <revolution/OS.h>
#include <revolution/SC.h>
#include <revolution/TPL.h>
#include "rndobj/Rnd.h"
#include "rndwii/Rnd.h"
#include "utl/MemMgr.h"
#include <cstddef>

void *AllocateMEM2(int size) { return _MemAlloc(size, 0x20); }

CustomSplash::CustomSplash() : mTimer1(), mTimer2() {
    unk_64 = 0;
    unk_48c = 0;
    float val = 250.0f;
    unk_60 = -val;
    unk_48d = 0;
    unk_490 = 1;
}

CustomSplash::~CustomSplash() {
    if (mPalette)
        _MemFree(mPalette);
}

void CustomSplash::Init() {
    mTimer1.Init();
    InitPAD();
    TheWiiRnd.SetFullScrProj();
    InitSplasher();
}

void CustomSplash::InitPAD() {
    JoypadWiiInitCommon(true);
    ThePlatformMgr.SystemInitPowerCallbacks();
}

void CustomSplash::InitSplasher() {
    uint x = 0;
    switch (SCGetLanguage()) {
    case SC_LANG_EN:
        sprintf(
            fname,
            "StrapUsage/StrapUsage_eng_%s.tpl",
            SCGetAspectRatio() == SC_ASPECT_WIDE ? "16_9" : "4_3"
        );
        break;
    case SC_LANG_FR:
        sprintf(
            fname,
            "StrapUsage/StrapUsage_fre_%s.tpl",
            SCGetAspectRatio() == SC_ASPECT_WIDE ? "16_9" : "4_3"
        );
        break;
    case SC_LANG_IT:
        sprintf(
            fname,
            "StrapUsage/StrapUsage_ita_%s.tpl",
            SCGetAspectRatio() == SC_ASPECT_WIDE ? "16_9" : "4_3"
        );
        break;
    case SC_LANG_DE:
        sprintf(
            fname,
            "StrapUsage/StrapUsage_deu_%s.tpl",
            SCGetAspectRatio() == SC_ASPECT_WIDE ? "16_9" : "4_3"
        );
        break;
    case SC_LANG_SP:
        sprintf(
            fname,
            "StrapUsage/StrapUsage_esl_%s.tpl",
            SCGetAspectRatio() == SC_ASPECT_WIDE ? "16_9" : "4_3"
        );
        break;
    case SC_LANG_NL:
        sprintf(
            fname,
            "StrapUsage/StrapUsage_nld_%s.tpl",
            SCGetAspectRatio() == SC_ASPECT_WIDE ? "16_9" : "4_3"
        );
        break;
    default:
        sprintf(
            fname,
            "StrapUsage/StrapUsage_eng_%s.tpl",
            SCGetAspectRatio() == SC_ASPECT_WIDE ? "16_9" : "4_3"
        );
    }
    mPalette = LoadFile(fname, x, AllocateMEM2);
    if (mPalette) {
        TPLBind(mPalette);
        DCStoreRange(mPalette, (x + 31) & ~31);
        TPLGetGXTexObjFromPalette(mPalette, &mGXTexObj, 0);
        GXLoadTexObj(&mGXTexObj, GX_TEXMAP0);
    }
}

void CustomSplash::DrawSplasher(unsigned char alpha) {
    if (mPalette) {
        u16 w = TheRnd->Width(), h = TheRnd->Height();
        GXClearVtxDesc();
        GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_POS, GX_POS_XY, GX_S16, 0);
        GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_TEX0, GX_CLR_RGBA, GX_RGBA4, 0);
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetNumChans(1);
        GXSetChanCtrl(
            GX_COLOR0A0,
            false,
            GX_SRC_VTX,
            GX_SRC_VTX,
            GX_LIGHT_NULL,
            GX_DF_NONE,
            GX_AF_NONE
        );
        GXSetChanCtrl(
            GX_COLOR1A1,
            false,
            GX_SRC_REG,
            GX_SRC_VTX,
            GX_LIGHT_NULL,
            GX_DF_NONE,
            GX_AF_NONE
        );
        GXSetNumTexGens(1);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60);
        // here lies the tev configuration. there is no honor to be gained here.
        GXColor col;
        col.r = 255;
        col.g = 255;
        col.b = 255;
        col.a = alpha;
        GXSetTevKColor(GX_KCOLOR0, col);
        GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
        GXSetNumTevStages(1);
        GXSetTevColor(GX_TEVREG0, (GXColor) { 0xFF, 0xFF, 0xFF, 0xFF });
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevColorOp(
            GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV
        );
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_KONST, GX_CA_ZERO);
        GXSetTevAlphaOp(
            GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV
        );
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetZMode(false, GX_LEQUAL, false);
        TPLGetGXTexObjFromPalette(mPalette, &mGXTexObj, 0);
        GXLoadTexObj(&mGXTexObj, GX_TEXMAP0);
        RndGXBegin(GX_QUADS, GX_VTXFMT3, 4);
        GXPosition2u16(0, h);
        GXTexCoord2u16(0, 1);
        GXPosition2u16(w, h);
        GXTexCoord2u16(1, 1);
        GXPosition2u16(w, 0);
        GXTexCoord2u16(1, 0);
        GXPosition2u16(0, 0);
        GXTexCoord2u16(0, 0);
        RndGXEnd();
    }
}

TPLPalette *CustomSplash::LoadFile(const char *filename, uint &fd, void *(*alloc)(int)) {
    void *v;
    DVDFileInfo fi;
    if (DVDOpen(const_cast<char *>(filename), &fi)) {
        fd = fi.startAddr;
        v = alloc((fd + 31) & ~31);
        DVDReadAsyncPrio(&fi, v, (fd + 31) & ~31, 0, NULL, 2);
        // u32 blkstat = DVDGetCommandBlockStatus(&fi);
    } else
        return 0;
    return (TPLPalette *)v;
}
