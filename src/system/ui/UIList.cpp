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
#include "ui/UIListWidget.h"
#include "ui/UIListDir.h"
#include <cstddef>
#include "decomp.h"

static bool gGCNewLists = true;
static bool gLoading = false;
std::list<UIList*> UIList::sUIListSet;

INIT_REVS(UIList)

UIList::UIList() : UITransitionHandler(this), mListDir(0), mListState(this, this), mDataProvider(0), 
    mNumData(100), mUser(0), mParent(0), mExtendedLabelEntries(this, kObjListNoNull), 
    mExtendedMeshEntries(this, kObjListNoNull), mExtendedCustomEntries(this, kObjListNoNull), mAutoScrollPause(2.0f), unk_0x1D8(1), 
    unk_0x1DC(-1), mPaginate(0), mAutoScrollSendMessages(0), mAutoScrolling(0), unk_0x1E4(0), unk_0x1E5(0),
    unk_0x1E6(0), unk_0x1E7(0) {}

UIList::~UIList(){
    for(std::list<UIList*>::iterator it = sUIListSet.begin(); it != sUIListSet.end(); it++) delete *it;
    sUIListSet.clear();
    delete mDataProvider;
    mDataProvider = 0;
}

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
    int local_numdisplay;
    float local_speed;
    bool local_circular;
    bool local_scrollpastmin = false;
    bool local_scrollpastmax = true;
    int local_gridspan = 1;
    int local_mindisplay = 0;
    int local_maxdisplay = -1;
    if(mUIListRev < 0xF){
        int i, j, k, x;
        bool bb;
        bs >> i >> j;
        if(mUIListRev > 4){
            if(mUIListRev > 6) bs >> k;
            else bs >> bb;
        }
        if(mUIListRev > 6){
            bool b; bs >> b;
        }
        if(mUIListRev > 8){
            bool b; bs >> b;
        }
        if(mUIListRev > 10){
            int b; bs >> b;
        }
        bs >> x;
    }
    bs >> local_numdisplay;
    if(mUIListRev > 0x11) bs >> local_gridspan;
    bs >> local_circular;
    bs >> local_speed;
    if(mUIListRev > 0xC){
        bs >> local_scrollpastmin;
    }
    if(mUIListRev > 7){
        bs >> local_scrollpastmax;
    }
    if(mUIListRev > 2) bs >> mPaginate;
    if(mUIListRev > 3) bs >> unk_0x4; // from scroll select
    if(mUIListRev >= 10) bs >> local_mindisplay;
    if(mUIListRev >= 6) bs >> local_maxdisplay;
    gLoading = true;
    SetNumDisplay(local_numdisplay);
    SetGridSpan(local_gridspan);
    SetCircular(local_circular);
    SetSpeed(local_speed);
    mListState.SetScrollPastMinDisplay(local_scrollpastmin);
    mListState.SetScrollPastMaxDisplay(local_scrollpastmax);
    mListState.SetMinDisplay(local_mindisplay);
    mListState.SetMaxDisplay(local_maxdisplay);
    if(mUIListRev == 1){
        int x, y;
        bs >> x >> y;
    }
    if (mUIListRev >= 12) bs >> mNumData;
    if (mUIListRev >= 14) bs >> mAutoScrollPause;
    if (mUIListRev < 19) mAutoScrollSendMessages = true;
    else bs >> mAutoScrollSendMessages;
    if (mUIListRev >= 0x10) {
        bs >> mExtendedLabelEntries;
        bs >> mExtendedMeshEntries;
        bs >> mExtendedCustomEntries;
    }
    if (mUIListRev >= 17) UITransitionHandler::LoadHandlerData(bs);
    gLoading = false;
    Update();
}

int UIList::NumDisplay() const { return mListState.mNumDisplay; }
float UIList::Speed() const { return mListState.Speed(); }
int UIList::FirstShowing() const { return mListState.mFirstShowing; }
int UIList::Selected() const { return mListState.Selected(); }
int UIList::SelectedDisplay() const { return mListState.SelectedDisplay(); }
int UIList::SelectedData() const { return mListState.SelectedData(); }
int UIList::SelectedPos() const { return mListState.Selected(); }

Symbol UIList::SelectedSym(bool fail) const {
    Symbol sym = mListState.Provider()->DataSymbol(mListState.SelectedData());
    if(fail){
        if(sym == gNullStr) MILO_FAIL("DataSymbol() not implemented in UIList provider");
    }
    return sym;
}

bool UIList::IsScrolling() const { return mListState.IsScrolling(); }

UIListState& UIList::GetListState(){ return mListState; }

UIList* UIList::ChildList(){
    return mListDir->SubList(mListState.SelectedDisplay(), mWidgets);
}

UIList* UIList::ParentList(){ return mParent; }
UIListDir* UIList::GetUIListDir() const { return mListDir; }

void UIList::SetNumDisplay(int i){
    mListState.SetNumDisplay(i, gLoading == 0);
    Update();
}

void UIList::SetGridSpan(int i){
    mListState.SetGridSpan(i, gLoading == 0);
    Update();
}

void UIList::SetCircular(bool b){
    mListState.SetCircular(b, gLoading == 0);
    Update();
    if(!gLoading) Refresh(false);
}

void UIList::SetSpeed(float f){ mListState.SetSpeed(f); }

void UIList::SetSelected(int i, int j){
    mListDir->CompleteScroll(mListState, mWidgets);
    mListState.SetSelected(i, j, true);
    Refresh(false);
    mListDir->Poll();
    UIList* uilist = mListDir->SubList(mListState.SelectedDisplay(), mWidgets);
    if(uilist) Poll();
    HandleSelectionUpdated();
}

bool UIList::SetSelected(Symbol sym, bool b, int i){
    int index = mListState.Provider()->DataIndex(sym);
    if(index == -1){
        if(b){
            MILO_WARN("Couldn't find %s in UIList provider", sym);
        }
        return false;
    }
    else {
        SetSelected(index, i);
        return true;
    }
}

void UIList::SetSelectedSimulateScroll(int i){
    mListDir->CompleteScroll(mListState, mWidgets);
    mListState.SetSelectedSimulateScroll(i);
    Refresh(false);
    mListDir->Poll();
    UIList* uilist = mListDir->SubList(mListState.SelectedDisplay(), mWidgets);
    if(uilist) Poll();
}

bool UIList::SetSelectedSimulateScroll(Symbol sym, bool b){
    int index = mListState.Provider()->DataIndex(sym);
    if(index == -1){
        if(b){
            MILO_WARN("Couldn't find %s in UIList provider", sym);
        }
        return false;
    }
    else {
        SetSelectedSimulateScroll(index);
        return true;
    }
}

void UIList::SetProvider(UIListProvider* prov){
    if(prov == mListState.Provider()){
        Refresh(true);
    }
    else {
        mListState.SetProvider(prov, mResource->Dir());
        SetSelected(0, -1);
    }
    UIList* uilist = mListDir->SubList(mListState.SelectedDisplay(), mWidgets);
    if(uilist) Poll();
}

void UIList::Scroll(int i){
    unk_0x1E4 = true;
    mListState.Scroll(i, false);
}

void UIList::SetParent(UIList* uilist){ mParent = uilist; }

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
