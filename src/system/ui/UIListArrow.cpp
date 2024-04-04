#include "ui/UIListArrow.h"
#include "rndobj/Mesh.h"
#include "rndobj/Anim.h"

UIListArrow::UIListArrow() : mMesh(this, 0), mScrollAnim(this, 0), mPosition(kUIListArrowBack), mShowOnlyScroll(0), mOnHighlight(0) {

}

SAVE_OBJ(UIListArrow, 0x47);
