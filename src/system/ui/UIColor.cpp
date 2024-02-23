#include "ui/UIColor.h"

UIColor::UIColor() : mColor() {
    
}

Hmx::Color UIColor::GetColor() const {
    return mColor;
}

void UIColor::SetColor(const Hmx::Color& color){
    mColor = color;
}
