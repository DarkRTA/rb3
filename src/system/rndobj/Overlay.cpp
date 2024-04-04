#include "rndobj/Overlay.h"
#include "os/Debug.h"

std::list<RndOverlay*> RndOverlay::sOverlays;

void RndOverlay::Terminate() {
    for (std::list<RndOverlay*>::iterator i = sOverlays.begin(); i != sOverlays.end(); i++) delete *i;
}

RndOverlay::~RndOverlay(){

}

RndOverlay::RndOverlay(const DataArray* da) : mShowing(0), mLines(), mLine(), mBackColor(0.0f, 0.0f, 0.0f, 0.2f), mTextColor(), 
    mCursorChar(-1), mCallback(0), mTimer(), mTimeout(0.0f), mModal(0), mDumpCount(0) {
    mName = da->Str(0);
    int lines = 1;
    da->FindData("lines", lines, false);
    SetLines(lines);
    da->FindData("showing", mShowing, false);
    da->FindData("color", mBackColor, false);
    da->FindData("modal", mModal, false);
    da->FindData("text_color", mTextColor, false);
}

void RndOverlay::SetLines(int lines) {
    MILO_ASSERT(lines >= 1, 117);
    int i;
    for (mLine = mLines.begin(); ++mLine != mLines.end(); i++) {}
    if (i == lines) return;
    mLines.resize(i);
    mLine = mLines.end();
}
