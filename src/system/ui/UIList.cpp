#include "UIList.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "os/Debug.h"
#include "ui/UI.h"
#include "ui/UIComponent.h"
#include "ui/UIListArrow.h"
#include "ui/UITransitionHandler.h"
#include "utl/Loader.h"
#include "ui/UIListCustom.h"
#include <cstddef>

#include "decomp.h"

static bool gGCNewLists = true;
static bool gLoading = false;

INIT_REVS(UIList)

UIList::UIList() : UITransitionHandler(this), unk_0x140(0), mListState(this, this), unk_0x194(0), 
    mNumData(100), unk_0x19C(0), unk_0x1A0(0), mExtendedLabelEntries(this, kObjListNoNull), 
    mExtendedMeshEntries(this, kObjListNoNull), mExtendedCustomEntries(this, kObjListNoNull), mAutoScrollPause(2.0f), unk_0x1D8(1), 
    unk_0x1DC(-1), mPaginate(0), mAutoScrollSendMessages(0), unk_0x1E3(0), unk_0x1E4(0), unk_0x1E5(0),
    unk_0x1E6(0), unk_0x1E7(0) {}

UIList::~UIList() {}

void UIList::Init() {
    TheUI->InitResources("UIList");
    REGISTER_OBJ_FACTORY(UIList)
    REGISTER_OBJ_FACTORY(UIListArrow)
    REGISTER_OBJ_FACTORY(UIListCustom)
    // REGISTER_OBJ_FACTORY(UIListDir)
    // REGISTER_OBJ_FACTORY(UIListHighlight)
    // REGISTER_OBJ_FACTORY(UIListLabel)
    // REGISTER_OBJ_FACTORY(UIListMesh)
    REGISTER_OBJ_FACTORY(UIListSlot)
    // REGISTER_OBJ_FACTORY(UIListSubList)
    REGISTER_OBJ_FACTORY(UIListWidget)
}

BEGIN_COPYS(UIList)
    CREATE_COPY_AS(UIList, l)
    MILO_ASSERT(l, 103);
    COPY_SUPERCLASS(UIList)
END_COPYS

SAVE_OBJ(UIList, 138)

BEGIN_LOADS(UIList)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void UIList::PreLoad(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(19, 0)
    PreLoadWithRev(bs, gRev);
}

void UIList::PreLoadWithRev(BinStream& bs, int rev) {
    mUIListRev = rev;
    if (mUIListRev > 19) {
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), mUIListRev, (unsigned short)19);
    }
    UIComponent::PreLoad(bs);
}

void UIList::PostLoad(BinStream& bs) {
    UIComponent::PostLoad(bs);
    unk_0x1E7 = gGCNewLists;


    if (mUIListRev >= 12) bs >> mNumData;
    if (mUIListRev >= 14) bs >> mAutoScrollPause;
    if (mUIListRev < 19) mAutoScrollSendMessages = true;
    else bs >> mAutoScrollSendMessages;
    if (mUIListRev >= 10) {
        bs >> mExtendedLabelEntries;
        bs >> mExtendedMeshEntries;
        bs >> mExtendedCustomEntries;
    }
    if (mUIListRev >= 17) UITransitionHandler::LoadHandlerData(bs);
    gLoading = false;
    Update();
}

void UIList::Update() {
    if (!gLoading) {
        unk_0x1E6 = false;
        UIComponent::Update();
        MILO_ASSERT(mResource && mResource->Dir(), 566);
        if (unk_0x1E7) {

        }

        if (TheLoadMgr.EditMode()) Refresh(false);
    }
}
