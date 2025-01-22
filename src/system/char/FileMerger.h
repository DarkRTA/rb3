#pragma once
#include "obj/Object.h"
#include "utl/FilePath.h"
#include "utl/Loader.h"
#include "obj/Utl.h"
#include "obj/ObjPtr_p.h"
#include "utl/Std.h"

class OriginalPathable {
public:
    OriginalPathable(){}
    virtual ~OriginalPathable(){}
    virtual bool OriginalPath(Hmx::Object*, String&) = 0;
};

class FileMerger : public Hmx::Object, public Loader::Callback, public MergeFilter, public OriginalPathable {
public:
    class Merger {
    public:
        struct SortBySelected {
            bool operator()(const Merger& a, const Merger& b){ return stricmp(a.mSelected.c_str(), b.mSelected.c_str()) < 0; }
        };

        Merger(Hmx::Object* o) : mProxy(0), mPreClear(0), mSubdirs(4), mDir(o), mLoadedObjects(o), mLoadedSubdirs(o) {}
        Merger(const Merger& m) : mDir(m.mDir.Owner()), mLoadedObjects(m.mLoadedObjects.mOwner), mLoadedSubdirs(m.mLoadedSubdirs.mOwner){
            mName = m.mName;
            mSelected = m.mSelected;
            unk10 = m.unk10;
            mLoaded = m.mLoaded;
            mDir = m.mDir;
            mProxy = m.mProxy;
            mSubdirs = m.mSubdirs;
            mLoadedObjects = m.mLoadedObjects;
            mLoadedSubdirs = m.mLoadedSubdirs;
            mPreClear = m.mPreClear;
        }
        ~Merger(){}
        Merger& operator=(const Merger& m){
            mName = m.mName;
            mSelected = m.mSelected;
            unk10 = m.unk10;
            mLoaded = m.mLoaded;
            mDir = m.mDir;
            mProxy = m.mProxy;
            mSubdirs = m.mSubdirs;
            mLoadedObjects = m.mLoadedObjects;
            mLoadedSubdirs = m.mLoadedSubdirs;
            mPreClear = m.mPreClear;
        }

        void Clear();

        ObjectDir* MergerDir(){
            if(mDir) return mDir;
            else return mDir.Owner()->Dir();
        }

        // gross and convoluted way to basically check if this object is in mLoadedObjects
        bool IsObjectLoaded(Hmx::Object* obj){
            return !mLoadedObjects.find(obj) == false;
        }

        void SetSelected(const FilePath& fp, bool b){
            mSelected = fp;
            unk29 = b;
        }

        Symbol mName; // 0x0
        FilePath mSelected; // 0x4
        FilePath unk10; // 0x10
        FilePath mLoaded; // 0x1c
        bool mProxy; // 0x28
        bool unk29; // 0x29
        bool mPreClear; // 0x2a
        int mSubdirs; // 0x2c
        ObjPtr<ObjectDir> mDir; // 0x30
        ObjPtrList<Hmx::Object> mLoadedObjects; // 0x3c
        ObjPtrList<ObjectDir> mLoadedSubdirs; // 0x4c
    };

    FileMerger();
    virtual ~FileMerger();
    OBJ_CLASSNAME(FileMerger);
    OBJ_SET_TYPE(FileMerger);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void PreSave(BinStream&);
    virtual void PostSave(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual bool OriginalPath(Hmx::Object*, String&);
    virtual void FinishLoading(Loader*);
    virtual void FailedLoading(Loader*);
    virtual Action Filter(Hmx::Object*, Hmx::Object*, class ObjectDir*);
    virtual Action FilterSubdir(class ObjectDir* o1, class ObjectDir*);

    void Clear();
    bool StartLoad(bool);
    bool StartLoadInternal(bool, bool);
    void Select(Symbol, const FilePath&, bool);
    int FindMergerIndex(Symbol, bool);
    Merger* FindMerger(Symbol, bool);
    bool NeedsLoading(Merger&);
    void AppendLoader(Merger&);
    void LaunchNextLoader();
    Merger* InMerger(Hmx::Object*);
    void DeleteCurLoader();
    void ClearSelections();

    std::vector<Merger VECTOR_SIZE_LARGE>& Mergers(){ return mMergers; }

    static bool sDisableAll;
    static FileMerger* sFmDeleting;

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(FileMerger)
    static void Init(){
        REGISTER_OBJ_FACTORY(FileMerger)
    }

    ObjVector<Merger VECTOR_SIZE_LARGE> mMergers; // 0x30
    bool mAsyncLoad; // 0x40
    bool mLoadingLoad; // 0x41
    int unk44; // 0x44
    std::list<Merger*> mFilesPending; // 0x48
    int unk50; // 0x50
    int mHeap; // 0x54
    Loader::Callback* mCoordinator; // 0x58
};
