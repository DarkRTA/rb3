#include "char/FileMerger.h"
#include "char/CharClipGroup.h"
#include "char/CharPollGroup.h"
#include "char/FileMergerOrganizer.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/DirLoader.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Utl.h"
#include "os/Debug.h"
#include "rndobj/Group.h"
#include "rndobj/Mat.h"
#include "rndobj/Tex.h"
#include "rndobj/Text.h"
#include "utl/BinStream.h"
#include "utl/Loader.h"
#include "utl/MemMgr.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

#define kNoHeap -3
#define kSystemHeap -1
INIT_REVS(FileMerger)

bool FileMerger::sDisableAll;
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

FileMerger::FileMerger() : mMergers(this), mAsyncLoad(0), mLoadingLoad(0), mCurLoader(0), mFilter(0), mHeap(GetCurrentHeapNum()), mCoordinator(this) {
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
    return StartLoadInternal(b, false);
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
    if(mCurLoader){
        tmp = mFilesPending.front();
        mFilesPending.pop_front();
    }
    mFilesPending.sort(FileMergerSort);
    if(mCurLoader) mFilesPending.push_front(tmp);
    mAsyncLoad = b1;
    mLoadingLoad = b2;

    if(mFilesPending.empty() || mCurLoader || mCoordinator != this) return false;
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
    if(mCurLoader){
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
    if(mCurLoader){
        Merger* merger = mFilesPending.front();
        mFilesPending.clear();
        mFilesPending.push_front(merger);
        DeleteCurLoader();
    }
}

bool FileMerger::NeedsLoading(FileMerger::Merger& merger){
    for(std::list<Merger*>::iterator it = mFilesPending.begin(); it != mFilesPending.end(); ++it){
        if(*it == &merger){
            return merger.mSelected != merger.loading || merger.unk29;
        }
    }
    return merger.mLoaded != merger.mSelected || merger.unk29;
}

void FileMerger::AppendLoader(FileMerger::Merger& merger){
    merger.unk29 = false;
    for(std::list<Merger*>::iterator it = mFilesPending.begin(); it != mFilesPending.end(); ++it){
        if(*it == &merger){
            if(mCurLoader){
                MILO_WARN("check_sync");
            }
//       if (*(param_1 + 0x44) != 0) {
//         fn_804FFCA0(auStack_18,param_1 + 0x48);
//         uVar2 = stlpmtx_std::_List_iterator<>::_List_iterator(auStack_14,auStack_18);
//         iVar3 = Symbol::operator==(auStack_10,uVar2);
//         if (iVar3 != 0) {
//           DeleteCurLoader(param_1);
//           goto LAB_80500120;
//         }
//       }
//       uVar2 = stlpmtx_std::_List_iterator<>::_List_iterator(auStack_20,auStack_10);
//       fn_80500164(auStack_1c,param_1 + 0x48,uVar2);
//       goto LAB_80500120;
        }
    }
    merger.loading = merger.mSelected;
    if(merger.mPreClear) merger.Clear();
    mFilesPending.push_back(&merger);
}

void FileMerger::DeleteCurLoader(){
    if(mCurLoader){
        DirLoader* d = dynamic_cast<DirLoader*>(mCurLoader);
        if(d) d->unk99 = true;
        delete mCurLoader;
    }
}

void FileMerger::LaunchNextLoader(){
    MILO_ASSERT(!mFilesPending.empty(), 0x156);
    MILO_ASSERT(!mCurLoader, 0x157);
    bool b1 = false;
    if(Dir()->Loader() && !Dir()->Loader()->IsLoaded()){
        if(Dir()->Loader()->GetPos() != kLoadStayBack){
            if(Dir()->Loader()->GetPos() != kLoadFrontStayBack) goto next;
        }
        b1 = true;
    }

next:
    int pos = 0;
    if(b1) pos = 2;
    FilePath& fp = mFilesPending.front()->loading;
    MemTempHeap tmp(mHeap);
    if(fp.empty()){
        mCurLoader = new NullLoader(fp, (LoaderPos)pos, mCoordinator);
    }
    else {
        mCurLoader = new DirLoader(fp, (LoaderPos)pos, mCoordinator, 0, 0, 0);
    }
}

MergeFilter::Action FileMerger::MergeAction(Hmx::Object* o1, Hmx::Object* o2, ObjectDir* dir){
    if(!o2) return kReplace;
    else {
        const char* o1Name = o1->Name();
        ObjectDir* loaderDir = ((DirLoader*)mCurLoader)->GetDir();
        if(o1 == loaderDir){
            MsgSource* src1 = dynamic_cast<MsgSource*>(o2);
            if(src1){
                MsgSource* src2 = dynamic_cast<MsgSource*>(loaderDir);
                if(src2){
                    src1->MergeSinks(src2);
                }
            }
            return kKeep;
        }
        else {
            if(strnicmp("spot_", o1Name, 5) == 0 || strnicmp("bone_", o1Name, 5) == 0){
                return kMerge;
            }
            else {
                if(dynamic_cast<RndGroup*>(o2) || dynamic_cast<CharClipGroup*>(o2) || dynamic_cast<CharPollGroup*>(o2)) return kMerge;
                else if(dynamic_cast<RndMat*>(o2)) return kKeep;
                else {
                    RndTex* tex = dynamic_cast<RndTex*>(o2);
                    if(tex && !tex->File().empty()){
                        MILO_LOG("%s replacing texture %s with %s\n", PathName(this), PathName(o2), PathName(o1));
                        return kReplace;
                    }
                    else if(o2->Dir() != dir){
                        MILO_WARN("%s trying to replace subdir'd object %s with %s, bad because subdirs are shared",
                            PathName(this), PathName(o2), PathName(o1));
                        return kKeep;
                    }
                    else return kReplace;
                }
            }
        }
    }
}

void FileMerger::AddObject(Hmx::Object* obj){
    mFilesPending.front()->mLoadedObjects.push_back(obj);
}

void FileMerger::AddSubdir(ObjectDir* dir){
    mFilesPending.front()->mLoadedSubdirs.push_back(dir);
}

MergeFilter::Action FileMerger::Filter(Hmx::Object* o1, Hmx::Object* o2, ObjectDir* dir){
    Action a;
    if(mFilter) a = mFilter->Filter(o1, o2, dir);
    else a = MergeAction(o1, o2, dir);
    if(a == kReplace && !o2){
        AddObject(o1);
    }
    return a;
}

MergeFilter::Action FileMerger::FilterSubdir(ObjectDir* o1, ObjectDir* o2){
    Action a;
    Merger* merger = mFilesPending.front();
    if(mFilter) a = mFilter->FilterSubdir(o1, o2);
    else a = DefaultSubdirAction(o1, (Subdirs)merger->mSubdirs);
    if(a == kReplace && !o2->HasSubDir(o1)){
        AddSubdir(o1);
    }
    return a;
}

void FileMerger::FailedLoading(Loader* l){
    MILO_ASSERT(l == mCurLoader, 0x1D4);
    MILO_ASSERT(l->LoaderFile() == mFilesPending.front()->loading, 0x1D5);
    static Message msg("on_load_failed", 0);
    msg[0] = mFilesPending.front()->mName;
    HandleType(msg);
    PostMerge(mFilesPending.front(), false);
    DirLoader* d = dynamic_cast<DirLoader*>(l);
    if(d && !d->IsLoaded()){
        d->SetDeleteSelf();
    }
}

FileMerger::Merger* FileMerger::NotifyFileLoaded(Loader* l, ObjectDir* dir){
    MILO_ASSERT_FMT(l->LoaderFile() == mFilesPending.front()->loading,
         "%s != %s", l->LoaderFile(), mFilesPending.front()->loading);
    MILO_ASSERT(l == mCurLoader, 0x1ED);
    Merger* m = mFilesPending.front();
    m->Clear();
    if(!sDisableAll){
        static Message msg("on_pre_merge", 0, 0, 0);
        msg[0] = m->mName;
        msg[1] = dir;
        msg[2] = m->MergerDir();
        HandleType(msg);
        m->mLoaded = m->loading;
        m->loading.SetRoot("");
    }
    return m;
}

void FileMerger::FinishLoading(Loader* l){
    DirLoader* d = dynamic_cast<DirLoader*>(l);
    ObjectDir* dDir = d ? d->GetDir() : nullptr;
    Merger* m = NotifyFileLoaded(l, dDir);
    if(d){
        if(!sDisableAll){
            if(m->IsProxy()){
                ObjectDir* find = Dir()->Find<ObjectDir>(d->GetDir()->Name(), false);
                if(find){
                    ReserveToFit(d->GetDir(), find, 0);
                    MergeDirs(d->GetDir(), find, *this);
                    find->SyncObjects();
                }
                else {
                    ObjectDir* dirLoaderDir = d->GetDir();
                    ReserveToFit(nullptr, Dir(), 2);
                    dirLoaderDir->SetName(dirLoaderDir->Name(), Dir());
                    m->mLoadedObjects.push_back(dirLoaderDir);
                }
            }
            else {
                ObjectDir* mergerDir = m->MergerDir();
                ReserveToFit(d->GetDir(), mergerDir, 0);
                MergeDirs(d->GetDir(), mergerDir, *this);
            }
        }
        if(!m->IsProxy()){
            delete d->GetDir();
        }
        else delete d;        
    }
    PostMerge(m, true);
}

void FileMerger::PostMerge(FileMerger::Merger* merger, bool b){
    mCurLoader = nullptr;
    mFilesPending.pop_front();
    mFilter = nullptr;
    if(b){
        static Message msg("on_post_merge", 0, 0, 0);
        msg[0] = merger->mName;
        msg[1] = merger->MergerDir();
        msg[2] = mFilesPending.empty();
        HandleType(msg);
        Hmx::Object* miloObj = ObjectDir::Main()->FindObject("milo", false);
        if(miloObj){
            miloObj->Handle(Message("update_objects", 1), true);
        }
    }
    if(!b && mCoordinator != this) return;
    if(mFilesPending.empty()){
        MILO_ASSERT(!mCurLoader, 0x24F);
    }
    else if(!mCurLoader) LaunchNextLoader();
}

bool FileMerger::OriginalPath(Hmx::Object* o, String& s){
    Merger* m = InMerger(o);
    if(m){
        s = m->mLoaded;
        return true;
    }
    else return false;
}

void FileMergerObjPtrSave(BinStream& bs, const ObjPtr<ObjectDir>& ptr){
    bs << ptr;
}

BinStream& operator>>(BinStream& bs, FileMerger::Merger& m){
    bs >> m.mName;
    bs >> m.mSelected;
    bs >> m.mLoaded;
    bs >> m.mDir;
    if(FileMerger::gRev != 0){
        if(FileMerger::gRev != 4) bs >> m.mProxy;
        bs >> m.mSubdirs;
        if(FileMerger::gRev > 2) bs >> m.mPreClear;
    }
    return bs;
}

SAVE_OBJ(FileMerger, 0x288)

void FileMerger::PreSave(BinStream&){ Clear(); }
void FileMerger::PostSave(BinStream&){
    StartLoadInternal(false, false);
}

void FileMerger::PreLoad(BinStream& bs){
    LOAD_REVS(bs)
    ASSERT_REVS(5, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    if(gRev < 2){
        String s; bs >> s;
    }
    bs >> mMergers;
    StartLoadInternal(true, true);
}

void FileMerger::PostLoad(BinStream&){}

BEGIN_LOADS(FileMerger)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

BEGIN_COPYS(FileMerger)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(FileMerger)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mMergers)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(FileMerger)
    HANDLE_EXPR(loaded, FindMerger(_msg->Sym(2), true)->mLoaded)
    HANDLE(select, OnSelect)
    HANDLE(start_load, OnStartLoad)
    HANDLE_ACTION(clear, Clear())
    HANDLE_ACTION(clear_selections, ClearSelections())
    HANDLE_EXPR(merger_index, FindMergerIndex(_msg->Sym(2), _msg->Int(3)))
    HANDLE_EXPR(is_loading, 0)
    HANDLE_ACTION(clear_filter, mFilter = nullptr)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x2DB)
END_HANDLERS

DataNode FileMerger::OnSelect(const DataArray* a){
    FilePath fp(a->Str(3));
    Select(a->Sym(2), fp, false);
    return 0;
}

DataNode FileMerger::OnStartLoad(const DataArray* a){
    StartLoadInternal(a->Size() == 3 ? a->Int(2) : true, false);
    return 0;
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