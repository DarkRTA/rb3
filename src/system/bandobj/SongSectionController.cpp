#include "bandobj/SongSectionController.h"
#include "obj/Msg.h"
#include "obj/MsgSource.h"
#include "utl/Symbols.h"

INIT_REVS(SongSectionController)

SongSectionController::SongSectionController() : mActivePool(this, 0), mPendingPool(this, 0), mSectionMappings(this), mMappingsOwner(this, 0),
    mContentPoolMappings(this), mCreateContentForPool(this, 0) {
    mOverlay = RndOverlay::Find("songsection_overlay", false);
}

SongSectionController::~SongSectionController(){

}

DECOMP_FORCEACTIVE(SongSectionController, "ObjPtr_p.h", "c.Owner()", "")

SAVE_OBJ(SongSectionController, 0x45)

BinStream& operator>>(BinStream& bs, SongSectionController::PracticeSectionMapping& m){
    bs >> m.mPoolCategory;
    int count;
    bs >> count;
    m.mValidPracticeSections.clear();
    for(int i = 0; i < count; i++){
        String str;
        bs >> str;
        m.mValidPracticeSections.push_back(str);
    }
    if(SongSectionController::gRev > 2){
        bs >> count;
        m.mInvalidPracticeSections.clear();
        for(int i = 0; i < count; i++){
            String str;
            bs >> str;
            m.mInvalidPracticeSections.push_back(str);
        }
    }
    return bs;
}

BinStream& operator>>(BinStream& bs, SongSectionController::ContentPoolMapping& m){
    bs >> m.mPoolCategory;
    SongSectionController::PoolTriggerOrder order;
    bs >> (int&)order;
    m.mTriggerOrder = order;
    bs >> m.mContentPools;
    return bs;
}

BEGIN_LOADS(SongSectionController)
    LOAD_REVS(bs)
    ASSERT_REVS(3, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndPollable)
    UnregisterEvents();
    bs >> mSectionMappings;
    bs >> mMappingsOwner;
    bs >> mDebugPoolCategory;
    bs >> mDebugSectionName;
    bs >> mContentPoolMappings;
    if(gRev > 1) bs >> mWaitForEvent;
    RegisterEvents();
END_LOADS

BEGIN_COPYS(SongSectionController)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndPollable)
    UnregisterEvents();
    CREATE_COPY(SongSectionController)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mMidiSection)
        COPY_MEMBER(mCurPoolCategory)
        COPY_MEMBER(mSectionMappings)
        COPY_MEMBER(mMappingsOwner)
        COPY_MEMBER(mDebugSectionName)
        COPY_MEMBER(mDebugPoolCategory)
        COPY_MEMBER(mContentPoolMappings)
        COPY_MEMBER(mWaitForEvent)
    END_COPYING_MEMBERS
    RegisterEvents();
END_COPYS

void SongSectionController::Enter(){
    RndPollable::Enter();
    ResetAll();
    ForceCatchAll();
}

void SongSectionController::ForceCatchAll(){
    mCurPoolCategory = "CATCH_ALL";
    ActivatePool(mCurPoolCategory, true);
}

void SongSectionController::ResetAll(){
    mActivePool = 0;
    mPendingPool = 0;
    mCurPoolCategory = gNullStr;
    for(ObjList<ContentPoolMapping>::iterator it = mContentPoolMappings.begin(); it != mContentPoolMappings.end(); ++it){
        it->mLastActivatedIdx = -1;
        for(ObjPtrList<EventTrigger, ObjectDir>::iterator lit = it->mContentPools.begin(); lit != it->mContentPools.end(); ++lit){
            (*lit)->BasicReset();
            (*lit)->mEnabled = false;
            for(ObjPtrList<RndDrawable, class ObjectDir>::iterator dit = (*lit)->mShows.begin(); dit != (*lit)->mShows.end(); ++dit){
                (*dit)->SetShowing(false);
            }
        }
    }
    mDebugSectionName = gNullStr;
    mDebugPoolCategory = gNullStr;
    mLastDebugPoolActivated = gNullStr;
}

void SongSectionController::Exit(){ RndPollable::Exit(); }

void SongSectionController::RegisterEvents(){
    MsgSource* src = dynamic_cast<MsgSource*>(Dir());
    if(!src || mWaitForEvent.Null()) return;
    src->AddSink(this, mWaitForEvent, wait_for_event_received);
}

void SongSectionController::UnregisterEvents(){
    MsgSource* src = dynamic_cast<MsgSource*>(Dir());
    if(src) src->RemoveSink(this, mWaitForEvent);
}

void SongSectionController::Poll(){
    if(UpdatePoolCategory()){
        ActivatePool(mCurPoolCategory, false);
    }
    UpdateOverlay();
}

#pragma push
#pragma pool_data off
void SongSectionController::UpdateOverlay(){
    if(mOverlay){
        if(!TheLoadMgr.EditMode()){
            static DataNode& disable = DataVariable("cheat.song_section_ctrl");
            mOverlay->SetOverlay(disable.Int());
        }
        if(mOverlay->Showing()){
            String cursec(mMidiSection.Null() ? "<none>" : mMidiSection.Str());
            *mOverlay << "[current practice section]: " << cursec.c_str() << "\n";

            String acpool;
            Symbol pc7;
            if(!mLastDebugPoolActivated.Null()){
                acpool = mLastDebugPoolActivated.Str();
                pc7 = mLastDebugPoolActivated;
            }
            else {
                acpool = mCurPoolCategory.Null() ? "<none>" : mCurPoolCategory.Str();
                pc7 = mCurPoolCategory;
            }
            *mOverlay << "[active pool]: " << acpool.c_str() << "\n";

            String str3c;
            if(!mActivePool){
                if(pc7.Null() || mPendingPool){
                    str3c = "<none>";
                }
                else str3c = MakeString("*** No content pool attached to category '%s'! ***", pc7.Str());
            }
            else {
                ContentPoolMapping* cpm = GetContentPoolMapping(pc7);
                if(cpm){
                    str3c = MakeString("%s   (#%d out of %d possible content pools)", mActivePool->Name(), cpm->mLastActivatedIdx + 1, cpm->mContentPools.size());
                }
                else str3c = MakeString("%s   [** there is no content pool for desired pool %s! ***]", mActivePool->Name(), pc7.Str());
            }
            (*mOverlay << "[pool asset]: ").Print(str3c.c_str());
            if(mPendingPool){
                *mOverlay << "  [up next]: " << mPendingPool->Name();
            }
            *mOverlay << "\n";

            String str48;
            if(!mActivePool) str48 = "<none>";
            else {
                static Message debugStr("debug_str");
                str48 = mActivePool->HandleType(debugStr).Str();
            }
            *mOverlay << "[current pool content]: " << str48.c_str() << "\n";
        }
    }
}
#pragma pop

void SongSectionController::DebugActivate(){
    if(mOverlay && !mOverlay->Showing()){
        mOverlay->SetOverlay(true);
    }
    if(mDebugPoolCategory != mLastDebugPoolActivated){
        ActivatePool(mDebugPoolCategory, true);
        mLastDebugPoolActivated = mDebugPoolCategory;
    }
    else if(mActivePool) mActivePool->Trigger();
}

BEGIN_CUSTOM_PROPSYNC(SongSectionController::PracticeSectionMapping)
    SYNC_PROP(pool_category, o.mPoolCategory)
    SYNC_PROP(valid_practice_sections, o.mValidPracticeSections)
    SYNC_PROP(invalid_practice_sections, o.mInvalidPracticeSections)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(SongSectionController::ContentPoolMapping)
    SYNC_PROP(pool_category, o.mPoolCategory)
    SYNC_PROP(trigger_order, (int&)o.mTriggerOrder)
    SYNC_PROP(trigger_pools, o.mContentPools)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(SongSectionController)
    SYNC_SUPERCLASS(RndPollable)
    SYNC_PROP(midi_section, mMidiSection)
    SYNC_PROP(pratice_section_debug, mDebugSectionName)
    SYNC_PROP_SET(pool_debug, FindPoolCategoryForPracSession(mDebugSectionName), )
    SYNC_PROP(pool_to_activate, mDebugPoolCategory)
    SYNC_PROP(section_mappings, mSectionMappings)
    SYNC_PROP(mappings_owner, mMappingsOwner)
    SYNC_PROP(trigger_mappings, mContentPoolMappings)
    SYNC_PROP(pool_to_createfor, mCreatePoolCategory)
    SYNC_PROP(triggerpool_to_createfor, mCreateContentForPool)
    {
        static Symbol _s("wait_for_event");
        if(sym == _s){
            if(!(_op & (kPropSize|kPropGet))) UnregisterEvents();
            bool synced = PropSync(mWaitForEvent, _val, _prop, _i + 1, _op);
            if(!synced) return false;
            else {
                if(!(_op & (kPropSize|kPropGet))) RegisterEvents();
                return true;
            }
        }
    }
END_PROPSYNCS

void SongSectionController::OnToggleOverlay(){
    if(mOverlay){
        mOverlay->SetOverlay(mOverlay->Showing() == 0);
    }
}

DataNode SongSectionController::OnFindPools(const DataArray* da){
    DataArrayPtr ptr;
    ptr->Insert(0, DataNode(Symbol()));
    for(ObjDirItr<EventTrigger> it(Dir(), true); it != 0; ++it){
        if(it->TypeDef() && it->TypeDef()->Sym(0) == Symbol("trigger_pool")){
            ptr->Insert(ptr->Size(), DataNode(it));
        }
    }
    return DataNode(ptr);
}

DataNode SongSectionController::OnAddTriggerPool(const DataArray* da){
    EventTrigger* trig = da->Obj<EventTrigger>(2);
    Symbol sym = da->Sym(3);
    ContentPoolMapping* cpm = GetContentPoolMapping(sym);
    if(!cpm){
        ContentPoolMapping* newcpm = new ContentPoolMapping(this);
        newcpm->mPoolCategory = sym;
        newcpm->mContentPools.push_back(trig);
        mContentPoolMappings.push_back(*newcpm);
    }
    else cpm->mContentPools.push_back(trig);
    return DataNode(0);
}

DataNode SongSectionController::OnWaitForEventReceived(const DataArray* da){
    if(mPendingPool){
        if(mActivePool){
            mActivePool->SetEnabled(false);
            mActivePool->BasicReset();
            mActivePool = 0;
        }
        mPendingPool->SetEnabled(true);
        mPendingPool->Trigger();
        mActivePool = mPendingPool;
        mPendingPool = 0;
    }
    return DataNode(0);
}

BEGIN_HANDLERS(SongSectionController)
    HANDLE_ACTION(trigger_debug_pool, DebugActivate())
    HANDLE_ACTION(reset_all, ResetAll(); ForceCatchAll(); )
    HANDLE(find_pools, OnFindPools)
    HANDLE_ACTION(toggle_overlay, OnToggleOverlay())
    HANDLE(add_trigger_pool, OnAddTriggerPool)
    HANDLE(wait_for_event_received, OnWaitForEventReceived)
    if(strlen(sym.Str()) < 4 || strncmp(sym.Str(), "prc_", 4) == 0){
        static Message msg("section", DataNode(""));
        msg[0] = DataNode(sym.Str());
        Handle(msg, true);
        return DataNode(0);
    }
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x2B7)
END_HANDLERS
