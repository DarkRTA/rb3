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
#include <cstddef>

#include "decomp.h"

static bool gGCNewLists = true;
static bool gLoading = false;

INIT_REVS(UIList)

UIList::UIList() : UITransitionHandler(this), unk_0x140(0), unk_0x14C(this, this), unk_0x194(0), 
    unk_0x198(100), unk_0x19C(0), unk_0x1A0(0), unk_0x1A4(this, kObjListNoNull), 
    unk_0x1B4(this, kObjListNoNull), unk_0x1C4(this, kObjListNoNull), unk_0x1D4(0), unk_0x1D8(1), 
    unk_0x1DC(-1), unk_0x1E1(0), unk_0x1E2(0), unk_0x1E3(0), unk_0x1E4(0), unk_0x1E5(0),
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
    mRev = rev;
    if (mRev > 19) {
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), mRev, (unsigned short)19);
    }
    UIComponent::PreLoad(bs);
}

void UIList::PostLoad(BinStream& bs) {
    UIComponent::PostLoad(bs);
    unk_0x1E7 = gGCNewLists;


    if (mRev >= 12) bs >> unk_0x198;
    if (mRev >= 14) bs >> unk_0x1D4;
    if (mRev < 19) unk_0x1E2 = true;
    else bs >> unk_0x1E2;
    if (mRev >= 10) {
        bs >> unk_0x1A4;
        bs >> unk_0x1B4;
        bs >> unk_0x1C4;
    }
    if (mRev >= 17) UITransitionHandler::LoadHandlerData(bs);
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
