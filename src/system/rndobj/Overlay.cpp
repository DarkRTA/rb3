#include "rndobj/Overlay.h"

std::list<RndOverlay*> RndOverlay::sOverlays;

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
