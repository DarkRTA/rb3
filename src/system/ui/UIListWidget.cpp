#include "ui/UIListWidget.h"

UIListWidget::UIListWidget() : mDrawOrder(0.0f), mDisabledAlphaScale(1.0f), mDefaultColor(this, 0) {
    
}

float UIListWidget::DrawOrder() const { return mDrawOrder; }
float UIListWidget::DisabledAlphaScale() const { return mDisabledAlphaScale; }
UIListWidgetDrawType UIListWidget::WidgetDrawType() const { return mWidgetDrawType; }
UIList* UIListWidget::ParentList(){ return mParentList; }

void UIListWidget::ResourceCopy(const UIListWidget* widget){
    Copy(widget, kCopyShallow);
}

void UIListWidget::SetParentList(UIList* list){ mParentList = list; }

SAVE_OBJ(UIListWidget, 0x97);

BEGIN_HANDLERS(UIListWidget)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xD0)
END_HANDLERS
