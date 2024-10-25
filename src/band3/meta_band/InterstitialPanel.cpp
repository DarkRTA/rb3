#include "meta_band/InterstitialPanel.h"
#include "InterstitialPanel.h"
#include "meta/DeJitterPanel.h"
#include "obj/ObjMacros.h"
#include "ui/PanelDir.h"
#include "ui/UIPanel.h"
#include "utl/Messages4.h"
#include "utl/Symbols.h"

InterstitialPanel::InterstitialPanel() : mCamshotDone(0), unk88(0), mShowing(1) {

}

void InterstitialPanel::Load(){ UIPanel::Load(); }

void InterstitialPanel::Enter(){
    DeJitterPanel::Enter();
    mCamshotDone = 0;
    unk88 = 0;
}

bool InterstitialPanel::Exiting() const {
    return UIPanel::Exiting() || !mCamshotDone || unk88 < 3;
}

void InterstitialPanel::Unload(){
    if(mLoader && mLoader->IsLoaded()){
        mDir = dynamic_cast<PanelDir*>(mLoader->GetDir());
        MILO_ASSERT_FMT(mDir, "%s not PanelDir", mLoader->mFile);
        RELEASE(mLoader);
    }
    UIPanel::Unload();
}

void InterstitialPanel::Draw(){
    if(mCamshotDone) unk88++;
    else if(mShowing) UIPanel::Draw();
}

void InterstitialPanel::SetCamshotDone(){ mCamshotDone = true; }

BEGIN_HANDLERS(InterstitialPanel)
    HANDLE_ACTION(transition_camshot_done, SetCamshotDone())
    HANDLE_ACTION(set_showing, mShowing = _msg->Int(2))
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x62)
END_HANDLERS

BackdropPanel::BackdropPanel() : mOutroDone(0) {

}

void BackdropPanel::Enter(){
    DeJitterPanel::Enter();
    mOutroDone = true;
}

void BackdropPanel::Exit(){
    mOutroDone = false;
    mDir->Handle(vignette_outro_msg, true);
    UIPanel::Exit();
}

bool BackdropPanel::Exiting() const {
    return UIPanel::Exiting() || !mOutroDone;
}

void BackdropPanel::SetOutroDone(){ mOutroDone = true; }

BEGIN_HANDLERS(BackdropPanel)
    HANDLE_ACTION(vignette_outro_done, SetOutroDone())
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x8A)
END_HANDLERS