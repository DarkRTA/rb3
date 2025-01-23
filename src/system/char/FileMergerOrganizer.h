#pragma once
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "utl/Loader.h"
#include "char/FileMerger.h"
#include "utl/MemMgr.h"

struct CatData {
    CatData() : priority(0), unk4(0) {}
    CatData(const CatData& c) : priority(c.priority), unk4(c.unk4) {}
    int priority; // 0x0
    int unk4; // 0x4
};

class FileMergerOrganizerLoader : public Loader {
public:
    FileMergerOrganizerLoader() : Loader(FilePath(""), kLoadFront) {}
    virtual ~FileMergerOrganizerLoader(){}
    virtual bool IsLoaded() const { return false; }
    virtual const char* StateName() const { return "FileMergerOrganizerLoader"; }
    virtual void PollLoading();
};

class FileMergerOrganizer : public Hmx::Object, Loader::Callback {
public:
    enum OrganizedState {
        kFinishLoad = 1,
        kFailedLoad = 2,
        kPendingLoad = 3
    };

    class OrganizedFileMerger {
    public:
        FileMerger* merger; // 0x0
        OrganizedState state; // 0x4
    };

    FileMergerOrganizer();
    virtual ~FileMergerOrganizer(){}
    OBJ_CLASSNAME(FileMergerOrganizer);
    OBJ_SET_TYPE(FileMergerOrganizer);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void FinishLoading(Loader*);
    virtual void FailedLoading(Loader*);

    void AddFileMerger(FileMerger*);
    void Dispatch(OrganizedFileMerger*);
    FileMerger::Merger* FrontInactiveMerger(OrganizedFileMerger*);
    void RemoveFileMerger(OrganizedFileMerger*);
    void CheckDone();
    void StartLoad();

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(FileMergerOrganizer)
    }
    NEW_OBJ(FileMergerOrganizer)
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    std::list<OrganizedFileMerger> unk20; // 0x20
    OrganizedFileMerger* mActiveOrg; // 0x28
    FileMergerOrganizerLoader* mStartOrg; // 0x2c
};

bool FileMergerSort(const FileMerger::Merger*, const FileMerger::Merger*);

extern FileMergerOrganizer* TheFileMergerOrganizer;