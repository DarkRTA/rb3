#include "bandobj/OvershellDir.h"
#include "obj/ObjVersion.h"
#include "bandobj/BandList.h"
#include "utl/Symbols.h"

INIT_REVS(OvershellDir)

OvershellDir::OvershellDir() : mSlotView("joined_default"), mInTrackMode(0), mControllerType("guitar"), mOnlineEnabled(0),
    mIsLocal(1), mPadNum(1), mPlatform("xbox"), mDefaultOption(gNullStr), mDefaultOptionIndex(0) {

}

SAVE_OBJ(OvershellDir, 0x1E)

void OvershellDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    PanelDir::PreLoad(bs);
}

void OvershellDir::PostLoad(BinStream& bs){
    PanelDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
}

BEGIN_COPYS(OvershellDir)
    COPY_SUPERCLASS(PanelDir)
END_COPYS

void OvershellDir::CacheLists(){
    mBandLists.clear();
    for(ObjDirItr<BandList> it(this, false); it != 0; ++it){
        mBandLists.push_back(it);
    }
}

void OvershellDir::ConcealAllLists(bool now){
    for(int i = 0; i < mBandLists.size(); i++){
        if(now) mBandLists[i]->ConcealNow();
        else mBandLists[i]->Conceal();
    }
}

void OvershellDir::ViewChanged(){
    static Message msgShowView("show_view", DataNode(mSlotView), DataNode(mInTrackMode), DataNode(mDefaultOption), DataNode(mDefaultOptionIndex));
    msgShowView[0] = DataNode(mSlotView);
    msgShowView[1] = DataNode(mInTrackMode);
    msgShowView[2] = DataNode(mDefaultOption);
    msgShowView[3] = DataNode(mDefaultOptionIndex);
    HandleType(msgShowView);
    mDefaultOption = gNullStr;
    mDefaultOptionIndex = -1;
}

BEGIN_HANDLERS(OvershellDir)
    HANDLE_SUPERCLASS(PanelDir)
    HANDLE_ACTION(set_default_option, SetDefaultOption(_msg->Sym(2)))
    HANDLE_ACTION(set_default_option_index, SetDefaultOptionIndex(_msg->Int(2)))
    HANDLE_ACTION(cache_lists, CacheLists())
    HANDLE_ACTION(conceal_all_lists, ConcealAllLists(_msg->Int(2)))
    HANDLE_CHECK(0x64)
END_HANDLERS

BEGIN_PROPSYNCS(OvershellDir)
    SYNC_PROP(controller_type, mControllerType)
    SYNC_PROP(online_enabled, mOnlineEnabled)
    SYNC_PROP(is_local, mIsLocal)
    SYNC_PROP(pad_num, mPadNum)
    SYNC_PROP(platform, mPlatform)
    SYNC_PROP_MODIFY(slot_view, mSlotView, ViewChanged())
    SYNC_PROP_MODIFY(in_track_mode, mInTrackMode, ViewChanged())
    SYNC_SUPERCLASS(PanelDir)
END_PROPSYNCS