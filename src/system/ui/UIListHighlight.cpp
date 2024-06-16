#include "ui/UIListHighlight.h"
#include "ui/UIList.h"
#include "utl/Symbols.h"

INIT_REVS(UIListHighlight)

UIListHighlight::UIListHighlight() : mMesh(this, 0) {

}

SAVE_OBJ(UIListHighlight, 0x28)

BEGIN_LOADS(UIListHighlight)
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    LOAD_SUPERCLASS(UIListWidget)
    bs >> mMesh;
END_LOADS

BEGIN_COPYS(UIListHighlight)
    COPY_SUPERCLASS(UIListWidget)
    CREATE_COPY_AS(UIListHighlight, h)
    MILO_ASSERT(h, 0x38);
    COPY_MEMBER_FROM(h, mMesh)
END_COPYS

void UIListHighlight::Draw(const UIListWidgetDrawState& drawstate, const UIListState& liststate, const Transform& tf, UIComponent::State compstate, Box* box, DrawCommand cmd){
    if(!mMesh || cmd == kDrawFirst) return;
    Transform& worldxfm = mMesh->WorldXfm();
    Transform xfm1 = worldxfm;
    Transform xfm2 = xfm1;
    if(ParentList()){
        ParentList()->AdjustTransSelected(xfm2);
    }
    CalcXfm(tf, drawstate.mHighlightPos, xfm2);
    DrawMesh(mMesh, drawstate.mHighlightElementState, compstate, xfm2, box);
    mMesh->SetWorldXfm(xfm1);
}

BEGIN_HANDLERS(UIListHighlight)
    HANDLE_SUPERCLASS(UIListWidget)
    HANDLE_CHECK(0x59)
END_HANDLERS

BEGIN_PROPSYNCS(UIListHighlight)
    SYNC_PROP(mesh, mMesh)
    SYNC_SUPERCLASS(UIListWidget)
END_PROPSYNCS