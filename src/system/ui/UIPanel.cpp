#include "ui/UIPanel.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

UIPanel::UIPanel() : mDir(0), mLoader(0), mFocusName(), mState(kUnloaded), mLoaded(0), mPaused(0), mShowing(1), mForceExit(0), mLoadRefs(0), mFilePath(), mPanelId(sMaxPanelId++) {
    MILO_ASSERT(sMaxPanelId < 0x8000, 0x24);
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
