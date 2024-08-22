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
#include "ui/UIListHighlight.h"
#include "ui/UIListLabel.h"
#include "ui/UIListMesh.h"
#include "ui/UIListSlot.h"
#include "ui/UIListSubList.h"
#include "utl/STLHelpers.h"
#include "ui/UIMessages.h"
#include "ui/Utl.h"
#include <cstddef>
#include "decomp.h"
#include "utl/Symbols.h"

static bool gGCNewLists = true;
static bool gLoading = false;
std::list<UIList*> sUIListSet;

INIT_REVS(UIList)

UIList::UIList() : UITransitionHandler(this), mListDir(0), mListState(this, this), mDataProvider(0), 
    mNumData(100), mUser(0), mParent(0), mExtendedLabelEntries(this, kObjListNoNull), 
    mExtendedMeshEntries(this, kObjListNoNull), mExtendedCustomEntries(this, kObjListNoNull), mAutoScrollPause(2.0f), unk_0x1D8(1), 
    unk_0x1DC(-1), mPaginate(0), mAutoScrollSendMessages(0), mAutoScrolling(0), unk_0x1E4(0), mDrawManuallyControlledWidgets(0),
    unk_0x1E6(0), mNeedsGarbageCollection(0) {}

UIList::~UIList(){
    for(std::list<UIList*>::iterator it = sUIListSet.begin(); it != sUIListSet.end(); it++){
        if(*it == this){
            it = sUIListSet.erase(it);
        }
    }
    DeleteRange(mWidgets.begin(), mWidgets.end());
    mWidgets.clear();
    delete mDataProvider;
    mDataProvider = 0;
}

void UIList::Init() {
    TheUI->InitResources("UIList");
    UIList::Register();
    UIListArrow::Init();
    UIListCustom::Init();
    UIListDir::Init();
    UIListHighlight::Init();
    UIListLabel::Init();
    UIListMesh::Init();
    UIListSlot::Init();
    UIListSubList::Init();
    UIListWidget::Init();
}

BEGIN_COPYS(UIList)
    CREATE_COPY_AS(UIList, l)
    MILO_ASSERT(l, 103);
    COPY_SUPERCLASS(UIComponent)
    SetCircular(l->Circular());
    SetNumDisplay(l->NumDisplay());
    SetGridSpan(l->GridSpan());
    SetSpeed(l->Speed());
    COPY_MEMBER_FROM(l, mPaginate)
    COPY_MEMBER_FROM(l, unk_0x4) // from ScrollSelect
    mListState.SetMinDisplay(l->mListState.MinDisplay());
    mListState.SetScrollPastMinDisplay(l->mListState.ScrollPastMinDisplay());
    mListState.SetMaxDisplay(l->mListState.MaxDisplay());
    mListState.SetScrollPastMaxDisplay(l->mListState.ScrollPastMaxDisplay());
    COPY_MEMBER_FROM(l, mNumData)
    COPY_MEMBER_FROM(l, mAutoScrollPause)
    COPY_MEMBER_FROM(l, mAutoScrollSendMessages)
    COPY_MEMBER_FROM(l, mExtendedLabelEntries)
    COPY_MEMBER_FROM(l, mExtendedMeshEntries)
    COPY_MEMBER_FROM(l, mExtendedCustomEntries)
    CopyHandlerData(dynamic_cast<const UIList*>(o));
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
#ifdef VERSION_SZBE69_B8
    if (mUIListRev > 19) {
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), mUIListRev, (unsigned short)19);
    }
#endif
    UIComponent::PreLoad(bs);
}

void UIList::PostLoad(BinStream& bs) {
    UIComponent::PostLoad(bs);
    mNeedsGarbageCollection = gGCNewLists;
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

int UIList::NumDisplay() const { return mListState.NumDisplay(); }
float UIList::Speed() const { return mListState.Speed(); }
int UIList::FirstShowing() const { return mListState.FirstShowing(); }
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
    if(ChildList()) Poll();
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

DECOMP_FORCEACTIVE(UIList, "mParent")

void UIList::SetSelectedSimulateScroll(int i){
    mListDir->CompleteScroll(mListState, mWidgets);
    mListState.SetSelectedSimulateScroll(i);
    Refresh(false);
    mListDir->Poll();
    if(ChildList()) Poll();
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
    if(ChildList()) Poll();
}

void UIList::Scroll(int i){
    unk_0x1E4 = true;
    mListState.Scroll(i, false);
}

void UIList::SetParent(UIList* uilist){ mParent = uilist; }

void UIList::AutoScroll(){
    UIListProvider* prov = mListState.Provider();
    if(!prov) prov = this;
    if(prov->NumData() <= NumDisplay()){
        StopAutoScroll();
    }
    else {
        mAutoScrolling = true;
        unk_0x1D8 = 1;
        unk_0x1DC = mAutoScrollPause + TheTaskMgr.UISeconds();
    }
}

void UIList::StopAutoScroll(){
    mAutoScrolling = false;
}

void UIList::Update() {
    if (!gLoading) {
        unk_0x1E6 = false;
        UIComponent::Update();
        MILO_ASSERT(mResource && mResource->Dir(), 566);
        if (mNeedsGarbageCollection) {
            for(std::list<UIList*>::iterator it = sUIListSet.begin(); it != sUIListSet.end(); it++){
                if(*it == this){
                    it = sUIListSet.erase(it);
                }
            }
            sUIListSet.push_back(this);
        }
        mListDir = dynamic_cast<UIListDir*>(mResource->Dir());
        MILO_ASSERT(mListDir, 0x248);
        mListDir->CreateElements(this, mWidgets, mListState.mNumDisplay);

        if (TheLoadMgr.EditMode()) Refresh(false);
    }
}

void UIList::CollectGarbage(){
    for(std::list<UIList*>::iterator it = sUIListSet.begin(); it != sUIListSet.end(); it++){
        UIList* pList = *it;
        pList->unk_0x1E0++;
        MILO_ASSERT(pList->mNeedsGarbageCollection, 600);
        if(pList->unk_0x1E0 > 4){
            pList->unk_0x1E6 = true;
        }
    }
}

void UIList::Refresh(bool b){
    if(unk_0x1E6) Poll();
    else {
        mListDir->FillElements(mListState, mWidgets);
        if(b){
            int nowrap = mListState.SelectedNoWrap();
            if(nowrap >= NumProviderData() && nowrap != 0) SetSelected(NumProviderData() - 1, -1);
            else {
                if(!mListState.Provider()->IsActive(mListState.SelectedData()) && !mListState.IsScrolling()){
                    SetSelected(nowrap, -1);
                }
            }
        }
    }
}

void UIList::Enter(){
    UIComponent::Enter();
    Reset();
    mListDir->ListEntered();
}

void UIList::Poll(){
    UIComponent::Poll();
    if(Showing()){
        if(mAutoScrolling){
            if(unk_0x1DC >= 0.0f && TheTaskMgr.UISeconds() >= unk_0x1DC){
                Scroll(unk_0x1D8);
                unk_0x1DC = -1.0f;
            }
        }
        mListState.Poll(TheTaskMgr.UISeconds());
        unk_0x1E0 = 0;
        if(unk_0x1E6){
            Update();
            Refresh(true);
        }
        mListDir->PollWidgets(mWidgets);
        unk_0x1E4 = false;
        UpdateHandler();
    }
}

void UIList::DrawShowing(){
    if(unk_0x1E4){
        mListState.Poll(TheTaskMgr.UISeconds());
        unk_0x1E4 = false;
    }
    bool b = mDrawManuallyControlledWidgets;
    if(ParentList()){
        if(ParentList()->ChildList() == this) b = ParentList()->mDrawManuallyControlledWidgets;
    }
    mListDir->DrawWidgets(mListState, mWidgets, WorldXfm(), DrawState(this), 0, b);
}

void UIList::CalcBoundingBox(Box& box){
    const Transform& tf1 = WorldXfm();
    const Transform& tf2 = WorldXfm();
    box.mMin = tf1.v;
    box.mMax = tf2.v;
    mListDir->DrawWidgets(mListState, mWidgets, WorldXfm(), DrawState(this), &box, mDrawManuallyControlledWidgets);
}

const std::vector<UIListWidget*>& UIList::GetWidgets() const { return mWidgets; }

#pragma push
#pragma dont_inline on
void UIList::BoundingBoxTriangles(std::vector<std::vector<Vector3> >& vec){
    vec.clear();
    Box box;
    CalcBoundingBox(box);
    std::vector<Vector3> locVec;
    for(int i = 0; i < 2; i++){
        float f = box.mMax.x;
        if(i != 0) f = box.mMin.x;
        locVec.clear();
        locVec.push_back(Vector3(f, box.mMin.y, box.mMin.z));
        locVec.push_back(Vector3(f, box.mMin.y, box.mMax.z));
        locVec.push_back(Vector3(f, box.mMax.y, box.mMax.z));
        vec.push_back(locVec);
        locVec.clear();
        locVec.push_back(Vector3(f, box.mMin.y, box.mMin.z));
        locVec.push_back(Vector3(f, box.mMax.y, box.mMin.z));
        locVec.push_back(Vector3(f, box.mMax.y, box.mMax.z));
        vec.push_back(locVec);
    }
    for(int i = 0; i < 2; i++){
        float f = box.mMax.y;
        if(i != 0) f = box.mMin.y;
        locVec.clear();
        locVec.push_back(Vector3(box.mMin.x, f, box.mMin.z));
        locVec.push_back(Vector3(box.mMin.x, f, box.mMax.z));
        locVec.push_back(Vector3(box.mMax.x, f, box.mMax.z));
        vec.push_back(locVec);
        locVec.clear();
        locVec.push_back(Vector3(box.mMin.x, f, box.mMin.z));
        locVec.push_back(Vector3(box.mMax.x, f, box.mMin.z));
        locVec.push_back(Vector3(box.mMax.x, f, box.mMax.z));
        vec.push_back(locVec);
    }
    for(int i = 0; i < 2; i++){
        float f = box.mMax.z;
        if(i != 0) f = box.mMin.z;
        locVec.clear();
        locVec.push_back(Vector3(box.mMin.x, box.mMin.y, f));
        locVec.push_back(Vector3(box.mMin.x, box.mMax.y, f));
        locVec.push_back(Vector3(box.mMax.x, box.mMax.y, f));
        vec.push_back(locVec);
        locVec.clear();
        locVec.push_back(Vector3(box.mMin.x, box.mMin.y, f));
        locVec.push_back(Vector3(box.mMax.x, box.mMin.y, f));
        locVec.push_back(Vector3(box.mMax.x, box.mMax.y, f));
        vec.push_back(locVec);
    }
}
#pragma pop

int UIList::NumData() const { return mNumData; }

int UIList::NumProviderData() const {
    UIListProvider* p = mListState.Provider();
    if(p) return p->NumData();
    else return NumData();
}

void UIList::EnableData(Symbol s){
    MILO_ASSERT(mDataProvider, 0x390);
    mDataProvider->Enable(s);
    Refresh(false);
}

void UIList::DisableData(Symbol s){
    MILO_ASSERT(mDataProvider, 0x397);
    mDataProvider->Disable(s);
    Refresh(false);
    if(!mDataProvider->IsActive(SelectedData())){
        mListState.SetSelected(0, -1, true);
    }
}

void UIList::DimData(Symbol s){
    MILO_ASSERT(mDataProvider, 0x3A4);
    mDataProvider->Dim(s);
    Refresh(false);
}

void UIList::UnDimData(Symbol s){
    MILO_ASSERT(mDataProvider, 0x3AB);
    mDataProvider->UnDim(s);
    Refresh(false);
}

int UIList::SelectedAux() const { return mListState.Selected(); }
void UIList::SetSelectedAux(int i){ SetSelected(i, -1); }

// fn_80565528
void UIList::StartScroll(const UIListState& state, int i, bool b){
    mListDir->StartScroll(state, mWidgets, i, b);
    if(state.Provider()->IsActive(state.SelectedData()) && (!mAutoScrolling || mAutoScrollSendMessages)){
        TheUI->Handle(UIComponentScrollStartMsg(this, mUser), false);
    }
}

// fn_80565700
void UIList::CompleteScroll(const UIListState& state){
    mListDir->CompleteScroll(state, mWidgets);
    if(mAutoScrolling){
        int firstshowing = FirstShowing();
        state.Provider();
        int i3 = unk_0x1D8 > 0 ? mListState.MaxFirstShowing() : 0;
        if(firstshowing == i3){
            unk_0x1D8 = -unk_0x1D8;
            unk_0x1DC = mAutoScrollPause + TheTaskMgr.UISeconds();
        }
        else Scroll(unk_0x1D8);
    }
    if(state.Provider()->IsActive(state.SelectedData())){
        if(!mAutoScrolling || mAutoScrollSendMessages){
            TheUI->Handle(UIComponentScrollMsg(this, mUser), false);
        }
        HandleSelectionUpdated();
    }
}

void UIList::HandleSelectionUpdated(){
    UITransitionHandler::StartValueChange();
    if(ChildList()){
        ChildList()->HandleSelectionUpdated();
    }
}

void UIList::UpdateExtendedEntries(const UIListState& state){
    UIListProvider* prov = state.Provider();
    if(prov && prov->NumData() > 0){
        UIList* pMainList = mParent ? mParent : this;
        MILO_ASSERT(pMainList, 0x3FD);
        for(ObjPtrList<UILabel, ObjectDir>::iterator it = pMainList->mExtendedLabelEntries.begin(); it != pMainList->mExtendedLabelEntries.end(); ++it){
            UILabel* label = *it;
            MILO_ASSERT(label, 0x404);
            prov->UpdateExtendedText(state.SelectedDisplay(), state.SelectedData(), label);
        }
        for(ObjPtrList<RndMesh, ObjectDir>::iterator it = pMainList->mExtendedMeshEntries.begin(); it != pMainList->mExtendedMeshEntries.end(); ++it){
            RndMesh* mesh = *it;
            MILO_ASSERT(mesh, 0x40F);
            prov->UpdateExtendedMesh(state.SelectedDisplay(), state.SelectedData(), mesh);
        }
        for(ObjPtrList<Hmx::Object, ObjectDir>::iterator it = pMainList->mExtendedCustomEntries.begin(); it != pMainList->mExtendedCustomEntries.end(); ++it){
            Hmx::Object* custom = *it;
            MILO_ASSERT(custom, 0x41A);
            prov->UpdateExtendedCustom(state.SelectedDisplay(), state.SelectedData(), custom);
        }
    }
}

DataNode UIList::OnMsg(const ButtonDownMsg& msg){
    mUser = msg.GetUser();
    Symbol cntType = JoypadControllerTypePadNum(msg.GetPadNum());
    if(CanScroll()){
        int gridspan = mListState.GridSpan();
        UIList* sub = ChildList();
        UIListOrientation o = mListDir->Orientation();
        bool b = false;
        if(sub){
            if(sub->Handle(msg, false) != DataNode(kDataUnhandled, 0)){
                return DataNode(1);
            }
            if(ScrollDirection(msg, cntType, sub->mListDir->Orientation() == kUIListVertical, sub->mListState.mGridSpan) == kAction_Confirm){
            
            }
        }
    }
    else {
        if(!mListState.IsScrolling()){
            if(msg.GetAction() == kAction_Confirm){
                if(SelectScrollSelect(this, mUser)) return DataNode(1);
                SendSelect(mUser);
                return DataNode(1);
            }
            if(msg.GetAction() == kAction_Cancel){
                if(RevertScrollSelect(this, mUser, 0)){
                    return DataNode(1);
                }
            }
        }
        return DataNode(kDataUnhandled, 0);
    }
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(UIList)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE(selected_sym, OnSelectedSym)
    HANDLE_EXPR(selected_pos, SelectedPos())
    HANDLE_EXPR(selected_data, SelectedData())
    HANDLE_EXPR(num_display, NumDisplay())
    HANDLE_EXPR(first_showing, FirstShowing())
    HANDLE_ACTION(set_provider, SetProvider(_msg->Obj<UIListProvider>(2)))
    HANDLE(set_data, OnSetData)
    HANDLE_EXPR(num_data, NumProviderData())
    HANDLE_ACTION(disable_data, DisableData(_msg->Sym(2)))
    HANDLE_ACTION(enable_data, EnableData(_msg->Sym(2)))
    HANDLE_ACTION(dim_data, DimData(_msg->Sym(2)))
    HANDLE_ACTION(undim_data, UnDimData(_msg->Sym(2)))
    HANDLE(set_selected, OnSetSelected)
    HANDLE(set_selected_simulate_scroll, OnSetSelectedSimulateScroll)
    HANDLE_ACTION(set_scroll_user, SetScrollUser(_msg->Obj<LocalUser>(2)))
    HANDLE_ACTION(refresh, Refresh(true))
    HANDLE_ACTION(set_draw_manually_controlled_widgets, SetDrawManuallyControlledWidgets(_msg->Int(2)))
    HANDLE(scroll, OnScroll)
    HANDLE_EXPR(is_scrolling, IsScrolling())
    HANDLE_EXPR(is_scrolling_down, mListState.CurrentScroll() != -1)
    HANDLE_ACTION(store, Store())
    HANDLE_ACTION(undo, RevertScrollSelect(this, _msg->Obj<LocalUser>(2), 0))
    HANDLE_ACTION(confirm, Reset())
    HANDLE_ACTION(set_num_display, SetNumDisplay(_msg->Int(2)))
    HANDLE_ACTION(set_grid_span, SetGridSpan(_msg->Int(2)))
    HANDLE_ACTION(auto_scroll, AutoScroll())
    HANDLE_ACTION(stop_auto_scroll, StopAutoScroll())
    HANDLE_EXPR(parent_list, ParentList())
    HANDLE_SUPERCLASS(ScrollSelect)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0x4F0)
END_HANDLERS
#pragma pop

DataNode UIList::OnSetData(DataArray* da){
    DataArray* arr = da->Array(2);
    int i3 = da->Size() > 3 ? da->Int(3) : 0;
    bool i4 = da->Size() > 4 ? da->Int(4) : 0;
    bool i5 = da->Size() > 5 ? da->Int(5) : 0;
    if(mDataProvider) mDataProvider->SetData(arr);
    else mDataProvider = new DataProvider(arr, i3, i4, i5, this);
    SetProvider(mDataProvider);
    return DataNode(1);
}

void UIList::SetScrollUser(LocalUser* user){
    mUser = user;
}

DataNode UIList::OnSetSelected(DataArray* da){
    DataNode node = da->Evaluate(2);
    int i6 = -1;
    if(node.Type() == kDataInt){
        if(da->Size() == 4) i6 = da->Int(3);
        SetSelected(node.Int(0), i6);
        return DataNode(1);
    }
    else if(node.Type() == kDataSymbol || node.Type() == kDataString){
        bool i3 = da->Size() == 4 ? da->Int(3) : true;
        if(da->Size() == 5) i6 = da->Int(4);
        return DataNode(SetSelected(node.ForceSym(0), i3, i6));
    }
    else {
        MILO_FAIL("bad arg to set_selected");
        return DataNode(0);
    }
}

DataNode UIList::OnSetSelectedSimulateScroll(DataArray* da){
    DataNode node = da->Evaluate(2);
    if(node.Type() == kDataInt){
        SetSelectedSimulateScroll(node.Int(0));
        return DataNode(1);
    }
    else if(node.Type() == kDataSymbol || node.Type() == kDataString){
        bool b3 = da->Size() == 4 ? da->Int(3) : true;
        return DataNode(SetSelectedSimulateScroll(node.ForceSym(0), b3));
    }
    else {
        MILO_FAIL("bad arg to set_selected_simulate_scroll");
        return DataNode(0);
    }
}

DataNode UIList::OnScroll(DataArray* da){
    int scroll = da->Int(2);
    mUser = da->Size() > 3 ? da->Obj<LocalUser>(3) : 0;
    Scroll(scroll);
    return DataNode(1);
}

DataNode UIList::OnSelectedSym(DataArray* da){
    if(da->Size() > 2){
        return DataNode(SelectedSym(da->Int(2)));
    }
    else return DataNode(SelectedSym(true));
}

bool UIList::IsEmptyValue() const { return mListState.SelectedData() == -1; }

void UIList::FinishValueChange(){
    UpdateExtendedEntries(mListState);
    UITransitionHandler::FinishValueChange();
}

void UIList::SetDrawManuallyControlledWidgets(bool b){ mDrawManuallyControlledWidgets = b; }

BEGIN_PROPSYNCS(UIList)
    SYNC_PROP_SET(display_num, mListState.mNumDisplay, SetNumDisplay(_val.Int(0)))
    SYNC_PROP_SET(grid_span, mListState.mGridSpan, SetGridSpan(_val.Int(0)))
    SYNC_PROP_SET(circular, mListState.mCircular, SetCircular(_val.Int(0)))
    SYNC_PROP_SET(scroll_time, mListState.Speed(), SetSpeed(_val.Float(0)))
    SYNC_PROP(paginate, mPaginate)
    SYNC_PROP_SET(min_display, mListState.MinDisplay(), mListState.SetMinDisplay(_val.Int(0)))
    SYNC_PROP_SET(scroll_past_min_display, mListState.ScrollPastMinDisplay(), mListState.SetScrollPastMinDisplay(_val.Int(0)))
    SYNC_PROP_SET(scroll_past_min_display, mListState.ScrollPastMinDisplay(), mListState.SetScrollPastMinDisplay(_val.Int(0)))
    SYNC_PROP_SET(max_display, mListState.MaxDisplay(), mListState.SetMaxDisplay(_val.Int(0)))
    SYNC_PROP_SET(scroll_past_max_display, mListState.ScrollPastMaxDisplay(), mListState.SetScrollPastMaxDisplay(_val.Int(0)))
    SYNC_PROP_MODIFY(num_data, mNumData, Update())
    SYNC_PROP(auto_scroll_pause, mAutoScrollPause)
    SYNC_PROP(auto_scroll_send_messages, mAutoScrollSendMessages)
    SYNC_PROP(extended_label_entries, mExtendedLabelEntries)
    SYNC_PROP(extended_mesh_entries, mExtendedMeshEntries)
    SYNC_PROP(extended_custom_entries, mExtendedCustomEntries)
    SYNC_PROP_SET(in_anim, GetInAnim(), SetInAnim(_val.Obj<RndAnimatable>(0)))
    SYNC_PROP_SET(out_anim, GetOutAnim(), SetOutAnim(_val.Obj<RndAnimatable>(0)))
    SYNC_SUPERCLASS(ScrollSelect)
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS