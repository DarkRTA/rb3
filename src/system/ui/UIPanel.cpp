#include "ui/UIPanel.h"
#include "ui/PanelDir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

int UIPanel::sMaxPanelId = 0;

UIPanel::UIPanel() : mDir(0), mLoader(0), mFocusName(), mState(kUnloaded), mLoaded(0), mPaused(0), mShowing(1), mForceExit(0), mLoadRefs(0), mFilePath(), mPanelId(sMaxPanelId++) {
    MILO_ASSERT(sMaxPanelId < 0x8000, 0x24);
}

class ObjectDir* UIPanel::DataDir() {
    if (mDir) {
        return mDir->DataDir();
    }
    return Hmx::Object::DataDir();
}

void UIPanel::SetTypeDef(DataArray* data){
    if(mTypeDef != data){
        Hmx::Object::SetTypeDef(data);
        if(data != 0){
            data->FindData(focus, mFocusName, false);
            data->FindData(force_exit, mForceExit, false);
        }
    }
}

void UIPanel::CheckLoad(){
    if(++mLoadRefs == 1) Load();
}

UIPanel::~UIPanel(){
    Unload();
}


BEGIN_HANDLERS(UIPanel)
    HANDLE_EXPR(is_loaded, IsLoaded())
    HANDLE_EXPR(check_is_loaded, CheckIsLoaded())
    HANDLE_EXPR(is_unloaded, mState == kUnloaded)
    HANDLE_EXPR(is_referenced, mLoadRefs != 0)
    HANDLE_EXPR(is_up, mState == kUp)
    HANDLE_ACTION(set_paused, SetPaused(_msg->Int(2)))
    HANDLE_EXPR(paused, mPaused)
    HANDLE(load, OnLoad)
    HANDLE_ACTION(unload, CheckUnload())
    HANDLE_ACTION(unset_loaded_dir, UnsetLoadedDir())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(450)
END_HANDLERS
