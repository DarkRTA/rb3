#include "char/CharClipSet.h"

CharClipSet::CharClipSet() : mCharFilePath(), mPreviewChar(this, 0), mPreviewClip(this, 0), mStillClip(this, 0) {
    ResetPreviewState();
    mRate = k1_fpb;
}

CharClipSet::~CharClipSet(){
    
}