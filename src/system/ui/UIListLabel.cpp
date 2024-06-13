#include "ui/UIListLabel.h"
#include "ui/UIList.h"

UIListLabel::UIListLabel() : mLabel(this, 0) {

}

const char* UIListLabel::GetDefaultText() const {
    if(mLabel) return mLabel->GetDefaultText();
    else return gNullStr;
}

UIListSlotElement* UIListLabel::CreateElement(UIList* uilist){
    MILO_ASSERT(mLabel, 0x80);
    UILabel* l = dynamic_cast<UILabel*>(Hmx::Object::NewObject(mLabel->ClassName()));
    MILO_ASSERT(l, 0x83);
    l->ResourceCopy(mLabel);
    l->SetTextToken(gNullStr);
    return new UIListLabelElement(this, l);
}