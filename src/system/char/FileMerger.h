#pragma once
#include "obj/Object.h"
#include "utl/Loader.h"
#include "obj/Utl.h"

class OriginalPathable {
public:
    OriginalPathable(){}
    virtual ~OriginalPathable(){}
    virtual bool OriginalPath(Hmx::Object*, String&) = 0;
};

class FileMerger : public Hmx::Object, public Loader::Callback, public MergeFilter, public OriginalPathable {
public:
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

    bool StartLoad(bool);
    void Select(Symbol, const FilePath&, bool);
    int FindMergerIndex(Symbol, bool);
};