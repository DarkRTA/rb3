#include "Rnd.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "revolution/gx/GXAttr.h"
#include "revolution/gx/GXFifo.h"
#include "revolution/gx/GXFrameBuf.h"
#include "revolution/gx/GXLight.h"
#include "revolution/gx/GXTev.h"
#include "revolution/gx/GXTransform.h"
#include "revolution/gx/GXTypes.h"
#include "revolution/gx/GXVert.h"
#include "revolution/os/OSError.h"
#include "revolution/sc/scapi.h"
#include "revolution/vi/vi.h"
#include "rndobj/Flare.h"
#include "rndobj/Font.h"
#include "rndobj/HiResScreen.h"
#include "rndobj/Rnd.h"
#include "rndwii/Mat.h"
#include "rndwii/Tex.h"
#include "types.h"
#include "utl/MemMgr.h"
#include "utl/Symbols.h"
#include "revolution/GX.h"
#include "revolution/OS.h"
#include <cstdarg>

bool gInBegin, gBeginIntState;
int gSuppressPointTest;
void *sDispFB, *sCopyFB;
OSThreadQueue drawDoneThreadQueue;
WiiRnd TheWiiRnd;

void DumpFifoStatus() {
    GXFifoObj fifo;
    GXGetCPUFifo(&fifo);
    GXGetFifoCount(&fifo);
    GXGetFifoWrap(&fifo);

    OSReport("Fifo Status\tbase:%p\tsize:\t%d\tlow:\t%d\thi:\t%d\tlinked:\t%d\n");
    OSReport("readPtr\twritePtr\treadIndex\twriteIndex\tcount\twrap\n");
    OSReport("%p\t%p\t%d\t%d\t%d\t%d\n");
}

extern "C" void MemErrorHandler(u8 error, OSContext *ctx, u32 dsisr, u32 dar, ...) {
    OSReport("MemErrorHandler: dsisr: %d dar: %p\n", dsisr, dar);
}

void WiiRnd::SwapFrameBuffer() {
    if (sDispFB == unk_0x1A8)
        sDispFB = unk_0x1AC;
    else
        sDispFB = unk_0x1A8;
}

void WiiRnd::RemovePointTest(RndFlare *) {
    if (!TheHiResScreen.mActive) {
        MILO_ASSERT(gSuppressPointTest>=0, 876);

        MILO_ASSERT(gSuppressPointTest>0, 897);
        gSuppressPointTest--;
    }
}

void OnDrawSync(u16 s) {
    if (s != 62001)
        return;
    if (gSuppressPointTest)
        return;
    TheWiiRnd.DoPointTests();
}

void DiagnoseHang() {
    u8 a, b, c, d, e;
    GXGetGPStatus(&a, &b, &c, &d, &e);
    OSReport("  GXGetGPStatus(%d, %d, %d, %d, %d);\n", a, b, c, d, e);
    OSReport("  GX FIFO overflow count: %d\n", GXGetOverflowCount());
    GXResetOverflowCount();
    DumpFifoStatus();
}

WiiOrthoProj::WiiOrthoProj() {
    GXGetProjectionv(proj);
    TheWiiRnd.SetOrthoProj();
}

WiiOrthoProj::~WiiOrthoProj() { GXSetProjectionv(proj); }

WiiRnd::WiiRnd()
    : unk_0x2B0(false), unk_0x2B1(false), unk_0x2B2(false), unk_0x2B3(false),
      unk_0x2BC(false), mFramesBuffered(2) {
    mClearColor.Set(0, 0, 0, 0);
    unk_0x2B4.reserve(0x20);
}

WiiRnd::~WiiRnd() {}

void WiiModal(bool &rb, char *c, bool b) { TheWiiRnd.Modal(rb, c, b); }

void WiiRnd::PreInit() {
    if (!unk_0x2B3) {
        unk_0x2B3 = true;
        WiiPreInit();
        OSSetErrorHandler(15, MemErrorHandler);
        if (unk_0x1A8 != nullptr) {
            _MemFree(unk_0x1A8);
            unk_0x1A8 = nullptr;
        }
        if (unk_0x1AC != nullptr) {
            _MemFree(unk_0x1AC);
            unk_0x1AC = nullptr;
        }
        if (unk_0x1B4 != nullptr) {
            _MemFree(unk_0x1B4);
            unk_0x1B4 = nullptr;
        }
        unk_0x1B8 = 0;
        ThePlatformMgr.InitGQR();
        VIInit();
        VITvFormat fmt = VIGetTvFormat();
        mProgScan = VIGetScanMode() == VI_SCAN_MODE_PROG;
        if (SCGetAspectRatio() == 1) {
            SetAspect(kWidescreen);
        } else {
            SetAspect(kLetterbox);
        }
        if (fmt == VI_TV_FMT_NTSC) {
        } else if (fmt == VI_TV_FMT_PAL) {
        } else if (fmt == VI_TV_FMT_EURGB60) {
            mProgScan;
        }
    }
}

void WiiRnd::WiiPreInit() {
    Rnd::PreInit();
    WiiTex::Register();
    WiiMat::PreInit();
}

bool WiiRnd::GetProgressiveScan() { return mProgScan; }

void WiiRnd::DrawLine(const Vector3 &a, const Vector3 &b, const Hmx::Color &c, bool) {
    GXLoadPosMtxImm(unk_0x23C, 0);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    int col = MakeU32Color(c);
    RndGXBegin(GX_LINES, GX_VTXFMT6, 2);
    GXPosition3f32(a.x, a.y, a.z);
    GXColor1u32(col);
    GXPosition3f32(b.x, b.y, b.z);
    GXColor1u32(col);
    RndGXEnd();
}

void WiiRnd::DoPostProcess() {
    Rnd::DoPostProcess();
    unk_0x2B0 = false;
    unk_0x274->DrawFinalTex();
    WiiMat::sCurrent = nullptr;
}

BEGIN_HANDLERS(WiiRnd)
    HANDLE_ACTION(tri_frame, SetTriFrameRendering(_msg->Int(2)))
    HANDLE_ACTION(toggle_locked_cache, ToggleLockedCache())
    HANDLE_ACTION(toggle_show_particle, ToggleShowParticle())
    HANDLE_ACTION(toggle_asset_name, ToggleAssetName())
    HANDLE_ACTION(frames_buffered, mFramesBuffered = _msg->Int(2))
    HANDLE_SUPERCLASS(Rnd)
    HANDLE_CHECK(2722)
END_HANDLERS

void WiiRnd::CopyBuffer() {
    GXSetCopyFilter(unk_0x185, 0, true, 0);
    GXCopyDisp(sCopyFB, true);
    GXSetCopyFilter(0, 0, 0, 0);
}

void WiiRnd::SetOrthoProj() {
    if (unk_0x2B0)
        GXSetProjection(unk_0x1FC, GX_ORTHOGRAPHIC);
    else
        GXSetProjection(unk_0x1BC, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(unk_0x23C, 0);
    GXSetCurrentMtx(0);
}

void WiiRnd::DrawQuad(int w, int h) {
    Hmx::Rect r;
    if (w == 0) {
        if (!unk_0x2B0)
            w = mWidth;
        else
            w = 608;
    }
    if (h == 0)
        h = mHeight;
    r.Set(0, 0, w, h);

    DrawQuad(r);
}

void WiiRnd::DrawQuad(const Hmx::Rect &r) {
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    RndGXBegin(GX_QUADS, GX_VTXFMT6, 4);
    float rx = r.x;
    float ry = r.y;
    float rh = r.h;
    GXPosition3f32(rx, ry, 0);
    GXTexCoord2u8(0, 0);
    GXPosition3f32(rx, rh, 0);
    GXTexCoord2u8(0, 1);
    GXPosition3f32(r.w, rh, 0);
    GXTexCoord2u8(1, 1);
    GXPosition3f32(r.w, ry, 0);
    GXTexCoord2u8(1, 0);
    RndGXEnd();
}

void WiiRnd::ClearSwapTables() {
    int i = 0;
    do {
        GXSetTevSwapMode((GXTevStageID)i, GX_TEV_SWAP0, GX_TEV_SWAP0);
    } while (++i < 16);
}

void WiiRnd::DrawBlackBackground() {
    GXColor c;
    c.b = c.g = c.r = 0;
    c.a = 0xff;
    GXColor c2;
    c.b = c.g = c.r = 0;
    c.a = 0xff;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetChanAmbColor(GX_COLOR0A0, c2);
    GXSetChanMatColor(GX_COLOR0A0, c);
    GXSetChanCtrl(
        GX_COLOR0A0, false, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE
    );
    GXSetChanCtrl(
        GX_COLOR1A1, false, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE
    );
    GXSetNumTexGens(0);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    RndGXBegin(GX_QUADS, GX_VTXFMT1, 4);
    GXPosition3f32(0, 0, 0);
    GXColor4u8(0, 0, 0, 0xff);
    GXPosition3f32(0, unk_0x170, 0);
    GXColor4u8(0, 0, 0, 0xff);
    GXPosition3f32(unk_0x172, unk_0x170, 0);
    GXColor4u8(0, 0, 0, 0xff);
    GXPosition3f32(unk_0x172, 0, 0);
    GXColor4u8(0, 0, 0, 0xff);
    RndGXEnd();
}

void WiiRnd::KeyboardOpen() { SetGPHangDetectEnabled(false, __FUNCTION__); }

void WiiRnd::KeyboardClose() {
    SetGPHangDetectEnabled(true, __FUNCTION__);
    BeginDrawing();
    EndDrawing();
    BeginDrawing();
    EndDrawing();
    BeginDrawing();
    EndDrawing();
}

void *WiiRnd::GetCurrXFB() { return sDispFB; }

void RndGXBegin(_GXPrimitive prim, _GXVtxFmt fmt, unsigned short verts) {
    MILO_ASSERT(!gInBegin, 3699);
    gInBegin = true;
    gBeginIntState = OSDisableInterrupts();
    GXBegin(prim, fmt, verts);
}

void RndGXEnd() { // this never calls GXEnd but it's ok because it's a nothing burger
    OSRestoreInterrupts(gBeginIntState);
    gInBegin = false;
}

void RndGXDrawDoneCallback() { OSWakeupThread(&drawDoneThreadQueue); }

void RndGxDrawDone() {
    int x = OSDisableInterrupts();
    GXSetDrawDoneCallback(RndGXDrawDoneCallback);
    GXSetDrawDone();
    OSSleepThread(&drawDoneThreadQueue);
    OSRestoreInterrupts(x);
}
