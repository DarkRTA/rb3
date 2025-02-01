#include "ui/UIList.h"
#include "ui/UIListDir.h"
#include "ui/UIListWidget.h"
#include <algorithm>
#include "obj/ObjVersion.h"
#include "utl/Std.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

INIT_REVS(UIListDir)

DECOMP_FORCEACTIVE(UIListDir, __FILE__, "( 0) <= (change) && (change) <= ( 1)")

namespace {
    class WidgetDrawSort {
    public:
        bool operator()(UIListWidget *w1, UIListWidget *w2) {
            return w1->DrawOrder() < w2->DrawOrder();
        }
    };
}

UIListDir::UIListDir()
    : mOrientation(kUIListVertical), mFadeOffset(0), mElementSpacing(50.0f),
      mScrollHighlightChange(0.5f), mTestMode(0), mTestState(this, this),
      mTestNumData(100), mTestGapSize(0.0f), mTestComponentState(UIComponent::kFocused),
      mTestDisableElements(0), unk1fc(), mDirection(0) {
    mTestState.SetNumDisplay(5, true);
    mTestState.SetGridSpan(1, true);
    mTestState.SetSelected(0, -1, true);
}

UIListDir::~UIListDir() { DeleteAll(unk1fc); }

UIListOrientation UIListDir::Orientation() const { return mOrientation; }
float UIListDir::ElementSpacing() const { return mElementSpacing; }

// fn_805693B0
void UIListDir::BuildDrawState(
    UIListWidgetDrawState &, const UIListState &, UIComponent::State, float
) const {}

void UIListDir::SetElementPos(Vector3 &v, float f1, int i2, float f3, float f4) const {
    v.Zero();
    int floored = std::floor(f1);
    float f3toset =
        mElementSpacing * ((f1 - (float)floored) + (float)(floored / i2)) + f3;
    float f2toset = mElementSpacing * (float)(floored % i2) + f4;
    if (mOrientation == kUIListVertical) {
        v.z -= f3toset;
        v.x += f2toset;
    } else {
        v.x += f3toset;
        v.z -= f2toset;
    }
}

UIList *UIListDir::SubList(int i, std::vector<UIListWidget *> &vec) {
    for (std::vector<UIListWidget *>::iterator it = vec.begin(); it != vec.end(); it++) {
        UIList *l = (*it)->SubList(i);
        if (l)
            return l;
    }
    return nullptr;
}

void UIListDir::CreateElements(UIList *uilist, std::vector<UIListWidget *> &vec, int i) {
    DeleteAll(vec);
    for (ObjDirItr<UIListWidget> it(this, true); it != 0; ++it) {
        UIListWidget *widget =
            dynamic_cast<UIListWidget *>(Hmx::Object::NewObject(it->ClassName()));
        widget->ResourceCopy(it);
        widget->SetParentList(uilist);
        vec.push_back(widget);
    }
    std::sort(vec.begin(), vec.end(), WidgetDrawSort());
    for (std::vector<UIListWidget *>::iterator it = vec.begin(); it != vec.end(); ++it) {
        (*it)->CreateElements(uilist, i);
    }
}

void UIListDir::FillElements(const UIListState &state, std::vector<UIListWidget *> &vec) {
    int num = state.NumDisplayWithData();
    for (int i = 0; i < num; i++) {
        FillElement(state, vec, i);
    }
}

// fn_8056AEBC
void UIListDir::FillElement(
    const UIListState &state, std::vector<UIListWidget *> &vec, int i
) {
    int disp = state.Display2Data(i);
    if (disp != -1) {
        int snapped = state.SnappedDataForDisplay(i);
        if (snapped >= 0)
            disp = snapped;
        int disp2show = state.Display2Showing(i);
        bool isnegone = i == -1;
        ClampEq(i, 0, state.NumDisplay());
        for (std::vector<UIListWidget *>::iterator it = vec.begin(); it != vec.end();
             ++it) {
            (*it)->Fill(*state.Provider(), i, disp2show, disp);
            if (isnegone && snapped >= 0) {
                (*it)->Fill(
                    *state.Provider(), 1, state.Display2Showing(0), state.Display2Data(0)
                );
            }
        }
    }
}

// fn_8056B014
void UIListDir::DrawWidgets(
    const UIListState &state,
    std::vector<UIListWidget *> &vec,
    const Transform &tf,
    UIComponent::State compstate,
    Box *box,
    bool bptr
) {
    // some ctor
    UIListWidgetDrawState drawstate;
    float f1;
    UIList *sublist = SubList(state.SelectedDisplay(), vec);
    if (sublist) {
        f1 =
            (float)sublist->SelectedDisplay() * sublist->GetUIListDir()->ElementSpacing();
    } else
        f1 = 0;
    BuildDrawState(drawstate, state, compstate, f1);
    bool scrolling = state.IsScrolling();
    for (std::vector<UIListWidget *>::iterator it = vec.begin(); it != vec.end(); ++it) {
        UIListWidget *curWidget = *it;
        UIListWidgetDrawType drawType = curWidget->WidgetDrawType();
        if (drawType == 0 || (drawType == 3 && (bptr || compstate == 1))
            || (drawType == 1 && compstate == 1)) {
            DrawCommand cmd = kDrawAll;
            if (scrolling)
                cmd = kExcludeFirst;
            curWidget->Draw(drawstate, state, tf, compstate, box, cmd);
        }
    }
    if (scrolling) {
        for (std::vector<UIListWidget *>::iterator it = vec.begin(); it != vec.end();
             ++it) {
            UIListWidget *curWidget = *it;
            UIListWidgetDrawType drawType = curWidget->WidgetDrawType();
            if (drawType == 0 || (drawType == 1 && compstate == 1)) {
                curWidget->Draw(drawstate, state, tf, compstate, box, kDrawFirst);
            }
        }
    }
}

void UIListDir::PollWidgets(std::vector<UIListWidget *> &widgets) {
    for (std::vector<UIListWidget *>::iterator it = widgets.begin(); it != widgets.end();
         ++it) {
        (*it)->Poll();
    }
}

void UIListDir::ListEntered() { Handle(start_msg, false); }

void UIListDir::StartScroll(const UIListState &state, int i, bool b) {
    StartScroll(state, unk1fc, i, b);
}

void UIListDir::CompleteScroll(const UIListState &state) {
    CompleteScroll(state, unk1fc);
}

void UIListDir::StartScroll(
    const UIListState &state, std::vector<UIListWidget *> &widgets, int i, bool b
) {
    mDirection = i;
    MILO_ASSERT(mDirection, 499);
    for (std::vector<UIListWidget *>::iterator it = widgets.begin(); it != widgets.end();
         ++it) {
        (*it)->StartScroll(mDirection, b);
    }
    if (b) {
        FillElement(state, widgets, mDirection > 0 ? state.mNumDisplay : -1);
    }
}

void UIListDir::CompleteScroll(
    const UIListState &state, std::vector<UIListWidget *> &widgets
) {
    for (std::vector<UIListWidget *>::iterator it = widgets.begin(); it != widgets.end();
         ++it) {
        (*it)->CompleteScroll(state, mDirection);
    }
    if (mDirection == 1 && state.SnappedDataForDisplay(0) >= 0) {
        FillElement(state, widgets, 0);
    }
}

void UIListDir::Reset() {
    mTestState.SetSelected(0, -1, true);
    FillElements(mTestState, unk1fc);
}

SAVE_OBJ(UIListDir, 0x21F);

void UIListDir::PreLoad(BinStream &bs) {
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    RndDir::PreLoad(bs);
}

void UIListDir::PostLoad(BinStream &bs) {
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
    bs >> numdisplay >> mElementSpacing >> speed >> mTestNumData >> compstate
        >> mTestGapSize;
    bs >> mTestDisableElements;
    if (gRev != 0)
        bs >> mScrollHighlightChange;
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

void UIListDir::SyncObjects() {
    RndDir::SyncObjects();
    if (LOADMGR_EDITMODE) {
        CreateElements(0, unk1fc, mTestState.mNumDisplay);
        FillElements(mTestState, unk1fc);
    }
}

void UIListDir::DrawShowing() {
    if (mTestMode && LOADMGR_EDITMODE) {
        DrawWidgets(mTestState, unk1fc, WorldXfm(), mTestComponentState, 0, false);
    } else
        RndDir::DrawShowing();
}

void UIListDir::Poll() {
    if (LOADMGR_EDITMODE) {
        RndDir::Poll();
        if (mTestMode) {
            mTestState.Poll(TheTaskMgr.Seconds(TaskMgr::kRealTime));
            PollWidgets(unk1fc);
        }
    }
}

int UIListDir::NumData() const { return mTestNumData; }
float UIListDir::GapSize(int, int, int, int) const { return mTestGapSize; }
bool UIListDir::IsActive(int i) const {
    if (mTestDisableElements)
        return !(i % 2);
    else
        return true;
}

BEGIN_PROPSYNCS(UIListDir)
    SYNC_PROP_SET(orientation, mOrientation, mOrientation = (UIListOrientation)_val.Int())
    SYNC_PROP(fade_offset, mFadeOffset)
    SYNC_PROP(element_spacing, mElementSpacing)
    SYNC_PROP(scroll_highlight_change, mScrollHighlightChange)
    SYNC_PROP(test_mode, mTestMode)
    SYNC_PROP(test_num_data, mTestNumData)
    SYNC_PROP(test_gap_size, mTestGapSize)
    SYNC_PROP_SET(
        test_num_display,
        mTestState.mNumDisplay,
        mTestState.SetNumDisplay(_val.Int(), true)
    )
    SYNC_PROP_SET(
        test_grid_span, mTestState.mGridSpan, mTestState.SetGridSpan(_val.Int(), true)
    )
    SYNC_PROP_SET(test_scroll_time, mTestState.Speed(), mTestState.SetSpeed(_val.Float()))
    SYNC_PROP_SET(
        test_list_state,
        mTestComponentState,
        mTestComponentState = (UIComponent::State)_val.Int()
    )
    SYNC_PROP_MODIFY(test_disable_elements, mTestDisableElements, Reset())
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS

BEGIN_HANDLERS(UIListDir)
    HANDLE_ACTION(test_scroll, mTestState.Scroll(_msg->Int(2), false))
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x2C2)
END_HANDLERS
