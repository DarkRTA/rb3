#include "bandobj/PatchRenderer.h"
#include "utl/Symbols.h"

RndDir* PatchRenderer::sBlankPatch;
RndDir* PatchRenderer::sTestPatch;

PatchRenderer::PatchRenderer() : mBackMat(this, 0), mOverlayMat(this, 0), mTestMode("blank"), mPosition("front") {

}

BEGIN_HANDLERS(PatchRenderer)
    HANDLE_SUPERCLASS(RndTexRenderer)
    HANDLE_CHECK(0xA8)
END_HANDLERS

BEGIN_PROPSYNCS(PatchRenderer)
    SYNC_PROP_MODIFY(test_mode, mTestMode, SetPatch(mTestMode == "test" ? sTestPatch : sBlankPatch))
    SYNC_PROP(position, mPosition)
    SYNC_PROP(back_mat, mBackMat)
    SYNC_PROP(overlay_mat, mOverlayMat)
    SYNC_SUPERCLASS(RndTexRenderer)
END_PROPSYNCS