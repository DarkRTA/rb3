#include "char/FileMerger.h"
#include "char/FileMergerOrganizer.h"
#include "obj/Msg.h"
#include "obj/Object.h"
#include "utl/Loader.h"
#include "utl/MemMgr.h"
#include "utl/Symbols.h"

#define kNoHeap -3
#define kSystemHeap -1

FileMerger* FileMerger::sFmDeleting;

#pragma push
#pragma pool_data off
void FileMerger::Merger::Clear(){
    mLoaded.SetRoot("");
    Hmx::Object* objectsOwner = mLoadedObjects.Owner();
    if(objectsOwner != sFmDeleting){
        static Message msg("on_pre_clear", 0);
        msg[0] = mName;
        objectsOwner->HandleType(msg);
    }
    while(!mLoadedObjects.empty()){
        delete mLoadedObjects.front();
    }
    ObjectDir* mergerDir = MergerDir();
    if(mergerDir){
        while(!mLoadedSubdirs.empty()){
            ObjectDir* cur = mLoadedSubdirs.front();
            mLoadedSubdirs.pop_front();
            mergerDir->RemoveSubDir(cur);
        }
    }
    else {
        mLoadedSubdirs.clear();
    }
}
#pragma pop

FileMerger::FileMerger() : mMergers(this), mAsyncLoad(0), mLoadingLoad(0), unk44(0), unk50(0), mHeap(GetCurrentHeapNum()), mCoordinator(this) {
    MILO_ASSERT(MemNumHeaps() == 0 || (mHeap != kNoHeap && mHeap != kSystemHeap), 0x73);
}

FileMerger::~FileMerger(){
    FileMerger* old = sFmDeleting;
    sFmDeleting = this;
    Clear();
    sFmDeleting = old;
}

FileMerger::Merger* FileMerger::FindMerger(Symbol name, bool warn){
    int idx = FindMergerIndex(name, warn);
    if(idx != -1) return &mMergers[idx];
    else return nullptr;
}

int FileMerger::FindMergerIndex(Symbol name, bool warn){
    for(int i = 0; i < mMergers.size(); i++){
        if(mMergers[i].mName == name) return i;
    }
    if(warn) MILO_WARN("%s could not find Merger %s", PathName(this), name);
    return -1;
}

void FileMerger::Select(Symbol name, const FilePath& fp, bool b){
    Merger* merger = FindMerger(name, true);
    if(merger){
        merger->SetSelected(fp, b);
    }
}

bool FileMerger::StartLoad(bool b){
    StartLoadInternal(b, false);
}

bool FileMerger::StartLoadInternal(bool b1, bool b2){
    static Message msg("change_files", 0, 0);
    msg[0] = b1;
    msg[1] = b2;
    HandleType(msg);
    for(int i = 0; i < mMergers.size(); i++){
        Merger& cur = mMergers[i];
        if(NeedsLoading(cur)){
            AppendLoader(cur);
        }
    }
    Merger* tmp = nullptr;
    if(unk44 != 0){
        tmp = mFilesPending.front();
        mFilesPending.pop_front();
    }
    mFilesPending.sort(FileMergerSort);
    if(unk44 != 0) mFilesPending.push_front(tmp);
    mAsyncLoad = b1;
    mLoadingLoad = b2;

    if(mFilesPending.empty() || unk44 != 0 || mCoordinator != this) return false;
    else {
        if(b1) TheFileMergerOrganizer->AddFileMerger(this);
        else {
            LaunchNextLoader();
            while(!mFilesPending.empty()){
                TheLoadMgr.Poll();
            }
        }
        return true;
    }
}

FileMerger::Merger* FileMerger::InMerger(Hmx::Object* o){
    for(int i = 0; i < mMergers.size(); i++){
        Merger& cur = mMergers[i];
        if(cur.IsObjectLoaded(o)){
            return &cur;
        }
    }
    return nullptr;
}

void FileMerger::Clear(){
    for(int i = 0; i < mMergers.size(); i++){
        mMergers[i].Clear();
    }
    if(unk44 != 0){
        Merger* merger = mFilesPending.front();
        mFilesPending.clear();
        mFilesPending.push_front(merger);
        DeleteCurLoader();
    }
}

void FileMerger::ClearSelections(){
    for(int i = 0; i < mMergers.size(); i++){
        mMergers[i].mSelected.SetRoot("");
    }
    if(unk44 != 0){
        Merger* merger = mFilesPending.front();
        mFilesPending.clear();
        mFilesPending.push_front(merger);
        DeleteCurLoader();
    }
}

bool FileMerger::NeedsLoading(FileMerger::Merger& merger){

}

BEGIN_CUSTOM_PROPSYNC(FileMerger::Merger)
    SYNC_PROP(name, o.mName)
    SYNC_PROP(selected, o.mSelected)
    SYNC_PROP_SET(loaded, o.mLoaded, )
    SYNC_PROP(dir, o.mDir)
    SYNC_PROP(proxy, o.mProxy)
    SYNC_PROP(subdirs, o.mSubdirs)
    SYNC_PROP(preclear, o.mPreClear)
    {
        static Symbol _s("loaded_objects");
        if(sym == _s && (_op & (kPropSize|kPropGet))){
            return PropSync(o.mLoadedObjects, _val, _prop, _i + 1, _op);
        }
    }
    {
        static Symbol _s("loaded_subdirs");
        if(sym == _s && (_op & (kPropSize|kPropGet))){
            return PropSync(o.mLoadedSubdirs, _val, _prop, _i + 1, _op);
        }
    }
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(FileMerger)
    SYNC_PROP(mergers, mMergers)
    SYNC_PROP(disable_all, sDisableAll)
    SYNC_PROP_SET(loading_load, mLoadingLoad, )
    SYNC_PROP_SET(async_load, mAsyncLoad, )
END_PROPSYNCS