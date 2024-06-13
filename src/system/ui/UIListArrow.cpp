#include "ui/UIListArrow.h"
#include "obj/Object.h"
#include "rndobj/Mesh.h"
#include "rndobj/Anim.h"
#include "ui/UIListWidget.h"
#include "ui/UIList.h"
#include "utl/Symbols.h"

INIT_REVS(UIListArrow)

UIListArrow::UIListArrow() : mMesh(this, 0), mScrollAnim(this, 0), mPosition(kUIListArrowBack), mShowOnlyScroll(0), mOnHighlight(0) {

}

SAVE_OBJ(UIListArrow, 0x47);

void UIListArrow::Load(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(1, 0)
    UIListWidget::Load(bs);
    int dump; bool tmp;
    bs >> mMesh >> dump >> mShowOnlyScroll >> tmp;
    mOnHighlight = tmp;
    mPosition = (UIListArrowPosition)dump;
    if (gRev != 0) bs >> mScrollAnim;
}

BEGIN_COPYS(UIListArrow)
    COPY_SUPERCLASS(UIListWidget)
    CREATE_COPY_AS(UIListArrow, a);
    MILO_ASSERT(a, 0x5C);
    COPY_MEMBER_FROM(a, mMesh)
    COPY_MEMBER_FROM(a, mPosition)
    COPY_MEMBER_FROM(a, mShowOnlyScroll)
    COPY_MEMBER_FROM(a, mOnHighlight)
    COPY_MEMBER_FROM(a, mScrollAnim)
END_COPYS

// fn_805681EC
void UIListArrow::Draw(const UIListWidgetDrawState& drawstate, const UIListState& liststate, const Transform& tf, UIComponent::State compstate, Box* box, DrawCommand cmd){
    if(!mMesh || cmd == kDrawFirst) return;
    const Vector3* vec = mOnHighlight ? &drawstate.mHighlightPos : (mPosition == kUIListArrowBack ? &drawstate.mFirstPos : &drawstate.mLastPos);
    bool onhighlight = mOnHighlight;

    if(box || !mShowOnlyScroll || 
        ((mPosition != kUIListArrowBack || liststate.CanScrollBack(onhighlight)) &&
        (mPosition != kUIListArrowNext || liststate.CanScrollNext(mOnHighlight)))){
        Transform& worldxfm = mMesh->WorldXfm();
        Transform xfm1 = worldxfm;
        Transform xfm2 = xfm1;
        if(ParentList()){
            ParentList()->AdjustTransSelected(xfm2);
        }
        CalcXfm(tf, *vec, xfm2);
        DrawMesh(mMesh, drawstate.mHighlightElementState, compstate, xfm2, box);
        mMesh->SetWorldXfm(xfm1);
    }    
}

void UIListArrow::StartScroll(int i, bool) { // holy fakematch
    if (mScrollAnim == NULL) return;
    if (i < 0) {
        if (!mPosition) goto a;
    }
    if (0 >= i) return;
    if (mPosition != 1) return;
    a:
    mScrollAnim->Animate(0, false, 0);
}

BEGIN_HANDLERS(UIListArrow)
    HANDLE_SUPERCLASS(UIListWidget)
    HANDLE_CHECK(0x96)
END_HANDLERS

BEGIN_PROPSYNCS(UIListArrow)
    SYNC_PROP(mesh, mMesh)
    SYNC_PROP(scroll_anim, mScrollAnim)
    SYNC_PROP_SET(position, mPosition, mPosition = (UIListArrowPosition)_val.Int(0))
    SYNC_PROP(show_only_scroll, mShowOnlyScroll)
    SYNC_PROP(on_highlight, mOnHighlight)
    SYNC_SUPERCLASS(UIListWidget)
END_PROPSYNCS