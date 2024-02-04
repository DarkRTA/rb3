#include "wiirnd.hpp"
#include "rb3/hmx/rect.hpp"
#include "revolution/GX.h"
#include "revolution/OS.h"
#include "types.h"
bool FakeGXinBegin, FakeGXIntMode;

WiiRnd::WiiRnd() {

}

WiiRnd::~WiiRnd() {

}

void FakeGXBegin(GXPrimitive mode, GXVtxFmtIdx idx, u16 verts) {
    FakeGXinBegin = true;
    FakeGXIntMode = OSDisableInterrupts();
    GXBegin(mode, idx, verts);
}

void FakeGXEnd() {
    OSRestoreInterrupts(FakeGXIntMode);
    FakeGXinBegin = false;
}

void WiiRnd::DrawQuad(const Hmx::Rect& rect) {
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_VA_TEX0MTXIDX);
    GXSetVtxDesc(GX_VA_TEX0, GX_VA_TEX0MTXIDX);
    FakeGXBegin(GX_QUADS, GX_VTXFMT6, 4U);
    GXPosition3f32(rect.x1, rect.y1, 0.0f);
    GXTexCoord2u8(0,0);
    GXPosition3f32(rect.x1, rect.y2, 0.0f);
    GXTexCoord2u8(0,1);
    GXPosition3f32(rect.x2, rect.y2, 0.0f);
    GXTexCoord2u8(1,1);
    GXPosition3f32(rect.x2, rect.y1, 0.0f);
    GXTexCoord2u8(1,0);
    FakeGXEnd();
}

WiiRnd TheWiiRnd();
