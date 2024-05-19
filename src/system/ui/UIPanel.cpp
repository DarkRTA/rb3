#include "UIPanel.h"
#include "utl/MemMgr.h"
#include "ui/PanelDir.h"
#include "obj/DirLoader.h"
#include "obj/Object.h"
#include "obj/DataUtl.h"
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
    if(TypeDef() != data){
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
            Handle(exit_complete_msg, false);
        }
        if(--mLoadRefs == 0) Unload();
    }
}

void UIPanel::SetLoadedDir(class PanelDir* dir, bool b) {
    MILO_ASSERT(!mLoader, 106);
    MILO_ASSERT(dir, 107);
    if (mDir) { mDir->mPanel = NULL; }
    mDir = dir;
    mLoaded = b;
    mDir->mPanel = this;
}

void UIPanel::UnsetLoadedDir() {
    MILO_ASSERT(!mLoader, 120);
    if (mDir) { mDir->mPanel = NULL; }
    mDir = NULL;
    mLoaded = false;
}

void UIPanel::Load(){
    if(mState != kUnloaded) MILO_FAIL("Can't load a panel already in state %i", mState);
    const_cast<UIPanel*>(this)->HandleType(load_msg);
    if(mTypeDef){
        static Symbol fileSym("file");
        FilePath fp;
        LoaderPos pos = kLoadBack;
        DataArray* found = mTypeDef->FindArray(fileSym, false);
        if(found){
            Hmx::Object* thisObj = DataSetThis(this);
            fp.Set(FileGetPath(found->mFile.Str(), 0), found->Str(1));
            if(found->Size() == 3){
                pos = (LoaderPos)found->Int(2);
            }
            DataSetThis(thisObj);
        }
        int heapInt = GetCurrentHeapNum();
        DataArray* heapArr = mTypeDef->FindArray(heap, false);
        if(heapArr){
            heapInt = MemFindHeap(heapArr->Str(1));
        }
        if(!fp.empty()){
            MemPushHeap(heapInt);
            MILO_ASSERT(!mLoader, 0xAD);
            mLoader = new DirLoader(fp, pos, 0, 0, 0, false);
            MILO_ASSERT(mLoader, 0xAF);
            mLoaded = false;
            MemPopHeap();
        }
    }
}

void UIPanel::Unload(){
    const_cast<UIPanel*>(this)->HandleType(unload_msg);
    if(UIPanel::IsLoaded()){
        bool b = false;
        if(mTypeDef){
            DataArray* unloadArr = mTypeDef->FindArray(unload_async, false);
            if(unloadArr){
                if(unloadArr->Int(1) != 0) b = true;
            }
        }
        if(b){
            TheLoadMgr.StartAsyncUnload();
            mFilePath.SetRoot(0);
        }
        else mFilePath.SetRoot(gNullStr);

        delete mDir;
        mDir = 0;
        if(b) TheLoadMgr.FinishAsyncUnload();
    }
    delete mLoader;
    mLoader = 0;
    MILO_ASSERT(mLoadRefs == 0, 0xD9);
    mLoaded = false;
    mState = kUnloaded;
}

bool UIPanel::IsLoaded() const {
    if(mState != kUnloaded) return true;
    if(mLoader && !mLoader->IsLoaded()) return false;
    DataNode node = const_cast<UIPanel*>(this)->HandleType(is_loaded_msg);
    if(node.Type() != kDataUnhandled) return node.Int(0);
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
    HandleType(finish_load_msg);
    MILO_ASSERT(mLoadRefs > 0, 0x118);
    mState = kDown;
}

UIComponent* UIPanel::FocusComponent(){
    if(mDir) return mDir->FocusComponent();
    else return 0;
}

UIPanel::~UIPanel(){
    Unload();
}

bool UIPanel::Entering() const {
    if(mDir && !mLoaded) return mDir->Entering();
    else return false;
}

bool UIPanel::Exiting() const {
    if(mDir && !mLoaded) return mDir->Exiting();
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
