#pragma once
#include "rndobj/Poll.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/Overlay.h"

class SongSectionController : public RndPollable {
public:
    class PracticeSectionMapping {
    public:
        PracticeSectionMapping(Hmx::Object*);
        Symbol mPoolCategory; // 0x0
        std::list<String> mValidPracticeSections; // 0x4
        std::list<String> mInvalidPracticeSections; // 0xc
    };

    enum PoolTriggerOrder {
        kPoolTriggerSequence,
        kPoolTriggerRandom,
        kPoolTriggerLoop
    };

    class ContentPoolMapping {
    public:
        ContentPoolMapping(Hmx::Object* o) : mContentPools(o, kObjListNoNull), mTriggerOrder(kPoolTriggerSequence), mLastActivatedIdx(-1) {}
        Symbol mPoolCategory; // 0x0
        ObjPtrList<EventTrigger, ObjectDir> mContentPools; // 0x4
        PoolTriggerOrder mTriggerOrder; // 0x14
        int mLastActivatedIdx; // 0x18
    };

    SongSectionController();
    OBJ_CLASSNAME(SongSectionController);
    OBJ_SET_TYPE(SongSectionController);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Enter();
    virtual void Exit();
    virtual ~SongSectionController();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    void RegisterEvents();
    void UnregisterEvents();
    void ResetAll();
    void ForceCatchAll();
    void ActivatePool(Symbol, bool);
    bool UpdatePoolCategory();
    void UpdateOverlay();
    ContentPoolMapping* GetContentPoolMapping(Symbol);
    Symbol FindPoolCategoryForPracSession(Symbol);
    void OnToggleOverlay();
    void DebugActivate();

    DataNode OnFindPools(const DataArray*);
    DataNode OnAddTriggerPool(const DataArray*);
    DataNode OnWaitForEventReceived(const DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    Symbol mMidiSection; // 0x8
    Symbol mCurPoolCategory; // 0xc
    ObjPtr<EventTrigger, ObjectDir> mActivePool; // 0x10
    ObjPtr<EventTrigger, ObjectDir> mPendingPool; // 0x1c
    ObjList<PracticeSectionMapping> mSectionMappings; // 0x28
    ObjPtr<SongSectionController, ObjectDir> mMappingsOwner; // 0x34
    ObjList<ContentPoolMapping> mContentPoolMappings; // 0x40
    Symbol mDebugSectionName; // 0x4c
    Symbol mDebugPoolCategory; // 0x50
    Symbol mLastDebugPoolActivated; // 0x54
    RndOverlay* mOverlay; // 0x58
    Symbol mWaitForEvent; // 0x5c
    Symbol mCreatePoolCategory; // 0x60
    ObjPtr<EventTrigger, ObjectDir> mCreateContentForPool; // 0x64
};