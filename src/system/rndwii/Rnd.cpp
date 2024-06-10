#include "Rnd.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "revolution/gx/GXAttr.h"
#include "revolution/gx/GXTransform.h"
#include "revolution/gx/GXTypes.h"
#include "revolution/gx/GXVert.h"
#include "rndwii/Tex.h"
#include "types.h"
#include "utl/Symbols.h"
#include "revolution/GX.h"
#include "revolution/OS.h"

bool gInBegin, gBeginIntState;
int gSuppressPointTest;
void* sDispFB;
OSThreadQueue drawDoneThreadQueue;

void WiiRnd::SwapFrameBuffer() {
    if (sDispFB == unk_0x1A8) sDispFB = unk_0x1AC;
    else sDispFB = unk_0x1A8;
}

void OnDrawSync(u16 s) {
    if (s != 62001) return;
    if (gSuppressPointTest) return;
    TheWiiRnd.DoPointTests();
}

WiiRnd::WiiRnd() : unk_0x2B0(false), unk_0x2B1(false), unk_0x2B2(false), unk_0x2B3(false), unk_0x2BC(false), 
    mFramesBuffered(2) { 
    mColor.Set(0, 0, 0, 0);
    unk_0x2B4.reserve(0x20); 
}

WiiRnd::~WiiRnd() {}

void WiiModal(bool& rb, char* c, bool b) { TheWiiRnd.Modal(rb, c, b); }

void WiiRnd::WiiPreInit() {
    Rnd::PreInit();
    Hmx::Object::RegisterFactory(WiiTex::StaticClassName(), WiiTex::NewObject);
}

bool WiiRnd::GetProgressiveScan() { return mProgScan; }

void WiiRnd::DrawLine(const Vector3& a, const Vector3& b, const Hmx::Color&, bool) { // ????·
    int col;
    GXLoadPosMtxImm(unk_0x23C, 0);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_VA_TEX0MTXIDX);
    GXSetVtxDesc(GX_VA_CLR0, GX_VA_TEX0MTXIDX);
    RndGXBegin(GX_LINES, GX_VTXFMT6, 2);
    GXPosition3f32(a.x, a.y, a.z);
    GXColor1u32(col);
    GXPosition3f32(b.x, b.y, b.z);
    GXColor1u32(col);
    RndGXEnd();
}

BEGIN_HANDLERS(WiiRnd)
    HANDLE_ACTION(tri_frame, SetTriFrameRendering(_msg->Int(2)))
    HANDLE_ACTION(toggle_locked_cache, mUseLockedCache = !mUseLockedCache)
    HANDLE_ACTION(toggle_show_particle, mShowParticle = !mShowParticle)
    HANDLE_ACTION(toggle_asset_name, mShowAssetName = !mShowAssetName)
    HANDLE_ACTION(frames_buffered, mFramesBuffered = _msg->Int(2))
    HANDLE_SUPERCLASS(Rnd)
    HANDLE_CHECK(2722)
END_HANDLERS

void WiiRnd::SetOrthoProj() {
    if (unk_0x2B0) GXSetProjection(unk_0x1FC, GX_ORTHOGRAPHIC);
    else GXSetProjection(unk_0x1BC, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(unk_0x23C, 0);
    GXSetCurrentMtx(0);
}

void WiiRnd::DrawQuad(const Hmx::Rect& r) {
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_VA_TEX0MTXIDX);
    GXSetVtxDesc(GX_VA_TEX0, GX_VA_TEX0MTXIDX);
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

void* WiiRnd::GetCurrXFB() { return sDispFB; }

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