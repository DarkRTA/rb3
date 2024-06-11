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
    RndDrawable* draw = mDraw;
    RndAnimatable* anim = dynamic_cast<RndAnimatable*>(draw);
    if(anim) children.push_back(anim);
}

void RndTexRenderer::ListDrawChildren(std::list<RndDrawable*>& children){
    if(mDraw && mDrawResponsible) children.push_back(mDraw);
}

void RndTexRenderer::ListPollChildren(std::list<RndPollable*>& children) const {
    RndDrawable* draw = mDraw;
    if(draw && mNoPoll){
        RndPollable* poll = dynamic_cast<RndPollable*>(draw);
        if(poll) children.push_back(poll);
    }
}

void RndTexRenderer::Enter(){ RndPollable::Enter(); }

float RndTexRenderer::StartFrame(){
    RndDrawable* draw = mDraw;
    RndAnimatable* anim = dynamic_cast<RndAnimatable*>(draw);
    if(anim){
        return anim->StartFrame();
    }
    else return 0.0f;
}