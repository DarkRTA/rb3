#include "TexRenderer.h"
#include "rndobj/Rnd.h"
#include "rndobj/TexRenderer.h"

WiiTexRenderer::WiiTexRenderer() {}

WiiTexRenderer::~WiiTexRenderer() {}

void WiiTexRenderer::DrawPreClear() {
    if (!Showing())
        return;
    if (TheRnd->DrawMode() == 4)
        return;
    DrawToTexture();
}

void WiiTexRenderer::Enter() {
    RndTexRenderer::Enter();
    if (mOutputTexture != NULL) {
        mDrawPreClear = true;
        UpdatePreClearState();
    }
}
