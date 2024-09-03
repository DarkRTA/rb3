#include "bandobj/OvershellDir.h"
#include "obj/ObjVersion.h"
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

BEGIN_HANDLERS(OvershellDir)
    HANDLE_SUPERCLASS(PanelDir)
    HANDLE_ACTION(set_default_option, mDefaultOption = _msg->Sym(2))
    HANDLE_ACTION(set_default_option_index, mDefaultOptionIndex = _msg->Int(2))
    HANDLE_ACTION(cache_lists, CacheLists())
    HANDLE_ACTION(conceal_all_lists, ConcealAllLists(_msg->Int(2)))
    HANDLE_CHECK(0x64)
END_HANDLERS