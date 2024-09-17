#include "bandobj/PatchRenderer.h"
#include "rndobj/Rnd.h"
#include "utl/Symbols.h"

INIT_REVS(PatchRenderer);
RndDir* PatchRenderer::sBlankPatch;
RndDir* PatchRenderer::sTestPatch;

void PatchRenderer::Init(){
    DataArray* cfg = SystemConfig("objects", "PatchRenderer");
    sBlankPatch = Hmx::Object::New<RndDir>();
    if(TheLoadMgr.EditMode()){
        DataArray* patchArr = cfg->FindArray("test_patch", false);
        if(patchArr){
            ObjectDir* loaded = DirLoader::LoadObjects(FilePath(FileGetPath(patchArr->File(), 0), patchArr->Str(1)), 0, 0);
            sTestPatch = dynamic_cast<RndDir*>(loaded);
        }
        if(!sTestPatch) sTestPatch = Hmx::Object::New<RndDir>();
        InitResources();
    }
    Register();
}

void PatchRenderer::Terminate(){
    RELEASE(sTestPatch);
    RELEASE(sBlankPatch);
}

PatchRenderer::PatchRenderer() : mBackMat(this, 0), mOverlayMat(this, 0), mTestMode("blank"), mPosition("front") {

}

BEGIN_COPYS(PatchRenderer)
    CREATE_COPY_AS(PatchRenderer, p)
    MILO_ASSERT(p, 0x4C);
    COPY_MEMBER_FROM(p, mBackMat)
    COPY_MEMBER_FROM(p, mOverlayMat)
    COPY_MEMBER_FROM(p, mTestMode)
    COPY_MEMBER_FROM(p, mPosition)
    COPY_SUPERCLASS_FROM(RndTexRenderer, p)
END_COPYS

SAVE_OBJ(PatchRenderer, 0x5A)

BEGIN_LOADS(PatchRenderer)
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    LOAD_SUPERCLASS(RndTexRenderer)
    bs >> mTestMode;
    bs >> mPosition;
    if(gRev != 0){
        bs >> mBackMat;
        bs >> mOverlayMat;
    }
END_LOADS

void PatchRenderer::DrawBefore(){
    unk90 = RndEnviron::sCurrent;
    if(mBackMat){
        Hmx::Rect rect(0,0,mOutputTexture->Height(),mOutputTexture->Width());
        TheRnd->DrawRect(rect, Hmx::Color(), mBackMat, 0, 0);
    }
}

void PatchRenderer::DrawAfter(){
    if(mOverlayMat){
        Hmx::Rect rect(0,0,mOutputTexture->Height(),mOutputTexture->Width());
        TheRnd->DrawRect(rect, Hmx::Color(), mOverlayMat, 0, 0);
    }
    if(unk90 != RndEnviron::sCurrent) unk90->Select(0);
}

void PatchRenderer::DrawShowing(){
    if(TheLoadMgr.EditMode() && !mDraw){
        mDraw = mTestMode == "test" ? sTestPatch : sBlankPatch;
    }
    RndTexRenderer::DrawShowing();
}

void PatchRenderer::SetPatch(RndDir* dir){
    mDraw = dir ? dir : sBlankPatch;
    mDirty = true;
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