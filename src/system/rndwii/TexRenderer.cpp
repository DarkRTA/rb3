#include "TexRenderer.h"
#include "rndobj/Rnd.h"
#include "rndobj/TexRenderer.h"

WiiTexRenderer::WiiTexRenderer() { }

WiiTexRenderer::~WiiTexRenderer() { }

void WiiTexRenderer::DrawPreClear() {
    if (!mShowing) return;
    if (TheRnd->UnkE4() == 4) return;
    DrawToTexture();
}

void WiiTexRenderer::Enter() {
    RndTexRenderer::Enter();
    if (mOutputTexture != NULL) {
        mDrawPreClear = true;
        UpdatePreClearState();
    }
}
