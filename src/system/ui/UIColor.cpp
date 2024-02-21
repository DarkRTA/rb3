#include "ui/UIColor.h"

UIColor::UIColor() : mColor() {
    
}

#pragma dont_inline on
Hmx::Color UIColor::GetColor() const {
    return mColor;
}
#pragma dont_inline reset

void UIColor::SetColor(const Hmx::Color& color){
    mColor = color;
}
