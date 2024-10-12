#include "UIPanel.h"
#include "utl/MemMgr.h"
#include "ui/UIComponent.h"
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
    if (mDir) { mDir->SetOwnerPanel(0); }
    mDir = dir;
    mLoaded = b;
    mDir->SetOwnerPanel(this);
}

void UIPanel::UnsetLoadedDir() {
    MILO_ASSERT(!mLoader, 120);
    if (mDir) { mDir->SetOwnerPanel(0); }
    mDir = NULL;
    mLoaded = false;
}

void UIPanel::Load(){
    if(mState != kUnloaded) MILO_FAIL("Can't load a panel already in state %i", mState);
    HandleType(load_msg);
    if(TypeDef()){
        static Symbol fileSym("file");
        FilePath fp;
        LoaderPos pos = kLoadBack;
        DataArray* found = TypeDef()->FindArray(fileSym, false);
        if(found){
            Hmx::Object* thisObj = DataSetThis(this);
            fp.Set(FileGetPath(found->File(), 0), found->Str(1));
            if(found->Size() == 3){
                pos = (LoaderPos)found->Int(2);
            }
            DataSetThis(thisObj);
        }
        int heapInt = GetCurrentHeapNum();
        DataArray* heapArr = TypeDef()->FindArray(heap, false);
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
    HandleType(unload_msg);
    if(UIPanel::IsLoaded()){
        bool b = false;
        if(TypeDef()){
            DataArray* unloadArr = TypeDef()->FindArray(unload_async, false);
            if(unloadArr){
                if(unloadArr->Int(1) != 0) b = true;
            }
        }
        if(b){
            TheLoadMgr.StartAsyncUnload();
            mFilePath.SetRoot(mDir->GetPathName());
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

void UIPanel::PollForLoading(){
    MILO_ASSERT(mState == kUnloaded, 0xE0);
    if(mLoader && mLoader->IsLoaded()){
        class PanelDir* pDir = dynamic_cast<class PanelDir*>(mLoader->GetDir());
        MILO_ASSERT_FMT(pDir, "%s not PanelDir", mLoader->mFile);
        delete mLoader;
        mLoader = 0;
        SetLoadedDir(pDir, mLoaded);
    }
}

bool UIPanel::IsLoaded() const {
    if(mState != kUnloaded) return true;
    if(mLoader && !mLoader->IsLoaded()) return false;
    DataNode node = const_cast<UIPanel*>(this)->HandleType(is_loaded_msg);
    if(node.Type() != kDataUnhandled) return node.Int();
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

bool UIPanel::Unloading() const {
    if(!mFilePath.empty()){
        if(TheLoadMgr.GetLoader(mFilePath)){
            return true;
        }
        const_cast<UIPanel*>(this)->mFilePath.SetRoot(gNullStr);
    }
    return false;
}

void UIPanel::Enter(){
    MILO_ASSERT(mState == kDown, 0x14E);
    if(!mFocusName.empty() && mDir){
        SetFocusComponent(mDir->FindComponent(mFocusName.c_str()));
    }
    MILO_ASSERT(mLoadRefs > 0, 0x154);
    mState = kUp;
    if(mDir && !mLoaded){
        mDir->Enter();
    }
    HandleType(enter_msg);
}

void UIPanel::Exit(){
    MILO_ASSERT(mState == kUp, 0x165);
    bool theBool = false;
    const DataArray* td = TypeDef();
    if(td){
        td->FindData("reset_focus", theBool, false);
    }
    if(!theBool && FocusComponent()){
        mFocusName = FocusComponent()->Name();
    }
    MILO_ASSERT(mLoadRefs > 0, 0x16E);
    mState = kDown;
    HandleType(exit_msg);
    if(mDir && !mLoaded){
        mDir->Exit();
    }
}

void UIPanel::Poll(){
    HandleType(poll_msg);
    if(mDir && !mLoaded){
        mDir->Poll();
    }
}

void UIPanel::Draw(){
    class PanelDir* pDir = mDir;
    if(!pDir) return;
    if(mLoaded) return;
    pDir->DrawShowing();
}

void UIPanel::SetFocusComponent(UIComponent* comp){
    if(mDir){
        mDir->SetFocusComponent(comp, gNullStr);
    }
}

BEGIN_HANDLERS(UIPanel)
    HANDLE_EXPR(is_loaded, IsLoaded())
    HANDLE_EXPR(check_is_loaded, CheckIsLoaded())
    HANDLE_EXPR(is_unloaded, GetState() == kUnloaded)
    HANDLE_EXPR(is_referenced, IsReferenced())
    HANDLE_EXPR(is_up, GetState() == kUp)
    HANDLE_ACTION(set_paused, SetPaused(_msg->Int(2)))
    HANDLE_EXPR(paused, Paused())
    HANDLE(load, OnLoad)
    HANDLE_ACTION(unload, CheckUnload())
    HANDLE_ACTION(set_focus, SetFocusComponent(_msg->Obj<UIComponent>(2)))
    HANDLE_ACTION(enter, Enter())
    HANDLE_ACTION_STATIC(exit, Exit())
    HANDLE_EXPR(loaded_dir, mDir)
    HANDLE_ACTION(set_showing, SetShowing(_msg->Int(2)))
    HANDLE_EXPR(showing, Showing())
    HANDLE_ACTION(set_loaded_dir, SetLoadedDir(_msg->Obj<class PanelDir>(2), false))
    HANDLE_ACTION(set_loaded_dir_shared, SetLoadedDir(_msg->Obj<class PanelDir>(2), true))
    HANDLE_ACTION(unset_loaded_dir, UnsetLoadedDir())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_MEMBER_PTR(mDir)
    HANDLE_CHECK(450)
END_HANDLERS

DataNode UIPanel::OnLoad(DataArray* da){
    CheckLoad();
    if(da->Size() > 2){
        if(da->Int(2) && mLoader){
            TheLoadMgr.PollUntilLoaded(mLoader, 0);
            bool bLoaded = CheckIsLoaded();
            MILO_ASSERT(bLoaded, 0x1D1);
        }
    }
    return DataNode(0);
}
