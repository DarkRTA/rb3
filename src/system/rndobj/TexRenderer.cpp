#include "rndobj/TexRenderer.h"
#include "rndobj/Tex.h"
#include "rndobj/Cam.h"
#include "rndobj/Rnd.h"

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

void RndTexRenderer::DrawShowing(){
    if(mDrawPreClear) return;
    else DrawToTexture();
}

#pragma push
#pragma dont_inline on
void RndTexRenderer::DrawToTexture(){
    if(TheRnd->DrawMode() == 0){
        RndDrawable* draw = mDraw;
        if((Hmx::Object*)Dir() != draw){
            if(Showing() && !mDrawWorldOnly){

            }
        }
    }
}
#pragma pop

float RndTexRenderer::StartFrame(){
    RndDrawable* draw = mDraw;
    RndAnimatable* anim = dynamic_cast<RndAnimatable*>(draw);
    if(anim){
        return anim->StartFrame();
    }
    else return 0.0f;
}

float RndTexRenderer::EndFrame(){
    RndDrawable* draw = mDraw;
    RndAnimatable* anim = dynamic_cast<RndAnimatable*>(draw);
    if(anim){
        return anim->EndFrame();
    }
    else return 0.0f;
}

void RndTexRenderer::SetFrame(float f1, float f2){
    RndDrawable* draw = mDraw;
    RndAnimatable* anim = dynamic_cast<RndAnimatable*>(draw);
    if(anim){
        anim->SetFrame(f1, f2);
        mDirty = true;
    }
}

void RndTexRenderer::UpdatePreClearState(){
    TheRnd->PreClearDrawAddOrRemove(this, mDrawPreClear, false);
    mDirty = true;
}

BEGIN_COPYS(RndTexRenderer)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_SUPERCLASS(RndDrawable)
    COPY_SUPERCLASS(RndPollable)
    CREATE_COPY(RndTexRenderer)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mDraw)
        COPY_MEMBER(mCam)
        COPY_MEMBER(mOutputTexture)
        COPY_MEMBER(mForce)
        COPY_MEMBER(mDrawWorldOnly)
        COPY_MEMBER(mDrawResponsible)
        COPY_MEMBER(mImposterHeight)
        COPY_MEMBER(mDrawPreClear)
        COPY_MEMBER(mPrimeDraw)
        COPY_MEMBER(mForceMips)
        COPY_MEMBER(mMirrorCam)
        COPY_MEMBER(mNoPoll)
        InitTexture();
        mDirty = true;
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(RndTexRenderer, 0x1FA)