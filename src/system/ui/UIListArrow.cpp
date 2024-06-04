#include "ui/UIListArrow.h"
#include "obj/Object.h"
#include "rndobj/Mesh.h"
#include "rndobj/Anim.h"
#include "ui/UIListWidget.h"
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
    CREATE_COPY(UIListArrow, a);
    MILO_ASSERT(a, 0x5C);
    COPY_MEM(a, mMesh)
    COPY_MEM(a, mPosition)
    COPY_MEM(a, mShowOnlyScroll)
    COPY_MEM(a, mOnHighlight)
    COPY_MEM(a, mScrollAnim)
END_COPYS

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