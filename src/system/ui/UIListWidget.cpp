#include "ui/UIListWidget.h"

UIListWidget::UIListWidget() : mDefaultColor(this, 0) {
    
}

float UIListWidget::DrawOrder() const { return mDrawOrder; }
