#include "rndobj/TexRenderer.h"
#include "rndobj/Tex.h"
#include "rndobj/Cam.h"

RndTexRenderer::RndTexRenderer() : mDirty(1), mForce(0), mDrawPreClear(1), mDrawWorldOnly(0), mDrawResponsible(1), 
    mNoPoll(0), mPrimeDraw(0), mFirstDraw(1), mForceMips(0), mImposterHeight(0.0f), 
    mOutputTexture(this, 0), mDraw(this, 0), mCam(this, 0), mMirrorCam(this, 0) {

}

RndTexRenderer::~RndTexRenderer(){

}

void RndTexRenderer::ListAnimChildren(std::list<RndAnimatable*>& children) const {
    // RndAnimatable* anim = dynamic_cast<RndAnimatable*>(mDraw); // ??? how is a cast like this even possible
}