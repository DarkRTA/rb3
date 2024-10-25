#include "meta_band/InterstitialPanel.h"
#include "InterstitialPanel.h"
#include "meta/DeJitterPanel.h"
#include "obj/ObjMacros.h"
#include "ui/PanelDir.h"
#include "ui/UIPanel.h"
#include "utl/Symbols.h"

InterstitialPanel::InterstitialPanel() : unk85(0), unk88(0), unk8c(1) {

}

void InterstitialPanel::Load(){ UIPanel::Load(); }

void InterstitialPanel::Enter(){
    DeJitterPanel::Enter();
    unk85 = 0;
    unk88 = 0;
}

bool InterstitialPanel::Exiting() const {
    return UIPanel::Exiting() || !unk85 || unk88 < 3;
}

void InterstitialPanel::Unload(){
    if(mLoader && mLoader->IsLoaded()){
        mDir = dynamic_cast<PanelDir*>(mLoader->GetDir());
        if(!mDir){
            MILO_FAIL("%s not PanelDir", mLoader->mFile);
        }
        RELEASE(mLoader);
    }
    UIPanel::Unload();
}

void InterstitialPanel::Draw(){
    if(unk85) unk88++;
    else if(unk8c) UIPanel::Draw();
}

void InterstitialPanel::SetCamshotDone(){ unk85 = true; }

BEGIN_HANDLERS(InterstitialPanel)
    HANDLE_ACTION(transition_camshot_done, SetCamshotDone())
    HANDLE_ACTION(set_showing, unk8c = _msg->Int(2))
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x62)
END_HANDLERS