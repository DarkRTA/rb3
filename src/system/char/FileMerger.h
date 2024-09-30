#pragma once
#include "obj/Object.h"
#include "utl/Loader.h"
#include "obj/Utl.h"
#include "obj/ObjPtr_p.h"

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

        Merger(Hmx::Object* o) : mProxy(0), mPreClear(0), mSubdirs(4), mDir(o, 0), mLoadedObjects(o, kObjListNoNull), mLoadedSubdirs(o, kObjListNoNull) {}
        Merger(const Merger& m) : mDir(m.mDir.Owner(), 0), mLoadedObjects(m.mLoadedObjects.mOwner, kObjListNoNull), mLoadedSubdirs(m.mLoadedSubdirs.mOwner, kObjListNoNull){
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

        Symbol mName; // 0x0
        FilePath mSelected; // 0x4
        FilePath unk10; // 0x10
        FilePath mLoaded; // 0x1c
        bool mProxy; // 0x28
        bool unk29; // 0x29
        bool mPreClear; // 0x2a
        int mSubdirs; // 0x2c
        ObjPtr<ObjectDir,ObjectDir> mDir; // 0x30
        ObjPtrList<Hmx::Object,ObjectDir> mLoadedObjects; // 0x3c
        ObjPtrList<ObjectDir,ObjectDir> mLoadedSubdirs; // 0x4c
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
    void Select(Symbol, const FilePath&, bool);
    int FindMergerIndex(Symbol, bool);
    Merger* FindMerger(Symbol, bool);
    std::vector<Merger, unsigned int>& Mergers(){ return mMergers; }

    static bool sDisableAll;

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjVector<Merger, unsigned int> mMergers; // 0x30
    bool mAsyncLoad; // 0x40
    bool mLoadingLoad; // 0x41
    int unk44;
    std::list<int> unk48;
    int unk50;
    int mHeap; // 0x54
    Loader::Callback* unk58; // 0x58
};