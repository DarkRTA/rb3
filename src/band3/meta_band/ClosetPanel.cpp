#include "meta_band/ClosetPanel.h"
#include "game/BandUser.h"
#include "meta/DeJitterPanel.h"
#include "meta_band/CharData.h"
#include "meta_band/ClosetMgr.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/User.h"
#include "rndobj/Tex.h"
#include "rndobj/TexRenderer.h"
#include "ui/UIPanel.h"
#include "utl/MakeString.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "world/CameraShot.h"
#include "world/Dir.h"
#include <cstdlib>

ClosetPanel::ClosetPanel() : mClosetMgr(0), mCameraManager(0), mPortraitRenderer(0), mPortraitState(0) {

}

void ClosetPanel::Load(){
    UIPanel::Load();
    mClosetMgr = ClosetMgr::GetClosetMgr();
    MILO_ASSERT(mClosetMgr, 0x25);
}

void ClosetPanel::FinishLoad(){
    UIPanel::FinishLoad();
    WorldDir* pWorldDir = dynamic_cast<WorldDir*>(mDir);
    MILO_ASSERT(pWorldDir, 0x2D);
    mCameraManager = &pWorldDir->mCameraManager;
    MILO_ASSERT(mCameraManager, 0x2F);
    mClosetMgr->SetCurrentClosetPanel(this);
}

void ClosetPanel::Enter(){ DeJitterPanel::Enter(); }

void ClosetPanel::Poll(){
    DeJitterPanel::Poll();
    LocalBandUser* user = mClosetMgr->mUser;
    if(mPortraitState == 2 && user){
        MILO_ASSERT(mPortraitRenderer, 0x40);
        mPortraitRenderer->SetShowing(false);
        CharData* pCharData = user->GetChar();
        MILO_ASSERT(pCharData, 0x44);
        RndTex* pOutputTexture = mPortraitRenderer->mOutputTexture;
        MILO_ASSERT(pOutputTexture, 0x47);
        pCharData->CachePortraitTex(pOutputTexture);
        mPortraitState = 0;
    }
}

void ClosetPanel::Draw(){
    UIPanel::Draw();
    if(mPortraitState == 1) mPortraitState = 2;
}

void ClosetPanel::Exit(){
    UIPanel::Exit();
    mClosetMgr->ClearCurrentClosetPanel();
}

bool ClosetPanel::Exiting() const {
    return UIPanel::Exiting() || mPortraitState != 0;
}

void ClosetPanel::Unload(){
    UIPanel::Unload();
    MILO_ASSERT(mClosetMgr, 0x69);
    MILO_ASSERT(mCameraManager, 0x6A);
    mClosetMgr = 0;
    mCameraManager = 0;
    mPortraitRenderer = 0;
}

CamShot* ClosetPanel::GetCurrentShot(){
    return mCameraManager->mCurrentShot;
}

void ClosetPanel::GotoShot(Symbol s){
    CamShot* symshot = mDir->Find<CamShot>(s.Str(), true);
    CamShot* cur = GetCurrentShot();
    if(!cur) mCameraManager->ForceCameraShot(symshot);
    else {
        String curname(cur->Name());
        String symname(symshot->Name());
        if(symname != curname){
            mCameraManager->ForceCameraShot(symshot);
        }
    }
}

void ClosetPanel::CycleCamera(){
    CamShot* pCurrentShot = GetCurrentShot();
    MILO_ASSERT(pCurrentShot, 0x93);
    String shotname(pCurrentShot->Name());
    shotname = shotname.substr(0, shotname.length() - 5);
    std::vector<String> substrs;
    if(shotname.split("_", substrs) > 1){
        int l6 = strtol(substrs.back().c_str(), 0, 10) + 1;
        String str30;
        for(int i = 0; i < substrs.size() - 1; i++){
            str30 += substrs[i] + "_";
        }
        const char* shotstr = MakeString("%s%d.shot", str30, l6);
        CamShot* foundshot = mDir->Find<CamShot>(shotstr, false);
        if(!foundshot){
            shotstr = MakeString("%s%d.shot", str30, 1);
            foundshot = mDir->Find<CamShot>(shotstr, false);
        }
        if(foundshot != pCurrentShot){
            mCameraManager->ForceCameraShot(foundshot);
        }
    }
}

void ClosetPanel::TakePortrait(){
    MILO_ASSERT(mPortraitRenderer, 0xB9);
    mPortraitRenderer->mDirty = true;
    mPortraitRenderer->SetShowing(true);
    mPortraitState = 1;
}

void ClosetPanel::GotoArtMakerShot(){
    CamShot* pCurrentShot = GetCurrentShot();
    MILO_ASSERT(pCurrentShot, 0xC5);
    String shotname(pCurrentShot->Name());
    const char* shotstr = MakeString("am_%s", shotname);
    CamShot* shot = mDir->Find<CamShot>(shotstr, false);
    if(shot) mCameraManager->ForceCameraShot(shot);
}

void ClosetPanel::LeaveArtMakerShot(){
    CamShot* pCurrentShot = GetCurrentShot();
    MILO_ASSERT(pCurrentShot, 0xD3);
    String shotname(pCurrentShot->Name());
    shotname = shotname.substr(3, shotname.length());
    CamShot* shot = mDir->Find<CamShot>(shotname.c_str(), false);
    if(shot) mCameraManager->ForceCameraShot(shot);
}

void ClosetPanel::SetPortraitRenderer(RndTexRenderer* renderer){
    mPortraitRenderer = renderer;
    if(mPortraitRenderer) mPortraitRenderer->SetShowing(false);
}

BEGIN_HANDLERS(ClosetPanel)
    HANDLE_EXPR(get_user, GetUser())
    HANDLE_ACTION(goto_shot, GotoShot(_msg->Sym(2)))
    HANDLE_ACTION(set_portrait_renderer, SetPortraitRenderer(_msg->Obj<RndTexRenderer>(2)))
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xF7)
END_HANDLERS