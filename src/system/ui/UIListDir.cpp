#include "ui/UIListDir.h"
#include "ui/UIListWidget.h"
#include <algorithm>
#include "obj/ObjVersion.h"
#include "utl/Messages.h"

INIT_REVS(UIListDir)

namespace {

    // struct WidgetDrawSort {
    //     bool operator(UIListWidget*, UIListWidget*){}
    // };

    // bool WidgetDrawSort(UIListWidget*, UIListWidget*){

    // }
}

UIListDir::UIListDir() : mOrientation(kUIListVertical), mFadeOffset(0), mElementSpacing(50.0f), mScrollHighlightChange(0.5f),
    mTestMode(0), mTestState(this, this), mTestNumData(100), mTestGapSize(0.0f), mTestComponentState(UIComponent::kFocused),
    mTestDisableElements(0), unk1fc(), mDirection(0) {
    mTestState.SetNumDisplay(5, true);
    mTestState.SetGridSpan(1, true);
    mTestState.SetSelected(0, -1, true);
}

UIListDir::~UIListDir(){

}

UIListOrientation UIListDir::Orientation() const { return mOrientation; }
float UIListDir::ElementSpacing() const { return mElementSpacing; }

UIList* UIListDir::SubList(int i, std::vector<UIListWidget*>& vec){
    for(std::vector<UIListWidget*>::iterator it = vec.begin(); it != vec.end(); it++){
        UIList* l = (*it)->SubList(i);
        if(l) return l;
    }
    return 0;
}

void UIListDir::CreateElements(UIList* uilist, std::vector<UIListWidget*>& vec, int i){
    for(std::vector<UIListWidget*>::iterator it = vec.begin(); it != vec.end(); it++){
        delete *it;
    }
    vec.clear();
    for(ObjDirItr<UIListWidget> it(this, true); it != 0; ++it){
        UIListWidget* widget = dynamic_cast<UIListWidget*>(Hmx::Object::NewObject(it->ClassName()));
        widget->ResourceCopy(it);
        widget->SetParentList(uilist);
        vec.push_back(widget);
    }
    // std::sort(vec.begin(), vec.end(), WidgetDrawSort);
    for(std::vector<UIListWidget*>::iterator it = vec.begin(); it != vec.end(); ++it){
        (*it)->CreateElements(uilist, i);
    }
}

void UIListDir::FillElements(const UIListState& state, std::vector<UIListWidget*>& vec){
    int num = state.NumDisplayWithData();
    for(int i = 0; i < num; i++){
        FillElement(state, vec, i);
    }
}

void UIListDir::PollWidgets(std::vector<UIListWidget*>& widgets){
    for(std::vector<UIListWidget*>::iterator it = widgets.begin(); it != widgets.end(); ++it){
        (*it)->Poll();
    }
}

void UIListDir::ListEntered(){
    Handle(start_msg, false);
}

void UIListDir::StartScroll(const UIListState& state, int i, bool b){
    StartScroll(state, unk1fc, i, b);
}

void UIListDir::CompleteScroll(const UIListState& state){
    CompleteScroll(state, unk1fc);
}

void UIListDir::StartScroll(const UIListState& state, std::vector<UIListWidget*>& widgets, int i, bool b){
    mDirection = i;
    MILO_ASSERT(mDirection, 499);
    for(std::vector<UIListWidget*>::iterator it = widgets.begin(); it != widgets.end(); ++it){
        (*it)->StartScroll(mDirection, b);
    }
    if(b){
        FillElement(state, widgets, mDirection > 0 ? state.mNumDisplay : -1);
    }
}

void UIListDir::CompleteScroll(const UIListState& state, std::vector<UIListWidget*>& widgets){
    for(std::vector<UIListWidget*>::iterator it = widgets.begin(); it != widgets.end(); ++it){
        (*it)->CompleteScroll(state, mDirection);
    }
    if(mDirection == 1 && state.SnappedDataForDisplay(0) >= 0){
        FillElement(state, widgets, 0);
    }
}

void UIListDir::Reset(){
    mTestState.SetSelected(0, -1, true);
    FillElements(mTestState, unk1fc);
}

SAVE_OBJ(UIListDir, 0x21F);

void UIListDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    RndDir::PreLoad(bs);
}

void UIListDir::PostLoad(BinStream& bs){
    RndDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    int orientation;
    bs >> orientation;
    bs >> mFadeOffset;
    mOrientation = (UIListOrientation)orientation;
    bs >> mTestMode;
    int numdisplay, compstate;
    float speed;
    bs >> numdisplay >> mElementSpacing >> speed >> mTestNumData >> compstate >> mTestGapSize;
    bs >> mTestDisableElements;
    if(gRev != 0) bs >> mScrollHighlightChange;
    mTestState.SetNumDisplay(numdisplay, true);
    mTestState.SetSpeed(speed);
    mTestComponentState = (UIComponent::State)compstate;
}

BEGIN_COPYS(UIListDir)
    COPY_SUPERCLASS(RndDir)
    CREATE_COPY(UIListDir)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mOrientation)
        COPY_MEMBER(mFadeOffset)
        COPY_MEMBER(mElementSpacing)
        COPY_MEMBER(mScrollHighlightChange)
        COPY_MEMBER(mTestMode)
        mTestState.SetNumDisplay(c->mTestState.mNumDisplay, true);
        mTestState.SetGridSpan(c->mTestState.mGridSpan, true);
        mTestState.SetSpeed(c->mTestState.Speed());
        COPY_MEMBER(mTestNumData)
        COPY_MEMBER(mTestComponentState)
        COPY_MEMBER(mTestGapSize)
        COPY_MEMBER(mTestDisableElements)
    END_COPYING_MEMBERS
END_COPYS

void UIListDir::SyncObjects(){
    RndDir::SyncObjects();
    if(TheLoadMgr.EditMode()){
        CreateElements(0, unk1fc, mTestState.mNumDisplay);
        FillElements(mTestState, unk1fc);
    }
}

void UIListDir::DrawShowing(){
    if(mTestMode && TheLoadMgr.EditMode()){
        DrawWidgets(mTestState, unk1fc, WorldXfm(), mTestComponentState, 0, false);
    }
    else RndDir::DrawShowing();
}

