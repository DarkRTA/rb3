#include "ui/UIPanel.h"
#include "ui/PanelDir.h"
#include "obj/DirLoader.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

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

void UIPanel::CheckUnload(){
    if(mLoadRefs >= 1){
        if(mState == kDown){
            Handle(exit_complete_msg.Data(), false);
        }
        if(--mLoadRefs == 0) Unload();
    }
}

bool UIPanel::IsLoaded() const {
    if(mState == kUnloaded){
        if(mLoader == 0 || mLoader->IsLoaded()){
            // this doesn't currently work because HandleType is not const, but this method is
            // DataNode node = HandleType(is_loaded_msg.Data());
        }
        else return false;
    }
    else return true;
}

bool UIPanel::CheckIsLoaded(){
    if(mState != kUnloaded) return true;
    else {
        PollForLoading();
        if(IsLoaded()){
            FinishLoad();
            return true;
        }
        else return false;
    }
}

void UIPanel::FinishLoad(){
    HandleType(finish_load_msg.Data());
    MILO_ASSERT(mLoadRefs > 0, 0x118);
    mState = kDown;
}

UIPanel::~UIPanel(){
    Unload();
}

bool UIPanel::Entering() const {
    if(mDir && !mLoaded){
        return mDir->IsDirPtr(); // TODO: find the right virtual function called here
    }
    else return false;
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
