#include "ui/UIListArrow.h"
#include "obj/Object.h"
#include "rndobj/Mesh.h"
#include "rndobj/Anim.h"
#include "ui/UIListWidget.h"

INIT_REVS(UIListArrow)

UIListArrow::UIListArrow() : mMesh(this, 0), mScrollAnim(this, 0), mPosition(kUIListArrowBack), mShowOnlyScroll(0), mOnHighlight(0) {

}

SAVE_OBJ(UIListArrow, 0x47);

void UIListArrow::Load(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(1, 0)
    UIListWidget::Load(bs);
    int dump; bool tmp, tmp2;
    bs >> mMesh;
    bs >> dump;
    bs >> tmp2;
    mShowOnlyScroll = tmp2;
    bs >> tmp;
    mOnHighlight = tmp;
    mPosition = (UIListArrowPosition)dump;
    if (gRev != 0) bs >> mScrollAnim;
}

BEGIN_COPYS(UIListArrow)
    GET_COPY_AND_ASSERT(UIListArrow, 92)
    COPY_MEMBER(mShowOnlyScroll)
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


UIListArrow::~UIListArrow() {}
