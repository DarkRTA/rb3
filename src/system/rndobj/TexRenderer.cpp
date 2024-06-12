#include "rndobj/TexRenderer.h"
#include "rndobj/Tex.h"
#include "rndobj/Cam.h"
#include "rndobj/Rnd.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

INIT_REVS(RndTexRenderer)

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

BEGIN_LOADS(RndTexRenderer)
    LOAD_REVS(bs)
    ASSERT_REVS(0xB, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    if(gRev > 2){
        LOAD_SUPERCLASS(RndAnimatable)
        LOAD_SUPERCLASS(RndDrawable)
        if(gRev > 10) LOAD_SUPERCLASS(RndPollable)
    }
    if(gRev < 1){
        char buf[0x100];
        FilePath fp;
        bs.ReadString(buf, 0x100);
        fp.SetRoot(buf);
    }
    else {
        char buf[0x80];
        bs.ReadString(buf, 0x80);
        if(mDraw && mDraw->Dir()){
            Hmx::Object* found = mDraw->Dir()->FindObject(buf, false);
            mDraw = dynamic_cast<RndDrawable*>(found);
        }
        else mDraw = 0;
    }
    if(gRev > 3) bs >> mCam;
    else mCam = 0;
    bs >> mOutputTexture;
    InitTexture();
    if(gRev > 1) bs >> mForce >> mImposterHeight;
    if(gRev > 4) bs >> mDrawResponsible;
    else mDrawResponsible = true;
    if(gRev > 5) bs >> mDrawPreClear;
    else mDrawPreClear = false;
    if(gRev > 6) bs >> mDrawWorldOnly;
    if(gRev > 7) bs >> mPrimeDraw;
    if(gRev > 8) bs >> mForceMips;
    if(gRev > 9) bs >> mMirrorCam;
    if(gRev > 10) bs >> mNoPoll;
    mDirty = true;
END_LOADS

void RndTexRenderer::InitTexture(){
    if(mForceMips){
        RndTex* tex = mOutputTexture;
        if(tex) tex->SetBitmap(tex->mWidth, tex->mHeight, tex->mBpp, tex->mType, true, 0);
    }
    mDirty = true;
}

DataNode RndTexRenderer::OnGetRenderTextures(DataArray* da){
    return GetRenderTextures(Dir());
}

BEGIN_HANDLERS(RndTexRenderer)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE(get_render_textures, OnGetRenderTextures)
    HANDLE_CHECK(0x280)
END_HANDLERS

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(RndTexRenderer)
    SYNC_PROP_MODIFY_ALT(draw, mDraw, mDirty = true; mFirstDraw = true; )
    SYNC_PROP_MODIFY_ALT(cam, mCam, mDirty = true)
    SYNC_PROP_MODIFY_ALT(output_texture, mOutputTexture, InitTexture())
    SYNC_PROP_MODIFY(force, mForce, mDirty = true)
    SYNC_PROP_MODIFY(imposter_height, mImposterHeight, mDirty = true)
    SYNC_PROP_MODIFY(draw_pre_clear, mDrawPreClear, UpdatePreClearState())
    {
        static Symbol _s("draw_world_only"); 
        if(sym == _s){
            if(_op == kPropSet) mDrawWorldOnly = _val.Int(0);
            else _val = DataNode(mDrawWorldOnly);
            return true; 
        }
    }
    {
        static Symbol _s("draw_responsible"); 
        if(sym == _s){
            if(_op == kPropSet) mDrawResponsible = _val.Int(0);
            else _val = DataNode(mDrawResponsible);
            return true; 
        }
    }
    {
        static Symbol _s("no_poll"); 
        if(sym == _s){
            if(_op == kPropSet) mNoPoll = _val.Int(0);
            else _val = DataNode(mNoPoll);
            return true; 
        }
    }
    SYNC_PROP_MODIFY(prime_draw, mPrimeDraw, mDirty = true)
    SYNC_PROP_MODIFY_ALT(force_mips, mForceMips, InitTexture())
    SYNC_PROP_MODIFY_ALT(mirror_cam, mMirrorCam, mDirty = true)
    SYNC_SUPERCLASS(RndAnimatable)
    SYNC_SUPERCLASS(RndDrawable)
    SYNC_SUPERCLASS(RndPollable)
END_PROPSYNCS
#pragma pop