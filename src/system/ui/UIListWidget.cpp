#include "ui/UIListWidget.h"
#include "utl/Symbols.h"

#include "decomp.h"

INIT_REVS(UIListWidget);

UIListWidget::UIListWidget() : mDrawOrder(0.0f), mDisabledAlphaScale(1.0f), mDefaultColor(this, 0) {
    for(int i = 0; i < kNumUIListWidgetStates; i++){
        std::vector<ObjPtr<UIColor, class ObjectDir> > vec;
        for(int j = 0; j < UIComponent::kNumStates; j++){
            vec.push_back(ObjPtr<UIColor, class ObjectDir>(this, 0));
        }
        // mColors.push_back(vec); // this causes an error
    }
}

float UIListWidget::DrawOrder() const { return mDrawOrder; }
float UIListWidget::DisabledAlphaScale() const { return mDisabledAlphaScale; }
UIListWidgetDrawType UIListWidget::WidgetDrawType() const { return mWidgetDrawType; }
UIList* UIListWidget::ParentList(){ return mParentList; }

void UIListWidget::ResourceCopy(const UIListWidget* widget){
    Copy(widget, kCopyShallow);
}

void UIListWidget::SetParentList(UIList* list){ mParentList = list; }

void UIListWidget::DrawMesh(RndMesh* mesh, UIListWidgetState, UIComponent::State, const Transform&, Box*){
    MILO_ASSERT(mesh, 0x40);
}

UIColor* UIListWidget::DisplayColor(UIListWidgetState element_state, UIComponent::State list_state) const {
    MILO_ASSERT(element_state < kNumUIListWidgetStates, 99);
    MILO_ASSERT(list_state < UIComponent::kNumStates, 100);
    UIColor* theColor = mColors[element_state][list_state];
    if(theColor && mDefaultColor) return theColor;
    else return 0;
}

void UIListWidget::SetColor(UIListWidgetState ws, UIComponent::State cs, UIColor* color){
    MILO_ASSERT(ws < kNumUIListWidgetStates, 0x7C);
    MILO_ASSERT(cs < UIComponent::kNumStates, 0x7D);
    ObjPtr<UIColor, class ObjectDir>& theColor = mColors[ws][cs];
    theColor = color;
}

SAVE_OBJ(UIListWidget, 0x97);

DECOMP_FORCEACTIVE(UIListWidget,
    "ObjPtr_p.h",
    "f.Owner()",
    ""
)

BEGIN_LOADS(UIListWidget)
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mDrawOrder;
    if(gRev < 1){
        int i, j;
        bs >> i >> j;
    }
    bs >> mDefaultColor;
    int x;
    bs >> x;
    mWidgetDrawType = (UIListWidgetDrawType)x;
    if(gRev > 1) bs >> mDisabledAlphaScale;
END_LOADS

BEGIN_COPYS(UIListWidget)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(UIListWidget, w)
    MILO_ASSERT(w, 0xC6);
    COPY_MEM(w, mDrawOrder)
    COPY_MEM(w, mDisabledAlphaScale)
    COPY_MEM(w, mDefaultColor)
    COPY_MEM(w, mColors)
    COPY_MEM(w, mWidgetDrawType)
END_COPYS

BEGIN_HANDLERS(UIListWidget)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xD0)
END_HANDLERS

BEGIN_PROPSYNCS(UIListWidget)
    SYNC_PROP(draw_order, mDrawOrder)
    SYNC_PROP(disabled_alpha_scale, mDisabledAlphaScale)
    SYNC_PROP(default_color, mDefaultColor)
    SYNC_PROP_SET(widget_draw_type, (int&)mWidgetDrawType, mWidgetDrawType = (UIListWidgetDrawType)_val.Int(0))
    SYNC_PROP_SET(active_normal_color, (Hmx::Object*)mColors[kUIListWidgetActive][UIComponent::kNormal], SetColor(kUIListWidgetActive, UIComponent::kNormal, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(active_focused_color, (Hmx::Object*)mColors[kUIListWidgetActive][UIComponent::kFocused], SetColor(kUIListWidgetActive, UIComponent::kFocused, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(active_disabled_color, (Hmx::Object*)mColors[kUIListWidgetActive][UIComponent::kDisabled], SetColor(kUIListWidgetActive, UIComponent::kDisabled, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(active_selecting_color, (Hmx::Object*)mColors[kUIListWidgetActive][UIComponent::kSelecting], SetColor(kUIListWidgetActive, UIComponent::kSelecting, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(active_selected_color, (Hmx::Object*)mColors[kUIListWidgetActive][UIComponent::kSelected], SetColor(kUIListWidgetActive, UIComponent::kSelected, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(highlight_normal_color, (Hmx::Object*)mColors[kUIListWidgetHighlight][UIComponent::kNormal], SetColor(kUIListWidgetHighlight, UIComponent::kNormal, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(highlight_focused_color, (Hmx::Object*)mColors[kUIListWidgetHighlight][UIComponent::kFocused], SetColor(kUIListWidgetHighlight, UIComponent::kFocused, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(highlight_disabled_color, (Hmx::Object*)mColors[kUIListWidgetHighlight][UIComponent::kDisabled], SetColor(kUIListWidgetHighlight, UIComponent::kDisabled, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(highlight_selecting_color, (Hmx::Object*)mColors[kUIListWidgetHighlight][UIComponent::kSelecting], SetColor(kUIListWidgetHighlight, UIComponent::kSelecting, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(highlight_selected_color, (Hmx::Object*)mColors[kUIListWidgetHighlight][UIComponent::kSelected], SetColor(kUIListWidgetHighlight, UIComponent::kSelected, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(inactive_normal_color, (Hmx::Object*)mColors[kUIListWidgetInactive][UIComponent::kNormal], SetColor(kUIListWidgetInactive, UIComponent::kNormal, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(inactive_focused_color, (Hmx::Object*)mColors[kUIListWidgetInactive][UIComponent::kFocused], SetColor(kUIListWidgetInactive, UIComponent::kFocused, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(inactive_disabled_color, (Hmx::Object*)mColors[kUIListWidgetInactive][UIComponent::kDisabled], SetColor(kUIListWidgetInactive, UIComponent::kDisabled, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(inactive_selecting_color, (Hmx::Object*)mColors[kUIListWidgetInactive][UIComponent::kSelecting], SetColor(kUIListWidgetInactive, UIComponent::kSelecting, _val.Obj<UIColor>(0)))
    SYNC_PROP_SET(inactive_selected_color, (Hmx::Object*)mColors[kUIListWidgetInactive][UIComponent::kSelected], SetColor(kUIListWidgetInactive, UIComponent::kSelected, _val.Obj<UIColor>(0)))
END_PROPSYNCS
